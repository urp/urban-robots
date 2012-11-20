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

# include "utk/math/fixed_size/multidim_slice_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      //---| remove_index
      //-----returns a new multidim_slice_layout with Index removed
      // TODO: Well defined place for vvv
      //template< typename Layout, index_type Index >
      //struct remove_index { /*unspecified*/ };

      template< typename...Attributes, index_type MaskedIndex >
      class remove_index< multidim_slice_layout< Attributes... >, MaskedIndex >
      {
          typedef multidim_slice_layout< Attributes... > old_layout;
          static_assert( MaskedIndex < old_layout::order, "Index greater or equal than multidim order");

          // find index in full_layout corresponding to MaskedIndex
          static constexpr index_type full_layout_index = helpers::unmask_index< typename old_layout::visibility_mask, MaskedIndex >::value;

        public:

          //:::| assamble result

          typedef typename remove_index< typename old_layout::full_layout, full_layout_index >::type new_full_layout;
          typedef typename meta::integral::remove_at< typename old_layout::full_index_mask, full_layout_index >::type new_index_mask;

          typedef multidim_slice_layout< new_full_layout, new_index_mask > type;
      };

    }
  }
}
