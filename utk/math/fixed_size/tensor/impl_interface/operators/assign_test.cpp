/*  assign_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/tensor/impl_interface/interface.hpp"
# include "utk/math/fixed_size/tensor/impl_interface/io.hpp"
# include "utk/math/fixed_size/tensor/impl_array/array.hpp"
# include "utk/math/fixed_size/tensor/impl_array/io.hpp"
# include "utk/math/fixed_size/tensor/impl_interface/make_layout.hpp"

# include "utk/math/fixed_size/tensor/impl_interface/operators/assign.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor::interface operator assign
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;


struct fixture
{
  typedef typename tensor::make_layout< tensor::size_vector<1>, tensor::contravariant_tag >::type contra_layout;
  typedef tensor::interface< int, contra_layout > type123;
  int dataA[1];
  type123 tensorA;


  fixture() : dataA{ 1 }, tensorA( dataA )  {}
};

BOOST_FIXTURE_TEST_SUITE( check_at, fixture )

  BOOST_AUTO_TEST_CASE( check_assign_to_array )
  {
    int dataB[1] = { 2 };
    tensor::array< int, contra_layout > tensorB( dataB );

    std::cerr << "before A " << tensorA ;

    std::cerr << "before B " << tensorB ;

    tensorB = tensorA;

    std::cerr << "after A " << tensorA ;

    std::cerr << "after B " << tensorB ;

    BOOST_CHECK_EQUAL( at( tensorB, 0 ),  1 );
  }

BOOST_AUTO_TEST_SUITE_END()


/*
struct fixture
{
  typedef typename tensor::make_layout< tensor::size_vector<1,2,3>, tensor::contravariant_tag >::type contra_layout;
  typedef tensor::interface< int, contra_layout > type123;
  int dataA[6];
  type123 tensorA;


  fixture() : dataA{ 1,2,3,4,5,6 }, tensorA( dataA )  {}
};

BOOST_FIXTURE_TEST_SUITE( check_at, fixture )

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
    int dataB[6] = { 2,3,4,5,6,7 };
    tensor::array< int, contra_layout > tensorB( dataB );

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
*/
