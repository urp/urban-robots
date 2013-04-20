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

# include "gl/tools.hpp"

# include "gtk/gl_view/gl_canvas.hpp"
# include "gtk/gl_view/gl_query.hpp"

using namespace gtk;

flat::coord_t GLCanvas::cam_dist_step = 0.1;

GLWindowRenderTarget::GLWindowRenderTarget( GLCanvas& canvas )
: GLRenderTarget( WINDOW, canvas )
{
  if( !Gtk::GL::widget_is_gl_capable( canvas ) )
  {
    Glib::RefPtr<Gdk::GL::Config> window_config = Gdk::GL::Config::create( Gdk::GL::MODE_RGB
                                                                         | Gdk::GL::MODE_DOUBLE
                                                                         | Gdk::GL::MODE_DEPTH );
    if( !window_config )
    {
      std::clog << "gtk::GLWindowRenderTarget::GLWindowRenderTarget\t|"
              << "WARNING - could not create double-buffered visual - trying single-buffered"
          << std::endl;

      window_config = Gdk::GL::Config::create( Gdk::GL::MODE_RGB | Gdk::GL::MODE_DEPTH );
    }
    else
    {
      std::clog << "gtk::GLWindowRenderTarget::GLWindowRenderTarget\t| created double-buffered visual" << std::endl;
      assert( window_config->is_double_buffered() );
    }
    assert( window_config );

    Gtk::GL::widget_set_gl_capability( canvas, window_config );
  }

  assert( Gtk::GL::widget_is_gl_capable( canvas ) );

}

bool GLWindowRenderTarget::configure( const size_t width, const size_t height )
{
  # if defined DBG_GTK_GL_RENDER_TARGETS
  std::clog << "gtk::GLWindowRenderTarget::configure\t|"
          << " width " << width << " height " << height << std::endl;
  # endif
  if( !m_drawable )
  m_drawable = Gtk::GL::widget_get_gl_drawable( m_canvas );

  if( !m_context  )
  {
    m_context  = Gtk::GL::widget_get_gl_context ( m_canvas );

    gl_begin_context();

    m_canvas.gl_initialize_context();
  }
  else gl_begin_context();

  m_canvas.gl_setup_view( width, height );

  gl_end_context();

  return true;
}



GLPixmapRenderTarget::GLPixmapRenderTarget( GLCanvas& canvas )
: GLRenderTarget( PIXMAP, canvas )
{
  m_config = Gdk::GL::Config::create( Gdk::GL::MODE_RGB | Gdk::GL::MODE_DEPTH );
  assert( m_config );

  m_canvas.set_colormap( m_config->get_colormap() );

  std::clog << "gtk::GLPixmapRenderTarget::GLPixmapRenderTarget\t| created single-buffered visual" << std::endl;

}

bool GLPixmapRenderTarget::configure( const size_t width, const size_t height )
{
  # if defined DBG_GTK_GL_RENDER_TARGETS
  std::clog << "gtk::GLPixmapRenderTarget::configure\t|"
          << " width " << width << " height " << height << std::endl << std::flush;
  # endif

  Glib::RefPtr< Gdk::Pixmap > pixmap = Gdk::Pixmap::create( m_canvas.get_window(), width, height, m_config->get_depth() );

  if( m_canvas.get_pixmap() )
    Gdk::GL::ext( m_canvas.get_pixmap() ).unset_gl_capability();

  m_canvas.set_pixmap( pixmap );

  m_drawable = Gdk::GL::ext( pixmap ).set_gl_capability( m_config );

  assert( Gdk::GL::ext( pixmap ).is_gl_capable() );
  # warning "BUG in gtk::GLPixmapRenderTarget::configure - context recreation causes texture loss"
  m_context  = Gdk::GL::Context::create( m_drawable, false );

  gl_begin_context();
    m_canvas.gl_initialize_context();
    m_canvas.gl_setup_view( width, height );
  gl_end_context();

  return true;
}




GLCanvas::GLCanvas( BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder )
: Gtk::DrawingArea( cobject )
, m_show_origin( false ), m_show_pivot( true )
, cam_dist( 10. ), cam_center( 0. ), cam_inertial()
{
  # if defined DBG_GTK_GL_CANVAS
  std::clog << "gtk::GLCanvas::GLCanvas" <<std::endl;
  # endif
  // setting camera position
  cam_inertial.position().z() += cam_dist;

  // view transformation signals. Events have to be enabled in the glade file
  signal_button_press_event().connect(  sigc::mem_fun(*this, &GLCanvas::on_button_press_event) );
  signal_motion_notify_event().connect( sigc::mem_fun(*this, &GLCanvas::on_motion_notify_event));
  signal_scroll_event().connect( sigc::mem_fun(*this, &GLCanvas::on_scroll_event));

  std::get< GLRenderTarget::WINDOW >( m_targets ).reset( new GLWindowRenderTarget( *this ) );
  //std::get< GLRenderTarget::PIXMAP >( m_targets ).reset( new GLPixmapRenderTarget( *this ) );

  // TODO: build in a gui swith
  m_active_target = std::get< GLRenderTarget::WINDOW >( m_targets );
}


void GLCanvas::gl_initialize_context()
{

  glClearColor(.2, .2, .2, 1.);
  glClearDepth(1.0);

  glDepthFunc( GL_LEQUAL );
  glEnable(GL_DEPTH_TEST);

  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  glEnable( GL_LINE_SMOOTH );

  //glDisable( GL_CULL_FACE );
  //glCullFace(GL_BACK);

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset (1., 1.);

  //glEnable( GL_LIGHTING );

  glShadeModel( GL_SMOOTH );

  glEnable( GL_COLOR_MATERIAL );

  glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR );

  glEnable( GL_LIGHT0 );

  // create light components
  GLfloat ambientLight[]  = { 0.15f, 0.15f, 0.15f, 1.f };
  GLfloat diffuseLight[]  = {   .7f,   .7f,   .7f, 1.f };
  GLfloat specularLight[] = {   .2f,   .2f,   .2f, 1.f };

  GLfloat position[]    = {   0.f,   0.f, -10.0f, 1.f };

  // assign created components to GL_LIGHT0
  glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
  glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight );
  glLightfv( GL_LIGHT0, GL_POSITION, position );

  # if defined DBG_GTK_GL_CANVAS
  std::cerr << "gtk::GLCanvas::gl_initialize_context\t| error checkpoint" << std::endl;
  gl::PrintError();
  # endif


}

void GLCanvas::gl_setup_view( const float width, const float height )
{
  glViewport(0, 0, width, height);

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 40.f, width/float(height), 0.001f, 100.f );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  # if defined DBG_GTK_GL_CANVAS
  std::cerr << "gtk::GLCanvas::gl_setup_view\t| error checkpoint" << std::endl;
  gl::PrintError();
  # endif

}

bool GLCanvas::on_configure_event( GdkEventConfigure* event )
{
  if( !m_active_target ) return false;

  return m_active_target->configure( event->width, event->height );
}


void GLCanvas::gl_render_scene()
{

  const bool context_double_buffered = Gdk::GL::Context::get_current()->get_gl_config()->is_double_buffered();

  # if defined DBG_GTK_GL_CANVAS
  GLint draw_buffer;
  glGetIntegerv(GL_DRAW_BUFFER, &draw_buffer );
  GLboolean gl_double_buffered;
  glGetBooleanv(GL_DOUBLEBUFFER, &gl_double_buffered );
  std::clog << "gtk::GLCanvas::gl_render_scene\t\t| double buffered " << bool(gl_double_buffered) << "(gl)/" << context_double_buffered << "(gtk)"
  << " draw buffer " << (draw_buffer == GL_FRONT ? "FRONT" : (draw_buffer == GL_BACK ? "BACK" : "unknown")) << std::endl;
  std::cerr << "gtk::GLCanvas::gl_render_scene\t\t| query gl attributes"<< std::endl;
  gl_query::examine_gl_attrib( Gtk::GL::widget_get_gl_config( *this ) );

  # endif

  glDrawBuffer( context_double_buffered ? GL_BACK : GL_FRONT );

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  gl::InvTrafo( cam_inertial ); // -> gl_setup_view

  // draw viewing pivot
  if( get_pivot_visibility() )
  { glPushMatrix();
    gl::Translate( cam_center );
    gl::DrawCoords(.2f);
    glPopMatrix();
  }

  if( get_origin_visibility() ) gl::DrawCoords( 1. );

  m_gl_content_request_signal();

  glPopMatrix();

  # if defined DBG_GTK_GL_CANVAS
  std::cerr << "gtk::GLCanvas::gl_render_scene\t| error checkpoint" << std::endl;
  gl::PrintError();
  # endif

}

bool  GLCanvas::render_to_window()
{
  # if defined DBG_GTK_GL_CANVAS
  std::clog << "gtk::GLCanvas::render_to_window\t\t|" << std::endl;
  # endif

  m_active_target->gl_begin_context();

    gl_render_scene();

    m_active_target->gl_flush();

  m_active_target->gl_end_context();

  // integrate into GLPixmapRenderTarget
  if( m_active_target->get_type() == GLRenderTarget::PIXMAP )
  {
    get_window()->draw_drawable( get_style()->get_fg_gc(get_state()),
                                 m_pixmap,
                                 0, 0, 0, 0,
                                 get_width(), get_height() );

    m_pixmap_update_signal( m_pixmap );

  } else assert( m_active_target->get_type() == GLRenderTarget::WINDOW );

  return true;
}

bool  GLCanvas::render_to_pixmap()
{
  if( m_active_target->get_type() == GLRenderTarget::PIXMAP )
  {
    render_to_window();

    m_pixmap_update_signal( m_pixmap );

    return true;
  }

  const std::shared_ptr< GLRenderTarget >&  pix_target = std::get< GLRenderTarget::PIXMAP >( m_targets );

  pix_target->configure(get_width(),get_height());

  pix_target->gl_begin_context();

    gl_render_scene();

    pix_target->gl_flush();

  pix_target->gl_end_context();

  m_pixmap_update_signal( m_pixmap );

  return true;
}

bool GLCanvas::on_expose_event( GdkEventExpose* event )
{
  # if defined DBG_GTK_GL_CANVAS
  std::clog << "gtk::GLCanvas::on_expose_event\t\t|"
        <<"count "<<event->count
      <<" x "<<event->area.x
      <<" y "<<event->area.y
      <<" width "<<event->area.width
      <<" height "<<event->area.height
      << std::flush<<std::endl;
  # endif

  return render_to_window();
}


bool GLCanvas::on_button_press_event( GdkEventButton* event )
{
  # if defined DBG_GTK_GL_CANVAS
  std::clog << "gtk::GLCanvas::on_button_press_event"
        << std::flush<<std::endl;
  # endif
  old_cam_inertial = cam_inertial;
  old_cam_center   = cam_center;
  old_mouse_pos.x() = event->x;
  old_mouse_pos.y() = event->y;

  // don't block
  return false;
}

bool GLCanvas::on_motion_notify_event(GdkEventMotion* event)
{
  location2d_t  cur_mouse_pos(event->x,event->y);
  utk::size_t width = get_width(),
        height= get_height();

  if(event->state & GDK_BUTTON3_MASK)
  {
    cam_center  = old_cam_center;
    cam_center.x() -= (old_mouse_pos.x()-cur_mouse_pos.x())/width;
    cam_center.y() += (old_mouse_pos.y()-cur_mouse_pos.y())/height;
  }

  if(event->state & GDK_BUTTON1_MASK)
  {
    cam_center = old_cam_center;
    cam_inertial.quat()=old_cam_inertial.quat();

    location2d_t       oldpos( 2*old_mouse_pos.x()/(width-1.)-1., 2*(1.-old_mouse_pos.y()/(height-1.))-1.);
    location2d_t       newpos( 2*cur_mouse_pos.x()/(width-1.)-1., 2*(1.-cur_mouse_pos.y()/(height-1.))-1.);
    utk::veca<coord_t,4> axan  (utk::get_axis_angle_from_trackball( oldpos, newpos ));

    axan.xyz() = old_cam_inertial.rot_vec( axan.xyz() );

    cam_inertial.rot(axan,-axan.a());
    cam_inertial.quat().normalize();
  }

  location_t  loc( 0.,0.,cam_dist );
  cam_inertial.position() = cam_inertial.rot_vec(loc) + cam_center;

  request_redraw();

// don't block
  return false;
}

bool  GLCanvas::on_scroll_event( GdkEventScroll* event )
{
  if( event->direction == GDK_SCROLL_UP )
    utk::clamp_min( cam_dist -= cam_dist_step );
  if( event->direction == GDK_SCROLL_DOWN )
    cam_dist += cam_dist_step;

  location_t pos( coord_t(0.), coord_t(0.), cam_dist );
  cam_inertial.position() = cam_inertial.rot_vec( pos ) + cam_center;

  request_redraw();
  return true;
}

void  GLCanvas::gl_draw_coords()  const
{
  glLineWidth( 1. );
  glDisable( GL_LIGHTING );
  glBegin(GL_LINES);
  {
    glColor3f (1.f,0.f,0.f);
    glVertex3f(0.f,0.f,0.f);
    glVertex3f(1.f,0.f,0.f);

    glColor3f (0.f,1.f,0.f);
    glVertex3f(0.f,0.f,0.f);
    glVertex3f(0.f,1.f,0.f);

    glColor3f (0.f,0.f,1.f);
    glVertex3f(0.f,0.f,0.f);
    glVertex3f(0.f,0.f,1.f);
  }
  glEnd();
}
