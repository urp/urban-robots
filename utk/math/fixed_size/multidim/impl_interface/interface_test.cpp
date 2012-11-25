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
# include "utk/math/fixed_size/multidim/impl_slice_layout/slice_layout.hpp"
# include "utk/math/fixed_size/multidim/impl_slice_layout/fix_index.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::interface
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size::multidim;

BOOST_AUTO_TEST_CASE( construct_with_initial_layout )
{
  typedef layout< size_vector<1,2,3> > layout;
  typedef interface< double, layout > multidim;
  multidim test_multidim( nullptr );
}

BOOST_AUTO_TEST_CASE( at_with_free_dimensions )
{
  typedef layout< size_vector<1,2,3> > layout;
  typedef interface< double, layout > type;
  double  data[ layout::total_size ] = { 0.,1.,2.,3.,4.,5. };
  type   multidim( data );

  //right
  BOOST_CHECK_EQUAL( multidim.at( 0,0,0 ) , 0. );
  BOOST_CHECK_EQUAL( multidim.at( 0,0,1 ) , 1. );
  BOOST_CHECK_EQUAL( multidim.at( 0,0,2 ) , 2. );
  BOOST_CHECK_EQUAL( multidim.at( 0,1,0 ) , 3. );
  BOOST_CHECK_EQUAL( multidim.at( 0,1,1 ) , 4. );
  BOOST_CHECK_EQUAL( multidim.at( 0,1,2 ) , 5. );
}

BOOST_AUTO_TEST_CASE( copy )
{
  typedef layout< size_vector<1,2,3> > layout;
  typedef interface< double, layout > type;
  double  data[ layout::total_size ] = { 0.,1.,2.,3.,4.,5. };
  type original( data );

  // check identical copy
  type id_copy( original );

  BOOST_CHECK_EQUAL( id_copy.at( 0,0,0 ) , 0. );
  BOOST_CHECK_EQUAL( id_copy.at( 0,0,1 ) , 1. );
  BOOST_CHECK_EQUAL( id_copy.at( 0,0,2 ) , 2. );
  BOOST_CHECK_EQUAL( id_copy.at( 0,1,0 ) , 3. );
  BOOST_CHECK_EQUAL( id_copy.at( 0,1,1 ) , 4. );
  BOOST_CHECK_EQUAL( id_copy.at( 0,1,2 ) , 5. );
}

BOOST_AUTO_TEST_SUITE( sliced_layout_tests )

  BOOST_AUTO_TEST_CASE( copy_with_other_layout )
  {
    typedef layout< size_vector<1,2,3> > layout;
    typedef interface< double, layout > type;
    double  data[ layout::total_size ] = { 0.,1.,2.,3.,4.,5. };
    type original( data );

    // check general copy
    typedef interface< double, slice_layout< layout, index_vector<1,0,3> > > fixed_type;

    fixed_type fixed_copy( original );
    type copy( fixed_copy );

    BOOST_CHECK_EQUAL( copy.at( 0,0,0 ) , 0. );
    BOOST_CHECK_EQUAL( copy.at( 0,0,1 ) , 1. );
    BOOST_CHECK_EQUAL( copy.at( 0,0,2 ) , 2. );
    BOOST_CHECK_EQUAL( copy.at( 0,1,0 ) , 3. );
    BOOST_CHECK_EQUAL( copy.at( 0,1,1 ) , 4. );
    BOOST_CHECK_EQUAL( copy.at( 0,1,2 ) , 5. );
  }


  BOOST_AUTO_TEST_CASE( at_with_fixed_dimensions )
  {
    typedef layout< size_vector<2,3,4> > unfixed_layout;
    typedef typename fix_index< unfixed_layout, 2, 2 >::type layout;
    typedef interface< double, layout > type;
    double  data[ layout::total_size ] = {  0.,  1., 2., 3., 4., 5.
                                         ,  6.,  7., 8., 9.,10.,11.
                                         , 12., 13.,14.,15.,16.,17.
                                         , 18., 19.,20.,21.,22.,23.};
    type multidim( data );

    size_type unfixed_offset = unfixed_layout::static_offset();
    size_type layout_offset = layout::static_offset();
    BOOST_MESSAGE( "unfixed offset: " << unfixed_offset << " fixed offset: "<< layout_offset );

    //right
    BOOST_CHECK_EQUAL( multidim.at( 0,0 ) , 2. );
    BOOST_CHECK_EQUAL( multidim.at( 0,1 ) , 6. );
    BOOST_CHECK_EQUAL( multidim.at( 0,2 ) , 10. );
    BOOST_CHECK_EQUAL( multidim.at( 1,0 ) , 14. );
    BOOST_CHECK_EQUAL( multidim.at( 1,1 ) , 18. );
    BOOST_CHECK_EQUAL( multidim.at( 1,2 ) , 22. );

  }

BOOST_AUTO_TEST_SUITE_END();