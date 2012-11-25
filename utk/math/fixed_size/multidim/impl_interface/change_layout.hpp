/*  change_layout.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_interface/specialized_functions.hpp"

# include "utk/math/fixed_size/multidim/impl_interface/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {
/* same as in  "utk/math/fixed_size/multidim/impl_interface/specialized_functions.hpp"
	template< typename ValueType, typename OldLayout, typename NewLayout >
	struct change_layout< interface< ValueType, OldLayout >, NewLayout >
	{
	  typedef interface< ValueType, NewLayout > type;
	};
*/
      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
