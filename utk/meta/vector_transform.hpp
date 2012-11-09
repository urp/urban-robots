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


      //---| function_operator

      template< template<class> class Function >
      struct function_operator
      {
        template< typename Value >
        struct apply
        { typedef typename Function< Value >::type type; };
      };


  } // of meta::
} // of utk::
