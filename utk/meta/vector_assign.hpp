/*  vector_assign.hpp - Copyright Peter Urban 2012-2013

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

# include "utk/meta/vector.hpp"
# include "utk/meta/vector_push_front.hpp"

namespace utk
{
  namespace meta
  {
    //---| assign

    template< typename Vector, index_type Index, typename > struct assign { /* unspecified */ };

    template< typename OldType, typename...OldTail, index_type Index, typename NewType >
    class assign< vector< OldType, OldTail... >, Index, NewType >
    {
	static_assert( Index < sizeof...(OldTail)+1, "Index must be smaller than vector size" );

	typedef typename assign< vector< OldTail... >, Index-1, NewType >::type tail;

      public:

	typedef typename push_front< tail, OldType >::type type;
    };

    template< typename OldType, typename...OldTail, typename NewType >
    struct assign< vector< OldType, OldTail... >, 0, NewType >
    {
      typedef vector< NewType, OldTail... > type;
    };

  } // of meta::
} // of utk::
