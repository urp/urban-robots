/***************************************************************************
 *            surface-generators.h
 *
 *  Fri Jan 28 14:37:40 2011
 *  Copyright  2011  Peter Urban
 *  <s9peurba@stud.uni-saarland.de>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

# pragma once

# include "common.hpp"

# include "surface/tri_surface/tri_surface.hpp"

//# define DBG_FLAT_SIMPLE_RECTLINEAR_TRIAGULATOR__PER_QUAD


namespace flat
{

  struct NoTransform
  {
    void operator () ( const std::shared_ptr< PointCloud> & )    const  {   };
  };


  // - shifts the surface such that the pivot (position averaged over all samples)
  // fit into the cube [pivot-0.5,pivot+.5]^3) along dimensions n for which rescale_flag[n]==true
  // - rescales the surface such that the bounds of the surface fit into the cube [pivot-0.5,pivot+.5]^3)
  // along dimensions n for which rescale_flag[n]==true
  // returns the new bounds of the sample
  struct CenterRescaleTransform
  {
    const utk::vecn3b   center_flags, rescale_flags;

    CenterRescaleTransform( const utk::vecn3b& 	center, const utk::vecn3b& 	rescale )
    : center_flags( center ), rescale_flags( rescale )  {   }

    void operator () ( const std::shared_ptr< PointCloud> & )    const;
  };

  struct RectlinearTriangulator
  {
    size_pair	vertices_size;

    RectlinearTriangulator( const size_pair& vertices_size )
    : vertices_size( vertices_size ) {   }

    virtual void operator() ( const std::shared_ptr< TriSurface >& surface )	= 0;
  };

  struct SimpleRectlinearTriangulator : public RectlinearTriangulator
  {
    SimpleRectlinearTriangulator( const size_pair& vertices_size )
    : RectlinearTriangulator( vertices_size ) {   }

    void operator() ( const std::shared_ptr< TriSurface >& surface );
  };

  struct TextureGenerator
  {
    protected:
      size_pair			m_texture_size;

    public:

      TextureGenerator( const size_pair& texture_size )
      : m_texture_size( texture_size ) {   };

      const size_pair& texture_size() const { return m_texture_size; }
  };


  struct RectlinearFieldGenerator
  {
    protected:

      size_pair	m_vertices_size;

      RectlinearFieldGenerator() : m_vertices_size{ 0, 0 } {   }

    public:

      RectlinearFieldGenerator( const size_pair& vertices_size )
      : m_vertices_size( vertices_size ) {   }

      virtual void  operator() ( const std::shared_ptr< TriSurface >& ) = 0;

      virtual std::string get_name() const = 0;

      const size_pair&	vertex_field_size() const { return m_vertices_size; }

      const typename TriSurface::vertices_size_type 	num_vertices()	const
      { return std::get<0>( m_vertices_size ) * std::get<1>( m_vertices_size ); }
  };


  //----| point cloud generators

  struct RandomHeightGenerator : public RectlinearFieldGenerator, public TextureGenerator
  {
      coord_t   noise_amplitude;

      static void add_noise( const std::shared_ptr< TriSurface >&, const coord_t );

      RandomHeightGenerator( const size_pair& size, const coord_t& amplitude )
      : RectlinearFieldGenerator( size ), TextureGenerator( size )
      , noise_amplitude( amplitude ) {    }

      void operator() ( const std::shared_ptr< TriSurface >& surface );

      std::string   get_name() const { return "HeightField"; }
  };

  struct WaveGenerator : public RandomHeightGenerator
  {
      WaveGenerator( const size_pair& size, const coord_t& noise_amplitude = 0 )
      : RandomHeightGenerator( size, noise_amplitude )
      {   }

      void operator() ( const std::shared_ptr< TriSurface >& surface );

      std::string   get_name() const { return "Wave"; }
  };

}
