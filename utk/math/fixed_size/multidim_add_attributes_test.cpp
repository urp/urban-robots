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

# include "utk/meta/vector_at.hpp"

# include "utk/math/fixed_size/multidim_layout.hpp"
# include "utk/math/fixed_size/multidim_add_attributes.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim_layout add_attributes
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;

struct multidim_layout_with_new_attributes
{
  typedef multidim_layout< size_vector< 2,3,4 > > old_layout;
  typedef typename add_attributes< old_layout, meta::integral::vector< bool, true, false, true > >::type new_layout;
};

BOOST_FIXTURE_TEST_SUITE( check_multidim_layout_with_new_attributes, multidim_layout_with_new_attributes )

  BOOST_AUTO_TEST_CASE( new_attribute )
  {
    typedef typename meta::at< typename new_layout::attributes, 2 >::type new_attribs;
    const bool new_attrib0 = meta::integral::at< new_attribs, 0 >::value;
    BOOST_CHECK_EQUAL( new_attrib0, true );
    const bool new_attrib1 = meta::integral::at< new_attribs, 1 >::value;
    BOOST_CHECK_EQUAL( new_attrib1, false );
    const bool new_attrib2 = meta::integral::at< new_attribs, 2 >::value;
    BOOST_CHECK_EQUAL( new_attrib2, true );
  }

BOOST_AUTO_TEST_SUITE_END()
