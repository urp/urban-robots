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

namespace utk
{
  namespace meta
  {

    //---| at

    template< typename, index_type > struct at { /* unspecified */ };

    template< typename Unpacked, typename...Pack >
    struct at< vector< Unpacked, Pack... >, 0 >
    {
      typedef Unpacked type;
    };

    template< typename Unpacked, typename...Pack, index_type Index >
    struct at< vector< Unpacked, Pack... >, Index >
    {
      static_assert( Index < sizeof...(Pack)+1, "Index must be smaller than vector size" );

      typedef typename at< vector< Pack... >, Index-1 >::type type;
    };

  } // of meta::
} // of utk::
