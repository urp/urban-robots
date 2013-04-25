/***************************************************************************
 *            gl_render_targets.hpp
 *
  *  Copyright  2011-2013 Peter Urban
 *  <urp@pks.mpg.de>
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

# define DBG_GTK_GL_RENDER_TARGETS

# include <gtkglmm.h>

# include "common.hpp"

namespace gtk
{

  class View;

  class GLCanvas;

  using namespace flat;

  class GLRenderTarget
  {

    public:
      typedef enum { WINDOW = 0, PIXMAP = 1 } types_t;

    protected:

      const types_t m_type;

      Glib::RefPtr< Gdk::GL::Context > m_context;

      GLRenderTarget( const types_t& type )
      : m_type( type ), m_context() {       }

    public:

      void gl_begin_context();

      void gl_end_context();

      void gl_flush();

      virtual bool configure( const size_t width, const size_t height) = 0;

      virtual Glib::RefPtr< Gdk::GL::Context> get_gdk_gl_context() = 0;
      virtual Glib::RefPtr< Gdk::GL::Drawable > get_gdk_gl_drawable() = 0;
      virtual Glib::RefPtr< Gdk::GL::Config > get_gdk_gl_config() = 0;

      const types_t& get_type() const { return m_type; }

  };


  class GLWindowRenderTarget : public GLRenderTarget
  {
    private:

      Gtk::Widget& m_widget;

    public:

      GLWindowRenderTarget( Gtk::Widget& widget, const Glib::RefPtr< const Gdk::GL::Context >& shared_context = Glib::RefPtr< const Gdk::GL::Context >() );

      virtual ~GLWindowRenderTarget();

      bool configure( const size_t width, const size_t height );

      Glib::RefPtr< Gdk::GL::Context> get_gdk_gl_context();

      Glib::RefPtr< Gdk::GL::Drawable > get_gdk_gl_drawable();

      Glib::RefPtr< Gdk::GL::Config > get_gdk_gl_config();

  };

  class GLPixmapRenderTarget : public GLRenderTarget
  {
    private:

      // refptr reference to which current pixmap is assigned

      Glib::RefPtr< Gdk::Pixmap >& m_pixmap;

      // opengl context
      Glib::RefPtr< Gdk::GL::Config > m_config;
      Glib::RefPtr< Gdk::GL::Drawable > m_drawable;

    public:

      GLPixmapRenderTarget( Glib::RefPtr< Gdk::Pixmap >& pixmap_target_ptr
                          , const size_t width = 400
                          , const size_t height = 400
                          , const Glib::RefPtr< const Gdk::GL::Context > shared_context = Glib::RefPtr< const Gdk::GL::Context >()
                          );

      bool configure( const size_t width, const size_t height );

      Glib::RefPtr< Gdk::GL::Context> get_gdk_gl_context()
      {
        return m_context;
      }

      Glib::RefPtr< Gdk::GL::Drawable > get_gdk_gl_drawable()
      {
        return m_drawable;
      }

      Glib::RefPtr< Gdk::GL::Config > get_gdk_gl_config()
      {
        return m_config;
      }

  };

} // of namespace gtk
