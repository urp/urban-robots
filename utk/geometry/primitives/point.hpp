/*  bla.h - Copyright Peter Urban 2012

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

# include "utk/math/vecn/vecn.hpp"

namespace utk
{
  namespace geometry
  {

	template< typename T, size_t Dim=3>
	using point = math::veca<T,Dim>;

	template< typename T, size_t Dim=3>
	using point_reference = math::vecn<T,Dim>;

	template< typename T, size_t Dim=3>
	using const_point_reference = const math::vecn<T,Dim>;
	
    enum	point_classification_type	{ INSIDE = -1, ONTO = 0, OUTSIDE = 1 };

  }
}
