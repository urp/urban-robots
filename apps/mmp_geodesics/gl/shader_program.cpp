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

#include "gl/shader.hpp"

#include "gl/context.hpp"

// moved to Context


/*---| create_from_file

std::shared_ptr< ShaderProgram >  ShaderProgram::create_from_file( const boost::filesystem::path& program_name
                                                                         , std::ifstream& file
                                                                         , Context& context )
{
  // open file

  if( not file )
  {
    std::cerr << "uv::gl::Context::create_from_file\t| ERROR opening file " << token << std::endl;
    return std::shared_ptr< ShaderProgram >();
  }

  // read header

  std::shared_ptr< ShaderProgram > program( new ShaderProgram( program_name ) );

  std::vector< GLchar* > source;

  std::string token = "nothing";

  if( not ( file >> token && token == "//<shaders>" ) )
  {
    std::cerr << "uv::gl::Context::create_from_file\t| WARNING - program <shaders> specifier expected, got " << token << std::endl;
    return std::shared_ptr< ShaderProgram >();
  }

  // attach shaders

  while( file >> token )
  {
    const std::shared_ptr< Shader >&  shader = context.request_shader( token );

    assert( shader );

    program->attatch( shader );
  }

  return program;
}
*/
