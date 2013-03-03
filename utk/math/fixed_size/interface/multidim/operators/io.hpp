/*  io.hpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/interface/generic_functions/print_components.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {
	namespace multidim
	{

	  template< typename ValueType, typename Storage, typename Layout >
	  auto operator<< ( std::ostream& os, const interface< ValueType, Storage, Layout >& t )
	  -> std::ostream&
	  {
	    // header
	    os << interface_traits< interface< ValueType, Storage, Layout > >::class_name() << "\t|" << std::endl
	       << "  value_type " << typeid(ValueType).name()
	       << "  data " << t.storage << "(" << Storage() << ")" << std::endl
	       << "  layout " << Layout() << std::endl;
	    // content
	    return print_components( os << "  ", t ) << std::endl;
	  }
	} // of multidim::
      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
