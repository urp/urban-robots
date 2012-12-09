/*  product_layout.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_layout/product_layout.hpp"

# include "utk/math/fixed_size/multidim/impl_slice_layout/slice_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {
        /*
        template< typename...AttributesA, typename...AttributesB >
        struct product_layout< slice_layout< AttributesA... >, slice_layout< AttributesB... > >
        {
        };

        template< typename...AttributesA, typename...AttributesB >
        struct product_layout< layout< AttributesA... >, slice_layout< AttributesB... > >
        {
        };

        template< typename...AttributesA, typename...AttributesB >
        struct product_layout< slice_layout< AttributesA... >, layout< AttributesB... > >
        {
        };
        */
      }
    }
  }
}
