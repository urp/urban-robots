/***************************************************************************
 *            gl-canvas.h
 *
 *  Sat Jan 15 14:41:56 2011
 *  Copyright  2011  urp
 *  <urp@<host>>
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

// debugging
# define DBG_GTK_GLCANVAS_ON_REALIZE
# define DBG_GTK_GLCANVAS_UPDATE_CONTEXT
# define DBG_GTK_GLCANVAS_CONFIGURE
# define DBG_GTK_GLCANVAS_ON_EXPOSE_EVENT
# define DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
# define DBG_GTK_GLCANVAS_GL_SETUP_VIEW
# define DBG_GTK_GLCANVAS_GL_RENDER_SCENE
# define DBG_GTK_GLCANVAS_INVALIDATE
# define DBG_GTK_GLCANVAS_ON_BUTTON_PRESS_EVENT

# include "gl/headers.hpp"

# include <gtkmm.h>
# include <gtkglmm.h>

# include "gl/drawable.hpp"

# include "gtk/gl_view/gl_render_targets.hpp"

# include "view.hpp"

# include "common.hpp"
# include "utk/inertial.h"

# include <array>
# include <boost/signals.hpp>

namespace gtk
{

  template
  class GLCanvas : public GLDrawingArea, public uv::View< uv::gl::Drawable >
  {
    public: //types

      static flat::distance_t cam_dist_step;

      typedef boost::signal< void( const Glib::RefPtr< Gdk::Pixmap >& ) > pixmap_update_signal;

    private:

      // drawing options
      // TODO: make mini-drawables
      bool m_show_origin;
      bool m_show_pivot;

      bool m_block_renderer;

      //std::shared_ptr< GLPixmap > m_gl_pixmap;

      pixmap_update_signal   m_pixmap_update_signal;

      // setup render target

      std::vector< View< uv::gl::Drawable >::drawable_pointer > m_gl_init_list;
      std::vector< View< uv::gl::Drawable >::drawable_pointer > m_gl_remove_list;

      // issue opengl commands

      void gl_initialize_context();

      void gl_initialize_queued_drawables();

      void gl_initialize_all_drawables();

      void gl_remove_queued_drawables();

      void gl_remove_all_drawables();

      void gl_setup_view( const float width, const float height );

      void gl_draw_scene();

      // camera
      flat::coord_t                  cam_dist;
      flat::location_t               cam_center;
      utk::inertial< flat::coord_t > cam_inertial;
      flat::location_t               old_cam_center;
      utk::inertial< flat::coord_t > old_cam_inertial;
      flat::location2d_t             old_mouse_pos;

    protected:

      // callback functions
      virtual void on_realize() override;
      virtual bool on_configure_event( GdkEventConfigure* event) override;
      virtual bool on_expose_event( GdkEventExpose* event) override;

      virtual bool on_button_press_event( GdkEventButton* event) override;
      virtual bool on_motion_notify_event( GdkEventMotion* event) override;
      virtual bool on_scroll_event( GdkEventScroll* event ) override;

    public:

      GLCanvas();

      virtual ~GLCanvas() { }

      // adding and removing drawables

      virtual void add_drawable( const uv::View< uv::gl::Drawable >::drawable_pointer& drawable )
      {

        std::clog << "gtk::GLCanvas::add_drawable" << std::endl;

        uv::View< uv::gl::Drawable >::add_drawable( drawable );

        m_gl_init_list.push_back( drawable );
      }

      virtual void remove_drawable( const uv::View< uv::gl::Drawable >::drawable_pointer& drawable )
      {
        std::clog << "gtk::GLCanvas::remove_drawable| valid context " << is_gl_context_valid() << std::endl;

        uv::View< uv::gl::Drawable >::remove_drawable( drawable );

        m_gl_remove_list.push_back( drawable );
      }

      void request_redraw()
      {
        Gtk::DrawingArea::queue_draw();
      }

      void set_origin_visibility( const bool show )
      {
        if( show == get_origin_visibility() ) return;

        m_show_origin = show;
        request_redraw();
      }

      void set_pivot_visibility( const bool show )
      {
        if( show == get_pivot_visibility() ) return;

        m_show_pivot = show;
        request_redraw();
      }

      void block_renderer( const bool block = true )
      {
        m_block_renderer = block;
      }

      bool is_renderer_blocked()   const
      {
        return m_block_renderer;
      }

      virtual void invalidate( const drawable_pointer& drawable = drawable_pointer() )
      {
        # if defined DBG_GTK_GLCANVAS_INVALIDATE
        std::clog << "flat::GLCanvas::invalidate\t|"
                  << ( drawable ? " drawable" : " view" )
                  << " render " << ( m_block_renderer ? "disabled" : "active" )
                  << std::endl;
        # endif

        if( not is_renderer_blocked() )
          request_redraw();
      }

/*
      Glib::RefPtr< Gdk::Pixmap > get_pixmap()
      {
        if( not m_gl_pixmap ) return Glib::RefPtr< Gdk::Pixmap >();

        return m_gl_pixmap->pixmap();
      }

      const Glib::RefPtr< Gdk::Pixmap > get_pixmap() const
      {
        if( not m_gl_pixmap ) return Glib::RefPtr< Gdk::Pixmap >();

        return m_gl_pixmap->pixmap();
      }
*/
      const bool&       get_origin_visibility() const   { return m_show_origin; }

      const bool&       get_pivot_visibility()  const   { return m_show_pivot; }
/*
      boost::signals::connection connect_pixmap_observer( pixmap_update_signal::slot_type observer )
      { return m_pixmap_update_signal.connect( observer ); }
*/
  };

} // of namespace flat
