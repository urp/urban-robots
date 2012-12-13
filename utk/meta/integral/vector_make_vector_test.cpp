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

# include "utk/meta/integral/vector_make_vector.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector functions
#include <boost/test/unit_test.hpp>

using namespace utk::meta::integral;

BOOST_AUTO_TEST_SUITE( check_make_vector )

  BOOST_AUTO_TEST_CASE( check_convert_value_type )
  {
    typedef typename make_vector< int, vector< unsigned, 1,2,3 > >::type  ints;

    const int size = ints::size;
    BOOST_CHECK_EQUAL( size, 3 );

    const bool is_target_type = std::is_same< typename ints::value_type, int >::value;
    BOOST_CHECK( is_target_type );

    const int i0 = at< ints, 0 >::value;
    BOOST_CHECK_EQUAL( i0, 1 );
    const int i1 = at< ints, 1 >::value;
    BOOST_CHECK_EQUAL( i1, 2 );
    const int i2 = at< ints, 2 >::value;
    BOOST_CHECK_EQUAL( i2, 3 );
  }

  BOOST_AUTO_TEST_CASE( check_integral_from_meta_vector )
  {
    typedef typename make_vector< int, utk::meta::vector< constant< int, 1 >
                                                        , constant< int, 2 >
                                                        , constant< int, 3 >
                                                        > >::type  ints;

    const int size = ints::size;
    BOOST_CHECK_EQUAL( size, 3 );

    const bool is_target_type = std::is_same< typename ints::value_type, int >::value;
    BOOST_CHECK( is_target_type );

    const int i0 = at< ints, 0 >::value;
    BOOST_CHECK_EQUAL( i0, 1 );
    const int i1 = at< ints, 1 >::value;
    BOOST_CHECK_EQUAL( i1, 2 );
    const int i2 = at< ints, 2 >::value;
    BOOST_CHECK_EQUAL( i2, 3 );
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( check_make_uniform_vector )

  BOOST_AUTO_TEST_CASE( check_uniform )
  {
    typedef typename make_uniform_vector< int, 3,2 >::type  ints;

    const int size = ints::size;
    BOOST_CHECK_EQUAL( size, 3 );

    const int i0 = at< ints, 0 >::value;
    BOOST_CHECK_EQUAL( i0, 2 );
    const int i1 = at< ints, 1 >::value;
    BOOST_CHECK_EQUAL( i1, 2 );
    const int i2 = at< ints, 2 >::value;
    BOOST_CHECK_EQUAL( i2, 2 );
  }

  BOOST_AUTO_TEST_CASE( check_make_position_index_vector )
  {
    typedef typename make_position_index_vector< int, 3 >::type pos;

    const int size = pos::size;
    BOOST_CHECK_EQUAL( size, 3 );

    const int i0 = at< pos, 0 >::value;
    BOOST_CHECK_EQUAL( i0, 0 );
    const int i1 = at< pos, 1 >::value;
    BOOST_CHECK_EQUAL( i1, 1 );
    const int i2 = at< pos, 2 >::value;
    BOOST_CHECK_EQUAL( i2, 2 );
  }

BOOST_AUTO_TEST_SUITE_END()
