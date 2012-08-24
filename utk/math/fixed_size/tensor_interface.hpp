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

# include "utk/math/fixed_size/vector_interface.hpp"
# include "utk/math/fixed_size/tensor_structure.hpp"


# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
	namespace fixed_size
	{
	  
	  //-----| tensor_interface
  
	  template< typename, typename > struct tensor_interface
	  { /* unspecified */ };
  
	  template < typename T, typename...Structure >
	  struct tensor_interface< T, tensor_structure< Structure... > > 
	  : public tensor_structure< Structure... >
	  ,	public vector_interface< T, tensor_structure< Structure... >::total_size() >
	  {
		  //---| 

		  typedef tensor_structure< Structure... > 				 structure;
		
		  typedef vector_interface< T, structure::total_size() > storage_base;

		  //---| constructor with storage pointer

		  explicit
		  tensor_interface( typename storage_base::pointer_type pointer ) : storage_base( pointer )  {	}

		  //---| fix dimension
	  
			
		  /*
		  std::conditional< dimension() > 1 )
					  , tensor_interface< T, strip_dimension< Dim-1,  >
					  , 
					  > 
		  operator[] ( size_t index ) { return ptr()+(O+S*index); }*/
			
	  };


	} // of fixed_size::
  } // of math::
} // of utk::
