/***************************************************************************
 *            surface-drawable.h
 *
 *  Sun Oct 24 14:58:49 2010
 *  Copyright  2010  urp
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

# include "surface/tri_surface/gl_drawable.hpp"

# include "gl/wrap/normal.hpp"

# include <boost/accumulators/accumulators.hpp>

# include <boost/accumulators/statistics/min.hpp>

# include <boost/accumulators/statistics/max.hpp>



using namespace uv::gl;

using flat::TriSurface;

const SurfaceDrawable::mode_t SurfaceDrawable::GAUSSIAN_CURVATURE_VERTEX_MODE = "gaussian curvature";
const SurfaceDrawable::mode_t SurfaceDrawable::HEIGHT_VERTEX_MODE       = "height";
const SurfaceDrawable::mode_t SurfaceDrawable::INVISIBLE_VERTEX_MODE    = "invisible";
const SurfaceDrawable::mode_t SurfaceDrawable::SOLID_VERTEX_MODE        = "solid";
const SurfaceDrawable::mode_t SurfaceDrawable::TEXTURE_VERTEX_MODE      = "texture";


const SurfaceDrawable::mode_t SurfaceDrawable::INVISIBLE_EDGE_MODE = "invisible";
const SurfaceDrawable::mode_t SurfaceDrawable::SOLID_EDGE_MODE     = "solid";

const SurfaceDrawable::mode_t SurfaceDrawable::INVISIBLE_FACE_MODE = "invisible";
const SurfaceDrawable::mode_t SurfaceDrawable::SOLID_FACE_MODE     = "solid";
const SurfaceDrawable::mode_t SurfaceDrawable::TEXTURE_FACE_MODE   = "texture";


void SurfaceDrawable::gl_initialize_context( const std::shared_ptr< uv::gl::Context >& )
{
  //


  //

  /*std::clog << "flat::SurfaceDrawable::gl_init_texture" << std::endl;

  glEnable( GL_TEXTURE_2D );

  // allocate a texture name
  glGenTextures( 1, &m_gl_texture_handle );

  // select our current texture
  glBindTexture( GL_TEXTURE_2D, m_gl_texture_handle );

  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture.size.first, texture.size.second, 0, GL_RGBA, GL_FLOAT, &m_texture.pixmap[0] );
*/
}

void SurfaceDrawable::gl_remove_from_context( const std::shared_ptr< uv::gl::Context >& )
{
}

void SurfaceDrawable::gl_draw_gaussian_curvature_vertices() const
{
  using namespace boost::accumulators;

  // draw position samples with color dependent on the local gaussian curvature
  accumulator_set< flat::curvature_t, features< tag::min, tag::max > > curv_acc;

  std::vector< flat::rgb_color_t > colors( get_surface()->num_vertices() );
  std::vector< flat::rgb_color_t >::iterator col_it = colors.begin();

  for( auto its = get_surface()->vertex_handles() ; its.first != its.second; its.first++ )
  {
    assert( col_it != colors.end() );

    // the gaussian curvature at vertex

    const auto curvature = its.first->is_boundary_vertex()
                           ? 0 : ( 2*M_PI - its.first->total_angle() ) / its.first->one_ring_area() / 3; // use voronoy region???

    curv_acc( curvature );

    std::cout << its.first->descriptor() << " curvature " << curvature << std::endl;

    *col_it++ = flat::rgb_color_t( curvature < 0 ? - curvature : 0.,
                                   curvature > 0 ?   curvature : 0.,
                                    std::fabs( curvature )
                                 );
  }

  //do the drawing
  glPointSize(get_vertex_size());

  get_surface()->set_curvature_extrema( min( curv_acc ), max( curv_acc ) );

  const auto maxmag = std::max( std::fabs( min( curv_acc ) ), std::fabs( max( curv_acc ) ) );

  for( auto color = colors.begin(); color != colors.end(); color++ )
    std::cout << "color " << (*color /= maxmag) << std::endl;

  gl_draw_scaled_vertices( colors.begin() );
}

bool  SurfaceDrawable::gl_draw_vertices( const mode_t& mode )   const
{

  if( mode == GAUSSIAN_CURVATURE_VERTEX_MODE )
  {
    gl_draw_gaussian_curvature_vertices();
    return true;
  }

  if( mode == HEIGHT_VERTEX_MODE )
  {
    const auto maxmag = std::max(   get_surface()->max_height(),
                                  - get_surface()->min_height() );
    // draw position samples with color dependent on the samples velocity_t

    glPushAttrib( GL_POINT_BIT );

    glPushMatrix();

      Scale ( get_global_scale() );

      glPointSize( get_vertex_size() );

      glBegin( GL_POINTS );

        for( flat::PointCloud::vertex_descriptor id=0; id < get_surface()->num_vertices(); id++ )
        {
          const auto location = get_surface()->vertex( id ).location();
          Color( flat::rgb_color_t( std::fabs( location[2] ) / maxmag ) );
          Vertex( location );
        }

      glEnd();

    glPopMatrix();

    glPopAttrib();

    return true;
  }

  if( mode == INVISIBLE_VERTEX_MODE )
    return true;

  if( mode == SOLID_VERTEX_MODE )
  {
    // draw position samples using a single color
    flat::rgb_color_t col(0.f);

    glPushAttrib( GL_POINT_BIT );

    glPushMatrix();

      Scale( get_global_scale() );

      glPointSize( get_vertex_size() );

      glBegin( GL_POINTS );

        Color( col );

        for( auto its = get_surface()->vertex_handles(); its.first != its.second; ++its.first )
        {
          const auto loc = its.first->location();
          Vertex( loc );
        }

      glEnd();

    glPopMatrix();

    glPopAttrib();

    return true;
  }

  if( mode == TEXTURE_VERTEX_MODE )
  {
    glPushAttrib( GL_POINT_BIT | GL_TEXTURE_BIT );

    /*
    rgb_color_t col;

    glPushMatrix();

      Scale( get_global_scale() );

      glPointSize( get_vertex_size() );

      glBegin( GL_POINTS );

        for( auto its = get_surface()->vertex_handles(); its.first != its.second; ++its.first )
        {
          const location_t loc = its.first->location();
          const TriSurface::texture_type& texture = get_surface()->texture();
          const vertex_texture_coord_t::type texcoord = its.first->texture_coordinate();

          col = texture.get_pixel( std::round( texcoord[0] * ( get<0>(texture.size) - 1 ) )
                                 , std::round( texcoord[1] * ( get<1>(texture.size) - 1 ) ) );

          Color( col );
          Vertex( loc );
        }

      glEnd();

    glPopMatrix();

    glPopAttrib();

    return true;
    */
  }

  return false;
}


bool  SurfaceDrawable::gl_draw_edges( const mode_t& mode )    const
{
  glPushAttrib( GL_LINE_BIT );

  if( mode == INVISIBLE_EDGE_MODE )
    return true;

  if( mode == SOLID_EDGE_MODE )
  {
    typedef std::vector< std::pair< TriSurface::vertex_descriptor, TriSurface::vertex_descriptor > > edges_t;

    edges_t edges( get_surface()->num_full_edges() );

    for( TriSurface::vertex_descriptor id = 0; id < get_surface()->num_vertices(); id++ )
    {
      std::vector< TriSurface::vertex_descriptor > adj( std::move( get_surface()->neighbors( id ) ) );
      std::for_each( adj.begin(), adj.end()
                   , [ &edges, &id ] ( TriSurface::vertex_descriptor adj ) { edges.push_back( edges_t::value_type( id , adj ) ); }
                   );
    }

    flat::rgb_color_t col(0.f);

    glPushMatrix();

      Scale( get_global_scale() );

      glLineWidth(1);

      glBegin( GL_LINES );

        Color( col );
        for( edges_t::iterator it = edges.begin() ; it != edges.end(); ++it )
        { Vertex( get_surface()->vertex( it->first ).location() );
          Vertex( get_surface()->vertex( it->second ).location() );
        }
      glEnd();

    glPopMatrix();

    return true;
  }

  return false;
}


bool SurfaceDrawable::gl_draw_faces( const mode_t& mode )    const
{
  if( mode == INVISIBLE_FACE_MODE ) return true;


  if( mode == SOLID_FACE_MODE )
  {
    glPushMatrix();

      Scale( get_global_scale() );

      for( auto its = get_surface()->face_handles(); its.first != its.second; its.first++ )
      {
        const TriSurface::edge_handle e0 = its.first->edge();
        const TriSurface::edge_handle e1 = e0.next();
        const TriSurface::edge_handle e2 = e1.next();

        const TriSurface::vertex_handle v0 = e0.source();
        const TriSurface::vertex_handle v1 = e1.source();
        const TriSurface::vertex_handle v2 = e2.source();

        const auto normal = its.first->normal();

        glBegin( GL_TRIANGLES );
          Color( flat::rgba_color_t( .3, .3, .3, 1. ) );
          Normal( normal );
          Vertex( v0.location() );
          Vertex( v1.location() );
          Vertex( v2.location() );
        glEnd();
      }

    glPopMatrix();
    return true;
  }

  if( mode == TEXTURE_FACE_MODE )
  {
    //gl_draw_textured_faces();

    //glDeleteTextures( 1, & m_gl_texture_handle );

    return true;
  }
  return false;
}

void    SurfaceDrawable::gl_draw_textured_faces()   const
{
/*
  glPushMatrix();

  Scale( get_global_scale() );

  //glEnable( GL_LIGHTING );

  glEnable( GL_TEXTURE_2D );
  glBindTexture( GL_TEXTURE_2D, m_gl_texture_handle );

  for( auto its = get_surface()->face_handles(); its.first != its.second; its.first++ )
  {
    const TriSurface::edge_handle e0 = its.first->edge();
    const TriSurface::edge_handle e1 = e0.next();
    const TriSurface::edge_handle e2 = e1.next();

    const TriSurface::vertex_handle v0 = e0.source();
    const TriSurface::vertex_handle v1 = e1.source();
    const TriSurface::vertex_handle v2 = e2.source();

    const location_t normal = its.first->normal();

    glBegin( GL_TRIANGLES );
    Color( rgba_color_t( 1., 1., 1., 1. ) );
    Normal( normal );
    gl::TexCoord2( v0.texture_coordinate() ); Vertex( v0.location() );
    gl::TexCoord2( v1.texture_coordinate() ); Vertex( v1.location() );
    gl::TexCoord2( v2.texture_coordinate() ); Vertex( v2.location() );
    glEnd();
  }

  glPopMatrix();

  glDisable( GL_TEXTURE_2D );
  glDisable( GL_LIGHTING );
  */
}
