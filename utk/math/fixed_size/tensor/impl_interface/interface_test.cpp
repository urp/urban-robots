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

# include "utk/math/fixed_size/tensor/interface.hpp"
# include "utk/math/fixed_size/multidim/slice_layout.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor::interface
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::tensor;

struct fixture123
{
  typedef variance_vector< covariant,covariant,covariant > variances;
  typedef typename make_layout< size_vector<1,2,3>, variances >::type layout123;
  typedef interface< double, layout123 > type123;

  double  data[ layout123::total_size ];
  type123 tensor123;

  fixture123() : data{ 0.,1.,2.,3.,4.,5. }, tensor123( data ) {}
};

BOOST_FIXTURE_TEST_SUITE( check_fixture123, fixture123 )

  BOOST_AUTO_TEST_CASE( with_layout )
  {
    BOOST_CHECK_EQUAL( tensor123.at( 0,0,0 ) , 0. );
    BOOST_CHECK_EQUAL( tensor123.at( 0,0,1 ) , 1. );
    BOOST_CHECK_EQUAL( tensor123.at( 0,0,2 ) , 2. );
    BOOST_CHECK_EQUAL( tensor123.at( 0,1,0 ) , 3. );
    BOOST_CHECK_EQUAL( tensor123.at( 0,1,1 ) , 4. );
    BOOST_CHECK_EQUAL( tensor123.at( 0,1,2 ) , 5. );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE( with_slice_layout )
{
  typedef multidim::layout< multidim::size_vector<3,2,3> > unfixed_layout;
  typedef typename multidim::fix_index< unfixed_layout, 2, 2 >::type layout32_2;
  typedef variance_vector< covariant,covariant > variances;
  typedef typename make_layout< layout32_2, variances >::type tensor_layout;

  typedef interface< double, tensor_layout > type;
  double  data[ tensor_layout::total_size ] = {  0., 1., 2., 3., 4., 5.
                                              ,  6.,  7., 8., 9.,10.,11.
                                              , 12., 13.,14.,15.,16.,17. };
  type   tensor32( data );

  //right
  BOOST_CHECK_EQUAL( tensor32.at( 0,0 ) , 2. );
  BOOST_CHECK_EQUAL( tensor32.at( 0,1 ) , 5. );
  BOOST_CHECK_EQUAL( tensor32.at( 1,0 ) , 8. );
  BOOST_CHECK_EQUAL( tensor32.at( 1,1 ) , 11. );
  BOOST_CHECK_EQUAL( tensor32.at( 2,0 ) , 14. );
  BOOST_CHECK_EQUAL( tensor32.at( 2,1 ) , 17. );

}
