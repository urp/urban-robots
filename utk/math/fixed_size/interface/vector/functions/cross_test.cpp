/*  cross_test.cpp - Copyright Peter Urban 2009

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

# include "utk/math/fixed_size/interface/vector/functions/cross.hpp"
# include "utk/math/fixed_size/interface/vector/operators.hpp"


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE fixed_size::interface::vector cross
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::interface::vector;

//-----| cross
BOOST_AUTO_TEST_CASE( check_cross )
{
  double data_a[] { 2., 0., 1. };
  const interface< double, 3 > a( data_a );

  double data_b[] { 0., 1., 0. };
  const interface< double, 3 > b( data_b );

  double data_c[] { M_PI, 3.3125, 1./3. };
  const interface< double, 3 > c( data_c );

  array< double, 3 > a_cross_b{ 0.*0.-1.*1., 1.*0.-2.*0., 2.*1.-0.*0. };

  BOOST_CHECK_EQUAL( cross( a, a ), 0. );
  BOOST_CHECK_EQUAL( cross( a, b ),  a_cross_b );
  BOOST_CHECK_EQUAL( cross( b, a ), -a_cross_b );

  BOOST_CHECK_EQUAL( cross( a * 3., c * 2. ), cross( a, c ) * 3. * 2. );
}

//-----| cross3
BOOST_AUTO_TEST_CASE( check_cross3 )
{
  double data_a[] { 2., 0., 1. };
  const interface< double, 3 > a( data_a );

  double data_b[] { 0., 1., 0. };
  const interface< double, 3 > b( data_b );

  double data_c[] { M_PI, 3.3125, 1./3. };
  const interface< double, 3 > c( data_c );

  BOOST_CHECK_EQUAL( cross( a, cross( b, c ) ), cross3( a, b, c ) );
  BOOST_CHECK_EQUAL( cross3( a,b,c ) + cross3( c,a,b ) + cross3( b,c,a ), 0. );
}
