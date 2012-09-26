//libutk - a utility library 
//Copyright (C) 2006  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

# pragma once

# include	"utk/math/fixed_size/square_matrix_interface.hpp"
# include	"utk/math/fixed_size/vector_array.hpp"

# pragma GCC visibility push(default)

namespace utk
{ 
  namespace math
  {
	namespace fixed_size
	{

      template< typename T, size_t Cnt >
      class mata : public matn<T,Cnt>
      { 
          vector_array<T,Cnt*Cnt> arr;
          
        public:
  
          mata() : matn<T,Cnt>(arr)							
          { matn<T,Cnt>::vec().fill(); }
				    
		  //fill diagonal elements
          explicit mata(const T& de,const T& nde=T(0)) : matn<T,Cnt>( arr.ptr() )
		  { fill(de,nde); }
          
          explicit mata(const vector_interface<T,Cnt> diag) : matn<T,Cnt>( arr.ptr() )
		  {
		    for(size_t i=0;i<Cnt;i++) 
			  for(size_t j=0;j<Cnt;j++) 
			    matn<T,Cnt>::valref(i,i)= i==j? diag[i] : T(0) ;
		  }
         
          explicit mata(const std::valarray<T>& diag) : matn<T,Cnt>( arr.ptr() )
		  { 
            assert(diag.size()==Cnt); 
		    for(size_t i=0;i<Cnt;i++)
			  for(size_t j=0;j<Cnt;j++)
			    matn<T,Cnt>::valref(i,i)= i==j? diag[i] : T(0);
		  }
		  
          explicit mata(T* array) : matn<T,Cnt>( arr.ptr() )
  	      {
		    assert(array!=0); 
		    for(size_t i=0;i<Cnt;i++)
			  for(size_t j=0;j<Cnt;j++)
			    matn<T,Cnt>::valref(i,j)=array[i*Cnt+j];
		  }
          
          template<size_t Cnt2> 		
          mata(const matn<T,Cnt2>& o) : matn<T,Cnt>( arr.ptr() )
		  {
		    const size_t cnt=std::min(Cnt,Cnt2);
	        for(size_t i=0;i<cnt;i++)
			  for(size_t j=0;j<cnt;j++)
			    matn<T,Cnt>::valref( i, j ) = o( i, j );
		  }
		  
  	      mata( const matn<T,Cnt>& other ) : matn<T,Cnt>( arr.ptr() )
		  { std::copy( other.begin(), other.end(), begin() ); }
		  
      };//of square_matrix_array

      
	} // of fixed_size::
  } // of math:: 
} // of utk::

#pragma GCC visibility pop

