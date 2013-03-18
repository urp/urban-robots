/***************************************************************************
 *            surface.h
 *
 *  Wed Aug  5 23:46:44 2009
 *  Copyright  2009  Peter Urban
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
# include "surface/point_cloud/point_cloud.hpp"

namespace flat
{

  class TriSurface : public PointCloud
  {
    public:

      typedef std::pair< vertex_descriptor, vertex_descriptor > vertex_pair;
      typedef std::pair< vertex_handle, vertex_handle > vertex_handle_pair;

      static vertex_handle_pair make_vertex_handle_pair( const vertex_pair& pair, const TriSurface& surface )
      { return { vertex_handle( pair.first, surface ), vertex_handle( pair.second, surface ) }; }

      struct texture_type
      {
        typedef	color_channel_t	channel_type;

        static const size_t num_components = 4;

        size_pair size;
        std::vector< channel_type > 	pixmap;

        texture_type( texture_type&& other )
        : size( std::move( other.size ) ), pixmap( std::move( other.pixmap ) )
        {   }

        texture_type( const size_pair& o_size )
        : size( o_size ), pixmap( std::get<0>(o_size) * std::get<1>(o_size) * num_components )
        {   }

        void set_pixel( size_t pixel_index
                      , const rgba_color_ref_t& color
		      )
        {
          for( size_t i = 0; i < num_components; ++i )
           pixmap[ pixel_index * num_components + i ] = color[i];
        }

        const rgba_color_t get_pixel( const size_t index ) const
        { return rgba_color_t( pixmap[ index + 0 ], pixmap[ index + 1 ], pixmap[ index + 2 ], pixmap[ index + 3 ] ); }

        const rgba_color_t get_pixel( const size_t s, const size_t t ) const
        { return get_pixel( ( s + t * size.first ) * num_components ); }
      };


    private:

      std::string  m_name;

      // vector containing three (rgb-)color components per texel
      texture_type m_texture;

      // the minimum and maximum value of the gaussian curvature on ther surface
      mutable std::pair<coord_t,coord_t>  curvature_extrema;

    protected:

      TriSurface( const vertices_size_type vertex_count = 0
             , const size_pair& texture_size = size_pair{ 0, 0 }
             , const std::string& name = "untitled" );

    public:

      template< typename Generator, typename Triangulator, typename Transform >
      static std::shared_ptr< TriSurface > create_with_generator( Generator&    generator
								, Triangulator& triangulator
								, Transform&    transform )
      {
        std::shared_ptr< TriSurface > surface( new TriSurface( generator.num_vertices(), generator.texture_size(), generator.get_name() ) );

        generator( surface );

        triangulator( surface );

        transform( surface );

        return surface;
      }


      virtual std::vector< vertex_descriptor > neighbors( const vertex_descriptor descriptor ) const
      {
        auto adj = adjacent_vertices( descriptor, get_graph() );

        return std::vector< vertex_descriptor >( adj.first, adj.second );
      }

      virtual std::vector< vertex_pair > neighbors() const;

      const std::string& get_name() const { return m_name; }

      texture_type& texture() { return m_texture; }
      const texture_type& texture() const { return m_texture; }

      const std::pair<coord_t,coord_t>&	get_curvature_extrema()	const	{ return curvature_extrema; }

      void set_curvature_extrema( const float min =  std::numeric_limits<float>::infinity()
				, const float max = -std::numeric_limits<float>::infinity() ) const
      { curvature_extrema = { min, max }; }

      virtual void prepare_step()
      {
        set_curvature_extrema();
        PointCloud::prepare_step();
      }

      // triangulation

      bool has_triangulation() const
      { return num_edges(); }

      void remove_triangulation()
      { clear_edges(); }

  };


}
