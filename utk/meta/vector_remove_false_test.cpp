/*  vector_remove_false_test.cpp - Copyright Peter Urban 2009

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

# include "utk/meta/integral/constant.hpp"

# include "utk/meta/vector.hpp"
# include "utk/meta/vector_at.hpp"
# include "utk/meta/vector_remove_false.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE meta::vector remove_false
#include <boost/test/unit_test.hpp>

using namespace utk::meta;

BOOST_AUTO_TEST_CASE( remove_3 )
{
  typedef vector< int, double, char > vec;
  typedef vector< integral::constant< bool, false >, integral::constant< bool, true > , integral::constant< bool, false > > predicates;

  typedef typename remove_false< vec, predicates >::type new_vec;

  const size_type size = new_vec::size;
  BOOST_CHECK_EQUAL( size, 1 );

  const bool same_type = std::is_same< typename at< new_vec, 0 >::type, double >::value;
  BOOST_CHECK( same_type );
}
