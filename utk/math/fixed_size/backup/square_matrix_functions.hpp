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

# include "utk/math/fixed_size/square_matrix_interface.hpp"
# include "utk/math/fixed_size/square_matrix_array.hpp"

namespace utk
{
  namespace math
  {
	namespace fixed_size
	{

	  matn<T,Cnt>	transposed() const
	  {
	    matn<T,Cnt> res;
	    for(size_t i=0;i<Cnt;i++)
		  for(size_t j=0;j<Cnt;j++)
		    res(i,j)=valref(j,i);
	    return res;
	  }
	  
	  vector_interface<T,Cnt>	col_sums()	const
	  {
	    vector_interface<T,Cnt> s;
	    for(size_t i=0;i<Cnt;i++)
		  s[i]+=colit[i].sum();
	    return s;
	  }
	  
	  vector_array<T,Cnt>	diag()	const
	  {
	    vector_array<T,Cnt> d;	
	    for(size_t i=0;i<Cnt;i++)
		  d[i]=valref(i,i);
	    return d;
	  }
	  
	  void fill( const T& d = T(0), const T& nd = T(0) )
	  {
	    for(size_t i=0;i<Cnt;i++)
		  for(size_t j=0;j<Cnt;j++)
		    valref(i,j)= i==j ? d : nd;
	  }
	  
	} // of fixed_size::
  } // of math::
} // of utk::
