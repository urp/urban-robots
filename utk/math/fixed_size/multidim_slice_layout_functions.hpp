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

# include "utk/math/fixed_size/multidim_slice_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      //---| product_layout

      // TODO: specify for all layout types (manage index attribs)
      //       vector x vector, vector x tensor and tensor x vector
      template< typename LayoutA, typename LayoutB > struct product_layout { /* unspecified */ };

      template< index_type...IndicesA, size_type...SizesA, index_type...IndicesB, size_type...SizesB >
      struct product_layout< multidim_layout< meta::integral::vector< index_type, IndicesA... >, meta::integral::vector< size_type, SizesA... > >
                           , multidim_layout< meta::integral::vector< index_type, IndicesB... >, meta::integral::vector< size_type, SizesB... > >
                           >
      {
        typedef multidim_slice_layout< index_vector< IndicesA..., IndicesB... >
                                     , size_vector< SizesA..., SizesB... >
                                     > type;
      };
    }
  }
}