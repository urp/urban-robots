/*  ceil.hpp - Copyright Peter Urban 2012

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
# include <exception>
# include <boost/lexical_cast.hpp>

# include "utk/math/fixed_size/interface/vector/array.hpp"

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

	  template< class ValueType, size_t Size >
	  array< ValueType, Size > ceil( const interface< ValueType, Size >& v )
	  {
	    array< ValueType, Size > res;
	    std::transform( v.begin(), v.end(), res.begin(), []( const ValueType& x ){ return std::ceil( x ); } );
	    return res;
	  }

	} // of vector::
      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
