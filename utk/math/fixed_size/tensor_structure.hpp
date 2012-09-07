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

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      using integral::index_type;

      // TODO: bad

      typedef unsigned size_type;
      typedef unsigned param_type;
      typedef unsigned dimension_type;
      typedef unsigned stride_type;

      //-----| bool_vector

      template< bool...Bools >
      using bool_vector = integral::vector< bool, Bools... >;

      //-----| index_vector

      template< index_type... Indices >
      using index_vector = integral::vector< index_type, Indices... >;

      //-----| size_vector

      template< size_type... Sizes >
      using size_vector = integral::vector< size_type, Sizes... >;

      //-----| stride_vector

      template< size_type... Strides >
      using stride_vector = integral::vector< stride_type, Strides... >;

      namespace helpers
      {
	//---| stride_sequence

	namespace
 	{
	  template< typename, typename > struct stride_sequence_recursion { /* unspecified */ };

	  template< stride_type...Strides >
	  struct stride_sequence_recursion< integral::vector< stride_type, Strides... >, integral::vector< size_type > >
	  {
	    typedef stride_vector< Strides... > type;
	  };

	  template< stride_type...Strides, size_type...Sizes >
	  class stride_sequence_recursion< integral::vector< stride_type, Strides... >, integral::vector< size_type, Sizes... > >
	  {
	      typedef typename integral::pop_front< integral::vector< size_type, Sizes... > > stripped;

	      static const stride_type new_stride = integral::pop_back< integral::vector< stride_type, Strides... > >::value * stripped::value;

	    public:

	      typedef typename stride_sequence_recursion< integral::vector< stride_type, Strides..., new_stride >, typename stripped::tail >::type type;
	  };
	}

	template< typename > struct stride_sequence { /* unspecified */ };

	template< size_type... Sizes >
	struct stride_sequence< integral::vector< size_type, Sizes... > >
	{
	  typedef typename stride_sequence_recursion< integral::vector< stride_type, 1 >
							, integral::vector< size_type, Sizes... > >::type type;
	};


	//---| stride
	//-----extract stride
	template< typename StrideVector, dimension_type Dim >
	struct stride
	{
	  static_assert( Dim <= StrideVector::size, "requested stride is undefined" );
	  //TODO: find out what gcc doesn't like about my helper.
	  //NOTE: SUPERSTRANGE works with Dim soecified explicitly (by using a constant)
	  //static constexpr stride_type value = integral::at< StrideVector, Dim >::value ;
	  const static stride_type value = boost::mpl::at_c< typename StrideVector::mpl_vector_c, Dim >::type::value;
	};

      } // of helpers::

      //---------------------
      //---| tensor structure
      //---------------------

      template< typename, typename>
      class tensor_structure
      { /* unspecified*/ };

      template< index_type... IndexInfo, size_type... Sizes >
      class tensor_structure< index_vector< IndexInfo... >, size_vector< Sizes... > >
      {
	  static_assert( sizeof...(IndexInfo) == sizeof...(Sizes)
			 , "the number of indices forwarded in index_vector< ... >"
			   " and the number sizes forwarded in size_vector< ... > must agree" );

	public:

	  typedef index_vector< IndexInfo... >	indices;
	  typedef  size_vector< Sizes ... >	sizes;

	  typedef tensor_structure< indices, sizes > type;

	  typedef typename helpers::stride_sequence< sizes >::type strides;

	  //---| stride
	  //-----extract stride
	  template< dimension_type Dim >
	  struct stride
	  {
	    static_assert( Dim <= sizeof...(Sizes), "requested dimension does not exist" );
	    //TODO: find out what gcc doesn't like about my helper
	    const static stride_type value = integral::at< strides, Dim >::value;
	  };

	  //---| dimension
	  //-----query dimensionality
	  constexpr static const dimension_type dimension()  { return sizeof...(Sizes); }

	  //---| total_size
	  //-----query size (number of scalars)
	  constexpr static const size_type total_size()
	  { return helpers::stride< strides, dimension() >::value; }

	  //---| fix_dimension
	  //-----returns a new tensor_structure with dimension DimIndex fixed
	  template< dimension_type Dim, index_type Index >
	  class fix_dimension
	  {
	      static_assert( Dim < dimension(), "Dim exceeds range");
	      typedef typename integral::assign< indices, Dim, integral::constant< index_type, Index > >::type new_indices;
	    public:
	      typedef tensor_structure< new_indices, sizes > type;
	  };

	  //---| unfix_dimension
	  //-----returns a new tensor_structure with dimension DimIndex unfixed
	  template< dimension_type Dim >
	  class unfix_dimension
	  {
	      static_assert( Dim < dimension(), "Dim exceeds range");
	      static const index_type dim_size = integral::at< sizes, Dim >::value;
	    public:
	      typedef typename fix_dimension< Dim, dim_size >::type type;
	  };

	  //---| remove_fixed - TODO: rename to 'compact'
	  //-----returns a new tensor_structure with all fixed dimensions removed.
	  class remove_fixed
	  {
	      typedef typename integral::equal< indices, sizes >::type free_dimensions;
	      typedef typename integral::remove_false< indices, free_dimensions >::type sub_indices;
	      typedef typename integral::remove_false< sizes  , free_dimensions >::type sub_sizes;
	    public:
	      typedef tensor_structure< sub_indices, sub_sizes > type;
	  };


	  //***| free_coord_offset
	  //-----TODO: rename to inner_product

	  // accumulate
	  template< typename StrideVector, typename...Coords >
	  static const stride_type free_coord_offset_recurse( index_type UnpackedCoord, Coords... coords )
	  {
	    typedef integral::pop_front< StrideVector > strides;

	    return  UnpackedCoord * strides::value + free_coord_offset_recurse< typename strides::tail >( coords... );
	  }

	  // terminate
	  template< typename StrideVector > static const stride_type free_coord_offset_recurse( )
	  { return 0; }

	  //:::| memory model

  	  //-----return offset for the specified coordinates
	  template< typename...Coords >
	  static const stride_type free_coord_offset( Coords... coords )
	  {
	    static const dimension_type coord_size = sizeof...(coords);
	    //static_assert( StrideVector::size::value == remove_fixed::type::dimension(), " BUG ");
	    static_assert( coord_size <= remove_fixed::type::dimension(), "number of coordinates must be smaller than number of 'free' dimensions." );

	    typedef typename integral::equal< indices, sizes >::type free_dimensions;
	    typedef typename integral::pop_back< strides >::tail strides_tail;
	    typedef typename integral::remove_false< strides_tail, free_dimensions >::type free_strides;

	    return integral::inner_product< free_strides >( coords... );
	  }

      };


      template< size_type...Sizes >
      using initial_structure = tensor_structure< index_vector< Sizes... >, size_vector< Sizes... > >;

    }
  }
}
