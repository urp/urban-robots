/*  bla.h - Copyright Peter Urban 2012

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

# pragma once

# include "utk/math/fixed_size/square_matrix_interface.hpp"
# include "utk/math/fixed_size/square_matrix_array.hpp"
# include "utk/math/fixed_size/square_matrix_operators.hpp"
# include "utk/math/fixed_size/square_matrix_functions.hpp"

# pragma GCC visibility push(default)

namespace utk
{ 
  namespace math
  {
	namespace fixed_size
	{
	  
      //----| predefined square matrix types
  
      typedef mata<size_t,2>	mat2s;
      typedef mata<size_t,3>	mat3s;
      typedef mata<size_t,4>	mat4s;
      typedef mata<int,2>		mat2i;
      typedef mata<int,3>		mat3i;
      typedef mata<int,4>		mat4i;
      typedef mata<float,2>		mat2f;
      typedef mata<float,3>		mat3f;
      typedef mata<float,4>		mat4f;
      typedef mata<double,2>	mat2d;
      typedef mata<double,3>	mat3d;
      typedef mata<double,4>	mat4d;  
      
      typedef matn<size_t,2>	matn2s;
      typedef matn<size_t,3>	matn3s;
      typedef matn<size_t,4>	matn4s;
      typedef matn<int,2>		matn2i;
      typedef matn<int,3>		matn3i;
      typedef matn<int,4>		matn4i;
      typedef matn<float,2>		matn2f;
      typedef matn<float,3>		matn3f;
      typedef matn<float,4>		matn4f;
      typedef matn<double,2>	matn2d;
      typedef matn<double,3>	matn3d;
      typedef matn<double,4>	matn4d;

	} // of fixed_size::
  } // of math::
} // of utk::

#pragma GCC visibility pop
