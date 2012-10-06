/*  multidim_interface_test.cpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim_interface.hpp"
# include "utk/math/fixed_size/multidim_static_iterator.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim static iterator
#include <boost/test/unit_test.hpp>

using namespace utk;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( multidim_1d_iterator_with_storage )
{
  typedef multidim_layout< size_vector<3> > layout;
  typedef multidim_interface< double, layout > multidim_type;
  double  data[ layout::total_size ] = { 0.,1.,2. };
  multidim_type multidim( data );

  typedef multidim_static_iterator< multidim_type, 0 > it0_type;
  it0_type it0( multidim );
  BOOST_CHECK_EQUAL(  (*it0).at(), 0. );

  typedef typename it0_type::increment_iterator it1_type;
  it1_type it1 = it0.increment();
  BOOST_CHECK_EQUAL( (*it1).at() , 1. );

  auto it2 = it1.increment();
  BOOST_CHECK_EQUAL( (*it2).at() , 2. );
}

BOOST_AUTO_TEST_CASE( multidim_2d_iterator_with_storage )
{
  typedef multidim_layout< size_vector<2,3> > layout;
  typedef multidim_interface< double, layout > multidim_type;
  double  data[ layout::total_size ] = { 0.,1.,2., 3., 4., 5. };
  multidim_type multidim( data );

  typedef multidim_static_iterator< multidim_type, 1 > it0_type;
  it0_type it0( multidim );
  BOOST_CHECK_EQUAL(  (*it0).at(0), 0. );
  BOOST_CHECK_EQUAL(  (*it0).at(1), 3. );

  auto it1 = it0.increment();
  BOOST_CHECK_EQUAL( (*it1).at(0) , 1. );
  BOOST_CHECK_EQUAL( (*it1).at(1) , 4. );

  auto it2 = it1.increment();
  BOOST_CHECK_EQUAL( (*it2).at(0) , 2. );
  BOOST_CHECK_EQUAL( (*it2).at(1) , 5. );
}

BOOST_AUTO_TEST_CASE( multidim_2d_compare_iterators )
{
  typedef multidim_layout< size_vector<2,3> > layout;
  typedef multidim_interface< double, layout > multidim_type;
  double  data[ layout::total_size ] = { 0.,1.,2., 3., 4., 5. };
  multidim_type multidim( data );

  typedef multidim_static_iterator< multidim_type, 1 > it0_type;
  it0_type it0( multidim );
  BOOST_CHECK_EQUAL(  (*it0).at(0), 0. );
  BOOST_CHECK_EQUAL(  (*it0).at(1), 3. );

  auto it1 = it0.increment();
  BOOST_CHECK_EQUAL( (*it1).at(0) , 1. );
  BOOST_CHECK_EQUAL( (*it1).at(1) , 4. );

  auto it2 = it1.increment();
  BOOST_CHECK_EQUAL( (*it2).at(0) , 2. );
  BOOST_CHECK_EQUAL( (*it2).at(1) , 5. );

  auto it1_id = it2.decrement();
  BOOST_CHECK_EQUAL( it1_id == it1, true );
  BOOST_CHECK_EQUAL( it0 != it1, true );

}
