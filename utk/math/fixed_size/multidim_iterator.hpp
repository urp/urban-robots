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

      template < typename MultidimInterface, index_type Index >
      struct multidim_iterator
      {

	typedef MultidimInterface 		interface;
	typedef typename interface::value_type 	value_type;
	typedef typename interface::layout 	layout;
	static constexpr index_type		index = Index;

	static const index_type current_index_value = integral::at< typename layout::indices, Index >::value;
	typedef typename layout::template fix_index< Index, current_index_value+1 >::type increment_layout;
	typedef multidim_iterator< typename interface::template changed_layout< increment_layout >::type , Index > increment_iterator;

	typename interface::storage_interface m_storage;

	//---| constructor with storage_interface

	explicit
	multidim_iterator( const MultidimInterface& md_interface ) : m_storage( md_interface.ptr() )  {	}

	//:::| iterator interface

	interface operator*() { return interface( m_storage ); }

	increment_iterator operator++() const
	{ return increment_iterator( *this ); }

	template< typename OtherInterface >
	bool operator==( const multidim_iterator< OtherInterface, OtherInterface::index >& other ) const
	{ return integral::all< typename integral::equal< typename layout::indices, typename OtherInterface::layout::indices >::type >::value
		 && m_storage.ptr() == other.ptr(); }

	template< typename OtherInterface >
	bool operator!=( const multidim_iterator< OtherInterface, OtherInterface::index >& other ) const
	{ return ! operator==( other ); }


	/*:::| element access

	template< typename...CoordTypes >
	value_type& at( CoordTypes...coords )
	{
	  //TODO: checks
	  return storage_interface::at( layout::free_indices_offset( coords... )
				    + layout::fixed_indices_offset()
				    );
	}

	template< typename...CoordTypes >
	const value_type& at( CoordTypes...coords ) const
	{
	  //TODO: checks
	  return storage_interface::at( layout::free_indices_offset( coords... )
				      + layout::fixed_indices_offset()
				      );
	}
	*/
      };

    } // of fixed_size::
  } // of math::
} // of utk::
