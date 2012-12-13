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

# include "utk/meta/vector.hpp"
# include "utk/meta/vector_push_front.hpp"

namespace utk
{
  namespace meta
  {

      //---| split

      template< typename Vector, index_type IndexAfterCut >
      struct split { /* unspecified */ };

      // terminate
      template< index_type IndexAfterCut >
      struct split< vector< >, IndexAfterCut >
      {
        typedef vector< > first;
        typedef vector< > second;
      };

      // general case
      template< typename Head, typename...Tail, index_type IndexAfterCut >
      class split< vector< Head, Tail... >, IndexAfterCut >
      {
          typedef split< vector< Tail... >, IndexAfterCut-1 > tail;

        public:

          typedef typename std::conditional< ( IndexAfterCut > 0 )
                                           , typename push_front< typename tail::first, Head >::type
                                           , typename tail::first
                                           >::type first;

          typedef typename std::conditional< ( IndexAfterCut <= 0 )
                                           , typename push_front< typename tail::second, Head >::type
                                           , typename tail::second
                                           >::type second;
      };

  } // of meta::
} // of utk::
