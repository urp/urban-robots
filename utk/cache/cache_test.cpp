/*  bla.cpp - Copyright Peter Urban 2009

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

# include "utk/cache/cache.hpp"

#define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE cache_test
# include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( constructors_test )
{
  utk::cache::Cache<int> test_cache;
  BOOST_CHECK_EQUAL( test_cache.is_valid(), false );

  // test with initialized cache variable
  utk::cache::Cache<int> test_cache2(2);
  BOOST_CHECK_EQUAL( test_cache2.is_valid(), true );
}

BOOST_AUTO_TEST_CASE( data_access_test )
{
  utk::cache::Cache<int> test_cache;
  test_cache = 1;
  BOOST_REQUIRE_EQUAL( test_cache, 1 );

  // test access with initialized cache variable
  utk::cache::Cache<int> test_cache2( 2 );
  BOOST_REQUIRE_EQUAL( int(test_cache2), 2 );

  test_cache2.invalidate();

  int a;
  BOOST_REQUIRE_EQUAL( test_cache2.is_valid(), false );
  BOOST_REQUIRE_THROW( a = test_cache2, utk::cache::invalid_access_error );

  a = 3; 
  test_cache2 = a;
  BOOST_REQUIRE_EQUAL( test_cache2.is_valid(), true );
  BOOST_REQUIRE_EQUAL( int(test_cache2), 3 );
}
