/*  multiply_test.cpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/interface/vector.hpp"

# include "utk/math/fixed_size/layout/generic_layout.hpp"

# include "utk/math/fixed_size/interface/multidim/interface.hpp"

# include "utk/math/fixed_size/interface/multidim/functions/at.hpp"

# include "utk/math/fixed_size/interface/multidim/operators/multiply.hpp"
# include "utk/math/fixed_size/interface/multidim/operators/io.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE utk::math::fixed_size::interface::multidim operator multiply
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::interface;
using namespace utk::math::fixed_size::interface::multidim;

struct fixture
{
  typedef layout::generic_layout< size_vector<2,3> > layout23;
  typedef interface< int, vector::unmanaged_tag, layout23 > type123;
  int data[6];
  type123 multidim123;

  fixture() : data{ 1,2,3,4,5,6 }, multidim123( data ) {}
};

BOOST_FIXTURE_TEST_SUITE( check_multiply, fixture )

  BOOST_AUTO_TEST_CASE( check_multipy_scalar )
  {
    auto result = multidim123 * 2;

    BOOST_CHECK_EQUAL( at( result, 0,0 ),  2 );
    BOOST_CHECK_EQUAL( at( result, 0,1 ),  4 );
    BOOST_CHECK_EQUAL( at( result, 0,2 ),  6 );
    BOOST_CHECK_EQUAL( at( result, 1,0 ),  8 );
    BOOST_CHECK_EQUAL( at( result, 1,1 ), 10 );
    BOOST_CHECK_EQUAL( at( result, 1,2 ), 12 );
  }

  BOOST_AUTO_TEST_CASE( check_multipy_scalar_with_slice_layout )
  {
    typedef typename layout::fix_index< layout23, 1, 2 >::type fixed_layout;
    typedef interface< int, vector::unmanaged_tag, fixed_layout > type12;

    type12 multidim12(data);

    auto result = multidim12 * 2;

    BOOST_CHECK_EQUAL( multidim12.order,  1 );
    BOOST_TEST_MESSAGE( "multidim12 * 2 = " << multidim12 );

    BOOST_CHECK_EQUAL( at( result, 0 ),  6 );
    BOOST_CHECK_EQUAL( at( result, 1 ), 12 );
  }


BOOST_AUTO_TEST_SUITE_END()
