/*  is_memory_structure_equivalent.hpp - Copyright Peter Urban 2012-2013

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

# include "utk/meta/integral/integral.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace layout
      {

        template< typename Layout, typename OtherLayout >
        class is_memory_structure_equivalent
        {
            // trim attributes
            static constexpr size_type min_size = Layout::order > OtherLayout::order ? OtherLayout::order : Layout::order;

            typedef typename meta::integral::split< typename Layout::sizes, min_size >::first trimmed_size1;
            typedef typename meta::integral::split< typename OtherLayout::sizes, min_size >::first trimmed_size2;

            typedef typename meta::integral::split< typename Layout::strides, min_size >::first trimmed_strides1;
            typedef typename meta::integral::split< typename OtherLayout::strides, min_size >::first trimmed_strides2;

          public:

            // compare order, sizes and variances for equality
            static constexpr bool value = Layout::order == OtherLayout::order
                                          and meta::integral::all< typename meta::integral::equal< trimmed_size1
                                                                                                 , trimmed_size2 >::type
                                                                 >::value
                                          and meta::integral::all< typename meta::integral::equal< trimmed_strides1
                                                                                                 , trimmed_strides2 >::type
                                                                 >::value;
        };

      } // of layout::
    } // of fixed_size
  } // of math::
} // of utk::
