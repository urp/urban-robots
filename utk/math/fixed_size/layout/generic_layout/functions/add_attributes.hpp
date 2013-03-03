/*  add_attributes.h - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/layout/generic_functions/add_attributes.hpp"

# include "utk/math/fixed_size/layout/generic_layout/generic_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace layout
      {
        //---| add_attributes

        //template< typename Layout, typename...NewAttributes > struct add_attributes { /* unspecified */ };

        template< typename...Attributes, typename...NewIndexAttributes >
        struct add_attributes< generic_layout< Attributes... >, NewIndexAttributes... >
        {
          typedef generic_layout< Attributes..., NewIndexAttributes... > type;
        };

      } // of layout::
    } // of fixed_size
  } // of math::
} // of utk::
