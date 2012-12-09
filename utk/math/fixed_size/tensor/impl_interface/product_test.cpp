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

# include "utk/math/fixed_size/tensor/impl_interface/make_layout.hpp"

# include "utk/math/fixed_size/tensor/impl_interface/product.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor::product
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::tensor;

struct product_fixture
{
  typedef multidim::layout< size_vector<2> > layout;
  typedef interface< double, typename make_layout< layout, contravariant_tag >::type > tensor_a;
  typedef interface< double, typename make_layout< layout, covariant_tag     >::type > tensor_b;

  typedef typename product_array< tensor_a, tensor_b >::type product_ab;
};

BOOST_FIXTURE_TEST_SUITE( check_product, product_fixture )

  BOOST_AUTO_TEST_CASE( check_type )
  {
    //order
    const index_type order = product_ab::order;
    BOOST_CHECK_EQUAL( order, 2 );

    // variances
    typedef typename product_ab::variances variances;

    const bool dim_0_contravariant = meta::integral::at< variances, 0 >::value == contravariant;
    BOOST_CHECK_EQUAL( dim_0_contravariant, true );

    const bool dim_1_covariant = meta::integral::at< variances, 1 >::value == covariant;
    BOOST_CHECK_EQUAL( dim_1_covariant, true );
  }

  BOOST_AUTO_TEST_CASE( check_components )
  {
    double data[] = { 1.,2.,3.,4. };

    tensor_a t_a( data );
    tensor_b t_b( data+2 );

    product_ab prod = product( t_a, t_b );

    const double p00 = at( prod, 0,0 );
    BOOST_CHECK_EQUAL( p00, 3 );

    const double p01 = at( prod, 0,1 );
    BOOST_CHECK_EQUAL( p01, 4 );

    const double p10 = at( prod, 1,0 );
    BOOST_CHECK_EQUAL( p10, 6 );

    const double p11 = at( prod, 1,1 );
    BOOST_CHECK_EQUAL( p11, 8 );
  }

BOOST_AUTO_TEST_SUITE_END()
