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

      template< typename ProvidedInterface, index_type Index >
      struct multidim_dynamic_iterator
      {
	//:::| parent interface

	typedef ProvidedInterface parent_interface;
	typedef typename parent_interface::layout parent_layout;
	typedef typename parent_interface::storage_interface parent_storage_interface;

	static_assert( not is_index_fixed< parent_layout, Index >::value,
		       "Index used for dynamic iteration should not be fixed."
		     );

	static constexpr stride_type index_stride = integral::at< typename parent_layout::strides, Index >::value;
	static constexpr size_type   index_size   = integral::at< typename parent_layout::sizes  , Index >::value;

	//:::| value interface

	typedef typename parent_layout::template remove_index< Index >::type value_layout;
	typedef typename parent_interface::template changed_layout< value_layout >::type value_interface;
	typedef typename value_interface::storage_interface value_storage_interface;

	//:::| iterator typedefs
	typedef value_interface	value_type;

	typedef multidim_dynamic_iterator< parent_interface, Index > type;

	// iteration index
	static constexpr index_type index = Index;

	//:::| non-static members

	parent_storage_interface storage;

	// current iteration

	mutable index_type index_value;

	//---| constructor with storage_interface

	explicit
	multidim_dynamic_iterator( const parent_storage_interface& storage ) : storage( storage )  { }

	//---| copy constuctor

	multidim_dynamic_iterator( const type& other )
	: storage( other.storage ), index_value( other.index_value )  { }

	//:::| iterator interface

	//---| dereference operators

	value_interface operator*()
	{ return value_interface( value_storage_interface( storage.ptr() + index_stride * index_value ) ); }

	const value_interface operator*() const
	{ return value_interface( value_storage_interface( storage + index_stride * index_value ) ); }

	//---| increment iterators

	type& operator++()
	{
	  ++index_value;
	  return *this;
	}

	const type& operator++() const
	{
	  ++index_value;
	  return *this;
	}

	// post_increment
	type operator++(int) const
	{
	  type old_self( *this );
	  ++index_value;
	  return old_self;
	}

	//---| decrement iterators

	type& operator--()
	{
	  --index_value;
	  return *this;
	}

	const type& operator--() const
	{
	  --index_value;
	  return *this;
	}

	// post_increment
	type operator--(int) const
	{
	  type old_self( *this );
	  index_value--;
	  return old_self;
	}


	bool operator==( const type& other ) const { return storage.ptr() == other.ptr(); }

	bool operator!=( const type& other ) const { return ! operator==( other ); }

      };

    } // of fixed_size::
  } // of math::
} // of utk::
