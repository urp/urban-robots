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

# include "utk/math/fixed_size/tensor_interface.hpp"
# include "utk/math/fixed_size/tensor_array.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      template< typename T, typename MultiDimLayout, variance_type Variance >
      struct make_non_mixed_tensor_interface
      {
	typedef tensor_interface< T, MultiDimLayout
							      , typename integral::make_uniform_vector< variance_type, MultiDimLayout::order, Variance >::type
							      > type;
      };

      template< typename T, typename MultiDimLayout, index_type ContravariantIndices >
      class make_mixed_tensor_interface
      {
	typedef typename integral::make_uniform_vector< variance_type, ContravariantIndices, contravariant >::type contravar;
	typedef typename integral::make_uniform_vector< variance_type, MultiDimLayout::order - ContravariantIndices, covariant >::type covar;

	public:

	  typedef tensor_interface< T, MultiDimLayout
				  , typename integral::concatinate< contravar, covar >::type
				  > type;
      };

      template< typename TensorA, typename TensorB >
      struct product_tensor_array { /* unspecified */ };

      template< typename T, typename LayoutA, typename VariancesA, typename LayoutB, typename VariancesB >
      struct product_tensor_array< tensor_interface<T, LayoutA, VariancesA >
				 , tensor_interface<T, LayoutB, VariancesB >
				 >
      {
	typedef tensor_array< T
			    , typename product_layout< LayoutA, LayoutB >::type
			    , typename integral::concatinate< VariancesA, VariancesB >::type
			    > type;
      };

      // tensor_product

      template< typename T, typename LayoutA, typename LayoutB, typename VariancesA, typename VariancesB >
      auto tensor_product( const tensor_interface<T, LayoutA, VariancesA >& a
			 , const tensor_interface<T, LayoutB, VariancesB >& b
			 )
      -> typename product_tensor_array< tensor_interface<T, LayoutA, VariancesA >
				      , tensor_interface<T, LayoutB, VariancesB >
				      >::type
      {
	typedef typename product_tensor_array< tensor_interface<T, LayoutA, VariancesA >
					     , tensor_interface<T, LayoutB, VariancesB >
					     >::type array_type;
	return array_type();
      }


    } // of fixed_size::
  } // of math::
} // of utk::
