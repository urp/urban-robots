/*  make_layout_test.cpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/tensor/impl_interface/make_layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor make_layout
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::tensor;

BOOST_AUTO_TEST_SUITE( make_tensor_layout )

  BOOST_AUTO_TEST_CASE( check_contravariant )
  {
    typedef typename make_layout< size_vector<1,2,3>, contravariant_tag >::type contra_layout;
    typedef interface< int, vector::unmanaged_tag, contra_layout > contra_tensor;
    contra_tensor contravariant_test_tensor( nullptr );

    const size_type var1 = meta::integral::at< contra_tensor::variances, 0 >::value;
    BOOST_CHECK_EQUAL( var1, contravariant );
    const size_type var2 = meta::integral::at< contra_tensor::variances, 1 >::value;
    BOOST_CHECK_EQUAL( var2, contravariant );
    const size_type var3 = meta::integral::at< contra_tensor::variances, 2 >::value;
    BOOST_CHECK_EQUAL( var3, contravariant );
  }

  BOOST_AUTO_TEST_CASE( check_covariant )
  {
    typedef typename make_layout< size_vector<1,2,3>, covariant_tag >::type co_layout;
    typedef interface< int, vector::unmanaged_tag, co_layout > co_tensor;
    co_tensor co_test_tensor( nullptr );

    const size_type covar1 = meta::integral::at< co_tensor::variances, 0 >::value;
    BOOST_CHECK_EQUAL( covar1, covariant );
    const size_type covar2 = meta::integral::at< co_tensor::variances, 1 >::value;
    BOOST_CHECK_EQUAL( covar2, covariant );
    const size_type covar3 = meta::integral::at< co_tensor::variances, 2 >::value;
    BOOST_CHECK_EQUAL( covar3, covariant );
  }

  BOOST_AUTO_TEST_CASE( check_mixed )
  {
    typedef typename make_layout< size_vector<1,2,3>, mixed_tag<2> >::type mixed_layout;
    typedef interface< double, vector::unmanaged_tag, mixed_layout > mixed_tensor;
    mixed_tensor mixed_test_tensor( nullptr );

    const size_type var1 = meta::integral::at< mixed_tensor::variances, 0 >::value;
    BOOST_CHECK_EQUAL( var1, contravariant );
    const size_type var2 = meta::integral::at< mixed_tensor::variances, 1 >::value;
    BOOST_CHECK_EQUAL( var2, contravariant );
    const size_type var3 = meta::integral::at< mixed_tensor::variances, 2 >::value;
    BOOST_CHECK_EQUAL( var3, covariant );
  }

BOOST_AUTO_TEST_SUITE_END()
