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
# include "utk/math/fixed_size/multidim_product_layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim product layout
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_SUITE( two_dim_x_one_dim )

  BOOST_AUTO_TEST_CASE( layout_stride )
  {
    typedef multidim_layout< size_vector<1> > layout1;
    typedef multidim_layout< size_vector<2,3> > layout2;
    typedef typename product_layout< layout1, layout2 >::type layout;

    // number of elements in the whole tensor
    size_type stride0 =  layout::stride<0>::value;
    BOOST_CHECK_EQUAL( stride0, 6 );

    // size of the first two subspaces
    size_type stride1 = layout::stride<1>::value;
    BOOST_CHECK_EQUAL( stride1, 3 );

    // scalar - 1d
    size_type stride2 = layout::stride<2>::value;
    BOOST_CHECK_EQUAL( stride2, 1 );

  }

  BOOST_AUTO_TEST_CASE( size )
  {
    typedef multidim_layout< size_vector<1> > layout1;
    typedef multidim_layout< size_vector<2,3> > layout2;
    typedef typename product_layout< layout1, layout2 >::type layout;

    const index_type order = layout::order;
    BOOST_CHECK_EQUAL( order, 3 );

    const size_type total = layout::total_size;
    BOOST_CHECK_EQUAL( total, 6 );


    std::array< size_type, 3 > size_array = meta::integral::make_array< layout::sizes >::value;
    BOOST_CHECK_EQUAL( size_array[0], 1 );
  }

  BOOST_AUTO_TEST_CASE( layout_static_offset )
  {
    typedef multidim_layout< size_vector<1> > layout1;
    typedef multidim_layout< size_vector<2,3> > layout2;
    typedef typename product_layout< layout1, layout2 >::type layout;

    const stride_type offset = layout::static_offset();
    BOOST_CHECK_EQUAL( offset, 0 );

  }

BOOST_AUTO_TEST_SUITE_END()
