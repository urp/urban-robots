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

# include <pair>

# include "utk/geometry/ray/ray.hpp"
# include "utk/geometry/plane/plane.hpp"

namespace utk
{
  namespace geometry
  {

	// return ray parameter of intersection point of a ray and a plane
    template< typename T, size_t Dim >
    typename ray<T,Dim>::parameter_type intersection( const ray<T,Dim>& ray, const plane<T,Dim>& plane )
    {
      const T denom = dot( ray.direction(), plane.normal() ); 
      //assert( denom != 0 ); 
      return ( plane.distance() - dot( ray.source() , plane.normal() ) ) / denom; 
    }

  }
}

