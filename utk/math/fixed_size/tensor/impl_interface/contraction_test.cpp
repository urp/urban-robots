/*  contraction_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/tensor/impl_interface/contraction.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE utk::math::tensor::contraction
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::tensor;

struct product_fixture
{
  typedef typename tensor::make_layout< size_vector< 2,2 >, variance_vector< contravariant,covariant > >::type layout22;
  typedef interface< double, unmanaged_tag, layout22 > tensor_a;

  typedef typename contracted< tensor_a, 0,1 >::type contraction22;
};

BOOST_FIXTURE_TEST_SUITE( check_product, product_fixture )

  BOOST_AUTO_TEST_CASE( check_type )
  {
    //order
    const index_type order = contraction22::order;
    BOOST_CHECK_EQUAL( order, 0 );

  }

  BOOST_AUTO_TEST_CASE( check_components )
  {
    double data[] = { 1.,2.,3.,4. };

    tensor_a t_a( data );

    contraction22 scalar = contraction< tensor_a, 0, 1 >( t_a );

    const double p00 = at( scalar );
    BOOST_CHECK_EQUAL( p00, 5 );
  }

BOOST_AUTO_TEST_SUITE_END()
