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

using namespace utk::math::fixed_size;


BOOST_AUTO_TEST_CASE( random_testing )
{
  typedef index_vector<2,3,4> indices;
  typedef size_vector<2,3,4>	sizes;
  typedef tensor_structure< indices , sizes > old_structure;
  typedef tensor_interface< double, old_structure > tensor;
  tensor test_tensor(0);

  typedef helpers::repack< index_type, indices >::type n_ind;
    const int indices_size = boost::mpl::size< n_ind >::type::value;
    BOOST_CHECK_EQUAL( indices_size, 3 );


  typedef helpers::mpl_assign_element< indices, 1, 9 >::type new_indices;
  typedef helpers::mpl_assign_element< sizes, 1, 9 >::type new_sizes;
  BOOST_TEST_MESSAGE( "CLASS NAME: " << typeid(new_sizes).name() );


  typedef tensor_structure< new_indices , new_sizes > structure;
  //tensor_interface< double, structure > t(0);

  typedef helpers::repack< index_type, new_indices >::type n_ind2;
  //typedef typename helpers::repack< new_sizes >::type n_siz;

}

