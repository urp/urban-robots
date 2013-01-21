/*  vector_assign_test.cpp - Copyright Peter Urban 2009

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

# include "utk/meta/vector_assign.hpp"
# include "utk/meta/vector_at.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE meta::vector assign
#include <boost/test/unit_test.hpp>

using namespace utk::meta;

BOOST_AUTO_TEST_SUITE( data_access )

BOOST_AUTO_TEST_CASE( vector_assign_element )
{
  typedef vector< int, double, char >  types;

  typedef assign< types, 1, float >::type new_types;
  constexpr bool ni1 = std::is_same< float, typename at< new_types, 1 >::type >::value;
  BOOST_CHECK( ni1 );
  //BOOST_TEST_MESSAGE( "assign float at index 1 : " << types() << " -> " << new_types() );

  constexpr size_t result_size = new_types::size;
  BOOST_CHECK_EQUAL( result_size, 3 );
}

BOOST_AUTO_TEST_SUITE_END()
