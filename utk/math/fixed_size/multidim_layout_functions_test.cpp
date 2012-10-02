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

# include "utk/math/fixed_size/multidim_layout_functions.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim layout functions
#include <boost/test/unit_test.hpp>

using namespace utk::math;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( layout_is_index_fixed )
{
  // not fixed
  typedef initial_layout< 1,9,8,4 > layout1;
  bool not_fixed1 = not is_index_fixed< layout1, 0 >::value;
  BOOST_CHECK( not_fixed1 );


  typedef multidim_layout< index_vector< 1,9,3,4 >, size_vector< 1,9,8,4 > > layout2;
  bool not_fixed2 = not is_index_fixed< layout2, 0 >::value;
  BOOST_CHECK( not_fixed2 );

  bool fixed2 = is_index_fixed< layout2, 2 >::value;
  BOOST_CHECK( fixed2 );


}
