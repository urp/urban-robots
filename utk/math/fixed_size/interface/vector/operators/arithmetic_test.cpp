/*  arthmetic_test.cpp - Copyright Peter Urban 2009-2013

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

# include "utk/math/fixed_size/interface/vector/operators/arithmetic.hpp"

# include "utk/math/fixed_size/interface/vector/operators/comparison.hpp"
# include "utk/math/fixed_size/interface/vector/operators/io.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector operators
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::interface::vector;

struct fixture
{
  double data_a[3];
  const interface<double,3> a;
  double data_b[3] ;
  const interface<double,3> b;
  const double s = 2.1 ;
  // plus
  double data_a_plus_b[3];
  const interface<double,3> a_plus_b;
  double data_a_plus_s[3];
  const interface<double,3> a_plus_s;
  // minus
  double data_a_minus_b[3];
  const interface<double,3> a_minus_b;
  double data_a_minus_s[3];
  const interface<double,3> a_minus_s;
  // mult
  double data_a_mult_b[3];
  const interface<double,3> a_mult_b;
  double data_a_mult_s[3];
  const interface<double,3> a_mult_s;
  // div
  double data_a_div_b[3];
  const interface<double,3> a_div_b;
  double data_a_div_s[3];
  const interface<double,3> a_div_s;

  fixture()
  : data_a{ 1., 2., 3. }, a(data_a)
  , data_b{ 2., 4., 6. }, b(data_b)
  , data_a_plus_b { 1.+2.  , 2.+4.  , 3.+6.  }, a_plus_b ( data_a_plus_b )
  , data_a_plus_s { 1.+2.1 , 2.+2.1 , 3.+2.1 }, a_plus_s ( data_a_plus_s )
  , data_a_minus_b{ 1.-2.  , 2.-4.  , 3.-6.  }, a_minus_b( data_a_minus_b )
  , data_a_minus_s{ 1.-2.1 , 2.-2.1 , 3.-2.1 }, a_minus_s( data_a_minus_s )
  , data_a_mult_b { 1.*2.  , 2.*4.  , 3.*6.  }, a_mult_b ( data_a_mult_b )
  , data_a_mult_s { 1.*2.1 , 2.*2.1 , 3.*2.1 }, a_mult_s ( data_a_mult_s )
  , data_a_div_b  { 1./2.  , 2./4.  , 3./6.  }, a_div_b  ( data_a_div_b )
  , data_a_div_s  { 1./2.1 , 2./2.1 , 3./2.1 }, a_div_s  ( data_a_div_s )
  { }
};

BOOST_FIXTURE_TEST_SUITE( check_arithmetic_operators, fixture )

BOOST_AUTO_TEST_CASE( check_negate_operator )
{
  // unitary
  double data_a_negative[] { -1., -2., -3. };
  const interface<double,3> a_negative( data_a_negative );
  BOOST_CHECK_EQUAL( -a, a_negative );
}

BOOST_AUTO_TEST_CASE( check_plus_operators )
{
  // plus

  array<double,3> a_plus(a);
  array<double,3> s_plus(a);
  BOOST_CHECK_EQUAL( a      +  b, a_plus_b );
  BOOST_CHECK_EQUAL( a_plus += b, a_plus_b );
  BOOST_CHECK_EQUAL( a      +  s, a_plus_s );
  BOOST_CHECK_EQUAL( s_plus +  s, a_plus_s );

}

BOOST_AUTO_TEST_CASE( check_minus_operators )
{
  // minus
  array<double,3> a_minus(a);
  array<double,3> s_minus(a);
  BOOST_CHECK_EQUAL( a       -  b, a_minus_b );
  BOOST_CHECK_EQUAL( a_minus -= b, a_minus_b );
  BOOST_CHECK_EQUAL( a       -  s, a_minus_s );
  BOOST_CHECK_EQUAL( s_minus -  s, a_minus_s );
}

BOOST_AUTO_TEST_CASE( check_multiply_operators )
{
  // multiply
  array<double,3> a_mult(a);
  array<double,3> s_mult(a);
  BOOST_CHECK_EQUAL( a      *  b, a_mult_b );
  BOOST_CHECK_EQUAL( a_mult *= b, a_mult_b );
  BOOST_CHECK_EQUAL( a      *  s, a_mult_s );
  BOOST_CHECK_EQUAL( s_mult *  s, a_mult_s );
}

BOOST_AUTO_TEST_CASE( check_divide_operators )
{
  // divide
  array<double,3> a_div(a);
  array<double,3> s_div(a);
  BOOST_CHECK_EQUAL( a     /  b, a_div_b );
  BOOST_CHECK_EQUAL( a_div /= b, a_div_b );
  BOOST_CHECK_EQUAL( a     /  s, a_div_s );
  BOOST_CHECK_EQUAL( s_div /  s, a_div_s );

}

BOOST_AUTO_TEST_SUITE_END()
