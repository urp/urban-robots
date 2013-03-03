/*  named_access_test.cpp - Copyright Peter Urban 2006-2012

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

# include "utk/math/fixed_size/interface/vector/functions/named_access.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE fixed_size::interface::vector named-access
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::interface::vector;

struct d4_fixture
{
  double data_d4[4];
  const interface< double, 4 > d4;

  d4_fixture() : data_d4{ 1., 2., 3., 4. }, d4( data_d4 ) {}
};

BOOST_FIXTURE_TEST_SUITE( check_double_4, d4_fixture )

BOOST_AUTO_TEST_CASE( single_element )
{
  BOOST_CHECK_EQUAL( x(d4), 1. );
  BOOST_CHECK_EQUAL( y(d4), 2. );
  BOOST_CHECK_EQUAL( z(d4), 3. );
  BOOST_CHECK_EQUAL( w(d4), 4. );
}

BOOST_AUTO_TEST_CASE( pair )
{
  const interface<double,2> d2( xy(d4) );
  BOOST_CHECK_EQUAL( x(d2), 1. );
  BOOST_CHECK_EQUAL( y(d2), 2. );
}

BOOST_AUTO_TEST_CASE( triple )
{
  const interface<double,3> d3( xyz(d4) );
  BOOST_CHECK_EQUAL( x(d3), 1. );
  BOOST_CHECK_EQUAL( y(d3), 2. );
  BOOST_CHECK_EQUAL( z(d3), 3. );
}

BOOST_AUTO_TEST_SUITE_END()
