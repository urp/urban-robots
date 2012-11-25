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

//# include "utk/math/fixed_size/interface.hpp"
# include "utk/math/fixed_size/tensor/impl_array/array.hpp"
# include "utk/math/fixed_size/multidim/layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace tensor
      {

	template< typename TensorA, typename TensorB >
	struct product_array { /* unspecified */ };

	template< typename T, typename LayoutA, typename VariancesA, typename LayoutB, typename VariancesB >
	struct product_array< interface<T, LayoutA, VariancesA >
			    , interface<T, LayoutB, VariancesB >
			    >
	{
	  typedef array< T
		       , typename multidim::product_layout< LayoutA, LayoutB >::type
		       , typename meta::integral::concatinate< VariancesA, VariancesB >::type
		       > type;
	};

	// product

	template< typename T, typename LayoutA, typename LayoutB, typename VariancesA, typename VariancesB >
	auto product( const interface<T, LayoutA, VariancesA >& a
		    , const interface<T, LayoutB, VariancesB >& b
		    )
	-> typename product_array< interface<T, LayoutA, VariancesA >
				 , interface<T, LayoutB, VariancesB >
				 >::type
	{
	  typedef typename product_array< interface<T, LayoutA, VariancesA >
				        , interface<T, LayoutB, VariancesB >
				        >::type array_type;
	  array_type result;

	  //result

	  return result;
	}

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
