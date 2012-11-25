/*  product_layout_test.cpp - Copyright Peter Urban 2012

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
# include "utk/math/fixed_size/multidim/impl_layout/product_layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::product_layout
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size::multidim;

BOOST_AUTO_TEST_SUITE( two_dim_x_one_dim )

  BOOST_AUTO_TEST_CASE( layout_stride )
  {
    typedef layout< size_vector<1> > layout1;
    typedef layout< size_vector<2,3> > layout2;
    typedef typename product_layout< layout1, layout2 >::type layout1x2;

    // number of elements in the whole tensor
    size_type stride0 =  layout1x2::stride<0>::value;
    BOOST_CHECK_EQUAL( stride0, 6 );

    // size of the first two subspaces
    size_type stride1 = layout1x2::stride<1>::value;
    BOOST_CHECK_EQUAL( stride1, 3 );

    // scalar - 1d
    size_type stride2 = layout1x2::stride<2>::value;
    BOOST_CHECK_EQUAL( stride2, 1 );

  }

  BOOST_AUTO_TEST_CASE( size )
  {
    typedef layout< size_vector<1> > layout1;
    typedef layout< size_vector<2,3> > layout2;
    typedef typename product_layout< layout1, layout2 >::type layout1x2;

    const index_type order = layout1x2::order;
    BOOST_CHECK_EQUAL( order, 3 );

    const size_type total = layout1x2::total_size;
    BOOST_CHECK_EQUAL( total, 6 );


    std::array< size_type, 3 > size_array = meta::integral::make_array< layout1x2::sizes >::value;
    BOOST_CHECK_EQUAL( size_array[0], 1 );
  }

  BOOST_AUTO_TEST_CASE( layout_static_offset )
  {
    typedef layout< size_vector<1> > layout1;
    typedef layout< size_vector<2,3> > layout2;
    typedef typename product_layout< layout1, layout2 >::type layout1x2;

    const stride_type offset = layout1x2::static_offset();
    BOOST_CHECK_EQUAL( offset, 0 );

  }

BOOST_AUTO_TEST_SUITE_END()
