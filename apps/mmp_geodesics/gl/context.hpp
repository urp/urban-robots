//gl_context.hpp
//Copyright (C) 2006-2013  Peter Urban (urpeter@gmx.net)
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

#pragma once

#define DB_UV_GL_RESOURCES
#ifdef          DB_UV_GL_RESOURCES
#  define       DB_UV_GL_RESOURCES_MSG(msg)       std::cerr << msg << std::endl;
#else
#  define       DB_UV_GL_RESOURCES_MSG(msg)       {     }
#endif

# include <unordered_map>
# include <string>
# include <cstring>

# include <boost/filesystem/path.hpp>

# include "gl/wrap/get_string.hpp"
# include "gl/texture.hpp"
# include "gl/shader.hpp"
# include "gl/shader_program.hpp"

namespace uv
{
  namespace gl
  {

    struct ContextInfo
    {
      std::string vendor;
      std::string renderer;
      std::string version;
      std::string sl_version;
      std::string extensions;
      GLint       max_texture_units;
      GLint       max_texture_size;

      ContextInfo()
      {
        refresh();
      }

      void refresh()
      {
        vendor        = GetString( GL_VENDOR );
        renderer      = GetString( GL_RENDERER );
        version       = GetString( GL_VERSION );
        sl_version    = GetString( GL_SHADING_LANGUAGE_VERSION );
        extensions    = GetString( GL_EXTENSIONS );

        // TODO: use wrapped version
        glGetIntegerv( GL_MAX_TEXTURE_UNITS, &max_texture_units );
        glGetIntegerv( GL_MAX_TEXTURE_SIZE,  &max_texture_size  );
      }

      void print() const
      {
        std::cout << "uv::gl::Context::Info::print\t|..." << std::endl
                  << "\t|vendor\t\t\t" << vendor << std::endl
                  << "\t|render\t\t\t" << renderer << std::endl
                  << "\t|version\t\t\t" << version << std::endl
                  << "\t|shading language version\t" << sl_version << std::endl
                  << "\t|max texture units\t\t" << max_texture_units << std::endl
                  << "\t|max texture size\t\t" << max_texture_size << std::endl;

      }
    };

    //forward
    static const char program_extension[] = "slp";
    static const char shader_extension[]  = "sls";

    class Context
    {
      public:

        typedef std::shared_ptr< ShaderProgram >                 program_value;
        typedef std::unordered_map< std::string, program_value > program_map;

        typedef std::shared_ptr< Shader >                       shader_value;
        typedef std::unordered_map< std::string, shader_value > shader_map;


        typedef std::shared_ptr< Texture  >                      texture_value;
        typedef std::unordered_map< std::string, texture_value > texture_map;

      private:

        typedef std::vector< boost::filesystem::path > search_paths;

        search_paths m_program_paths;
        search_paths m_shader_paths;

        program_map  m_programs;
        shader_map   m_shaders;
        texture_map  m_textures;

        boost::filesystem::path find_shader_path( const std::string& shader_name );
        boost::filesystem::path find_program_path( const std::string& program_name );

      public:

        Context( //const boost::filesystem::path& program_path = boost::filesystem::current_path()
               //, const boost::filesystem::path& shader_path = boost::filesystem::current_path()
               )
        : m_program_paths(), m_shader_paths(), m_programs(), m_shaders(), m_textures()
        {
          //add_program_search_path( program_path );
          //add_shader_search_path( shader_path );
        }

        Context( const Context& shared )
        : m_program_paths( shared.program_search_paths() )
        , m_shader_paths( shared.shader_search_paths() )
        , m_programs( shared.m_programs )
        , m_shaders( shared.m_shaders )
        , m_textures( shared.m_textures )
        {
        }


        virtual ~Context()
        {
          std::clog<<"uv::gl::Context::~Context"<<std::endl;
        }

        //:::| Context Information

        virtual bool is_current() = 0;

        const std::shared_ptr< ContextInfo > gl_info() const
        {
          return std::shared_ptr< ContextInfo >( new ContextInfo() );
        }

        //:::| Resource API

        std::shared_ptr< ShaderProgram > create_program_from_file( const std::string& program_name
                                                                 , std::ifstream& file
                                                                 );


        std::shared_ptr< Shader > request_shader( const std::string& name );

        std::shared_ptr< ShaderProgram > request_program( const std::string& name );

        template< class T, size_t Dim, size_t Cmp >
        const std::shared_ptr< Texture >& request_texture( const std::string& name
                                                         , const std::shared_ptr< buffer_data< T, Dim, Cmp > >& data
                                                         , GLenum internal_format = base_internal_format< Cmp >::gl_int()
                                                         , GLenum target = texture_target< Dim >::gl_enum()
                                                         );


        const search_paths& program_search_paths() const { return m_program_paths; }

        void  add_program_search_path( const boost::filesystem::path& program_dir )
        {
          assert( boost::filesystem::is_directory( program_dir ) );

          m_program_paths.push_back( program_dir );
        }

        const search_paths& shader_search_paths() const { return m_shader_paths; }

        void add_shader_search_path( const boost::filesystem::path& shader_dir )
        {
          assert( boost::filesystem::is_directory( shader_dir ) );

          m_shader_paths.push_back( shader_dir );
        }

    };

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::| implementation |:::::::::::::::::::::::::::::::::::::::::::::


    //---| request texture

    template< class T, size_t Dim, size_t Cmp >
    const std::shared_ptr< Texture >& Context::request_texture( const std::string& name
                                                              , const std::shared_ptr< buffer_data< T, Dim, Cmp > >& data
                                                              , GLenum internal_format
                                                              , GLenum target
                                                              )
    {
      //std::cerr<<"uv::gl::Context::request_texture\t|dim "<<Dim<<"\t|components "<<Cnt<<std::endl;

      texture_map::iterator it = m_textures.find( name );
      {
        if( it != m_textures.end() )
        {
          DB_UV_GL_RESOURCES_MSG( "uv::gl::Context::request_texture\t| texture["  << name << "] found" )
          return it->second;
        }
      }

      DB_UV_GL_RESOURCES_MSG( "uv::gl::Context::request_texture\t|creating new texture for data [" << name << "]" )

      auto new_texture = m_textures[ name ] = Texture::create_from_data( data, internal_format, target );

      return new_texture;
    }

  } // of gl::
} // of ::uv::
