/*  index_iterator.hpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/layout/slice_layout/slice_layout.hpp"
# include "utk/math/fixed_size/layout/slice_layout/functions/fix_index.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace iterator
      {
	namespace fusion
	{
	  template < typename Interface, index_type Index, ptrdiff_t IndexValue = 0 >
	  class index_iterator : public index_iterator_base< Interface, Index >
	  {
	      typedef index_iterator_base< Interface, Index > base;

	      //:::| static value interface |::::::::::::::::::::::::::::/

	      typedef typename layout::fix_index< typename base::parent_layout, Index, IndexValue >::type value_layout;

	      // use unmanaged storage to avoid unintentional allocations and copies
	      typedef typename interface::interface_traits< typename base::parent_interface >::unmanaged_interface unmanaged;

	      typedef typename interface::change_layout< unmanaged, value_layout >::type value_interface;

	    public:

	      //:::| container and value types |:::::::::::::::::::::::::/

	      typedef value_interface value_type;

	      //:::| iteration information |:::::::::::::::::::::::::::::/

	      static constexpr ptrdiff_t index_value = IndexValue;

	      //:::| iterator types |::::::::::::::::::::::::::::::::::::/

	      //---| random access iterator
	      template< index_type NewIndexValue >
	      using random_access_iterator = index_iterator< Interface , Index, NewIndexValue >;

	      //---| forward iterator
	      typedef random_access_iterator< IndexValue + 1 > forward_iterator;

	      //---| reverse iterator
	      typedef random_access_iterator< IndexValue - 1 > reverse_iterator;

	      //:::| constructors |::::::::::::::::::::::::::::::::::::::/

	      //---| constructor with storage_interface
	      index_iterator( const Interface& inter )
	      : base( inter )  { }

	      //---| copy constuctor
	      template< ptrdiff_t OtherIndexValue >
	      index_iterator( const index_iterator< Interface, Index, OtherIndexValue >& other )
	      : base( other )  { }

	      //:::| dereference operator |::::::::::::::::::::::::::::::/

	      value_interface operator*()
	      { return value_interface( typename value_interface::storage_type( base::storage.ptr() ) ); }

	      //:::| increment operator |::::::::::::::::::::::::::::::::/

	      forward_iterator increment() const
	      { return forward_iterator( *this ); }

	      //:::| decrement operator |::::::::::::::::::::::::::::::::/
	      // TODO: !!! CHECK for underrun ( mark rend() )

	      reverse_iterator decrement() const
	      { return reverse_iterator( *this ); }

	      //:::| comparison operators |::::::::::::::::::::::::::::::/

	      template< typename OtherLayout, ptrdiff_t OtherIndexValue >
	      bool operator==( const index_iterator< OtherLayout, Index, OtherIndexValue >& other ) const
	      { return OtherIndexValue == IndexValue && base::operator==(other); }

	      template< typename OtherLayout, ptrdiff_t OtherIndexValue >
	      bool operator!=( const index_iterator< OtherLayout, Index, OtherIndexValue >& other ) const
	      { return not operator==( other ); }

	  }; // of index_iterator<>

	} // of fusion::
      } // of iterator::
    } // of fixed_size::
  } // of math::
} // of utk::
