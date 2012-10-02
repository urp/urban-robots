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

# include "utk/math/fixed_size/vector_array.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector array test
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( veca_constructors )
{
  //---default

  vector_array<double,4>	empty;
  BOOST_CHECK( empty.is_valid() );
  auto empty_size = empty.size;
  BOOST_CHECK_EQUAL( empty_size, 4 );

  //---copy

  double data_orig[] { 1., 2., 3., 4. };
  const vector_interface<double,4> orig( data_orig );
  auto orig_size = orig.size;
  BOOST_CHECK_EQUAL( orig_size, sizeof(data_orig)/sizeof(double) );

  const vector_array<double,4> copy( orig );
  size_t copy_size = copy.size;
  BOOST_CHECK_EQUAL( copy_size, orig_size );
  BOOST_CHECK_NE   ( copy.ptr() , orig.ptr() );
  BOOST_CHECK_EQUAL( copy[0]    , 1. );
  BOOST_CHECK_EQUAL( copy[1]    , 2. );
  BOOST_CHECK_EQUAL( copy[2]    , 3. );
  BOOST_CHECK_EQUAL( copy[3]    , 4. );

  const vector_array<double,3> shrink_copy( orig );
  auto shrink_copy_size = shrink_copy.size;
  BOOST_CHECK_EQUAL( shrink_copy_size, orig_size-1 );
  BOOST_CHECK_NE   ( shrink_copy.ptr() , orig.ptr() );
  BOOST_CHECK_EQUAL( shrink_copy[0]    , 1. );
  BOOST_CHECK_EQUAL( shrink_copy[1]    , 2. );
  BOOST_CHECK_EQUAL( shrink_copy[2]    , 3. );

  const vector_array<double,5> part_copy( orig );

  size_t part_copy_size = part_copy.size;
  BOOST_CHECK_EQUAL( part_copy_size, orig_size+1 );
  BOOST_CHECK_NE   ( part_copy.ptr() , orig.ptr() );
  BOOST_CHECK_EQUAL( part_copy[0]    , 1. );
  BOOST_CHECK_EQUAL( part_copy[1]    , 2. );
  BOOST_CHECK_EQUAL( part_copy[2]    , 3. );
  BOOST_CHECK_EQUAL( part_copy[3]    , 4. );

  //---initializer list

  const vector_array<double,4> init{ 1., 2., 3., 4. };
  auto init_size = init.size;
  BOOST_CHECK_EQUAL( init_size, 4 );
  BOOST_CHECK_EQUAL( init[0]    , 1. );
  BOOST_CHECK_EQUAL( init[1]    , 2. );
  BOOST_CHECK_EQUAL( init[2]    , 3. );
  BOOST_CHECK_EQUAL( init[3]    , 4. );

  //---sequence

  const std::vector<double> vec{ 1., 2., 3., 4. };
  const vector_array<double,4> seq(vec.begin(),vec.end());
  auto seq_size = seq.size;
  BOOST_CHECK_EQUAL( seq_size, 4 );
  BOOST_CHECK_EQUAL( seq[0]    , 1. );
  BOOST_CHECK_EQUAL( seq[1]    , 2. );
  BOOST_CHECK_EQUAL( seq[2]    , 3. );
  BOOST_CHECK_EQUAL( seq[3]    , 4. );

# ifdef UTK_MATH_FIXED_SIZE_VECTORS__VALARRAY_SUPPORT
  std::valarray<double> valarr(3);
  valarr[0] = 1.;
  valarr[1] = 2.;
  valarr[2] = 3.;
  vector_array<double,3> valarr_copy(valarr);
  BOOST_CHECK_EQUAL( valarr_copy[0], 1. );
  BOOST_CHECK_EQUAL( valarr_copy[1], 2. );
  BOOST_CHECK_EQUAL( valarr_copy[2], 3. );
# endif
}
