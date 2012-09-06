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

BOOST_AUTO_TEST_SUITE( variadic_vectors )

  BOOST_AUTO_TEST_CASE( mpl_vector_c )
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

    static const int at_size2 = helpers::at< 2, sizes >::value;
    BOOST_CHECK_EQUAL( at_size2, 4 );
  }

  BOOST_AUTO_TEST_CASE( bool_vector_at )
  {
    typedef bool_vector< false,true,false >  bools;

    static const bool b0 = bools::at<0>();
    BOOST_CHECK( !b0 );
    static const bool b1 = bools::at<1>();
    BOOST_CHECK(  b1 );
    static const bool b2 = bools::at<2>();
    BOOST_CHECK( !b2 );
  }


  BOOST_AUTO_TEST_CASE( equal )
  {
    typedef size_vector< 1,2,3 >  A;
    typedef size_vector< 3,2,1 >  B;
    typedef typename helpers::equal< A, B >::type equal_result;

    static const bool eq0 = equal_result::at<0>();
    BOOST_CHECK( !eq0 );
    static const bool eq1 = equal_result::at<1>();
    BOOST_CHECK(  eq1 );
    static const bool eq2 = equal_result::at<2>();
    BOOST_CHECK( !eq2 );

    typedef size_vector< 1,1,3 >  A2;
    typedef size_vector< 1,2,3 >  B2;
    typedef typename helpers::equal< A2, B2 >::type equal_result2;

    static const bool eq20 = equal_result2::at<0>();
    BOOST_CHECK(  eq20 );
    static const bool eq21 = equal_result2::at<1>();
    BOOST_CHECK( !eq21 );
    static const bool eq22 = equal_result2::at<2>();
    BOOST_CHECK(  eq22 );
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

  BOOST_AUTO_TEST_CASE( stride_vector )
  {
    typedef helpers::stride_sequence< size_vector<2,3,4,5> >::type strides;
    static const stride_type s0 = helpers::at< 0, strides >::value;
    BOOST_CHECK_EQUAL( s0, 1 );
    static const stride_type s1 = helpers::at< 1, strides >::value;
    BOOST_CHECK_EQUAL( s1, 2 );
    static const stride_type s2 = helpers::at< 2, strides >::value;
    BOOST_CHECK_EQUAL( s2, 6 );
    static const stride_type s3 = helpers::at< 3, strides >::value;
    BOOST_CHECK_EQUAL( s3, 24 );
    static const stride_type s4 = helpers::at< 4, strides >::value;
    BOOST_CHECK_EQUAL( s4, 120 );

  }

  BOOST_AUTO_TEST_CASE( free_coord_offset )
  {
    typedef tensor_structure< index_vector<2,3,4,5>, size_vector<2,3,4,5> > structure;
    //typedef helpers::stride_sequence< structure::sizes >::type strides;

    const stride_type offset_111 = structure::free_coord_offset( 1,1,1 );
    BOOST_CHECK_EQUAL( offset_111, 6 );

    // fix
    typedef typename structure::fix_dimension< 0, 1 >::type fixed;

    const stride_type fixed_111 = fixed::free_coord_offset( 1,1 );
    BOOST_CHECK_EQUAL( fixed_111, 6 );

  }


BOOST_AUTO_TEST_SUITE_END()


