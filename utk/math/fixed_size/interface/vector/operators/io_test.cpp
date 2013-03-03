/*  io_test.cpp - Copyright Peter Urban 2009-2013

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

# include "utk/math/fixed_size/interface/vector/operators/io.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE utk:math::fixed_size::interface::vector::operators io
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::interface::vector;

struct output_fixture
{
  double data_one[3] ;
  const interface<double,3> one;
  output_fixture() : data_one{ 1., 2., 3. }, one(data_one)
  {}
};

BOOST_FIXTURE_TEST_SUITE( check_io, output_fixture )

  BOOST_AUTO_TEST_CASE( check_output_operators )
  {
    BOOST_TEST_MESSAGE( "vector output test: " << one );
  }

BOOST_AUTO_TEST_SUITE_END()
