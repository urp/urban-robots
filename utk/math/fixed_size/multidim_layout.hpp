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

      template< typename, typename>
      class multidim_layout
      { /* unspecified*/ };

      template< index_type... IndexInfo, size_type... Sizes >
      class multidim_layout< index_vector< IndexInfo... >, size_vector< Sizes... > >
      {
	  static_assert( sizeof...(IndexInfo) == sizeof...(Sizes)
			 , "the number of indices forwarded in index_vector< ... >"
			   " and the number sizes forwarded in size_vector< ... > must agree" );

	public:

	  typedef index_vector< IndexInfo... >	indices;
	  typedef  size_vector< Sizes ... >	sizes;

	  typedef multidim_layout< indices, sizes > type;

	  typedef typename helpers::stride_sequence< sizes >::type strides;

	  //---| order
	  //-----number of dimensions
	  //order is defined below!
	  static constexpr index_type full_order = sizes::size;


	  //---| stride
	  //-----extract stride
	  template< index_type Index >
	  struct stride
	  {
	    static_assert( Index <= sizeof...(Sizes), "requested dimension does not exist" );
	    const static stride_type value = integral::at< strides, Index >::value;
	  };

	  //---| total_size
	  //-----query size (number of scalars)
	  constexpr static const size_type total_size()
	  { return stride< 0 >::value; }

	  //---| fix_dimension
	  //-----returns a new multidim_layout with Index fixed (to Value)
	  template< index_type Index, index_type Value >
	  class fix_index
	  {
	      static_assert( Index < full_order, "Index greater or equal than tensor order");
	      typedef typename integral::assign< indices, Index, integral::constant< index_type, Value > >::type new_indices;
	    public:
	      typedef multidim_layout< new_indices, sizes > type;
	  };

	  //---| unfix_dimension
	  //-----returns a new multidim_layout with Index released.
	  template< index_type Index >
	  class release_index
	  {
	     static_assert( Index < full_order, "Index greater or equal than tensor order");
	      static const index_type dim_size = integral::at< sizes, Index >::value;
	    public:
	      typedef typename fix_index< Index, dim_size >::type type;
	  };

	  //---| remove_fixed - TODO: rename to 'compact'
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
	  // TODO: free_indices_offset< Coords >
	  // TODO: use free_indices_offset and fixed_dimension_offset in specializations of 'at< Coords >( dyn_coords )'
	  //---| free_indices_offset
  	  //-----return offset for the specified coordinates
	  template< typename...Coords >
	  static const stride_type free_indices_offset( Coords... coords )
	  {
	    static_assert( sizeof...(coords) == remove_fixed::type::order
			   , "number of coordinates must be smaller than number of 'free' indices." );

	    // detect fixed dimensions
	    typedef typename integral::equal< indices, sizes >::type free_dimensions;
	    // remove first element (total_size) from strides
	    typedef typename integral::pop_front< strides >::tail strides_tail;
	    // remove fixed dimensions from the vectors
	    typedef typename integral::remove_false< strides_tail, free_dimensions >::type free_strides;

	    return integral::inner_product_with_arguments< free_strides >( coords... );
	  }

	  //---| fixed_dimension_offset

	  static constexpr stride_type fixed_indices_offset()
	  {
	    typedef typename integral::equal< indices, sizes >::type free_dimensions;
	    typedef typename integral::transform< free_dimensions , integral::negate<bool> >::type fixed_dimensions;

	    typedef typename integral::pop_front< strides >::tail strides_tail;
	    typedef typename integral::remove_false< strides_tail, fixed_dimensions >::type fixed_strides;
	    typedef typename integral::remove_false< indices    , fixed_dimensions >::type fixed_indices;

	    return integral::inner_product< fixed_strides, fixed_indices >::value;
	  }

      };

      template< size_type...Sizes >
      using initial_layout = multidim_layout< index_vector< Sizes... >, size_vector< Sizes... > >;

    }
  }
}
