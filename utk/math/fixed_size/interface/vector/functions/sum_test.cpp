/*  sum_test.cpp - Copyright Peter Urban 2009

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

# include "utk/math/fixed_size/interface/vector/functions/sum.hpp"

# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE fixed_size::interface::vector sum
# include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::interface::vector;

BOOST_AUTO_TEST_CASE( check_sum )
{
  double data_d3[] { 4., -2., -3. };
  const interface< double, 3 > d3( data_d3 );
  BOOST_CHECK_EQUAL( sum( d3 ), 4.-2.-3. );
}
