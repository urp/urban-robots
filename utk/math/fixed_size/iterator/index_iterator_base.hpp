/*  index_iterator_base.hpp - Copyright Peter Urban 2012

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

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace iterator
      {

	template< typename Interface, index_type Index >
	struct index_iterator_base
	{
	  //:::| parent interface |::::::::::::::::::::::::::::::::::::/

	  typedef Interface parent_interface;
	  typedef typename parent_interface::layout parent_layout;
	  // storage type is unmanaged to avoid copies
	  typedef typename interface::interface_traits< parent_interface >::unmanaged_storage storage_type;

	  //:::| storage interface |:::::::::::::::::::::::::::::::::::/

	  storage_type storage;

	  //:::| iteration information |:::::::::::::::::::::::::::::::/

	  static constexpr index_type index = Index;

	  static constexpr stride_type index_stride = meta::integral::at< typename parent_layout::strides, Index >::value;
	  static constexpr size_type   index_size   = meta::integral::at< typename parent_layout::sizes  , Index >::value;

	  //---| constructor with storage_type

	  index_iterator_base( const Interface& interface )
	  : storage( interface.storage ) { }

	  //---| copy constuctor

	  index_iterator_base( const index_iterator_base< Interface, Index >& other )
	  : storage( other.storage ) { }

	  //:::| comparison operators |::::::::::::::::::::::::::::::/

	  bool operator==( const index_iterator_base< Interface, Index >& other ) const
	  { return storage.ptr() == other.storage.ptr(); }

	}; // of index_iterator_base<>

      } // of iterator::
    } // of fixed_size::
  } // of math::
} // of utk::
