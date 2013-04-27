/***************************************************************************
 *            surface-drawable.hpp
 *
 *  Sun Oct 24 14:58:31 2010
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

# pragma once

# include "surface/tri_surface/tri_surface.hpp"

# include "gtk/gl_view/gl_drawable.hpp"
# include "view.hpp"

namespace gl
{
  class SurfaceDrawable : public gl::Drawable
  {
    public:

      typedef std::string         mode_t;
      typedef std::list< mode_t > mode_list_t;

      // vertex modes
      static const mode_t GAUSSIAN_CURVATURE_VERTEX_MODE;
      static const mode_t HEIGHT_VERTEX_MODE;
      static const mode_t INVISIBLE_VERTEX_MODE;
      static const mode_t SOLID_VERTEX_MODE;
      static const mode_t TEXTURE_VERTEX_MODE;

      // edge modes
      static const mode_t INVISIBLE_EDGE_MODE;
      static const mode_t SOLID_EDGE_MODE;
      // face modes
      static const mode_t INVISIBLE_FACE_MODE;
      static const mode_t SOLID_FACE_MODE;
      static const mode_t TEXTURE_FACE_MODE;

    private:

      // the active modes
      mode_t      m_vertex_mode, m_edge_mode, m_face_mode;
      // available modes
      mode_list_t m_vertex_modes, m_edge_modes, m_face_modes;

    public:

      const mode_t&   get_vertex_mode()   const   { return m_vertex_mode; }
      const mode_t&   get_edge_mode()     const   { return m_edge_mode; }
      const mode_t&   get_face_mode()     const   { return m_face_mode; }

      virtual mode_list_t get_vertex_mode_list()  const { return m_vertex_modes; }
      virtual mode_list_t get_edge_mode_list()    const { return m_edge_modes; }
      virtual mode_list_t get_face_mode_list()    const { return m_face_modes; }

      bool      is_vertex_mode_supported( const mode_t& mode )
      { return std::find( m_vertex_modes.begin(), m_vertex_modes.end(), mode ) != m_vertex_modes.end(); }

      bool      is_edge_mode_supported( const mode_t& mode )
      { return std::find( m_edge_modes.begin(), m_edge_modes.end(), mode ) != m_edge_modes.end(); }

      bool      is_face_mode_supported( const mode_t& mode )
      { return std::find( m_face_modes.begin(), m_face_modes.end(), mode ) != m_face_modes.end(); }

    protected:

      void append_vertex_modes( const mode_list_t& modes )
      {
        m_vertex_modes.insert( m_vertex_modes.end(), modes.begin(), modes.end() );
        m_vertex_modes.sort();
        m_vertex_modes.unique();
      }

      void append_edge_modes( const mode_list_t& modes )
      {
        m_edge_modes.insert( m_edge_modes.end(), modes.begin(), modes.end() );
        m_edge_modes.sort();
        m_edge_modes.unique();
      }

      void append_face_modes( const mode_list_t& modes )
      {
        m_face_modes.insert( m_face_modes.end(), modes.begin(), modes.end() );
        m_face_modes.sort();
        m_face_modes.unique();
      }

    private:

      std::shared_ptr< const flat::TriSurface > m_surface;

      mutable GLuint    m_gl_texture_handle;

      flat::location_t  m_global_scale;
      float             m_vertex_size;

      void  gl_draw_gaussian_curvature_vertices() const;
      void  gl_draw_textured_faces()    const;

    protected:

      SurfaceDrawable( const std::shared_ptr< const flat::TriSurface >& surface )
      : m_vertex_mode ( SOLID_VERTEX_MODE )
      , m_edge_mode   ( SOLID_EDGE_MODE )
      , m_face_mode   ( INVISIBLE_FACE_MODE )
      , m_vertex_modes( { GAUSSIAN_CURVATURE_VERTEX_MODE, HEIGHT_VERTEX_MODE, INVISIBLE_VERTEX_MODE, SOLID_VERTEX_MODE, TEXTURE_VERTEX_MODE } )
      , m_edge_modes  ( { INVISIBLE_EDGE_MODE, SOLID_EDGE_MODE } )
      , m_face_modes  ( { INVISIBLE_FACE_MODE, SOLID_FACE_MODE, TEXTURE_FACE_MODE } )
      , m_surface( surface )
      , m_global_scale( 1. ), m_vertex_size( 2. )
      { std::clog << "gl::SurfaceDrawable::SurfaceDrawable" << std::endl; }

    public:

      static std::shared_ptr< SurfaceDrawable > create( const std::shared_ptr< const flat::TriSurface >& surface )
      { return std::shared_ptr< SurfaceDrawable >( new SurfaceDrawable( surface ) ); }

      virtual ~SurfaceDrawable() { std::clog << "gl::SurfaceDrawable::~SurfaceDrawable" << std::endl; }

      virtual bool  gl_draw_vertices( const mode_t& )   const;
      virtual bool  gl_draw_edges   ( const mode_t& )   const;
      virtual bool  gl_draw_faces   ( const mode_t& )   const;

      virtual void  gl_draw_others() const {    };

      void set_surface( const std::shared_ptr< flat::TriSurface >& surface )
      { m_surface = surface; invalidate(); }

      const std::shared_ptr< const flat::TriSurface >& get_surface() const { return m_surface; }

      virtual void gl_initialize_context();
      virtual void gl_remove_from_context();

      virtual void gl_draw()
      {
        //std::clog << "flat::gl::SurfaceDrawable::gl_draw"
        //          << std::flush << std::endl;

        if( ! gl_draw_vertices( get_vertex_mode() ) )
          std::cerr << "gl::SurfaceDrawable::gl_draw\t|" << " vertex mode \"" << get_vertex_mode() << "\" not rendered" << std::endl;

        if( ! gl_draw_edges( get_edge_mode() ) )
          std::cerr << "gl::SurfaceDrawable::gl_draw\t|" << " edge mode \"" << get_edge_mode() << "\" not rendered" << std::endl;

        if( ! gl_draw_faces( get_face_mode() ) )
          std::cerr << "gl::SurfaceDrawable::gl_draw\t|" << " face mode \"" << get_face_mode() << "\" not rendered" << std::endl;

        gl_draw_others();
      };

      // sets the display mode of the surfaces vertices
      // returns true if drawing in this mode is possible
      // returns false if the mode is not supported
      bool set_vertex_mode( const mode_t& mode )
      {
        if( mode == get_vertex_mode() ) return true;

        if( !is_vertex_mode_supported( mode ) )
        {
          std::cerr << "gl::SurfaceDrawable::set_vertex_mode\t|"
                    << "WARNING: requested verex display mode \"" << mode <<"\""
                    << " not supported." << std::endl;
          m_vertex_mode = INVISIBLE_VERTEX_MODE;
          return false;
        }
        m_vertex_mode = mode;
        invalidate();
        return true;
      }

      bool set_edge_mode( const mode_t& mode )
      {
        if( mode == get_edge_mode() ) return true;

        if( !is_edge_mode_supported( mode ) )
        { std::cerr << "gl::SurfaceDrawable::set_edge_mode\t|"
                    << "WARNING: requested edge display mode \"" << mode <<"\""
                    << " not supported." << std::endl;
          m_edge_mode = INVISIBLE_EDGE_MODE;
          return false;
        }
        m_edge_mode = mode;
        invalidate();
        return true;
      }

      bool set_face_mode( const mode_t& mode )
      {
        if( mode == get_face_mode() ) return true;

        if( !is_face_mode_supported( mode ) )
        { std::cerr << "gl::SurfaceDrawable::set_face_mode\t|"
                    << "WARNING: requested face display mode \"" << mode <<"\""
                    << " not supported." << std::endl;
          m_face_mode = INVISIBLE_FACE_MODE;
          return false;
        }
        m_face_mode = mode;
        invalidate();
        return true;
      }

      const float& get_vertex_size() const
      { return m_vertex_size; }

      virtual void set_vertex_size( const float& size )
      {
        assert( size >= 0. );
        if( size == m_vertex_size )     return;
        m_vertex_size = size;
        invalidate();
      }

      const flat::location_ref_t&       get_global_scale()      const
      { return m_global_scale; }

      virtual void set_global_scale( const flat::location_ref_t& scale )
      { if( ( m_global_scale == scale ) == true ) return;
        m_global_scale = scale;
        invalidate();
      }

      template< typename ColorIt >
      void gl_draw_scaled_vertices( ColorIt col_it )    const;

  };

} // of gl::

template< typename ColorIt >
void gl::SurfaceDrawable::gl_draw_scaled_vertices( ColorIt col_it )     const
{
  glPushMatrix();
    Scale( m_global_scale );
    glBegin( GL_POINTS );
      for( auto vertex_its = m_surface->vertex_handles(); vertex_its.first != vertex_its.second; ++vertex_its.first )
      { Color( *col_it++ );
        Vertex( vertex_its.first->location() );
      }
    glEnd();
  glPopMatrix();
}
