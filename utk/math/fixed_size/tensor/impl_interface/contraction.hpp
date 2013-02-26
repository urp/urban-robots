/*  contracton.h - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/tensor/impl_interface/at.hpp"
# include "utk/math/fixed_size/tensor/impl_interface/operators/plus.hpp"
# include "utk/math/fixed_size/tensor/impl_interface/operators/io.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace tensor
      {

	template< typename Tensor, index_type Index, index_type DualIndex >
	struct contracted { /* unspecified */ };

	template< typename ValueType, typename StorageTag, typename Layout, index_type Index, index_type DualIndex >
	struct contracted< interface< ValueType, StorageTag, Layout >, Index, DualIndex >
	{
	  typedef typename interface< ValueType, StorageTag, Layout >::layout::sizes sizes;
	  typedef typename interface< ValueType, StorageTag, Layout >::variances variances;

	  static_assert( meta::integral::at< variances, Index >::value == contravariant
		       , "template parameter Index must be contravariant" );

	  static_assert( meta::integral::at< variances, DualIndex >::value == covariant
		       , "template parameter DualIndex must be covariant" );

	  static_assert( meta::integral::at< sizes, Index >::value == meta::integral::at< sizes, DualIndex >::value
		       , "Contracted indeces have diffents size," );


	  typedef typename multidim::remove_index< Layout, DualIndex >::type dual_removed;
	  typedef typename multidim::remove_index< dual_removed, Index >::type contracted_layout;

	  typedef typename multidim::replace_strides< contracted_layout >::type new_layout;

	  typedef interface< ValueType
			   , typename storage_traits< StorageTag >::managed_tag
			   , new_layout
			   //, contracted_layout
			   > type;
	};

	//---| assign_contraction

	template< size_type Size, index_type Index, index_type DualIndex, index_type IndexValue >
	struct assign_contraction
	{

	  template< typename Tensor, typename Result >
	  static auto apply( const Tensor& A, Result& result ) -> void
	  {
	    std::cerr << "tensor::assign_contraction | current "<< IndexValue << " ---------------------------------------" << std::endl;

	    typedef typename Tensor::layout::sizes sizes;

	    // fix Index an DualIndex

	    typedef typename meta::integral::make_vector< index_type, sizes >::type all_free;
	    typedef typename meta::integral::assign< all_free, Index, meta::integral::constant< index_type, IndexValue > >::type index_fixed;
	    typedef typename meta::integral::assign< index_fixed, DualIndex, meta::integral::constant< index_type, IndexValue > >::type index_mask;

	    typedef typename multidim::slice_layout< typename Tensor::layout, index_mask > new_layout;
	    typedef typename interface_traits< typename change_layout< Tensor, new_layout >::type >::unmanaged_interface slice_interface;

	    const slice_interface slice( A.storage );

	    std::cerr << "tensor::assign_contraction | slice "<< slice << std::endl;
	    std::cerr << "tensor::assign_contraction | result "<< result << std::endl;

	    // component-wise sum

	    result += slice;

	    std::cerr << "tensor::assign_contraction | result (new) "<< result << std::endl;

	    assign_contraction< Size, Index, DualIndex, IndexValue+1 >::template apply( A, result ) ;
	  }
	};

	// terminate

	template< size_type Size, index_type Index, index_type DualIndex >
	struct assign_contraction< Size, Index, DualIndex, Size >
	{
	  template< typename Tensor, typename Result >
	  static auto apply( const Tensor& A, Result& result ) -> void
	  { };
	};


	//---| contraction

	template< typename Tensor, index_type Index, index_type DualIndex >
	auto contraction( const Tensor& A )
	-> typename contracted< Tensor, Index, DualIndex >::type
	{
	  typedef typename contracted< Tensor, Index, DualIndex >::type result_type;
	  result_type result;

	  std::fill( result.storage.begin(), result.storage.end(), typename result_type::value_type( 0 ) );

	  static constexpr index_type index_size = meta::integral::at< typename Tensor::layout::sizes, Index >::value;

	  assign_contraction< index_size, Index, DualIndex, 0 >::template apply( A, result );

	  //std::cerr << "utk::math::fixed_size::tensor::contraction | result -> " << std::endl << result;

	  return result;
	}

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
