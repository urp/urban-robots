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

# include "utk/math/fixed_size/vector/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace vector
      {
	// array (stack memory) managed by interface
	// TODO: !!! generate all fixed_size::*_array templates by MACROS
	template<typename T,size_t Cnt>
	class array : public interface<T,Cnt>
	{
	  private:

	    T	arr[Cnt];

	  public:

	    typedef T*  iterator;
	    typedef T*  const_iterator;

	    // construct with unitialized stack-memory
	    array() : interface<T,Cnt>(arr)	{ 	}

	    // initialize with scalar
	    explicit
	    array( const T& scalar ) : interface<T,Cnt>( arr )
	    { std::fill( interface<T,Cnt>::begin(), interface<T,Cnt>::end(), scalar); }

	    // copy sequence
	    template< typename Iterator >
	    array( Iterator begin_it ,Iterator end_it ) : interface<T,Cnt>( arr )
	    {
	      std::copy( begin_it, end_it, interface<T,Cnt>::begin() );
	    }

	    // copy interface
	    array( const interface<T,Cnt>& o )
	    : interface<T,Cnt>(arr)
	    { std::copy( o.begin(), o.end(), interface<T,Cnt>::begin() ); }

	    // TODO: needs LOVE (combine with variadic/init_list? conditional?)
	    // copy interface of different size
	    template<size_t Cnt2>
	    array(const interface<T,Cnt2>& o) : interface<T,Cnt>(arr)
	    { std::copy( o.ptr(), o.ptr()+std::min(Cnt,Cnt2), interface<T,Cnt>::begin() ); }


	    // initializer_list
	    array( std::initializer_list<T> seq ) : interface<T,Cnt>(arr)
	    {
	      assert( seq.size() == Cnt );
	      std::copy(seq.begin(), seq.end(), arr);
	    }

#	    ifdef UTK_MATH_FIXED_SIZE_VECTOR__VALARRAY_SUPPORT
	    // copy valarray
	    explicit
	    array( const std::valarray<T>& o ) : interface<T,Cnt>(arr)
	    {
	      assert(o.size()>=Cnt);
	      for(size_t i=0;i<Cnt;++i)
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
	template< typename ValueType, vector::size_type Size >
	using type = vector::array< ValueType, Size >;
      };

    } // of fixed_size::
  } // of math::
} // of utk::
