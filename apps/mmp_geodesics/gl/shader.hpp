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

# include <iostream>

# include <boost/filesystem.hpp>

# include "gl/tools.hpp"

namespace uv
{
  namespace gl
  {

    // wrapper for GLSL shaders
    class Shader
    {
      public:

        enum  shader_type { UV_GL_VERTEX_SHADER   = GL_VERTEX_SHADER
                          , UV_GL_FRAGMENT_SHADER = GL_FRAGMENT_SHADER
                          , UV_GL_UNDEFINED_SHADER
                          };

        typedef std::vector< const GLchar* >  source_type;


      private:

        shader_type m_type;
        std::string m_name;
        GLuint      m_gl_name;
        bool        m_compiled;
        source_type m_source;

        Shader() = delete;
        Shader( const Shader& ) = delete;

      protected:

        Shader(const std::string& name, shader_type type, const source_type& source_code = source_type() )
        : m_type( type ), m_name( name ), m_gl_name( 0 ), m_compiled( false ), m_source( )
        {
          switch( type )
          {
            case UV_GL_VERTEX_SHADER  : m_gl_name = glCreateShader( UV_GL_VERTEX_SHADER ); break;
            case UV_GL_FRAGMENT_SHADER: m_gl_name = glCreateShader(UV_GL_FRAGMENT_SHADER); break;
          }

          assert( gl_name() );

          if( not source().empty() ) set_source( source_code );
        }

      public:

        static std::shared_ptr< Shader > create_from_source( const std::string& shader_name
                                                           , shader_type        type
                                                           , const source_type& source_code
                                                           );

        static std::shared_ptr< Shader > create_from_file( const std::string&             shader_name
                                                         , const boost::filesystem::path& shader_path
                                                         );

        virtual ~Shader()
        {
          std::cerr << "uv::gl::Shader[" << name() << "]::~Shader" << std::endl;
        }

        //:::| getters

        const std::string& name() const
        {
          return m_name;
        }

        GLuint gl_name() const
        {
          return m_gl_name;
        }

        const shader_type& type() const
        {
          return m_type;
        }

        bool is_compiled() const
        {
          return m_compiled;
        }

        const source_type& source() const
        {
          return m_source;
        }

        void set_source( const source_type& new_source )
        {
          m_source = new_source;

          std::cerr << "uv::gl::Shader[" << name() << "]::set_sourcecode:\t|lines "  << source().size() << std::endl;

          glShaderSource( gl_name(), source().size(), static_cast< const GLchar** >( m_source.data() ), 0 );
        }

        void print_source() const
        {
          std::cerr << "uv::gl::Shader[" << name() << "]::print_sourcecode:\t|..." << std::endl;

          for( auto line : source() )
            std::cerr /* <<std::distance( &source()[0], &line ) */<< "\t|" << *line;
        }


        //:::| opengl operations

        bool gl_compile()
        {
          std::cerr << "uv::gl::Shader[" << name() << "]::gl_compile:\t| ..." << std::endl;

          assert( not source().empty() );

          glCompileShader( gl_name() );

          GLint success;
          glGetShaderiv( gl_name(), GL_COMPILE_STATUS, &success );

          m_compiled = success;

          if( not is_compiled() )
          {
            print_source();
            std::cerr << "uv::gl::Shader[" << name() << "]::gl_compile:\t| FAILED";
          }
          else
            std::clog << "uv::gl::Shader[" << name() << "]::gl_compile:\t| success";

          std::clog << " message :" << std::endl << gl_log() << std::endl;

          PrintError( std::clog << "uv::gl::Shader[" << name() << "]::gl_compile\t| error checkpoint" << std::endl );

          return is_compiled();
        }

        void gl_delete()
        {
          glDeleteShader( m_gl_name );

          m_compiled = false;
        }

        const std::string gl_log() const
        {
          static constexpr size_t maxchar = 5000;

          GLchar log[ maxchar ];

          glGetShaderInfoLog( m_gl_name, maxchar, 0, log );

          return log;
        }

    };

  } // of gl::
} // of ::uv::
