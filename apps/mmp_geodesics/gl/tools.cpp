// tools.cpp
// Copyright (C) 2006-2013  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
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

#include "gl/tools.hpp"

#include "gl/wrap/vertex.hpp"

#include "gl/wrap/color.hpp"

using namespace uv::gl;

void uv::gl::PrintError( std::ostream& os )
{
  GLenum code = glGetError();

  if(code != GL_NO_ERROR)
    os << "gl::PrintError\t| "
       << " WARNING: an OpenGL error has occured."
       << " message: " << gluErrorString(code) << std::endl;

}

void uv::gl::DrawCoords( GLfloat size )
{
  //std::cerr<<"uv::gl::glDrawCoords\t|axis length "<<s<<std::endl;
  glBegin(GL_LINES);
  {
    Color ( 1.f , 0.f, 0.f );
    Vertex( 0.f , 0.f, 0.f );
    Vertex( size, 0.f, 0.f );

    Color ( 0.f, 1.f , 0.f );
    Vertex( 0.f, 0.f , 0.f );
    Vertex( 0.f, size, 0.f );

    Color ( 0.f, 0.f, 1.f );
    Vertex( 0.f, 0.f, 0.f );
    Vertex( 0.f, 0.f, size );
  }
  glEnd();
}
