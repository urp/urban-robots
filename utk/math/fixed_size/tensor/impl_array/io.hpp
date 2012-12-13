/*  io.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/tensor/impl_interface/io.hpp"

# include "utk/math/fixed_size/tensor/impl_array/array.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace tensor
      {

	template< typename ValueType, typename Layout >
	std::ostream& operator<< ( std::ostream& os, const array< ValueType, Layout >& t )
	{
	  // header
	  os << "fixed_size::tensor::array\t|" << std::endl
	     << "  array " << t.array_data() << std::endl
	     << "  interface " << static_cast< const interface< ValueType, Layout >& >(t) << std::endl;
	  // content
	  return os << std::endl;
	}

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
