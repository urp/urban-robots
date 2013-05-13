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
# include "utk/inertial.h"

# include "gl/headers.hpp"

# include "gl/wrap/translate.hpp"
# include "gl/wrap/mult_matrix.hpp"

namespace uv
{
  namespace gl
  {

    template< typename T >
    inline void gl_apply_transform( const utk::inertial< T >& inertial )
    {
      std::clog << "uv::gl::gl_apply\t| " << inertial << std::endl;

      MultMatrix( inertial.get_mat4().ptr() );
    }

    template< typename T >
    inline void gl_apply_inverse_transform( const utk::inertial< T >& inertial )
    {
      std::clog << "uv::gl::InvTrafo\t| " << inertial << std::endl;

      utk::mata< T, 4 > mat4( inertial.get_inverse_mat3() );

      mat4(0,3) = mat4(1,3) = mat4(2,3) = mat4(3,0) = mat4(3,1) = mat4(3,2) = 0.;

      mat4(3,3) = 1.;

      MultMatrix( mat4 );

      Translate( -inertial.position() );
    }


    void PrintError( std::ostream& os = std::clog );

    // draws a coordinate system of size s x s x s
    void DrawCoords( GLfloat );

    //returns normal of a triangle given by points p1,p2,p3 which have to be in counter-clockwise order
    template<class T>
    utk::veca<T,3> ccw_normal( const utk::vecn<T,3>& p1,const utk::vecn<T,3>& p2,const utk::vecn<T,3>& p3 )
    {
      utk::veca<T,3>    v12n( p2 );
      utk::veca<T,3>  v23( p3 );
      v12n -= p1;
      v23  -= p2;
      v12n  = cross(v12n,v23);
      v12n.normalize();
      //DB_UV_GL_TOOLS_MSG("uv::gl::ccw_normal:\t|a "<<p1<<"\t|b "<<p2<<"\t|c "<<p3<<"\t|normal "<<v12n);
      return v12n;
    }


  }// of gl::

} // of ::uv::
