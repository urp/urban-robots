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

# include "utk/meta/integral/integral.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      namespace
      {
	//---| make_position_index_vector

	template< typename T, size_type Size >
	class make_position_index_vector
	{
	    typedef typename meta::integral::make_uniform_vector< T, Size-1, 1 >::type ones;

	  public:

	    typedef typename meta::integral::accumulate< ones, meta::integral::add< index_type, index_type >, 0 >::type type;
	};

	//---| remove_indices

	template< typename, typename > struct remove_indices { /* unspecified */ };

	// terminate
	template< typename FullLayout >
	struct remove_indices< FullLayout, meta::integral::vector< index_type > >
	{
	  typedef FullLayout type;
	};

	// start -> recurse
	template< typename FullLayout, index_type...Indices >
	class remove_indices< FullLayout, meta::integral::vector< index_type, Indices... > >
	{
	    typedef typename meta::integral::pop_front< meta::integral::vector< index_type, Indices... > > indices_pop;
	    typedef typename remove_indices< FullLayout, typename indices_pop::tail >::type tail;
	  public:
	    typedef typename FullLayout::template remove_index< indices_pop::value >::type type;
	};

	//---| make_slice_layout

	template< typename FullLayout, typename FullIndexMask >
	class make_slice_layout
	{
	    typedef typename make_position_index_vector< index_type, FullLayout::order >::type index_positions;
	  public:

	    typedef typename meta::integral::equal< typename FullLayout::sizes, FullIndexMask >::type visibility_mask;
	    typedef typename meta::integral::transform< visibility_mask , meta::integral::negate<bool> >::type hidden_mask;

	    typedef typename meta::integral::remove_false< index_positions, hidden_mask >::type hidden_indices;

	    typedef typename remove_indices< FullLayout, hidden_indices >::type type;
	};
      }

      //--------------------------
      //---| multidim slice layout
      //--------------------------
      //-----| hides indices equal to size eg. at(FullIndexMask,i) == at(SizeVector,i)
      //-----| default: all indices visible
      template< typename FullLayout
	      , typename FullIndexMask = typename meta::integral::make_vector< index_type, typename FullLayout::sizes >::type
	      >
      class multidim_slice_layout : public make_slice_layout< FullLayout, FullIndexMask >::type
      {
	  static_assert( FullIndexMask::size == FullLayout::order
		       , "Size of FullIndexMask and SizeVector must agree"
		       );
	  static_assert( not meta::integral::any< typename meta::integral::equal< typename FullLayout::sizes
								    , meta::integral::constant< size_type, 0 >
								    >::type >::value
		       , "Index with empty range (Size=0) are nor allowed"
		       );

	public:

	  // mask

	  typedef typename make_slice_layout< FullLayout, FullIndexMask >::type 	   slice_layout;
	  typedef typename make_slice_layout< FullLayout, FullIndexMask >::visibility_mask visibility_mask;

	  typedef FullIndexMask  full_index_mask;
	  typedef FullLayout full_layout;

	  //---| total_size
	  //-----query size (number of scalars)
	  //-----note: empty layout is a scalar
	  // TODO: investigate
	  static constexpr size_type total_size = full_layout::total_size;

	  //---| remove_index
	  //-----returns a new multidim_slice_layout with Index fixed (to Value)
	  // TODO: tests
	  template< index_type MaskedIndex >
	  struct remove_index
	  {
	      static_assert( MaskedIndex < slice_layout::order, "Index greater or equal than multidim order");

	      // find index in full_layout corresponding to MaskedIndex
	      typedef typename make_position_index_vector< index_type, full_layout::order >::type index_positions;
	      typedef typename meta::integral::remove_false< index_positions, visibility_mask >::type visible_index_positions;

	      static constexpr index_type full_layout_index = meta::integral::at< visible_index_positions, MaskedIndex >::value;

	    public:

	      //:::| assamble result

	      typedef typename full_layout::template remove_index< full_layout_index >::type new_full_layout;
	      typedef typename meta::integral::remove_at< full_index_mask, full_layout_index >::type new_index_mask;

	      typedef multidim_slice_layout< new_full_layout, new_index_mask > type;
	  };


	  //---| fix_index
	  //-----returns a new multidim_slice_layout with Index (referring to FullLayout) fixed (to Value)
	  template< index_type FullIndex, index_type Value >
	  class fix_index
	  {
	      static_assert( FullIndex < full_layout::order, "Index greater or equal than multidim order" );
	      typedef typename meta::integral::assign< full_index_mask, FullIndex, meta::integral::constant< index_type, Value > >::type new_index_mask;
	    public:
	      typedef multidim_slice_layout< full_layout, new_index_mask > type;
	  };

	  //---| release_index
	  //-----returns a new multidim_slice_layout with Index released.
	  // TODO: tests
	  template< index_type Index >
	  class release_index
	  {
	     static_assert( Index < full_layout::order, "Index greater or equal than multidim order");
	      static const index_type index_size = meta::integral::at< typename full_layout::sizes, Index >::value;
	    public:
	      typedef typename fix_index< Index, index_size >::type type;
	  };

	  //:::| memory model

	  //---| fixed_dimension_offset

	  static constexpr stride_type static_offset()
	  {
	    typedef typename meta::integral::transform< visibility_mask , meta::integral::negate<bool> >::type hidden_mask;
	    // remove free indices from the dope vectors
	    typedef typename meta::integral::remove_false< typename full_layout::strides, hidden_mask >::type hidden_strides;
	    typedef typename meta::integral::remove_false< FullIndexMask, hidden_mask >::type hidden_indices;

	    return meta::integral::inner_product< hidden_strides, hidden_indices >::value + full_layout::static_offset();
	  }

      };

    }
  }
}
