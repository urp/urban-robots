// get_string.hpp
// Copyright (C) 2013  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
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

# include "gl/headers.hpp"

# include <string>

namespace uv
{
  namespace gl
  {

    inline std::string GetString( GLenum name )
    {
      const GLubyte* gl_string = glGetString( name );

      if( not gl_string )
      {
        std::cerr << "gl::GetString\t| " << " ERROR: OpenGL could not provide string for <name> " << name << std::endl;

        return std::string();
      }

      return std::string( reinterpret_cast< const char* >( gl_string ) );
    }

  }// of gl::

} // of ::uv::
