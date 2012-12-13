/*  vector_split_test.cpp - Copyright Peter Urban 2009

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

# include "utk/meta/integral/vector_split.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE meta::integral::vector split
#include <boost/test/unit_test.hpp>

using namespace utk::meta::integral;

struct fixture
{
  typedef vector< int, 1,2,3,4,5 >  vec5;
};

BOOST_FIXTURE_TEST_SUITE( check_split, fixture )

  BOOST_AUTO_TEST_CASE( check_no_split_begin )
  {
    typedef split< vec5, 0 > result;

    static const unsigned sizefirst = result::first::size;
    BOOST_CHECK_EQUAL( sizefirst, 0 );

    static const unsigned sizesecond = result::second::size;
    BOOST_CHECK_EQUAL( sizesecond, 5 );

    static const int n0 = at< result::second, 0 >::value;
    BOOST_CHECK_EQUAL( n0, 1 );
    static const int n1 = at< result::second, 1 >::value;
    BOOST_CHECK_EQUAL( n1, 2 );
    static const int n2 = at< result::second, 2 >::value;
    BOOST_CHECK_EQUAL( n2, 3 );
    static const int n3 = at< result::second, 3 >::value;
    BOOST_CHECK_EQUAL( n3, 4 );
    static const int n4 = at< result::second, 4 >::value;
    BOOST_CHECK_EQUAL( n4, 5 );
  }

  BOOST_AUTO_TEST_CASE( check_no_split_end )
  {
    typedef split< vec5, 5 > result;

    static const unsigned sizefirst = result::first::size;
    BOOST_CHECK_EQUAL( sizefirst, 5 );

    static const int n0 = at< result::first, 0 >::value;
    BOOST_CHECK_EQUAL( n0, 1 );
    static const int n1 = at< result::first, 1 >::value;
    BOOST_CHECK_EQUAL( n1, 2 );
    static const int n2 = at< result::first, 2 >::value;
    BOOST_CHECK_EQUAL( n2, 3 );
    static const int n3 = at< result::first, 3 >::value;
    BOOST_CHECK_EQUAL( n3, 4 );
    static const int n4 = at< result::first, 4 >::value;
    BOOST_CHECK_EQUAL( n4, 5 );

    static const unsigned sizesecond = result::second::size;
    BOOST_CHECK_EQUAL( sizesecond, 0 );
  }

  BOOST_AUTO_TEST_CASE( check_split )
  {
    typedef split< vec5, 3 > result;

    static const unsigned sizefirst = result::first::size;
    BOOST_CHECK_EQUAL( sizefirst, 3 );

    static const int n0 = at< result::first, 0 >::value;
    BOOST_CHECK_EQUAL( n0, 1 );
    static const int n1 = at< result::first, 1 >::value;
    BOOST_CHECK_EQUAL( n1, 2 );
    static const int n2 = at< result::first, 2 >::value;
    BOOST_CHECK_EQUAL( n2, 3 );

    static const unsigned sizesecond = result::second::size;
    BOOST_CHECK_EQUAL( sizesecond, 2 );

    static const int n3 = at< result::second, 0 >::value;
    BOOST_CHECK_EQUAL( n3, 4 );
    static const int n4 = at< result::second, 1 >::value;
    BOOST_CHECK_EQUAL( n4, 5 );
  }

BOOST_AUTO_TEST_SUITE_END()
