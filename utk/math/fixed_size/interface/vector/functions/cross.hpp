/*  cross.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/interface/vector/array.hpp"
# include "utk/math/fixed_size/interface/vector/functions/dot.hpp"

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

	  //-----| cross product

	  template< class ValueType >
	  array< ValueType, 3 > cross( const interface< ValueType, 3 >& a, const interface< ValueType, 3 >& b )
	  {
	    array<ValueType,3> res;
	    res[0]= a[1] * b[2] - b[1] * a[2];
	    res[1]= a[2] * b[0] - b[2] * a[0];
	    res[2]= a[0] * b[1] - b[0] * a[1];
	    return res;
	  }

	  template<class ValueType>
	  array<ValueType,3> cross3( const interface<ValueType,3>& a, const interface<ValueType,3>& b, const interface<ValueType,3>& c)
	  { return b * dot( a, c ) - c * dot( a, b ); }


	} // of vector::
      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
