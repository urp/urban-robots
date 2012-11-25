/*  fix_index_test.cpp - Copyright Peter Urban 2012

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

# include "utk/meta/vector_at.hpp"

# include "utk/math/fixed_size/multidim/impl_slice_layout/fix_index.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::slice_layout fix_index
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size::multidim;


//---| fix_unmasked_index ( slice_layout ) |------------------/

struct slice__fix_unmasked_index
{
  typedef layout< size_vector< 2,3,4 > > old_layout;
  typedef slice_layout< old_layout, index_vector< 1,3,4 > > slice_layout;
  typedef typename fix_unmasked_index< slice_layout, 0,1 >::type layout34;
  // fixed 0->1 (overwrite)
};

BOOST_FIXTURE_TEST_SUITE( check_slice__fix_unmasked_index, slice__fix_unmasked_index )

  BOOST_AUTO_TEST_CASE( check_order )
  {
    const size_type order = layout34::order;
    BOOST_CHECK_EQUAL( order, 2 );
  }
  BOOST_AUTO_TEST_CASE( check_size )
  {
    const size_type size0 = meta::integral::at< typename layout34::sizes, 0 >::value;
    BOOST_CHECK_EQUAL( size0, 3 );

    const size_type size1 = meta::integral::at< typename layout34::sizes, 1 >::value;
    BOOST_CHECK_EQUAL( size1, 4 );
  }
  BOOST_AUTO_TEST_CASE( check_stride )
  {
    const stride_type stride0 = meta::integral::at< typename layout34::strides, 0 >::value;
    BOOST_CHECK_EQUAL( stride0, 4 );

    const stride_type stride1 = meta::integral::at< typename layout34::strides, 1 >::value;
    BOOST_CHECK_EQUAL( stride1, 1 );
  }
  BOOST_AUTO_TEST_CASE( check_static_offset )
  {
    const stride_type offset_static = layout34::static_offset();
    BOOST_CHECK_EQUAL( offset_static, 12 );
  }

BOOST_AUTO_TEST_SUITE_END()

//---| fix_index ( slice_layout ) |---------------------------/

struct slice__fix_index
{
  typedef layout< size_vector< 2,3,4 > > old_layout;
  //typedef slice_layout< old_layout, index_vector< 1,1,4 > > layout4;
  typedef typename fix_index< old_layout, 0,1 >::type slice_layout;
  typedef typename fix_index< slice_layout, 0,1 >::type layout4;
  // fixed 0->1, 1->1
};

BOOST_FIXTURE_TEST_SUITE( check_slice__fix_index, slice__fix_index )

  BOOST_AUTO_TEST_CASE( check_order )
  {
    const size_type order = layout4::order;
    BOOST_CHECK_EQUAL( order, 1 );
  }
  BOOST_AUTO_TEST_CASE( check_size )
  {
    const size_type size0 = meta::integral::at< typename layout4::sizes, 0 >::value;
    BOOST_CHECK_EQUAL( size0, 4 );
  }
  BOOST_AUTO_TEST_CASE( check_stride )
  {
    const stride_type stride0 = meta::integral::at< typename layout4::strides, 0 >::value;
    BOOST_CHECK_EQUAL( stride0, 1 );
  }
  BOOST_AUTO_TEST_CASE( check_static_offset )
  {
    const stride_type offset_static = layout4::static_offset();
    BOOST_CHECK_EQUAL( offset_static, 16 );
  }

BOOST_AUTO_TEST_SUITE_END()


//---| fix_index ( layout ) |---------------------------------/

struct layout_fix_index
{
  typedef layout< size_vector< 2,3,4 > > old_layout;
  typedef typename fix_index< old_layout, 0,1 >::type layout34;
  // fixed 0->1
};

BOOST_FIXTURE_TEST_SUITE( check__fix_index, layout_fix_index )

  BOOST_AUTO_TEST_CASE( check_order )
  {
    const size_type order = layout34::order;
    BOOST_CHECK_EQUAL( order, 2 );
  }
  BOOST_AUTO_TEST_CASE( check_size )
  {
    const size_type size0 = meta::integral::at< typename layout34::sizes, 0 >::value;
    BOOST_CHECK_EQUAL( size0, 3 );

    const size_type size1 = meta::integral::at< typename layout34::sizes, 1 >::value;
    BOOST_CHECK_EQUAL( size1, 4 );
  }
  BOOST_AUTO_TEST_CASE( check_stride )
  {
    const stride_type stride0 = meta::integral::at< typename layout34::strides, 0 >::value;
    BOOST_CHECK_EQUAL( stride0, 4 );

    const stride_type stride1 = meta::integral::at< typename layout34::strides, 1 >::value;
    BOOST_CHECK_EQUAL( stride1, 1 );
  }
  BOOST_AUTO_TEST_CASE( check_static_offset )
  {
    const stride_type offset_static = layout34::static_offset();
    BOOST_CHECK_EQUAL( offset_static, 12 );
  }

BOOST_AUTO_TEST_SUITE_END()
