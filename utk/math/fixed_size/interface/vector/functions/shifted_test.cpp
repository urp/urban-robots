/*  shifted_test.cpp - Copyright Peter Urban 2009

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

# include "utk/math/fixed_size/interface/vector/functions/shifted.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE fixed_size::interface::vector shifted
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::interface::vector;

BOOST_AUTO_TEST_CASE( check_shifted )
{
  double data[] { 1., 2., 3., 4., 5., 6., 7. };
  interface<double,3> d3( data+2 );
  const interface<double,3> shifted_plus_2 = shifted<2,3>(d3);
  auto shifted_plus_2_size = shifted_plus_2.size;

  BOOST_CHECK_EQUAL(  shifted_plus_2_size, 3 );
  BOOST_CHECK_EQUAL(  shifted_plus_2.ptr(), data+4 );

  const interface<double,3> shifted_minus_2 = shifted<-2,3>(d3);

  BOOST_CHECK_EQUAL( shifted_minus_2.ptr(), data+0 );
}
