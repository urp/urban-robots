
// flatter - gl_tools.h
// Copyright (C) 2006-2011  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
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

#pragma once

#include  "gl/headers.hpp"

#include  "gl/buffer_data.hpp"

#include  "gl/wrap/gl_type.hpp"

#include  "gl/wrap/pixel_format.hpp"

#include  "gl/wrap/internal_format.hpp"

#include  <limits>

namespace uv
{
  namespace gl
  {
    //---| TexImage

    // 1d
    template< typename T, size_t Cmp >
    inline void TexImage( const buffer_data< T, 1, Cmp >& data
                        , const GLenum internal_target       = GL_TEXTURE_1D
                        , const GLint  internal_mipmap_level = 0
                        , const GLint  internal_format       = base_internal_format< Cmp >::gl_int()
                        )
    {
      glTexImage1D( internal_target
                  , internal_mipmap_level
                  , internal_format
                  , data.shape()[0]
                  , 0 // data_border
                  , pixel_format< Cmp >::gl_enum()
                  , gl_type< T >::gl_enum()
                  , static_cast< const GLvoid* >( data )
                  );
    }

    // 2d
    template< typename T, size_t Cmp >
    inline void TexImage( const buffer_data< T, 2, Cmp > data
                        , const GLenum internal_target       = GL_TEXTURE_2D
                        , const GLint  internal_mipmap_level = 0
                        , const GLint  internal_format       = base_internal_format< Cmp >::gl_int()
                        )
    {
      glTexImage2D( internal_target
                  , internal_mipmap_level
                  , internal_format
                  , data.shape()[0]
                  , data.shape()[1]
                  , 0 // data_border
                  , pixel_format< Cmp >::gl_enum()
                  , gl_type< T >::gl_enum()
                  , static_cast< const GLvoid* >( data.raw_data() )
                  );
    }

    // 3d
    template< typename T, size_t Cmp >
    inline void TexImage( const buffer_data< T, 3, Cmp > data
                        , const GLenum internal_target       = GL_TEXTURE_3D
                        , const GLint  internal_mipmap_level = 0
                        , const GLint  internal_format       = base_internal_format< Cmp >::gl_enum()
                        )
    {
      glTexImage3D( internal_target
                  , internal_mipmap_level
                  , internal_format
                  , data.shape()[0]
                  , data.shape()[1]
                  , data.shape()[2]
                  , 0 // data_border
                  , pixel_format< Cmp >::gl_enum()
                  , gl_type< T >::gl_enum()
                  , static_cast< const GLvoid* >( data.raw_data() )
                  );
    }

  }// of gl::

} // of ::uv::
