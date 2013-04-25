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

# include "mmp/visualizer/gl_drawable.hpp"

//# include "surface/tri_surface/gl_drawable.hpp"

# include "common.hpp"

# include <boost/lexical_cast.hpp>

gl::GeodesicsDrawable::GeodesicsDrawable( Geodesics* g )
: m_geodesics( g ), m_covering_visible( true )
{ }


void gl::GeodesicsDrawable::gl_initialize_context()
{
  const size_t width = 256;
  const size_t num_components = 4;
  float data[ width * num_components ];

  data[0] = 1.;
  data[1] = 0.;
  data[2] = 0.;
  data[3] = 1.;

  const size_t subdivisions = 10;
  const size_t gap = width / subdivisions;
  for( size_t i = 1; i < width; ++i )
  {
    const size_t pix = i * num_components;
    data[pix + 0] = i % gap == 0 ? 1.f : .3f;
    data[pix + 1] = i % gap == 0 ? 1.f : .3f;
    data[pix + 2] = i % gap == 0 ? 1.f : .3 + float(i) / ( width - 1 ) * .3;
    data[pix + 3] = i % gap == 0 ? 1.f : .9;
  }

  // allocate a texture name
  glGenTextures( 1, &m_equidist_texture );

  // select our current texture
  glBindTexture( GL_TEXTURE_1D, m_equidist_texture );

  glMatrixMode( GL_TEXTURE );

    glLoadIdentity();
    glScalef( 10., 10., 10. );

  glMatrixMode( GL_MODELVIEW );

  // select modulate to mix texture with color for shading
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

  glTexParameterf( GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
  glTexParameterf( GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  glTexParameterf( GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT );

  // build our texture mipmaps
  gluBuild1DMipmaps( GL_TEXTURE_1D, num_components /*3*/, width
                   , GL_RGBA, GL_FLOAT, data );
}


void gl::GeodesicsDrawable::gl_draw_event_point( EventPoint* ev, const bool is_top_event )
{
  using ::gl::Color;
  using ::gl::Vertex;

  Geodesics::edge_handle edge( ev->window()->edge, get_geodesics()->surf );

  const location_t evloc =  edge.ray().at_arc_length( ev->point() );

  glDisable( GL_LIGHTING );

 // draw event point
  if( is_top_event )
  { // draw top-event marker
    glPointSize( 5. );
    Color( rgba_color_t( 1, .2, .2, 1 ) );

  }else
  {
    glPointSize( 3. );

    const rgba_color_t ev_col( ev->flags() & EventPoint::FRONTIER ? rgba_color_t( 1., .1, .1, .8 ) : rgba_color_t( .1, .1, 1, .2 ) );
    Color( ev_col );
  }

  glBegin( GL_POINTS );
    Vertex( evloc );
  glEnd();

}

void gl::GeodesicsDrawable::gl_draw_window_edges( const Window& window, const Window::types& window_type
                                                , const location_t& win_left, const location_t& win_right
                                                , const location_t& pre_left, const location_t& pre_right
                                                , const rgba_color_ref_t edge_color, const rgba_color_ref_t source_edge_color )
{
  using ::gl::Vertex;
  using ::gl::Color;

  glDisable( GL_LIGHTING );

  if( window_type == Window::INNER_SIDELOBE )
  {
    glLineWidth( 1. );
    //const bool ps_left = window.has_ps_vertex<mmp::LEFT>();

    glBegin( GL_LINES );

      Color( /*ps_left ? source_edge_color :*/ edge_color ); Vertex( win_left );
      /*Color( ps_left ? edge_color : source_edge_color );*/ Vertex( win_right );

    glEnd();
  }else
  {
    glLineWidth( 1. );
    glBegin( GL_LINES );

      Color( edge_color );
      Vertex( win_left  );

      if(window_type == Window::OUTER_SIDELOBE)
        Color( source_edge_color );
      Vertex( pre_left  );

      Color( edge_color );
      Vertex( win_right );
      if(window_type == Window::OUTER_SIDELOBE)
        Color( source_edge_color );
      Vertex( pre_right );

      //Color( edge_color );
      //Vertex( win_left  ); Vertex( win_right );

    glEnd();
  }
}


bool gl::GeodesicsDrawable::gl_draw_window_subdivision( const Window& window
                                                      , const rgba_color_ref_t edge_color
                                                      , const rgba_color_ref_t fill_color
                                                      , const rgba_color_ref_t source_color
                                                      , const shading_t shading
                                                      )
{ using mmp::LEFT;
  using mmp::RIGHT;

  const Window* pre = window.predeccessor();

  const Window::types type = window.type();
  if( pre )
  {
    std::tuple< coord_t, coord_t > pre_bounds = get_geodesics()->backtrace( window, window );

    const Geodesics::edge_handle win_edge( window.edge, m_geodesics->get_surface() );
    const Geodesics::edge_handle pre_edge( pre->edge  , m_geodesics->get_surface() );

    const location_t win_left  = win_edge.ray().at_arc_length( window.bound< mmp::LEFT  >() );
    const location_t win_right = win_edge.ray().at_arc_length( window.bound< RIGHT >() );

    const location_t pre_left  = pre_edge.ray().at_arc_length( get<  LEFT >(pre_bounds) );
    const location_t pre_right = pre_edge.ray().at_arc_length( get< RIGHT >(pre_bounds) );

    ps_t pre_ps = pre->pseudosource();

    gl_do_draw_subdivision( window
                          , type
                          , 2e-4
                          , edge_color, fill_color, source_color, shading
                          , win_edge.face().normal()
                          , window.bounds()
                          , window.source_distances()
                          , std::make_pair( pre->source_distance( get< LEFT>(pre_bounds), pre_ps )
                                          , pre->source_distance( get<RIGHT >(pre_bounds), pre_ps ) )
                          , std::make_pair( win_left, win_right )
                          , std::make_pair( pre_left, pre_right )
                          , window.pseudosource()
                          , pre_ps );

    gl_draw_window_edges( window, type, win_left, win_right, pre_left, pre_right, edge_color, /*!!!*/ source_color );

    return ! ( type & Window::OUTER_SIDELOBE );
  }
  return false;
}



void gl::GeodesicsDrawable::gl_do_draw_subdivision( const Window&           window
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
                                                  , const ps_t& win_ps
                                                  , const ps_t& pre_ps
                                                  )
{ using mmp::LEFT;
  using mmp::RIGHT;

  using ::gl::Vertex;
  using ::gl::Normal;
  using ::gl::Color;

  //std::cout<< "gl::GeodesicsDrawable::gl_do_draw_subdivision\t| " << window << std::endl;

  assert( window.predeccessor() );
  const Window& pre = *window.predeccessor();

  const Geodesics::edge_handle win_edge( window.edge, m_geodesics->get_surface() );
  const Geodesics::edge_handle pre_edge( pre.edge   , m_geodesics->get_surface() );

  const coord_t    win_mid          = .5 * ( get< LEFT >( bounds ) + get< RIGHT >( bounds ) );
  const distance_t win_mid_distance = window.source_distance( win_mid , win_ps );

  const bool subdivide = std::fabs( ( .5*( get< LEFT >(win_distances) + get< RIGHT >(win_distances) ) -  win_mid_distance ) /* ( get< LEFT >(bounds) + get< RIGHT >(bounds) */ ) > recursion_threshold;

  if( subdivide )
  {
    const coord_t    pre_mid          = m_geodesics->backtrace( window, win_mid );
    const distance_t pre_mid_distance = pre.source_distance( pre_mid , pre_ps );

    const location_t win_mid_point  = win_edge.ray().at_arc_length( win_mid );
    const location_t pre_mid_point  = pre_edge.ray().at_arc_length( pre_mid );


    gl_do_draw_subdivision( window
                          , window_type
                          , recursion_threshold
                          , edge_color, fill_color, source_color, shading
                          , normal
                          , { get< LEFT >(bounds)       , win_mid }
                          , { get< LEFT >(win_distances), win_mid_distance }
                          , { get< LEFT >(pre_distances), pre_mid_distance }
                          , { get< LEFT >(win_points)   , win_mid_point }
                          , { get< LEFT >(pre_points)   , pre_mid_point }
                          , win_ps, pre_ps
                          );
    gl_do_draw_subdivision( window
                          , window_type
                          , recursion_threshold
                          , edge_color, fill_color, source_color, shading
                          , normal
                          , { win_mid         , get< RIGHT >(bounds) }
                          , { win_mid_distance, get< RIGHT >(win_distances) }
                          , { pre_mid_distance, get< RIGHT >(pre_distances) }
                          , { win_mid_point   , get< RIGHT >(win_points) }
                          , { pre_mid_point   , get< RIGHT >(pre_points) }
                          , win_ps, pre_ps
                          );
    // uncomment to drw subdivision
    //
    glPointSize( 1 );

    glBegin( GL_LINES );

      gl::Color( .5, .2, 1. , 1.);

      gl::Vertex( win_mid_point );

      gl::Vertex( pre_mid_point );

    glEnd();
    //
  }
  else
  {
    gl_draw_interval( window
                    , window_type
                    , edge_color, fill_color, source_color, shading
                    , normal
                    , { get< LEFT >(win_distances), get< RIGHT >(win_distances) }
                    , { get< LEFT >(pre_distances), get< RIGHT >(pre_distances) }
                    , { get< LEFT >(win_points)   , get< RIGHT >(win_points) }
                    , { get< LEFT >(pre_points)   , get< RIGHT >(pre_points) }
                    );
  }

}

void gl::GeodesicsDrawable::gl_draw_interval( const Window&             window
                                            , const Window::types       window_type
                                            , const rgba_color_ref_t    edge_color
                                            , const rgba_color_ref_t    fill_color
                                            , const rgba_color_ref_t    source_color
                                            , const shading_t           shading
                                            , const location_ref_t      normal
                                            , const std::pair< const distance_t&, const distance_t& >& win_distances
                                            , const std::pair< const distance_t&, const distance_t& >& pre_distances
                                            , const std::pair< const location_t&, const location_t& >& win_points
                                            , const std::pair< const location_t&, const location_t& >& pre_points )
{
  using mmp::LEFT;
  using mmp::RIGHT;

  using ::gl::Vertex;
  using ::gl::Normal;
  using ::gl::Color;

  // default: FLAT_SHADING
  rgba_color_t win_left_color = fill_color, win_right_color = fill_color,
               pre_left_color = fill_color, pre_right_color = fill_color;


  if( shading == ABSOLUTE_DISTANCE_SHADING )
  {
    const distance_t max_distance = get_geodesics()->max_distance();

    win_left_color.rgb()  = rgb_color_t( get< LEFT>(win_distances) / max_distance );
    win_right_color.rgb() = rgb_color_t( get<RIGHT>(win_distances) / max_distance );

    pre_left_color.rgb()  = rgb_color_t( get< LEFT>(pre_distances) / max_distance );
    pre_right_color.rgb() = rgb_color_t( get<RIGHT>(pre_distances) / max_distance );
  }


  if( shading == TEXTURE_DISTANCE_SHADING )
  {
    glEnable( GL_TEXTURE_1D );
    glBindTexture( GL_TEXTURE_1D, m_equidist_texture );
  }

  glEnable( GL_LIGHTING );

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

  const distance_t top_distance = m_geodesics->event_queue.empty() ? 0. : m_geodesics->event_queue.top()->distance();

  if( window_type == Window::OUTER_SIDELOBE )
  {
  // pseudosource vertex
    glBegin( GL_TRIANGLES );
      Normal( normal );
    Color( win_left_color  ); glTexCoord1d( get< LEFT>(win_distances) - top_distance ); Vertex( get< LEFT>(win_points) );
    Color( win_right_color ); glTexCoord1d( get<RIGHT>(win_distances) - top_distance ); Vertex( get<RIGHT>(win_points) );
    Color( source_color    ); glTexCoord1d( get<RIGHT>(pre_distances) - top_distance ); Vertex( get<RIGHT>(pre_points) );
    glEnd();
  }
  else
  {
    glBegin( GL_QUADS );
      Normal( normal );
    Color( win_left_color  ); glTexCoord1d( get< LEFT>(win_distances) - top_distance ); Vertex( get< LEFT>(win_points) );
    Color( win_right_color ); glTexCoord1d( get<RIGHT>(win_distances) - top_distance ); Vertex( get<RIGHT>(win_points) );
    Color( pre_right_color ); glTexCoord1d( get<RIGHT>(pre_distances) - top_distance ); Vertex( get<RIGHT>(pre_points) );
    Color( pre_left_color  ); glTexCoord1d( get< LEFT>(pre_distances) - top_distance ); Vertex( get< LEFT>(pre_points) );
    glEnd();
  }

  if( shading == TEXTURE_DISTANCE_SHADING )
  { glDisable( GL_TEXTURE_1D ); }

  glDisable( GL_LIGHTING );
}

bool gl::GeodesicsDrawable::gl_draw_window( const Window& window
                                          , const rgba_color_ref_t edge_color
                                          , const rgba_color_ref_t fill_color
                                          , const rgba_color_ref_t source_color
                                          , const shading_t shading )
{ using mmp::LEFT;
  using mmp::RIGHT;

  const Window* pre = window.predeccessor();

  const Window::types type = window.type();
  if( pre )
  {
    std::tuple< coord_t, coord_t > pre_bounds = get_geodesics()->backtrace( window, window );

    const Geodesics::edge_handle win_edge( window.edge, m_geodesics->get_surface() );
    const Geodesics::edge_handle pre_edge( pre->edge  , m_geodesics->get_surface() );

    const utk::ray< coord_t, 3 > win_ray = win_edge.ray();
    const utk::ray< coord_t, 3 > pre_ray = pre_edge.ray();

    const location_t win_left  = win_ray.at_arc_length( window.bound<  LEFT >() );
    const location_t win_right = win_ray.at_arc_length( window.bound< RIGHT >() );

    const location_t pre_left  = pre_ray.at_arc_length( get<  LEFT >( pre_bounds ) );
    const location_t pre_right = pre_ray.at_arc_length( get< RIGHT >( pre_bounds ) );

    ps_t pre_ps = pre->pseudosource();
    glPolygonOffset( 0.4,0.4 );
    gl_draw_interval( window
                    , type
                    , edge_color, fill_color, source_color, shading
                    , win_edge.face().normal()
                    , window.source_distances()
                    , std::make_pair( pre->source_distance( get< LEFT >( pre_bounds ), pre_ps )
                                    , pre->source_distance( get<RIGHT >( pre_bounds ), pre_ps ) )
                    , std::make_pair( win_left, win_right )
                    , std::make_pair( pre_left, pre_right )
                    );
    glPolygonOffset( 1.,1. );
    return ! ( type & Window::OUTER_SIDELOBE );
  }
  return false;
}


void gl::GeodesicsDrawable::gl_draw_window_sequence( const Window& window
                                                   , const rgba_color_ref_t edge_color
                                                   , const rgba_color_ref_t fill_color
                                                   , const rgba_color_ref_t source_color
                                                   , const shading_t shading )
{
  bool no_root = gl_draw_window( window, edge_color, fill_color, source_color, shading );
  if( window.predeccessor() && no_root )
  {
    glPolygonOffset( 0.,0. );
      gl_draw_window_sequence( *window.predeccessor(), edge_color, fill_color, source_color, shading );
    glPolygonOffset( 1.,1. );
  }
  //else std::cout<< "mmp::visualizer::gl::GeodesicsDrawable::gl_draw_window_sequence\t| last " << window << std::endl;
}

void gl::GeodesicsDrawable::gl_draw_covering( const shading_t shading )
{
  auto edges = m_geodesics->get_surface().edge_handles();

  for( auto edge_it = edges.first; edge_it != edges.second; ++edge_it )
  {
    const Geodesics::winlist_t& window_list = m_geodesics->windows[ *edge_it ];

    const rgba_color_t edge_color( .5, .5, .5, .5 );
    const rgba_color_t fill_color( .5, .5, .5, 1. );
    const rgba_color_t source_color( 1., 1., .0, 1. );

    std::for_each( window_list.begin(), window_list.end()
                 , [&]( Geodesics::winlist_t::value_type win_ptr )
                   { return gl_draw_window_subdivision( *win_ptr, edge_color, fill_color, source_color, shading ); }
                 );
  }

}


void gl::GeodesicsDrawable::gl_draw_wavefront_indicators( EventPoint*   ev
                                                        , const rgba_color_ref_t crossing_color
                                                        , const rgba_color_ref_t colinear_color )
{ using mmp::LEFT;
  using mmp::RIGHT;

  using ::gl::Vertex;
  using ::gl::Color;

  const Window& window = *ev->window();
  Geodesics::edge_handle edge( window.edge, get_geodesics()->surf );

  const coord_t rel_length = .333;

  auto draw_indicators = [&] ( EventPoint* left_ev, EventPoint* right_ev )
                         { const Window& left_win =  *left_ev->window();
                           const Window& right_win = *right_ev->window();

                           Geodesics::edge_handle  left_edge(  left_win.edge, m_geodesics->get_surface() );
                           Geodesics::edge_handle right_edge( right_win.edge, m_geodesics->get_surface() );

                           Vertex(  left_edge.ray().at_arc_length( left_win.bound<RIGHT>() - rel_length * left_win.length() ) );
                           Vertex(  left_edge.ray().at_arc_length( left_win.bound<RIGHT>() ) );

                           Vertex( right_edge.ray().at_arc_length( right_win.bound<LEFT>() ) );
                           Vertex( right_edge.ray().at_arc_length( right_win.bound<LEFT>() + rel_length * right_win.length() ) );
                         };

  # if defined FLAT_MMP_MAINTAIN_WAVEFRONT


  if( ev->colinear<LEFT>() )
  {
    glLineWidth( 3. );
    Color( colinear_color );
  }else
  {
    glLineWidth( 2. );
    Color( crossing_color );
  }

  glBegin( GL_LINE_STRIP );

  if( ev->adjacent< LEFT >() )
  draw_indicators( ev->adjacent< LEFT >(), ev );

  glEnd();

  # endif
}

void gl::GeodesicsDrawable::gl_draw_wavefront( const shading_t shading )
{
  using mmp::LEFT;
  using mmp::RIGHT;

  Geodesics::event_queue_t& queue = m_geodesics->event_queue;

  rgba_color_t top_edge_color           ( 1, 0, 0, .5 );
  rgba_color_t top_covering_color       ( 1, 0, 0, .3 );

  # if defined FLAT_MMP_MAINTAIN_WAVEFRONT
  rgba_color_t colin_indicator_color  ( .3, .8, .1, 1. );
  rgba_color_t colin_edge_color     ( .3, .8, .1, .4 );
  rgba_color_t colin_covering_color   ( .3, .8, .1, .3 );

  rgba_color_t cross_indicator_color  ( .8, .3, .1, 1. );
  rgba_color_t cross_edge_color       ( .8, .3, .1, .4 );
  rgba_color_t cross_covering_color   ( .8, .3, .1, .3 );
  # endif

  rgba_color_t edge_color           ( 1, .5, 1, .6 );
  rgba_color_t fill_color           ( 1, .5, 1, .1 );
  rgba_color_t source_color         ( 1., 1. ,.0, 1. );

  /*auto draw_win     = [&] ( const Window& win )
                      { this->gl_draw_window( win, edge_color, fill_color, source_color, shading ); };*/

  auto draw_top_win = [&] ( const Window& win )
                      { this->gl_draw_window_sequence( win, top_edge_color, top_covering_color, source_color, shading ); };

  # if defined FLAT_MMP_MAINTAIN_WAVEFRONT
  auto draw_colin_win = [&] ( const Window& win )
                        { this->gl_draw_window_sequence( win, colin_edge_color, colin_covering_color, source_color, shading ); };

  auto draw_cross_win = [&] ( const Window& win )
                        { this->gl_draw_window_sequence( win, cross_edge_color, cross_covering_color, source_color, shading ); };
  # endif

  //glDisable( GL_DEPTH_TEST );

  EventPoint* top_ev = queue.top();

  std::for_each( queue.rbegin(), queue.rend()
               , [&] ( EventPoint* ev )
                 {
                   const bool is_top_ev = ev == top_ev;

                   # if defined MMP__INSERT_BOUNDARY_EVENTS
                   if( ev->flags() & EventPoint::FRONTIER )
                   # endif
                   {
                     gl_draw_wavefront_indicators( ev, cross_indicator_color, colin_indicator_color );

                     if( is_top_ev )
                       draw_top_win( *ev->window() );
                     # if defined FLAT_MMP_MAINTAIN_WAVEFRONT
                     else if( ev == top_ev->colinear<LEFT>() || ev == top_ev->colinear<RIGHT>() )
                       draw_colin_win( *ev->window() );
                     else if( ev == top_ev->adjacent<LEFT>() || ev == top_ev->adjacent<RIGHT>() )
                       draw_cross_win( *ev->window() );
                     # endif
                    // else
                    //   draw_win( *ev->window() );

                     gl_draw_event_point( ev, is_top_ev );
                   }

                 }
               );
  //glEnable( GL_DEPTH_TEST );
}


void gl::GeodesicsDrawable::gl_draw()
{
  //std::clog << "gl::GeodesicsDrawable::gl_draw" << std::endl;

  if( get_covering_visibility() )
    gl_draw_covering( TEXTURE_DISTANCE_SHADING );

  if( ! m_geodesics->event_queue.empty() )
    gl_draw_wavefront( FLAT_SHADING );

  //glDeleteTextures( 1, &m_equidist_texture );
}
