
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

# include "gtk/gl_view/gl_view.hpp"
# include "gtk/gl_view/gl_drawable.hpp"
//# include "surface/tri_surface/drawable.h"

# include <utk/geometry.h>

# include <fstream>


//#define DBG_FLAT_MMP_VISUALIZER_DRAW_WINDOW

namespace gl
{
  using namespace mmp;

  class GeodesicsDrawable : public ::gl::Drawable
  {
    public: // types

      typedef enum { FLAT_SHADING
                   , ABSOLUTE_DISTANCE_SHADING
                   , TEXTURE_DISTANCE_SHADING   }   shading_t;

    private: // data members

      Geodesics* m_geodesics;

      bool m_covering_visible;

      GLuint m_equidist_texture;

    private: // functions

      void gl_draw_wavefront_indicators( EventPoint* ev
                                       , const rgba_color_ref_t crossing_color
                                       , const rgba_color_ref_t colinear_color
                                       );

      void gl_draw_window_edges( const Window& window, const Window::types& window_type
                               , const location_t& win_left, const location_t& win_right
                               , const location_t& pre_left, const location_t& pre_right
                               , const rgba_color_ref_t edge_color
                               , const rgba_color_ref_t source_edge_color );

      bool gl_draw_window( const Window&          window
                         , const rgba_color_ref_t edge_color
                         , const rgba_color_ref_t fill_color
                         , const rgba_color_ref_t source_color
                         , const shading_t        shading );

      bool gl_draw_window_subdivision( const Window& window
                                     , const rgba_color_ref_t edge_color
                                     , const rgba_color_ref_t fill_color
                                     , const rgba_color_ref_t source_color
                                     , const shading_t shading
                                     );

      void gl_do_draw_subdivision( const Window&           window
                                 , const Window::types     window_type
                                 , const distance_t        recursion_threshold
                                 , const rgba_color_ref_t  edge_color
                                 , const rgba_color_ref_t  fill_color
                                 , const rgba_color_ref_t  source_color
                                 , const shading_t         shading
                                 , const location_ref_t    normal
                                 , const std::pair< const coord_t&   , const coord_t&    >& bounds
                                 , const std::pair< const distance_t&, const distance_t& >& win_distances
                                 , const std::pair< const distance_t&, const distance_t& >& pre_distances
                                 , const std::pair< const location_t&, const location_t& >& win_points
                                 , const std::pair< const location_t&, const location_t& >& pre_points
                                 , const ps_t& ps
                                 , const ps_t& pre_ps
                                 );

      void gl_draw_interval( const Window&             window
                           , const Window::types       window_type
                           , const rgba_color_ref_t    edge_color
                           , const rgba_color_ref_t    fill_color
                           , const rgba_color_ref_t    source_color
                           , const shading_t           shading
                           , const location_ref_t      normal
                           , const std::pair< const distance_t&, const distance_t& >& win_distances
                           , const std::pair< const distance_t&, const distance_t& >& pre_distances
                           , const std::pair< const location_t&, const location_t& >& win_points
                           , const std::pair< const location_t&, const location_t& >& pre_points );


      void gl_draw_event_point( EventPoint* ev, const bool is_top_event );

      void gl_draw_window_sequence( const Window& window
                                  , const rgba_color_ref_t edge_color
                                  , const rgba_color_ref_t fill_color
                                  , const rgba_color_ref_t source_color
                                  , const shading_t         shading );

      void gl_draw_wavefront( const shading_t );

      void gl_draw_covering( const shading_t );

    public: // functions

      GeodesicsDrawable( Geodesics* g );

      virtual ~GeodesicsDrawable()
      { std::clog << "flat::gl::GeodesicsDrawable::~GeodesicsDrawable\t" << std::endl; }

      virtual void gl_initialize_context();

      virtual void gl_draw();

      const bool& get_covering_visibility() const
      { return m_covering_visible; }

      void set_covering_visibility( const bool& visibility )
      { m_covering_visible = visibility; }

      Geodesics* get_geodesics() const   { return m_geodesics; }
  };
}
