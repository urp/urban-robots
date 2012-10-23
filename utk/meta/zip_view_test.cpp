/*  zip_view_test.cpp - Copyright Peter Urban 2012

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


# include "utk/meta/integral/vector.hpp"

# include "utk/meta/vector.hpp"
# include "utk/meta/vector_at.hpp"

# include "utk/meta/zip_view.hpp"

# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE meta zip_view
# include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::meta;

BOOST_AUTO_TEST_CASE( two )
{
  typedef typename zip_view< 2
                           , typename integral::vector< int, 1,2 >::meta_vector
                           , typename integral::vector< int, 3,4 >::meta_vector >::type zip;

  const size_type zip_size = zip::size;
  BOOST_CHECK_EQUAL( zip_size, 2 );

  const int z00 = at< typename at< zip, 0 >::type, 0 >::type::value;
  BOOST_CHECK_EQUAL( z00, 1 );
  const int z10 = at< typename at< zip, 1 >::type, 0 >::type::value;
  BOOST_CHECK_EQUAL( z10, 2 );
  const int z01 = at< typename at< zip, 0 >::type, 1 >::type::value;
  BOOST_CHECK_EQUAL( z01, 3 );
  const int z11 = at< typename at< zip, 1 >::type, 1 >::type::value;
  BOOST_CHECK_EQUAL( z11, 4 );
}

BOOST_AUTO_TEST_CASE( three )
{
  typedef typename zip_view< 2
                           , typename integral::vector< int, 1,2 >::meta_vector
                           , typename integral::vector< int, 3,4 >::meta_vector
                           , typename integral::vector< int, 5,6 >::meta_vector >::type zip;

  const size_type zip_size = zip::size;
  BOOST_CHECK_EQUAL( zip_size, 2 );

  const int z00 = at< typename at< zip, 0 >::type, 0 >::type::value;
  BOOST_CHECK_EQUAL( z00, 1 );
  const int z10 = at< typename at< zip, 1 >::type, 0 >::type::value;
  BOOST_CHECK_EQUAL( z10, 2 );
  const int z01 = at< typename at< zip, 0 >::type, 1 >::type::value;
  BOOST_CHECK_EQUAL( z01, 3 );
  const int z11 = at< typename at< zip, 1 >::type, 1 >::type::value;
  BOOST_CHECK_EQUAL( z11, 4 );
  const int z02 = at< typename at< zip, 0 >::type, 2 >::type::value;
  BOOST_CHECK_EQUAL( z02, 5 );
  const int z12 = at< typename at< zip, 1 >::type, 2 >::type::value;
  BOOST_CHECK_EQUAL( z12, 6 );
}
