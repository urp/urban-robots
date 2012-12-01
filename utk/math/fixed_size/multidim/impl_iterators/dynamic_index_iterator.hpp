/*  dynamic_index_iterator.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_iterators/index_iterator_base.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {

	// iterates over an index
	template< typename Interface, index_type Index >
	class dynamic_index_iterator : public index_iterator_base< Interface, Index >
	{
	    typedef dynamic_index_iterator< Interface, Index > type;
	    typedef index_iterator_base< Interface, Index >    base;

	    //:::| dynamic value interface

	    typedef typename remove_index< typename base::parent_layout, Index >::type value_layout;
	    typedef typename change_layout< typename base::parent_interface, value_layout >::type value_interface;
	    typedef typename value_interface::storage_interface value_storage_interface;

	  public:

	    //:::| container and value types

	    typedef value_interface value_type;


	    //:::| iteration information

	    mutable ptrdiff_t index_value;

	    //---| constructor with storage_interface

	    explicit
	    dynamic_index_iterator( const Interface& interface, ptrdiff_t index_value = 0 )
	    : base( interface ), index_value( index_value )  { }

	    //---| copy constuctor

	    dynamic_index_iterator( const type& other )
	    : base( other ), index_value( other.index_value )  { }

	    //:::| iterator interface

	    //---| dereference operators
	    // TODO: ask layout for offset?!!!
	    value_interface operator*()
	    { return value_interface( value_storage_interface( base::storage.ptr() + ptrdiff_t( base::index_stride ) * index_value ) ); }
	    // TODO: ask layout for offset?!!!
	    const value_interface operator*() const
	    { return value_interface( value_storage_interface( base::storage.ptr() + ptrdiff_t( base::index_stride ) * index_value ) ); }

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

	    //:::| comparison operators

	    bool operator==( const type& other ) const
	    { return index_value == other.index_value and base::operator==( other ); }

	    bool operator!=( const type& other ) const
	    { return not operator==( other ); }

	}; // of dynamic_index_iterator<>

      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
