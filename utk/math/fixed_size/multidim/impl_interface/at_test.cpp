/*  tensor_interface_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/vector/vector.hpp"

# include "utk/math/fixed_size/multidim/impl_interface/interface.hpp"
# include "utk/math/fixed_size/multidim/impl_interface/at.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::interface at
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::multidim;

struct fixture
{
  typedef layout< size_vector< 1,2,3 > > layout123;
  typedef interface< int, vector::unmanaged_tag, layout123 > type123;
  int data[6];
  type123 multidim123;

  fixture() : data{ 1,2,3,4,5,6 }, multidim123( data ) {}
};

BOOST_FIXTURE_TEST_SUITE( check_at, fixture )

  BOOST_AUTO_TEST_CASE( check_complete_index_set )
  {
    BOOST_CHECK_EQUAL( at( multidim123, 0,0,0 ), 1 );
    BOOST_CHECK_EQUAL( at( multidim123, 0,0,1 ), 2 );
    BOOST_CHECK_EQUAL( at( multidim123, 0,0,2 ), 3 );
    BOOST_CHECK_EQUAL( at( multidim123, 0,1,0 ), 4 );
    BOOST_CHECK_EQUAL( at( multidim123, 0,1,1 ), 5 );
    BOOST_CHECK_EQUAL( at( multidim123, 0,1,2 ), 6 );
  }

  BOOST_AUTO_TEST_CASE( check_complete_index_set_assign )
  {
    at(multidim123, 0,0,0) = -1;
    BOOST_CHECK_EQUAL( at( multidim123, 0,0,0 ), -1 );
    at(multidim123, 0,0,1) = -2;
    BOOST_CHECK_EQUAL( at( multidim123, 0,0,1 ), -2 );
    at(multidim123, 0,0,2) = -3;
    BOOST_CHECK_EQUAL( at( multidim123, 0,0,2 ), -3 );
    at(multidim123, 0,1,0) = -4;
    BOOST_CHECK_EQUAL( at( multidim123, 0,1,0 ), -4 );
    at(multidim123, 0,1,1) = -5;
    BOOST_CHECK_EQUAL( at( multidim123, 0,1,1 ), -5 );
    at(multidim123, 0,1,2) = -6;
    BOOST_CHECK_EQUAL( at( multidim123, 0,1,2 ), -6 );
  }


  BOOST_AUTO_TEST_CASE( check_incomplete_index_set )
  {
    auto i00 = at( multidim123, index_vector< 0,0 >() );

    const size_type o00 = decltype(i00)::order;
    BOOST_CHECK_EQUAL( o00, 1 );
    BOOST_CHECK_EQUAL( at(i00, 0 ), 1 );
    BOOST_CHECK_EQUAL( at(i00, 1 ), 2 );
    BOOST_CHECK_EQUAL( at(i00, 2 ), 3 );

    auto i01 = at( multidim123, index_vector< 0,1 >() );

    const size_type o01 = decltype(i01)::order;
    BOOST_CHECK_EQUAL( o01, 1 );
    BOOST_CHECK_EQUAL( at(i01, 0 ), 4 );
    BOOST_CHECK_EQUAL( at(i01, 1 ), 5 );
    BOOST_CHECK_EQUAL( at(i01, 2 ), 6 );
  }


BOOST_AUTO_TEST_SUITE_END()
