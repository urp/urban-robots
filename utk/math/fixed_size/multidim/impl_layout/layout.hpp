/*  layout.hpp - Copyright Peter Urban 2012

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
# include "utk/meta/vector.hpp"

# include "utk/math/fixed_size/multidim/impl_layout/helpers.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {

	//---------------------
	//---| multidim layout
	//---------------------

	template< typename SizeVector
		, typename StrideVector = typename helpers::stride_sequence< SizeVector >::type // TODO: remove default - only applies if no attrib is given
		, typename...IndexAttributes
		>
	class layout
	{
	    static_assert( StrideVector::size == SizeVector::size
			 , "Size of StrideVector and SizeVector must agree"
			 );
	    static_assert( not meta::integral::any< typename meta::integral::equal< SizeVector, meta::integral::constant< size_type, 0 > >::type >::value
			 , "Index with empty range (Size=0) are nor allowed"
			 );

	  public:
	    layout() {}

	    typedef meta::vector< SizeVector, StrideVector, IndexAttributes... > attributes;

	    typedef   SizeVector sizes;
	    typedef StrideVector strides;

	    //---| order
	    //-----number of dimensions
	    static constexpr size_type order = sizes::size;

	    //---| stride
	    //-----extract stride
	    template< index_type Index >
	    struct stride
	    {
	      static_assert( Index < strides::size, "requested dimension does not exist" );
	      const static stride_type value = meta::integral::at< strides, Index >::value;
	    };

	    //---| total_size
	    //-----query size (number of scalars)
	    //-----note: empty layout represents a scalar
	    static constexpr size_type total_size = helpers::total_size< sizes, strides >::value;

	    //:::| memory model

	    //---| index_offset
	    //-----return offset for the specified coordinates
	    template< typename...CoordinateTypes >
	    static const stride_type index_offset( CoordinateTypes... coords )
	    {
	      static_assert( sizeof...(CoordinateTypes) <= order, "number of provided coordinates and indices must agree." );

	      return meta::integral::inner_product_with_arguments< strides >( coords... );
	    }

	    //---| static_offset

	    static constexpr stride_type static_offset() { return 0; }

	};

	template< typename >
	struct make_layout { /* unspecified */ };

	template< typename...IndexAttributes >
	struct make_layout< meta::vector< IndexAttributes... > >
	{
	  typedef layout< IndexAttributes... > type;
	};

      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
