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

using namespace utk::math;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_SUITE( compile_time_information )

  BOOST_AUTO_TEST_CASE( layout_stride )
  {
    typedef multidim_layout< index_vector<2,3,4>, size_vector<2,3,4> > layout;

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
    typedef multidim_layout< index_vector<2,3,4>, size_vector<2,3,4> > layout;

    const index_type order = layout::order;
    BOOST_CHECK_EQUAL( order, 3 );

    BOOST_CHECK_EQUAL( layout::total_size, 24 );


    std::array< size_type, 3 > size_array = utk::math::integral::make_array< layout::sizes >::value;
    BOOST_CHECK_EQUAL( size_array[0], 2 );
  }

  BOOST_AUTO_TEST_CASE( fix_dimension )
  {
    typedef multidim_layout< index_vector<2,3,4>, size_vector<2,3,4> > layout;

    // fix
    typedef typename layout::fix_index< 0, 1 >::type fixed;

    index_type fixed0 = integral::at< typename fixed::indices, 0 >::value;
    BOOST_CHECK_EQUAL( fixed0 , 1 );

    // remove_fixed
    typedef typename fixed::remove_fixed::type removed;

    index_type removed0 = integral::at< typename removed::indices, 0 >::value;
    BOOST_CHECK_EQUAL( removed0, 3 );
    index_type removed1 = integral::at< typename removed::indices, 1 >::value;
    BOOST_CHECK_EQUAL( removed1, 4 );

    BOOST_CHECK_EQUAL( removed::total_size, 12 );

    const index_type order = removed::order;
    BOOST_CHECK_EQUAL( order, 2 );

    // unfix
    typedef typename layout::release_index< 0 >::type unfixed;
    BOOST_CHECK_EQUAL( unfixed::total_size, 24 );
    index_type unfixed0 = integral::at< unfixed::indices, 0 >::value;
    BOOST_CHECK_EQUAL( unfixed0, 2 );

  }

  // used by index_offset & fixed_coord_offset
  BOOST_AUTO_TEST_CASE( strides_stripping_and_reversal )
  {

    typedef helpers::stride_sequence< size_vector<2,3,4,5> >::type strides;

    // remove last element (total_size) from strides
    typedef typename integral::pop_front< strides >::tail strides_tail;
    // reverse strides (last index has stride=1)
    typedef typename integral::reverse< strides_tail >::type strides_reverse;

    strides         strides_instance;
    strides_reverse strides_reverse_instance;

    BOOST_TEST_MESSAGE( strides_instance << " -> " << strides_reverse_instance );
  }

  BOOST_AUTO_TEST_CASE( index_offset )
  {
    typedef multidim_layout< index_vector<1,2,3,4>, size_vector<1,2,3,4> > layout;

    const stride_type offset_111 = layout::index_offset( 0,1,1,1 );
    BOOST_CHECK_EQUAL( offset_111, 17 );

    // fix
    typedef typename layout::fix_index< 3, 0 >::type fixed;

    const stride_type fixed_11 = fixed::index_offset( 0,1,1 );
    BOOST_CHECK_EQUAL( fixed_11, 16 );
  }

  BOOST_AUTO_TEST_CASE( fixed_coord_offset )
  {
    typedef multidim_layout< index_vector<2,3,4,5>, size_vector<2,3,4,5> > layout;

    const stride_type offset = layout::static_offset();
    BOOST_CHECK_EQUAL( offset, 0 );

    // fix 1
    typedef typename layout::fix_index< 1, 1 >::type fixed0100;

    const stride_type fixed1 = fixed0100::static_offset();
    BOOST_CHECK_EQUAL( fixed1, 20 );

    // fix 1
    typedef typename fixed0100::fix_index< 2, 2 >::type fixed0120;

    const stride_type fixed2 = fixed0120::static_offset();
    BOOST_CHECK_EQUAL( fixed2, 30 );


  }

BOOST_AUTO_TEST_SUITE_END()
