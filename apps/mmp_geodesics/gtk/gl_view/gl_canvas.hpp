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
# define DBG_GTK_GLCANVAS_SET_RENDER_TARGET
# define DBG_GTK_GLCANVAS_CONFIGURE
# define DBG_GTK_GLCANVAS_ON_EXPOSE_EVENT
# define DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
# define DBG_GTK_GLCANVAS_GL_SETUP_VIEW
# define DBG_GTK_GLCANVAS_GL_RENDER_SCENE
# define DBG_GTK_GLCANVAS_INVALIDATE
# define DBG_GTK_GLCANVAS_ON_BUTTON_PRESS_EVENT

# include <gtkmm.h>
# include <gtkglmm.h>

# include "gtk/gl_view/gl_drawable.hpp"
# include "gtk/gl_view/gl_render_targets.hpp"

# include "view.hpp"

# include "common.hpp"
# include "utk/inertial.h"

# include <array>
# include <boost/signals.hpp>

namespace gtk
{

  class GLCanvas : public Gtk::DrawingArea, public flat::View< gl::Drawable >
  {
    public: //types

      friend class GLWindowRenderTarget;
      friend class GLPixmapRenderTarget;

      static flat::distance_t    cam_dist_step;

      typedef boost::signal< void( const Glib::RefPtr<Gdk::Pixmap>& ) > pixmap_update_signal;

    private:

      // drawing options
      bool      m_show_origin;
      bool      m_show_pivot;

      bool      m_block_renderer;

      pixmap_update_signal   m_pixmap_update_signal;

      std::shared_ptr< GLRenderTarget > m_target;

      // make temporary in gl::View
      Glib::RefPtr< Gdk::Pixmap >       m_pixmap;


      // setup render target

      bool configure_target( const size_t width, const size_t height );

      void gl_initialize_context();
      void gl_setup_view( const float width, const float height );

      // issue opengl drawing commands

      void gl_render_scene();

      // camera
      coord_t                   cam_dist;
      location_t                cam_center;
      utk::inertial<coord_t>    cam_inertial;
      location_t                old_cam_center;
      utk::inertial<coord_t>    old_cam_inertial;
      location2d_t              old_mouse_pos;

    protected:

      // callback functions
      virtual bool      on_configure_event(GdkEventConfigure* event);
      virtual bool      on_expose_event(GdkEventExpose* event);

      virtual bool      on_button_press_event(GdkEventButton* event);
      virtual bool      on_motion_notify_event(GdkEventMotion* event);
      virtual bool      on_scroll_event(GdkEventScroll* event);

    public:

      GLCanvas( BaseObjectType* cobject
              , const Glib::RefPtr<Gtk::Builder>& builder );

      virtual ~GLCanvas() { }

      // TODO: add gui switch

      void set_render_target( const GLRenderTarget::types_t target_type );

      bool render_to_window();
      bool render_to_pixmap();

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

      virtual void invalidate( gl::Drawable* drawable = 0 )
      {
        # if defined DBG_GTK_GLCANVAS_INVALIDATE
        std::clog << "flat::GLCanvas::invalidate\t|"
                  << ( drawable ? " drawable" : " view" )
                  << " render " << ( m_block_renderer ? "disabled" : "active" )
                  << std::endl;
        # endif

        if( !is_renderer_blocked() )
          request_redraw();
      }


      Glib::RefPtr< Gdk::Pixmap >&       get_pixmap() { return m_pixmap; };
      const Glib::RefPtr< Gdk::Pixmap >& get_pixmap() const { return m_pixmap; };

      const bool&       get_origin_visibility() const   { return m_show_origin; }

      const bool&       get_pivot_visibility()  const   { return m_show_pivot; }

      boost::signals::connection connect_pixmap_observer( pixmap_update_signal::slot_type observer )
      { return m_pixmap_update_signal.connect( observer ); }

  };

} // of namespace flat
