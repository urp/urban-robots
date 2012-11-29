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

# include "utk/math/fixed_size/multidim/impl_interface/change_layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::interface change_layout
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
//using namespace utk::math::fixed_size::multidim;

struct interface_fixture
{
  typedef multidim::layout< multidim::size_vector< 1,2,3 > > layout123;
  typedef multidim::interface< int, layout123 >::type type123;
  int data[6];
  type123 multidim123;

  interface_fixture() : data{ 1,2,3,4,5,6 }, multidim123( data ) {}
};

BOOST_FIXTURE_TEST_SUITE( check_change_layout, interface_fixture )

  BOOST_AUTO_TEST_CASE( check_change_to_1d )
  {
    typedef multidim::layout< multidim::size_vector< 6 > > layout6;

    auto multidim6 = multidim::use_layout<type123,layout6>( multidim123 );

    BOOST_CHECK_EQUAL( multidim6.at(0), 1 );
    BOOST_CHECK_EQUAL( multidim6.at(1), 2 );
    BOOST_CHECK_EQUAL( multidim6.at(2), 3 );
    BOOST_CHECK_EQUAL( multidim6.at(3), 4 );
    BOOST_CHECK_EQUAL( multidim6.at(4), 5 );
    BOOST_CHECK_EQUAL( multidim6.at(5), 6 );
  }

BOOST_AUTO_TEST_SUITE_END()
