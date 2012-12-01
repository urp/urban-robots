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

# include "utk/meta/integral/integral.hpp"
# include "utk/meta/vector_transform.hpp"

# include "utk/math/fixed_size/multidim/impl_interface/change_layout.hpp"
# include "utk/math/fixed_size/multidim/impl_slice_layout/slice_layout.hpp"

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

	  typedef enum { forward,backward } direction_type;

	  namespace // <anonymous>
	  {
	    //---| indices_from_index

	    template< typename StrideVector, index_type Index >
	    struct indices_from_index { /* unspecified */ };

	    template< /*stride_type LargestStride, stride_type...StrideVector, index_type Index*/ >
	    struct indices_from_index< meta::integral::vector< stride_type >, 0 >
	    {
	      typedef index_vector< > type;
	    };

	    // TODO: might be layout dependent
	    template< stride_type LargestStride, stride_type...StrideTail, index_type Index >
	    class indices_from_index< meta::integral::vector< stride_type, LargestStride, StrideTail... >, Index >
	    {
		typedef meta::integral::vector< stride_type, StrideTail... > stride_tail;
		/*static_assert( LargestStride > ( meta::integral::pop_front< stride_tail >::value )
			     , "Strides must be sorted - this is a limitation of the implementation"
			     );*/

		constexpr static index_type index_digit = Index / LargestStride;

		typedef typename indices_from_index< stride_tail
						   , Index - index_digit * LargestStride // TODO: might be layout dependent
						   >::type tail;

	      public:

		typedef typename meta::integral::push_front< tail, meta::integral::constant< index_type, index_digit > >::type type;

	    };

	    //---| advance_digits

	    // TODO: use index (+/- difference) -> indices

	    template < typename IndexVector, typename SizeVector, index_type Difference, direction_type Direction = (Difference >= 0 ? forward : backward) >
	    struct advance_digits_lsb { /* unspecified */ };

	    template < index_type Difference, direction_type Direction >
	    struct advance_digits_lsb< meta::integral::vector< index_type >
				     , meta::integral::vector<  size_type >
				     , Difference
				     , Direction
				     >
	    { typedef index_vector< > type; };

	    //:::| forward |:::::::::::::::::::::::::::::::::::::::::::::/

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

	    //:::| backward |::::::::::::::::::::::::::::::::::::::::::::/

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

 	  template < typename IndexVector, typename SizeVector, index_type Difference, direction_type Forward = (Difference >= 0 ? forward : backward) >
	  class advance_digits
	  {
	      typedef typename meta::integral::reverse< IndexVector >::type rev_indices;
	      typedef typename meta::integral::reverse< SizeVector >::type rev_sizes;
	      typedef typename advance_digits_lsb< rev_indices, rev_sizes, Difference, Forward >::type rev_result;
	    public:
	      typedef typename meta::integral::reverse< rev_result >::type type;
	  };

	} // of helpers

	//---| static_iterator
	//---| use slice_layout

	template < typename Interface
		 , typename CurrentIndexVector = typename meta::integral::make_uniform_vector< index_type, Interface::layout::order, 0 >::type
		 >
	class static_iterator
	{

	    //:::| static value interface |::::::::::::::::::::::::::::/

	    typedef slice_layout< typename Interface::layout, CurrentIndexVector  > value_layout;
	    typedef typename change_layout< Interface, value_layout >::type value_interface;
	    typedef typename value_interface::storage_interface value_storage_interface;

	  public:

	    //:::| iteration information |:::::::::::::::::::::::::::::/

	    typedef CurrentIndexVector current_indices;

	    //:::| container and value types |:::::::::::::::::::::::::/

	    typedef value_interface value_type;

	    //:::| iterator types |::::::::::::::::::::::::::::::::::::/

	    //---| random access iterator
	    template< index_type IndexDelta >
	    using random_access_iterator = static_iterator< Interface
							  , // TODO: !!! reverse vector
							    typename helpers::advance_digits< current_indices
											     , typename Interface::layout::sizes
											     , IndexDelta
											     >::type
							  >;

	    //---| forward iterator
	    typedef random_access_iterator<  1 > forward_iterator;

	    //---| reverse iterator
	    typedef random_access_iterator< -1 > reverse_iterator;


	    //:::| storage interface |:::::::::::::::::::::::::::::::::/

	    typename value_interface::storage_interface storage;

	    //:::| constructors |::::::::::::::::::::::::::::::::::::::/

	    //---| constructor with storage_interface
	    static_iterator( const Interface& interface )
	    : storage( interface )  { }

	    //---| copy constuctor
	    template< typename OtherInterface, typename OtherIndexVector >
	    static_iterator( const static_iterator< OtherInterface, OtherIndexVector >& other )
	    : storage( other.storage )  { }

	    //:::| dereference operator |::::::::::::::::::::::::::::::/

	    value_interface operator*()
	    { return value_interface( value_storage_interface( storage.ptr() ) ); }

	    //:::| increment operator |::::::::::::::::::::::::::::::::/

	    forward_iterator next() const
	    { return forward_iterator( *this ); }

	    //:::| decrement operator |::::::::::::::::::::::::::::::::/
	    // TODO: !!! CHECK for underrun ( mark rend() )

	    reverse_iterator previous() const
	    { return reverse_iterator( *this ); }

	    //:::| comparison operators |::::::::::::::::::::::::::::::/

	    template< typename OtherInterface, typename OtherIndexVector >
	    bool operator==( const static_iterator< OtherInterface, OtherIndexVector >& other ) const
	    {
	      assert( storage.ptr() == other.storage.ptr() );
	      return meta::integral::all< typename meta::integral::equal< OtherIndexVector, CurrentIndexVector >::type >::value;
	    }

	    template< typename OtherInterface, typename OtherIndexVector >
	    bool operator!=( const static_iterator< OtherInterface, OtherIndexVector >& other ) const
	    { return not operator==( other ); }

	}; // of static_iterator<>
      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
