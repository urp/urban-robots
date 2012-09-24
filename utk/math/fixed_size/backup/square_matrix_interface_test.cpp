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

# include "utk/math/fixed_size/square_matrix_interface.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE square matrix interface test
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( matn_constructors )
{
  matn<double,1> invalid = matn<double,1>::invalid;
  BOOST_CHECK_EQUAL( invalid.is_valid(), false );

  int data_i1[] = { 1 };
  const matn<int,1> i1( data_i1 );
  BOOST_CHECK( i1.is_valid() );
  BOOST_CHECK_EQUAL(  i1[0].ptr() , data_i1 );
  BOOST_CHECK_EQUAL(  i1.ptr()    , data_i1 );
  BOOST_CHECK_EQUAL(  i1.size()   , 1 );
  BOOST_CHECK_EQUAL(  i1[0]       , 1 );

  double data_d4[] { 1., 2., 3., 4. };
  const matn<double,2> d4( data_d4 );
  BOOST_CHECK_EQUAL( d4.size(), 4 );
  BOOST_CHECK_EQUAL( *(d4.ptr()+0) , 1. );
  BOOST_CHECK_EQUAL( *(d4.ptr()+1) , 2. );
  BOOST_CHECK_EQUAL( *(d4.ptr()+2) , 3. );  
  BOOST_CHECK_EQUAL( *(d4.ptr()+3) , 4. );    

  const matn<double,2> copy( d4 );
  BOOST_CHECK_EQUAL( copy.size(), d4.size() );
  BOOST_CHECK_EQUAL( copy.ptr() , d4.ptr() );
  BOOST_CHECK_EQUAL( *copy.ptr(), 1. );
    
}

BOOST_AUTO_TEST_CASE( matn_assignment_operators )
{
  double data1[] { 1., 2., 3., 4. };
  const matn<double,2> d22( data1 );
  BOOST_CHECK_EQUAL( d22.ptr(), data1 );

  double data2[] { 5., 6., 7., 8. };
  matn<double,2> copy( data2 );
  copy = d22;
  BOOST_CHECK_EQUAL( copy[0][0], 1. );
  BOOST_CHECK_EQUAL( copy[0][1], 2. );
  BOOST_CHECK_EQUAL( copy[1][0], 3. );
  BOOST_CHECK_EQUAL( copy[1][1], 4. );
  
}

BOOST_AUTO_TEST_CASE( matn_pointer_interface )
{
  double data_d4[] { 1., 2., 3., 4. };
  matn<double,2> d22( data_d4 );
  BOOST_CHECK_EQUAL( &d22[0], d22.ptr() );

  // unref
  d22.unref();
  BOOST_CHECK_EQUAL( &d22[0], static_cast<double*>(0) );

  // ref
  d22.ref( data_d4 );
  BOOST_CHECK_EQUAL( &d22[0], data_d4 );

  // operator*()
  BOOST_CHECK_EQUAL( d22.ptr(), (*d22).ptr() );
  BOOST_CHECK_EQUAL( (*d22).size(), 2 );
  
  // operator->()
  //vector_interface<double,2> vec = vector_interface<double,2>::invalid ;
  //vec.ref( d22.operator->().ptr() );
  //vec.ref( (*d22).ptr() );
  //BOOST_CHECK_EQUAL( d22.ptr(), (*d22->ptr() );

  // operator&()
  BOOST_CHECK_EQUAL( &d22[0], data_d4 );
}

BOOST_AUTO_TEST_CASE( matn_iterator_interface )
{
  double data[] { 1., 2., 3., 4., 5., 6., 7. };
  // increment
  matn<double,2> d22( data );
  BOOST_CHECK_EQUAL( (++d22).ptr(), data+4 );

  d22.ref( data );
  BOOST_CHECK_EQUAL( (d22++).ptr(), data );
  BOOST_CHECK_EQUAL( d22.ptr(), data+4 );

  // decrement
  d22.ref( data + 4 );
  BOOST_CHECK_EQUAL( (--d22).ptr(), data );

  d22.ref( data + 4 );
  BOOST_CHECK_EQUAL( (d22--).ptr(), data+4 );
  BOOST_CHECK_EQUAL( d22.ptr(), data );

  // shift
  d22.ref( data );
  d22.shift(2);
  BOOST_REQUIRE_EQUAL( d22.ptr(), data+2 );

  d22.shift(-2);
  BOOST_CHECK_EQUAL( d22.ptr(), data );
}

BOOST_AUTO_TEST_CASE( matn_data_access )
{
  double data_d4[] { 1., 2., 3., 4. };
  matn<double,2> d22( data_d4 );

  // iterators
  BOOST_CHECK_EQUAL( *d22.begin(), 1. );
  BOOST_CHECK_EQUAL( *(d22.end()-1), 4. );  

  // operator[]
  BOOST_CHECK_EQUAL( d22[0][0] , 1. );
  BOOST_CHECK_EQUAL( d22[0][1] , 2. );
  BOOST_CHECK_EQUAL( d22[1][0] , 3. );
  BOOST_CHECK_EQUAL( **d22     , 1. );

  // operator()
  BOOST_CHECK_EQUAL( d22(0,0), 1. );
  BOOST_CHECK_EQUAL( d22(1,1), 4. );  

  // at()
  BOOST_CHECK_EQUAL( d22.at(0,0), 1. );
  BOOST_CHECK_EQUAL( d22.at(1,1), 4. );  
  BOOST_CHECK_THROW( d22.at(1,3), std::out_of_range );

  d22.at(0,1) = 2.2;
  BOOST_CHECK_EQUAL( data_d4[1], 2.2 );

  d22[1][0] = 3.3;
  BOOST_CHECK_EQUAL( data_d4[2], 3.3 );
}

