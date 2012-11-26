/*  io_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_layout/io.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::layout io
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size::multidim;

struct fixture
{
  typedef layout< size_vector< 1,2,3 > > layout123;
};

BOOST_FIXTURE_TEST_SUITE( check_io, fixture )


  BOOST_AUTO_TEST_CASE( check_3d )
  {
    BOOST_TEST_MESSAGE( layout123() );
  }

BOOST_AUTO_TEST_SUITE_END()
