/*  iterator_base.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_layout/remove_index.hpp"

# include "utk/math/fixed_size/multidim/impl_slice_layout/fix_index.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {

	template< typename Interface, index_type Index >
	struct iterator_base
	{
	  //:::| parent interface

	  typedef Interface parent_interface;
	  typedef typename parent_interface::layout parent_layout;
	  typedef typename parent_interface::storage_interface parent_storage_interface;


	  //:::| storage interface

	  parent_storage_interface storage;

	  //:::| iteration information

	  static constexpr index_type index = Index;

	  static constexpr stride_type index_stride = meta::integral::at< typename parent_layout::strides, Index >::value;
	  static constexpr size_type   index_size   = meta::integral::at< typename parent_layout::sizes  , Index >::value;

	  //---| constructor with storage_interface

	  iterator_base( const Interface& interface )
	  : storage( interface ) { }

	  //---| copy constuctor

	  iterator_base( const iterator_base< Interface, Index >& other )
	  : storage( other.storage ) { }

	  //:::| iterator interface

	  bool operator==( const iterator_base< Interface, Index >& other ) const
	  { return storage.ptr() == other.storage.ptr(); }

	}; // of iterator_base<>
      }
    } // of fixed_size::
  } // of math::
} // of utk::
