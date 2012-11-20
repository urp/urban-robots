/*  named_access.hpp - Copyright Peter Urban 2012

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

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace vector
      {

	//x
	template< typename T, size_t Size>
	T& 		x( interface<T,Size>& v )      			{ return v[0]; }

	template< typename T, size_t Size>
	const T&	x( const interface<T,Size>& v ) 		{ return v[0]; }

	//y
	template< typename T, size_t Size>
	T&		y(interface<T,Size>& v) 	    		{ return v[1]; }

	template< typename T, size_t Size>
	const T&	y(const interface<T,Size>& v)   		{ return v[1]; }

	//z
	template< typename T, size_t Size>
	T&	        z(interface<T,Size>& v) 			{ return v[2]; }

	template< typename T, size_t Size>
	const T&	z(const interface<T,Size>& v)   		{ return v[2]; }

	//w
	template< typename T, size_t Size>
	T&	        w(interface<T,Size>& v) 			{ return v[3]; }

	template< typename T, size_t Size>
	const T&	w(const interface<T,Size>& v)  		 	{ return v[3]; }

	//xy
	template< typename T, size_t Size >
	interface<T,2>		xy(interface<T,Size>& v)		{ return interface<T,2>(v); }

	template< typename T, size_t Size>
	const interface<T,2>	xy(const interface<T,Size>& v) 		{ return interface<T,2>(v); }

	//xyz
	template< typename T, size_t Size>
	interface<T,3>		xyz(interface<T,Size>& v)		{ return interface<T,3>(v); }

	template< typename T, size_t Size>
	const interface<T,3>	xyz(const interface<T,Size>& v) 	{ return interface<T,3>(v); }

      } // of vector::
    } // of fixed_size::
  } // of math::
} // of utk::
