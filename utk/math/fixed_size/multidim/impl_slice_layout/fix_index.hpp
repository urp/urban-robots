/*  multidim_slice_fix_index.h - Copyright Peter Urban 2012

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
      //---| fix_index

      template< typename Layout, index_type FullIndex, index_type Value >
      class fix_unmasked_index { /* unspecified */ };


      //-----returns a new multidim_slice_layout with Index (referring to FullLayout) fixed (to Value)
      template< typename...SliceAttributes, index_type FullIndex, index_type Value >
      class fix_unmasked_index< multidim_slice_layout< SliceAttributes... >, FullIndex, Value >
      {
          typedef multidim_slice_layout< SliceAttributes... > slice_layout;

          static_assert( FullIndex < slice_layout::full_layout::order, "Index greater or equal than multidim order" );

          typedef typename meta::integral::assign< typename slice_layout::full_index_mask, FullIndex, meta::integral::constant< index_type, Value > >::type new_index_mask;
        public:
          typedef multidim_slice_layout< typename slice_layout::full_layout, new_index_mask > type;
      };

      //---| fix_index

      template< typename Layout, index_type FullIndex, index_type Value >
      class fix_index { /* unspecified */ };

      //-----returns a new multidim_slice_layout with Index (referring to SliceLayout) fixed (to Value)
      template< typename...SliceAttributes, index_type MaskedIndex, index_type Value >
      class fix_index< multidim_slice_layout< SliceAttributes... >, MaskedIndex, Value >
      {
          typedef multidim_slice_layout< SliceAttributes... > old_layout;

          static constexpr index_type unmasked_index = helpers::unmask_index< typename old_layout::visibility_mask, MaskedIndex >::value;

        public:
          typedef typename fix_unmasked_index< old_layout, unmasked_index, Value >::type type;
      };

      //-----returns a new multidim_slice_layout with Index (referring to multidim_layout) fixed (to Value)
      template< typename...Attributes, index_type Index, index_type Value >
      class fix_index< multidim_layout< Attributes... >, Index, Value >
      {
          typedef multidim_layout< Attributes... > old_layout;

          typedef typename meta::integral::make_vector< index_type, typename old_layout::sizes >::type default_index_mask;
          typedef multidim_slice_layout< old_layout, default_index_mask > slice_layout;
        public:
          typedef typename fix_unmasked_index< slice_layout, Index, Value >::type type;
      };


    }
  }
}
