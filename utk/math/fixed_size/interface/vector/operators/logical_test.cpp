/*  operators.cpp - Copyright Peter Urban 2009

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

# include "utk/math/fixed_size/interface/vector/operators/logical.hpp"

# include "utk/math/fixed_size/interface/vector/operators/comparison.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector operators
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::interface::vector;

struct fixture
{
  bool data_true_one[3];
  const interface<bool,3>  true_one;

  bool data_false_one[3];
  const interface<bool,3> false_one;

  fixture()
  : data_true_one { false,  true, false }, true_one( data_true_one )
  , data_false_one{  true, false,  true }, false_one( data_false_one )
  { }
};


BOOST_FIXTURE_TEST_SUITE( check_io, fixture )

BOOST_AUTO_TEST_CASE( check_logical_operators )
{
  // unitary
  BOOST_CHECK_EQUAL( !true_one, false_one );
}


BOOST_AUTO_TEST_SUITE_END()
