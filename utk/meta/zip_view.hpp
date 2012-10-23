/*  zip_view.hpp - Copyright Peter Urban 2012

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

# include "utk/meta/vector_make_uniform_vector.hpp"
# include "utk/meta/vector_push_front.hpp"

namespace utk
{
  namespace meta
  {

    namespace //<anonymous>
    {
      template< typename... Vectors > struct push_to_zip_view { /* unspecified */ };

      template< typename...ZipVector, typename...Vector >
      struct push_to_zip_view< vector< ZipVector... >, vector< Vector... > >
      {
        static_assert( sizeof...(ZipVector) == sizeof...(Vector), "Size of Vectors must agree.");
        typedef vector< typename push_front< ZipVector, Vector >::type... > type;
      };
    }

    //---| zip_view

    template< size_type Size, typename... Vectors >
    struct zip_view { /* unspecified */ };

    template< size_type Size >
    struct zip_view< Size >
    {
      typedef typename make_uniform_vector< Size, vector< > >::type type;
    };

    template< size_type Size, typename...Vector >
    struct zip_view< Size, vector< Vector... > >
    {
      static_assert( Size == sizeof...(Vector), "Size mismatch!");

      typedef vector< vector< Vector >... > type;
    };

    template< size_type Size, typename Vector, typename...MoreVectors >
    struct zip_view< Size, Vector, MoreVectors... >
    {
      typedef typename zip_view< Size, MoreVectors... >::type tail;
      typedef typename push_to_zip_view< tail, Vector >::type type;

    };



  } // of meta::
} // of utk::
