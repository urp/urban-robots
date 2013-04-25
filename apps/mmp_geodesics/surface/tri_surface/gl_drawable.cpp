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

//# include <gtkmm/box.h>

# include <boost/accumulators/accumulators.hpp>
# include <boost/accumulators/statistics/min.hpp>
# include <boost/accumulators/statistics/max.hpp>

using namespace flat;

const gl::SurfaceDrawable::mode_t gl::SurfaceDrawable::GAUSSIAN_CURVATURE_VERTEX_MODE = "gaussian curvature";
const gl::SurfaceDrawable::mode_t gl::SurfaceDrawable::HEIGHT_VERTEX_MODE       = "height";
const gl::SurfaceDrawable::mode_t gl::SurfaceDrawable::INVISIBLE_VERTEX_MODE    = "invisible";
const gl::SurfaceDrawable::mode_t gl::SurfaceDrawable::SOLID_VERTEX_MODE        = "solid";
const gl::SurfaceDrawable::mode_t gl::SurfaceDrawable::TEXTURE_VERTEX_MODE      = "texture";


const gl::SurfaceDrawable::mode_t gl::SurfaceDrawable::INVISIBLE_EDGE_MODE = "invisible";
const gl::SurfaceDrawable::mode_t gl::SurfaceDrawable::SOLID_EDGE_MODE     = "solid";

const gl::SurfaceDrawable::mode_t gl::SurfaceDrawable::INVISIBLE_FACE_MODE = "invisible";
const gl::SurfaceDrawable::mode_t gl::SurfaceDrawable::SOLID_FACE_MODE     = "solid";
const gl::SurfaceDrawable::mode_t gl::SurfaceDrawable::TEXTURE_FACE_MODE   = "texture";


void gl::SurfaceDrawable::gl_initialize_context()
{
  /*std::clog << "flat::gl::SurfaceDrawable::gl_init_texture" << std::endl;

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

void gl::SurfaceDrawable::gl_draw_gaussian_curvature_vertices() const
{
  using namespace boost::accumulators;

  // draw position samples with color dependent on the local gaussian curvature
  accumulator_set< curvature_t, features< tag::min, tag::max > > curv_acc;

  std::vector<rgb_color_t>      colors( get_surface()->num_vertices() );
  std::vector<rgb_color_t>::iterator  col_it = colors.begin();

  for( auto its = get_surface()->vertex_handles() ; its.first != its.second; its.first++ )
  {
    assert( col_it!=colors.end());

    // the gaussian curvature at vertex

    const curvature_t curvature = its.first->is_boundary_vertex()
                                  ? 0 : ( 2*M_PI - its.first->total_angle() ) / its.first->one_ring_area() / 3; // use voronoy region???

    curv_acc( curvature );

    std::cout << its.first->descriptor() << " curvature " << curvature << std::endl;

    *col_it++ = rgb_color_t( curvature < 0 ? - curvature : 0.,
                             curvature > 0 ?   curvature : 0.,
                             std::fabs( curvature )
                           );
  }

  //do the drawing
  glPointSize(get_vertex_size());

  get_surface()->set_curvature_extrema( min( curv_acc ), max( curv_acc ) );

  const curvature_t maxmag = std::max( std::fabs( min( curv_acc ) ), std::fabs( max( curv_acc ) ) );

  for( auto it = colors.begin(); it != colors.end(); it++ )
    std::cout << "color " << (*it /= maxmag) << std::endl;

  gl_draw_scaled_vertices( colors.begin() );
}

bool  gl::SurfaceDrawable::gl_draw_vertices( const mode_t& mode )   const
{
  if( mode == GAUSSIAN_CURVATURE_VERTEX_MODE )
  {
    gl_draw_gaussian_curvature_vertices();
    return true;
  }

  if( mode == HEIGHT_VERTEX_MODE )
  {
    const coord_t maxmag = std::max(   get_surface()->max_height(),
                                     - get_surface()->min_height() );
    // draw position samples with color dependent on the samples velocity_t

    glPushMatrix();

      gl::Scale ( get_global_scale() );

      glPointSize( get_vertex_size() );

      glBegin( GL_POINTS );

        for( PointCloud::vertex_descriptor id=0; id < get_surface()->num_vertices(); id++ )
        {
          const location_t& location = get_surface()->vertex( id ).location();
          gl::Color( rgb_color_t( fabsf( location[2] ) / maxmag ) );
          gl::Vertex( location );
        }

      glEnd();

    glPopMatrix();

    return true;
  }

  if( mode == INVISIBLE_VERTEX_MODE )
    return true;

  if( mode == SOLID_VERTEX_MODE )
  {
    // draw position samples using a single color
    rgb_color_t col(0.f);

    glPushMatrix();

      gl::Scale( get_global_scale() );

      glPointSize( get_vertex_size() );

      glBegin( GL_POINTS );

        gl::Color( col );

        for( auto its = get_surface()->vertex_handles(); its.first != its.second; ++its.first )
        { const location_t loc = its.first->location();
          gl::Vertex( loc );
        }

      glEnd();

    glPopMatrix();
    return true;
  }

  if( mode == TEXTURE_VERTEX_MODE )
  {
    /*
    rgb_color_t col;

    glPushMatrix();

      gl::Scale( get_global_scale() );

      glPointSize( get_vertex_size() );

      glBegin( GL_POINTS );

        for( auto its = get_surface()->vertex_handles(); its.first != its.second; ++its.first )
        {
          const location_t loc = its.first->location();
          const TriSurface::texture_type& texture = get_surface()->texture();
          const vertex_texture_coord_t::type texcoord = its.first->texture_coordinate();

          col = texture.get_pixel( std::round( texcoord[0] * ( get<0>(texture.size) - 1 ) )
                                 , std::round( texcoord[1] * ( get<1>(texture.size) - 1 ) ) );

          gl::Color( col );
          gl::Vertex( loc );
        }

      glEnd();

    glPopMatrix();
    return true;
    */
  }

  return false;

}

bool  gl::SurfaceDrawable::gl_draw_edges( const mode_t& mode )    const
{
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

    rgb_color_t col(0.f);

    glPushMatrix();

      gl::Scale( get_global_scale() );

      glLineWidth(1);

      glBegin( GL_LINES );

        gl::Color( col );
        for( edges_t::iterator it = edges.begin() ; it != edges.end(); ++it )
        { gl::Vertex( get_surface()->vertex( it->first ).location() );
          gl::Vertex( get_surface()->vertex( it->second ).location() );
        }
      glEnd();

    glPopMatrix();

    return true;
  }

  return false;
}

bool    gl::SurfaceDrawable::gl_draw_faces( const mode_t& mode )    const
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

        const location_t normal = its.first->normal();

        glBegin( GL_TRIANGLES );
          gl::Color( rgba_color_t( .3, .3, .3, 1. ) );
          gl::Normal( normal );
          gl::Vertex( v0.location() );
          gl::Vertex( v1.location() );
          gl::Vertex( v2.location() );
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

void    gl::SurfaceDrawable::gl_draw_textured_faces()   const
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
    gl::Color( rgba_color_t( 1., 1., 1., 1. ) );
    gl::Normal( normal );
    gl::TexCoord2( v0.texture_coordinate() ); gl::Vertex( v0.location() );
    gl::TexCoord2( v1.texture_coordinate() ); gl::Vertex( v1.location() );
    gl::TexCoord2( v2.texture_coordinate() ); gl::Vertex( v2.location() );
    glEnd();
  }

  glPopMatrix();

  glDisable( GL_TEXTURE_2D );
  glDisable( GL_LIGHTING );
  */
}
