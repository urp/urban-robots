//libuv - a visualization library
//Copyright (C) 2006  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

# pragma once

# include "gl/tools.hpp"

# include "gl/buffer_data.hpp"

# include "gl/wrap/tex_image.hpp"

# include "gl/wrap/texture_target.hpp"

namespace uv
{
  namespace gl
  {

    class Texture
    {

        Texture() = delete;

        Texture( const Texture& ) = delete;

      public:

        static constexpr GLenum not_active = 0;

      protected:

        //data_type m_data;

        std::string m_name;
        GLuint      m_gl_name;             // opengl handle identifying the texture
        GLenum      m_gl_unit;             // active opengl texture unit ()
        GLenum      m_gl_target;           // opengl texture target GL_TEXTURE_1D, GL_TEXTURE_2D ...
        GLenum      m_gl_format;           // pixel format for m_data
        GLenum      m_gl_internal_format;  // internal gl storage format request

        template< class T, size_t Dim, size_t Cmp>
        Texture( const std::string& name
               , const std::shared_ptr< buffer_data< T, Dim, Cmp > >& data
               , GLenum internal_format = base_internal_format< Cmp >::gl_int()
               , GLenum target = texture_target< Dim >::gl_enum()
               )
        : m_name( name )
        , m_gl_name()
        , m_gl_unit( not_active )
        , m_gl_target( target )
        , m_gl_format()
        , m_gl_internal_format( internal_format )
        {
          gl_upload( data, internal_format, target );
        }

      public:

        template< class T, size_t Dim, size_t Cmp>
        static std::shared_ptr< Texture > create_from_data( const std::string& name
                                                          , const std::shared_ptr< buffer_data< T, Dim, Cmp > >& data
                                                          , GLenum internal_format = base_internal_format< Cmp >::gl_int()
                                                          )
        {
          return std::shared_ptr< Texture >( new Texture( data, internal_format ) );
        }


        virtual ~Texture() { }

        // getters

        size_t num_dimensions() const
        {
          switch( gl_target() )
          {
            case GL_TEXTURE_1D: return 1; break;
            case GL_TEXTURE_2D: return 2; break;
            case GL_TEXTURE_3D: return 3; break;
          };

          assert( false );

          return 0;
        }

        const std::string&  name()              const   { return m_name; }

        const GLuint&       gl_name()           const   { return m_gl_name; }

        const GLenum&       gl_target()         const   { return m_gl_target; }

        const GLenum&       gl_internal_format()const   { return m_gl_internal_format; }

        const GLenum&       gl_texture_unit()   const   { return m_gl_unit; }

        // opengl wrappers

        template< typename T, size_t Dim, size_t Cmp >
        void gl_upload( const std::shared_ptr< buffer_data< T, Dim, Cmp > >& data
                      , GLenum internal_format = base_internal_format< Cmp >::gl_enum()
                      , GLenum target  = texture_target< Cmp >::gl_enum()
                      );


        void gl_delete()
        {
          std::cerr << "uv::gl::Texture::~Texture[" << name() << "]\t|removing texture" << std::endl;

          glDeleteTextures( 1, &m_gl_name );
        }

        void gl_activate_on( GLenum texture_unit )
        {
          std::cerr << "uv::gl::Texture[" << name() << "]::activate\t|unit " << gl_texture_unit() << std::endl;

          if( gl_texture_unit() != not_active )
            std::cerr << "uv::gl::Texture[" << name() << "]::activate\t| "
                      << "WARNING - texture already active on unit " << gl_texture_unit() << std::endl;

          m_gl_unit = texture_unit;

          glActiveTexture( gl_texture_unit() );

          glEnable( gl_target() );

          glBindTexture( gl_target(), gl_name() );
        }

        void gl_deactivate()
        {
          assert( gl_texture_unit() != not_active );

          std::cerr<<"uv::gl::Texture[" << name() << "]::deactivate\t| unit " << gl_texture_unit() << std::endl;

          glActiveTexture( gl_texture_unit() );

          glDisable( gl_target() );

          m_gl_unit = not_active;
        }

    };

    // TODO: TextureSetup - sets up all kinds of glTexParameteri

    // TODO: remove
    //glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT ) ;
    //glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT ) ;
    //glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT ) ;
    //glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ) ;
    //glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ) ;
    //glPrintError();


    template<class T, size_t Dim, size_t Cmp >
    void Texture::gl_upload( const std::shared_ptr< buffer_data< T, Dim, Cmp > >& data, GLenum internal_format, GLenum target )
    {
      assert( data );

      glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

      std::cerr << "uv::gl::Texture[" << name() << "]::gl_upload_data\t|"
                << " dimension " << data.num_components()
                << " value components " << data.num_components()
                << " data" << data.data().get()
                << std::endl;

      m_gl_target = target;

      glBindTexture( gl_target(), gl_name() );

      gl::TexImage( data, gl_target(), 0, internal_format );

      PrintError( std::cerr << "uv::gl::Texture[" << name() << "]::gl_upload_data\t| error checkpoint" << std::endl );

      std::cerr << "\t|complete" << std::endl;
    }

  }
}
