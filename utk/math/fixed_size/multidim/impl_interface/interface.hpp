/*  interface.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/vector/interface.hpp"
# include "utk/math/fixed_size/vector/at.hpp"

# include "utk/math/fixed_size/multidim/impl_layout/helpers.hpp" // for index_type, ...

# include "utk/math/fixed_size/multidim/impl_interface/change_layout.hpp"
# include "utk/math/fixed_size/multidim/impl_iterators/declare_iterators.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {

	template < typename T, typename Layout >
	struct interface
	{
	  typedef interface< T, Layout > type;

	  typedef T value_type;

	  typedef Layout layout;

	  typedef vector::interface< value_type, layout::total_size > storage_interface;


	  // storage

	  storage_interface storage;

	  static constexpr index_type order = layout::order;

	  //:::| constructors

	  //---| constructor with storage pointer

	  explicit
	  interface( typename storage_interface::pointer_type pointer ) : storage( pointer )  {	}

	  explicit
	  interface( const storage_interface& s ) : storage( s )
	  { }

	  //---| copy constructor - TODO: use iterators
	  template< typename OtherInterface >
	  interface( const typename OtherInterface::storage_interface& other ) : storage( other )
	  {
	    static_assert( storage_interface::size >= OtherInterface::layout::total_size, "given storage is too short." );
	  }

	  //:::| iterators |:::::::::::::::::::::::::::::::::::::::::::/

	  UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ITERATORS( type )

	  //:::| conversion operators

	  //---| scalar component

	  template< size_type order = layout::order, typename = typename std::enable_if< order==0, void >::type >
	  operator value_type& () { return at( storage, layout::static_offset() ); }

	  template< size_type order = layout::order, typename = typename std::enable_if< order==0, void >::type >
	  operator const value_type& () const { return at( storage, layout::static_offset() ); }

	};

	template< typename T, typename Layout >
	constexpr index_type interface< T, Layout >::order;

      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
