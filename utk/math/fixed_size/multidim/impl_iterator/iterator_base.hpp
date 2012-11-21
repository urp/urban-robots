/*  bla.h - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim_layout.hpp"
# include "utk/math/fixed_size/multidim_remove_index.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      //-----| multidim_interface

      template< typename Interface, index_type Index >
      struct multidim_iterator_base
      {
	//:::| parent interface

	typedef Interface parent_interface;
	typedef typename parent_interface::layout parent_layout;
	typedef typename parent_interface::storage_interface parent_storage_interface;

	//:::| value interface

	typedef typename remove_index< parent_layout, Index >::type value_layout;
	typedef typename parent_interface::template changed_layout< value_layout >::type value_interface;
	typedef typename value_interface::storage_interface value_storage_interface;

	//:::| container and value types

	typedef value_interface	value_type;

	//:::| storage interface

	parent_storage_interface storage;

	//:::| iteration information

	static constexpr index_type index = Index;

	static constexpr stride_type index_stride = meta::integral::at< typename parent_layout::strides, Index >::value;
	static constexpr size_type   index_size   = meta::integral::at< typename parent_layout::sizes  , Index >::value;

	//---| constructor with storage_interface

	multidim_iterator_base( const Interface& interface )
	: storage( interface ) { }

	//---| copy constuctor

	multidim_iterator_base( const multidim_iterator_base< Interface, Index >& other )
	: storage( other.storage ) { }

	//:::| iterator interface

	bool operator==( const multidim_iterator_base< Interface, Index >& other ) const
	{ return storage.ptr() == other.storage.ptr(); }

      }; // of multidim_iterator_base<>

    } // of fixed_size::
  } // of math::
} // of utk::
