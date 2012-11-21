/*  floor.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/vector/array.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace vector
      {

	template< class T, size_t Size >
	array< T, Size > floor( const interface< T, Size >& v )
	{
	  array< T, Size > res;
	  std::transform( v.begin(), v.end(), res.begin()
			, []( const T& x ){ return std::floor( x ); }
			);
	  return res;
	}

      } // of vector::
    } // of fixed_size::
  } // of math::
} // of utk::
