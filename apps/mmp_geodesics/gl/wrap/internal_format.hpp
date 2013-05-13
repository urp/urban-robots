// internal_format.hpp
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

namespace uv
{
  namespace gl
  {
    //---| base_internal_format

    template< size_t Components, bool DepthTexture = false >
    struct base_internal_format
    {
      //static constexpr GLint gl_int();
    };

    template< >
    struct base_internal_format< 1, false >
    {
      static constexpr GLint gl_int() { return GL_RED; }
    };

    template< >
    struct base_internal_format< 1, true >
    {
      static constexpr GLint gl_int() { return GL_DEPTH_COMPONENT; }
    };


    template< >
    struct base_internal_format< 2, false >
    {
      static constexpr GLint gl_int() { return GL_RG; }
    };

    template< >
    struct base_internal_format< 2, true >
    {
      static constexpr GLint gl_int() { return GL_DEPTH_STENCIL; }
    };

    template< >
    struct base_internal_format< 3, false >
    {
      static constexpr GLint gl_int() { return GL_RGB; }
    };

    template< >
    struct base_internal_format< 4, false >
    {
      static constexpr GLint gl_int() { return GL_RGBA; }
    };


    //---| sized_internal_format

    typedef enum  { UNSIGNED_NORMALIZED
                  , SIGNED_NORMALIZED
                  , UNSIGNED_INTEGRAL
                  , SIGNED_INTEGRAL
                  , FLOATING_POINT
                  } format_type;

    template< GLint Base, size_t Size, format_type type = UNSIGNED_NORMALIZED >
    struct sized_internal_format
    {
      //static constexpr GLint gl_int();
    };

    // GL_RED

    // 8 bit

    template< >
    struct sized_internal_format< GL_RED, 8, UNSIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_R8; }
    };

    template< >
    struct sized_internal_format< GL_RED, 8, SIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_R8_SNORM; }
    };

    template< >
    struct sized_internal_format< GL_RED, 8, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_R8UI; }
    };

    template< >
    struct sized_internal_format< GL_RED, 8, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_R8I; }
    };

    template< >
    struct sized_internal_format< GL_RED, 8, FLOATING_POINT >
    {
      //static constexpr GLint gl_int() { return GL_R8F; }
    };

    // 16 bit

    template< >
    struct sized_internal_format< GL_RED, 16, UNSIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_R16; }
    };

    template< >
    struct sized_internal_format< GL_RED, 16, SIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_R16_SNORM; }
    };

    template< >
    struct sized_internal_format< GL_RED, 16, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_R16UI; }
    };

    template< >
    struct sized_internal_format< GL_RED, 16, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_R16I; }
    };

    template< >
    struct sized_internal_format< GL_RED, 16, FLOATING_POINT >
    {
      static constexpr GLint gl_int() { return GL_R16F; }
    };

    // 32 bit

    template< >
    struct sized_internal_format< GL_RED, 32, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_R32UI; }
    };

    template< >
    struct sized_internal_format< GL_RED, 32, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_R32I; }
    };

    template< >
    struct sized_internal_format< GL_RED, 32, FLOATING_POINT >
    {
      static constexpr GLint gl_int() { return GL_R32F; }
    };

    // GL_RG

    // 8 bit

    template< >
    struct sized_internal_format< GL_RG, 8, UNSIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RG8; }
    };

    template< >
    struct sized_internal_format< GL_RG, 8, SIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RG8_SNORM; }
    };

    template< >
    struct sized_internal_format< GL_RG, 8, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RG8UI; }
    };

    template< >
    struct sized_internal_format< GL_RG, 8, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RG8I; }
    };

    template< >
    struct sized_internal_format< GL_RG, 8, FLOATING_POINT >
    {
      //static constexpr GLint gl_int() { return GL_RG8F; }
    };

    // 16 bit

    template< >
    struct sized_internal_format< GL_RG, 16, UNSIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RG16; }
    };

    template< >
    struct sized_internal_format< GL_RG, 16, SIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RG16_SNORM; }
    };

    template< >
    struct sized_internal_format< GL_RG, 16, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RG16UI; }
    };

    template< >
    struct sized_internal_format< GL_RG, 16, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RG16I; }
    };

    template< >
    struct sized_internal_format< GL_RG, 16, FLOATING_POINT >
    {
      static constexpr GLint gl_int() { return GL_RG16F; }
    };

    // 32 bit

    template< >
    struct sized_internal_format< GL_RG, 32, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RG32UI; }
    };

    template< >
    struct sized_internal_format< GL_RG, 32, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RG32I; }
    };

    template< >
    struct sized_internal_format< GL_RG, 32, FLOATING_POINT >
    {
      static constexpr GLint gl_int() { return GL_RG32F; }
    };

    // GL_RGB

    // 8 bit

    template< >
    struct sized_internal_format< GL_RGB, 8, UNSIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RGB8; }
    };

    template< >
    struct sized_internal_format< GL_RGB, 8, SIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RGB8_SNORM; }
    };

    template< >
    struct sized_internal_format< GL_RGB, 8, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGB8UI; }
    };

    template< >
    struct sized_internal_format< GL_RGB, 8, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGB8I; }
    };

    template< >
    struct sized_internal_format< GL_RGB, 8, FLOATING_POINT >
    {
      //static constexpr GLint gl_int() { return GL_RGB8F; }
    };

    // 16 bit

    template< >
    struct sized_internal_format< GL_RGB, 16, UNSIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RGB16; }
    };

    template< >
    struct sized_internal_format< GL_RGB, 16, SIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RGB16_SNORM; }
    };

    template< >
    struct sized_internal_format< GL_RGB, 16, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGB16UI; }
    };

    template< >
    struct sized_internal_format< GL_RGB, 16, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGB16I; }
    };

    template< >
    struct sized_internal_format< GL_RGB, 16, FLOATING_POINT >
    {
      static constexpr GLint gl_int() { return GL_RGB16F; }
    };

    // 32 bit

    template< >
    struct sized_internal_format< GL_RGB, 32, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGB32UI; }
    };

    template< >
    struct sized_internal_format< GL_RGB, 32, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGB32I; }
    };

    template< >
    struct sized_internal_format< GL_RGB, 32, FLOATING_POINT >
    {
      static constexpr GLint gl_int() { return GL_RGB32F; }
    };

    // GL_RGBA

    // 8 bit

    template< >
    struct sized_internal_format< GL_RGBA, 8, UNSIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RGBA8; }
    };

    template< >
    struct sized_internal_format< GL_RGBA, 8, SIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RGBA8_SNORM; }
    };

    template< >
    struct sized_internal_format< GL_RGBA, 8, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGBA8UI; }
    };

    template< >
    struct sized_internal_format< GL_RGBA, 8, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGBA8I; }
    };

    template< >
    struct sized_internal_format< GL_RGBA, 8, FLOATING_POINT >
    {
      //static constexpr GLint gl_int() { return GL_RGBA8F; }
    };

    // 16 bit

    template< >
    struct sized_internal_format< GL_RGBA, 16, UNSIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RGBA16; }
    };

    template< >
    struct sized_internal_format< GL_RGBA, 16, SIGNED_NORMALIZED >
    {
      static constexpr GLint gl_int() { return GL_RGBA16_SNORM; }
    };

    template< >
    struct sized_internal_format< GL_RGBA, 16, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGBA16UI; }
    };

    template< >
    struct sized_internal_format< GL_RGBA, 16, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGBA16I; }
    };

    template< >
    struct sized_internal_format< GL_RGBA, 16, FLOATING_POINT >
    {
      static constexpr GLint gl_int() { return GL_RGBA16F; }
    };

    // 32 bit

    template< >
    struct sized_internal_format< GL_RGBA, 32, UNSIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGBA32UI; }
    };

    template< >
    struct sized_internal_format< GL_RGBA, 32, SIGNED_INTEGRAL >
    {
      static constexpr GLint gl_int() { return GL_RGBA32I; }
    };

    template< >
    struct sized_internal_format< GL_RGBA, 32, FLOATING_POINT >
    {
      static constexpr GLint gl_int() { return GL_RGBA32F; }
    };



  }// of gl::

} // of ::uv::
