/*  index_iterator.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/iterator/index_iterator_base.hpp"

# include "utk/math/fixed_size/layout/generic_functions/remove_index.hpp"

# include "utk/math/fixed_size/interface/generic_functions/interface_traits.hpp"
# include "utk/math/fixed_size/interface/generic_functions/change_layout.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace iterator
      {
	namespace stl
	{

	  // iterates over an index
	  template< typename Interface, index_type Index >
	  class index_iterator : public index_iterator_base< Interface, Index >
	  {
	      typedef index_iterator< Interface, Index > type;
	      typedef index_iterator_base< Interface, Index >    base;

	      //:::| dynamic value interface |:::::::::::::::::::::::::::/

	      // TODO: investigate possible size problems
	      typedef typename layout::remove_index< typename base::parent_layout, Index >::type value_layout;

	      // use unmanaged storage to avoid unintentional allocations and copies
	      typedef typename interface::interface_traits< typename base::parent_interface >::unmanaged_interface unmanaged_interface;
	      // switch to value_layout
	      typedef typename interface::change_layout< unmanaged_interface, value_layout >::type value_interface;

	    public:

	      //:::| types needed std::iterator_traits<type>  |:::::::::

	      typedef value_interface value_type;
	      typedef stride_type     difference_type;
	      typedef value_type*     pointer;
	      typedef value_type&     reference;
	      typedef std::random_access_iterator_tag	iterator_category;

	      //:::| iteration information |::::::::::::::::::::::::::::

	      mutable ptrdiff_t index_value;

	      //---| constructor with storage_type

	      explicit
	      index_iterator( const Interface& inter, ptrdiff_t index_value = 0 )
	      : base( inter ), index_value( index_value )  { }

	      //---| copy constuctor

	      index_iterator( const type& other )
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

	  }; // of index_iterator<>

	} // of stl::
      } // of iterator::
    } // of fixed_size::
  } // of math::
} // of utk::
