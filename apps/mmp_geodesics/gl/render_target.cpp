//           gl-canvas.cpp
//  Sat Jan 15 14:41:56 2011
//  Copyright  2011  urp
//  <urp@<host>>

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA

//# include <gtkglmm.h>

# include "gl/render_target.hpp"

# include "gl/tools.hpp"

# include "gtk/gl_view/gl_query.hpp"

using namespace gl;

//:::| GLRenderTarget |:::

bool GLRenderTarget::gl_begin_context()
{
  assert( is_valid() );

  if( ! get_gdk_gl_drawable()->gl_begin( get_gdk_gl_context() ) )
  {
    std::cerr << "gtk::GLRenderTarget::gl_begin_context\t|" << "FAILED" << std::endl;
    return false;
  }

  return true;
}

void GLRenderTarget::gl_end_context()
{
  get_gdk_gl_drawable()->gl_end();
}

void GLRenderTarget::gl_flush()
{
  Glib::RefPtr< Gdk::GL::Drawable > gldrawable = get_gdk_gl_drawable();

  assert( is_valid() );

  if( gldrawable->is_double_buffered() )
    gldrawable->swap_buffers();
  else
    glFlush();
}


//:::| GLWindowRenderTarget |:::

GLWindowRenderTarget::GLWindowRenderTarget( Gtk::Widget& widget, const Glib::RefPtr< const Gdk::GL::Context >& shared_context )
: GLRenderTarget( WINDOW ), m_widget( widget )
{

  if( !Gtk::GL::widget_is_gl_capable( widget ) )
  {
    Glib::RefPtr<Gdk::GL::Config>  window_config = Gdk::GL::Config::create( Gdk::GL::MODE_RGB
                                                                          | Gdk::GL::MODE_DOUBLE
                                                                          | Gdk::GL::MODE_DEPTH );
    if( !window_config )
    {
      std::clog << "gtk::GLWindowRenderTarget::GLWindowRenderTarget\t|"
              << "WARNING - could not create double-buffered visual - trying single-buffered"
          << std::endl;

      window_config = Gdk::GL::Config::create( Gdk::GL::MODE_RGB | Gdk::GL::MODE_DEPTH );
    }

    assert( window_config );

    Gtk::GL::widget_set_gl_capability( m_widget, window_config, shared_context );
  }

  assert( Gtk::GL::widget_is_gl_capable( m_widget ) );

  # if defined DBG_GTK_GL_RENDER_TARGETS
  gl_query::examine_gl_attrib( std::clog << "gtk::GLWindowRenderTarget::GLWindowRenderTarget\t\t| query gl attributes" << std::endl
                             , Gtk::GL::widget_get_gl_config( m_widget ) );
  # endif
}

bool GLWindowRenderTarget::configure( const size_t width, const size_t height )
{
  # if defined DBG_GTK_GL_RENDER_TARGETS
  std::clog << "gtk::GLWindowRenderTarget::configure\t|"
            << " width " << width << " height " << height << std::endl;
  # endif

  if( !m_context )
  {
    m_context  = Gtk::GL::widget_get_gl_context ( m_widget );
  }
  else
    assert( m_context == Gtk::GL::widget_get_gl_context ( m_widget ) );

  assert( is_valid() );

  return m_context;
}


Glib::RefPtr< Gdk::GL::Context> GLWindowRenderTarget::get_gdk_gl_context()
{
  return m_context;
}

Glib::RefPtr< Gdk::GL::Drawable > GLWindowRenderTarget::get_gdk_gl_drawable()
{
  return Gtk::GL::widget_get_gl_drawable( m_widget );
}

Glib::RefPtr< Gdk::GL::Config > GLWindowRenderTarget::get_gdk_gl_config()
{
  return Gtk::GL::widget_get_gl_config( m_widget );
}

//:::| GLPixmapRenderTarget |:::


GLPixmapRenderTarget::GLPixmapRenderTarget( Glib::RefPtr< Gdk::Pixmap >& pixmap_target_ptr
                                          , const size_t width
                                          , const size_t height
                                          , const Glib::RefPtr< const Gdk::GL::Context > shared_context
                                          )
: GLRenderTarget( PIXMAP ), m_pixmap( pixmap_target_ptr )
{
  m_config = Gdk::GL::Config::create( Gdk::GL::MODE_RGB | Gdk::GL::MODE_DEPTH );

  assert( m_config );

  Glib::RefPtr< Gdk::Pixmap > new_pixmap = Gdk::Pixmap::create( Glib::RefPtr< Gdk::Drawable >(), width, height, m_config->get_depth() );

  m_drawable = Gdk::GL::ext( new_pixmap ).set_gl_capability( m_config );

  assert( Gdk::GL::ext( new_pixmap ).is_gl_capable() );

  // share display lists and textures with current context if shared context is also 'indirect' (X11 limitation)

  if( shared_context && ! shared_context->is_direct() )
  {
    # if defined DBG_GTK_GL_RENDER_TARGETS
    std::clog << "GLPixmapRenderTarget::GLPixmapRenderTarget\t| " << "sharing and copying context" << std::endl;
    #endif

    // create shared indirect context
    m_context  = Gdk::GL::Context::create( m_drawable, shared_context, false );

    // copy all attributes

    assert( Glib::RefPtr< const Gdk::GL::Context >( Gdk::GL::Context::get_current() ) == shared_context ); // required by glxCopyContext

    m_context->copy( shared_context ); // uses glxCopyContext
  }
  else
  {
    # if defined DBG_GTK_GL_RENDER_TARGETS
    std::clog << "GLPixmapRenderTarget::GLPixmapRenderTarget\t| " << "not sharing and copying context" << std::endl;
    #endif

    // create new indirect context
    m_context  = Gdk::GL::Context::create( m_drawable, false );
  }

  m_pixmap = new_pixmap;

  # if defined DBG_GTK_GL_RENDER_TARGETS
  gl_query::examine_gl_attrib( std::clog << "gtk::GLPixmapRenderTarget::GLPixmapRenderTarget\t\t| query gl attributes" << std::endl
                             , m_config );
  # endif
}

bool GLPixmapRenderTarget::configure( const size_t width, const size_t height )
{

  # warning "BUG in gtk::GLPixmapRenderTarget::configure - context recreation causes texture loss"

  # if defined DBG_GTK_GL_RENDER_TARGETS
  std::clog << "gtk::GLPixmapRenderTarget::configure\t|"
          << " width " << width << " height " << height << std::endl << std::flush;
  # endif

  // create new opengl-capable pixmap

  Glib::RefPtr< Gdk::Pixmap > new_pixmap = Gdk::Pixmap::create( Glib::RefPtr< Gdk::Drawable >(), width, height, m_config->get_depth() );

  assert( new_pixmap );

  Glib::RefPtr< Gdk::GL::Drawable > new_drawable = Gdk::GL::ext( new_pixmap ).set_gl_capability( m_config );

  assert( new_drawable );

  assert( Gdk::GL::ext( new_pixmap ).is_gl_capable() );

  // indirect context, shares display lists and textures with current context

  Glib::RefPtr< Gdk::GL::Context > old_context = get_gdk_gl_context();

  assert( old_context );

  assert( ! old_context->is_direct() ); // required by glxCreateContext

  Glib::RefPtr< Gdk::GL::Context > new_context  = Gdk::GL::Context::create( new_drawable, old_context , false ); // uses glxCreateContext

  assert( new_context );

  // copy OpenGL attributes to new context

  m_drawable->make_current( old_context );

  assert( Gdk::GL::Context::get_current() == old_context ); // required by glxCopyContext

  new_context->copy( old_context ); // uses glxCopyContext

  // make new pixmap current

  m_pixmap = new_pixmap;

  m_drawable = new_drawable;

  m_context = new_context;

  return true;
}
