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

# include "utk/meta/vector_size.hpp"
# include "utk/meta/vector_at.hpp"
# include "utk/meta/vector_transform.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE meta::vector at
#include <boost/test/unit_test.hpp>

using namespace utk::meta;

BOOST_AUTO_TEST_CASE( size_of_subvectors )
{
  typedef vector< vector< int >
                , vector< double, double >
                , vector< char, char, char >
                >  vec_vec;

  typedef typename transform< vec_vec, function< size > >::type size_vec;

  const size_type size0 = at< size_vec, 0 >::type::value;
  BOOST_CHECK_EQUAL( size0, 1 );
  const size_type size1 = at< size_vec, 1 >::type::value;
  BOOST_CHECK_EQUAL( size1, 2 );
  const size_type size2 = at< size_vec, 2 >::type::value;
  BOOST_CHECK_EQUAL( size2, 3 );
}
