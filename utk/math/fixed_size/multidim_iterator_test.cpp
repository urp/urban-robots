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
# include "utk/math/fixed_size/multidim_iterator.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE multidim iterator
#include <boost/test/unit_test.hpp>

using namespace utk::math;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( multidim_iterator_with_storage )
{
  typedef initial_layout< 6 > layout;
  typedef multidim_interface< double, layout > multidim_type;
  double  data[ layout::total_size() ] = { 0.,1.,2.,3.,4.,5. };
  multidim_type multidim( data );

  multidim_iterator< multidim_type, 0 > it( multidim );

  auto it0 = (it++).at();

  BOOST_CHECK_EQUAL(  it0, 0. );
  BOOST_CHECK_EQUAL( it++.at( 0,0,1 ) , 1. );
  BOOST_CHECK_EQUAL( it++.at( 0,0,2 ) , 2. );
  BOOST_CHECK_EQUAL( it++.at( 0,1,0 ) , 3. );
  BOOST_CHECK_EQUAL( it++.at( 0,1,1 ) , 4. );
  BOOST_CHECK_EQUAL( it++.at( 0,1,2 ) , 5. );
}
