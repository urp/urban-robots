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

# include "utk/math/fixed_size/multidim/impl_interface/specialized_functions.hpp"

# include "utk/math/fixed_size/multidim/iterators.hpp"


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
	// TODO: make member
	: public vector::interface< T, Layout::total_size >
	{
	  typedef interface< T, Layout > type;

	  typedef T value_type;

	  typedef Layout layout;

	  typedef vector::interface< value_type, layout::total_size > storage_interface;

	  static constexpr index_type order = layout::order;

	  //:::| constructors

	  //---| constructor with storage pointer

	  explicit
	  interface( typename storage_interface::pointer_type pointer ) : storage_interface( pointer )  {	}

	  explicit
	  interface( const storage_interface& storage ) : storage_interface( storage )
	  {
	    static_assert( storage_interface::size >= Layout::total_size, "given storage is too short." );
	  }

	  /*---| copy constructor
	  template< typename OtherInterface >
	  interface( const OtherInterface& other ) : storage_interface( other )
	  {
	    static_assert( meta::integral::all< typename meta::integral::equal< typename OtherInterface::layout::sizes, typename layout::sizes >::type >::value
			 , "incompatible layouts!"
			 );
	  }*/


	  //:::| static iterator interface |:::::::::::::::::::::::::::/

	  //:::::| prepare static_index_iterator_begin

	  // TODO: !!! these aliases make gcc-4.7 crash

	  template< index_type Index >
	  using static_index_iterator_begin = static_index_iterator< type, Index, 0 >;

	  template< index_type Index >
	  using const_static_index_iterator_begin = const static_index_iterator< type, Index, 0 >;

	  //:::::| prepare static_index_iterator_end

	  template< index_type Index >
	  using static_index_iterator_end = static_index_iterator< type, Index, meta::integral::at< typename layout::sizes, Index >::value >;

	  template< index_type Index >
	  using const_static_index_iterator_end = const static_index_iterator< type, Index, meta::integral::at< typename layout::sizes, Index >::value >;

	  //---| begin
	  template< index_type Index >
	  static_index_iterator_begin<Index> static_begin() { return static_index_iterator_begin< Index >( *this ); }

	  template< index_type Index >
	  const_static_index_iterator_begin<Index> static_begin() const { return const_static_index_iterator_begin< Index >( *this ); }

	  //---| end

	  template< index_type Index >
	  static_index_iterator_end<Index> static_end() { return static_index_iterator_end< Index >( *this ); }

	  template< index_type Index >
	  const_static_index_iterator_end<Index> static_end() const { return const_static_index_iterator_end< Index >( *this ); }

	  //:::| dynamic iterator interface |::::::::::::::::::::::::::/

	  //:::::| declare iterators


	  template< index_type Index >
	  using iterator = const dynamic_index_iterator< type, Index >;

	  template< index_type Index >
	  using const_iterator = const dynamic_index_iterator< type, Index >;

	  //---| begin
	  template< index_type Index >
	  iterator<Index> begin() { return iterator< Index >( *this, 0 ); }

	  template< index_type Index >
	  const_iterator<Index> begin() const { return const_iterator< Index >( *this, 0 ); }

	  //---| end

	  template< index_type Index >
	  auto end( ) -> iterator<Index>
	  {
	    constexpr index_type end_index = meta::integral::at< typename Layout::sizes, Index>::value;
	    return const_iterator< Index >( *this, end_index );

	  }

	  template< index_type Index >
	  auto end( ) const -> const_iterator<Index>
	  {
    	    constexpr index_type end_index = meta::integral::at< typename Layout::sizes, Index>::value;
	    return const_iterator< Index >( *this, end_index );
	  }

	  //:::| element access

	  //---| at

	  template< typename...CoordTypes >
	  value_type& at( CoordTypes...coords ) throw( std::out_of_range )
	  {
	    //TODO: checks
	    const size_t storage_index = layout::index_offset( coords... ) + layout::static_offset();
	    return fixed_size::vector::at( static_cast< storage_interface& >(*this), storage_index );
	  }

	  template< typename...CoordTypes >
	  const value_type& at( CoordTypes...coords ) const throw( std::out_of_range )
	  {
	    //TODO: checks
	    const size_t storage_index = layout::index_offset( coords... ) + layout::static_offset();
	    return fixed_size::vector::at( static_cast< const storage_interface& >(*this), storage_index );
	  }

	};

	template< typename T, typename Layout >
	constexpr index_type interface< T, Layout >::order;

      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
