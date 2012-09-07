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

# include <type_traits>

# include "utk/math/integral/constant.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE integral constant
#include <boost/test/unit_test.hpp>

using namespace utk::math::integral;


BOOST_AUTO_TEST_CASE( type_consistency )
{
  typedef constant< int, -1 > const_int;
  bool type_match = std::is_same< const_int::value_type, const int >::value;
  BOOST_CHECK( type_match );
}

BOOST_AUTO_TEST_CASE( value_consistency )
{
  typedef constant< int, -1 > const_int;
  int value = const_int::value;
  BOOST_CHECK_EQUAL( value, -1 );
}

