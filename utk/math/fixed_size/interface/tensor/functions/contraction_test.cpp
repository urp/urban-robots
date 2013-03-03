/*  contraction_test.cpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/interface/vector.hpp"

# include "utk/math/fixed_size/interface/tensor/functions/make_layout.hpp"

# include "utk/math/fixed_size/interface/tensor/functions/contraction.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE utk::math::interface::tensor::contraction
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::interface;
using namespace utk::math::fixed_size::interface::tensor;

struct fixture22
{
  typedef typename make_layout< size_vector< 2,2 >, variance_vector< contravariant,covariant > >::type layout22;
  typedef interface< double, vector::unmanaged_tag, layout22 > tensor22;

  typedef typename contracted< tensor22, 0,1 >::type contraction22;
};

BOOST_FIXTURE_TEST_SUITE( check_contraction22, fixture22 )

  BOOST_AUTO_TEST_CASE( check_type )
  {
    //order
    const index_type order = contraction22::order;
    BOOST_CHECK_EQUAL( order, 0 );
  }

  BOOST_AUTO_TEST_CASE( check_components )
  {
    double data[] = { 1.,2.,3.,4. };

    tensor22 t_a( data );

    contraction22 scalar = contraction< tensor22, 0, 1 >( t_a );

    const double p00 = at( scalar );
    BOOST_CHECK_EQUAL( p00, 5 );
  }

BOOST_AUTO_TEST_SUITE_END()

struct fixture222
{
  typedef typename tensor::make_layout< size_vector< 2,2,2 >, variance_vector< contravariant,covariant,covariant > >::type layout222;
  typedef interface< double, vector::unmanaged_tag, layout222 > tensor222;

  typedef typename contracted< tensor222, 0,2 >::type contraction222;
};

BOOST_FIXTURE_TEST_SUITE( check_contraction222, fixture222 )

  BOOST_AUTO_TEST_CASE( check_type )
  {
    //order
    const index_type order = contraction222::order;
    BOOST_CHECK_EQUAL( order, 1 );
  }

  BOOST_AUTO_TEST_CASE( check_components )
  {
    double data[] = { 1.,2.,3.,4.,5.,6.,7.,8. };

    tensor222 t_a( data );

    contraction222 vec2 = contraction< tensor222, 0, 2 >( t_a );

    BOOST_TEST_MESSAGE( "result: " << vec2 );

    const double c0 = at( vec2, 0 );
    BOOST_CHECK_EQUAL( c0, 7 );
    const double c1 = at( vec2, 1 );
    BOOST_CHECK_EQUAL( c1, 11 );

  }

BOOST_AUTO_TEST_SUITE_END()
