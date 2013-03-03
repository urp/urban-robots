/*  comparison_test.cpp - Copyright Peter Urban 2009-2013

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

# include "utk/math/fixed_size/interface/vector/operators/comparison.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE utk::math::fixed_size::interface::vector::operator  (comparison)
#include <boost/test/unit_test.hpp>

using namespace utk::math::fixed_size::interface::vector;

struct fixture
{
  double data_one[3];
  const interface<double,3> one;
  double data_two[3];
  const interface<double,3> two;

  double data_gt_one[3] ;
  const interface<double,3> gt_one;

  double data_gt_all[3];
  const interface<double,3> gt_all;

  double data_lt_one[3] ;
  const interface<double,3> lt_one;

  double data_lt_all[3];
  const interface<double,3> lt_all;

  bool data_true_all[3];
  const interface<bool,3>  true_all;

  bool data_false_all[3] ;
  const interface<bool,3> false_all;

  bool data_true_one[3];
  const interface<bool,3>  true_one;

  bool data_false_one[3];
  const interface<bool,3> false_one;

  fixture()
  : data_one   { 1. , 2. , 3.  }, one(data_one)
  , data_two   { 1. , 2. , 3.  }, two(data_two)
  , data_gt_one{ 1. , 2.2, 3.  }, gt_one( data_gt_one )
  , data_gt_all{ 1.1, 2.2, 3.3 }, gt_all( data_gt_all )
  , data_lt_one{ 1. , 0.2, 3.  }, lt_one( data_lt_one )
  , data_lt_all{ 0.1, 0.2, 0.3 }, lt_all( data_lt_all )
  , data_true_all {  true,  true,  true }, true_all( data_true_all )
  , data_false_all{ false, false, false }, false_all( data_false_all )
  , data_true_one { false,  true, false }, true_one( data_true_one )
  , data_false_one{  true, false,  true }, false_one( data_false_one )
  { }
};

BOOST_FIXTURE_TEST_SUITE( check_comparison_operators, fixture )

BOOST_AUTO_TEST_CASE( check_vector_scalar_equality_operator )
{
  BOOST_CHECK_EQUAL(  true_all ==  true, true );
  BOOST_CHECK_EQUAL(  true_all == false, false );
  BOOST_CHECK_EQUAL( false_all ==  true, false );
  BOOST_CHECK_EQUAL( false_all == false,  true );
  BOOST_CHECK_EQUAL(  true_one ==  true, false );
  BOOST_CHECK_EQUAL(  true_one == false, false );
  BOOST_CHECK_EQUAL( false_one == false, false );
  BOOST_CHECK_EQUAL( false_one ==  true, false );
}

BOOST_AUTO_TEST_CASE( check_vector_vector_comparison_operators )
{
  //equal
  BOOST_CHECK_EQUAL( one == two, true );
  BOOST_CHECK_EQUAL( one != two, false );

  BOOST_CHECK_EQUAL( one == two,  true_all );
  BOOST_CHECK_EQUAL( one != two, false_all );
  BOOST_CHECK_EQUAL( one >= two,  true_all );
  BOOST_CHECK_EQUAL( one <= two,  true_all );
  BOOST_CHECK_EQUAL( one >  two, false_all );
  BOOST_CHECK_EQUAL( one <  two, false_all );

  //compare with - one less
  BOOST_CHECK_EQUAL( one == lt_one, false_one );
  BOOST_CHECK_EQUAL( one != lt_one,  true_one );
  BOOST_CHECK_EQUAL( one >= lt_one,  true_all );
  BOOST_CHECK_EQUAL( one <= lt_one, false_one );
  BOOST_CHECK_EQUAL( one >  lt_one,  true_one );
  BOOST_CHECK_EQUAL( one <  lt_one, false_all );

  //compare with - one greater
  BOOST_CHECK_EQUAL( one == gt_one, false_one );
  BOOST_CHECK_EQUAL( one != gt_one,  true_one );
  BOOST_CHECK_EQUAL( one >= gt_one, false_one );
  BOOST_CHECK_EQUAL( one <= gt_one,  true_all );
  BOOST_CHECK_EQUAL( one >  gt_one, false_all );
  BOOST_CHECK_EQUAL( one <  gt_one,  true_one );

  //compare with - all less
  BOOST_CHECK_EQUAL( one == lt_all, false_all );
  BOOST_CHECK_EQUAL( one != lt_all,  true_all );
  BOOST_CHECK_EQUAL( one >= lt_all,  true_all );
  BOOST_CHECK_EQUAL( one <= lt_all, false_all );
  BOOST_CHECK_EQUAL( one >  lt_all,  true_all );
  BOOST_CHECK_EQUAL( one <  lt_all, false_all );

  //compare with - all greater
  BOOST_CHECK_EQUAL( one == gt_all, false_all );
  BOOST_CHECK_EQUAL( one != gt_all,  true_all );
  BOOST_CHECK_EQUAL( one >= gt_all, false_all );
  BOOST_CHECK_EQUAL( one <= gt_all,  true_all );
  BOOST_CHECK_EQUAL( one >  gt_all, false_all );
  BOOST_CHECK_EQUAL( one <  gt_all,  true_all );
}

BOOST_AUTO_TEST_SUITE_END()
