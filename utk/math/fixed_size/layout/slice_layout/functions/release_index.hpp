/*  release_index.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/layout/slice_layout/functions/fix_index.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace layout
      {
        //---| release_index
        //-----returns a new slice_layout with Index released.

        template< typename, index_type >
        struct release_index { /* unspecified */ };

        template< typename FullLayout, typename FullIndexMask, typename...NewAttributes, index_type UnmaskedIndex >
        class release_index< slice_layout< FullLayout, FullIndexMask, NewAttributes... >, UnmaskedIndex >
        {
            typedef slice_layout< FullLayout, FullIndexMask, NewAttributes... > old_layout; // FullLayout == old_layout::full_layout
            static_assert( UnmaskedIndex < old_layout::full_layout::order, "Index greater or equal than layout order");
            static const index_type index_size = meta::integral::at< typename old_layout::full_layout::sizes, UnmaskedIndex >::value;
          public:
            typedef typename fix_unmasked_index< old_layout, UnmaskedIndex, index_size >::type type;
        };

      } // of layout::
    } // of fixed_size::
  } // of math::
} // of utk::
