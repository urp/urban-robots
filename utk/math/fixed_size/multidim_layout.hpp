/*  bla.h - Copyright Peter Urban 2012

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

# include <boost/mpl/at.hpp>


# include "utk/math/integral/integral.hpp"

# include "utk/math/fixed_size/multidim_layout_helpers.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      //---------------------
      //---| tensor layout
      //---------------------
      // TODO: make index fixing invisible to outside multidim_layout
      // e.g indices & sizes & strides contains only 'free indices'
      // in the manner of order vs. full_order
      template< typename IndexVector
	      , typename SizeVector
	      , typename StrideVector = typename helpers::stride_sequence< SizeVector >::type
	      >
      class multidim_layout
      {
	  static_assert( IndexVector::size == SizeVector::size
		       , "Size of IndexVector and SizeVector must agree"
		       );
  	  static_assert( StrideVector::size == SizeVector::size
		       , "Size of StrideVector and SizeVector must agree"
		       );
	  static_assert( not integral::any< typename integral::equal< SizeVector, integral::constant< size_type, 0 > >::type >::value
		       , "Index with empty range (Size=0) are nor allowed"
		       );

	public:
	  // TODO: make indices private
	  typedef  IndexVector indices;
	  typedef   SizeVector sizes;
	  typedef StrideVector strides;

	  typedef multidim_layout< indices, sizes, strides > type;

	  //---| order
	  //-----number of dimensions
	  //order is defined below!
	  static constexpr index_type full_order = sizes::size;


	  //---| stride
	  //-----extract stride
	  template< index_type Index >
	  struct stride
	  {
	    static_assert( Index < SizeVector::size, "requested dimension does not exist" );
	    const static stride_type value = integral::at< strides, Index >::value;
	  };

	  //---| total_size
	  //-----query size (number of scalars)
	  //-----note: empty layout is a scalar
	  static constexpr size_type total_size = helpers::total_size< sizes, strides >::value;

	  //---| fix_dimension
	  //-----returns a new multidim_layout with Index fixed (to Value)
	  template< index_type Index, index_type Value >
	  class fix_index
	  {
	      static_assert( Index < full_order, "Index greater or equal than multidim order");
	      typedef typename integral::assign< indices, Index, integral::constant< index_type, Value > >::type new_indices;
	    public:
	      typedef multidim_layout< new_indices, sizes > type;
	  };

	  //---| fix_dimension
	  //-----returns a new multidim_layout with Index fixed (to Value)
	  // TODO: tests
	  template< index_type Index >
	  struct remove_index
	  {
	    static_assert( Index < full_order, "Index greater or equal than multidim order");

	    typedef typename integral::remove_at< indices, Index >::type new_indices;
	    typedef typename integral::remove_at< sizes  , Index >::type new_sizes;
	    typedef typename integral::remove_at< strides, Index >::type new_strides;

	    typedef multidim_layout< new_indices, new_sizes, new_strides > type;
	  };


	  //---| unfix_dimension
	  //-----returns a new multidim_layout with Index released.
	  // TODO: tests
	  template< index_type Index >
	  class release_index
	  {
	     static_assert( Index < full_order, "Index greater or equal than multidim order");
	      static const index_type dim_size = integral::at< sizes, Index >::value;
	    public:
	      typedef typename fix_index< Index, dim_size >::type type;
	  };

	  //---| remove_fixed
	  //-----returns a new multidim_layout with all fixed dimensions removed.
	  class remove_fixed
	  {
	      typedef typename integral::equal< indices, sizes >::type free_dimensions;
	      typedef typename integral::remove_false< indices, free_dimensions >::type sub_indices;
	      typedef typename integral::remove_false< sizes  , free_dimensions >::type sub_sizes;
	    public:
	      typedef multidim_layout< sub_indices, sub_sizes > type;
	  };

	  //---| order
	  //-----number of dimensions
	  static constexpr index_type order = remove_fixed::type::sizes::size;

	  //:::| memory model
	  // TODO: index_offset< Coords >
	  // TODO: use index_offset and fixed_dimension_offset in specializations of 'at< Coords >( dyn_coords )'
	  //---| index_offset
  	  //-----return offset for the specified coordinates
	  template< typename...FreeIndexTypes >
	  static const stride_type index_offset( FreeIndexTypes... free_indices )
	  {
	    static_assert( sizeof...(FreeIndexTypes) <= remove_fixed::type::order
			   , "number of coordinates must be smaller than number of 'free' indices." );

	    // detect fixed indices
	    typedef typename integral::equal< indices, sizes >::type free_indices_mask;
	    // remove fixed indices from the vectors
	    typedef typename integral::remove_false< strides, free_indices_mask >::type free_strides;

	    return integral::inner_product_with_arguments< free_strides >( free_indices... );
	  }

	  //---| fixed_dimension_offset

	  static constexpr stride_type static_offset()
	  {
	    typedef typename integral::equal< indices, sizes >::type free_indices_mask;
	    typedef typename integral::transform< free_indices_mask , integral::negate<bool> >::type fixed_indices_mask;
	    // remove free indices from the vectors
	    typedef typename integral::remove_false< strides, fixed_indices_mask >::type fixed_strides;
	    typedef typename integral::remove_false< indices, fixed_indices_mask >::type fixed_indices;

	    return integral::inner_product< fixed_strides, fixed_indices >::value;
	  }

      };

      //:::| allocate static storage
      template< typename IndexVector
	      , typename SizeVector
	      , typename StrideVector
	      >
      constexpr size_type multidim_layout< IndexVector, SizeVector, StrideVector >::total_size;

      template< size_type...Sizes >
      using initial_layout = multidim_layout< index_vector< Sizes... >, size_vector< Sizes... > >;

    }
  }
}
