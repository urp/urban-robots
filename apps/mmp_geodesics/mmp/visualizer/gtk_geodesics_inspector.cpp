//           mmp-visualizer.cpp
//  Thu Jun 10 18:13:48 2010
//  Copyright  2010  Peter Urban
//  <s9peurba@stud.uni-saarland.de>

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

#include "common.hpp"

#include "mmp/visualizer/gtk_geodesics_inspector.hpp"

#include "surface/tri_surface/gl_drawable.hpp"

#include <boost/lexical_cast.hpp>

gtk::GeodesicsInspector::GeodesicsInspector( BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder )
: Gtk::Window( cobject ), m_geodesics(0), m_view( 0 ), m_clog_buffer( 0 ), m_builder( builder )
{
  std::clog << "gtk::GeodesicsInspector::GeodesicsInspector\t" << std::endl;

  m_builder->get_widget( "observer_vbox", m_vbox );

  m_builder->get_widget( "top_event_entry", m_top_event_entry );
  m_builder->get_widget( "top_window_entry", m_top_window_entry );
  m_builder->get_widget( "top_distance_label", m_top_distance_label );
  m_builder->get_widget( "queue_size_label", m_queue_size_label );

  m_builder->get_widget( "check_result_check", m_check_result_check );
  on_check_result_check_clicked();
  m_check_result_check->signal_clicked().connect( sigc::mem_fun( *this, &GeodesicsInspector::on_check_result_check_clicked ) );


  m_builder->get_widget( "stop_on_errors_check", m_stop_on_errors_check );
  on_stop_on_errors_check_clicked();
  m_stop_on_errors_check->signal_clicked().connect( sigc::mem_fun( *this, &GeodesicsInspector::on_stop_on_errors_check_clicked ) );

  m_builder->get_widget( "step_button", m_step_button );
  m_step_button->signal_clicked().connect( sigc::mem_fun( *this, &GeodesicsInspector::single_step ) );

  m_builder->get_widget( "iterate_toggle", m_iterate_button );
  m_iterate_button->signal_clicked().connect( sigc::mem_fun( *this, &GeodesicsInspector::toggle_iteration ) );
  m_iterate_button->set_label( Gtk::StockID( Gtk::Stock::MEDIA_PLAY ).get_string() );

  set_view( gtk::GLView::create() );
}


void gtk::GeodesicsInspector::initialize( const std::shared_ptr< Geodesics >& geodesics, const std::shared_ptr< const TriSurface >& surface )
{
  assert( geodesics );

  const std::shared_ptr< const TriSurface >& new_surface =  surface;// TODO: geodesics->get_surface(); - NEED: std::shared_ptr NOTE: would allow to remove surface arg

  bool same_surface = m_geodesics && ( &m_geodesics->get_surface() == new_surface.get() );

  m_geodesics = geodesics;

  if( ! same_surface )
  {
    if( m_surface_drawable )
      m_surface_drawable->remove_from_all_views();

    m_surface_drawable = gl::SurfaceDrawable::create( new_surface );

    m_surface_drawable->set_edge_mode( gl::SurfaceDrawable::INVISIBLE_EDGE_MODE );
    m_view->get_canvas()->add_drawable( m_surface_drawable );
  }

  if( m_geodesics_drawable )
    m_geodesics_drawable->remove_from_all_views();

  m_geodesics_drawable = gl::GeodesicsDrawable::create( m_geodesics );

  m_view->get_canvas()->add_drawable( m_geodesics_drawable );

  set_title( "propagating from vertex " + boost::lexical_cast<std::string>( m_geodesics->source() ) );

  m_step_button->set_sensitive( true );
  m_iterate_button->set_sensitive( true );
}

void gtk::GeodesicsInspector::run_propagation( )
{
  // set up file for debug
  std::ostringstream path;

  path << "logs/" << m_geodesics->source() << "_propagation";

  redirect_clog_to_file( path.str() );

  assert( m_geodesics );

  m_geodesics->initialize();

  Gtk::Main::run(*this);

  std::clog << "mmp::visualizer::gtk::GeodesicsInspector::run_debugging_propagation\t|"
            << "completed source " << m_geodesics->source()
            << " with " << mmp::Window::next_id << " windows created in total"
            << std::endl;
}

bool gtk::GeodesicsInspector::step()
{
  std::clog << "mmp::visualizer::gtk::GeodesicsInspector::step" << std::endl;

  // skip non-frontier event points
  do
  {
    if( ! m_geodesics->step() )
    {
      //:::|propagation finished

      const bool end_result_sane = m_check_result ? m_geodesics->sanity_check() :true;

      // deactivate propagation controls
      m_step_button->set_sensitive( false );
      m_iterate_button->set_sensitive( false );

      if( m_view->get_canvas()->is_renderer_blocked() )  m_view->force_redraw();

      // check result
      if( !end_result_sane && m_stop_on_errors )
      { Gtk::MessageDialog( "sanity check failed for source "
                          + boost::lexical_cast< std::string >( m_geodesics->source() )
                          ).run();
        m_iterate_button->set_active( false );
        return false; // block idle signal -> keep window open for eximination
      }
      hide();// stops inner main-loop
    }
  }while( !m_geodesics->event_queue.empty() && ! ( m_geodesics->event_queue.top()->flags() & EventPoint::FRONTIER ) );

  //:::|show text information about the next event

  if( !m_geodesics->event_queue.empty() )
  {
    const EventPoint* top_event = m_geodesics->event_queue.top();

    m_top_event_entry   ->set_text( boost::lexical_cast<std::string>( *top_event ) );
    m_top_window_entry  ->set_text( boost::lexical_cast<std::string>( *top_event->window() ) );
    m_top_distance_label->set_text( boost::lexical_cast<std::string>( top_event->distance() ) );
    m_queue_size_label  ->set_text( boost::lexical_cast<std::string>( m_geodesics->event_queue.size() ) );

    m_geodesics_drawable->invalidate();
  }
  return true;
}

void gtk::GeodesicsInspector::toggle_iteration()
{

  std::clog << "mmp::visualizer::gtk::GeodesicsInspector::toggle_iteration" << std::endl;

  if( !m_iterate_connection.connected() )
  { m_iterate_connection = Glib::signal_idle().connect( sigc::mem_fun( *this, &GeodesicsInspector::step ) );
    m_iterate_connection.block();
  }

  if( m_iterate_connection.blocked() )
  {
    m_iterate_connection.unblock();
    m_iterate_button->set_label( Gtk::StockID( Gtk::Stock::MEDIA_PAUSE ).get_string() );
  }
  else
  {
    m_iterate_connection.block();
    m_iterate_button->set_label( Gtk::StockID( Gtk::Stock::MEDIA_PLAY ).get_string() );
  }

}
