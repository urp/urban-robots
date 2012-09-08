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

# include "utk/math/fixed_size/tensor_structure.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE tensor structure
#include <boost/test/unit_test.hpp>

using namespace utk::math;
using namespace utk::math::fixed_size;

BOOST_AUTO_TEST_SUITE( compile_time_information )

  BOOST_AUTO_TEST_CASE( structure_stride )
  {
    typedef tensor_structure< index_vector<2,3,4>, size_vector<2,3,4> > structure;

    // scalar
    size_type size0 =  tensor_structure< index_vector<2,3,4>, size_vector<2,3,4> >::stride<0>::value;
    BOOST_CHECK_EQUAL( size0, 1 );
    // size of the first two sub dimensions - in elements

    size_type stride1 = structure::stride<1>::value;
    BOOST_CHECK_EQUAL( stride1, 2 );

    // size of the first three sub dimensions
    size_type stride2 = structure::stride<2>::value;
    BOOST_CHECK_EQUAL( stride2, 6 );
    // number of elements in the whole tensor
    size_type total_size = structure::stride<3>::value;
    BOOST_CHECK_EQUAL( total_size, 24 );

    // higher (non existing) dimensions should produce a compile time error
    //size_type total_size2 = tensor::stride<5>();
  }

  BOOST_AUTO_TEST_CASE( size )
  {
    typedef tensor_structure< index_vector<2,3,4>, size_vector<2,3,4> > structure;

    BOOST_CHECK_EQUAL( structure::dimension(), 3 );

    BOOST_CHECK_EQUAL( structure::total_size(), 24 );


    std::array< size_type, 3 > size_array = utk::math::integral::make_array< structure::sizes >::value;
    BOOST_CHECK_EQUAL( size_array[0], 2 );
  }

  BOOST_AUTO_TEST_CASE( fix_dimension )
  {
    typedef tensor_structure< index_vector<2,3,4>, size_vector<2,3,4> > structure;

    // fix
    typedef typename structure::fix_dimension< 0, 1 >::type fixed;

    index_type fixed0 = integral::at< typename fixed::indices, 0 >::value;
    BOOST_CHECK_EQUAL( fixed0 , 1 );

    // remove_fixed
    typedef typename fixed::remove_fixed::type removed;

    index_type removed0 = integral::at< typename removed::indices, 0 >::value;
    BOOST_CHECK_EQUAL( removed0, 3 );
    index_type removed1 = integral::at< typename removed::indices, 1 >::value;
    BOOST_CHECK_EQUAL( removed1, 4 );

    BOOST_CHECK_EQUAL( removed::total_size(), 12 );
    BOOST_CHECK_EQUAL( removed::dimension(), 2 );

    // unfix
    typedef typename structure::unfix_dimension< 0 >::type unfixed;
    BOOST_CHECK_EQUAL( unfixed::total_size(), 24 );
    index_type unfixed0 = integral::at< unfixed::indices, 0 >::value;
    BOOST_CHECK_EQUAL( unfixed0, 2 );

  }

  BOOST_AUTO_TEST_CASE( stride_vector )
  {
    typedef helpers::stride_sequence< size_vector<2,3,4,5> >::type strides;

    static const stride_type s0 = integral::at< strides, 0 >::value;
    BOOST_CHECK_EQUAL( s0, 1 );
    static const stride_type s1 = integral::at< strides, 1 >::value;
    BOOST_CHECK_EQUAL( s1, 2 );
    static const stride_type s2 = integral::at< strides, 2 >::value;
    BOOST_CHECK_EQUAL( s2, 6 );
    static const stride_type s3 = integral::at< strides, 3 >::value;
    BOOST_CHECK_EQUAL( s3, 24 );
    static const stride_type s4 = integral::at< strides, 4 >::value;
    BOOST_CHECK_EQUAL( s4, 120 );

  }

  BOOST_AUTO_TEST_CASE( free_coord_offset )
  {
    typedef tensor_structure< index_vector<2,3,4,5>, size_vector<2,3,4,5> > structure;

    const stride_type offset_111 = structure::free_coord_offset( 1,1,1 );
    BOOST_CHECK_EQUAL( offset_111, 9 );

    // fix
    typedef typename structure::fix_dimension< 1, 0 >::type fixed;

    const stride_type fixed_11 = fixed::free_coord_offset( 1,1 );
    BOOST_CHECK_EQUAL( fixed_11, 7 );
  }

  BOOST_AUTO_TEST_CASE( fixed_coord_offset )
  {
    typedef tensor_structure< index_vector<2,3,4,5>, size_vector<2,3,4,5> > structure;

    const stride_type offset = structure::fixed_dimensions_offset();
    BOOST_CHECK_EQUAL( offset, 0 );

    // fix
    typedef typename structure::fix_dimension< 1, 0 >::type fixed;

    const stride_type fixed1 = fixed::fixed_dimensions_offset();
    BOOST_CHECK_EQUAL( fixed1, 2 );
  }


BOOST_AUTO_TEST_SUITE_END()
