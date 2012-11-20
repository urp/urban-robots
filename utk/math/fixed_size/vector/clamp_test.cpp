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

# include "utk/math/fixed_size/vector/array.hpp"
# include "utk/math/fixed_size/vector/at.hpp"
# include "utk/math/fixed_size/vector/clamp.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE fixed_size::vector clamp_min/clamp_max test
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::vector;

struct double3_data
{
  double data_d3[3];
  const interface<double,3> d3;

  double3_data() : data_d3{ 1., 2., 3. }, d3( data_d3 ) {}
};

BOOST_FIXTURE_TEST_SUITE( check_double3_data, double3_data )

BOOST_AUTO_TEST_CASE( clamp_min_to_scalar )
{
  array<double,3> min_s(d3);
  clamp_min(min_s,1.5);
  BOOST_CHECK_EQUAL( at( min_s, 0 ), 1.5 );
  BOOST_CHECK_EQUAL( at( min_s, 1 ), 2. );
  BOOST_CHECK_EQUAL( at( min_s, 2 ), 3. );
}

BOOST_AUTO_TEST_CASE( clamp_max_to_scalar )
{
  array<double,3> max_s(d3);
  clamp_max(max_s,1.5);
  BOOST_CHECK_EQUAL( at( max_s, 0 ), 1. );
  BOOST_CHECK_EQUAL( at( max_s, 1 ), 1.5 );
  BOOST_CHECK_EQUAL( at( max_s, 2 ), 1.5 );
}

BOOST_AUTO_TEST_CASE( clamp_min_to_vector )
{
  array<double,3> min_v(d3);
  clamp_min(min_v, array<double,3>{ 0.9, 2.1, 1.} );
  BOOST_CHECK_EQUAL( at( min_v, 0 ), 1. );
  BOOST_CHECK_EQUAL( at( min_v, 1 ), 2.1 );
  BOOST_CHECK_EQUAL( at( min_v, 2 ), 3. );
}

BOOST_AUTO_TEST_CASE( clamp_max_to_vector )
{
  array<double,3> max_v(d3);
  clamp_max(max_v, array<double,3>{ 0.9, 2.1, 1.} );
  BOOST_CHECK_EQUAL( at( max_v, 0 ), 0.9 );
  BOOST_CHECK_EQUAL( at( max_v, 1 ), 2. );
  BOOST_CHECK_EQUAL( at( max_v, 2 ), 1. );
}

BOOST_AUTO_TEST_SUITE_END()
