/*  multidim_interface_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim_interface.hpp"
# include "utk/math/fixed_size/multidim_slice_layout.hpp"
# include "utk/math/fixed_size/multidim_slice_fix_index.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim interface
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( construct_with_initial_layout )
{
  typedef multidim_layout< size_vector<1,2,3> > layout;
  typedef multidim_interface< double, layout > multidim;
  multidim test_multidim( nullptr );
}

BOOST_AUTO_TEST_CASE( multidim_at_with_free_dimensions )
{
  typedef multidim_layout< size_vector<1,2,3> > layout;
  typedef multidim_interface< double, layout > multidim_type;
  double  data[ layout::total_size ] = { 0.,1.,2.,3.,4.,5. };
  multidim_type   multidim( data );

  //right
  BOOST_CHECK_EQUAL( multidim.at( 0,0,0 ) , 0. );
  BOOST_CHECK_EQUAL( multidim.at( 0,0,1 ) , 1. );
  BOOST_CHECK_EQUAL( multidim.at( 0,0,2 ) , 2. );
  BOOST_CHECK_EQUAL( multidim.at( 0,1,0 ) , 3. );
  BOOST_CHECK_EQUAL( multidim.at( 0,1,1 ) , 4. );
  BOOST_CHECK_EQUAL( multidim.at( 0,1,2 ) , 5. );
}

BOOST_AUTO_TEST_CASE( multidim_copy )
{
  typedef multidim_layout< size_vector<1,2,3> > layout;
  typedef multidim_interface< double, layout > multidim_type;
  double  data[ layout::total_size ] = { 0.,1.,2.,3.,4.,5. };
  multidim_type original( data );

  // check identical copy
  multidim_type id_copy( original );

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
    typedef multidim_layout< size_vector<1,2,3> > layout;
    typedef multidim_interface< double, layout > multidim_type;
    double  data[ layout::total_size ] = { 0.,1.,2.,3.,4.,5. };
    multidim_type original( data );

    // check general copy
    typedef multidim_interface< double, multidim_slice_layout< layout, index_vector<1,0,3> > > fixed_type;

    fixed_type fixed_copy( original );
    multidim_type copy( fixed_copy );

    BOOST_CHECK_EQUAL( copy.at( 0,0,0 ) , 0. );
    BOOST_CHECK_EQUAL( copy.at( 0,0,1 ) , 1. );
    BOOST_CHECK_EQUAL( copy.at( 0,0,2 ) , 2. );
    BOOST_CHECK_EQUAL( copy.at( 0,1,0 ) , 3. );
    BOOST_CHECK_EQUAL( copy.at( 0,1,1 ) , 4. );
    BOOST_CHECK_EQUAL( copy.at( 0,1,2 ) , 5. );
  }


  BOOST_AUTO_TEST_CASE( multidim_at_with_fixed_dimensions )
  {
    typedef multidim_layout< size_vector<2,3,4> > unfixed_layout;
    typedef typename fix_index< unfixed_layout, 2, 2 >::type layout;
    typedef multidim_interface< double, layout > multidim_type;
    double  data[ layout::total_size ] = {  0.,  1., 2., 3., 4., 5.
                                         ,  6.,  7., 8., 9.,10.,11.
                                         , 12., 13.,14.,15.,16.,17.
                                         , 18., 19.,20.,21.,22.,23.};
    multidim_type multidim( data );

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

// integrate of delete
BOOST_AUTO_TEST_CASE( random_testing )
{
  typedef index_vector<2,3,4> old_indices;
  typedef size_vector<2,3,4>	old_sizes;

  typedef multidim_layout< old_indices , old_sizes > old_layout;
  typedef multidim_interface< double, old_layout > old_multidim;
  old_multidim old_test_multidim(0);

  const int old_indices_size = boost::mpl::size< old_indices::mpl_vector_c >::type::value;
  BOOST_CHECK_EQUAL( old_indices_size, 3 );


  typedef meta::integral::assign< old_indices, 0, meta::integral::constant< index_type, 7 > >::type new_indices;
  typedef meta::integral::assign< old_sizes  , 0, meta::integral::constant< size_type, 9 > >::type new_sizes;

  typedef multidim_layout< new_indices , new_sizes > new_layout;
  typedef multidim_interface< double, new_layout > new_multidim;
  new_multidim new_test_multidim( nullptr );

  const int new_index = boost::mpl::at_c< new_indices::mpl_vector_c, 0 >::type::value;
  BOOST_CHECK_EQUAL( new_index, 7 );

  const int new_size = meta::integral::at< new_sizes, 0 >::value;
  BOOST_CHECK_EQUAL( new_size, 9 );


  const int new_indices_size = boost::mpl::size< new_indices::mpl_vector_c >::type::value;
  BOOST_CHECK_EQUAL( new_indices_size, 3 );
}
