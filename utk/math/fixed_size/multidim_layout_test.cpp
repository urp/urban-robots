/*  bla.cpp - Copyright Peter Urban 2009

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

# include "utk/math/fixed_size/multidim_layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim layout
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_SUITE( static_use )

  BOOST_AUTO_TEST_CASE( layout_stride )
  {
    typedef multidim_layout< size_vector<2,3,4> > layout;

    // number of elements in the whole tensor
    size_type stride0 =  layout::stride<0>::value;
    BOOST_CHECK_EQUAL( stride0, 12 );

    // size of the first three sub dimensions
    size_type stride1 = layout::stride<1>::value;
    BOOST_CHECK_EQUAL( stride1, 4 );

    // scalar
    size_type stride2 = layout::stride<2>::value;
    BOOST_CHECK_EQUAL( stride2, 1 );

  }

  BOOST_AUTO_TEST_CASE( size )
  {
    typedef multidim_layout< size_vector<2,3,4> > layout;

    const index_type order = layout::order;
    BOOST_CHECK_EQUAL( order, 3 );

    const size_type total = layout::total_size;
    BOOST_CHECK_EQUAL( total, 24 );


    std::array< size_type, 3 > size_array = meta::integral::make_array< layout::sizes >::value;
    BOOST_CHECK_EQUAL( size_array[0], 2 );
  }

  BOOST_AUTO_TEST_CASE( layout_static_offset )
  {
    typedef multidim_layout< size_vector<2,3,4,5> > layout;

    const stride_type offset = layout::static_offset();
    BOOST_CHECK_EQUAL( offset, 0 );

  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( layout_remove_index )

  BOOST_AUTO_TEST_CASE( size_and_stride_with_3d )
  {
    typedef multidim_layout< size_vector<1,2,3> > old_layout;

    typedef typename remove_index< old_layout, 0 >::type layout;

    const size_type order = layout::order;
    BOOST_CHECK_EQUAL( order, 2 );

    const size_type size0 = meta::integral::at< typename layout::sizes, 0 >::value;
    BOOST_CHECK_EQUAL( size0, 2 );

    const size_type size1 = meta::integral::at< typename layout::sizes, 1 >::value;
    BOOST_CHECK_EQUAL( size1, 3 );

    const stride_type stride0 = meta::integral::at< typename layout::strides, 0 >::value;
    BOOST_CHECK_EQUAL( stride0, 3 );

    const stride_type stride1 = meta::integral::at< typename layout::strides, 1 >::value;
    BOOST_CHECK_EQUAL( stride1, 1 );

  }

BOOST_AUTO_TEST_SUITE_END()
