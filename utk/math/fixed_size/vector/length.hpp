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

# include "utk/math/fixed_size/vector/dot.hpp"
# include "utk/math/fixed_size/vector/named_access.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace vector
      {
	//euklidian norm
	template< class T, size_t Size >
	T l2norm( const interface< T, Size >& v )
	{
	  return std::sqrt( dot(v,v) );
	}

	template< class T, size_t Size >
	T   length( const interface< T, Size >& v )
	{
	  return l2norm(v);
	}

	template< typename T >
	typename std::enable_if< std::is_fundamental< T >::value
			       &&std::is_arithmetic<T>::value
			       &&std::is_scalar<T>::value
			       , T >::type
	length( const interface< T, 2 >& v )
	{
	  return std::hypot( x( v ), y( v ) );
	}

	template< typename T >
	typename std::enable_if< std::is_fundamental< T >::value
			       &&std::is_arithmetic<T>::value
			       &&std::is_scalar<T>::value
			       , T >::type
	length( const interface< T, 3 >& v )
	{
	  return std::hypot( x( v ), std::hypot( y( v ), z( v ) ) );
	}

      } // of vector::
    } // of fixed_size::
  } // of math::
} // of utk::
