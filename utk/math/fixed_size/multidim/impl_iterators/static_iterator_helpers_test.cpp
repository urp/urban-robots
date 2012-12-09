/*  static_iterator_test.cpp - Copyright Peter Urban 2012

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

//# include "utk/math/fixed_size/multidim/impl_interface/interface.hpp"
//# include "utk/math/fixed_size/multidim/impl_interface/change_layout.hpp"

# include "utk/math/fixed_size/multidim/impl_iterators/static_iterator_helpers.hpp"

# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE multidim::static_iterator helpers
# include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size::multidim;

BOOST_AUTO_TEST_SUITE( check_static_iterator_helpers )

  BOOST_AUTO_TEST_CASE( check_index_to_indices )
  {
    typedef index_vector< 0,0 > i0;
    typedef stride_vector< 2,1 > str2; // coresponding to sizes (x,2)

    // first element -> coords (0,0)
    typedef typename helpers::index_to_indices< str2, 0 >::type i0;
    constexpr index_type i0_0 = meta::integral::at< i0, 0 >::value;
    BOOST_CHECK_EQUAL( i0_0, 0 );
    constexpr index_type i0_1 = meta::integral::at< i0, 1 >::value;
    BOOST_CHECK_EQUAL( i0_1, 0 );
    // second element -> coords (0,1)
    typedef typename helpers::index_to_indices< str2, 1 >::type i1;
    constexpr index_type i1_0 = meta::integral::at< i1, 0 >::value;
    BOOST_CHECK_EQUAL( i1_0, 0 );
    constexpr index_type i1_1 = meta::integral::at< i1, 1 >::value;
    BOOST_CHECK_EQUAL( i1_1, 1 );

    typedef typename helpers::index_to_indices< str2, 2 >::type i2;
    constexpr index_type i2_0 = meta::integral::at< i2, 0 >::value;
    BOOST_CHECK_EQUAL( i2_0, 1 );
    constexpr index_type i2_1 = meta::integral::at< i2, 1 >::value;
    BOOST_CHECK_EQUAL( i2_1, 0 );

    typedef typename helpers::index_to_indices< str2, 3 >::type i3;
    constexpr index_type i3_0 = meta::integral::at< i3, 0 >::value;
    BOOST_CHECK_EQUAL( i3_0, 1 );
    constexpr index_type i3_1 = meta::integral::at< i3, 1 >::value;
    BOOST_CHECK_EQUAL( i3_1, 1 );
  }

  BOOST_AUTO_TEST_CASE( check_advance_digits )
  {
    typedef index_vector< 0,0 > i0;
    typedef size_vector< 2,2 > s23;

    // indices (0,0) -> (0,1)
    typedef typename helpers::advance_digits< i0, s23, 1 >::type i1;
    constexpr index_type i1_0 = meta::integral::at< i1, 0 >::value;
    BOOST_CHECK_EQUAL( i1_0, 0 );
    constexpr index_type i1_1 = meta::integral::at< i1, 1 >::value;
    BOOST_CHECK_EQUAL( i1_1, 1 );

    // indices (0,1) -> (1,0)
    typedef typename helpers::advance_digits< i1, s23, 1 >::type i2;
    constexpr index_type i2_0 = meta::integral::at< i2, 0 >::value;
    BOOST_CHECK_EQUAL( i2_0, 1 );
    constexpr index_type i2_1 = meta::integral::at< i2, 1 >::value;
    BOOST_CHECK_EQUAL( i2_1, 0 );
  }

  BOOST_AUTO_TEST_CASE( check_end_indices )
  {
    typedef index_vector< 0,0 > i0;
    typedef meta::integral::vector< size_type, 2,2 > s23;

    // indices (0,0) -> (0,1)
    typedef typename helpers::advance_digits< i0, s23, 1 >::type i1;
    // indices (0,1) -> (1,0)
    typedef typename helpers::advance_digits< i1, s23, 1 >::type i2;
    // indices (1,0) -> (1,1)
    //typedef typename helpers::advance_digits< i2, s23, 1 >::type i3;
    // indices (1,1) -> (2,2)
    typedef typename meta::integral::make_vector< index_type
                                                 , typename meta::integral::transform< s23, meta::integral::minus< index_type, 1 > >::type
                                                 //, typename meta::integral::minus< s23, size_type(1) >::type
                                                 >::type i3;
    typedef typename helpers::advance_digits< i3, s23, 1 >::type iend;


    constexpr index_type ie_0 = meta::integral::at< iend, 0 >::value;
    BOOST_CHECK_EQUAL( ie_0, 2 );
    constexpr index_type ie_1 = meta::integral::at< iend, 1 >::value;
    BOOST_CHECK_EQUAL( ie_1, 2 );
  }

BOOST_AUTO_TEST_SUITE_END()
