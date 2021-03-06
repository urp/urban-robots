/*  arithmetic.hpp - Copyright Peter Urban 2009-2013

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

# include "utk/math/fixed_size/interface/vector/array.hpp"

# include "utk/io/io.hpp"

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

	  //---| arithmetic operators
	  //---| perform arithmetic operations on a per element basis

	  //-----| vector-vector

	  template<typename T,size_t Cnt>
	  array<T,Cnt>	operator- (const interface<T,Cnt>& v)
	  {
	    array<T,Cnt> res(v);
	    return res *= -T(1);
	  }

	  template<typename T,size_t Cnt>
	  array<T,Cnt>	operator+ ( const interface<T,Cnt>& a, const interface<T,Cnt>& b )
	  {
	    array<T,Cnt> r;
	    std::transform( a.begin(), a.end(), b.begin(), r.begin(), std::plus<T>() );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<T,Cnt>	operator- ( const interface<T,Cnt>& a, const interface<T,Cnt>& b )
	  {
	    array<T,Cnt> r;
	    std::transform( a.begin(), a.end(), b.begin(), r.begin(), std::minus<T>() );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<T,Cnt>	operator* ( const interface<T,Cnt>& a, const interface<T,Cnt>& b )
	  {
	    array<T,Cnt> r;
	    std::transform( a.begin(), a.end(), b.begin(), r.begin(), std::multiplies<T>() );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<T,Cnt>	operator/ ( const interface<T,Cnt>& a, const interface<T,Cnt>& b )
	  {
	    array<T,Cnt> r;
	    std::transform( a.begin(), a.end(), b.begin(), r.begin(), std::divides<T>() );
	    return r;
	  }

	  //-----| vector-scalar

	  template<typename T,size_t Cnt>
	  array<T,Cnt>	operator+ ( const interface<T,Cnt>& a, const T& s )
	  {
	    array<T,Cnt> r;
	    std::transform( a.begin(), a.end(), r.begin(), bind2nd( std::plus<T>(), s ) );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<T,Cnt>	operator- ( const interface<T,Cnt>& a, const T& s )
	  {
	    array<T,Cnt> r;
	    std::transform( a.begin(), a.end(), r.begin(), bind2nd( std::minus<T>(), s ) );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<T,Cnt>	operator* ( const interface<T,Cnt>& a, const T& s )
	  {
	    array<T,Cnt> r;
	    std::transform( a.begin(), a.end(), r.begin(), bind2nd( std::multiplies<T>(), s ) );
	    return r;
	  }

	  template<typename T,size_t Cnt>
	  array<T,Cnt>	operator/ ( const interface<T,Cnt>& a, const T& s )
	  {
	    array<T,Cnt> r;
	    std::transform( a.begin(), a.end(), r.begin(), bind2nd( std::divides<T>(), s ) );
	    return r;
	  }

	  //---arithmetic assignment-operators

	  //-----| vector-vector

	  template<typename T,size_t Cnt>
	  interface<T,Cnt>&	operator+= ( interface<T,Cnt>& a, const interface<T,Cnt>& b)
	  {
	    std::transform( a.begin(), a.end(), b.begin(), a.begin(), std::plus<T>() );
	    return a;
	  }

	  template<typename T,size_t Cnt>
	  interface<T,Cnt>&	operator-= ( interface<T,Cnt>& a, const interface<T,Cnt>& b)
	  {
	    std::transform( a.begin(), a.end(), b.begin(), a.begin(), std::minus<T>() );
	    return a;
	  }

	  template<typename T,size_t Cnt>
	  interface<T,Cnt>&    operator*= ( interface<T,Cnt>& a, const interface<T,Cnt>& b)
	  {
	    std::transform( a.begin(), a.end(), b.begin(), a.begin(), std::multiplies<T>() );
	    return a;
	  }

	  template<typename T,size_t Cnt>
	  interface<T,Cnt>&	operator/= ( interface<T,Cnt>& a, const interface<T,Cnt>& b)
	  {
	    std::transform( a.begin(), a.end(), b.begin(), a.begin(), std::divides<T>() );
	    return a;
	  }

	  //-----| vector-scalar

	  template<typename T,size_t Cnt>
	  interface<T,Cnt>&	operator+= ( interface<T,Cnt>& v, const T& s)
	  {
	    std::transform( v.begin(), v.end(), v.begin(), std::bind2nd( std::plus<T>(), s ) );
	    return v;
	  }

	  template<typename T,size_t Cnt>
	  interface<T,Cnt>&	operator-= ( interface<T,Cnt>& v, const T& s)
	  {
	    std::transform( v.begin(), v.end(), v.begin(), std::bind2nd( std::minus<T>(), s ) );
	    return v;
	  }

	  template<typename T,size_t Cnt>
	  interface<T,Cnt>&	operator*= ( interface<T,Cnt>& v, const T& s)
	  {
	    std::transform( v.begin(), v.end(), v.begin(), std::bind2nd( std::multiplies<T>(), s ) );
	    return v;
	  }

	  template<typename T,size_t Cnt>
	  interface<T,Cnt>&	operator/= ( interface<T,Cnt>& v, const T& s)
	  {
	    std::transform( v.begin(), v.end(), v.begin(), std::bind2nd( std::divides<T>(), s ) );
	    return v;
	  }

	} // of vector::
      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
