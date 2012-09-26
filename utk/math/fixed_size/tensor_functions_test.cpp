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

# include "utk/math/fixed_size/tensor_functions.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor functions
#include <boost/test/unit_test.hpp>

using namespace utk::math;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_SUITE( make_tensor_interface )

BOOST_AUTO_TEST_CASE( make_non_mixed_tensor_interface_test )
{
  typedef initial_layout< 1,2,3 > layout;

  // contravariant

  typedef typename make_non_mixed_tensor_interface< double, layout, contravariant >::type contravariant_tensor;
  contravariant_tensor contravariant_test_tensor( nullptr );

  const size_type var1 = integral::at< contravariant_tensor::variances, 0 >::value;
  BOOST_CHECK_EQUAL( var1, contravariant );
  const size_type var2 = integral::at< contravariant_tensor::variances, 1 >::value;
  BOOST_CHECK_EQUAL( var2, contravariant );
  const size_type var3 = integral::at< contravariant_tensor::variances, 2 >::value;
  BOOST_CHECK_EQUAL( var3, contravariant );

  // covariant

  typedef typename make_non_mixed_tensor_interface< double, layout, covariant >::type covariant_tensor;
  covariant_tensor covariant_test_tensor( nullptr );

  const size_type covar1 = integral::at< covariant_tensor::variances, 0 >::value;
  BOOST_CHECK_EQUAL( covar1, covariant );
  const size_type covar2 = integral::at< covariant_tensor::variances, 1 >::value;
  BOOST_CHECK_EQUAL( covar2, covariant );
  const size_type covar3 = integral::at< covariant_tensor::variances, 2 >::value;
  BOOST_CHECK_EQUAL( covar3, covariant );
}

BOOST_AUTO_TEST_SUITE_END()