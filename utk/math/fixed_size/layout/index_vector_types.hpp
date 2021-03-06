/*  index_vector_types.hpp - Copyright Peter Urban 2012-2013

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

# include <boost/mpl/at.hpp>

# include "utk/meta/integral/integral.hpp"

# include "utk/math/fixed_size/index_types.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      // TODO: move to layout?

      //namespace layout
      //{

	//-----| bool_vector

	template< bool...Bools >
	using bool_vector = meta::integral::vector< bool, Bools... >;

	//-----| index_vector

	template< index_type... Indices >
	using index_vector = meta::integral::vector< index_type, Indices... >;

	//-----| size_vector

	template< size_type... Sizes >
	using size_vector = meta::integral::vector< size_type, Sizes... >;

	//-----| stride_vector

	template< size_type... Strides >
	using stride_vector = meta::integral::vector< stride_type, Strides... >;

      //}	// of layout::
    } // of fixed_size::
  } // of math::
} // of utk::
