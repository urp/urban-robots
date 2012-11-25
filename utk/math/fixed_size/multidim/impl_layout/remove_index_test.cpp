/*  remove_index_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_layout/layout.hpp"
# include "utk/math/fixed_size/multidim/impl_layout/remove_index.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim_layout add_attributes
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size::multidim;

BOOST_AUTO_TEST_SUITE( layout_remove_index )

  BOOST_AUTO_TEST_CASE( with_3d_layout )
  {
    typedef layout< size_vector<1,2,3> > layout123;

    typedef typename remove_index< layout123, 0 >::type layout23;

    const size_type order = layout23::order;
    BOOST_CHECK_EQUAL( order, 2 );

    const size_type size0 = meta::integral::at< typename layout23::sizes, 0 >::value;
    BOOST_CHECK_EQUAL( size0, 2 );

    const size_type size1 = meta::integral::at< typename layout23::sizes, 1 >::value;
    BOOST_CHECK_EQUAL( size1, 3 );

    const stride_type stride0 = meta::integral::at< typename layout23::strides, 0 >::value;
    BOOST_CHECK_EQUAL( stride0, 3 );

    const stride_type stride1 = meta::integral::at< typename layout23::strides, 1 >::value;
    BOOST_CHECK_EQUAL( stride1, 1 );

  }

BOOST_AUTO_TEST_SUITE_END()