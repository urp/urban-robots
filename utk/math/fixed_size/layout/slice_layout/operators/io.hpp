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

//# include "utk/math/fixed_size/layout/generic_layout/functions/io.hpp"
# include "utk/math/fixed_size/layout/slice_layout/slice_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace layout
      {

	template< typename FullLayout, typename FullIndexMask, typename...NewIndexAttributes >
	std::ostream& operator<< ( std::ostream& os, const slice_layout< FullLayout, FullIndexMask, NewIndexAttributes... >& l )
	{
	  typedef slice_layout< FullLayout, FullIndexMask, NewIndexAttributes... > type;

	  // header
	  os << "fixed_size::layout::slice_layout\t|" << std::endl
	     << "  type\t" << typename type::base() << std::endl
	     << "  mask\t" << FullIndexMask() << "  offset " << type::static_offset()
	     << ( sizeof...(NewIndexAttributes) > 0
		  ? "  new attributes " + boost::lexical_cast<std::string>( sizeof...(NewIndexAttributes) )
		  : ""
		) << std::endl
	     << "  full\t" << FullLayout();
	  return os;
	}

      } // of layout::
    } // of fixed_size::
  } // of math::
} // of utk::
