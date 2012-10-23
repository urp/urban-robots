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
# include "utk/meta/vector_pop_front.hpp"
# include "utk/meta/vector_push_front.hpp"

# include "utk/meta/integral/constant.hpp"

namespace utk
{
  namespace meta
  {

    //---| remove_false

    template< typename, typename >
    struct remove_false { /* unspecified */ };


    // terminate
    template< >
    struct remove_false< vector< >, vector< > >
    {
      typedef vector< > type;
    };

    // recurse
    template< bool...Predicates, typename ...Types >
    class remove_false< vector< Types... >
                      , vector< integral::constant< bool, Predicates >... >
                      >
    {
        typedef pop_front< vector< integral::constant< bool, Predicates >... > > predicates;
        typedef pop_front< vector< Types... > > values;

        typedef typename remove_false< typename values::tail
                                     , typename predicates::tail
                                     >::type tail;

      public:
        typedef typename std::conditional< predicates::type::value
                                         , typename push_front< tail, typename values::type >::type
                                         , tail
                                         >::type type;
    };

  } // of meta::
} // of utk::
