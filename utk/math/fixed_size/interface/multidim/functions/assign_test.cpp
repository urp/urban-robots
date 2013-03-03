/*  assign_test.cpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/interface/multidim/operators/io.hpp"


# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE utk::math::fixed_size::interface assign (multidim)
# include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::interface;
using namespace utk::math::fixed_size::interface::multidim;

struct fixture
{
  typedef layout::generic_layout< size_vector<1,2,3> > layout;
  typedef interface< int, vector::unmanaged_tag, layout > type123;
  int dataA[6];
  type123 multidimA;

  fixture() : dataA{ 1,2,3,4,5,6 }, multidimA( dataA )  {}
};

BOOST_FIXTURE_TEST_SUITE( check_at, fixture )

  BOOST_AUTO_TEST_CASE( check_assign_to_interface )
  {
    int dataB[6] = { 2,3,4,5,6,7 };
    type123 multidimB( dataB );

    multidimB = multidimA;

    BOOST_CHECK_EQUAL( at( multidimB, 0,0,0 ),  1 );
    BOOST_CHECK_EQUAL( at( multidimB, 0,0,1 ),  2 );
    BOOST_CHECK_EQUAL( at( multidimB, 0,0,2 ),  3 );
    BOOST_CHECK_EQUAL( at( multidimB, 0,1,0 ),  4 );
    BOOST_CHECK_EQUAL( at( multidimB, 0,1,1 ),  5 );
    BOOST_CHECK_EQUAL( at( multidimB, 0,1,2 ),  6 );
  }

  BOOST_AUTO_TEST_CASE( check_assign_to_array )
  {
    typedef typename interface_traits< type123 >::managed_interface array_type;
    array_type multidimB( typename array_type::storage_type( 0 ) );

    BOOST_TEST_MESSAGE( "before A " << multidimA );

    BOOST_TEST_MESSAGE( "before B " << multidimB );

    multidimB = multidimA;

    BOOST_TEST_MESSAGE( "after A " << multidimA );

    BOOST_TEST_MESSAGE( "after B " << multidimB );


    BOOST_CHECK_EQUAL( at( multidimB, 0,0,0 ),  1 );
    BOOST_CHECK_EQUAL( at( multidimB, 0,0,1 ),  2 );
    BOOST_CHECK_EQUAL( at( multidimB, 0,0,2 ),  3 );
    BOOST_CHECK_EQUAL( at( multidimB, 0,1,0 ),  4 );
    BOOST_CHECK_EQUAL( at( multidimB, 0,1,1 ),  5 );
    BOOST_CHECK_EQUAL( at( multidimB, 0,1,2 ),  6 );
  }


BOOST_AUTO_TEST_SUITE_END()
