/*  comparison.hpp - Copyright Peter Urban 2009-2013

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

# include "utk/math/fixed_size/interface/vector/interface.hpp"
# include "utk/math/fixed_size/interface/vector/array.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {
	namespace vector
	{

	  //---| comparison operators

	  //-----|vector-vector
	  //-----|returns vector of bools with per element results

	  template<typename T,size_t Cnt>
	  array<bool,Cnt>	operator==( const interface<T,Cnt>& a, const interface<T,Cnt>& b )
	  {
	    array<bool,Cnt> r;
	    std::transform( a.begin(), a.end(), b.begin(), r.begin(), std::equal_to<T>() );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<bool,Cnt>	operator!=( const interface<T,Cnt>& a, const interface<T,Cnt>& b )
	  {
	    array<bool,Cnt> r;
	    std::transform( a.begin(), a.end(), b.begin(), r.begin(), std::not_equal_to<T>() );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<bool,Cnt>	operator< ( const interface<T,Cnt>& a, const interface<T,Cnt>& b )
	  {
	    array<bool,Cnt> r;
	    std::transform( a.begin(), a.end(), b.begin(), r.begin(), std::less<T>() );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<bool,Cnt>	operator<=( const interface<T,Cnt>& a, const interface<T,Cnt>& b )
	  {
	    array<bool,Cnt> r;
	    std::transform( a.begin(), a.end(), b.begin(), r.begin(), std::less_equal<T>() );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<bool,Cnt>	operator> ( const interface<T,Cnt>& a, const interface<T,Cnt>& b )
	  {
	    array<bool,Cnt> r;
	    std::transform( a.begin(), a.end(), b.begin(), r.begin(), std::greater<T>() );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<bool,Cnt>	operator>=( const interface<T,Cnt>& a, const interface<T,Cnt>& b )
	  {
	    array<bool,Cnt> r;
	    std::transform( a.begin(), a.end(), b.begin(), r.begin(), std::greater_equal<T>() );
	    return r;
	  }

	  //-----| vector-scalar
	  //-----| returns true if and only if all elements are compare (to true) with scalar s

	  template<typename T,size_t Cnt>
	  bool    operator==( const interface<T,Cnt>& v, const T& s )
	  {
	    return std::all_of( v.begin(), v.end(), std::bind2nd( std::equal_to<T>(), s) );
	  }

	  template<typename T,size_t Cnt>
	  bool    operator!=( const interface<T,Cnt>& v, const T& s )
	  {
	    return std::all_of( v.begin(), v.end(), std::bind2nd( std::not_equal_to<T>(), s) );
	  }

	  template<typename T,size_t Cnt>
	  bool	operator< ( const interface<T,Cnt>& v, const T& s )
	  {
	    return std::all_of( v.begin(), v.end(), std::bind2nd( std::less<T>(), s) );
	  }

	  template<typename T,size_t Cnt>
	  bool	operator<=( const interface<T,Cnt>& v, const T& s )
	  {
	    return std::all_of( v.begin(), v.end(), std::bind2nd( std::less_equal<T>(), s) );
	  }

	  template<typename T,size_t Cnt>
	  bool	operator> ( const interface<T,Cnt>& v, const T& s )
	  {
	    return std::all_of( v.begin(), v.end(), std::bind2nd( std::greater<T>(), s) );
	  }

	  template<typename T,size_t Cnt>
	  bool	operator>= ( const interface<T,Cnt>& v, const T& s )
	  {
	    return std::all_of( v.begin(), v.end(), std::bind2nd(std::greater_equal<T>(), s) );
	  }

	} // of vector::
      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
