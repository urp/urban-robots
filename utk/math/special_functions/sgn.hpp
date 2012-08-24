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

namespace utk
{
  namespace math
  {

    //sign function returns -1 for x<0, 0 for x=0 and 1 for x>0
    template <typename T> int sgn(T val) 
    { return (T(0) < val) - (val < T(0)); }
    
    /*old version with branches
    template<class T>  
    T			sgn(const T& x)
    { return x>T(0) ? T(1) : (x<T(0) ? T(-1) : T(0)); }*/
  }
}

