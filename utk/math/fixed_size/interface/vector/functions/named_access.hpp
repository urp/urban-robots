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

# include "utk/math/fixed_size/interface/vector/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {
	namespace vector
	{

	  //x
	  template< typename ValueType, size_t Size>
	  ValueType& 		x( interface<ValueType,Size>& v )      			{ return v[0]; }

	  template< typename ValueType, size_t Size>
	  const ValueType&	x( const interface<ValueType,Size>& v ) 		{ return v[0]; }

	  //y
	  template< typename ValueType, size_t Size>
	  ValueType&		y(interface<ValueType,Size>& v) 	    		{ return v[1]; }

	  template< typename ValueType, size_t Size>
	  const ValueType&	y(const interface<ValueType,Size>& v)   		{ return v[1]; }

	  //z
	  template< typename ValueType, size_t Size>
	  ValueType&	        z(interface<ValueType,Size>& v) 			{ return v[2]; }

	  template< typename ValueType, size_t Size>
	  const ValueType&	z(const interface<ValueType,Size>& v)   		{ return v[2]; }

	  //w
	  template< typename ValueType, size_t Size>
	  ValueType&	        w(interface<ValueType,Size>& v) 			{ return v[3]; }

	  template< typename ValueType, size_t Size>
	  const ValueType&	w(const interface<ValueType,Size>& v)  		 	{ return v[3]; }

	  //xy
	  template< typename ValueType, size_t Size >
	  interface<ValueType,2>		xy(interface<ValueType,Size>& v)		{ return interface<ValueType,2>(v); }

	  template< typename ValueType, size_t Size>
	  const interface<ValueType,2>	xy(const interface<ValueType,Size>& v) 		{ return interface<ValueType,2>(v); }

	  //xyz
	  template< typename ValueType, size_t Size>
	  interface<ValueType,3>		xyz(interface<ValueType,Size>& v)		{ return interface<ValueType,3>(v); }

	  template< typename ValueType, size_t Size>
	  const interface<ValueType,3>	xyz(const interface<ValueType,Size>& v) 	{ return interface<ValueType,3>(v); }

	} // of vector::
      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
