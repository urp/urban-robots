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

# define UTK_MATH_FIXED_SIZE_VECTORS__VALARRAY_SUPPORT
# ifdef  UTK_MATH_FIXED_SIZE_VECTORS__VALARRAY_SUPPORT
#   include <valarray>
# endif

# include <cassert>

# include "utk/math/fixed_size/vector_interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      // array (in stack memory) with vector_interface interface
      template<typename T,size_t Cnt>
      class vector_array : public vector_interface<T,Cnt>
      {
	private:
	    
          T	arr[Cnt];
          
        public:
        
          typedef T*  iterator;
          typedef T*  const_iterator;
  
	  // construct with unitialized stack-memory
	  vector_array() : vector_interface<T,Cnt>(arr)	{ 	}
  
	  // initialize with scalar
          explicit
     	  vector_array( const T& scalar ) : vector_interface<T,Cnt>( arr )
          { std::fill( vector_interface<T,Cnt>::begin(), vector_interface<T,Cnt>::end(), scalar); }
  
	  // copy sequence
	  template< typename Iterator >
	  vector_array( Iterator begin_it ,Iterator end_it ) : vector_interface<T,Cnt>( arr )
          { 
	    std::copy( begin_it, end_it, vector_interface<T,Cnt>::begin() );
	  }
  
	  // copy vector_interface
          vector_array( const vector_interface<T,Cnt>& o )
          : vector_interface<T,Cnt>(arr)				
          { std::copy( o.begin(), o.end(), vector_interface<T,Cnt>::begin() ); }

	  // TODO: needs LOVE (combine with variadic/init_list? conditional?)
	  // copy vector_interface of different size
          template<size_t Cnt2>
	  vector_array(const vector_interface<T,Cnt2>& o) : vector_interface<T,Cnt>(arr)
	  { std::copy( o.ptr(), o.ptr()+std::min(Cnt,Cnt2), vector_interface<T,Cnt>::begin() ); }
  
  
          // initializer_list
          vector_array( std::initializer_list<T> seq ) : vector_interface<T,Cnt>(arr)
          {
            assert( seq.size() == Cnt );
            std::copy(seq.begin(), seq.end(), arr); 
          }
  
#	  ifdef UTK_MATH_FIXED_SIZE_VECTORS__VALARRAY_SUPPORT
	  // copy valarray			
          explicit
	  vector_array( const std::valarray<T>& o ) : vector_interface<T,Cnt>(arr)
          { 
            assert(o.size()>=Cnt); 
	    for(size_t i=0;i<Cnt;++i)
	      arr[i]=o[i];
	  }
# 	  endif

          virtual				
          ~vector_array()
    	  {	}
      };
    } // of fixed_size::
  } // of math::
} // of utk::
