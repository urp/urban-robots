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

using namespace gtk;

flat::coord_t GLCanvas::cam_dist_step = 0.1;

GLCanvas::GLCanvas( BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder )
: Gtk::DrawingArea( cobject )
, m_show_origin( false )
, m_show_pivot( true )
, m_block_renderer(false)
, cam_dist( 3. )
, cam_center( 0. )
, cam_inertial()
{
  # if defined DBG_GTK_GL_CANVAS
  std::clog << "gtk::GLCanvas::GLCanvas" <<std::endl;
  # endif

  // setting camera position
  cam_inertial.position().z() += cam_dist;

  set_app_paintable( true );
  set_double_buffered( false );

  // view transformation signals. Events have to be enabled in the glade file
  signal_button_press_event().connect(  sigc::mem_fun(*this, &GLCanvas::on_button_press_event) );
  signal_motion_notify_event().connect( sigc::mem_fun(*this, &GLCanvas::on_motion_notify_event));
  signal_scroll_event().connect( sigc::mem_fun(*this, &GLCanvas::on_scroll_event));

  // The context of the window

  m_target.reset( new GLWindowRenderTarget( *this )
                  //new GLPixmapRenderTarget( m_pixmap )
                );
}

void GLCanvas::gl_initialize_context()
{

  # if defined DBG_GTK_GLCANVAS_CONFIGURE
  std::clog << "gtk::GLCanvas::configure_target\t| (re-)initializing context" << std::endl;
  # endif

  glClearColor( .2, .2, .2, 1. );
  glClearDepth( 1. );

  glDepthFunc( GL_LEQUAL );
  glEnable(GL_DEPTH_TEST);

  //glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  glEnable( GL_LINE_SMOOTH );

  //glDisable( GL_CULL_FACE );
  //glCullFace( GL_BACK );

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset( 1., 1. );

  //glEnable( GL_LIGHTING );

  glShadeModel( GL_SMOOTH );

  glEnable( GL_COLOR_MATERIAL );

  glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR );

  // light 0

  glEnable( GL_LIGHT0 );

  // create light components
  GLfloat ambient0[]  = { 0.15f, 0.15f, 0.15f, 1.f };
  GLfloat diffuse0[]  = {   .7f,   .7f,   .7f, 1.f };
  GLfloat specular0[] = {   .2f,   .2f,   .2f, 1.f };

  GLfloat position0[]    = {   0.f,   0.f, -10.0f, 1.f };

  // assign created components to GL_LIGHT0
  glLightfv( GL_LIGHT0, GL_AMBIENT, ambient0 );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse0 );
  glLightfv( GL_LIGHT0, GL_SPECULAR, specular0 );
  glLightfv( GL_LIGHT0, GL_POSITION, position0 );

  // light 1

  glEnable( GL_LIGHT1 );

  // create light components
  GLfloat ambient1[]  = { 0.15f, 0.15f, 0.15f, 1.f };
  GLfloat diffuse1[]  = {   .7f,   .7f,   .7f, 1.f };
  GLfloat specular1[] = {   .2f,   .2f,   .2f, 1.f };

  GLfloat position1[]    = { 0.f, 0.f, 10.0f, 1.f };

  // assign created components to GL_LIGHT1
  glLightfv( GL_LIGHT1, GL_AMBIENT, ambient1 );
  glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuse1 );
  glLightfv( GL_LIGHT1, GL_SPECULAR, specular1 );
  glLightfv( GL_LIGHT1, GL_POSITION, position1 );

  # if defined DBG_GTK_GL_CANVAS
  gl::PrintError( std::clog << "gtk::GLCanvas::gl_initialize_context\t| canvas error checkpoint" << std::endl );
  # endif
}

void GLCanvas::gl_initialize_drawables( const bool init_all )
{
  # if defined DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
  std::clog << "gtk::GLCanvas::gl_initialize_drawables\t| "
            << "initialize " << (init_all ? "all" : ( m_gl_init_list.empty() ? "no new" : "new" ) ) << "drawables"
            << std::endl;
  # endif

  assert( m_target->is_valid() );

  if( init_all)
    std::for_each( flat::View< gl::Drawable >::begin(), flat::View< gl::Drawable >::end(), std::mem_fun( &gl::Drawable::gl_initialize_context ) );
  else
    std::for_each( m_gl_init_list.begin(), m_gl_init_list.end(), std::mem_fun( &gl::Drawable::gl_initialize_context ) );

  m_gl_init_list.clear();

  # if defined DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
  gl::PrintError( std::clog << "gtk::GLCanvas::gl_initialize_drawables\t| drawable error checkpoint" << std::endl );
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

  # if defined DBG_GTK_GLCANVAS_GL_SETUP_VIEW
  gl::PrintError( std::clog << "gtk::GLCanvas::gl_setup_view\t| error checkpoint" << std::endl );
  # endif

}

void GLCanvas::set_render_target( const GLRenderTarget::types_t target_type )
{
  # if defined DBG_GTK_GLCANVAS_SET_RENDER_TARGET
  std::clog << "gtk::GLCanvas::set_render_targets\t|"
            << ( target_type == GLRenderTarget::WINDOW ? " window" : "" )
            << ( target_type == GLRenderTarget::PIXMAP ? " pixmap" : "" )
            << std::endl;
  # endif


  if( m_target->get_type() == target_type ) return;

  Glib::RefPtr< const Gdk::GL::Context>  old_context = m_target->get_gdk_gl_context();

  std::shared_ptr< GLRenderTarget > new_target;

  switch(target_type)
  {
    case GLRenderTarget::WINDOW : new_target.reset( new GLWindowRenderTarget( *this, old_context ) ); break;
    case GLRenderTarget::PIXMAP : new_target.reset( new GLPixmapRenderTarget( m_pixmap, get_width(), get_height(), old_context ) ); break;
    default : assert(false);
  }

  assert( new_target );

  set_colormap( new_target->get_gdk_gl_config()->get_colormap() );

  m_target = new_target;

  configure_target( get_width(), get_height() );

  request_redraw();
}

bool GLCanvas::configure_target( const size_t width, const size_t height )
{
  if( !m_target ) return false;

  const bool old_context_was_not_shared = ! m_target->get_gdk_gl_context() || ! m_target->get_gdk_gl_context()->get_share_list();

  const bool configured = m_target->configure( width, height );

  # if defined DBG_GTK_GLCANVAS_CONFIGURE
  std::clog << "gtk::GLCanvas::configure_target\t| preparing context" << std::endl;
  # endif

  m_target->gl_begin_context();

    if( ! m_target->get_gdk_gl_context()->get_share_list() || old_context_was_not_shared )
    {
      gl_initialize_context();
      gl_initialize_drawables( true );

    }else
    {
      gl_initialize_drawables();
    }

    gl_setup_view(get_width(),get_height());

  m_target->gl_end_context();

  return configured;
}

bool GLCanvas::on_configure_event( GdkEventConfigure* event )
{
  configure_target( event->width, event->height);
}

void GLCanvas::gl_render_scene()
{
  # if defined DBG_GTK_GLCANVAS_GL_RENDER_SCENE
  const bool context_double_buffered = Gdk::GL::Context::get_current()->get_gl_config()->is_double_buffered();

  GLint draw_buffer;
  glGetIntegerv(GL_DRAW_BUFFER, &draw_buffer );
  GLboolean gl_double_buffered;
  glGetBooleanv(GL_DOUBLEBUFFER, &gl_double_buffered );
  std::clog << "gtk::GLCanvas::gl_render_scene\t\t| double buffered " << bool(gl_double_buffered) << "(gl)/" << context_double_buffered << "(gtk)"
  << " draw buffer " << (draw_buffer == GL_FRONT ? "FRONT" : (draw_buffer == GL_BACK ? "BACK" : "unknown")) << std::endl;
  # endif

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushAttrib( GL_ALL_ATTRIB_BITS );
  glPushMatrix();
  {
    gl::InvTrafo( cam_inertial );

    // draw viewing pivot
    if( get_pivot_visibility() )
    {
      glPushMatrix();
        gl::Translate( cam_center );
        gl::DrawCoords(.2f);
      glPopMatrix();
    }

    if( get_origin_visibility() )
      gl::DrawCoords( 1. );

    std::for_each( flat::View< gl::Drawable >::begin(), flat::View< gl::Drawable >::end(), std::mem_fun( &gl::Drawable::gl_draw ) );

  }
  glPopMatrix();
  glPopAttrib();

  # if defined DBG_GTK_GLCANVAS_GL_RENDER_SCENE
  gl::PrintError( std::clog << "gtk::GLCanvas::gl_render_scene\t| error checkpoint" << std::endl );
  # endif

}

bool GLCanvas::render_to_window()
{
  # if defined DBG_GTK_GL_CANVAS
  std::clog << "gtk::GLCanvas::render_to_window\t\t|" << std::endl;
  # endif

  m_target->gl_begin_context();

    gl_render_scene();

    m_target->gl_flush();

  m_target->gl_end_context();

  if( m_target->get_type() == GLRenderTarget::PIXMAP )
  {

    get_window()->draw_drawable( get_style()->get_fg_gc(get_state()),
                                 m_pixmap,
                                 0, 0, 0, 0,
                                 get_width(), get_height() );

    m_pixmap_update_signal( m_pixmap );

  } else assert( m_target->get_type() == GLRenderTarget::WINDOW );

  return true;
}

bool  GLCanvas::render_to_pixmap()
{

  const auto target_type = m_target->get_type();

  // TODO: try to create pixmap context in parallel
  set_render_target( GLRenderTarget::PIXMAP );

  render_to_window();

  set_render_target( target_type );

  return true;
}

bool GLCanvas::on_expose_event( GdkEventExpose* event )
{
  # if defined DBG_GTK_GLCANVAS_ON_EXPOSE_EVENT
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
  # if defined DBG_GTK_GLCANVAS_ON_BUTTON_PRESS_EVENT
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
  const location2d_t  cur_mouse_pos(event->x,event->y);
  const utk::size_t width = get_width();
  const utk::size_t height= get_height();

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
