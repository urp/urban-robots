/*  vector_split.hpp - Copyright Peter Urban 2012

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

# include "utk/meta/integral/vector.hpp"
# include "utk/meta/integral/vector_functions.hpp"

namespace utk
{
  namespace meta
  {
    namespace integral
    {

      //---| split

      template< typename Vector, index_type IndexAfterCut >
      struct split { /* unspecified */ };

      // terminate
      template< typename T, index_type IndexAfterCut >
      struct split< vector< T >, IndexAfterCut >
      {
	typedef vector< T > first;
	typedef vector< T > second;
      };

      // general case
      template< typename T, T HeadValue, T...TailValues, index_type IndexAfterCut >
      class split< vector< T, HeadValue, TailValues... >, IndexAfterCut >
      {
	  typedef split< vector< T, TailValues... >, IndexAfterCut-1 > tail;

	public:

	  typedef typename std::conditional< ( IndexAfterCut > 0 )
					   , typename push_front< typename tail::first, constant< T, HeadValue > >::type
					   , typename tail::first
					   >::type first;

  	  typedef typename std::conditional< ( IndexAfterCut <= 0 )
					   , typename push_front< typename tail::second, constant< T, HeadValue > >::type
					   , typename tail::second
					   >::type second;
      };

    } // of integral::
  } // of meta::
} // of utk::
