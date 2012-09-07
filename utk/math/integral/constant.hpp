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

# include <type_traits>

namespace utk
{
  namespace math
  {
    namespace integral
    {

      //---| constant
      //-----stores an integral constant value

      template<typename T, T Value>
      struct constant
      {
        static_assert( std::is_fundamental< T >::value
                      , "utk::math::integral::constant is supposed to store "
                        "only integral constants (fundamental types)" );

        typedef const T value_type;

        static const T value = Value;
      };

    } // of integral::
  } // of math::
} // of utk::
