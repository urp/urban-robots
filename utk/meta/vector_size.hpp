/*  vector_at.hpp - Copyright Peter Urban 2012

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

# include "utk/meta/integral/constant.hpp"

# include "utk/meta/vector.hpp"

namespace utk
{
  namespace meta
  {

    //---| at

    template< typename > struct size { /* unspecified */ };

    template< typename...Vector >
    struct size< vector< Vector... > >
    {
      typedef integral::constant< size_type, sizeof...(Vector) > type;
    };

  } // of meta::
} // of utk::
