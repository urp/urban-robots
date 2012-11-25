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

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {
	// type

	template< typename Interface, typename NewLayout >
	struct change_layout { /* unspecified */ };

	// general
	template< typename ValueType
		, typename OldLayout
		, template< typename, typename > class Interface
		, typename NewLayout
		>
	struct change_layout< Interface< ValueType, OldLayout >, NewLayout >
	{
	  typedef Interface< ValueType, NewLayout > type;
	};

	// instance

	template< typename Interface, typename NewLayout >
	auto use_layout( const Interface& t )
	-> typename change_layout< Interface, NewLayout >::type
	{
	  static_assert( NewLayout::total_size == Interface::layout::total_size
		       , "NewLayout::total_size must fit to original layout"
		       );
	  typedef typename change_layout< Interface, NewLayout >::type type;
	  return type( t );
	};

      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
