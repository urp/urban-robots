/*  add_attribute_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/layout/slice_layout/slice_layout.hpp"
# include "utk/math/fixed_size/layout/slice_layout/fix_index.hpp"
# include "utk/math/fixed_size/layout/slice_layout/add_attributes.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE layout::slice_layout add_attributes
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size::layout;

struct slice_with_new_attributes
{
  typedef generic_layout< size_vector< 2,3,4 > > old_layout;
  typedef typename fix_index< old_layout, 1, 2 >::type slice_layout;
  typedef typename add_attributes< slice_layout, meta::integral::vector< bool, true, false > >::type new_layout;
};

BOOST_FIXTURE_TEST_SUITE( check_slice_with_new_attributes, slice_with_new_attributes )

  BOOST_AUTO_TEST_CASE( new_attribute )
  {
    typedef typename meta::at< typename new_layout::attributes, 2 >::type new_attributes;
    const bool new_attrib0 = meta::integral::at< new_attributes, 0 >::value;
    BOOST_CHECK_EQUAL( new_attrib0, true );
    const bool new_attrib1 = meta::integral::at< new_attributes, 1 >::value;
    BOOST_CHECK_EQUAL( new_attrib1, false );
  }

BOOST_AUTO_TEST_SUITE_END()
