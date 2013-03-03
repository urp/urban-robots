//libutk - a utility library 
//Copyright (C) 2006-2010  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef	UTK_GEOMETRY_H
#define	UTK_GEOMETRY_H

#include	"math.h"
#include	"vecn.h"
#include	"ray.h"
#include	<cmath>
#include	<limits>
#include	<cassert>

#pragma GCC visibility push(default)

namespace utk
{ 



  



  


  template< typename T >
  std::pair< T, T > intersection_with_center_ray( const typename ray<T,2u>::value_type& direction, const circle<T>& twocircle )
  { 
    // TODO: check for no intersection

    //const T center2 = dot( twocircle.center(), twocircle.center() );
    
    const T a = dot( direction, direction );
    const T c = - sqr( twocircle.radius() );

    return solve_quadratic_equation( a, T(0.), c );
  }
    








}




#pragma GCC visibility pop

#endif

