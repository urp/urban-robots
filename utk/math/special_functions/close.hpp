/*  close.hpp - Copyright Peter Urban 2009-2013

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

# include <cassert>
# include <cmath>

// utk::close_ulps uses boost::math::float_distance
# include <boost/math/special_functions/next.hpp>

namespace utk
{
  namespace math
  {
    //TODO: include comparison type in template arguiment (boost???)
    template<class T>
    bool close_ulps(const T& a, const T& b, const int& maxulps = 10)
    { assert( maxulps > 0 );
      return std::abs( boost::math::float_distance(a,b) ) <= maxulps;
    }

    template<class T>
    bool close_rel(const T& a, const T& b, const T& reltol)
    { assert( reltol > T(0.) );
      return std::abs( a - b ) <= reltol * std::max( std::abs(a), std::abs(b) );
    }

    template<class T>
    bool close_to_zero(const T& a, const T& tol = 1e-5)
    { assert( tol > T(0.) );
      return std::abs(a) <= tol;
    }

    template<typename T>
    struct close
    {
      bool operator()(const T& a, const T& b)	const
      { return close_ulps(a,b); }
    };

    template<typename T>
    struct greater_close
    {
      bool operator()(const T& a, const T& b)	const
      { return a>b || close_ulps(a,b); }
    };

    template<typename T>
    struct less_close
    {
      bool operator()(const T& a, const T& b)	const
      { return a<b || close_ulps(a,b); }
    };

    template<typename T>
    struct less_not_close
    {
      bool operator()(const T& a, const T& b)	const
      { return a<b || !close_ulps(a,b); }
    };
  }
}
