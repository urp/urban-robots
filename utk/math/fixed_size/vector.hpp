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

# include "utk/math/fixed_size/vector/interface.hpp"
# include "utk/math/fixed_size/vector/array.hpp"
# include "utk/math/fixed_size/vector/operators.hpp"
# include "utk/math/fixed_size/vector/functions.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace vector
      {
        //---| predifined vector types

        typedef	array<bool,1>		vec1b;
        typedef	array<bool,2>		vec2b;
        typedef	array<bool,3>		vec3b;
        typedef	array<bool,4>		vec4b;
        typedef	array<size_t,1>	vec1s;
        typedef	array<size_t,2>	vec2s;
        typedef	array<size_t,3>	vec3s;
        typedef	array<size_t,4>	vec4s;
        typedef	array<int,1>		vec1i;
        typedef	array<int,2>		vec2i;
        typedef	array<int,3>		vec3i;
        typedef	array<int,4>		vec4i;
        typedef	array<float,1>		vec1f;
        typedef	array<float,2>		vec2f;
        typedef	array<float,3>		vec3f;
        typedef	array<float,4>		vec4f;
        typedef	array<double,1>	vec1d;
        typedef	array<double,2>	vec2d;
        typedef	array<double,3>	vec3d;
        typedef	array<double,4>	vec4d;

        typedef	interface<bool,1>		vecn1b;
        typedef	interface<bool,2>		vecn2b;
        typedef	interface<bool,3>		vecn3b;
        typedef	interface<bool,4>		vecn4b;
        typedef	interface<size_t,1>	vecn1s;
        typedef	interface<size_t,2>	vecn2s;
        typedef	interface<size_t,3>	vecn3s;
        typedef	interface<size_t,4>	vecn4s;
        typedef	interface<int,1>		vecn1i;
        typedef	interface<int,2>		vecn2i;
        typedef	interface<int,3>		vecn3i;
        typedef	interface<int,4>		vecn4i;
        typedef	interface<float,1>	vecn1f;
        typedef	interface<float,2>	vecn2f;
        typedef	interface<float,3>	vecn3f;
        typedef	interface<float,4>	vecn4f;
        typedef	interface<double,1>	vecn1d;
        typedef	interface<double,2>	vecn2d;
        typedef	interface<double,3>	vecn3d;
        typedef	interface<double,4>	vecn4d;
      } // of vector::
    } // of fixed_size::
  } // of math::
} // of utk::
