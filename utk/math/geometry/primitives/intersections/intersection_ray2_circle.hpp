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

# include "utk/math/special_functions/solve_quadratic_equation.hpp"
# include "utk/geometry/ray/ray.hpp"
# include "utk/geometry/circle/circle.hpp"

namespace utk
{
  namespace geometry
  {
    template< typename T >
    std::pair< T, T > intersection( const ray<T,2u>& ray, const circle<T>& circle )
    { 
      // check for no intersection
    
      const T a = dot( ray.direction(), ray.direction() );
      const T b = T(2.) * sum( ray.direction() * ( ray.source() - circle.center() ) );
      const T c =   dot( circle.center(), circle.center() ) 
                  + dot( ray.source(), ray.source() ) 
                  - T(2.) * dot( ray.source(), circle.center() )
                  - sqr( circle.radius() );

      return solve_quadratic_equation(a,b,c);
    }

  }
}

