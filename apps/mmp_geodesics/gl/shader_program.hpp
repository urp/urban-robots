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

# include        "gl/headers.hpp"

# include        "gl/shader.hpp"

# include        <string>

namespace uv
{
  namespace gl
  {

    //class Context; // required to get m_linked shaders


    class ShaderProgram
    {

      public:

        typedef std::vector< std::shared_ptr< Shader > > shaders_t;

      private:

        shaders_t   m_shaders;
        std::string m_name;
        GLuint      m_gl_name;
        bool        m_linked;

        ShaderProgram() = delete;
        ShaderProgram( const ShaderProgram& ) = delete;

      protected:

        ShaderProgram( const std::string& name )
        : m_shaders(), m_name( name ), m_gl_name( glCreateProgram() ), m_linked( false )
        {
          assert(m_gl_name);
        }

      public:

        friend class Context;

        // std::shared_ptr< ShaderProgram >  ShaderProgram::create_from_file( const std::string& program_name, std::ifstream& file, Context& );

        ~ShaderProgram()
        {
          std::cerr << "uv::gl::ShaderProgram[" << name() << "]::~ShaderProgram" << std::endl;
        }

        //:::| getters

        const std::string name() const
        {
          return m_name;
        }

        const GLuint& gl_name() const
        {
          return m_gl_name;
        }

        bool is_linked() const
        {
          return m_linked;
        }


        //:::| opengl calls

        void gl_attatch( const std::shared_ptr< Shader >& shader )
        {
          assert( shader );

          if( not shader->is_compiled())
            shader->gl_compile();

          if( shader->is_compiled() )
          {
            glAttachShader( m_gl_name, shader->gl_name() );

            m_shaders.push_back( shader );
          }else
            std::cerr << "uv::gl::ShaderProgram[" << name() << "]::gl_attach\t|shader[" << shader->name() << "]\t|FAILED" << std::endl;
        }

        void gl_detatch( const std::shared_ptr< Shader >& shader )
        {
          glDetachShader( gl_name(), shader->gl_name() );

          auto it = std::find( m_shaders.begin(), m_shaders.end(), shader );

          assert( it != m_shaders.end() );

          it->reset();

          m_shaders.erase( it );
        }

        bool gl_link()
        {
          std::cerr << "uv::gl::ShaderProgram[" << name() << "]::gl_link";
          glLinkProgram( gl_name() );

          GLint success = false;
          glGetProgramiv( gl_name(), GL_LINK_STATUS, &success );
          m_linked = success;

          if( not is_linked() )
            std::cerr<<"\t| FAILED";
          else
            std::cerr << "\t| success";

          std::cerr << "\t| message :" << std::endl
                    << gl_log() << "\t|end" << std::endl;

          PrintError( std::cerr << "uv::gl::ShaderProgram[" << name() << "]::gl_link\t| error checkpoint" << std::endl );

          return is_linked();
        }

        bool gl_validate() const
        {
          std::cerr << "uv::gl::ShaderProgram[" << name() << "]::gl_validate\t| ";

          glValidateProgram( gl_name() );

          GLint success = false;
          glGetProgramiv( gl_name(), GL_VALIDATE_STATUS, &success );

          if( success )
          {
            std::cerr << "complete\t| info log:" << std::endl << gl_log();
            return true;
          }

          std::cerr << "FAILED\t| info log:" << std::endl << gl_log();
          return false;
        }


        const std::string gl_log() const
        {
          const size_t maxchar = 5000;

          char log[ maxchar ];

          glGetProgramInfoLog( gl_name(), maxchar, 0, log );

          return log;
        }


        void gl_activate()
        {
          if( not is_linked() ) gl_link();

          glUseProgram( gl_name() );
        }

        static void gl_deactivate()
        {
          glUseProgram( 0 );
        }

        void gl_delete()
        {
          std::cerr << "uv::gl::ShaderProgram[" << name() << "]::gl_delete\t| deleting shader " << gl_name() << std::endl;

          glDeleteProgram( gl_name() );
        }

        //:::| uniform definition

        //---| gl_uniform_matrix

        template< typename T, size_t Cmp >
        void gl_uniform_matrix( const utk::matn< T, Cmp >& data_iter
                              , const std::string& uniform_variable
                              , const size_t size = 1
                              , const bool transpose = false
                              ) const
        {
          GLint location = glGetUniformLocation( gl_name(), uniform_variable.c_str() );

          if( location == -1 )
          {
            std::cerr << "uv::gl::ShaderProgram[" << name() << "]::bind_uniform:\t| WARNING no location found for uniform " << uniform_variable << std::endl;
            return;
          }

          UniformMatrix( data_iter.ptr(), location, size, transpose );
        }

        //---| gl_uniform

        template< typename T, size_t Cmp >
        void gl_uniform( const buffer_data< T, 1, Cmp >& data_iter
                       , const std::string& uniform_variable
                       ) const
        {
          GLint location = glGetUniformLocation( gl_name(), uniform_variable.c_str() );

          if( location == -1 )
          {
            std::cerr << "uv::gl::ShaderProgram[" << name() << "]::bind_uniform:\t| WARNING no location found for uniform " << uniform_variable << std::endl;
            return;
          }

          Uniform( data_iter.ptr(), location );
        }

    }; // of ShaderProgram

  } // of gl::
} // of ::uv::
