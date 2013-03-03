/*  storage_traits.hpp - Copyright Peter Urban 2013

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

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {
        // defines a tag based to construct linear storage types ( like (un-)managed pointers and (managed) arrays,
        template< typename Storage > struct storage_traits
        {
          /* typedef unspecified unmanaged_tag*/
          /* typedef unspecified managed_tag*/
          /* typedef unspecified type*/
        };

      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
