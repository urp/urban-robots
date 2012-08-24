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

//# include "utk/math/special_functions/solve_quadratic_equation.hpp"
# include "utk/geometry/ray/ray.hpp"

namespace utk
{
  namespace geometry
  {

	// find intersection of two 2d-rays
	template< typename T >
	typename ray<T,2>::point_type	intersection( const ray<T,2>& ray1, const ray<T,2>& ray2 )
	{
	  const typename ray<T,2>::point_type A1 = ray1.source();
	  const typename ray<T,2>::point_type B1 = ray1.target(); 
	  const typename ray<T,2>::point_type A2 = ray2.source();
	  const typename ray<T,2>::point_type B2 = ray2.target(); 

	  const T denom = ( A1[0] - B1[0] ) * ( A2[1] - B2[1] ) - ( A1[1] - B1[1] ) * ( A2[0] - B2[0] );
	  const T det1  = ( A1[0] * B1[1] - A1[1] * B1[0] );
	  const T det2  = ( A2[0] * B2[1] - A2[1] * B2[0] );

	  return typename ray<T,2>::point_type( ( A2 - B2 ) * det1 - ( A1 - B1 ) * det2 ) / denom; 
	}

  }
}

