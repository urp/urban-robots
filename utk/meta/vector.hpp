/*  vector.hpp - Copyright Peter Urban 2012

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

#include <boost/mpl/vector.hpp>

namespace utk
{
  namespace meta
  {
    // TODO: move to seperate file
    typedef ptrdiff_t index_type;
    typedef size_t size_type;

    //---| vector

    template< typename... Content >
    struct vector
    {
      static constexpr size_type size = sizeof...(Content);

      typedef boost::mpl::vector< Content... > mpl_vector;

      vector() = default;
    };
  } // of meta::
} // of utk::
