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

# include "gl/headers.hpp"

# include "gl/buffer_data.hpp"

namespace uv
{
  namespace gl
  {
    //---| glUniformMatrix

    // GLfloat 2
    void UniformMatrix( const buffer_data< GLfloat, 1, 4 >& data
                      , GLint  location, bool transpose = false
                      )
    {
      glUniformMatrix2fv( location, data.shape()[0], transpose, data.raw_data() );
    }

    // GLfloat 3
    void UniformMatrix( const buffer_data< GLfloat, 1, 9 >& data
                      , GLint  location, bool transpose = false
                      )
    {
      glUniformMatrix3fv( location, data.shape()[0], transpose, data.raw_data() );
    }

    // GLfloat 4
    void UniformMatrix( const buffer_data< GLfloat, 1, 16 >& data
                      , GLint  location, bool transpose = false
                      )
    {
      glUniformMatrix4fv( location, data.shape()[0], transpose, data.raw_data() );
    }


    //---| glUniform


    // GLfloat 1
    void Uniform( const buffer_data< GLfloat, 1, 1 >& data, GLint location )
    {
      glUniform1fv( location, data.shape()[0], data.raw_data() );
    }

    // GLfloat 2
    void Uniform( const buffer_data< GLfloat, 1, 2 >& data, GLint location )
    {
      glUniform2fv( location, data.shape()[0], data.raw_data() );
    }

    // GLfloat 3
    void Uniform( const buffer_data< GLfloat, 1, 3 >& data, GLint location )
    {
      glUniform3fv( location, data.shape()[0], data.raw_data() );
    }

    // GLfloat 4
    void Uniform( const buffer_data< GLfloat, 1, 4 >& data, GLint location )
    {
      glUniform4fv( location, data.shape()[0], data.raw_data() );
    }


    // GLint 1
    void Uniform( const buffer_data< GLint, 1, 1 >& data, GLint location )
    {
      glUniform1iv( location, data.shape()[0], data.raw_data() );
    }

    // GLint 2
    void Uniform( const buffer_data< GLint, 1, 2 >& data, GLint location )
    {
      glUniform2iv( location, data.shape()[0], data.raw_data() );
    }

    // GLint 3
    void Uniform( const buffer_data< GLint, 1, 3 >& data, GLint location )
    {
      glUniform3iv( location, data.shape()[0], data.raw_data() );
    }

    // GLint 4
    void Uniform( const buffer_data< GLint, 1, 4 >& data, GLint location )
    {
      glUniform4iv( location, data.shape()[0], data.raw_data() );
    }

  }// of gl::

} // of ::uv::
