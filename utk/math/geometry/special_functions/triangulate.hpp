/*  bla.h - Copyright Peter Urban 2009

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

# include <cmath>
# include <pair>
# include "utk/math/special_functions/sqr.hpp"

namespace utk
{
  namespace geometry
  {
    template< typename T >
    std::pair< T, T > triangulate( const T& base_length, const T& left_distance, const T& right_distance)
    { 
      assert( base_length > T(0) );
      assert( left_distance >= T(0) );
      assert( right_distance >= T(0) );

      if(  left_distance == T(0) ) return std::make_pair( T(0) , T(0) );
      if( right_distance == T(0) ) return std::make_pair( base_length , T(0) );

      const T sqr_left_distance  = sqr(left_distance);
    
      std::pair< T, T > p( T(.5) * ( ( sqr_left_distance + sqr(base_length) ) - sqr(right_distance) ) / base_length, T(0) );

      p.second = std::sqrt( std::max( T(0), sqr_left_distance - sqr(p.first) ) );

      return p;
    }
  }
}
