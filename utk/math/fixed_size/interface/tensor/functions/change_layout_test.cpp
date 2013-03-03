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

# include "utk/math/fixed_size/interface/vector.hpp"

# include "utk/math/fixed_size/interface/tensor/functions/at.hpp"
# include "utk/math/fixed_size/interface/tensor/functions/make_layout.hpp"
# include "utk/math/fixed_size/interface/tensor/functions/change_layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor::interface change_layout
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::interface;
using namespace utk::math::fixed_size::interface::tensor;

struct fixture
{
  typedef typename make_layout< size_vector< 1,2,3 >, contravariant_tag >::type layout123;
  typedef interface< int, vector::unmanaged_tag, layout123 > type123;
  int data[6];
  type123 tensor123;

  fixture() : data{ 1,2,3,4,5,6 }, tensor123(data) {}
};

BOOST_FIXTURE_TEST_SUITE( check_change_layout, fixture )

BOOST_AUTO_TEST_CASE( check_change_to_1d )
{
  typedef typename make_layout< size_vector< 6 >, covariant_tag >::type layout6;

  constexpr variance_type lvar1 = meta::integral::at< typename meta::pop_back< typename layout6::attributes >::type, 0 >::value;
  BOOST_CHECK_EQUAL( lvar1, covariant );

  auto tensor6 = math::fixed_size::interface::use_layout< type123, layout6 >( tensor123 );

  constexpr variance_type var1 = meta::integral::at< typename decltype(tensor6)::variances, 0 >::value;
  BOOST_CHECK_EQUAL( var1, lvar1 );

  BOOST_CHECK_EQUAL( at( tensor6, 0 ), 1 );
  BOOST_CHECK_EQUAL( at( tensor6, 1 ), 2 );
  BOOST_CHECK_EQUAL( at( tensor6, 2 ), 3 );
  BOOST_CHECK_EQUAL( at( tensor6, 3 ), 4 );
  BOOST_CHECK_EQUAL( at( tensor6, 4 ), 5 );
  BOOST_CHECK_EQUAL( at( tensor6, 5 ), 6 );
}

BOOST_AUTO_TEST_SUITE_END()
