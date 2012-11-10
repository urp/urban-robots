/*  vector_transform.hpp - Copyright Peter Urban 2012

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

      //---| transform

      template< typename, typename > struct transform { /* unspecified */ };

      template< typename...Vector, class UnaryScalarOperator >
      struct transform< vector< Vector... >, UnaryScalarOperator >
      {
        typedef vector< typename UnaryScalarOperator::template apply<Vector>::type... > type;
      };

      //---| transform

      template< typename, typename, typename > struct binary_transform { /* unspecified */ };

      template< typename...VectorA, typename...VectorB, class BinaryScalarOperator >
      struct binary_transform< vector< VectorA... >, vector< VectorB... >, BinaryScalarOperator >
      {
        typedef vector< typename BinaryScalarOperator::template apply< VectorA, VectorB>::type... > type;
      };

      //---| function

      template< template< typename... > class Function >
      struct function
      {
        template< typename...Parameters >
        struct apply { typedef typename Function< Parameters... >::type type; };
      };

  } // of meta::
} // of utk::
