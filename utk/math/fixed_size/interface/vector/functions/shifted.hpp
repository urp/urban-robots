/*  shifted.hpp - Copyright Peter Urban 2012

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

	  template< ptrdiff_t N, size_t ResultSize, typename ValueType, size_type Size>
	  interface< ValueType, ResultSize > shifted( const interface< ValueType, Size >& v )
	  {
	    return interface< ValueType , ResultSize >( v.ptr() + N );
	  }

	} // of vector::
      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
