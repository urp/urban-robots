/*  bla.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_slice_layout/remove_index.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::slice_layout remove_index
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size::multidim;

struct first_fixed
{
  typedef slice_layout< layout< size_vector<1,2,3> >, index_vector<0,2,3> > old_layout;
};

BOOST_FIXTURE_TEST_SUITE( layout_remove_index, first_fixed )

  BOOST_AUTO_TEST_CASE( remove_free_index )
  {
    typedef typename remove_index< old_layout, 1 >::type layout23;

    const size_type order = layout23::order;
    BOOST_CHECK_EQUAL( order, 1 );

    const size_type size0 = meta::integral::at< typename layout23::sizes, 0 >::value;
    BOOST_CHECK_EQUAL( size0, 2 );

    const stride_type stride0 = meta::integral::at< typename layout23::strides, 0 >::value;
    BOOST_CHECK_EQUAL( stride0, 3 );
  }


BOOST_AUTO_TEST_SUITE_END()
