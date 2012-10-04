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

      //---| product_layout

      // TODO: specify for vector x vector, vector x tensor and tensor x vector
      // TODO: specialize for multidim_slice_layout
      template< typename LayoutA, typename LayoutB > struct product_layout { /* unspecified */ };

      template< index_type...StridesA, size_type...SizesA, index_type...StridesB, size_type...SizesB >
      struct product_layout< multidim_layout< integral::vector< size_type, SizesA... >, integral::vector< stride_type, StridesA... > >
                           , multidim_layout< integral::vector< size_type, SizesB... >, integral::vector< stride_type, StridesB... > >
                           >
      {
        typedef multidim_layout< size_vector< SizesA..., SizesB... >
                               , stride_vector< StridesA..., StridesB... >
                               > type;
      };
    }
  }
}
