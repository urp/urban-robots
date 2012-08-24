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
#define BOOST_TEST_MODULE tensor structure
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_SUITE( mpl_interface )

  BOOST_AUTO_TEST_CASE( dim_info_to_mpl_vector_c )
  {
    typedef index_vector<2,3,4> indices;
    typedef size_vector<2,3,4>	sizes;
    //typedef tensor_structure< indices, sizes > structure;

    //---| mpl::size

    const int indices_size = boost::mpl::size< indices >::type::value;
    BOOST_CHECK_EQUAL( indices_size, 3 );

    const int sizes_size = boost::mpl::size< sizes >::type::value;
    BOOST_CHECK_EQUAL( sizes_size, 3 );

    //---| mpl::at_c

    static const int at_index2 = boost::mpl::at_c< indices ,2 >::type::value;
    BOOST_CHECK_EQUAL( at_index2, 4 );

    static const int at_size2 = boost::mpl::at_c< sizes ,2 >::type::value;
    BOOST_CHECK_EQUAL( at_size2, 4 );
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( compile_time_information )

  BOOST_AUTO_TEST_CASE( structure_stride )
  {
    typedef tensor_structure< index_vector<2,3,4>, size_vector<2,3,4> > structure;
    typedef tensor_interface< double, structure > tensor;

    // scalar
    size_type size0 =  tensor_structure< index_vector<2,3,4>, size_vector<2,3,4> >::stride<0>();
    BOOST_CHECK_EQUAL( size0, 0 );
    // size of the first two sub dimensions - in elements
    size_type size1 = tensor::stride<1>();
    BOOST_CHECK_EQUAL( size1, 1 );

    // size of the first three sub dimensions
    size_type size2 = tensor::structure::stride<2>();
    BOOST_CHECK_EQUAL( size2, 2 );

    // size of the first three sub dimensions
    size_type size3 = tensor::structure::stride<3>();
    BOOST_CHECK_EQUAL( size3, 6 );

    // number of elements in the whole tensor
    size_type total_size = tensor::stride<4>();
    BOOST_CHECK_EQUAL( total_size, 24 );

    // higher (non existing) dimensions should produce a compile time error
    //size_type total_size2 = tensor::stride<5>();
  }

  BOOST_AUTO_TEST_CASE( structure_size_info )
  {
    typedef tensor_structure< index_vector<2,3,4>, size_vector<2,3,4> > structure;

    BOOST_CHECK_EQUAL( structure::dimension(), 3 );

    BOOST_CHECK_EQUAL( structure::total_size(), 24 );


    auto sizes = structure::size_array();
    BOOST_CHECK_EQUAL( sizes[0], 2 );
  }

BOOST_AUTO_TEST_SUITE_END()


