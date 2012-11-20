/*  normal.hpp - Copyright Peter Urban 2012

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

# include <exception>
# include <boost/lexical_cast.hpp>

# include "utk/math/fixed_size/vector/array.hpp"
# include "utk/math/fixed_size/vector/operators.hpp" // operator/=
# include "utk/math/fixed_size/vector/length.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace vector
      {
	//---| normalize

	template<class T,size_t Size>
	interface< T, Size >& normalize( interface< T, Size >& o )
	{
	  const T len = length(o);

  	  if( len == 0 )
	    throw std::out_of_range( "zero vector can not be normalized" );

	  return o /= len;
	}

	//---| normal
	//-----normalized vector copy
	template< typename T, size_t Size >
	array< T, Size > normal( const interface< T, Size >& o )
	{
	  array< T, Size > res(o);
	  return normalize(res);
	}

      } // of vector::
    } // of fixed_size::
  } // of math::
} // of utk::
