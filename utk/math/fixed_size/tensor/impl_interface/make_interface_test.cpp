/*  make_interface_test.cpp - Copyright Peter Urban 2012

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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor make_interface
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::tensor;

BOOST_AUTO_TEST_SUITE( make_tensor_interface )

BOOST_AUTO_TEST_CASE( make_non_mixed_tensor_interface_test )
{
  typedef multidim::layout< multidim::size_vector<1,2,3> > layout123;

  // contravariant

  typedef typename make_non_mixed_interface< double, layout123, contravariant >::type contravariant_tensor;
  contravariant_tensor contravariant_test_tensor( nullptr );

  const size_type var1 = meta::integral::at< contravariant_tensor::variances, 0 >::value;
  BOOST_CHECK_EQUAL( var1, contravariant );
  const size_type var2 = meta::integral::at< contravariant_tensor::variances, 1 >::value;
  BOOST_CHECK_EQUAL( var2, contravariant );
  const size_type var3 = meta::integral::at< contravariant_tensor::variances, 2 >::value;
  BOOST_CHECK_EQUAL( var3, contravariant );

  // covariant

  typedef typename make_non_mixed_interface< double, layout123, covariant >::type covariant_tensor;
  covariant_tensor covariant_test_tensor( nullptr );

  const size_type covar1 = meta::integral::at< covariant_tensor::variances, 0 >::value;
  BOOST_CHECK_EQUAL( covar1, covariant );
  const size_type covar2 = meta::integral::at< covariant_tensor::variances, 1 >::value;
  BOOST_CHECK_EQUAL( covar2, covariant );
  const size_type covar3 = meta::integral::at< covariant_tensor::variances, 2 >::value;
  BOOST_CHECK_EQUAL( covar3, covariant );
}

BOOST_AUTO_TEST_CASE( make_mixed_tensor_interface_test )
{
  typedef multidim::layout< multidim::size_vector<1,2,3> > layout123;

  typedef typename make_mixed_interface< double, layout123, 2 >::type mixed_tensor;
  mixed_tensor mixed_test_tensor( nullptr );

  const size_type var1 = meta::integral::at< mixed_tensor::variances, 0 >::value;
  BOOST_CHECK_EQUAL( var1, contravariant );
  const size_type var2 = meta::integral::at< mixed_tensor::variances, 1 >::value;
  BOOST_CHECK_EQUAL( var2, contravariant );
  const size_type var3 = meta::integral::at< mixed_tensor::variances, 2 >::value;
  BOOST_CHECK_EQUAL( var3, covariant );
}

BOOST_AUTO_TEST_SUITE_END()
