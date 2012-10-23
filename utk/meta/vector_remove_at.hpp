/*  vector_at.hpp - Copyright Peter Urban 2012

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
# include "utk/meta/vector_remove_false.hpp"

namespace utk
{
  namespace meta
  {

    // remove_at<

    template< typename Container, index_type Index >  struct remove_at { /* unspecified */ };

    // terminate
    template< typename FrontType,typename...Types >
    struct remove_at< vector< FrontType, Types... >, 0 >
    {
      typedef vector< Types... > type;
    };

    // recurse
    template< typename FrontType, typename...Types, index_type Index >
    class remove_at< vector< FrontType,Types... >, Index >
    {
        static_assert( Index < sizeof...(Types), "Out of bounds" );

        typedef typename remove_at< vector< Types... >, Index-1 >::type tail;

      public:

        typedef typename push_front< tail, FrontType >::type type;
    };

  } // of meta::
} // of utk::
