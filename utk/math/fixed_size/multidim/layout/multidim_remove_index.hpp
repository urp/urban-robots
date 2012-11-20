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

# include "utk/math/fixed_size/multidim_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      //---| remove_index
      //-----returns a new multidim_layout with Index fixed (to Value)
      // TODO: tests
      template< typename Layout, index_type Index >
      struct remove_index { /* unspecified */ };

      template< typename SizeVector, typename StrideVector, typename...MoreAttributes, index_type Index>
      struct remove_index< multidim_layout< SizeVector, StrideVector, MoreAttributes... >, Index >
      {
        typedef multidim_layout< SizeVector, StrideVector, MoreAttributes... > old_layout;

        static_assert( Index < old_layout::order, "Index greater or equal than multidim order");

        template< typename Vector >
        using remove_attrib = meta::integral::remove_at< Vector, Index >;

        typedef typename meta::transform< typename old_layout::attributes , meta::function<remove_attrib> >::type new_attributes;

        typedef typename make_multidim_layout< new_attributes >::type type;
      };

    }
  }
}
