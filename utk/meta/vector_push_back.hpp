/*  vector_push_back.hpp - Copyright Peter Urban 2012

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

# include "utk/meta/vector.hpp"

namespace utk
{
  namespace meta
  {

    //---| push_back

    template< typename, typename > struct push_back { /* unspecified */ };

    template< typename... Vector, typename Back >
    struct push_back< vector< Vector... >, Back >
    {
      typedef vector< Vector..., Back > type;
    };

  } // of meta::
} // of utk::
