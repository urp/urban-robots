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

# include "utk/math/fixed_size/vector_functions.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector functions test
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size;


BOOST_AUTO_TEST_CASE( vecn_named_element_access )
{
  double data_d4[] { 1., 2., 3., 4. };
  const vector_interface<double,4> d4( data_d4 );
  BOOST_CHECK_EQUAL( x(d4), 1. );
  BOOST_CHECK_EQUAL( y(d4), 2. );
  BOOST_CHECK_EQUAL( z(d4), 3. );
  BOOST_CHECK_EQUAL( w(d4), 4. );
  
  const vector_interface<double,2> d2( xy(d4) );
  BOOST_CHECK_EQUAL( x(d2), 1. );
  BOOST_CHECK_EQUAL( y(d2), 2. );

  const vector_interface<double,3> d3( xyz(d4) );
  BOOST_CHECK_EQUAL( x(d3), 1. );
  BOOST_CHECK_EQUAL( y(d3), 2. );
  BOOST_CHECK_EQUAL( z(d3), 3. );
}

BOOST_AUTO_TEST_CASE( vecn_min_max_functions )
{
  double data_d4[] { 1., 2., 3., 4. };
  const vector_interface<double,4> d4( data_d4 );
  BOOST_CHECK_EQUAL( min(d4), 1. );
  BOOST_CHECK_EQUAL( max(d4), 4. );
}

BOOST_AUTO_TEST_CASE( vecn_normal )
{
  double data_d3[] { 1., 2., 3., };
  const double len = std::hypot( 1., std::hypot( 2., 3. ) );
  vector_interface<double,3> d3( data_d3 );
  vector_array<double,3> d3_copy( normal(d3) );
  normalize(d3);

  BOOST_CHECK_EQUAL( d3, d3_copy );  
  BOOST_CHECK_EQUAL( d3.at(0), 1./len );
  BOOST_CHECK_EQUAL( d3.at(1), 2./len );
  BOOST_CHECK_EQUAL( d3.at(2), 3./len );
}

BOOST_AUTO_TEST_CASE( vecn_clamp )
{
  double data_d3[] { 1., 2., 3. };
  const vector_interface<double,3> d3( data_d3 );

  //---| clamp to scalar

  vector_array<double,3> min_s(d3);
  clamp_min(min_s,1.5);
  BOOST_CHECK_EQUAL( min_s.at(0), 1.5 );  
  BOOST_CHECK_EQUAL( min_s.at(1), 2. );  
  BOOST_CHECK_EQUAL( min_s.at(2), 3. );

  vector_array<double,3> max_s(d3);
  clamp_max(max_s,1.5);
  BOOST_CHECK_EQUAL( max_s.at(0), 1. );  
  BOOST_CHECK_EQUAL( max_s.at(1), 1.5 );  
  BOOST_CHECK_EQUAL( max_s.at(2), 1.5 );

  //---| clamp to vector

  vector_array<double,3> min_v(d3);
  clamp_min(min_v, vector_array<double,3>{ 0.9, 2.1, 1.} );
  BOOST_CHECK_EQUAL( min_v.at(0), 1. );  
  BOOST_CHECK_EQUAL( min_v.at(1), 2.1 );  
  BOOST_CHECK_EQUAL( min_v.at(2), 3. );

  vector_array<double,3> max_v(d3);
  clamp_max(max_v, vector_array<double,3>{ 0.9, 2.1, 1.} );
  BOOST_CHECK_EQUAL( max_v.at(0), 0.9 );  
  BOOST_CHECK_EQUAL( max_v.at(1), 2. );  
  BOOST_CHECK_EQUAL( max_v.at(2), 1. );
}

BOOST_AUTO_TEST_CASE( vecn_abs )
{
  double data_d3[] { -1., 2., -3. };
  const vector_interface<double,3> d3( data_d3 );
  vector_array<double,3> d3_abs = abs(d3);
  BOOST_CHECK_EQUAL( d3_abs.at(0), 1. );  
  BOOST_CHECK_EQUAL( d3_abs.at(1), 2. );  
  BOOST_CHECK_EQUAL( d3_abs.at(2), 3. );
}

//-----| abs
BOOST_AUTO_TEST_CASE( vecn_sgn )
{
  double data_d3[] { -1., 0., 3. };
  const vector_interface<double,3> d3( data_d3 );
  vector_array<double,3> d3_sgn = sgn(d3);
  BOOST_CHECK_EQUAL( d3_sgn.at(0), -1. );  
  BOOST_CHECK_EQUAL( d3_sgn.at(1),  0. );  
  BOOST_CHECK_EQUAL( d3_sgn.at(2),  1. );
}

//-----| floor
BOOST_AUTO_TEST_CASE( vecn_floor )
{
  double data_d3[] { -1., 2.8, -3.4 };
  const vector_interface<double,3> d3( data_d3 );
  vector_array<double,3> d3_floor = floor(d3);
  BOOST_CHECK_EQUAL( d3_floor.at(0), -1. );  
  BOOST_CHECK_EQUAL( d3_floor.at(1),  2. );  
  BOOST_CHECK_EQUAL( d3_floor.at(2), -4. );
}

//-----| ceil
BOOST_AUTO_TEST_CASE( vecn_ceil )
{
  double data_d3[] { -1.4, 2.5, -3.6 };
  const vector_interface<double,3> d3( data_d3 );
  vector_array<double,3> d3_ceil = ceil(d3);
  BOOST_CHECK_EQUAL( d3_ceil.at(0), -1. );  
  BOOST_CHECK_EQUAL( d3_ceil.at(1),  3. );  
  BOOST_CHECK_EQUAL( d3_ceil.at(2), -3. );
}
  
//-----| sum
BOOST_AUTO_TEST_CASE( vecn_sum )
{
  double data_d3[] { 4. , -2., -3. };
  const vector_interface<double,3> d3( data_d3 );
  BOOST_CHECK_EQUAL( sum(d3), 4.-2.-3. );  
}

BOOST_AUTO_TEST_CASE( vecn_shifted )
{
  double data[] { 1., 2., 3., 4., 5., 6., 7. };
  vector_interface<double,3> d3( data+2 );
  const vector_interface<double,3> shifted_plus_2 = shifted<2,3>(d3);
  BOOST_CHECK_EQUAL(  shifted_plus_2.ptr(), data+4 );
  BOOST_CHECK_EQUAL(  shifted_plus_2.size(), 3 );

  const vector_interface<double,3> shifted_minus_2 = shifted<-2,3>(d3);
  BOOST_CHECK_EQUAL( shifted_minus_2.ptr(), data+0 );
}

//-----| flipped
BOOST_AUTO_TEST_CASE( vecn_flipped )
{
  double data_d3[] { 1., 2., 3. };
  const vector_interface<double,3> d3( data_d3 );
  vector_array<double,3> d3_flipped = flipped(d3);
  BOOST_CHECK_EQUAL( d3_flipped.at(0), 3. );  
  BOOST_CHECK_EQUAL( d3_flipped.at(1), 2. );  
  BOOST_CHECK_EQUAL( d3_flipped.at(2), 1. );
}

//-----| dot
BOOST_AUTO_TEST_CASE( vecn_dot )
{
  double data_a[] { 2., 0., 1. };
  const vector_interface<double,3> a( data_a );
  double data_b[] { 0., 1., 0. };
  const vector_interface<double,3> b( data_b );
  double data_c[] { M_PI, 3.3125, 1./3. };
  const vector_interface<double,3> c( data_c );

  BOOST_CHECK_EQUAL( dot( a, a ), 2.*2. + 1.*1. );
  BOOST_CHECK_EQUAL( dot( a, b ), 0. );
  BOOST_CHECK_EQUAL( dot( c, a ), dot( a, c ) );
  BOOST_CHECK_EQUAL( dot( a * 3., c * 2. ), 3. * dot( a * 2., c ) );
}

//-----| cross
BOOST_AUTO_TEST_CASE( vecn_cross )
{
  double data_a[] { 2., 0., 1. };
  const vector_interface<double,3> a( data_a );
  double data_b[] { 0., 1., 0. };
  const vector_interface<double,3> b( data_b );
  double data_c[] { M_PI, 3.3125, 1./3. };
  const vector_interface<double,3> c( data_c );

  vector_array<double,3> a_cross_b{ 0.*0.-1.*1., 1.*0.-2.*0., 2.*1.-0.*0. };

  BOOST_CHECK_EQUAL( cross( a, a ), 0. );
  BOOST_CHECK_EQUAL( cross( a, b ),  a_cross_b );
  BOOST_CHECK_EQUAL( cross( b, a ), -a_cross_b );

  BOOST_CHECK_EQUAL( cross( a * 3., c * 2. ), cross( a, c ) * 3. * 2. );
}

//-----| cross3
BOOST_AUTO_TEST_CASE( vecn_cross3 )
{
  double data_a[] { 2., 0., 1. };
  const vector_interface<double,3> a( data_a );
  double data_b[] { 0., 1., 0. };
  const vector_interface<double,3> b( data_b );
  double data_c[] { M_PI, 3.3125, 1./3. };
  const vector_interface<double,3> c( data_c );

  BOOST_CHECK_EQUAL( cross( a, cross( b, c ) ), cross3( a, b, c ) );
  BOOST_CHECK_EQUAL( cross3( a,b,c ) + cross3( c,a,b ) + cross3( b,c,a ), 0. );
}

//-----| length
BOOST_AUTO_TEST_CASE( vecn_length )
{
  double data_d3[] { .00001, 2., 30000., };

  const double len_d3 = std::hypot( data_d3[0], std::hypot( data_d3[1], data_d3[2] ) );
  vector_interface<double,3> d3( data_d3 );
  BOOST_CHECK_EQUAL( length(d3), len_d3 );  

  const double len_d2 = std::hypot( data_d3[0], data_d3[1] );
  vector_interface<double,2> d2( data_d3 );
  BOOST_CHECK_EQUAL( length(d2), len_d2 );  

  const size_t N = 100;
  vector_array<double,N> dN( 2. );
  BOOST_CHECK_EQUAL( length(dN), sqrt( 2.*2.*N ) );  
}

//-----| distance
BOOST_AUTO_TEST_CASE( vecn_distance )
{
  double data_a[] { 1., 2., 3., };
  vector_interface<double,3> a( data_a );

  double data_b[] { 2., 4., 6., };
  vector_interface<double,3> b( data_b );

  const double dist = std::hypot( b[0]-a[0], std::hypot( b[1]-a[1], b[2]-a[2] ) );

  BOOST_CHECK_EQUAL( distance(a,b), dist );  
}
