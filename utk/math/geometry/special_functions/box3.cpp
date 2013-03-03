/*  bla.cpp - Copyright Peter Urban 2009

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

# include <cassert>
# include "utk/math/vecn/vecn.hpp"
# include "utk/geometry/box/box3.hpp"

using namespace utk::math;

vecn3s	utk::geometry::box3_vertex(unsigned int i)
{ static size_t bv[24]	=	{0,0,0,1,0,0,0,1,0,1,1,0,0,0,1,1,0,1,0,1,1,1,1,1};
  switch(i) // maybe static storage of the coords is better
  { case 0: return vecn3s(bv);
    case 1: return vecn3s(bv+3);
    case 2: return vecn3s(bv+6);
    case 3: return vecn3s(bv+9);
    case 4: return vecn3s(bv+12);
    case 5: return vecn3s(bv+15);
    case 6: return vecn3s(bv+18);
    case 7: return vecn3s(bv+21);
    default: assert(0);
  } 
}

vec3i	utk::geometry::box3_nb6(unsigned int i)
{ vec3i	bp;
  assert(i<6);	
  bp[i/2]=i%2?1:-1;	  
  return bp;
}

vec3i	utk::geometry::box3_nb26(unsigned int i)
{ veca<int,3> bp;
  assert(i<26);	
  if(i>=13) ++i;	  
  bp.z()=i/9-1;
  bp.y()=(i-(bp.z()+1)*9)/3-1;
  bp.x()=i-(bp.z()+1)*9-(bp.y()+1)*3-1;
  return bp;
}



vec3s	utk::geometry::box_vertex_nb(unsigned int vertex)		
{ return vec3s(vertex^1,vertex^2,vertex^4); }

