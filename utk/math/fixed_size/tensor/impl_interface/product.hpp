/*  product.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/vector/vector.hpp"

# include "utk/math/fixed_size/tensor/impl_interface/interface.hpp"

# include "utk/math/fixed_size/tensor/impl_interface/at.hpp"
# include "utk/math/fixed_size/tensor/impl_interface/operators/io.hpp"
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

	template< typename ValueType, typename StorageTagA, typename LayoutA, typename StorageTagB, typename LayoutB >
	struct product_array< interface< ValueType, StorageTagA, LayoutA >
			    , interface< ValueType, StorageTagB, LayoutB >
			    >
	{
	  typedef interface< ValueType
			   , typename storage_traits< StorageTagA >::managed_tag
			   , typename multidim::product_layout< LayoutA, LayoutB >::type
			   > type;
	};

	//---| assign_product

	template< typename ItA, typename ItEndA, typename B, typename Result >
	auto assign_product( Result& result, const ItA& ita, const ItEndA& itenda, const B& b )
	-> void
	{
	  std::cerr << "tensor::assign_product | current indices "<< typename ItA::current_indices() << std::endl;

	  auto res_part = at( result, typename ItA::current_indices() );
	  std::cerr << "  res_part " << res_part << std::endl;
	  auto val_part = b * typename Result::value_type(*ita) ;
	  std::cerr << "  val_part " << res_part << std::endl;

	  res_part = val_part;
	  assign_product( result, ita.next(), itenda, b ) ;
	}

	template< typename ItEndA, typename B, typename Result >
	auto assign_product( Result& result, const ItEndA& ita, const ItEndA& itenda, const B& b )
	-> void
	{ }


	//---| product

	template< typename ValueType, typename StorageTagA, typename LayoutA, typename StorageTagB, typename LayoutB >
	auto product( const interface< ValueType, StorageTagA, LayoutA >& a
		    , const interface< ValueType, StorageTagB, LayoutB >& b
		    )
	-> typename product_array< interface< ValueType, StorageTagA, LayoutA >, interface< ValueType, StorageTagB, LayoutB > >::type//product_array< decltype(a), decltype(b) >::type
	{
	  typedef typename //product_array< decltype(a), decltype(b) >::type
	  product_array< interface< ValueType, StorageTagA, LayoutA >, interface< ValueType, StorageTagB, LayoutB > >::type type;
	  type result;

	  std::cerr << "utk::math::fixed_size::tensor::product | result -> " << std::endl << result;

	  assign_product( result, a.begin(), a.end(), b );

	  std::cerr << "utk::math::fixed_size::tensor::product | result -> " << std::endl << result;

	  return result;
	}

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
