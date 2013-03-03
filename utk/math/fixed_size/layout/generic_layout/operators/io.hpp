/*  io.hpp - Copyright Peter Urban 2012

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

# include <iostream>

# include <boost/lexical_cast.hpp>

# include "utk/meta/integral/integral.hpp"

# include "utk/math/fixed_size/layout/generic_layout/generic_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace layout
      {

	template< typename...Attributes >
	std::ostream& operator<< ( std::ostream& os, const generic_layout< Attributes... >& l )
	{
	  typedef generic_layout< Attributes... > type;

	  // header
	  os << "fixed_size::layout::generic_layout\t|" << std::endl
	     << "  size " << typename type::sizes() << " (total " << type::total_size << ") "
	     << "  stride " << typename type::strides()
	     << "  offset " << type::static_offset() << "  "
	     << ( sizeof...(Attributes) > 2
		  ? "  attributes " + boost::lexical_cast<std::string>( sizeof...(Attributes) - 2 )
		  : ""
		) << std::endl;

	  return os;
	}

      } // of layout::
    } // of fixed_size::
  } // of math::
} // of utk::
