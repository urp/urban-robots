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

# include "utk/math/fixed_size/vector_interface.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector_interface
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( constructors )
{
  vector_interface<double,1> d1_invalid = vector_interface<double,1>::invalid;
  BOOST_CHECK_EQUAL( d1_invalid.is_valid(), false );

  int data_i1[] = { 1 };
  const vector_interface<int,1> i1( data_i1 );
  BOOST_CHECK( i1.is_valid() );
  BOOST_CHECK_EQUAL( &i1[0]    , data_i1 );
  BOOST_CHECK_EQUAL(  i1.ptr() , data_i1 );
  BOOST_CHECK_EQUAL(  i1.size, 1 );
  BOOST_CHECK_EQUAL(  i1[0]    , 1 );

  double data_d4[] { 1., 2., 3., 4. };
  const vector_interface<double,4> d4( data_d4 );
  BOOST_CHECK_EQUAL( d4.size, 4 );
  BOOST_CHECK_EQUAL( d4[0]    , 1. );
  BOOST_CHECK_EQUAL( d4[1]    , 2. );
  BOOST_CHECK_EQUAL( d4[2]    , 3. );
  BOOST_CHECK_EQUAL( d4[3]    , 4. );

  const vector_interface<double,4> copy( d4 );
  BOOST_CHECK_EQUAL( copy.size, d4.size );
  BOOST_CHECK_EQUAL( copy.ptr() , d4.ptr() );
  BOOST_CHECK_EQUAL( copy[0]    , 1 );

  const vector_interface<double,3> shrink_copy( d4 );
  size_t shrink_copy_size = shrink_copy.size;
  BOOST_CHECK_EQUAL( shrink_copy_size, copy.size-1 );
  BOOST_CHECK_EQUAL( shrink_copy.ptr() , d4.ptr() );
  BOOST_CHECK_EQUAL( shrink_copy[0]    , 1. );
  BOOST_CHECK_EQUAL( shrink_copy[1]    , 2. );
  BOOST_CHECK_EQUAL( shrink_copy[2]    , 3. );
}

BOOST_AUTO_TEST_CASE( assignment_operators )
{
  double data_d3[] { 1., 2., 3. };
  const vector_interface<double,3> d3( data_d3 );
  BOOST_CHECK_EQUAL( &d3[0], data_d3 );

  double data2_d3[] { 4., 5., 6. };
  vector_interface<double,3> d3_copy( data2_d3 );
  d3_copy = d3;
  BOOST_CHECK_EQUAL( d3_copy[0], 1. );
  BOOST_CHECK_EQUAL( d3_copy[1], 2. );
  BOOST_CHECK_EQUAL( d3_copy[2], 3. );

  double data_d2[] { 7., 8. };
  vector_interface<double,2> d2( data_d2 );
  d2 = d3;
  BOOST_CHECK_EQUAL( d2[0], 1. );
  BOOST_CHECK_EQUAL( d2[1], 2. );
  BOOST_CHECK_EQUAL( d3[0], 1. );
  BOOST_CHECK_EQUAL( d3[1], 2. );
}

BOOST_AUTO_TEST_CASE( pointer_interface )
{
  double data[] { 1., 2. };
  vector_interface<double,2> d2( data );

  BOOST_CHECK_EQUAL( &d2[0], d2.ptr() );

  d2.unref();
  BOOST_CHECK_EQUAL( &d2[0], static_cast<double*>(0) );

  d2.ref( data );
  BOOST_CHECK_EQUAL( &d2[0], data );

}

BOOST_AUTO_TEST_CASE( shift )
{
  double data[] { 1., 2., 3., 4., 5., 6., 7. };
  vector_interface<double,3> d3( data );

  // shift
  d3.ref( data );
  d3.shift(2);
  BOOST_REQUIRE_EQUAL( d3.ptr(), data+2 );

  d3.shift(-2);
  BOOST_CHECK_EQUAL( d3.ptr(), data );

}

BOOST_AUTO_TEST_CASE( data_access )
{
  double data_d3[] { 1., 2., 3. };
  vector_interface<double,3> d3( data_d3 );

  // iterators
  BOOST_CHECK_EQUAL( *d3.begin(), 1. );
  BOOST_CHECK_EQUAL( *(d3.end()-1), 3. );

  // operator()
  BOOST_CHECK_EQUAL( d3(0), 1. );
  BOOST_CHECK_EQUAL( d3(2), 3. );

  // operator[]
  d3(0) = 1.1;
  BOOST_CHECK_EQUAL( data_d3[0], 1.1 );

  d3[1] = 2.2;
  BOOST_CHECK_EQUAL( data_d3[1], 2.2 );
}

BOOST_AUTO_TEST_CASE( conversion_operators )
{
  //---| operator bool()

  bool data_bool[] { true, true, true, false };
  vector_interface<bool,3> many( data_bool );
  //BOOST_CHECK_EQUAL( many , true );
  many.shift(1);
  BOOST_CHECK_EQUAL( bool(many), false );

  vector_interface<bool,1> one( data_bool+2 );
  BOOST_CHECK_EQUAL( bool(one) , true );
  one.shift(1);
  BOOST_CHECK_EQUAL( bool(one) , false );

  //---| operator T() - only for vector_interface<T,1>
  int data_int[] { 1, 2, 3, 0 };
  vector_interface<int,1> b( data_int+1 );
  BOOST_CHECK_EQUAL( b , 2 );
  BOOST_CHECK_EQUAL( int(b) , 2 );

}
