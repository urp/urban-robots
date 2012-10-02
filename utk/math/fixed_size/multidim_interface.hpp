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

# include "utk/math/fixed_size/vector_interface.hpp"
# include "utk/math/fixed_size/vector_functions.hpp" //required for fixed_size::at
# include "utk/math/fixed_size/multidim_layout.hpp"
# include "utk/math/fixed_size/multidim_layout_functions.hpp"
# include "utk/math/fixed_size/multidim_static_iterator.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      //-----| multidim_interface

      template < typename T, typename Layout >
      struct multidim_interface
      :	public vector_interface< T, Layout::total_size >
      {
	typedef multidim_interface< T, Layout > type;

	typedef T value_type;

	typedef Layout layout;

	typedef vector_interface< value_type, layout::total_size > storage_interface;

	static constexpr index_type order = layout::order;

	//:::| constructors

	//---| constructor with storage pointer

	explicit
	multidim_interface( typename storage_interface::pointer_type pointer ) : storage_interface( pointer )  {	}

	explicit
	multidim_interface( const storage_interface& storage ) : storage_interface( storage )  {	}

	//---| copy constructor
	template< typename OtherInterface
		  // TODO: replace condition by something like check_layout_compatibility< Layout1, Layout2 >
		, typename  = typename std::enable_if< integral::all< typename integral::equal< typename OtherInterface::layout::sizes
											      , typename layout::sizes
											      >::type
								    >::value
						     , void
						     >::type
		>
	multidim_interface( const OtherInterface& other ) : storage_interface( other )	{	}

	//:::| derived interfaces

	template< typename OtherLayout >
	struct changed_layout
	{
	  typedef multidim_interface<T, OtherLayout > type;
	};


	template< typename OtherLayout >
	typename changed_layout< OtherLayout >::type change_layout() const
	{
	  static_assert( integral::all< typename integral::equal< typename OtherLayout::sizes, typename layout::sizes >::type >::value
		       , "OtherLayouts vector-space dimensions must agree with original layout"
		       );

	  return typename changed_layout< OtherLayout >::type( *this );
	}

	//:::| iterator interface

	//:::::| prepare iterator_begin

	// TODO: !!! these aliases make gcc-4.7 crash

	template< index_type Index >
	using iterator_begin_interface = typename changed_layout< typename layout::template fix_index< Index, 0 >::type >::type;

	template< index_type Index >
	using iterator_begin = multidim_static_iterator< iterator_begin_interface< Index >, Index >;

	template< index_type Index >
	using const_iterator_begin = const multidim_static_iterator< iterator_begin_interface< Index >, Index >;

	//:::::| prepare iterator_end

	template< index_type Index >
	using iterator_end_interface = typename changed_layout< typename layout::template fix_index< Index
												   , integral::at< typename layout::sizes, Index >::value
												   >::type
							      >::type;

	template< index_type Index >
	using iterator_end = multidim_static_iterator< iterator_end_interface< Index >, Index >;

	template< index_type Index >
	using const_iterator_end = const multidim_static_iterator< iterator_end_interface< Index >, Index >;

	//---| begin

	template< index_type Index >
	iterator_begin<Index> begin() { return const_iterator_begin< Index >( *this ); }

	template< index_type Index >
	const_iterator_begin<Index> begin() const { return const_iterator_begin< Index >( *this ); }

	//---| end

	template< index_type Index >
	iterator_end<Index> end() { return const_iterator_end< Index >( *this ); }

	template< index_type Index >
	const_iterator_end<Index> end() const { return const_iterator_end< Index >( *this ); }


	//:::| element access

	//---| at

	template< typename...CoordTypes >
	value_type& at( CoordTypes...coords ) throw( std::out_of_range )
	{
	  //TODO: checks
	  const size_t storage_index = layout::free_indices_offset( coords... ) + layout::fixed_indices_offset();
	  return fixed_size::at( static_cast< storage_interface& >(*this), storage_index );
	}

	template< typename...CoordTypes >
	const value_type& at( CoordTypes...coords ) const throw( std::out_of_range )
	{
	  //TODO: checks
	  const size_t storage_index = layout::free_indices_offset( coords... ) + layout::fixed_indices_offset();
	  return fixed_size::at( static_cast< const storage_interface& >(*this), storage_index );
	}

      };

      template< typename T, typename Layout >
      constexpr index_type multidim_interface< T, Layout >::order;

    } // of fixed_size::
  } // of math::
} // of utk::
