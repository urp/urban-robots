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

      namespace
      {
	template< typename FullLayout, typename FullIndexMask >
	struct make_slice_layout
	{
	  typedef typename integral::equal< typename FullLayout::sizes, FullIndexMask >::type visibility_mask;
	  typedef multidim_layout< typename integral::remove_false< typename FullLayout::sizes  , visibility_mask >::type
				 , typename integral::remove_false< typename FullLayout::strides, visibility_mask >::type
				 > type;
	};
      }

      //--------------------------
      //---| multidim slice layout
      //--------------------------
      //-----| hides indices equal to size eg. at(FullIndexMask,i) == at(SizeVector,i)
      //-----| default: all indices visible
      template< typename FullLayout
	      , typename FullIndexMask  = typename FullLayout::sizes
	      >
      class multidim_slice_layout : public make_slice_layout< FullLayout, FullIndexMask >::type
      {
	  static_assert( FullIndexMask::size == FullLayout::sizes::size
		       , "Size of FullIndexMask and SizeVector must agree"
		       );
	  static_assert( not integral::any< typename integral::equal< typename FullLayout::sizes
								    , integral::constant< size_type, 0 >
								    >::type >::value
		       , "Index with empty range (Size=0) are nor allowed"
		       );

	public:

	  // mask

	  typedef typename make_slice_layout< FullLayout, FullIndexMask >::type 	   slice_layout;
	  typedef typename make_slice_layout< FullLayout, FullIndexMask >::visibility_mask visibility_mask;

	  typedef FullIndexMask  full_index_mask;
	  typedef FullLayout full_layout;
	  typedef typename full_layout::sizes   full_sizes;
	  typedef typename full_layout::strides full_strides;


	  //---| total_size
	  //-----query size (number of scalars)
	  //-----note: empty layout is a scalar
	  // TODO: investigate
	  static constexpr size_type total_size = full_layout::total_size;

	  //---| remove_index
	  //-----returns a new multidim_layout with Index fixed (to Value)
	  // TODO: tests
	  template< index_type MaskedIndex >
	  struct remove_index
	  {
	      static_assert( MaskedIndex < full_layout::order, "Index greater or equal than multidim order");

	      //:::| find index in full_layout corresponding to MaskedIndex

	      typedef typename integral::make_uniform_vector< index_type, full_layout::order, 1 >::type ones;
	      typedef typename integral::accumulate< ones, integral::add< index_type, index_type >, 0 >::type index_positions;
	      typedef typename integral::remove_false< index_positions, visibility_mask >::type visible_index_positions;

	      static constexpr index_type full_layout_index = integral::at< visible_index_positions, MaskedIndex >::value;

	    public:

	      //:::| assamble result

	      typedef typename full_layout::template remove_index< full_layout_index >::type new_full_layout;
	      typedef typename integral::remove_at< full_index_mask, full_layout_index >::type new_index_mask;

	      typedef multidim_slice_layout< new_full_layout, new_index_mask > type;
	  };


	  //---| fix_index
	  //-----returns a new multidim_layout with Index fixed (to Value)
	  template< index_type FullIndex, index_type Value >
	  class fix_index
	  {
	      static_assert( FullIndex < full_layout::order, "Index greater or equal than multidim order" );
	      typedef typename integral::assign< full_index_mask, FullIndex, integral::constant< index_type, Value > >::type new_index_mask;
	    public:
	      typedef multidim_slice_layout< full_layout, new_index_mask > type;
	  };

	  //---| release_index
	  //-----returns a new multidim_layout with Index released.
	  // TODO: tests
	  template< index_type Index >
	  class release_index
	  {
	     static_assert( Index < full_layout::order, "Index greater or equal than multidim order");
	      static const index_type index_size = integral::at< typename full_layout::sizes, Index >::value;
	    public:
	      typedef typename fix_index< Index, index_size >::type type;
	  };

	  //:::| memory model

	  //---| fixed_dimension_offset

	  static constexpr stride_type static_offset()
	  {
	    typedef typename integral::transform< visibility_mask , integral::negate<bool> >::type hidden_mask;
	    // remove free indices from the dope vectors
	    typedef typename integral::remove_false< full_strides, hidden_mask >::type hidden_strides;
	    typedef typename integral::remove_false< full_index_mask, hidden_mask >::type hidden_indices;

	    return integral::inner_product< hidden_strides, hidden_indices >::value + full_layout::static_offset();
	  }

      };

    }
  }
}
