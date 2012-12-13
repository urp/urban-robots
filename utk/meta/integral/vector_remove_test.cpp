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

# include "utk/meta/integral/vector_remove.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE meta::integral::vector remove
#include <boost/test/unit_test.hpp>

using namespace utk::meta::integral;

BOOST_AUTO_TEST_SUITE( check_remove )

  BOOST_AUTO_TEST_CASE( check_remove_false )
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

  BOOST_AUTO_TEST_CASE( check_remove_at )
  {
    typedef vector< int, 1,2,3,4,5 >  vec;

    typedef typename remove_at< vec, 1 >::type result;

    static const unsigned nsize = result::size;
    BOOST_CHECK_EQUAL( nsize, 4 );

    static const int n0 = at< result, 0 >::value;
    BOOST_CHECK_EQUAL( n0, 1 );
    static const int n1 = at< result, 1 >::value;
    BOOST_CHECK_EQUAL( n1, 3 );
    static const int n2 = at< result, 2 >::value;
    BOOST_CHECK_EQUAL( n2, 4 );
    static const int n3 = at< result, 3 >::value;
    BOOST_CHECK_EQUAL( n3, 5 );
  }

BOOST_AUTO_TEST_SUITE_END()
