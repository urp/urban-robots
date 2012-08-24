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

# define DBG_UTK_MATH_SOLVE_QUADRATIC_EQUATION

# include <pair>
# include "utk/math/close.hpp"

# ifdef DBG_UTK_MATH_SOLVE_QUADRATIC_EQUATION
#   include <iostream>
#   include <iomanip>  
# endif


namespace utk
{
  namespace math
  {

    // solve the quadratic equation with coefficients a,b,c
	// for positive discriminants, two solutions are returned
    // for discriminants close to zero, two identical solutions are returned
	// for negative discriminants (no solution) (NaN,NaN) is returned
    template<typename T>
    std::pair<T,T> solve_quadratic_equation(const T& a, const T& b, const T& c)
    { 
      const T discriminant = b*b - T(4.) * a * c;
      # if defined DBG_UTK_MATH_SOLVE_QUADRATIC_EQUATION
      std::clog << "utk::solve_quadratic_equation\t\t|"
                << " a " << a << " b " << b << " c " << c
	    		<< " discriminant " << discriminant
                << std::endl;
      # endif
      //two solution	
      if( discriminant > T(0.) )
      { const T q = - T(.5) * ( b + std::copysign( std::sqrt(discriminant), b ) );
        return std::make_pair( q/a, c/q );
      }

      //single solution (double root)
      if( close_to_zero(discriminant) )
      { 
        const T q = - T(.5) * b;
                       //           v  ?????  v
	    const T r = fabs(a) > fabs(q) ? q/a : c/q;
        # if defined DBG_UTK_MATH_SOLVE_QUADRATIC_EQUATION
        if( discriminant < T(0.) )
          std::clog << "\t\t\t\t\t|" << " WARNING - negative discriminant " << discriminant  << std::endl;
        std::clog << "\t\t\t\t\t|" << "double root " << r
                  << " from (" << (q/a) << "," << (c/q) << ")"
                  << std::endl;
        # endif
	    return std::make_pair(r,r);
      }

      //no solution
      # if defined DBG_UTK_MATH_SOLVE_QUADRATIC_EQUATION
      std::clog << "\t\t\t\t\t|" << "no solution - returning(NaN,NaN)" << std::endl;
      # endif
      return std::make_pair(  std::numeric_limits<T>::quiet_NaN()
  	    				    , std::numeric_limits<T>::quiet_NaN() );
    }
  }
}
