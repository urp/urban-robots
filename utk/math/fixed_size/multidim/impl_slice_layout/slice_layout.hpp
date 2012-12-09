/*  slice_layout.hpp - Copyright Peter Urban 2012

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

# include "utk/meta/integral/integral.hpp"
# include "utk/math/fixed_size/multidim/impl_layout/remove_index.hpp"
# include "utk/math/fixed_size/multidim/impl_layout/add_attributes.hpp"


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
	  //---| unmask_indices
	  //-----return a list of 'visible' indices

	  template< typename VisibilityMask >
	  class unmask_indices
	  {
	      typedef typename meta::integral::make_position_index_vector< index_type, VisibilityMask::size >::type index_positions;
	    public:
	      typedef typename meta::integral::remove_false< index_positions, VisibilityMask >::type type;
	  };

	  //---| unmask_indiex
	  //-----find index in full_layout corresponding to MaskedIndex

	  template< typename VisibilityMask, index_type MaskedIndex >
	  class unmask_index
	  {
	      typedef typename unmask_indices< VisibilityMask >::type visible_index_positions;
	    public:
	      static constexpr index_type value = meta::integral::at< visible_index_positions, MaskedIndex >::value;
	  };
	} // of helpers::


	namespace
	{
	  //---| remove_indices
	  //-----remove a list of indices from FullLayout
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
	      typedef typename remove_index< tail, indices_pop::value >::type type;
	  };

	  //---| make_slice_layout
	  //-----remove hidden indices from FullLayout, add NewAttributes to new layout (type)

	  template< typename FullLayout, typename FullIndexMask, typename...NewIndexAttributes >
	  struct slice_layout_base
	  {
	      static_assert( FullIndexMask::size == FullLayout::order
			   , "Size of FullIndexMask and FullLayout::order must agree" );

	      typedef typename meta::integral::equal< typename FullLayout::sizes, FullIndexMask >::type visibility_mask;
	      typedef typename meta::integral::transform< visibility_mask , meta::integral::negate<bool> >::type hidden_mask;
	      typedef typename helpers::unmask_indices< hidden_mask >::type hidden_indices;

	      typedef typename remove_indices< FullLayout, hidden_indices >::type slice_layout;
	    // add attributes

	      typedef typename add_attributes< slice_layout, NewIndexAttributes... >::type type;
	  };

	} // of <anonymous>::

	//--------------------------
	//---| slice layout
	//--------------------------
	//-----| hides indices equal to size eg. at(FullIndexMask,i) == at(SizeVector,i)
	//-----| default: all indices visible
	template< typename FullLayout
		, typename FullIndexMask = typename meta::integral::make_vector< index_type, typename FullLayout::sizes >::type
		, typename...NewIndexAttributes
		>
	class slice_layout : public slice_layout_base< FullLayout, FullIndexMask, NewIndexAttributes... >::type
	{
	    static_assert( FullIndexMask::size == FullLayout::order
			 , "Size of FullIndexMask and FullLayout::order must agree"
			 );
	    static_assert( not meta::integral::any< typename meta::integral::equal< typename FullLayout::sizes
										  , meta::integral::constant< size_type, 0 >
										  >::type
						  >::value
			 , "Index with empty range (Size=0) are not allowed"
			 );

	  public:

	    // mask

	    typedef typename slice_layout_base< FullLayout, FullIndexMask >::type 	     layout;
	    typedef typename slice_layout_base< FullLayout, FullIndexMask >::visibility_mask visibility_mask;

	    typedef FullIndexMask  full_index_mask;
	    typedef FullLayout full_layout;

	    //---| total_size
	    //-----number of Values (memory-)managed by the layout
	    //-----note: empty layout has total_size=1
	    static constexpr size_type total_size = full_layout::total_size;

	    //:::| memory model

	    //-----| static_offset

	    static constexpr stride_type static_offset()
	    {
	      typedef typename meta::integral::transform< visibility_mask , meta::integral::negate<bool> >::type hidden_mask;
	      // remove free indices from the dope vectors
	      typedef typename meta::integral::remove_false< typename full_layout::strides, hidden_mask >::type hidden_strides;
	      typedef typename meta::integral::remove_false< full_index_mask, hidden_mask >::type hidden_indices;

	      return meta::integral::inner_product< hidden_strides, hidden_indices >::value + full_layout::static_offset();
	    }

	};

      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
