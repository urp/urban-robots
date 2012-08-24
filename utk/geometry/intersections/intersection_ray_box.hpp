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

# include "utk/geometry/ray/ray.hpp"

namespace utk
{
  namespace geometry
  {

	//ray-box intersection test (centered box with dimensions 2*dist )
    template<class T>	
    std::pair< typename ray<T>::parameter_type, typename ray<T>::parameter_type >	
	ray_box_is(const ray<T>&,const box<T>&);

  }
}


//--------------
//IMPLEMENTATION
////////////////

# include <algorithm>

template<class T>	
std::pair< typename utk::geometry::ray<T>::parameter_type, typename utk::geometry::ray<T>::parameter_type >
utk::geometry::intersection(const ray<T>& r,const box<T>& b)	
{
  size_t k=0;

  typename ray<T>::parameter_type	t[2];
  typename ray<T>::parameter_type	t1, t2, tu, tv;
 
  for(size_t i=0;i<3 && k<=1;i++)
  {
	t1 = ( b.get_box_min[i] - r.source()[i] )/r.direction()[i],
    t2 = ( b.get_box_max[i] - r.source()[i] )/r.direction()[i];

    size_t 	u= (i+1) % 3,	
 			v= (i+2) % 3;
    if(t1>=0)	
    { tu = r.source()[u] + t1 * r.direction()[u];
      tv = r.source()[v] + t1 * r.direction()[v];	    
      if(   tu >= b.get_box_min()[u] && tu <= b.get_box_max()[u] 
         && tv >= b.get_box_min()[v] && tv >= b.get_box_min()[v] ) t[k++]=t1; 
    }
    if(t2>=0)
    { tu = r.source()[u] + t2 * r.direction()[u];
      tv = r.source()[v] + t2 * r.direction()[v];
      if(   tu >= b.get_box_min()[u] && tu <= b.get_box_max()[u]
         && tv >= b.get_box_min()[v] && tv >= b.get_box_min()[v] ) t[k++]=t2; 
    }
  } 

  //sort intersections along the ray
  if(k==2) 
  { if(t[0]>t[1]) std::swap(t[0],t[1])
    return std::make_pair(t[0],t[1]);
  }

  // only one intersection is strange 
  assert(k==0;)

  // no intersection - return (NaN,NaN)
  return { std::numeric_limits< ray<T>::parameter_type >::quiet_NaN, ray<T>::parameter_type >::quiet_NaN };
}
