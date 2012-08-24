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

# include "utk/math/fixed_size/square_matrix_interface.hpp"

# pragma GCC visibility push(default)

namespace utk
{ 
  namespace math
  {
	namespace fixed_size
	{

	  //---| stream io operators
	    
      template< typename T, size_t Cnt >
      std::ostream& operator<<( std::ostream& os, const matn<T,Cnt>& m )	
      {
	    std::foreach( m.col_begin(), m.col_end()
				    , [os](matn<T,Cnt>::column_iterator col ) { os << col; if(col  }
				    )
				    
        for(size_t i=0;i<Cnt;i++)
	    { for(size_t j=0;j<Cnt;j++)	
	        os << m(j,i) << "\t" ;
	        os<<std::endl;
	    }   
	    return os;
      }
  
	  //---| pointer interface operators
  
	  //---| arithmetic operators
  
      template<class T,size_t Cnt>
      vector_array<T,Cnt>						operator*(const matn<T,Cnt>& m,const vector_interface<T,Cnt>& v)	
      { 
        vector_array<T,Cnt> res(T(0));
	    for(size_t i=0;i<Cnt;i++)	
	      res+=m[i]*v[i];
	    return res;
      }
      
      template<class T,size_t Cnt>
      vector_array<T,Cnt>						operator*(const vector_interface<T,Cnt>& v,const matn<T,Cnt>& m)	
      { 
        vector_array<T,Cnt> res;
	    for(size_t i=0;i<Cnt;i++)	
	      res[i]=dot(v,m[i]);
	    return res;
      }
      
      template<class T,size_t Cnt>
      mata<T,Cnt>						operator*(const matn<T,Cnt>& m1,const matn<T,Cnt>& m2)	
      { 
        mata<T,Cnt> res;
	    for(size_t i=0;i<Cnt;i++)	
	      for(size_t j=0;j<Cnt;j++)	
		    res[i]+=m1[j]*m2[j][i];
	    return res;
      }
  
      
      matn<T,Cnt>&    operator*= (const matn<T,Cnt>& m)
	  { 
        iterator itv=begin();
        iterator itm=m.begin();
	    while(itv!=end()) 
	      *(itv++) *= *(itm++); 
	    return *this;
	  }
  
      mata<T,Cnt> operator* (const T& m)
      { 
        mata<T,Cnt> r;
	    iterator itr=r.begin();
	    iterator itv=begin();
	    while(itr!=r.end()) 
	      *(itr++) = (*(itv++)) * m; 
	    return r;
	  }      
      
      mata<T,Cnt>	operator/ (const T& m)
      { 
        mata<T,Cnt> r;
        iterator itr=r.begin();
        iterator itv=begin();
        while(itr!=r.end()) 
          *(itr++) = (*(itv++)) / m; 
        return r;
	  }
      
      matn<T,Cnt>&	operator*= (const T& m)
	  { iterator itv=begin();
        while(itv!=end()) 
	      *(itv++) *= m; 
	    return *this;
      }
    
      matn<T,Cnt>&	operator/= (const T& m)
      { 
        typename matn<T,Cnt>::iterator itv=begin();
	    while(itv!=end()) 
	      *(itv++) /= m; 
	    return *this;
	  }
	  
    } // of fixed_size:: 
  } // of math::
} // of utk::

#pragma GCC visibility pop
