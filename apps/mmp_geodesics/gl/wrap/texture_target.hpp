// texture_target.hpp
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

#pragma once

#include  "gl/headers.hpp"

namespace uv
{
  namespace gl
  {
    //---| texture_target

    template< size_t Components, bool Proxy = false >
    struct texture_target
    {
      //typedef     GLvoid    texture_target;
      //static const  GLenum    gl_enum = 0;
    };

    template< >
    struct texture_target< 1, false >
    {
      static constexpr GLenum gl_enum() { return GL_TEXTURE_1D; }
    };

    template< >
    struct texture_target< 1, true >
    {
      static constexpr GLenum gl_enum() { return GL_PROXY_TEXTURE_1D; }
    };


    template< >
    struct texture_target< 2, false >
    {
      static constexpr GLenum gl_enum() { return GL_TEXTURE_2D; }
    };

    template< >
    struct texture_target< 2, true >
    {
      static constexpr GLenum gl_enum() { return GL_PROXY_TEXTURE_2D; }
    };


    template< >
    struct texture_target< 3, false >
    {
      static constexpr GLenum gl_enum() { return GL_TEXTURE_3D; }
    };

    template< >
    struct texture_target< 3, true >
    {
      static constexpr GLenum gl_enum() { return GL_PROXY_TEXTURE_3D; }
    };


  }// of gl::

} // of ::uv::
