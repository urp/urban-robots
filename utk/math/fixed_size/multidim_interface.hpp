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
# include "utk/math/fixed_size/multidim_layout.hpp"
# include "utk/math/fixed_size/multidim_layout_functions.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      //-----| multidim_interface

      template < typename T, typename Layout >
      struct multidim_interface
      :	public vector_interface< T, Layout::total_size() >
      {
	typedef T value_type;

	typedef Layout layout;

	typedef vector_interface< value_type, layout::total_size() > storage_interface;

	static constexpr index_type order = layout::order;

	//---| constructor with storage pointer

	explicit
	multidim_interface( typename storage_interface::pointer_type pointer ) : storage_interface( pointer )  {	}

	// element access

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

      };

    } // of fixed_size::
  } // of math::
} // of utk::
