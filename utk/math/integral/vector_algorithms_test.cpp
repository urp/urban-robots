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

BOOST_AUTO_TEST_SUITE( unary_transform )

  BOOST_AUTO_TEST_CASE( vector_equal )
  {
    typedef vector< int, 1,2,3 >  A;
    typedef vector< int, 3,2,1 >  B;
    typedef typename equal< A, B >::type result;

    static const bool eq0 = at< result, 0 >::value;
    BOOST_CHECK( !eq0 );
    static const bool eq1 = at< result, 1 >::value;
    BOOST_CHECK(  eq1 );
    static const bool eq2 = at< result, 2 >::value;
    BOOST_CHECK( !eq2 );

    typedef vector< int, 1,1,3 >  A2;
    typedef vector< int, 1,2,3 >  B2;
    typedef typename equal< A2, B2 >::type result2;

    static const bool eq20 = at< result2, 0 >::value;
    BOOST_CHECK(  eq20 );
    static const bool eq21 = at< result2, 1 >::value;
    BOOST_CHECK( !eq21 );
    static const bool eq22 = at< result2, 2 >::value;
    BOOST_CHECK(  eq22 );
  }

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

  BOOST_AUTO_TEST_CASE( vector_inner_product )
  {
    typedef vector< int, 1,2,3,4,5 >  a;

    static const int result = inner_product_with_arguments< a >( 3,0,0,1,1);
    BOOST_CHECK_EQUAL( result, 12 );

  }


BOOST_AUTO_TEST_SUITE_END()
