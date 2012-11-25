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

# include "utk/math/fixed_size/multidim/layout.hpp"
# include "utk/math/fixed_size/tensor/impl_array/array.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor array
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::tensor;

BOOST_AUTO_TEST_CASE( construct_with_uninitialized_data )
{
  typedef multidim::layout< multidim::size_vector<1,2,3> > layout;
  typedef variance_vector< covariant, covariant, covariant > variances;
  typedef array< double, layout, variances > tensor123;
  tensor123 test_tensor;

  test_tensor.at( 0,0,0 ) = 1.;

  BOOST_CHECK_EQUAL( test_tensor.at( 0,0,0 ), 1. );
}
