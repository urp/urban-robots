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

# include <vector>
# include "utk/geometry/primitives/point.hpp"
# include "utk/geometry/primitives/plane.hpp"
# include "utk/geometry/primitives/box.hpp"

namespace utk
{
  namespace geometry
  {

    template<class T>
    std::vector<point<T,3>> intersection(const plane<T>& plane,const box<T>& box);

  }
}

//______________
//Implementation
////////////////

# include "utk/geometry/special_functions/box3.hpp"

template<class T>
std::vector< utk::geometry::point<T,3> > 
utk::geometry::intersection(const plane<T>& plane,const box<T>& b)
{ 
  std::vector< veca<T,3> >	ispnts(6); //result
  std::vector< uint8_t >	inpnts(6); //inside plane points
  veca<uint8_t,3>	        nbpnts(6); //neighbours
  
  for(uint8_t i=0;i<8;i++)
    if( plane.classify( b.vertex(i) ) == INSIDE )
      inpnts.push_back(i);
  // ????
  for( std::vector<uint8_t>::iterator it = inpnts.begin(); it != inpnts.end(); it++ )  
  { nbpnts = box3_vertex_nb( *it );        
    for( uint8_t i=0; i<3; i++ )
      if( std::find( inpnts.begin(), inpnts.end(), nbpnts[i] ) == inpnts.end() )
      { ray<T> r( b.vertex(*it), b.vertex(nbpnts[i]) );
        r.direction() -= r.source();
	    if( dot( r, plane.normal() ) )
          ispnts.push_back( ray_plane_is( r, plane ) );
      }  
  }
  return ispnts;
}

