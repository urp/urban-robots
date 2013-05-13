
/*  mmp-visualizer.h - Copyright Peter Urban 2010

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

# pragma once



# include "mmp/geodesics.hpp"

# include "gl/drawable.hpp"
# include "gtk/gl_view/gl_view.hpp"

# include <utk/geometry.h>

# include <fstream>


//#define DBG_FLAT_MMP_VISUALIZER_DRAW_WINDOW

namespace uv
{
  namespace gl
  {

    class GeodesicsDrawable : public uv::gl::Drawable
    {
      public: // types

        typedef enum { FLAT_SHADING
                     , ABSOLUTE_DISTANCE_SHADING
                     , TEXTURE_DISTANCE_SHADING   }   shading_t;

      private: // data members

        std::shared_ptr< mmp::Geodesics > m_geodesics;

        bool m_covering_visible;

        GLuint m_equidist_texture;

      private: // functions

        void gl_draw_wavefront_indicators( mmp::EventPoint* ev
                                         , const mmp::rgba_color_ref_t crossing_color
                                         , const mmp::rgba_color_ref_t colinear_color
                                         );

        void gl_draw_window_edges( const mmp::Window& window, const mmp::Window::types& window_type
                                 , const mmp::location_t& win_left, const mmp::location_t& win_right
                                 , const mmp::location_t& pre_left, const mmp::location_t& pre_right
                                 , const mmp::rgba_color_ref_t edge_color
                                 , const mmp::rgba_color_ref_t source_edge_color );

        bool gl_draw_window( const mmp::Window&     window
                           , const mmp::rgba_color_ref_t edge_color
                           , const mmp::rgba_color_ref_t fill_color
                           , const mmp::rgba_color_ref_t source_color
                           , const shading_t        shading );

        bool gl_draw_window_subdivision( const mmp::Window&     window
                                       , const mmp::rgba_color_ref_t edge_color
                                       , const mmp::rgba_color_ref_t fill_color
                                       , const mmp::rgba_color_ref_t source_color
                                       , const shading_t shading
                                       );

        void gl_do_draw_subdivision( const mmp::Window&           window
                                   , const mmp::Window::types     window_type
                                   , const mmp::distance_t        recursion_threshold
                                   , const mmp::rgba_color_ref_t  edge_color
                                   , const mmp::rgba_color_ref_t  fill_color
                                   , const mmp::rgba_color_ref_t  source_color
                                   , const shading_t         shading
                                   , const mmp::location_ref_t    normal
                                   , const std::pair< const mmp::coord_t&   , const mmp::coord_t&    >& bounds
                                   , const std::pair< const mmp::distance_t&, const mmp::distance_t& >& win_distances
                                   , const std::pair< const mmp::distance_t&, const mmp::distance_t& >& pre_distances
                                   , const std::pair< const mmp::location_t&, const mmp::location_t& >& win_points
                                   , const std::pair< const mmp::location_t&, const mmp::location_t& >& pre_points
                                   , const mmp::ps_t& ps
                                   , const mmp::ps_t& pre_ps
                                   );

        void gl_draw_interval( const mmp::Window&        window
                             , const mmp::Window::types  window_type
                             , const mmp::rgba_color_ref_t    edge_color
                             , const mmp::rgba_color_ref_t    fill_color
                             , const mmp::rgba_color_ref_t    source_color
                             , const shading_t           shading
                             , const mmp::location_ref_t      normal
                             , const std::pair< const mmp::distance_t&, const mmp::distance_t& >& win_distances
                             , const std::pair< const mmp::distance_t&, const mmp::distance_t& >& pre_distances
                             , const std::pair< const mmp::location_t&, const mmp::location_t& >& win_points
                             , const std::pair< const mmp::location_t&, const mmp::location_t& >& pre_points );


        void gl_draw_event_point( mmp::EventPoint* ev, const bool is_top_event );

        void gl_draw_window_sequence( const mmp::Window& window
                                    , const mmp::rgba_color_ref_t edge_color
                                    , const mmp::rgba_color_ref_t fill_color
                                    , const mmp::rgba_color_ref_t source_color
                                    , const shading_t         shading );

        void gl_draw_wavefront( const shading_t );

        void gl_draw_covering( const shading_t );

      protected:

         GeodesicsDrawable( const std::shared_ptr< mmp::Geodesics >& g );

      public: // functions


        static std::shared_ptr< GeodesicsDrawable > create( const std::shared_ptr< mmp::Geodesics >& g )
        { return std::shared_ptr< GeodesicsDrawable >( new GeodesicsDrawable( g ) ); }

        virtual ~GeodesicsDrawable()
        {
          std::clog << "flat::gl::GeodesicsDrawable::~GeodesicsDrawable\t" << std::endl;
        }

        virtual void gl_initialize_context( const std::shared_ptr< uv::gl::Context >& ) override;

        virtual void gl_remove_from_context( const std::shared_ptr< uv::gl::Context >& ) override;

        virtual void gl_draw( const std::shared_ptr< uv::gl::Context >& ) override;

        const bool& get_covering_visibility() const
        { return m_covering_visible; }

        void set_covering_visibility( const bool& visibility )
        { m_covering_visible = visibility; }

        const std::shared_ptr< mmp::Geodesics >& get_geodesics() const  { return m_geodesics; }
    };
  } // of gl::
} // of ::uv::
