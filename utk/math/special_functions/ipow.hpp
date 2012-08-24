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

    //power with positive integer exponent
    template<class T,size_t Exp>
    const T&		ipow(const T& base)
    { T res=T(1);
      for(size_t i=0;i<Exp;i++) res*=base;
      return res;  
    };
  
    //power with positive integer exponent
    template<class T>
    T			ipow(T base,size_t exp)
    { T res=T(1);
      for(size_t i=0;i<exp;i++) res*=base;
      return res;  
    }

    template<int Base,size_t Exponent>
    struct integer_power
    {
      enum { value = Base * integer_power<Base,Exponent-1>::value };  
    };

    template<int Base>
    struct integer_power<Base,0>
    {
      enum { value = 1 };  
    };

  }
}

