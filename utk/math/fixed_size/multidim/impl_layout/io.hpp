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

# include <boost/lexical_cast.hpp>

# include "utk/meta/integral/integral.hpp"

# include "utk/math/fixed_size/multidim/impl_interface/interface.hpp"
# include "utk/math/fixed_size/multidim/impl_interface/change_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {

	template< typename...Attributes >
	std::ostream& operator<< ( std::ostream& os, const layout< Attributes... >& l )
	{
	  typedef layout< Attributes... > type;

	  // header
	  os << "fixed_size::multidim::layout\t|" << std::endl
	     //<< "  typeid " <<< typeid(type).name() << std::endl // requires <typeinfo>
	     << "  size " << typename type::sizes() << " (total " << type::total_size << ") "
	     << "  stride " << typename type::strides()
	     << "  offset " << type::static_offset() << "  "
	     << ( sizeof...(Attributes) > 2
		  ? "  attributes " + boost::lexical_cast<std::string>( sizeof...(Attributes) - 2 )
		  : ""
		) << std::endl;

	  return os;
	}

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
