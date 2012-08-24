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

# include <cmath>
# include "utk/math/vecn/vecn.hpp"

namespace utk
{
  namespace geometry
  {

	template<class T>
    T	project_to_sphere(const T& r,const vecn<T,2>& pos);

  }
}



/--------------
/IMPLEMENTATION
///////////////

// the code of the function below is based on the sgi trackball example under the following license: 
/* (c) Copyright 1993, 1994, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 */
 
//! orthogonal project an x,y pair onto a sphere of radius r OR a hyperbolic sheet
//! if we are away from the center of the sphere.
template<class T>
T     utk::geometry::project_to_sphere(const T& r,const utk::math::vecn<T,2>& pos)
{
  const T d = pos.length();
  
  if (d < r * 0.70710678118654752440) 
  { //Inside sphere
    //std::cerr<<"utk::project_to_sphere\t|inside sphere"<<std::endl;
    return std::sqrt(r*r - d*d);
  }else 
  { //On hyperbola
    //std::cerr<<"utk::project_to_sphere\t|on hyperbolia"<<std::endl;
    const T t = r / 1.41421356237309504880;
    return t*t/d;
  }
}
