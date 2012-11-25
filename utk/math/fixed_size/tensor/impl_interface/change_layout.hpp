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

# include "utk/math/fixed_size/tensor/impl_interface/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace tensor
      {
	//:::| type |::::::::::::::::::::::::::::::::::::::::::::::::::/

	template< typename ValueType, typename OldLayout, typename VarianceVector, typename NewLayout >
	struct change_layout< interface< ValueType, OldLayout, VarianceVector >, NewLayout >
	{
	  typedef interface< ValueType, NewLayout, VarianceVector > type;
	};

      } // of tensor::

      namespace multidim
      {
	template< typename ValueType, typename OldLayout, typename VarianceVector, typename NewLayout >
	struct change_layout< tensor::interface< ValueType, OldLayout, VarianceVector >, NewLayout >
	{
	  typedef typename tensor::change_layout< tensor::interface< ValueType, OldLayout, VarianceVector >, NewLayout >::type type;
	};
      }
    } // of fixed_size::
  } // of math::
} // of utk::
