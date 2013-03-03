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

# include "utk/math/fixed_size/interface/vector/interface.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE utk::math::fixed_size::interface::vector::interface
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::interface::vector;

struct fixture_d3
{
  double data_d3[3] ;
  const interface<double,3> d3;

  fixture_d3() : data_d3{ 1., 2., 3. }, d3( data_d3 ) {}
};

BOOST_AUTO_TEST_CASE( check_is_invalid )
{
  interface<double,1> d1_invalid = interface<double,1>::invalid;
  BOOST_CHECK_EQUAL( d1_invalid.is_valid(), false );
}

BOOST_FIXTURE_TEST_SUITE( check_constructors, fixture_d3 )

  BOOST_AUTO_TEST_CASE( check_ptr )
  {
    BOOST_CHECK_EQUAL( &d3[0], d3.ptr() );
    BOOST_CHECK_EQUAL(  d3.ptr() , data_d3 );
  }

  BOOST_AUTO_TEST_CASE( check_valid )
  {
    BOOST_CHECK( d3.is_valid() );
  }

  BOOST_AUTO_TEST_CASE( check_size )
  {
    BOOST_CHECK_EQUAL( d3.size, 3 );
  }

  BOOST_AUTO_TEST_CASE( check_constructor )
  {
    BOOST_CHECK_EQUAL( d3[0]    , 1. );
    BOOST_CHECK_EQUAL( d3[1]    , 2. );
    BOOST_CHECK_EQUAL( d3[2]    , 3. );
  }

  BOOST_AUTO_TEST_CASE( copy_constructor )
  {
    const interface<double,3> copy( d3 );
    BOOST_CHECK_EQUAL( copy.size, d3.size );
    BOOST_CHECK_EQUAL( copy.ptr() , d3.ptr() );
    BOOST_CHECK_EQUAL( copy[0]    , 1 );
  }

  BOOST_AUTO_TEST_CASE( shrink_copy_constructor )
  {
    const interface<double,2> shrink_copy( d3 );
    size_t shrink_copy_size = shrink_copy.size;
    BOOST_CHECK_EQUAL( shrink_copy_size  , d3.size-1 );
    BOOST_CHECK_EQUAL( shrink_copy.ptr() , d3.ptr() );
    BOOST_CHECK_EQUAL( shrink_copy[0]    , 1. );
    BOOST_CHECK_EQUAL( shrink_copy[1]    , 2. );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE( assignment_operators, fixture_d3 )

  BOOST_AUTO_TEST_CASE( normal_assignment )
  {
    double data2_d3[] { 4., 5., 6. };
    interface<double,3> d3_copy( data2_d3 );
    d3_copy = d3;
    BOOST_CHECK_EQUAL( d3_copy[0], 1. );
    BOOST_CHECK_EQUAL( d3_copy[1], 2. );
    BOOST_CHECK_EQUAL( d3_copy[2], 3. );
  }

  BOOST_AUTO_TEST_CASE( shrink_assignment )
  {
    double data_d2[] { 5., 6. };
    interface<double,2> d2( data_d2 );
    d2 = d3;
    BOOST_CHECK_EQUAL( d2[0], d3[0] );
    BOOST_CHECK_EQUAL( d2[1], d3[1] );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE( pointer_management, fixture_d3 )

  BOOST_AUTO_TEST_CASE( check_unref )
  {
    interface<double,2> d2( data_d3 );
    d2.unref();
    BOOST_CHECK_EQUAL( &d2[0], static_cast<double*>(0) );
  }

  BOOST_AUTO_TEST_CASE( pointer_interface )
  {
    interface<double,2> d2( nullptr );
    d2.ref( data_d3 );
    BOOST_CHECK_EQUAL( &d2[0], data_d3 );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE( shift )
{
  double data[] { 1., 2., 3., 4., 5., 6., 7. };
  interface<double,3> d3( data );

  // shift
  d3.ref( data );
  d3.shift(2);
  BOOST_REQUIRE_EQUAL( d3.ptr(), data+2 );

  d3.shift(-2);
  BOOST_CHECK_EQUAL( d3.ptr(), data );
}

BOOST_FIXTURE_TEST_SUITE( data_access, fixture_d3 )

  BOOST_AUTO_TEST_CASE( check_iterator_begin )
  {
    BOOST_CHECK_EQUAL( *d3.begin(), 1. );
  }

  BOOST_AUTO_TEST_CASE( check_iterator_end )
  {
    BOOST_CHECK_EQUAL( *(d3.end()-1), 3. );
  }

  BOOST_AUTO_TEST_CASE( check_parenthesis )
  {
    BOOST_CHECK_EQUAL( d3(0), 1. );
    BOOST_CHECK_EQUAL( d3(2), 3. );
  }

  BOOST_AUTO_TEST_CASE( check_brackets )
  {
    double data_d2[] { 1.,2. };
    interface< double, 2 > d2( data_d2 );
    d2(0) = 1.1;
    BOOST_CHECK_EQUAL( data_d2[0], 1.1 );
    d2[1] = 2.2;
    BOOST_CHECK_EQUAL( data_d2[1], 2.2 );
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( check_conversion_operators )

  BOOST_AUTO_TEST_CASE( check_operator_bool )
  {
    bool data_bool[] { true, true, true, false };
    interface<bool,3> many( data_bool );

    many.shift(1);
    BOOST_CHECK_EQUAL( bool(many), false );

    interface<bool,1> one( data_bool+2 );
    BOOST_CHECK_EQUAL( bool(one) , true );
    one.shift(1);
    BOOST_CHECK_EQUAL( bool(one) , false );
  }

  BOOST_AUTO_TEST_CASE( check_operator_T )
  {
    //---| operator T() - only for interface<T,1>
    int data_int[] { 1, 2, 3, 0 };
    interface<int,1> scalar( data_int+1 );
    BOOST_CHECK_EQUAL( scalar , 2 );
    BOOST_CHECK_EQUAL( int(scalar) , 2 );
  }

BOOST_AUTO_TEST_SUITE_END()
