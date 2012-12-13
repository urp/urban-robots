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

# include "utk/meta/vector_at.hpp"

# include "utk/meta/vector_split.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE meta::vector split
#include <boost/test/unit_test.hpp>

using namespace utk::meta;

struct fixture
{
  typedef vector< int,double,char >  vec3;
};

BOOST_FIXTURE_TEST_SUITE( check_split, fixture )

  BOOST_AUTO_TEST_CASE( check_no_split_begin )
  {
    typedef  split< vec3, 0 > result;

    static const unsigned sizefirst = result::first::size;
    BOOST_CHECK_EQUAL( sizefirst, 0 );

    static const unsigned sizesecond = result::second::size;
    BOOST_CHECK_EQUAL( sizesecond, 3 );

    static const bool b0 = std::is_same< typename at< result::second, 0 >::type, int >::value;
    BOOST_CHECK( b0 );

    static const bool b1 = std::is_same< typename at< result::second, 1 >::type, double >::value;
    BOOST_CHECK( b1 );

    static const bool b2 = std::is_same< typename at< result::second, 2 >::type, char >::value;
    BOOST_CHECK( b2 );
  }

  BOOST_AUTO_TEST_CASE( check_no_split_end )
  {
    typedef split< vec3, 3 > result;

    static const unsigned sizefirst = result::first::size;
    BOOST_CHECK_EQUAL( sizefirst, 3 );

    static const bool b0 = std::is_same< typename at< result::first, 0 >::type, int >::value;
    BOOST_CHECK( b0 );

    static const bool b1 = std::is_same< typename at< result::first, 1 >::type, double >::value;
    BOOST_CHECK( b1 );

    static const bool b2 = std::is_same< typename at< result::first, 2 >::type, char >::value;
    BOOST_CHECK( b2 );

    static const unsigned sizesecond = result::second::size;
    BOOST_CHECK_EQUAL( sizesecond, 0 );
  }

  BOOST_AUTO_TEST_CASE( check_split )
  {
    typedef split< vec3, 2 > result;

    static const unsigned sizefirst = result::first::size;
    BOOST_CHECK_EQUAL( sizefirst, 2 );

    static const bool b0 = std::is_same< typename at< result::first, 0 >::type, int >::value;
    BOOST_CHECK( b0 );

    static const bool b1 = std::is_same< typename at< result::first, 1 >::type, double >::value;
    BOOST_CHECK( b1 );


    static const unsigned sizesecond = result::second::size;
    BOOST_CHECK_EQUAL( sizesecond, 1 );

    static const bool b2 = std::is_same< typename at< result::second, 0 >::type, char >::value;
    BOOST_CHECK( b2 );

  }

BOOST_AUTO_TEST_SUITE_END()
