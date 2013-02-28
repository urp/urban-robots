/*  slice_layout_test.cpp - Copyright Peter Urban 2009

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

# include "utk/meta/integral/integral.hpp"

# include "utk/math/fixed_size/multidim/impl_slice_layout/slice_layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim slice layout
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::multidim;

//---| nothing fixed |-------------------------------------------------/

struct nothing_fixed_234
{
    typedef layout< size_vector<2,3,4> > old_layout;
    typedef slice_layout< old_layout, index_vector< 2,3,4 > > layout234;
};

BOOST_FIXTURE_TEST_SUITE( nothing_fixed, nothing_fixed_234 )

  BOOST_AUTO_TEST_CASE( layout_stride )
  {
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
    const index_type order = layout234::order;
    BOOST_CHECK_EQUAL( order, 3 );

    const size_type total_size = layout234::total_size;
    BOOST_CHECK_EQUAL( total_size, 24 );

    std::array< size_type, 3 > size_array = meta::integral::make_array< typename layout234::sizes >::value;
    BOOST_CHECK_EQUAL( size_array[0], 2 );
  }

  BOOST_AUTO_TEST_CASE( index_offset )
  {
    const stride_type old_offset_111 = layout234::index_offset( 1,1,1 );
    const stride_type offset_111 = layout234::index_offset( 1,1,1 );
    BOOST_CHECK_EQUAL( offset_111, old_offset_111 );
  }

  BOOST_AUTO_TEST_CASE( static_offset )
  {
    const stride_type offset = layout234::static_offset();
    BOOST_CHECK_EQUAL( offset, 0 );
  }


BOOST_AUTO_TEST_SUITE_END()


//---| first fixed |---------------------------------------------------/

struct first_fixed_234
{
    typedef layout< size_vector<2,3,4> > old_layout;
    typedef slice_layout< old_layout, index_vector< 1,3,4 > > layout34;
};

BOOST_FIXTURE_TEST_CASE( unmask_index, first_fixed_234 )
{
  const index_type unmask0 = helpers::unmask_index< layout34::visibility_mask, 0 >::value;
  BOOST_CHECK_EQUAL( unmask0, 1 );

  const index_type unmask1 = helpers::unmask_index< layout34::visibility_mask, 1 >::value;
  BOOST_CHECK_EQUAL( unmask1, 2 );

}


BOOST_FIXTURE_TEST_SUITE( first_fixed, first_fixed_234 )

  BOOST_AUTO_TEST_CASE( sizes )
  {
    index_type fixed0 = meta::integral::at< typename layout34::sizes, 0 >::value;
    BOOST_CHECK_EQUAL( fixed0 , 3 );

    index_type fixed1 = meta::integral::at< typename layout34::sizes, 1 >::value;
    BOOST_CHECK_EQUAL( fixed1 , 4 );
  }

  BOOST_AUTO_TEST_CASE( index_offset )
  {
    const stride_type fixed_11 = layout34::index_offset( 1,1 );
    BOOST_CHECK_EQUAL( fixed_11, 5 );
  }

  BOOST_AUTO_TEST_CASE( static_offset )
  {
    const stride_type fixed1 = layout34::static_offset();
    BOOST_CHECK_EQUAL( fixed1, 12 );
  }

BOOST_AUTO_TEST_SUITE_END()
