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

# include "gtk/gl_view/gl_render_targets.hpp"

# include "gl/tools.hpp"

# include "gtk/gl_view/gl_query.hpp"

using namespace gtk;

//:::| GLRenderTarget |:::

bool GLRenderTarget::gl_begin_context()
{
  assert( is_gl_context_valid() );

  if( not gl_drawable()->gl_begin( *gl_context() ) )
  {
    std::cerr << "gtk::GLRenderTarget::gl_begin_context\t|" << "FAILED" << std::endl;
    return false;
  }

  assert( gl_context()->is_current() );

  return true;
}

void GLRenderTarget::gl_end_context()
{
  assert( is_gl_context_valid() );

  gl_drawable()->gl_end();
}

void GLRenderTarget::gl_flush()
{
  assert( is_gl_context_valid() );

  if( gl_drawable()->is_double_buffered() )
    gl_drawable()->swap_buffers();
  else
    glFlush(); //need this ???
}


//:::| GLDrawingArea |:::

Glib::RefPtr< const Gdk::GL::Config > create_gl_config()
{
  //
  // Configure OpenGL-capable visual.
  //
  Glib::RefPtr< Gdk::GL::Config > gl_config;

  // Try double-buffered visual
  gl_config = Gdk::GL::Config::create( Gdk::GL::MODE_RGB
                                     | Gdk::GL::MODE_DEPTH
                                     | Gdk::GL::MODE_DOUBLE);
  if( not gl_config )
  {
    std::clog << "gtk::GLDrawingArea::create_gl_config\t| " << std::endl
              << "WARNING: Cannot find the double-buffered visual." << std::endl
              << "Trying single-buffered visual." << std::endl;

    // Try single-buffered visual
    gl_config = Gdk::GL::Config::create( Gdk::GL::MODE_RGB |Gdk::GL::MODE_DEPTH );

    if( not gl_config )
    {
      std::cerr << "gtk::GLDrawingArea::create_gl_config\t| "
                << "ERROR: Cannot find any OpenGL-capable visual."
                << std::endl;
      std::terminate();
    }
  }

  return gl_config;
}

GLDrawingArea::GLDrawingArea( const std::shared_ptr< const GLContext >& shared_context
                            , const Glib::RefPtr< const Gdk::GL::Config >& config
                            )
: GLRenderTarget( shared_context )
, Gtk::GL::DrawingArea()
{
  auto configuration = config ? config : create_gl_config();

  set_gl_capability( configuration );

  // print frame buffer attributes.
  # if defined DBG_GTK_GL_RENDER_TARGETS
  gl_query::examine_gl_attrib( std::clog << "gtk::GLDrawingArea::GLDrawingArea\t\t| query gl attributes" << std::endl
                             , gl_config() );
  # endif
}


void GLDrawingArea::on_realize()
{
  # if defined DBG_GTK_GL_RENDER_TARGETS
  std::clog << "gtk::GLDrawingArea::on_realize\t|"
            << std::endl;
  # endif

  // We need to call the base on_realize()
  Gtk::DrawingArea::on_realize();
}

void GLDrawingArea::on_unrealize()
{
  # if defined DBG_GTK_GL_RENDER_TARGETS
  std::clog << "gtk::GLDrawingArea::on_unrealize\t| invalidating context..." << std::endl;
  # endif

  Gtk::DrawingArea::on_unrealize();

  invalidate_context();
}


bool GLDrawingArea::configure( const size_t width, const size_t height )
{
  # if defined DBG_GTK_GL_RENDER_TARGETS
  std::clog << "gtk::GLDrawingArea::configure\t|"
            << " width " << width << " height " << height << std::endl;
  # endif

  return is_gl_context_valid();
}

//:::| GLPixmap |:::

std::pair< Glib::RefPtr< Gdk::Pixmap >, Glib::RefPtr< Gdk::GL::Drawable > >
    create_gl_pixmap( Glib::RefPtr< const Gdk::GL::Config > config, const size_t width, const size_t height )
{
  Glib::RefPtr< Gdk::Pixmap > new_pixmap = Gdk::Pixmap::create( Glib::RefPtr< Gdk::Drawable >(), width, height, config->get_depth() );

  Glib::RefPtr< Gdk::GL::Drawable > new_drawable = Gdk::GL::ext( new_pixmap ).set_gl_capability( config );

  assert( Gdk::GL::ext( new_pixmap ).is_gl_capable() );

  return std::make_pair( new_pixmap, new_drawable );
}

GLPixmap::GLPixmap( const size_t width, const size_t height, const std::shared_ptr< const GLContext > shared_context )
: GLRenderTarget( shared_context )
, m_pixmap()
{
  m_gl_config = Gdk::GL::Config::create( Gdk::GL::MODE_RGB | Gdk::GL::MODE_DEPTH );

  assert( gl_config() );

  std::tie( m_pixmap, m_gl_drawable ) = create_gl_pixmap( gl_config(), width, height );



  # if defined DBG_GTK_GL_RENDER_TARGETS
  gl_query::examine_gl_attrib( std::clog << "gtk::GLPixmap::GLPixmap\t\t| query gl attributes" << std::endl, gl_config() );
  # endif
}

bool GLPixmap::configure( const size_t width, const size_t height )
{
  # if defined DBG_GTK_GL_RENDER_TARGETS
  std::clog << "gtk::GLPixmap::configure\t|"
          << " width " << width << " height " << height << std::endl << std::flush;
  # endif

  // create new opengl-capable pixmap

  Glib::RefPtr< Gdk::Pixmap > new_pixmap;

  Glib::RefPtr< Gdk::GL::Drawable > new_drawable;

  std::tie( new_pixmap, new_drawable ) = create_gl_pixmap( gl_config(), width, height );

  assert( new_pixmap && Gdk::GL::ext( new_pixmap ).is_gl_capable() );
  assert( new_drawable );

  // indirect context, shares display lists and textures with current context

  std::shared_ptr< GLContext > old_context = gl_context();

  assert( old_context );

  assert( not old_context->is_direct() ); // required by glxCreateContext

  GLRenderTarget::set_shared_gl_context( old_context );

  /* copy OpenGL attributes to new context

  gl_drawable()->make_current( old_context );

  assert( Gdk::GL::Context::get_current() == old_context ); // required by glxCopyContext

  new_context->copy( old_context ); // uses glxCopyContext
  */

  // make new pixmap current

  m_pixmap = new_pixmap;

  m_gl_drawable = new_drawable;

  return true;
}
