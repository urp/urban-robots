/*  interface_test.cpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/interface/vector.hpp"

# include "utk/math/fixed_size/layout/generic_layout.hpp"
# include "utk/math/fixed_size/layout/slice_layout.hpp"

# include "utk/math/fixed_size/interface/tensor/interface.hpp"

# include "utk/math/fixed_size/interface/tensor/functions/make_layout.hpp"
# include "utk/math/fixed_size/interface/tensor/functions/at.hpp"

# include "utk/math/fixed_size/interface/tensor/operators/io.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor::interface
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::interface;
using namespace utk::math::fixed_size::interface::tensor;

struct fixture123
{
  typedef variance_vector< covariant,covariant,covariant > variances;
  typedef typename make_layout< size_vector<1,2,3>, variances >::type layout123;
  typedef interface< double, vector::unmanaged_tag, layout123 > type123;

  double  data[ layout123::total_size ];
  type123 tensor123;

  fixture123() : data{ 0.,1.,2.,3.,4.,5. }, tensor123( data ) {}
};

BOOST_AUTO_TEST_SUITE( intiallize_interface )

  BOOST_FIXTURE_TEST_CASE( with_layout, fixture123 )
  {
    BOOST_CHECK_EQUAL( at( tensor123, 0,0,0 ) , 0. );
    BOOST_CHECK_EQUAL( at( tensor123, 0,0,1 ) , 1. );
    BOOST_CHECK_EQUAL( at( tensor123, 0,0,2 ) , 2. );
    BOOST_CHECK_EQUAL( at( tensor123, 0,1,0 ) , 3. );
    BOOST_CHECK_EQUAL( at( tensor123, 0,1,1 ) , 4. );
    BOOST_CHECK_EQUAL( at( tensor123, 0,1,2 ) , 5. );
  }

  BOOST_AUTO_TEST_CASE( with_slice_layout )
  {
    typedef layout::generic_layout< size_vector<3,2,3> > unfixed_layout;
    typedef typename layout::fix_index< unfixed_layout, 2, 2 >::type layout32_2;
    typedef variance_vector< covariant,covariant > variances;
    typedef typename make_layout< layout32_2, variances >::type tensor_layout;

    typedef interface< double, vector::unmanaged_tag, tensor_layout > type;
    double  data[ tensor_layout::total_size ] = {  0., 1., 2., 3., 4., 5.
                                                ,  6.,  7., 8., 9.,10.,11.
                                                , 12., 13.,14.,15.,16.,17. };
    type   tensor32( data );

    //right
    BOOST_CHECK_EQUAL( at( tensor32, 0,0 ) , 2. );
    BOOST_CHECK_EQUAL( at( tensor32, 0,1 ) , 5. );
    BOOST_CHECK_EQUAL( at( tensor32, 1,0 ) , 8. );
    BOOST_CHECK_EQUAL( at( tensor32, 1,1 ) , 11. );
    BOOST_CHECK_EQUAL( at( tensor32, 2,0 ) , 14. );
    BOOST_CHECK_EQUAL( at( tensor32, 2,1 ) , 17. );

  }

BOOST_AUTO_TEST_SUITE_END()

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struct fixture
{
  typedef typename make_layout< size_vector<1,2,3>, tensor::contravariant_tag >::type contra_layout;
  typedef interface< int, vector::unmanaged_tag, contra_layout > type123;
  int dataA[6];
  type123 tensorA;


  fixture() : dataA{ 1,2,3,4,5,6 }, tensorA( dataA )  {}
};

BOOST_FIXTURE_TEST_SUITE( check_assign_operator, fixture )

  BOOST_AUTO_TEST_CASE( check_assign_to_interface )
  {
    int dataB[6] = { 2,3,4,5,6,7 };
    type123 tensorB( dataB );

    tensorB = tensorA;

    BOOST_CHECK_EQUAL( at( tensorB, 0,0,0 ),  1 );
    BOOST_CHECK_EQUAL( at( tensorB, 0,0,1 ),  2 );
    BOOST_CHECK_EQUAL( at( tensorB, 0,0,2 ),  3 );
    BOOST_CHECK_EQUAL( at( tensorB, 0,1,0 ),  4 );
    BOOST_CHECK_EQUAL( at( tensorB, 0,1,1 ),  5 );
    BOOST_CHECK_EQUAL( at( tensorB, 0,1,2 ),  6 );
  }

  BOOST_AUTO_TEST_CASE( check_assign_to_array )
  {
    typedef typename interface_traits< type123 >::managed_interface array_type;
    array_type tensorB( typename array_type::storage_type( 0 ) );

    BOOST_TEST_MESSAGE( "before A " << tensorA );

    BOOST_TEST_MESSAGE( "before B " << tensorB );

    tensorB = tensorA;

    BOOST_TEST_MESSAGE( "after A " << tensorA );

    BOOST_TEST_MESSAGE( "after B " << tensorB );

    BOOST_CHECK_EQUAL( at( tensorB, 0,0,0 ),  1 );
    BOOST_CHECK_EQUAL( at( tensorB, 0,0,1 ),  2 );
    BOOST_CHECK_EQUAL( at( tensorB, 0,0,2 ),  3 );
    BOOST_CHECK_EQUAL( at( tensorB, 0,1,0 ),  4 );
    BOOST_CHECK_EQUAL( at( tensorB, 0,1,1 ),  5 );
    BOOST_CHECK_EQUAL( at( tensorB, 0,1,2 ),  6 );
  }

BOOST_AUTO_TEST_SUITE_END()
