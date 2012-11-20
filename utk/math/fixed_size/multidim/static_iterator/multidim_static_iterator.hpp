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
# include "utk/math/fixed_size/multidim_iterator_base.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      //-----| multidim_interface
      // TODO: cleanup and unify with dynamic_iterator
      template < typename Interface, index_type Index, ptrdiff_t IndexValue = 0 >
      struct multidim_static_iterator : public multidim_iterator_base< Interface, Index >
      {
	typedef multidim_iterator_base< Interface, Index > base;

	//:::| iterator types

	typedef multidim_static_iterator< Interface , Index, IndexValue + 1 > increment_iterator;
	typedef multidim_static_iterator< Interface , Index, IndexValue - 1 > decrement_iterator;

	//:::| iteration information

	static constexpr ptrdiff_t index_value = IndexValue;

	//---| constructor with storage_interface

	multidim_static_iterator( const Interface& interface )
	: base( interface )  { }

	//---| copy constuctor
	template< ptrdiff_t OtherIndexValue >
	multidim_static_iterator( const multidim_static_iterator< Interface, Index, OtherIndexValue >& other )
	: base( other )  { }

	//:::| iterator interface
	// TODO: ask layout for offset
	typename base::value_interface operator*()
	{ return typename base::value_interface( typename base::value_storage_interface( base::storage.ptr() + index_value * ptrdiff_t( base::index_stride ) ) ); }

	increment_iterator increment() const
	{ return increment_iterator( *this ); }

	// TODO: !!! CHECK for underrun ( mark rend() )
	decrement_iterator decrement() const
	{ return decrement_iterator( *this ); }

	template< typename OtherLayout, ptrdiff_t OtherIndexValue >
	bool operator==( const multidim_static_iterator< OtherLayout, Index, OtherIndexValue >& other ) const
	{ return OtherIndexValue == IndexValue && base::operator==(other); }

	template< typename OtherLayout, ptrdiff_t OtherIndexValue >
	bool operator!=( const multidim_static_iterator< OtherLayout, Index, OtherIndexValue >& other ) const
	{ return not operator==( other ); }

      }; // of multidim_static_iterator<>

    } // of fixed_size::
  } // of math::
} // of utk::
