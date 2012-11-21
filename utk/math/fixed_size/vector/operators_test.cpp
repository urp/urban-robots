/*  operators.cpp - Copyright Peter Urban 2009

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

# include "utk/math/fixed_size/vector/operators.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector operators
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::vector;

// TODO: use fixtures

BOOST_AUTO_TEST_CASE( check_comparison_operators )
{
  double data_one[] { 1., 2., 3. };
  const interface<double,3> one( data_one );
  double data_two[] { 1., 2., 3. };
  const interface<double,3> two( data_two );

  double data_gt_one[] { 1., 2.2, 3. };
  const interface<double,3> gt_one( data_gt_one );

  double data_gt_all[] { 1.1, 2.2, 3.3 };
  const interface<double,3> gt_all( data_gt_all );

  double data_lt_one[] { 1., 0.2, 3. };
  const interface<double,3> lt_one( data_lt_one );

  double data_lt_all[] { 0.1, 0.2, 0.3 };
  const interface<double,3> lt_all( data_lt_all );

  bool data_true_all[]  { true, true, true };
  const interface<bool,3>  true_all( data_true_all );

  bool data_false_all[] { false, false, false };
  const interface<bool,3> false_all( data_false_all );

  bool data_true_one[]  { false, true, false };
  const interface<bool,3>  true_one( data_true_one );

  bool data_false_one[] { true, false, true };
  const interface<bool,3> false_one( data_false_one );

  // check vector-scalar equality operator
  BOOST_CHECK_EQUAL(  true_all ==  true, true );
  BOOST_CHECK_EQUAL(  true_all == false, false );
  BOOST_CHECK_EQUAL( false_all ==  true, false );
  BOOST_CHECK_EQUAL( false_all == false,  true );
  BOOST_CHECK_EQUAL(  true_one ==  true, false );
  BOOST_CHECK_EQUAL(  true_one == false, false );
  BOOST_CHECK_EQUAL( false_one == false, false );
  BOOST_CHECK_EQUAL( false_one ==  true, false );

  //equal
  BOOST_CHECK_EQUAL( one == two, true );
  BOOST_CHECK_EQUAL( one != two, false );

  BOOST_CHECK_EQUAL( one == two,  true_all );
  BOOST_CHECK_EQUAL( one != two, false_all );
  BOOST_CHECK_EQUAL( one >= two,  true_all );
  BOOST_CHECK_EQUAL( one <= two,  true_all );
  BOOST_CHECK_EQUAL( one >  two, false_all );
  BOOST_CHECK_EQUAL( one <  two, false_all );

  //compare with - one less
  BOOST_CHECK_EQUAL( one == lt_one, false_one );
  BOOST_CHECK_EQUAL( one != lt_one,  true_one );
  BOOST_CHECK_EQUAL( one >= lt_one,  true_all );
  BOOST_CHECK_EQUAL( one <= lt_one, false_one );
  BOOST_CHECK_EQUAL( one >  lt_one,  true_one );
  BOOST_CHECK_EQUAL( one <  lt_one, false_all );

  //compare with - one greater
  BOOST_CHECK_EQUAL( one == gt_one, false_one );
  BOOST_CHECK_EQUAL( one != gt_one,  true_one );
  BOOST_CHECK_EQUAL( one >= gt_one, false_one );
  BOOST_CHECK_EQUAL( one <= gt_one,  true_all );
  BOOST_CHECK_EQUAL( one >  gt_one, false_all );
  BOOST_CHECK_EQUAL( one <  gt_one,  true_one );

  //compare with - all less
  BOOST_CHECK_EQUAL( one == lt_all, false_all );
  BOOST_CHECK_EQUAL( one != lt_all,  true_all );
  BOOST_CHECK_EQUAL( one >= lt_all,  true_all );
  BOOST_CHECK_EQUAL( one <= lt_all, false_all );
  BOOST_CHECK_EQUAL( one >  lt_all,  true_all );
  BOOST_CHECK_EQUAL( one <  lt_all, false_all );

  //compare with - all greater
  BOOST_CHECK_EQUAL( one == gt_all, false_all );
  BOOST_CHECK_EQUAL( one != gt_all,  true_all );
  BOOST_CHECK_EQUAL( one >= gt_all, false_all );
  BOOST_CHECK_EQUAL( one <= gt_all,  true_all );
  BOOST_CHECK_EQUAL( one >  gt_all, false_all );
  BOOST_CHECK_EQUAL( one <  gt_all,  true_all );

  // unitary
  BOOST_CHECK_EQUAL( !true_one, false_one );
}

BOOST_AUTO_TEST_CASE( vecn_arithmetic_operators )
{
  double data_a[] { 1., 2., 3. };
  const interface<double,3> a( data_a );
  double data_b[] { 2., 4., 6. };
  const interface<double,3> b( data_b );
  const double s = 2.1;

  // unitary
  double data_a_negative[] { -1., -2., -3. };
  const interface<double,3> a_negative( data_a_negative );
  BOOST_CHECK_EQUAL( -a, a_negative );

  // plus
  double data_a_plus_b[] { 1.+2., 2.+4., 3.+6. };
  const interface<double,3> a_plus_b( data_a_plus_b );
  double data_a_plus_s[] { 1.+s, 2.+s, 3.+s };
  const interface<double,3> a_plus_s( data_a_plus_s );
  array<double,3> a_plus(a);
  array<double,3> s_plus(a);
  BOOST_CHECK_EQUAL( a      +  b, a_plus_b );
  BOOST_CHECK_EQUAL( a_plus += b, a_plus_b );
  BOOST_CHECK_EQUAL( a      +  s, a_plus_s );
  BOOST_CHECK_EQUAL( s_plus +  s, a_plus_s );

  // minus
  double data_a_minus_b[] { 1.-2., 2.-4., 3.-6. };
  const interface<double,3> a_minus_b( data_a_minus_b );
  double data_a_minus_s[] { 1.-s, 2.-s, 3.-s };
  const interface<double,3> a_minus_s( data_a_minus_s );
  array<double,3> a_minus(a);
  array<double,3> s_minus(a);
  BOOST_CHECK_EQUAL( a       -  b, a_minus_b );
  BOOST_CHECK_EQUAL( a_minus -= b, a_minus_b );
  BOOST_CHECK_EQUAL( a       -  s, a_minus_s );
  BOOST_CHECK_EQUAL( s_minus -  s, a_minus_s );

  // multiply
  double data_a_mult_b[] { 1.*2., 2.*4., 3.*6. };
  const interface<double,3> a_mult_b( data_a_mult_b );
  double data_a_mult_s[] { 1.*s, 2.*s, 3.*s };
  const interface<double,3> a_mult_s( data_a_mult_s );
  array<double,3> a_mult(a);
  array<double,3> s_mult(a);
  BOOST_CHECK_EQUAL( a      *  b, a_mult_b );
  BOOST_CHECK_EQUAL( a_mult *= b, a_mult_b );
  BOOST_CHECK_EQUAL( a      *  s, a_mult_s );
  BOOST_CHECK_EQUAL( s_mult *  s, a_mult_s );

  // divide
  double data_a_div_b[] { 1./2., 2./4., 3./6. };
  const interface<double,3> a_div_b( data_a_div_b );
  double data_a_div_s[] { 1./s, 2./s, 3./s };
  const interface<double,3> a_div_s( data_a_div_s );
  array<double,3> a_div(a);
  array<double,3> s_div(a);
  BOOST_CHECK_EQUAL( a     /  b, a_div_b );
  BOOST_CHECK_EQUAL( a_div /= b, a_div_b );
  BOOST_CHECK_EQUAL( a     /  s, a_div_s );
  BOOST_CHECK_EQUAL( s_div /  s, a_div_s );

}
