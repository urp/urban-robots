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

# include "utk/geometry/plane/plane.hpp"
# include "utk/geometry/ray/ray.hpp"

namespace utk
{
  namespace geometry
  {
	// 
    template< typename T >
    plane<T,2>                plane_from_ray( const ray<T,2>& );

  }
}

//---------------
// IMPLEMENTATION
/////////////////

template< typename T >
utk::geometry::plane<T,2>  utk::geometry::plane_from_ray(const ray<T,2>& r)
{
  //std::clog << "utk::plane_from_ray\t\t\t| " << r <<std::endl;
  
  const typename ray<T,2>::parameter_type      rlen = r.length();
  typename ray<T,2>::const_direction_reference rdir = r.direction();
  const typename ray<T,2>::direction_type      normal( -rdir[1] / rlen, rdir[0] / rlen );
    
  return plane<T,2>( normal , dot( normal, r.source() ) );
}
