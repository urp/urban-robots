// normal.hpp
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
    //---| glNormal

    inline void Normal( GLfloat  x, GLfloat  y, GLfloat  z )  { glNormal3f( x, y, z ); }
    inline void Normal( GLdouble x, GLdouble y, GLdouble z )  { glNormal3d( x, y, z ); }

    inline void Normal( const utk::vecn< GLfloat , 3 >& n ) { glNormal3fv( n.ptr() ); }
    inline void Normal( const utk::vecn< GLdouble, 3 >& n ) { glNormal3dv( n.ptr() ); }

  }// of gl::

} // of ::uv::
