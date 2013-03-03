/*  dynamic_index_iterator_test.cpp - Copyright Peter Urban 2012

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
//# include "utk/math/fixed_size/interface/vector/operators.hpp"

# include "utk/math/fixed_size/layout/generic_layout.hpp"

# include "utk/math/fixed_size/interface/multidim/interface.hpp"

# include "utk/math/fixed_size/interface/multidim/functions/at.hpp"


# include "utk/math/fixed_size/iterator/stl/index_iterator.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim::dynamic_index_iterator
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::interface;
using namespace utk::math::fixed_size::interface::multidim;

BOOST_AUTO_TEST_CASE( layout_1d )
{
  typedef layout::generic_layout< size_vector<3> > layout3;
  typedef interface< double, vector::unmanaged_tag, layout3 > type;
  double  data[ layout3::total_size ] = { 0.,1.,2. };
  type multidim3( data );

  typedef iterator::stl::index_iterator< type, 0 > it0_type;

  BOOST_CHECK_EQUAL( it0_type::value_type::order, 0. );

  it0_type it0( multidim3 );

  BOOST_MESSAGE( "it0.storage = " << it0.storage );

  BOOST_CHECK_EQUAL( *it0, 0. );
  BOOST_CHECK_EQUAL( at(*it0), 0. );

  BOOST_CHECK_EQUAL( (*it0++), 0. );
  BOOST_CHECK_EQUAL( (*it0++), 1. );
  BOOST_CHECK_EQUAL( (*it0)  , 2. );

}

struct layout23_fixture
{
  typedef layout::generic_layout< size_vector<2,3> > layout23;
  typedef interface< double, vector::unmanaged_tag, layout23 > type;
  double  data[ layout23::total_size ];
  type multidim23;

  typedef iterator::stl::index_iterator< type, 1 > it1_type;
  it1_type it1;

  layout23_fixture()
  : data{ 0.,1.,2., 3., 4., 5. }, multidim23(data), it1( multidim23 ) {}
};

BOOST_FIXTURE_TEST_SUITE( check_iterator23, layout23_fixture )

  BOOST_AUTO_TEST_CASE( iterate_and_access )
  {

    BOOST_CHECK_EQUAL( it1_type::value_type::order, 1. );

    BOOST_MESSAGE( "it0.storage = " << it1.storage );

    BOOST_CHECK_EQUAL( at( *it1, 0 ), 0. );
    BOOST_CHECK_EQUAL( at( *it1, 1 ), 3. );

    BOOST_CHECK_EQUAL( at( *(++it1), 0 ), 1. );
    BOOST_CHECK_EQUAL( at( *it1++  , 1 ), 4. );

    BOOST_CHECK_EQUAL( at(*it1, 0 ) , 2. );
    BOOST_CHECK_EQUAL( at(*it1, 1 ) , 5. );
  }

  BOOST_AUTO_TEST_CASE( compare_iterators )
  {
    BOOST_CHECK_EQUAL( at( *it1, 0 ), 0. );
    BOOST_CHECK_EQUAL( at( *it1, 1 ), 3. );

    BOOST_CHECK_EQUAL( at( *++it1, 0 ) , 1. );
    BOOST_CHECK_EQUAL( at(   *it1, 1   ) , 4. );

    auto it1_1 = it1;

    BOOST_CHECK_EQUAL( at( *++it1, 0 ) , 2. );
    BOOST_CHECK_EQUAL( at(   *it1, 1) , 5. );

    BOOST_CHECK_EQUAL( (--it1).index_value, it1_1.index_value );
    BOOST_CHECK_EQUAL( it1.storage.ptr(), it1_1.storage.ptr() );

    BOOST_CHECK_EQUAL( it1 == it1_1, true );
    BOOST_CHECK_EQUAL( it1 != it1_1, false );

    BOOST_CHECK_EQUAL( --it1 == it1_1, false );
    BOOST_CHECK_EQUAL( it1 != it1_1, true );
  }

BOOST_AUTO_TEST_SUITE_END()
