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

# include "vector_interface.hpp"
# include "vector_array.hpp"

# include "vector_operators.hpp"
# include "vector_functions.hpp"

namespace utk
{
  namespace math
  {
	namespace fixed_size
	{
    
      //---| predifined vector types
      
      typedef	vector_array<bool,1>		vec1b;
      typedef	vector_array<bool,2>		vec2b;
      typedef	vector_array<bool,3>		vec3b;
      typedef	vector_array<bool,4>		vec4b;
      typedef	vector_array<size_t,1>	vec1s;
      typedef	vector_array<size_t,2>	vec2s;
      typedef	vector_array<size_t,3>	vec3s;
      typedef	vector_array<size_t,4>	vec4s;
      typedef	vector_array<int,1>		vec1i;
      typedef	vector_array<int,2>		vec2i;
      typedef	vector_array<int,3>		vec3i;
      typedef	vector_array<int,4>		vec4i;
      typedef	vector_array<float,1>		vec1f;
      typedef	vector_array<float,2>		vec2f;
      typedef	vector_array<float,3>		vec3f;
      typedef	vector_array<float,4>		vec4f;
      typedef	vector_array<double,1>	vec1d;
      typedef	vector_array<double,2>	vec2d;
      typedef	vector_array<double,3>	vec3d;
      typedef	vector_array<double,4>	vec4d;
  
      typedef	vector_interface<bool,1>		vecn1b;
      typedef	vector_interface<bool,2>		vecn2b;
      typedef	vector_interface<bool,3>		vecn3b;
      typedef	vector_interface<bool,4>		vecn4b;
      typedef	vector_interface<size_t,1>	vecn1s;
      typedef	vector_interface<size_t,2>	vecn2s;
      typedef	vector_interface<size_t,3>	vecn3s;
      typedef	vector_interface<size_t,4>	vecn4s;
      typedef	vector_interface<int,1>		vecn1i;
      typedef	vector_interface<int,2>		vecn2i;
      typedef	vector_interface<int,3>		vecn3i;
      typedef	vector_interface<int,4>		vecn4i;
      typedef	vector_interface<float,1>	vecn1f;
      typedef	vector_interface<float,2>	vecn2f;
      typedef	vector_interface<float,3>	vecn3f;
      typedef	vector_interface<float,4>	vecn4f;
      typedef	vector_interface<double,1>	vecn1d;
      typedef	vector_interface<double,2>	vecn2d;
      typedef	vector_interface<double,3>	vecn3d;
      typedef	vector_interface<double,4>	vecn4d;

	} // of fixed_size::
  } // of math::
} // of utk::
