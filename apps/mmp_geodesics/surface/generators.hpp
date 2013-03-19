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

  struct DisturbTransform
  {
    coord_t amplitude;

    void add_noise( const std::shared_ptr< PointCloud >& surface, const coord_t amplitude ) const;

    void operator() ( const std::shared_ptr< PointCloud> & ) const;
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

    void operator() ( const std::shared_ptr< PointCloud> & ) const;
  };

  struct RectlinearTriangulator
  {
    size_pair	vertex_field_size;

    RectlinearTriangulator( const size_pair& vertex_field_size )
    : vertex_field_size( vertex_field_size ) {   }

    virtual void operator() ( const std::shared_ptr< TriSurface >& surface )	= 0;
  };

  struct SimpleRectlinearTriangulator : public RectlinearTriangulator
  {
    SimpleRectlinearTriangulator( const size_pair& vertex_field_size )
    : RectlinearTriangulator( vertex_field_size ) {   }

    void operator() ( const std::shared_ptr< TriSurface >& surface );
  };

  struct RegularGridTransform
  {
    protected:

      RegularGridTransform() : vertex_field_size{ 0, 0 } {   }

    public:

      size_pair	vertex_field_size;

      void arrange_as_regular_grid( const std::shared_ptr< PointCloud >& surface );

      RegularGridTransform( const size_pair& field_size )
      : vertex_field_size( field_size ) {  }

      virtual void  operator() ( const std::shared_ptr< PointCloud >& surface )
      {
        arrange_as_regular_grid( surface );
      }

      virtual std::string get_name() const  { return "regular_grid_generator"; }

      const typename PointCloud::vertices_size_type	num_vertices()	const
      { return std::get<0>( vertex_field_size ) * std::get<1>( vertex_field_size ); }

  };


  //----| point cloud generators
  //---| TODO: Let a Transformation do the job

  struct WaveTransform
  {
      WaveTransform( )
      {   }

      virtual void operator() ( const std::shared_ptr< PointCloud >& surface );

      virtual std::string   get_name() const { return "Wave"; }
  };

}
