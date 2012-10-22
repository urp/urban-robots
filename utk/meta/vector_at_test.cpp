/*  vector_at_test.cpp - Copyright Peter Urban 2009

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

# include "utk/meta/vector_at.hpp"

# include "utk/meta/vector_push_back.hpp"


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE meta::vector at
#include <boost/test/unit_test.hpp>

using namespace utk::meta;

BOOST_AUTO_TEST_CASE( element_access )
{
  typedef vector< int, double, char >  vec;

  const bool same_type0 = std::is_same< typename at< vec, 0 >::type, int >::value;
  BOOST_CHECK( same_type0 );
  const bool same_type1 = std::is_same< typename at< vec, 1 >::type, double >::value;
  BOOST_CHECK( same_type1 );
  const bool same_type2 = std::is_same< typename at< vec, 2 >::type, char >::value;
  BOOST_CHECK( same_type2 );
}
