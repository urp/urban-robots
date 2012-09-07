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

# include "utk/math/fixed_size/tensor_interface.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor interface
#include <boost/test/unit_test.hpp>

using namespace utk::math;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_CASE( using_initial_structure )
{
  typedef initial_structure< 1,2,3 > structure;
  typedef tensor_interface< double, structure > tensor;
  tensor test_tensor( nullptr );
}



BOOST_AUTO_TEST_CASE( random_testing )
{
  typedef index_vector<2,3,4> old_indices;
  typedef size_vector<2,3,4>	old_sizes;

  typedef tensor_structure< old_indices , old_sizes > old_structure;
  typedef tensor_interface< double, old_structure > old_tensor;
  old_tensor old_test_tensor(0);

  const int old_indices_size = boost::mpl::size< old_indices::mpl_vector_c >::type::value;
  BOOST_CHECK_EQUAL( old_indices_size, 3 );


  typedef integral::assign< old_indices, 0, integral::constant< index_type, 7 > >::type new_indices;
  typedef integral::assign< old_sizes  , 0, integral::constant< index_type, 9 > >::type new_sizes;

  typedef tensor_structure< new_indices , new_sizes > new_structure;
  typedef tensor_interface< double, new_structure > new_tensor;
  new_tensor new_test_tensor( nullptr );

  const int new_index = boost::mpl::at_c< new_indices::mpl_vector_c, 0 >::type::value;
  BOOST_CHECK_EQUAL( new_index, 7 );

  const int new_size = integral::at< new_sizes, 0 >::value;
  BOOST_CHECK_EQUAL( new_size, 9 );


  const int new_indices_size = boost::mpl::size< new_indices::mpl_vector_c >::type::value;
  BOOST_CHECK_EQUAL( new_indices_size, 3 );

}
