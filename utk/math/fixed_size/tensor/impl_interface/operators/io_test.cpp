/*  io_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/tensor/impl_interface/operators/io.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor::interface io
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::tensor;

struct fixture
{
  int data[6];

  typedef typename make_layout< size_vector< 1,2,3 >, contravariant_tag >::type layout123;
  typedef interface< int, unmanaged_tag, layout123 > type123;
  type123 tensor123;

  typedef typename make_layout< size_vector< 1,2 >, contravariant_tag >::type layout12;
  typedef interface< int, unmanaged_tag, layout12 > type12;
  type12 tensor12;

  typedef typename make_layout< size_vector< 1 >, contravariant_tag >::type layout1;
  typedef interface< int, unmanaged_tag, layout1 > type1;
  type1  tensor1;


  typedef typename make_layout< size_vector< >, contravariant_tag >::type layout_;
  typedef interface< int, unmanaged_tag, layout_ > type_;
  type_  tensor_;

  fixture() : data{ 1,2,3,4,5,6 }, tensor123(data), tensor12(data), tensor1(data), tensor_(data) {}
};

BOOST_FIXTURE_TEST_SUITE( check_io, fixture )

  BOOST_AUTO_TEST_CASE( check_0d )
  {
    BOOST_TEST_MESSAGE( tensor_ );
  }


  BOOST_AUTO_TEST_CASE( check_2d )
  {
    BOOST_TEST_MESSAGE( tensor12 );
  }

  BOOST_AUTO_TEST_CASE( check_3d )
  {
    BOOST_TEST_MESSAGE( tensor123 );
  }

BOOST_AUTO_TEST_SUITE_END()
