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

# include "utk/meta/vector.hpp"

# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE meta vector
# include <boost/test/unit_test.hpp>

using namespace utk::meta;

BOOST_AUTO_TEST_CASE( size )
{
  typedef vector< int, double > vec;
  unsigned size = vec::size;
  BOOST_CHECK_EQUAL( size, 2 );
}

BOOST_AUTO_TEST_CASE( mpl_vector )
{
  typedef vector< int,double,char > indices;

  //---| mpl::size

  typedef indices::mpl_vector mplvec;

  const int indices_size = boost::mpl::size< mplvec >::type::value;
  BOOST_CHECK_EQUAL( indices_size, 3 );

  //---| mpl::at

  typedef typename boost::mpl::at< mplvec, boost::mpl::int_<2> >::type mplvec2;
  static const bool at_index2_same = std::is_same< mplvec2, char >::value;
  BOOST_CHECK( at_index2_same );
}
