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


# include "utk/math/special_functions/sgn.hpp"

#define BOOST_TEST_MODULE utk::math::sgn test
#include <boost/test/unit_test.hpp>

using namespace utk::math;

BOOST_AUTO_TEST_CASE( sign_function )
{
  BOOST_CHECK_EQUAL( sgn(1) , 1 );
  BOOST_CHECK_EQUAL( sgn(-1), -1 );
  BOOST_CHECK_EQUAL( sgn(0) , 0 );

  BOOST_CHECK_EQUAL( sgn(1.1) , 1 );
  BOOST_CHECK_EQUAL( sgn(-1.2), -1 );
  BOOST_CHECK_EQUAL( sgn(0.) , 0 );
}
