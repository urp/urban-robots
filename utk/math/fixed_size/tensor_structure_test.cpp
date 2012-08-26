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

    const int indices_size = boost::mpl::size< indices::mpl_vector >::type::value;
    BOOST_CHECK_EQUAL( indices_size, 3 );

    const int sizes_size = boost::mpl::size< sizes::mpl_vector >::type::value;
    BOOST_CHECK_EQUAL( sizes_size, 3 );

    //---| mpl::at_c

    static const int at_index2 = boost::mpl::at_c< indices::mpl_vector ,2 >::type::value;
    BOOST_CHECK_EQUAL( at_index2, 4 );

    static const int at_size2 = helpers::at< size_type, 2, sizes >::value;
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
    BOOST_CHECK_EQUAL( size0, 1 );
    // size of the first two sub dimensions - in elements

    size_type stride1 = tensor::structure::stride<1>();
    BOOST_CHECK_EQUAL( stride1, 2 );

    // size of the first three sub dimensions
    size_type stride2 = tensor::stride<2>();
    BOOST_CHECK_EQUAL( stride2, 6 );
    // number of elements in the whole tensor
    size_type total_size = tensor::stride<3>();
    BOOST_CHECK_EQUAL( total_size, 24 );

    // higher (non existing) dimensions should produce a compile time error
    //size_type total_size2 = tensor::stride<5>();
  }

  BOOST_AUTO_TEST_CASE( size )
  {
    typedef tensor_structure< index_vector<2,3,4>, size_vector<2,3,4> > structure;

    BOOST_CHECK_EQUAL( structure::dimension(), 3 );

    BOOST_CHECK_EQUAL( structure::total_size(), 24 );


    auto sizes = structure::size_array();
    BOOST_CHECK_EQUAL( sizes[0], 2 );
  }

  BOOST_AUTO_TEST_CASE( fix_dimension )
  {
    typedef tensor_structure< index_vector<2,3,4>, size_vector<2,3,4> > structure;

    // fix
    typedef typename structure::fix_dimension< 0, 1 >::type fixed;

    BOOST_CHECK_EQUAL( fixed::indices::at<0>(), 1 );

    // remove_fixed
    typedef typename fixed::remove_fixed::type removed;
    BOOST_CHECK_EQUAL( removed::indices::at<0>(), 3 );
    BOOST_CHECK_EQUAL( removed::indices::at<1>(), 4 );
    BOOST_CHECK_EQUAL( removed::total_size(), 12 );
    BOOST_CHECK_EQUAL( removed::dimension(), 2 );

    // unfix
    typedef typename structure::unfix_dimension< 0 >::type unfixed;

    BOOST_CHECK_EQUAL( unfixed::indices::at<0>(), 2 );
    BOOST_CHECK_EQUAL( unfixed::total_size(), 24 );
  }

  BOOST_AUTO_TEST_CASE( free_coord_offset )
  {
    typedef tensor_structure< index_vector<2,3,4>, size_vector<2,3,4> > structure;

    const stride_type offset_111 = structure::free_coord_offset< size_vector< 1,2,6 > >( 1,1,1 );
    BOOST_CHECK_EQUAL( offset_111, 9 );

  }


BOOST_AUTO_TEST_SUITE_END()


