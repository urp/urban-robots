/*  array.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_interface/interface.hpp"
# include "utk/math/fixed_size/vector/array.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {

	template < typename T, typename Layout >
	struct array
	: public interface< T, Layout >
	{
	  typedef interface < T, Layout > interface;

	  typedef vector::array< T, interface::layout::total_size > storage_array;

	  //---| data storage

	  storage_array data;

	  //---| constructor (create with uninitialized data)

	  explicit array() : interface( nullptr ), data() { interface::ref( data.ptr() ); }

	};

      } // of multidim
    } // of fixed_size::
  } // of math::
} // of utk::

# pragma GCC visibility pop