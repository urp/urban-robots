/*  length_test.cpp - Copyright Peter Urban 2009

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

# include "utk/math/fixed_size/interface/vector/array.hpp"
# include "utk/math/fixed_size/interface/vector/functions/length.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE fixed_size::interface::vector length
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::interface::vector;

BOOST_AUTO_TEST_CASE( check_length )
{
  double data_d3[] { .00001, 2., 30000., };

  const double len_d3 = std::hypot( data_d3[0], std::hypot( data_d3[1], data_d3[2] ) );
  interface<double,3> d3( data_d3 );
  BOOST_CHECK_EQUAL( length(d3), len_d3 );

  const double len_d2 = std::hypot( data_d3[0], data_d3[1] );
  interface<double,2> d2( data_d3 );
  BOOST_CHECK_EQUAL( length(d2), len_d2 );

  const size_t N = 100;
  array<double,N> dN( 2. );
  BOOST_CHECK_EQUAL( length(dN), std::sqrt( 2.*2.*N ) );
}
