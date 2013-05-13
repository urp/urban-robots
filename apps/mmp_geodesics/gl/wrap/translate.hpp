// translate.hpp
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

# pragma once

# include "utk/vecn.h"

# include "gl/headers.hpp"

namespace uv
{
  namespace gl
  {
    // glTranslate

    inline void Translate( GLfloat  x, GLfloat  y, GLfloat  z )
    {
      std::clog << "uv::gl::glTranslate:\t| GLfloat (" << x << ", " << y << ", " << z << ")" << std::endl;
      glTranslatef( x, y, z );
    }

    inline void Translate( GLdouble x, GLdouble y, GLdouble z )
    {
      std::clog << "uv::gl::glTranslate:\t| GLdouble (" << x << ", " << y << ", " << z << ")" << std::endl;
      glTranslated( x, y, z );
    }

    inline void Translate( const utk::vecn< GLfloat , 3 >& v )
    {
      std::clog << "uv::gl::glTranslate:\t| GLfloat " << v << std::endl;
      Translate( v.x(), v.y(), v.z() );
    }

    inline void Translate( const utk::vecn< GLdouble, 3 >& v )
    {
      std::clog << "uv::gl::glTranslate:\t| GLdouble " << v << std::endl;
      Translate( v.x(), v.y(), v.z() );
    }


  }// of gl::

} // of ::uv::
