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

# include "utk/math/fixed_size/tensor/impl_interface/make_layout.hpp"
# include "utk/math/fixed_size/tensor/impl_interface/change_layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor::interface change_layout
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::tensor;

struct fixture
{
  typedef typename make_layout< size_vector< 1,2,3 >, contravariant_tag >::type layout123;
  typedef interface< int, layout123 > type123;
  int data[6];
  type123 tensor123;

  fixture() : data{ 1,2,3,4,5,6 }, tensor123(data) {}
};

BOOST_FIXTURE_TEST_SUITE( check_change_layout, fixture )

BOOST_AUTO_TEST_CASE( check_change_to_1d )
{
  typedef typename make_layout< size_vector< 6 >, contravariant_tag >::type layout6;

  auto tensor6 = tensor::use_layout< type123, layout6 >( tensor123 );

  BOOST_CHECK_EQUAL( tensor6.at(0), 1 );
  BOOST_CHECK_EQUAL( tensor6.at(1), 2 );
  BOOST_CHECK_EQUAL( tensor6.at(2), 3 );
  BOOST_CHECK_EQUAL( tensor6.at(3), 4 );
  BOOST_CHECK_EQUAL( tensor6.at(4), 5 );
  BOOST_CHECK_EQUAL( tensor6.at(5), 6 );
}

BOOST_AUTO_TEST_SUITE_END()
