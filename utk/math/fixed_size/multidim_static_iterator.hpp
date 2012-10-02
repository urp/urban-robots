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

      template < typename ProvidedInteface, index_type Index >
      struct multidim_static_iterator
      {

	// check if Index is fixed, othwise fix it.
	// this is for convenience
	typedef typename std::conditional< is_index_fixed< typename ProvidedInteface::layout, Index >::value
					 , ProvidedInteface
					 , typename ProvidedInteface::template changed_layout< typename ProvidedInteface::layout::template fix_index< Index, 0 >::type >::type
					 >::type interface;

	typedef typename interface::value_type 	value_type;
	typedef typename interface::layout 	layout;

	//:::| iteration index information

	static constexpr index_type index = Index;
	static constexpr index_type index_value = integral::at< typename layout::indices, Index >::value;

	static_assert( is_index_fixed< layout, Index >::value, "Iteration Index must be fixed." );

	//:::| prepare increment iterator

	typedef typename layout::template fix_index< Index, index_value+1 >::type increment_layout;
	typedef typename interface::template changed_layout< increment_layout >::type increment_interface;
	typedef multidim_static_iterator< increment_interface , Index > increment_iterator;

	//:::| prepare decrement iterator

	typedef typename layout::template fix_index< Index, index_value-1 >::type decrement_layout;
	typedef typename interface::template changed_layout< decrement_layout >::type decrement_interface;
	typedef multidim_static_iterator< decrement_interface , Index > decrement_iterator;

	//:::| memory interface

	typename interface::storage_interface storage;

	//---| constructor with storage_interface

	explicit
	multidim_static_iterator( const typename interface::storage_interface& other_storage ) : storage( other_storage )  {	}

	//---| copy constuctor

	multidim_static_iterator( const multidim_static_iterator< interface, Index >& other ) : storage( other.storage )  {	}

	//:::| iterator interface

	interface operator*() { return interface( storage ); }

	increment_iterator increment() const { return increment_iterator( storage ); }

	// TODO: CHECK for underrun ( mark rend() )
	decrement_iterator decrement() const { return decrement_iterator( storage ); }

	template< typename OtherInterface >
	bool operator==( const multidim_static_iterator< OtherInterface, Index >& other ) const
	{ return integral::all< typename integral::equal< typename layout::indices, typename OtherInterface::layout::indices >::type >::value
		 && storage.ptr() == other.storage.ptr();
	}

	template< typename OtherInterface >
	bool operator!=( const multidim_static_iterator< OtherInterface, Index >& other ) const
	{ return ! operator==( other ); }

      };

    } // of fixed_size::
  } // of math::
} // of utk::
