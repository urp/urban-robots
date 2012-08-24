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

      template< index_type... IndexInfo >
      struct index_vector : public boost::mpl::vector_c< index_type, IndexInfo... >
      {	};
      //using index_vector = boost::mpl::vector_c< index_type, IndexInfo... >;
      
      template< size_type... SizeInfo >
      struct size_vector : public boost::mpl::vector_c< size_type, SizeInfo... >
      {	};
      //using size_vector = boost::mpl::vector_c< size_type, SizeInfo... >;

      namespace helpers
      {

	template< typename >
	struct repack { /* unspecified */ };

	template< typename T, T...Pack >
	struct repack< boost::mpl::vector_c< T, Pack...> >
	{
	  typedef typename std::enable_if< std::is_same< T, index_type >::value, index_vector< Pack... > >::type
 	  index_vector_type;
	  
	  typedef typename std::enable_if< std::is_same< T,  size_type >::value,  size_vector< Pack... > >::type
	  size_vector_type; 
	};
	

	template < index_type Index, class Sequence, class NewValue>
	class mpl_assign_element
	{
	    typedef typename boost::mpl::begin< Sequence>::type begin;
	    typedef typename boost::mpl::advance_c< begin, Index >::type pos;
	    typedef typename boost::mpl::erase<Sequence, pos>::type sequence2;

	    typedef typename boost::mpl::begin<sequence2>::type begin2;
	    typedef typename boost::mpl::advance_c<begin2, Index >::type pos2;
    	    typedef typename boost::mpl::insert <sequence2, pos2, NewValue>::type result_vec;

	  public:

	    typedef repack< result_vec > type;
        };

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

	  typedef index_vector< IndexInfo... >	index_info;
	  typedef  size_vector< SizeInfo ... >	size_info;

	  //---| extract stride

	  template< dimension_type Dim >
	  constexpr static stride_type stride( )
	  { 
		static_assert( Dim <= (sizeof...(SizeInfo)+1), "requested dimension does not exist" );
		return Dim == 0 ? 0 : extract_stride_recursion< Dim - 1 , SizeInfo... >();
	  }

	  constexpr static const size_type dimension()  { return sizeof...(SizeInfo); }
		
	  constexpr static const size_type total_size() { return stride< dimension() + 1  >(); }
		
	  constexpr static const std::array< size_type, dimension()/*TODO: why not dimension()*/ >	size_array()
	  {
		return std::array< size_type, dimension() >{ {SizeInfo...} };
	  }
	  
	  template< dimension_type Dim, index_type Index >
	  struct fix_dimension
	  {
		// TODO: check if dimension is already fixed
		typedef index_vector<  > free_indices;
		//typedef tensor< T, tensor_impl::replace< free_indices, Dim  >
	  };
	      
      };

      
      template< size_type...SizeInfo >
      using initial_structure = tensor_structure< index_vector< SizeInfo... >, size_vector< SizeInfo... > >;

    } 
  }
}
