/*  vector_functions_test.cpp - Copyright Peter Urban 2009

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

# include "utk/math/integral/vector_algorithms.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector algorithms
#include <boost/test/unit_test.hpp>

using namespace utk::math::integral;

BOOST_AUTO_TEST_SUITE( unary_transforms )

  BOOST_AUTO_TEST_CASE( vector_negate )
  {
    typedef vector< bool, true,false,true > bools;
    typedef typename negate< bools >::type  result;
    static const int r0 = at< result, 0 >::value;
    BOOST_CHECK_EQUAL( r0,  false );
    static const int r1 = at< result, 1 >::value;
    BOOST_CHECK_EQUAL( r1,  true );
    static const int r2 = at< result, 2 >::value;
    BOOST_CHECK_EQUAL( r2,  false );

  }

  BOOST_AUTO_TEST_CASE( vector_is_true )
  {
    typedef vector< bool, true,false,true > bools;
    typedef typename is_true< bools >::type  result;
    static const bool r0 = at< result, 0 >::value;
    BOOST_CHECK(  r0 );
    static const bool r1 = at< result, 1 >::value;
    BOOST_CHECK( !r1 );
    static const bool r2 = at< result, 2 >::value;
    BOOST_CHECK(  r2 );
  }


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( binary_transforms )

  BOOST_AUTO_TEST_CASE( vector_multiply )
  {
    typedef vector< int, 1,2, 3 >  A;
    typedef vector< int, 3,2,-1 >  B;
    typedef typename multiply< A, B >::type result;

    static const int r0 = at< result, 0 >::value;
    BOOST_CHECK_EQUAL( r0,  3 );
    static const int r1 = at< result, 1 >::value;
    BOOST_CHECK_EQUAL( r1,  4 );
    static const int r2 = at< result, 2 >::value;
    BOOST_CHECK_EQUAL( r2, -3 );
  }

  BOOST_AUTO_TEST_CASE( vector_add )
  {
    typedef vector< int, 1,2, 3 >  A;
    typedef vector< int, 3,2,-1 >  B;
    typedef typename add< A, B >::type result;

    static const int r0 = at< result, 0 >::value;
    BOOST_CHECK_EQUAL( r0,  4 );
    static const int r1 = at< result, 1 >::value;
    BOOST_CHECK_EQUAL( r1,  4 );
    static const int r2 = at< result, 2 >::value;
    BOOST_CHECK_EQUAL( r2,  2 );
  }

  BOOST_AUTO_TEST_CASE( vector_conjunction )
  {
    typedef vector< bool, true,false,true >  A;
    typedef vector< bool, false,false,true >  B;

    typedef typename conjunction< A, B >::type AandB;

    static const bool AandB0 = at< AandB, 0 >::value;
    BOOST_CHECK( !AandB0 );
    static const bool AandB1 = at< AandB, 1 >::value;
    BOOST_CHECK( !AandB1 );
    static const bool AandB2 = at< AandB, 2 >::value;
    BOOST_CHECK(  AandB2 );

    typedef typename conjunction< A, A >::type AandA;

    static const bool AandA0 = at< AandA, 0 >::value;
    BOOST_CHECK( AandA0 );
    static const bool AandA1 = at< AandA, 1 >::value;
    BOOST_CHECK( !AandA1 );
    static const bool AandA2 = at< AandA, 2 >::value;
    BOOST_CHECK( AandA2 );
  }

  BOOST_AUTO_TEST_CASE( vector_equal )
  {
    typedef vector< int, 1,2,3 >  A;
    typedef vector< int, 3,2,1 >  B;
    typedef typename equal< A, B >::type AeqB;

    static const bool AeqB0 = at< AeqB, 0 >::value;
    BOOST_CHECK( !AeqB0 );
    static const bool AeqB1 = at< AeqB, 1 >::value;
    BOOST_CHECK(  AeqB1 );
    static const bool AeqB2 = at< AeqB, 2 >::value;
    BOOST_CHECK( !AeqB2 );

    typedef typename equal< A, A >::type AeqA;

    static const bool AeqA0 = at< AeqA, 0 >::value;
    BOOST_CHECK( AeqA0 );
    static const bool AeqA1 = at< AeqA, 1 >::value;
    BOOST_CHECK( AeqA1 );
    static const bool AeqA2 = at< AeqA, 2 >::value;
    BOOST_CHECK( AeqA2 );

  }

  BOOST_AUTO_TEST_CASE( vector_all )
  {
    typedef vector< int, 1,2,3 >  A;
    typedef vector< int, 3,2,1 >  B;
    typedef vector< int, 1,2,3 >  C;

    static const bool AeqB = all< typename equal< A, B >::type >::value;
    BOOST_CHECK( !AeqB );

    static const bool AeqC = all< equal< A, C >::type >::value;
    BOOST_CHECK( AeqC );

    static const bool AeqA = all< equal< A, A >::type >::value;
    BOOST_CHECK( AeqA );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( conditional_remove )

  BOOST_AUTO_TEST_CASE( vector_remove_false )
  {
    typedef vector< int, 1,2,3,4,5 >  vec;
    typedef vector< bool, true,false,true,false,true >  predicates;

    typedef typename remove_false< vec, predicates >::type result;

    static const unsigned nsize = result::size;
    BOOST_CHECK_EQUAL( nsize, 3 );

    static const int n0 = at< result, 0 >::value;
    BOOST_CHECK_EQUAL( n0, 1 );
    static const int n1 = at< result, 1 >::value;
    BOOST_CHECK_EQUAL( n1, 3 );
    static const int n2 = at< result, 2 >::value;
    BOOST_CHECK_EQUAL( n2, 5 );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( miscellanious )

  BOOST_AUTO_TEST_CASE( vector_reverse )
  {
    typedef vector< int, 1,2,3 >  forward;
    typedef typename reverse< forward >::type backward;

    static const int b0 = at< backward, 0 >::value;
    BOOST_CHECK_EQUAL( b0, 3 );
    static const int b1 = at< backward, 1 >::value;
    BOOST_CHECK_EQUAL( b1, 2 );
    static const int b2 = at< backward, 2 >::value;
    BOOST_CHECK_EQUAL( b2, 1 );

  }

  BOOST_AUTO_TEST_CASE( vector_inner_product )
  {
    typedef vector< int, 1,2,3,4,5 >  a;

    static const int result = inner_product_with_arguments< a >( 3,0,0,1,1);
    BOOST_CHECK_EQUAL( result, 12 );

  }

BOOST_AUTO_TEST_SUITE_END()
