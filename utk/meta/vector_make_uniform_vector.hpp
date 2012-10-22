/*  vector_push_front.hpp - Copyright Peter Urban 2012

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
# include "utk/meta/vector_push_back.hpp"

namespace utk
{
  namespace meta
  {
    //---| make_uniform_vector

    template< size_type Size, typename Type >
    class make_uniform_vector
    {
        typedef typename make_uniform_vector< Size-1, Type >::type tail;

      public:

        typedef typename push_back< tail, Type >::type type;
    };

    template< typename Type >
    struct make_uniform_vector< 0, Type >
    {
      typedef vector< > type;
    };

  } // of meta::
} // of utk::
