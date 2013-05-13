/***************************************************************************
 *            gl_render_targets.hpp
 *
  *  Copyright  2011-2013 Peter Urban
 *  <urp@pks.mpg.de>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

# pragma once

# define DBG_UV_GL_RENDER_TARGET

# include "gl/headers.hpp"

namespace uv
{
  namespace gl
  {
    class RenderTarget
    {

      protected:

        RenderTarget() { }

      public:

        virtual bool gl_begin_context() = 0;

        virtual void gl_end_context() = 0;

        virtual void gl_flush() = 0;

        virtual bool is_gl_context_valid() = 0;

        virtual bool configure( const size_t width, const size_t height) = 0;

        //virtual uv::gl::Context >& gl_context() = 0;

        //virtual const uv::gl::Context >& gl_context() const = 0;
    };
  } // of gl::
} // of ::uv::
