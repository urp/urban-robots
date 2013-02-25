/*  interface_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_interface/interface.hpp"
# include "utk/math/fixed_size/multidim/impl_interface/at.hpp"

# include "utk/math/fixed_size/multidim/impl_slice_layout/slice_layout.hpp"
# include "utk/math/fixed_size/multidim/impl_slice_layout/fix_index.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::interface
#include <boost/test/unit_test.hpp>


using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::multidim;


struct fixture
{
  typedef layout< size_vector<1,2,3> > layout123;
  typedef interface< double, vector::unmanaged_tag, layout123 > type123;
  double  data6[ layout123::total_size ];
  type123    multidim123;

  fixture() : data6{ 0.,1.,2.,3.,4.,5. }, multidim123( data6 ) { }
};

BOOST_FIXTURE_TEST_SUITE( check_constructors, fixture )

  BOOST_AUTO_TEST_CASE( check_construct_with_nullptr )
  {
    type123 test_multidim( nullptr );
  }

  BOOST_AUTO_TEST_CASE( copy )
  {
    // check identical copy
    type123 id_copy( multidim123 );

    BOOST_CHECK_EQUAL( at( id_copy, 0,0,0 ) , 0. );
    BOOST_CHECK_EQUAL( at( id_copy, 0,0,1 ) , 1. );
    BOOST_CHECK_EQUAL( at( id_copy, 0,0,2 ) , 2. );
    BOOST_CHECK_EQUAL( at( id_copy, 0,1,0 ) , 3. );
    BOOST_CHECK_EQUAL( at( id_copy, 0,1,1 ) , 4. );
    BOOST_CHECK_EQUAL( at( id_copy, 0,1,2 ) , 5. );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE( sliced_layout_tests, fixture )

  BOOST_AUTO_TEST_CASE( copy_handle_other_layout )
  {
    // check general copy
    typedef interface< double, vector::unmanaged_tag, slice_layout< layout123, index_vector<1,0,3> > > fixed_type;

    fixed_type fixed_copy( multidim123.storage );

    BOOST_CHECK_EQUAL( at( fixed_copy, 0,0 ) , 0. );
    BOOST_CHECK_EQUAL( at( fixed_copy, 0,1 ) , 1. );
    BOOST_CHECK_EQUAL( at( fixed_copy, 0,2 ) , 2. );

  }

  BOOST_AUTO_TEST_CASE( at_with_fixed_dimensions )
  {
    typedef layout< size_vector<2,3,4> > unfixed_layout;
    typedef typename fix_index< unfixed_layout, 2, 2 >::type layout;
    typedef interface< double, vector::unmanaged_tag, layout > type;
    double  data[ layout::total_size ] = {  0.,  1., 2., 3., 4., 5.
                                         ,  6.,  7., 8., 9.,10.,11.
                                         , 12., 13.,14.,15.,16.,17.
                                         , 18., 19.,20.,21.,22.,23.};
    type multidim( data );

    size_type unfixed_offset = unfixed_layout::static_offset();
    size_type layout_offset = layout::static_offset();
    BOOST_MESSAGE( "unfixed offset: " << unfixed_offset << " fixed offset: "<< layout_offset );

    //right
    BOOST_CHECK_EQUAL( at( multidim, 0,0 ) , 2. );
    BOOST_CHECK_EQUAL( at( multidim, 0,1 ) , 6. );
    BOOST_CHECK_EQUAL( at( multidim, 0,2 ) , 10. );
    BOOST_CHECK_EQUAL( at( multidim, 1,0 ) , 14. );
    BOOST_CHECK_EQUAL( at( multidim, 1,1 ) , 18. );
    BOOST_CHECK_EQUAL( at( multidim, 1,2 ) , 22. );
  }

BOOST_AUTO_TEST_SUITE_END();
