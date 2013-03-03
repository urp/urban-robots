/*  remove_index.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/layout/generic_functions/remove_index.hpp"

# include "utk/math/fixed_size/layout/generic_layout/generic_layout.hpp"

# include "utk/meta/vector_transform.hpp"


namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace layout
      {
        //---| remove_index
        //-----returns a new generic_layout with Index fixed (to Value)

        template< typename SizeVector, typename StrideVector, typename...MoreAttributes, index_type Index>
        struct remove_index< generic_layout< SizeVector, StrideVector, MoreAttributes... >, Index >
        {
          typedef generic_layout< SizeVector, StrideVector, MoreAttributes... > old_layout;

          static_assert( Index < old_layout::order, "Index greater or equal than layout order");

          template< typename Vector >
          using remove_attrib = meta::integral::remove_at< Vector, Index >;

          typedef typename meta::transform< typename old_layout::attributes , meta::function<remove_attrib> >::type new_attributes;

          typedef typename make_generic_layout< new_attributes >::type type;
        };
      } // of layout::
    } // of fixed_size::
  } // of math::
} // of utk::
