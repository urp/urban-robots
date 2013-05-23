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

GLCanvas::GLCanvas()
: GLDrawingArea()
, m_show_origin( false )
, m_show_pivot( true )
, m_block_renderer(false)
, cam_dist( 3. )
, cam_center( 0. )
, cam_inertial()
{
  # if defined DBG_GTK_GL_CANVAS
  std::clog << "gtk::GLCanvas::GLCanvas" << std::endl;
  # endif

  // setting camera position
  cam_inertial.position().z() += cam_dist;

  // add event signals

  add_events( Gdk::BUTTON_PRESS_MASK
            | Gdk::BUTTON_MOTION_MASK
            | Gdk::BUTTON_RELEASE_MASK
            | Gdk::SCROLL_MASK
            //| Gdk::STRUCTURE_MASK
            );


  // view transformation signals. Events have to be enabled in the glade file
  signal_button_press_event().connect(  sigc::mem_fun(*this, &GLCanvas::on_button_press_event) );
  signal_motion_notify_event().connect( sigc::mem_fun(*this, &GLCanvas::on_motion_notify_event));
  signal_scroll_event().connect( sigc::mem_fun(*this, &GLCanvas::on_scroll_event));

}

void GLCanvas::gl_initialize_context( )
{

  # if defined DBG_GTK_GLCANVAS_CONFIGURE
  std::clog << "gtk::GLCanvas::configure_target\t| (re-)initializing context" << std::endl;
  # endif

  glClearColor( .2, .2, .2, 1. );
  glClearDepth( 1. );

  //---| point and lines

  glEnable( GL_POINT_SMOOTH );
  glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );

  glEnable( GL_LINE_SMOOTH );
  glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

  glEnable( GL_POLYGON_SMOOTH );
  glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

  //---| fragments

  glEnable(GL_DEPTH_TEST);
  glDepthFunc( GL_LEQUAL );

  //glEnable( GL_BLEND );
  //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset( 1., 1. );

  //---| lighting

  //glDisable( GL_LIGHTING );

  //glShadeModel( GL_SMOOTH );

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


void GLCanvas::gl_initialize_queued_drawables()
{
  # if defined DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
  std::clog << "gtk::GLCanvas::gl_initialize_queued_drawables\t| "
            << "initialize " << ( m_gl_init_list.empty() ? "no " : "" ) << "queued drawables"
            << std::endl;
  # endif

  for( auto drawable : m_gl_init_list )
  { drawable->gl_initialize_context( gl_context() ); }

  m_gl_init_list.clear();

  # if defined DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
  uv::gl::PrintError( std::clog << "gtk::GLCanvas::gl_initialize_queued_drawables\t| error checkpoint" << std::endl );
  # endif
}

void GLCanvas::gl_initialize_all_drawables()
{
  # if defined DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
  std::clog << "gtk::GLCanvas::gl_initialize_all_drawables\t| " << "initialize all drawables" << std::endl;
  # endif

  for( auto drawable : *this )
  { drawable->gl_initialize_context( gl_context() ); }

  m_gl_init_list.clear();

  # if defined DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
  uv::gl::PrintError( std::clog << "gtk::GLCanvas::gl_initialize_all_drawables\t| " << "error checkpoint" << std::endl );
  # endif
}

void GLCanvas::gl_remove_queued_drawables( )
{
  # if defined DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
  std::clog << "gtk::GLCanvas::gl_remove_queued_drawables\t| "
            << "remove " << ( m_gl_remove_list.empty() ? "no " : "" ) << "queued drawables"
            << std::endl;
  # endif

  for( auto drawable : m_gl_remove_list )
  {
    drawable->gl_remove_from_context( gl_context() );
  }

  m_gl_remove_list.clear();

  # if defined DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
  uv::gl::PrintError( std::clog << "gtk::GLCanvas::gl_remove_queued_drawables\t| error checkpoint" << std::endl );
  # endif
}


void GLCanvas::gl_remove_all_drawables()
{
  # if defined DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
  std::clog << "gtk::GLCanvas::gl_remove_all_drawables\t| "
            << "removing all drawables..." << std::endl;
  # endif

  for( auto drawable : *this )
  {
    drawable->gl_remove_from_context( gl_context() );
  }

  m_gl_remove_list.clear();

  # if defined DBG_GTK_GLCANVAS_GL_INITIALIZE_CONTEXT
  uv::gl::PrintError( std::clog << "gtk::GLCanvas::gl_remove_all_drawables\t| error checkpoint" << std::endl );
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
  uv::gl::PrintError( std::clog << "gtk::GLCanvas::gl_setup_view\t| error checkpoint" << std::endl );
  # endif

}

void GLCanvas::on_realize()
{
  # if defined DBG_GTK_GLCANVAS_ON_REALIZE
  std::clog << "gtk::GLCanvas::on_realize\t| " << std::endl;
  # endif

  GLDrawingArea::on_realize();

  gl_begin_context();

    gl_initialize_context();

  gl_end_context();
}

bool GLCanvas::on_configure_event( GdkEventConfigure* event )
{
  bool success = configure( event->width, event->height );

  // TODO: should be called here, not in update_context()
  /* set up the viewport and set view matrix to identity
  gl_begin_context();
    gl_setup_view( event->width, event->height );
  gl_end_context();*/

  std::clog << "gtk::GLCanvas::on_configure_event\t| success " << success << std::endl;

  return success;
}

void GLCanvas::gl_draw_scene()
{
  # if defined DBG_GTK_GLCANVAS_GL_RENDER_SCENE
  std::clog << "gtk::GLCanvas::gl_draw_scene\t| "<< std::endl;
  # endif

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glPushMatrix();
  {
    uv::gl::gl_apply_inverse_transform( cam_inertial );

    // draw viewing pivot
    if( get_pivot_visibility() )
    {
      glPushMatrix();

        uv::gl::Translate( cam_center );

        uv::gl::DrawCoords( .2 );

      glPopMatrix();
    }

    // draw origin

    if( get_origin_visibility() )
      uv::gl::DrawCoords( 1. );

    // draw drawables

    auto context = gl_context();

    for( auto drawable : static_cast< uv::View< uv::gl::Drawable >& >( *this ) )
    {
      glPushAttrib( GL_ALL_ATTRIB_BITS );

        drawable->gl_draw( context );

      glPopAttrib();
    };

  } // of glPushMatrix()
  glPopMatrix();

  # if defined DBG_GTK_GLCANVAS_GL_RENDER_SCENE
  uv::gl::PrintError( std::clog << "gtk::GLCanvas::gl_render_scene\t| error checkpoint" << std::endl );
  # endif

}

bool GLCanvas::on_expose_event( GdkEventExpose* event )
{
  # if defined DBG_GTK_GLCANVAS_ON_EXPOSE_EVENT
  std::clog << "gtk::GLCanvas::on_expose_event\t\t|"
      <<" width " << event->area.width
      <<" height " << event->area.height
      << std::flush<<std::endl;
  # endif

  gl_begin_context();

    // process queued gl resource initializations and removals

    gl_remove_queued_drawables();

    gl_initialize_queued_drawables();

    // set up the viewport and set view matrix to identity
    // NOTE: should be called from on_configure_event
    gl_setup_view( get_width(), get_height() );

    // draw the drawables
    gl_draw_scene();

    // swap buffers if double buffered
    gl_flush();

  gl_end_context();

  /*if( m_gl_pixmap )
  {
    // TODO ??? (*gl_drawable)->wait_gl();

    get_window()->draw_drawable( get_style()->get_fg_gc(get_state()),
                                 m_gl_pixmap->pixmap(),
                                 0, 0, 0, 0,
                                 get_width(), get_height() );

    m_pixmap_update_signal( m_gl_pixmap->pixmap() );

  }*/

  return true;
}


bool GLCanvas::on_button_press_event( GdkEventButton* event )
{
  # if defined DBG_GTK_GLCANVAS_ON_BUTTON_PRESS_EVENT
  std::clog << "gtk::GLCanvas::on_button_press_event" << std::endl;
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
  const flat::location2d_t  cur_mouse_pos(event->x,event->y);
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

    flat::location2d_t       oldpos( 2*old_mouse_pos.x()/(width-1.)-1., 2*(1.-old_mouse_pos.y()/(height-1.))-1.);
    flat::location2d_t       newpos( 2*cur_mouse_pos.x()/(width-1.)-1., 2*(1.-cur_mouse_pos.y()/(height-1.))-1.);

    utk::veca< flat::coord_t, 4 > axan  ( utk::get_axis_angle_from_trackball( oldpos, newpos ));

    axan.xyz() = old_cam_inertial.rot_vec( axan.xyz() );

    cam_inertial.rot(axan,-axan.a());
    cam_inertial.quat().normalize();
  }

  flat::location_t  loc( 0.,0.,cam_dist );
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

  flat::location_t pos( flat::coord_t(0.), flat::coord_t(0.), cam_dist );
  cam_inertial.position() = cam_inertial.rot_vec( pos ) + cam_center;

  request_redraw();
  return true;
}
