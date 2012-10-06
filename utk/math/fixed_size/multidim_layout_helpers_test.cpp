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

# include "utk/math/fixed_size/multidim_layout_helpers.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim layout helpers
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( strides_sequence_helper )
{
  typedef helpers::stride_sequence< size_vector<2,3,4,5> >::type strides;

  static const stride_type s0 = meta::integral::at< strides, 0 >::value;
  BOOST_CHECK_EQUAL( s0, 60 );
  static const stride_type s1 = meta::integral::at< strides, 1 >::value;
  BOOST_CHECK_EQUAL( s1, 20 );
  static const stride_type s2 = meta::integral::at< strides, 2 >::value;
  BOOST_CHECK_EQUAL( s2, 5 );
  static const stride_type s3 = meta::integral::at< strides, 3 >::value;
  BOOST_CHECK_EQUAL( s3, 1 );
}

BOOST_AUTO_TEST_CASE( total_size_helper )
{
  typedef size_vector<2,3,4,5> sizes;
  typedef helpers::stride_sequence< sizes >::type strides;

  size_t total1 = helpers::total_size< sizes, strides >::value;
  BOOST_CHECK_EQUAL( total1, 120 );

  size_t total2 = helpers::total_size< size_vector< >, stride_vector< > >::value;
  BOOST_CHECK_EQUAL( total2, 1 );

}
