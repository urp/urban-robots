/*  interface.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/storage_traits.hpp"
# include "utk/math/fixed_size/vector/vector.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace vector
      {
	struct unmanaged_tag {};
	struct managed_tag {};

	std::ostream& operator<< ( std::ostream& os, const unmanaged_tag& )
	{
	  return os << "unmanaged";
	}

	std::ostream& operator<< ( std::ostream& os, const managed_tag& )
	{
	  return os << "managed";
	}

	struct default_storage_tags
	{
	  typedef unmanaged_tag unmanaged;

	  typedef managed_tag managed;
	};

      } // of vector:

      template< >
      struct storage_traits< vector::unmanaged_tag > : public vector::default_storage_tags
      {
	template< typename ValueType, vector::size_type Size >
	using type = vector::interface< ValueType, Size >;
      };

      template< >
      struct storage_traits< vector::managed_tag > : public vector::default_storage_tags
      {
	template< typename ValueType, vector::size_type Size >
	using type = vector::array< ValueType, Size >;
      };

    } // of fixed_size::
  } // of math::
} // of utk::
