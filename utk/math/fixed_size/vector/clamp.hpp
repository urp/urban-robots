/*  functions.h - Copyright Peter Urban 2012

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

# include <algorithm>

# include "utk/math/special_functions/clamp.hpp"

# include "utk/math/fixed_size/vector/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace vector
      {
	//---| clamp to scalar-----------------------------------------/

	//-----| clamp_min

	template<class T,size_t Size>
	interface< T, Size >& clamp_min( interface< T, Size >& v, const T& min )
	{
	  std::transform( v.begin(), v.end(), v.begin(), [&min]( T& x ){ return utk::math::clamp_min( x, min ); });
	  return v;
	}

	//-----| clamp_max

	template<class T,size_t Size>
	interface< T, Size >& clamp_max( interface< T, Size >& v, const T& max )
	{
	  std::transform( v.begin(), v.end(), v.begin(), [&max]( T& x ){ return utk::math::clamp_max( x, max ); });
	  return v;
	}

	//---| clamp to vector-----------------------------------------/

	//-----| clamp_min

	template<class T,size_t Size>
	interface< T, Size >& clamp_min( interface< T, Size >& v, const interface< T, Size >& min )
	{
	  std::transform( v.begin(), v.end(), min.begin(), v.begin()
			, []( T& x,const T& xmin ) { return utk::math::clamp_min( x, xmin ); }
			);
	  return v;
	}

	//-----| clamp_max

	template<class T,size_t Size>
	interface< T, Size >& clamp_max( interface< T, Size >& v, const interface< T, Size >& max )
	{
	  std::transform( v.begin(), v.end(), max.begin(), v.begin()
			, []( T& x, const T& xmax ) { return utk::math::clamp_max( x, xmax ); }
			);
	  return v;
	}

      } // of vector::
    } // of fixed_size::
  } // of math::
} // of utk::
