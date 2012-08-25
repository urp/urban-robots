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


      namespace helpers
      {
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

	template< typename T, index_type Index, template<T...> class Container, T Unpacked, T...Pack >
	struct at< T, Index, Container< Unpacked, Pack... > >
	{
	  static_assert(Index < sizeof...(Pack)+1, "Index must be smaller than Container size" );
	  typedef T value_type;
	  static const T value = at< T, Index-1, Container< Pack... > >::value;
	};

      } // of helpers


      // dimension info TODO: avoid repetition

      template< index_type... IndexInfo >
      struct index_vector
      {
	typedef index_type value_type;
	typedef boost::mpl::vector_c< index_type, IndexInfo... > mpl_vector;

	template< index_type Index>
	constexpr static const value_type at()
	{ return helpers::at< index_type, Index, index_vector< IndexInfo... > >::value; }

      };


      template< size_type... SizeInfo >
      struct size_vector
      {
	typedef size_type value_type;
	typedef boost::mpl::vector_c< size_type, SizeInfo... > mpl_vector;
	template< index_type Index>
	constexpr static const value_type at()
	{ return helpers::at< size_type, Index, size_vector< SizeInfo... > >::value; }

      };

      namespace helpers
      {
	//---| extract_stride
      /*
	template< dimension_type Dim,  >
	struct stride_type extract_stride_recursion( )
	{
	  return 1;
	}

	template< dimension_type Dim, size_type Size1, size_type... Sizes >
	constexpr static stride_type extract_stride_recursion( )
	{
	  return Dim == 0 ? 1 :  Size1 * extract_stride_recursion< Dim - 1 , Sizes... >();
	}*/
      }

      //-----| tensor structure

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

	  //---| extract stride

	  template< dimension_type Dim >
	  constexpr static stride_type stride( )
	  {
	    static_assert( Dim <= sizeof...(SizeInfo), "requested dimension does not exist" );
	    return extract_stride_recursion< Dim, SizeInfo... >();
	  }

	  constexpr static const size_type dimension()  { return sizeof...(SizeInfo); }

	  constexpr static const size_type total_size() { return stride< dimension() >(); }

	  constexpr static const std::array< size_type, dimension() >	size_array()
	  {
	    return std::array< size_type, dimension() >{ {SizeInfo...} };
	  }

	  template< dimension_type Dim, index_type Index >
	  class fix_dimension
	  {
	      static_assert( Dim < dimension(), "Dim exceeds range");
	      typedef typename helpers::assign< index_type, Dim, Index, indices >::type new_indices;
	    public:
	      typedef tensor_structure< new_indices, sizes > type;
	  };

	  template< dimension_type Dim >
	  class unfix_dimension
	  {
	      static_assert( Dim < dimension(), "Dim exceeds range");
	      static const index_type dim_size = helpers::at< size_type, Dim, sizes >::value;
	    public:
	      typedef typename fix_dimension< Dim, dim_size >::type type;
	  };
      };


      template< size_type...SizeInfo >
      using initial_structure = tensor_structure< index_vector< SizeInfo... >, size_vector< SizeInfo... > >;

    }
  }
}
