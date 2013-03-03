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

# define UTK_MATH_FIXED_SIZE_VECTOR__VALARRAY_SUPPORT

# ifdef  UTK_MATH_FIXED_SIZE_VECTOR__VALARRAY_SUPPORT
#   include <valarray>
# endif

# include <cassert>

# include "utk/math/fixed_size/interface/vector/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {
	namespace vector
	{
	  // array (stack memory) managed by interface
	  template< typename ValueType, size_type Size >
	  class array : public interface< ValueType, Size >
	  {

	      typedef interface< ValueType, Size > base;

	      ValueType	arr[ Size ];

	    public:

	      // construct with unitialized stack-memory
	      array() : interface< ValueType, Size >( arr )
	      { 	}

	      // initialize with scalar
	      explicit
	      array( const ValueType& scalar ) : base( arr )
	      {
		std::fill( base::begin(), base::end(), scalar );
	      }

	      // copy sequence
	      template< typename Iterator >
	      array( Iterator begin_it ,Iterator end_it ) : base( arr )
	      {
		std::copy( begin_it, end_it, base::begin() );
	      }

	      // copy interface
	      array( const interface< ValueType, Size >& o )
	      : interface< ValueType, Size >( arr )
	      {
		std::copy( o.begin(), o.end(), base::begin() );
	      }

	      // TODO: needs LOVE (combine with variadic/init_list? conditional?)
	      // copy interface of different size
	      template< size_type Size2 >
	      array( const interface< ValueType, Size2 >& o ) : base( arr )
	      {
		std::copy( o.ptr(), o.ptr()+std::min( Size, Size2 ), base::begin() );
	      }


	      // initializer_list
	      array( std::initializer_list< ValueType > seq ) : base( arr )
	      {
		//static_assert( seq.size() == Size, "initializer_list has wrong size" );
		std::copy( seq.begin(), seq.end(), arr );
	      }

  #	    ifdef UTK_MATH_FIXED_SIZE_VECTOR__VALARRAY_SUPPORT
	      // copy valarray
	      explicit
	      array( const std::valarray<ValueType>& o ) : interface<ValueType,Size>(arr)
	      {
		assert( o.size()>=Size );
		for(size_t i=0;i<Size;++i)
		  arr[i]=o[i];
	      }
  #	    endif

	      virtual
	      ~array()
	      {	}

	  }; // of array

	} // of vector::

	//:::| storage_traits |:::::::::::::::::::::::::::::::::::::::::::

	template< >
	struct storage_traits< vector::managed_tag > : public vector::default_storage_tags
	{
	  template< typename ValueType, size_type Size >
	  using type = vector::array< ValueType, Size >;
	};

      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
