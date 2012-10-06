/*  multidim_interface_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim_array.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim array
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( construct_with_uninitialized_data )
{
  typedef multidim_layout< size_vector<1,2,3> > layout;
  typedef multidim_array< double, layout > multidim;
  multidim test_multidim;

  test_multidim.at( 0,0,0 ) = 1.;

  BOOST_CHECK_EQUAL( test_multidim.at( 0,0,0 ), 1. );
}
