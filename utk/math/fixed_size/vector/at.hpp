/*  functions.h - Copyright Peter Urban 2012

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

# include <stdexcept>
# include <boost/lexical_cast.hpp>

# include "utk/math/fixed_size/vector/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace vector
      {

	template< typename T, size_t Size >
	T& at( interface< T, Size >& interface, size_t index ) throw( std::out_of_range )
	{
	  if( index >= interface.size )
	    throw std::out_of_range( "index "
				    + boost::lexical_cast<std::string>( index )
				    + " exceeds vector dimension"
				    + boost::lexical_cast<std::string>( interface.size )
				   );
	  return interface[index];
	}

	template< typename T, size_t Size >
	const T& at( const interface< T, Size >& interface, size_t index ) throw( std::out_of_range )
	{
	  if( index >= interface.size )
	    throw std::out_of_range( "index "
				    + boost::lexical_cast<std::string>( index )
				    + " exceeds vector dimension"
				    + boost::lexical_cast<std::string>( interface.size )
				   );
	  return interface[index];
	}

      } // of vector::
    } // of fixed_size::
  } // of math::
} // of utk::
