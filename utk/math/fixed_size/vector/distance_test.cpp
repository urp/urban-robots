/*  distance_test.cpp - Copyright Peter Urban 2009

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

# include "utk/math/fixed_size/vector/distance.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE fixed_size::vector distance test
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::vector;

BOOST_AUTO_TEST_CASE( check_distance )
{
  double data_a[] { 1., 2., 3., };
  interface<double,3> a( data_a );

  double data_b[] { 2., 4., 6., };
  interface<double,3> b( data_b );

  const double dist = std::hypot( b[0]-a[0], std::hypot( b[1]-a[1], b[2]-a[2] ) );

  BOOST_CHECK_EQUAL( distance(a,b), dist );
}
