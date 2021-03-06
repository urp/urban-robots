/*  plus_test.cpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/interface/multidim/operators/plus.hpp"
# include "utk/math/fixed_size/interface/multidim/operators/io.hpp"

# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE utk::math::fixed_size::interface::multidim::operator plus
# include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::interface;
using namespace utk::math::fixed_size::interface::multidim;

struct fixture
{
  typedef layout::generic_layout< size_vector<2,3> > layout23;
  typedef interface< int, vector::unmanaged_tag, layout23 > type23;
  int data[6];
  type23 multidim23;

  fixture() : data{ 1,2,3,4,5,6 }, multidim23( data ) {}
};

BOOST_FIXTURE_TEST_SUITE( plus_scalar, fixture )

  BOOST_AUTO_TEST_CASE( check_multidim_plus_assign_scalar )
  {
    typename interface_traits< type23 >::managed_interface result( multidim23 );

    result += 1;
    std::cerr << " result " << result << std::endl;

    BOOST_CHECK_EQUAL( at( result, 0,0 ), 2 );
    BOOST_CHECK_EQUAL( at( result, 0,1 ), 3 );
    BOOST_CHECK_EQUAL( at( result, 0,2 ), 4 );
    BOOST_CHECK_EQUAL( at( result, 1,0 ), 5 );
    BOOST_CHECK_EQUAL( at( result, 1,1 ), 6 );
    BOOST_CHECK_EQUAL( at( result, 1,2 ), 7 );
  }

  BOOST_AUTO_TEST_CASE( check_multidim_plus_scalar )
  {
    auto result = multidim23 + 1;

    std::cerr << "result " << result << std::endl;


    BOOST_CHECK_EQUAL( at( result, 0,0 ), 2 );
    BOOST_CHECK_EQUAL( at( result, 0,1 ), 3 );
    BOOST_CHECK_EQUAL( at( result, 0,2 ), 4 );
    BOOST_CHECK_EQUAL( at( result, 1,0 ), 5 );
    BOOST_CHECK_EQUAL( at( result, 1,1 ), 6 );
    BOOST_CHECK_EQUAL( at( result, 1,2 ), 7 );
  }

  BOOST_AUTO_TEST_CASE( check_scalar_plus_multidim )
  {
    auto result = 1 + multidim23;

    std::cerr << "result " << result << std::endl;

    BOOST_CHECK_EQUAL( at( result, 0,0 ), 2 );
    BOOST_CHECK_EQUAL( at( result, 0,1 ), 3 );
    BOOST_CHECK_EQUAL( at( result, 0,2 ), 4 );
    BOOST_CHECK_EQUAL( at( result, 1,0 ), 5 );
    BOOST_CHECK_EQUAL( at( result, 1,1 ), 6 );
    BOOST_CHECK_EQUAL( at( result, 1,2 ), 7 );
  }

BOOST_AUTO_TEST_SUITE_END()



BOOST_FIXTURE_TEST_SUITE( plus_multidim, fixture )

  BOOST_AUTO_TEST_CASE( check_multidim_plus_assign_multidim )
  {
    typename interface_traits< type23 >::managed_interface result( multidim23 );

    result += multidim23;

    std::cerr << "result " << result << std::endl;

    BOOST_CHECK_EQUAL( at( result, 0,0 ), 2 );
    BOOST_CHECK_EQUAL( at( result, 0,1 ), 4 );
    BOOST_CHECK_EQUAL( at( result, 0,2 ), 6 );
    BOOST_CHECK_EQUAL( at( result, 1,0 ), 8 );
    BOOST_CHECK_EQUAL( at( result, 1,1 ), 10 );
    BOOST_CHECK_EQUAL( at( result, 1,2 ), 12 );
  }

  BOOST_AUTO_TEST_CASE( check_multidim_plus_multidim )
  {
    auto result = multidim23 + multidim23;

    std::cerr << "result " << result << std::endl;

    BOOST_CHECK_EQUAL( at( result, 0,0 ), 2 );
    BOOST_CHECK_EQUAL( at( result, 0,1 ), 4 );
    BOOST_CHECK_EQUAL( at( result, 0,2 ), 6 );
    BOOST_CHECK_EQUAL( at( result, 1,0 ), 8 );
    BOOST_CHECK_EQUAL( at( result, 1,1 ), 10 );
    BOOST_CHECK_EQUAL( at( result, 1,2 ), 12 );
  }

BOOST_AUTO_TEST_SUITE_END()
