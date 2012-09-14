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

# include "utk/math/integral/vector_functions.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector functions
#include <boost/test/unit_test.hpp>

using namespace utk::math::integral;

BOOST_AUTO_TEST_SUITE( data_access )

BOOST_AUTO_TEST_CASE( array_conversion )
{
  typedef vector< int, 1,2,3 >  bools;

  std::array< int,3 > array = make_array< bools >::value;

  BOOST_CHECK_EQUAL( array[0], 1 );
  BOOST_CHECK_EQUAL( array[1], 2 );
  BOOST_CHECK_EQUAL( array[2], 3 );
}

BOOST_AUTO_TEST_CASE( element_access )
{
  typedef vector< int, -1, 0, 3 >  ints;

  static const int i0 = at< ints, 0 >::value;
  BOOST_CHECK_EQUAL( i0, -1 );
  static const int i1 = at< ints, 1 >::value;
  BOOST_CHECK_EQUAL( i1, 0 );
  static const int i2 = at< ints, 2 >::value;
  BOOST_CHECK_EQUAL( i2, 3 );
}

BOOST_AUTO_TEST_CASE( vector_assign_element )
{
  typedef vector< int, -1, 0, 3 >  ints;
  typedef assign< ints, 1, constant< int, 7 > >::type new_ints;
  static const int ni1 = at< new_ints, 1 >::value;
  BOOST_CHECK_EQUAL( ni1, 7 );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( sequence_manipulators )

  BOOST_AUTO_TEST_CASE( vector_push_front )
  {
    typedef vector< int, -1, 0 >  ints;
    typedef typename push_front< ints, constant< int, 2 > >::type new_ints;

    static const int ni0 = at< new_ints, 0 >::value;
    BOOST_CHECK_EQUAL( ni0, 2 );
    static const int ni1 = at< new_ints, 1 >::value;
    BOOST_CHECK_EQUAL( ni1, -1 );
    static const int ni2 = at< new_ints, 2 >::value;
    BOOST_CHECK_EQUAL( ni2, 0 );
  }

  BOOST_AUTO_TEST_CASE( vector_push_back )
  {
    typedef vector< int, -1, 0 >  ints;
    typedef typename push_back< ints, constant< int, 2 > >::type new_ints;

    static const int ni0 = at< new_ints, 0 >::value;
    BOOST_CHECK_EQUAL( ni0, -1 );
    static const int ni1 = at< new_ints, 1 >::value;
    BOOST_CHECK_EQUAL( ni1,  0 );
    static const int ni2 = at< new_ints, 2 >::value;
    BOOST_CHECK_EQUAL( ni2,  2 );
  }

  BOOST_AUTO_TEST_CASE( vector_pop_front )
  {
    typedef vector< int, -1, 0, 2 >  ints;
    typedef pop_front< ints > pop_ints;

    static const int ni0 = pop_ints::value;
    BOOST_CHECK_EQUAL( ni0, -1 );
    static const int ni1 = at< pop_ints::tail, 0 >::value;
    BOOST_CHECK_EQUAL( ni1,  0 );
    static const int ni2 = at< pop_ints::tail, 1 >::value;
    BOOST_CHECK_EQUAL( ni2,  2 );
  }

  BOOST_AUTO_TEST_CASE( vector_pop_back )
  {
    typedef vector< int, -1, 0, 2 >  ints;
    typedef pop_back< ints > pop_ints;

    static const int ni0 = at< pop_ints::tail, 0 >::value;
    BOOST_CHECK_EQUAL( ni0, -1 );
    static const int ni1 = at< pop_ints::tail, 1 >::value;
    BOOST_CHECK_EQUAL( ni1,  0 );
    static const int ni2 = pop_ints::value;
    BOOST_CHECK_EQUAL( ni2,  2 );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( vector_instance_operators )

  BOOST_AUTO_TEST_CASE( stream_insertion )
  {
    const vector< int, 1,2,3 > instance;
    BOOST_MESSAGE( instance );
  }

BOOST_AUTO_TEST_SUITE_END()
