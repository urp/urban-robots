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

# include "utk/math/fixed_size/multidim/interface.hpp"
# include "utk/math/fixed_size/tensor/impl_array/array.hpp"
# include "utk/math/fixed_size/tensor/impl_interface/at.hpp"
# include "utk/math/fixed_size/tensor/impl_interface/operators/multiply.hpp"

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

	template< typename T, typename LayoutA, typename LayoutB >
	struct product_array< interface<T, LayoutA >
			    , interface<T, LayoutB >
			    >
	{
	  typedef array< T
		       , typename multidim::product_layout< LayoutA, LayoutB >::type
		       > type;
	};

	//---| assign_product

	template< typename ItA, typename ItEndA, typename B, typename Result >
	auto assign_product( Result& result, const ItA& ita, const ItEndA& itenda, const B& b )
	-> void
	{
	  std::cerr << "utk::math::fixed_size::tensor::assign_product | current "<< typename ItA::current_indices() << std::endl;

	  auto res_part = at( result, typename ItA::current_indices() );
	  auto val_part = b * typename Result::value_type(*ita) ;

	  res_part = val_part;

	  assign_product( result, ita.next(), itenda, b ) ;
	}

	template< typename ItEndA, typename B, typename Result >
	auto assign_product( Result& result, const ItEndA& ita, const ItEndA& itenda, const B& b )
	-> void
	{ }


	//---| product

	template< typename T, typename LayoutA, typename LayoutB >
	auto product( const interface<T, LayoutA >& a
		    , const interface<T, LayoutB >& b
		    )
	-> typename product_array< interface<T, LayoutA >, interface<T, LayoutB > >::type
	{
	  typedef typename product_array< interface<T, LayoutA >, interface<T, LayoutB > >::type type;
	  type result;

	  assign_product( result, a.begin(), a.end(), b );

	  std::cerr << "utk::math::fixed_size::tensor::product | result -> " << std::endl << result;

	  return result;
	}

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
