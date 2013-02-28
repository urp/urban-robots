/*  layout_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_layout/layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::layout
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::multidim;

BOOST_AUTO_TEST_SUITE( static_use )

  BOOST_AUTO_TEST_CASE( layout_stride )
  {
    typedef layout< size_vector<2,3,4> > layout234;

    // number of elements in the whole tensor
    size_type stride0 =  layout234::stride<0>::value;
    BOOST_CHECK_EQUAL( stride0, 12 );

    // size of the first three sub dimensions
    size_type stride1 = layout234::stride<1>::value;
    BOOST_CHECK_EQUAL( stride1, 4 );

    // scalar
    size_type stride2 = layout234::stride<2>::value;
    BOOST_CHECK_EQUAL( stride2, 1 );

  }

  BOOST_AUTO_TEST_CASE( size )
  {
    typedef layout< size_vector<2,3,4> > layout234;

    const index_type order = layout234::order;
    BOOST_CHECK_EQUAL( order, 3 );

    const size_type total = layout234::total_size;
    BOOST_CHECK_EQUAL( total, 24 );


    std::array< size_type, 3 > size_array = utk::meta::integral::make_array< layout234::sizes >::value;
    BOOST_CHECK_EQUAL( size_array[0], 2 );
  }

  BOOST_AUTO_TEST_CASE( layout_static_offset )
  {
    typedef layout< size_vector<2,3,4,5> > layout234;

    const stride_type offset = layout234::static_offset();
    BOOST_CHECK_EQUAL( offset, 0 );

  }

BOOST_AUTO_TEST_SUITE_END()
