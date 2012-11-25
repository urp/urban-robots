/*  vector_pop_back.hpp - Copyright Peter Urban 2012

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

    //---| pop_front

    template< typename > struct pop_back { /* unspecified */ };

    // terminate
    template< typename Back >
    struct pop_back< vector< Back > >
    {
      typedef Back type;

      typedef vector< > tail;
    };

    // pop first value and continue
    template< typename Unpacked , typename...Pack >
    class pop_back< vector< Unpacked, Pack... > >
    {
        typedef pop_back< vector< Pack... > > popped;

      public:

        typedef typename popped::type type;

        typedef typename push_front< typename popped::tail, Unpacked >::type tail;
    };


    // TODO: clang: warning: class template partial specialization contains template parameters
    /*              that can not be deduced; this partial specialization will never be used
    template< typename Unpacked, typename...Pack >
    struct pop_back< vector< Pack..., Unpacked > >
    {
      typedef Unpacked type;

      typedef vector< Pack... > tail;
    };*/

  } // of meta::
} // of utk::
