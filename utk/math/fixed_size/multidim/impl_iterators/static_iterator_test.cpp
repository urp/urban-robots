/*  static_iterator_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_interface/interface.hpp"

# include "utk/math/fixed_size/multidim/impl_iterators/static_iterator.hpp"

# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE multidim::static_iterator
# include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;
using namespace utk::math::fixed_size::multidim;

BOOST_AUTO_TEST_CASE( check_layout3 )
{
  typedef layout< size_vector<3> > layout3;
  typedef interface< double, vector::unmanaged_tag, layout3 > type;
  double  data[ layout3::total_size ] = { 0.,1.,2. };
  type multidim( data );

  typedef static_iterator< type > it0_type;
  it0_type it0( multidim );
  BOOST_CHECK_EQUAL( *it0, 0. );

  typedef typename it0_type::forward_iterator it1_type;
  it1_type it1 = it0.next();
  BOOST_CHECK_EQUAL( *it1, 1. );

  auto it2 = it1.next();
  BOOST_CHECK_EQUAL( *it2, 2. );
}

struct layout23_fixture
{
  typedef layout< size_vector<2,3> > layout23;
  typedef interface< double, vector::unmanaged_tag, layout23 > type;
  double  data[ layout23::total_size ];
  type multidim23;

  typedef static_iterator< type > it0_type;
  it0_type it0;

  layout23_fixture()
  : data{ 0.,1.,2., 3., 4., 5. }, multidim23(data), it0( multidim23 ) {}
};

BOOST_FIXTURE_TEST_SUITE( check_layout23, layout23_fixture )

  BOOST_AUTO_TEST_CASE( increment_and_access )
  {

    BOOST_CHECK_EQUAL( *it0, 0. );
    auto it1 = it0.next();
    BOOST_CHECK_EQUAL( *it1, 1. );
    auto it2 = it1.next();
    BOOST_CHECK_EQUAL( *it2, 2. );

    auto it3 = it2.next();
    BOOST_CHECK_EQUAL( *it3, 3. );
    auto it4 = it3.next();
    BOOST_CHECK_EQUAL( *it4, 4. );
    auto it5 = it4.next();
    BOOST_CHECK_EQUAL( *it5, 5. );
  }

  BOOST_AUTO_TEST_CASE( compare_iterators )
  {
    typedef static_iterator< type > it0_type;
    it0_type it0( multidim23 );
    BOOST_CHECK_EQUAL( *it0, 0. );
    auto it1 = it0.next();
    BOOST_CHECK_EQUAL( *it1, 1. );
    auto it2 = it1.next();
    BOOST_CHECK_EQUAL( *it2, 2. );

    auto it3 = it2.next();
    BOOST_CHECK_EQUAL( *it3, 3. );
    auto it4 = it3.next();
    BOOST_CHECK_EQUAL( *it4, 4. );
    auto it5 = it4.next();
    BOOST_CHECK_EQUAL( *it5, 5. );

    auto it1_id = it2.previous();
    BOOST_CHECK_EQUAL( it1_id == it1, true );
    BOOST_CHECK_EQUAL( it0 != it1, true );
  }

BOOST_AUTO_TEST_SUITE_END()
