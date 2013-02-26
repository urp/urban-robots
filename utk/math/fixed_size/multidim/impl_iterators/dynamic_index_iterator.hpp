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

	    //:::| dynamic value interface |:::::::::::::::::::::::::::/

	    typedef typename remove_index< typename base::parent_layout, Index >::type value_layout;

	    // use unmanaged storage to avoid unintentional allocations and copies
	    typedef typename interface_traits< typename base::parent_interface >::unmanaged_interface unmanaged_interface;
	    // switch to value_layout
	    typedef typename change_layout< unmanaged_interface, value_layout >::type value_interface;

	    //typedef typename value_interface::storage_type value_storage_type;

	  public:

	    //:::| container and value types |:::::::::::::::::::::::::/

	    typedef value_interface value_type;


	    //:::| iteration information |:::::::::::::::::::::::::::::/

	    mutable ptrdiff_t index_value;

	    //---| constructor with storage_type

	    explicit
	    dynamic_index_iterator( const Interface& inter, ptrdiff_t index_value = 0 )
	    : base( inter ), index_value( index_value )  { }

	    //---| copy constuctor

	    dynamic_index_iterator( const type& other )
	    : base( other ), index_value( other.index_value )  { }

	    //:::| dereference operator |::::::::::::::::::::::::::::::/

	    //---| dereference operators

	    // TODO: ask layout for offset?!!!
	    auto operator*() -> value_interface
	    { return value_interface( typename value_interface::storage_type( base::storage.ptr() + ptrdiff_t( base::index_stride ) * index_value ) ); }

	    // TODO: ask layout for offset?!!!, need this???
	    auto operator*() const -> const value_interface
	    { return value_interface( typename value_interface::storage_type( base::storage.ptr() + ptrdiff_t( base::index_stride ) * index_value ) ); }

	    //:::| increment operators |:::::::::::::::::::::::::::::::/

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

	    //---| post increment
	    type operator++(int) const
	    {
	      type old_self( *this );
	      ++index_value;
	      return old_self;
	    }

	    //:::| decrement operators |:::::::::::::::::::::::::::::::/

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

	    //---| post decrement
	    type operator--(int) const
	    {
	      type old_self( *this );
	      index_value--;
	      return old_self;
	    }

	    //:::| comparison operators |::::::::::::::::::::::::::::::/

	    bool operator==( const type& other ) const
	    { return index_value == other.index_value and base::operator==( other ); }

	    bool operator!=( const type& other ) const
	    { return not operator==( other ); }

	}; // of dynamic_index_iterator<>

      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
