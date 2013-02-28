/*  release_index_test.cpp - Copyright Peter Urban 2012

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

# include "utk/meta/integral/vector_functions.hpp"

# include "utk/math/fixed_size/multidim/impl_slice_layout/release_index.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::slice_layout release_index
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::multidim;


//---| fix_unmasked_index ( multidim_slice_layout ) |------------------/

struct first_index_released
{
  typedef layout< size_vector< 2,3,4 > > old_layout;
  typedef slice_layout< old_layout, index_vector< 1,1,4 > > slice_layout;
  typedef typename release_index< slice_layout, 0 >::type layout34;
  // fixed 1->1
};

BOOST_FIXTURE_TEST_SUITE( check_first_index_released, first_index_released )

  BOOST_AUTO_TEST_CASE( check_order )
  {
    const size_type order = layout34::order;
    BOOST_CHECK_EQUAL( order, 2 );
  }
  BOOST_AUTO_TEST_CASE( check_size )
  {
    const size_type size0 = meta::integral::at< typename layout34::sizes, 0 >::value;
    BOOST_CHECK_EQUAL( size0, 2 );

    const size_type size1 = meta::integral::at< typename layout34::sizes, 1 >::value;
    BOOST_CHECK_EQUAL( size1, 4 );
  }
  BOOST_AUTO_TEST_CASE( check_stride )
  {
    const stride_type stride0 = meta::integral::at< typename layout34::strides, 0 >::value;
    BOOST_CHECK_EQUAL( stride0, 12 );

    const stride_type stride1 = meta::integral::at< typename layout34::strides, 1 >::value;
    BOOST_CHECK_EQUAL( stride1, 1 );
  }
  BOOST_AUTO_TEST_CASE( check_static_offset )
  {
    const stride_type offset_static = layout34::static_offset();
    BOOST_CHECK_EQUAL( offset_static, 4 );
  }

BOOST_AUTO_TEST_SUITE_END()
