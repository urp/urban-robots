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

# include <boost/filesystem/fstream.hpp>

#include "gl/context.hpp"

using namespace uv::gl;

boost::filesystem::path find_path( const std::vector< boost::filesystem::path >& directories, const std::string& name, const std::string& extension )
{
  using namespace boost::filesystem;

  // find file

  path file_name = path( name ).replace_extension( program_extension );

  for( auto directory : directories )
  {
    path try_path = directory / file_name;

    if( exists( try_path ) )
    {
      assert( not is_directory( try_path ) );
      return try_path;
    }
  }

  return path();
}


//---| find_program_path

boost::filesystem::path Context::find_program_path( const std::string& program_name )
{
  return find_path( m_program_paths, program_name, program_extension );
}


//---| find_shader_path

boost::filesystem::path Context::find_shader_path( const std::string& shader_name )
{
  return find_path( m_shader_paths, shader_name, shader_extension );
}

//---| request_program

std::shared_ptr< ShaderProgram > Context::request_program( const std::string& program_name )
{
  program_map::iterator it = m_programs.find( program_name );

  if( it != m_programs.end() )
  {
    DB_UV_GL_RESOURCES_MSG( "uv::gl::Context::request_program\t|found [" << program_name << "]" )
    return it->second;
  }

  // create new program from file ( requesting shaders from context )

  DB_UV_GL_RESOURCES_MSG( "uv::gl::Context::request_program\t|loading [" << program_name << "] from file" )

  const boost::filesystem::path program_path = find_program_path( program_name );

  if( not boost::filesystem::is_empty( program_path ) )
  {
    boost::filesystem::ifstream program_file( program_path );

    program_file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

    return m_programs[ program_name ] = create_program_from_file( program_name, program_file );
  }

  DB_UV_GL_RESOURCES_MSG( "uv::gl::Context::request_program\t| source file for program " << program_name << " not found" )

  return std::shared_ptr< ShaderProgram >();
}


//---| request_shader

std::shared_ptr< Shader > Context::request_shader( const std::string& shader_name )
{
  shader_map::iterator it = m_shaders.find( shader_name );

  if( it != m_shaders.end() )
  {
    DB_UV_GL_RESOURCES_MSG( "uv::gl::Context::request_shader\t|found [" << shader_name << "]" )
    return it->second;
  }

  // create new shader from file

  DB_UV_GL_RESOURCES_MSG( "uv::gl::Context::request_shader\t|loading [" << shader_name << "] from file" )

  const boost::filesystem::path shader_path = find_shader_path( shader_name );

  if( not boost::filesystem::is_empty( shader_path ) )
  {
    boost::filesystem::ifstream shader_file( shader_path );

    return m_shaders[ shader_name ] = Shader::create_from_file( shader_name, shader_path );
  }

  DB_UV_GL_RESOURCES_MSG( "uv::gl::Context::request_program\t| source file for shader " << shader_name << " not found" )

  return std::shared_ptr< Shader >();
}

//---| create_program_from_file

std::shared_ptr< ShaderProgram > Context::create_program_from_file( const std::string& program_name
                                                                  , std::ifstream& file
                                                                  )
{
  // open file

  if( not file )
  {
    std::cerr << "uv::gl::Context::create_program_from_file\t| ERROR opening file" << std::endl;
    return std::shared_ptr< ShaderProgram >();
  }

  // read header

  std::shared_ptr< ShaderProgram > program( new ShaderProgram( program_name ) );

  std::vector< GLchar* > source;

  std::string token = "nothing";

  if( not ( file >> token && token == "//<shaders>" ) )
  {
    std::cerr << "uv::gl::Context::create_program_from_file\t| WARNING - program <shaders> specifier expected, got " << token << std::endl;
    return std::shared_ptr< ShaderProgram >();
  }

  // attach shaders

  while( file >> token )
  {
    const std::shared_ptr< Shader >& shader = request_shader( token );

    assert( shader );

    program->gl_attatch( shader );
  }

  return program;
}
