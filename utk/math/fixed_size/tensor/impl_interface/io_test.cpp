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

# include "utk/math/fixed_size/tensor/impl_interface/make_interface.hpp"

# include "utk/math/fixed_size/tensor/impl_interface/io.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor::interface io
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::tensor;

struct fixture
{
  int data[6];

  typedef multidim::layout< multidim::size_vector< 1,2 > > layout12;
  typedef typename make_non_mixed_interface< int, layout12, contravariant >::type type12;
  type12 tensor12;

  typedef multidim::layout< multidim::size_vector< 1 > > layout1;
  typedef typename make_non_mixed_interface< int, layout1, contravariant >::type type1;
  type1  tensor1;


  typedef multidim::layout< multidim::size_vector< > > layout_;
  typedef typename make_non_mixed_interface< int, layout_, contravariant >::type type_;
  type_  tensor_;

  fixture() : data{ 1,2,3,4,5,6 }, tensor12(data), tensor1(data), tensor_(data) {}
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

BOOST_AUTO_TEST_SUITE_END()
