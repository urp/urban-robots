/*  product_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/tensor/impl_interface/make_interface.hpp"

# include "utk/math/fixed_size/tensor/impl_interface/product.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor::product
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::tensor;

BOOST_AUTO_TEST_SUITE( tensor_product_test )

  BOOST_AUTO_TEST_CASE( check_product_array )
  {
    typedef multidim::layout< multidim::size_vector<3> > layout3;
    typedef typename make_non_mixed_interface< double, layout3, contravariant >::type tensor_a;
    typedef typename make_non_mixed_interface< double, layout3, covariant >::type tensor_b;

    typedef typename product_array< tensor_a, tensor_b >::type product;

    //order
    const index_type order = product::order;
    BOOST_CHECK_EQUAL( order, 2 );

    // variances
    typedef typename product::variances variances;

    const bool dim_0_contravariant = meta::integral::at< variances, 0 >::value == contravariant;
    BOOST_CHECK_EQUAL( dim_0_contravariant, true );

    const bool dim_1_covariant = meta::integral::at< variances, 1 >::value == covariant;
    BOOST_CHECK_EQUAL( dim_1_covariant, true );
  }

  BOOST_AUTO_TEST_CASE( check_product )
  {
    typedef multidim::layout< multidim::size_vector<2> > layout2;
    double data[] = { 1.,2.,3.,4. };
    typedef typename make_non_mixed_interface< double, layout2, contravariant >::type tensor_a_type;
    typedef typename make_non_mixed_interface< double, layout2, covariant >::type tensor_b_type;
    typedef typename product_array< tensor_a_type, tensor_b_type >::type product_type;

    tensor_a_type tensor_a( data );
    tensor_b_type tensor_b( data+2 );

    product_type prod = product( tensor_a, tensor_b );

    const double p00 = prod.at(0,0);
    BOOST_CHECK_EQUAL( p00, 3 );

    const double p01 = prod.at(0,1);
    BOOST_CHECK_EQUAL( p01, 4 );

    const double p10 = prod.at(1,0);
    BOOST_CHECK_EQUAL( p10, 6 );

    const double p11 = prod.at(1,1);
    BOOST_CHECK_EQUAL( p11, 8 );
  }

BOOST_AUTO_TEST_SUITE_END()
