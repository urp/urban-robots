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

# include <array>
# include <utility>
# include <type_traits>

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/insert.hpp>

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      // TODO: bad
      typedef unsigned int size_type;
      typedef unsigned int param_type;
      typedef unsigned int dimension_type;
      typedef size_type index_type;
      typedef size_type stride_type;

      template<typename T, T Value>
      struct integral { static const T value = Value; };



      namespace helpers
      {
	//---| pop_front
	//-----splits non-type template sequences
	template< typename T, typename >
	struct pop_front { /* unspecified */ };

	template< typename T, T Unpacked, template<T...> class Container, T...Pack >
	struct pop_front< T, Container< Unpacked, Pack... > >
	{
	  static const T value = Unpacked;

	  typedef Container< Pack... > tail;
	};

	//---| assign

	namespace
	{
	  template< typename T, index_type, T ,typename, typename >
	  struct assign_recurse { /* unspecified */ };

	  // assign -> terminate
	  template< typename T, T NewValue, template<T...> class Container, T Unpacked, T...NewPack, T...OldPack >
	  struct assign_recurse< T, 0, NewValue, Container< NewPack... >, Container< Unpacked, OldPack... > >
	  { typedef Container< NewPack..., NewValue , OldPack... > type; };

	  // move value to result -> recurse
	  template< typename T, index_type Index, T NewValue, template<T...> class Container, T...NewPack, T Unpacked, T...OldPack  >
	  struct assign_recurse< T, Index, NewValue, Container< NewPack... >, Container< Unpacked, OldPack... > >
	  { typedef typename assign_recurse< T, Index-1, NewValue, Container< NewPack..., Unpacked >, Container< OldPack... > >::type type; };
	}

	// start recursion
	template< typename T, index_type, T, typename  > struct assign {  };
	template< typename T, index_type Index, T NewValue, template<T...> class Container, T...OldPack >
	struct assign< T, Index, NewValue, Container< OldPack... > >
	{
	  static_assert( Index < sizeof...(OldPack), "Index must be smaller than Container size" );
	  typedef typename assign_recurse< typename Container<>::value_type, Index, NewValue, Container<>, Container< OldPack... > >::type type;
	};

	//---| at

	template< typename T, index_type, typename > struct at {  };

	template< typename T, template<T...> class Container, T Unpacked, T...Pack >
	struct at< T, 0, Container< Unpacked, Pack... > >
	{
	  static const T value = Unpacked;
	};

	template< typename T, index_type DimIndex, template<T...> class Container, T Unpacked, T...Pack >
	struct at< T, DimIndex, Container< Unpacked, Pack... > >
	{
	  static_assert( DimIndex < sizeof...(Pack)+1, "Index must be smaller than Container size" );
	  typedef T value_type;
	  static const T value = at< T, DimIndex-1, Container< Pack... > >::value;
	};

      } // of helpers


      //---| dimension info structures
      //-----TODO: avoid repetition - use template typedef - requires deduction of parameter pack type

      //-----| index_vector

      template< index_type... IndexInfo >
      struct index_vector
      {
	typedef index_type value_type;
	typedef boost::mpl::vector_c< index_type, IndexInfo... > mpl_vector;

	template< dimension_type DimIndex>
	constexpr static const value_type at()
	{ return helpers::at< index_type, DimIndex, index_vector< IndexInfo... > >::value; }

      };

      //-----| size_vector

      template< size_type... SizeInfo >
      struct size_vector
      {
	typedef size_type value_type;
	typedef boost::mpl::vector_c< size_type, SizeInfo... > mpl_vector;

	template< dimension_type DimIndex>
	constexpr static const value_type at()
	{ return helpers::at< size_type, DimIndex, size_vector< SizeInfo... > >::value; }

      };

      namespace helpers
      {
	//---| remove fixed_dimensions - TODO: add predicate tempalate parameter ( or simply a bool )

	namespace
	{
	  template< typename, typename, typename, typename >
	  struct remove_fixed_recursion	{	};

	  // terminate
	  template< index_type...NewIndices, size_type...NewSizes >
	  struct remove_fixed_recursion< index_vector< NewIndices... >, index_vector< >
				       ,  size_vector< NewSizes... >  ,  size_vector< > >
	  {
	    typedef std::pair< index_vector< NewIndices... >, size_vector< NewSizes... > > type;
	  };

	  // remove if UnpackedIndex!=UnpackedSize -> continue
	  template< index_type...NewIndices, index_type UnpackedIndex, index_type...OldIndices
		  ,  size_type...NewSizes  ,  size_type UnpackedSize ,  size_type...OldSizes   >
	  struct remove_fixed_recursion< index_vector< NewIndices... >, index_vector< UnpackedIndex, OldIndices... >
				       ,  size_vector< NewSizes...   >,  size_vector< UnpackedSize , OldSizes...   > >
	  {
	    typedef typename std::conditional< UnpackedIndex != UnpackedSize
					     , typename remove_fixed_recursion< index_vector< NewIndices... >, index_vector< OldIndices... >
									      ,  size_vector< NewSizes... >  ,  size_vector< OldSizes...   >
									      >::type
    					     , typename remove_fixed_recursion< index_vector< NewIndices..., UnpackedIndex >, index_vector< OldIndices... >
									      ,  size_vector< NewSizes...  , UnpackedSize  >,  size_vector< OldSizes...   >
									      >::type
					     >::type type;
	  };

	} // of <anonymous>

	template< typename, typename >  struct remove_fixed_dimensions	{	};

	template< index_type...Indices, size_type...Sizes >
	struct remove_fixed_dimensions< index_vector< Indices... >, size_vector< Sizes... > >
	{
	  typedef typename remove_fixed_recursion< index_vector<>, index_vector< Indices... >
						 ,  size_vector<>,  size_vector< Sizes...   >
						 >::type type;
	};

	/***| sub_structure

	namespace
	{
	  template< typename, typename, typename, typename >
	  struct sub_structure_recursion	{	};

	  // terminate
	  template< index_type...NewIndices, size_type...NewSizes >
	  class sub_structure_recursion< index_vector< NewIndices... >, index_vector< >
				       ,  size_vector< NewSizes... >  ,  size_vector< > >
	  {
	    typedef std::pair< index_vector< NewIndices... >, size_vector< NewSizes... > > type;
	  };

	  // remove if UnpackedIndex!=UnpackedSize -> continue
	  template< index_type UnpackCoord  , index_type...Coords
		  , index_type UnpackedIndex, index_type...Indices
		  ,  size_type UnpackedSize ,  size_type...Sizes >
	  class sub_structure_recursion< index_vector< UnpackedIndex, Indices... >, size_vector< UnpackedSize , Sizes... > >
	  {


	    typedef typename std::conditional< UnpackedIndex != UnpackedSize
			*/	/*fixed*/ /*   , typename remove_fixed_recursion< index_vector< OldIndices... >
									      ,  size_vector< OldSizes...   >
									      >::type
    			*/	/*free*/ /*     , typename remove_fixed_recursion< index_vector< OldIndices... >
									      , size_vector< OldSizes...   >
									      >::type
					     >::type type;

	    public:

	      typedef typename integral< stride_type, recursion_type::offset >  offset;

	  };
	}


	template< typename, typename >  struct sub:structure {	};

	template< index_type...Indices, size_type...Sizes >
	class sub_structure< index_vector< Indices... >, size_vector< Sizes... > >
	{
	    typedef typename sub_structure_recursion< index_vector<>, index_vector< Indices... >
						    ,  size_vector<>,  size_vector< Sizes...   >
						    >::type recursion;

	  public:

	    typedef typename integral< stride_type, recursion_type::offset >  offset;

	    typedef typename result::sub_structure sub_structure;
	};*/

      } // of helpers

      //---------------------
      //---| tensor structure
      //---------------------

      template< typename, typename>
      class tensor_structure
      { /* unspecified*/ };

      template< index_type... IndexInfo, size_type... SizeInfo >
      class tensor_structure< index_vector< IndexInfo... >, size_vector< SizeInfo... > >
      {
	  static_assert( sizeof...(IndexInfo) == sizeof...(SizeInfo)
				   , "the number of indices forwarded in index_vector< ... >"
				     " and the number sizes forwarded in size_vector< ... > must agree"
				   );
	  // helpers

	  template< dimension_type Dim >
	  constexpr static stride_type extract_stride_recursion( )
	  {
	    return 1;
	  }

	  template< dimension_type Dim, size_type Size1, size_type... Sizes >
	  constexpr static stride_type extract_stride_recursion( )
	  {
	    return Dim == 0 ? 1 :  Size1 * extract_stride_recursion< Dim - 1 , Sizes... >();
	  }

	public:

	  typedef tensor_structure< index_vector< IndexInfo... >, size_vector< SizeInfo... > > type;

	  typedef index_vector< IndexInfo... >	indices;
	  typedef  size_vector< SizeInfo ... >	sizes;

	  //---| stride
	  //-----extract stride
	  template< dimension_type Dim >
	  constexpr static stride_type stride( )
	  {
	    static_assert( Dim <= sizeof...(SizeInfo), "requested dimension does not exist" );
	    //TODO: find out what gcc doesn't like about my helper
	    return extract_stride_recursion< Dim, SizeInfo... >();
		    /*helpers::stride< Dim, size_vector< SizeInfo... > >::value;*/
	  }

	  //---| dimension
	  //-----query dimensionality
	  constexpr static const dimension_type dimension()  { return sizeof...(SizeInfo); }

	  //---| total_size
	  //-----query size (number of scalars)
	  constexpr static const size_type total_size()
	  { return stride< dimension() >(); }

	  //---| size_array
	  //-----returns an std::array containing the size of all tensor-dimensions
	  constexpr static const std::array< size_type, dimension() >	size_array()
	  {
	    return std::array< size_type, dimension() >{ {SizeInfo...} };
	  }

	  //---| fix_dimension
	  //-----returns a new tensor_structure with dimension DimIndex fixed
	  template< dimension_type DimIndex, index_type Index >
	  class fix_dimension
	  {
	      static_assert( DimIndex < dimension(), "Dim exceeds range");
	      typedef typename helpers::assign< index_type, DimIndex, Index, indices >::type new_indices;
	    public:
	      typedef tensor_structure< new_indices, sizes > type;
	  };

	  //---| unfix_dimension
	  //-----returns a new tensor_structure with dimension DimIndex unfixed
	  template< dimension_type DimIndex >
	  class unfix_dimension
	  {
	      static_assert( DimIndex < dimension(), "Dim exceeds range");
	      static const index_type dim_size = helpers::at< size_type, DimIndex, sizes >::value;
	    public:
	      typedef typename fix_dimension< DimIndex, dim_size >::type type;
	  };

	  //---| remove_fixed - TODO: rename to 'compact'
	  //-----returns a new tensor_structure with all fixed dimensions removed.
	  class remove_fixed
	  {
	      typedef typename helpers::remove_fixed_dimensions< indices, sizes >::type sub;
	    public:
	      typedef tensor_structure< typename sub::first_type, typename sub::second_type > type;
	  };


	  //***| free_coord_offset
	  //-----TODO: rename to inner_product

	  // accumulate
	  template< typename StrideVector, typename...Coords >
	  stride_type free_coord_offset( index_type UnpackedCoord, Coords... coords )
	  {
	    static const stride_type stride_head = helpers::pop_front< stride_type, StrideVector >::value;

	    typedef typename helpers::pop_front< stride_type, StrideVector >::type::tail stride_tail;

	    return  UnpackedCoord * stride_head + free_coord_offset< stride_tail >( coords... );
	  }

	  // terminate
	  template< typename StrideVector > stride_type free_coord_offset( )
	  { return 0; }

	  //start
  	  //-----return offset for the specified coordinates
	  template< typename StrideVector/*strides of the full tensor for all free dimensions*/, typename...Coords >
	  stride_type free_coord_offset( Coords... coords )
	  {
	    static const dimension_type coord_size = sizeof...(coords);
	    static_assert( StrideVector::size::value == dimension() - remove_fixed::dimension(), " BUG ");
	    static_assert( coord_size <= dimension() - remove_fixed::dimension(), "number of coordinates must be smaller than number of 'free' dimensions." );

	    return free_coord_offset< StrideVector >( coords... );
	  }

      };


      template< size_type...SizeInfo >
      using initial_structure = tensor_structure< index_vector< SizeInfo... >, size_vector< SizeInfo... > >;

    }
  }
}
