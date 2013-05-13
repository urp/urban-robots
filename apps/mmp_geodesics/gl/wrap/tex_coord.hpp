// tex_coord.hpp
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
# include "utk/inertial.h"

# include "gl/headers.hpp"

namespace uv
{
  namespace gl
  {

    //---| glTexCoord

    // 1d
    inline void TexCoord( GLfloat  s ) { glTexCoord1f( s ); }
    inline void TexCoord( GLdouble s ) { glTexCoord1d( s ); }

    inline void TexCoord( const utk::vecn< GLfloat , 1 >& tc ) { glTexCoord1fv( tc.ptr() ); }
    inline void TexCoord( const utk::vecn< GLdouble, 1 >& tc ) { glTexCoord1dv( tc.ptr() ); }

    // 2d
    inline void TexCoord( GLfloat  s, GLfloat  t ) { glTexCoord2f( s, t ); }
    inline void TexCoord( GLdouble s, GLdouble t ) { glTexCoord2d( s, t ); }

    inline void TexCoord( const utk::vecn< GLfloat , 2 >& tc ) { glTexCoord2fv( tc.ptr() ); }
    inline void TexCoord( const utk::vecn< GLdouble, 2 >& tc ) { glTexCoord2dv( tc.ptr() ); }

  }// of gl::

} // of ::uv::
