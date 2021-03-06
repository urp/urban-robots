// tools.hpp
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
    //---| glVertex

    inline void Vertex( GLfloat  x, GLfloat  y, GLfloat  z )
    {
      glVertex3f( x, y, z );
    }

    inline void Vertex( GLdouble x, GLdouble y, GLdouble z )
    {
      glVertex3d( x, y, z );
    }


    inline void Vertex( const utk::vecn< GLfloat , 3 >& v)
    {
      glVertex3fv( v.ptr() );
    }

    inline void Vertex( const utk::vecn< GLdouble, 3 >& v)
    {
      glVertex3dv( v.ptr() );
    }

  }// of gl::

} // of ::uv::
