/*  specialized_functions.hpp - Copyright Peter Urban 2012

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
      namespace tensor
      {
	// type

	template< typename Interface, typename NewLayout >
	struct change_layout { /* unspecified */ };

	// instance

	template< typename Interface, typename NewLayout >
	typename change_layout< Interface, NewLayout >::type use_layout( const Interface& t )
	{
	  static_assert( NewLayout::total_size == Interface::layout::total_size
		       , "NewLayout::total_size must fit to original layout"
		       );
	  typedef typename change_layout< Interface, NewLayout >::type type;
	  return type( t );
	};

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::