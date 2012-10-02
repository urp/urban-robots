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

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      //-----| multidim_interface
      // TODO: cleanup and unify with dynamic_iterator
      template < typename ProvidedInterface, index_type Index, index_type IndexValue = 0 >
      struct multidim_static_iterator
      {

	//:::| parent interface

	typedef ProvidedInterface parent_interface;
	typedef typename parent_interface::layout parent_layout;
	typedef typename parent_interface::storage_interface parent_storage_interface;

	//:::| value interface

	typedef typename parent_layout::template remove_index< Index >::type value_layout;
	typedef typename parent_interface::template changed_layout< value_layout >::type value_interface;
	typedef typename value_interface::storage_interface value_storage_interface;

	//:::| container and value types

	typedef value_interface	value_type;

	typedef multidim_static_iterator< parent_interface , Index, IndexValue + 1 > increment_iterator;
	typedef multidim_static_iterator< parent_interface , Index, IndexValue - 1 > decrement_iterator;

	//:::| storage interface

	parent_storage_interface storage;

	//:::| iteration information

	static constexpr index_type index = Index;
	static constexpr index_type index_value = IndexValue;
	static constexpr size_type   index_size   = integral::at< typename parent_layout::sizes  , Index >::value;
	static constexpr stride_type index_stride = integral::at< typename parent_layout::strides, Index >::value;

	static_assert( not is_index_fixed< parent_layout, Index >::value, "Iteration Index must not be fixed." );

	//---| constructor with storage_interface

	explicit
	multidim_static_iterator( const parent_storage_interface& other_storage ) : storage( other_storage )  {	}

	//---| copy constuctor
	template< index_type OtherIndexValue >
	multidim_static_iterator( const multidim_static_iterator< parent_interface, Index, OtherIndexValue >& other )
	: storage( other.storage )  { }

	//:::| iterator interface
	// TODO: ask layout for offset
	value_interface operator*() { return value_interface( value_storage_interface( storage.ptr() + index_value * index_stride ) ); }

	increment_iterator increment() const { return increment_iterator( storage ); }

	// TODO: !!! CHECK for underrun ( mark rend() )
	decrement_iterator decrement() const { return decrement_iterator( storage ); }

	template< typename OtherLayout, index_type OtherIndexValue >
	bool operator==( const multidim_static_iterator< OtherLayout, Index, OtherIndexValue >& other ) const
	{ return OtherIndexValue == IndexValue && storage.ptr() == other.storage.ptr();	}

	template< typename OtherLayout, index_type OtherIndexValue >
	bool operator!=( const multidim_static_iterator< OtherLayout, Index, OtherIndexValue >& other ) const
	{ return ! operator==( other ); }

      };

    } // of fixed_size::
  } // of math::
} // of utk::
