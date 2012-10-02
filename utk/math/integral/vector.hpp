/*  bla.h - Copyright Peter Urban 2012

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

#include <boost/mpl/vector_c.hpp>

namespace utk
{
  namespace math
  {
    namespace integral
    {
      //---| vector

      template< typename T, T... Content >
      struct vector
      {
        typedef T value_type;

        static const size_t size = sizeof...(Content);

        typedef boost::mpl::vector_c< T, Content... > mpl_vector_c;

        vector() = default;
      };

    } // of integral::
  } // of math::
} // of utk::
