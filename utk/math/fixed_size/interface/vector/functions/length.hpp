/*  length.hpp - Copyright Peter Urban 2012

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

# include <cmath>
# include <type_traits>

# include "utk/math/fixed_size/interface/vector/functions/dot.hpp"
# include "utk/math/fixed_size/interface/vector/functions/named_access.hpp"

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
	  //euklidian norm
	  template< class ValueType, size_t Size >
	  ValueType l2norm( const interface< ValueType, Size >& v )
	  {
	    return std::sqrt( dot(v,v) );
	  }

	  template< class ValueType, size_t Size >
	  ValueType   length( const interface< ValueType, Size >& v )
	  {
	    return l2norm(v);
	  }

	  template< typename ValueType >
	  typename std::enable_if< std::is_fundamental< ValueType >::value
				 &&std::is_arithmetic<ValueType>::value
				 &&std::is_scalar<ValueType>::value
				 , ValueType >::type
	  length( const interface< ValueType, 2 >& v )
	  {
	    return std::hypot( x( v ), y( v ) );
	  }

	  template< typename ValueType >
	  typename std::enable_if< std::is_fundamental< ValueType >::value
				 &&std::is_arithmetic<ValueType>::value
				 &&std::is_scalar<ValueType>::value
				 , ValueType >::type
	  length( const interface< ValueType, 3 >& v )
	  {
	    return std::hypot( x( v ), std::hypot( y( v ), z( v ) ) );
	  }

	} // of vector::
      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
