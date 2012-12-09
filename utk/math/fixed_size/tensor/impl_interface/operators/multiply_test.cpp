/*  multiply_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/tensor/impl_interface/interface.hpp"

# include "utk/math/fixed_size/tensor/impl_interface/operators/multiply.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor::interface operator multiply
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;

struct fixture
{
  typedef typename tensor::make_layout< tensor::size_vector<1,2,3>, tensor::contravariant_tag >::type contra_layout;
  typedef tensor::interface< int, contra_layout > type123;
  int data[6];
  type123 tensor123;

  fixture() : data{ 1,2,3,4,5,6 }, tensor123( data ) {}
};

BOOST_FIXTURE_TEST_SUITE( check_multiply, fixture )

  BOOST_AUTO_TEST_CASE( check_multipy_scalar )
  {
    auto result = tensor123 * 2;

    BOOST_CHECK_EQUAL( at( result, 0,0,0 ),  2 );
    BOOST_CHECK_EQUAL( at( result, 0,0,1 ),  4 );
    BOOST_CHECK_EQUAL( at( result, 0,0,2 ),  6 );
    BOOST_CHECK_EQUAL( at( result, 0,1,0 ),  8 );
    BOOST_CHECK_EQUAL( at( result, 0,1,1 ), 10 );
    BOOST_CHECK_EQUAL( at( result, 0,1,2 ), 12 );
  }

BOOST_AUTO_TEST_SUITE_END()
