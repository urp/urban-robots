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

//#include "boost/filesystem.hpp"

# include <boost/filesystem/operations.hpp>
# include <boost/filesystem/fstream.hpp>

# include "gl/shader.hpp"

using namespace uv::gl;

//---| create_shader_from_source

std::shared_ptr< Shader > Shader::create_from_source( const std::string& shader_name
                                                    , shader_type        type
                                                    , const source_type& source_code
                                                    )
{
  return std::shared_ptr< Shader >( new Shader( shader_name, type, source_code ) );
}

//---| create_shader_from_file

std::shared_ptr< Shader > Shader::create_from_file( const std::string& shader_name
                                                  , const boost::filesystem::path& shader_path
                                                  )
{
  // open file

  assert( boost::filesystem::is_regular_file( shader_path ) );

  boost::filesystem::ifstream file( shader_path );

  file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

  if( !file )
  {
    std::cerr << "uv::gl::Context::create_shader_from_file\t| ERROR opening file " << shader_path << std::endl;
    return std::shared_ptr< Shader >();
  }

  // read header

  std::vector< const GLchar* > source;

  std::string token = "nothing";

  if( not ( file >> token and token == "//<type>" and file >> token ) )
  {
    std::cerr << "uv::gl::Context::create_shader_from_file\t|WARNING shader <type> specifier expected, got " << token << std::endl;
    return std::shared_ptr< Shader >();
  }

  shader_type type = UV_GL_UNDEFINED_SHADER;

  if( token == "vertex" )
    type = UV_GL_VERTEX_SHADER;
  else if( token == "fragment" )
    type = UV_GL_FRAGMENT_SHADER;
  else
    std::cerr << "uv::gl::Context::create_shader_from_file\t|WARNING shader type (vertex/fragment) expected, got " << token << std::endl;

  assert( type != UV_GL_UNDEFINED_SHADER );

  // read source

  token = "nothing";
  if( file >> token and token == "//<source>" )
  {
    std::cerr << "uv::gl::Context::create_shader_from_file\t|WARNING shader <source> specifier expected, got " << token << std::endl;
    return std::shared_ptr< Shader >();
  }

  std::clog << "uv::gl::Context::create_shader_from_file\t| reading source code..." << std::endl;

  while( std::getline( file, token ) )
    if( token.length() )
    {
      GLchar* line = std::strcpy( new GLchar[ token.length() +2 ], std::string( token += "\n" ).c_str() );
      source.push_back( line );
    }

  std::shared_ptr< Shader > shader = create_from_source( shader_name, type, source );

  assert( shader );

  std::clog << "uv::gl::Context::create_shader_from_file\t|loaded " << shader->source().size() << " code lines for shader " << shader->name() << std::endl;

  return shader;
}
