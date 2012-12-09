/*  static_permutation_iterator.hpp - Copyright Peter Urban 2012

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



# pragma once

#include <type_traits>

# include "utk/math/fixed_size/multidim/impl_layout/helpers.hpp" // for some vector and primitive typedefs

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {
	namespace helpers
	{

	  //---| advance_digits |--------------------------------------/
	  //-----advance coordinates by lowest index
	  // TODO: only implemented for IndexDelta +/-1 and 0

	  namespace // <anonymous>
	  {
	    typedef enum { forward,backward } direction_type;

	    // TODO: use index (+/- difference) -> indices
	    template < typename IndexVector, typename SizeVector, index_type Difference, direction_type Direction = (Difference >= 0 ? forward : backward) >
	    struct advance_digits_lsb { /* unspecified */ };

	    // terminate
	    template < index_type Difference, direction_type Direction >
	    struct advance_digits_lsb< index_vector< >, size_vector< >, Difference, Direction >
	    { typedef index_vector< > type; };

	    //:::| forward |:::::::::::::::::::::::::::::::::::::::::::/

	    // carry forward
	    template < index_type...Indices, size_type FirstSize, size_type...Sizes >
	    struct advance_digits_lsb< meta::integral::vector< index_type, FirstSize-1, Indices... >
				     , meta::integral::vector<  size_type, FirstSize  , Sizes... >
				     , 1
				     >
	    {
	      typedef typename advance_digits_lsb< index_vector< Indices... >, size_vector< Sizes... >, 1, forward >::type tail;
	      typedef typename meta::integral::push_front< tail, meta::integral::constant< index_type, 0 > >::type type;
	    };

	    // increment
	    template < index_type FirstIndex, index_type...Indices, size_type FirstSize, size_type...Sizes >
	    struct advance_digits_lsb< meta::integral::vector< index_type, FirstIndex, Indices... >
				     , meta::integral::vector<  size_type, FirstSize ,   Sizes... >
				     , 1, forward
				     >
	    {
	      typedef index_vector< FirstIndex+1, Indices... > type;
	    };

	    //:::| backward |::::::::::::::::::::::::::::::::::::::::::/

	    // carry backward
	    template < index_type...Indices, size_type FirstSize, size_type...Sizes >
	    struct advance_digits_lsb< meta::integral::vector< index_type, 0, Indices... >
				     , meta::integral::vector<  size_type, FirstSize  , Sizes... >
				     , -1, backward
				     >
	    {
	      typedef typename advance_digits_lsb< index_vector< Indices... >, size_vector< Sizes... >, -1, backward >::type tail;
	      typedef typename meta::integral::push_front< tail, meta::integral::constant< index_type, FirstSize-1 > >::type type;
	    };

	    // backward
	    template < index_type FirstIndex, index_type...Indices, size_type FirstSize, size_type...Sizes >
	    struct advance_digits_lsb< meta::integral::vector< index_type, FirstIndex, Indices... >
				     , meta::integral::vector<  size_type, FirstSize ,   Sizes... >
				     , -1, backward
				     >
	    {
	      typedef index_vector< FirstIndex-1, Indices... > type;
	    };

	  } // of <anonymous>::

 	  template < typename IndexVector, typename SizeVector, index_type Difference >
	  class advance_digits
	  {
	      typedef typename meta::integral::reverse< IndexVector >::type rev_indices;
	      typedef typename meta::integral::reverse< SizeVector >::type rev_sizes;
	      typedef typename advance_digits_lsb< rev_indices, rev_sizes, Difference >::type rev_result;
	    public:
	      typedef typename meta::integral::reverse< rev_result >::type type;
	  };

	  //:::| mark end iterator

	  template< typename SizeVector >
	  struct end_iterator_indices
	  {
	      typedef typename meta::integral::make_vector< index_type, SizeVector >::type type;
	  };

	  template < typename SizeVector, index_type Difference >
	  struct advance_digits< typename meta::integral::make_vector< index_type
								     //, typename meta::integral::minus< SizeVector, 1 >::type
								     , typename meta::integral::transform< SizeVector, meta::integral::minus< index_type, 1 > >::type
								     >::type
			       , SizeVector
			       , Difference
			       >

	  {
	      typedef typename end_iterator_indices< SizeVector >::type type;
	  };

	  //---| index_to_indices |----------------------------------/
	  //-----retrieve multidim indices from 'linear' index

	  template< typename StrideVector, index_type Index >
	  struct index_to_indices { /* unspecified */ };
	  // teminate
	  template<>
	  struct index_to_indices< meta::integral::vector< stride_type >, 0 >
	  {
	    typedef index_vector< > type;
	  };
	  // recurse - (index) digit by digit
	  // TODO: is layout dependent
	  template< stride_type LargestStride, stride_type...StrideTail, index_type Index >
	  class index_to_indices< meta::integral::vector< stride_type, LargestStride, StrideTail... >, Index >
	  {
	      typedef meta::integral::vector< stride_type, StrideTail... > stride_tail;

	      constexpr static index_type index_digit = Index / LargestStride;

	      typedef typename index_to_indices< stride_tail
					       , Index - index_digit * LargestStride // TODO: is layout dependent
					       >::type tail;

	    public:

	      typedef typename meta::integral::push_front< tail, meta::integral::constant< index_type, index_digit > >::type type;

	  };

	} // of helpers::
      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
