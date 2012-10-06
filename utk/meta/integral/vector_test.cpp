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

#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>

# include "utk/meta/integral/vector.hpp"

# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE meta/integral vector
# include <boost/test/unit_test.hpp>

using namespace utk::meta::integral;

BOOST_AUTO_TEST_CASE( type )
{
  typedef vector< int, 0,1,2 > ints;
  bool match = std::is_same< ints::value_type, int >::value;
  BOOST_CHECK( match );
}

BOOST_AUTO_TEST_CASE( size )
{
  typedef vector< int, 2,3,4> indices;
  unsigned size = indices::size;
  BOOST_CHECK_EQUAL( size, 3 );
}

BOOST_AUTO_TEST_CASE( mpl_vector_c )
{
  typedef vector< int, 2,3,4> indices;

  //---| mpl::size

  const int indices_size = boost::mpl::size< indices::mpl_vector_c >::type::value;
  BOOST_CHECK_EQUAL( indices_size, 3 );

  //---| mpl::at_c

  static const int at_index2 = boost::mpl::at_c< indices::mpl_vector_c ,2 >::type::value;
  BOOST_CHECK_EQUAL( at_index2, 4 );
}
