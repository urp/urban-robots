/*  product_layout.hpp - Copyright Peter Urban 2012-2013

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

# include "utk/meta/vector_push_front.hpp"
# include "utk/meta/vector_split.hpp"
# include "utk/meta/vector_transform.hpp"

# include "utk/math/fixed_size/layout/generic_layout/generic_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace layout
      {

        template< typename LayoutA, typename LayoutB >
        struct product_layout
        {
          typedef typename meta::integral::concatinate< typename LayoutA::sizes
                                                      , typename LayoutB::sizes >::type new_sizes;
          typedef typename helpers::stride_sequence< new_sizes >::type new_strides;

          typedef typename meta::split< typename LayoutA::attributes, 2 >::second extra_attributesA;
          typedef typename meta::split< typename LayoutB::attributes, 2 >::second extra_attributesB;

          static_assert( extra_attributesA::size == extra_attributesB::size,
                        "Number of extra layout parameters must agree for both layouts" );

          typedef typename meta::binary_transform< extra_attributesA
                                                 , extra_attributesB
                                                 , meta::function< meta::integral::concatinate >
                                                 >::type product_attributes;

          typedef typename meta::push_front< typename meta::push_front< product_attributes, new_strides >::type, new_sizes >::type new_attributes;

          typedef typename make_generic_layout< new_attributes >::type type;
        };

      } // of layout::
    } // of fixed_size::
  } // of math::
} // of utk::
