/*  tensor_interface_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/tensor_interface.hpp"
# include "utk/math/fixed_size/multidim_slice_layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor interface
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( construct_with_initial_layout )
{
  typedef multidim_layout< size_vector<1,2,3> > layout;
  typedef meta::integral::vector< variance_type, covariant,covariant,covariant > variances;
  typedef tensor_interface< double, layout, variances > tensor;
  tensor test_tensor( nullptr );
}

BOOST_AUTO_TEST_CASE( tensor_at_with_free_dimensions )
{
  typedef multidim_layout< size_vector<1,2,3> > layout;
  typedef meta::integral::vector< variance_type, covariant,covariant,covariant > variances;
  typedef tensor_interface< double, layout, variances > tensor_type;
  double  data[ layout::total_size ] = { 0.,1.,2.,3.,4.,5. };
  tensor_type tensor( data );

  //right
  BOOST_CHECK_EQUAL( tensor.at( 0,0,0 ) , 0. );
  BOOST_CHECK_EQUAL( tensor.at( 0,0,1 ) , 1. );
  BOOST_CHECK_EQUAL( tensor.at( 0,0,2 ) , 2. );
  BOOST_CHECK_EQUAL( tensor.at( 0,1,0 ) , 3. );
  BOOST_CHECK_EQUAL( tensor.at( 0,1,1 ) , 4. );
  BOOST_CHECK_EQUAL( tensor.at( 0,1,2 ) , 5. );
}

BOOST_AUTO_TEST_CASE( tensor_at_with_fixed_dimensions )
{
  typedef multidim_slice_layout< multidim_layout< size_vector<3,2,3> > > unfixed_layout;
  typedef typename unfixed_layout::fix_index< 2, 2 >::type layout;
  typedef meta::integral::vector< variance_type, covariant,covariant > variances;
  typedef tensor_interface< double, layout, variances > tensor_type;
  double  data[ layout::total_size ] = {  0., 1., 2., 3., 4., 5.
                                       ,  6.,  7., 8., 9.,10.,11.
                                       , 12., 13.,14.,15.,16.,17. };
  tensor_type   tensor( data );

  //right
  BOOST_CHECK_EQUAL( tensor.at( 0,0 ) , 2. );
  BOOST_CHECK_EQUAL( tensor.at( 0,1 ) , 5. );
  BOOST_CHECK_EQUAL( tensor.at( 1,0 ) , 8. );
  BOOST_CHECK_EQUAL( tensor.at( 1,1 ) , 11. );
  BOOST_CHECK_EQUAL( tensor.at( 2,0 ) , 14. );
  BOOST_CHECK_EQUAL( tensor.at( 2,1 ) , 17. );

}
