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
# include <cassert>
# include <algorithm>

# include "utk/math/fixed_size/vector_interface.hpp"
# include "utk/math/fixed_size/vector_array.hpp"
# include "utk/math/fixed_size/vector_operators.hpp"

# include "utk/math/special_functions/sgn.hpp"
# include "utk/math/special_functions/clamp.hpp"

namespace utk
{
  namespace math
  {
  	namespace fixed_size
	{

	  //---| named element access
	  //x
      template<typename T,size_t Cnt>
      T&	        x(vector_interface<T,Cnt>& v)       { return v[0]; }

      template<typename T,size_t Cnt>
      const T&	x(const vector_interface<T,Cnt>& v) { return v[0]; }
	  //y
      template<typename T,size_t Cnt>
      T&	        y(vector_interface<T,Cnt>& v)       { return v[1]; }

      template<typename T,size_t Cnt>
      const T&	y(const vector_interface<T,Cnt>& v) { return v[1]; }
	  //z
      template<typename T,size_t Cnt>
      T&	        z(vector_interface<T,Cnt>& v)       { return v[2]; }

      template<typename T,size_t Cnt>
      const T&	z(const vector_interface<T,Cnt>& v) { return v[2]; }
	  //w
      template<typename T,size_t Cnt>
      T&	        w(vector_interface<T,Cnt>& v)       { return v[3]; }

      template<typename T,size_t Cnt>
      const T&	w(const vector_interface<T,Cnt>& v) { return v[3]; }
 	  //xy
      template<typename T,size_t Cnt>
      vector_interface<T,2>			xy(vector_interface<T,Cnt>& v)	     { return vector_interface<T,2>(v); }
      template<typename T,size_t Cnt>
      const vector_interface<T,2>	xy(const vector_interface<T,Cnt>& v) { return vector_interface<T,2>(v); }
	  //xyz
      template<typename T,size_t Cnt>
      vector_interface<T,3>			xyz(vector_interface<T,Cnt>& v)	{ return vector_interface<T,3>(v); }
      template<typename T,size_t Cnt>
      const vector_interface<T,3>	xyz(const vector_interface<T,Cnt>& v) { return vector_interface<T,3>(v); }

	  //---| min/max

      template<typename T,size_t Cnt>
      const T&	min(const vector_interface<T,Cnt>& v)
      {
        return *std::min_element(v.begin(),v.end());
      }

      template<typename T,size_t Cnt>
      const T&	max(const vector_interface<T,Cnt>& v)
      {
        return *std::max_element(v.begin(),v.end());
      }

	  //---| modifiers

      template<class T,size_t Cnt>
      vector_interface<T,Cnt>&	normalize( vector_interface<T,Cnt>& o )
	  {
        assert( length(o) > 0. );
	    return o /= length(o);
	  }

      template<class T,size_t Cnt>
      vector_interface<T,Cnt>&	clamp_min(vector_interface<T,Cnt>&	v,const T& min)
      {
        std::transform( v.begin(), v.end(), v.begin(), [&min](T& x){ return utk::math::clamp_min(x,min); });
        return v;
      }

      template<class T,size_t Cnt>
      vector_interface<T,Cnt>&	clamp_max(vector_interface<T,Cnt>&	v,const T& max)
      {
        std::transform( v.begin(), v.end(), v.begin(), [&max](T& x){ return utk::math::clamp_max(x,max); });
        return v;
      }

      template<class T,size_t Cnt>
      vector_interface<T,Cnt>&	clamp_min(vector_interface<T,Cnt>&	v,const vector_interface<T,Cnt>& min)
      {
        std::transform( v.begin(), v.end(), min.begin(), v.begin()
					  , [](T&	x,const T& xmin) { return utk::math::clamp_min( x, xmin ); }
					  );
        return v;
      }

      template<class T,size_t Cnt>
      vector_interface<T,Cnt>&	clamp_max(vector_interface<T,Cnt>&	v,const vector_interface<T,Cnt>& max)
      {
        std::transform( v.begin(), v.end(), max.begin(), v.begin()
		      , [](T& x,const T& xmax) { return utk::math::clamp_max( x, xmax ); }
		      );
        return v;
      }

	  //---| unary functions

	  //-----| per element

      inline double f(const float& v) {return v*v; }
      inline double f(const double& v) {return v*v; }

      template<class T,size_t Cnt>
      vector_array<T,Cnt>	abs(const vector_interface<T,Cnt>&	v)
      {
        vector_array<T,Cnt>	res;
        std::transform( v.begin(), v.end(), res.begin()
					  , std::function<T(const T&)>( [](const T& x){ return std::abs(x); } )
					  );
        return res;
      }

      template<class T,size_t Cnt>
      vector_array<T,Cnt>	sgn(const vector_interface<T,Cnt>&	v)
      {
        vector_array<T,Cnt> res;
        std::transform( v.begin(), v.end(), res.begin()
  					  , std::function<T(const T&)>( [](const T& x){ return utk::math::sgn(x); } )
					  );

        return res;
      }

      template<class T,size_t Cnt>
      vector_array<T,Cnt> floor(const vector_interface<T,Cnt>& v)
      {
        vector_array<T,Cnt>	res;
        std::transform( v.begin(), v.end(), res.begin()
   					  , std::function<T(const T&)>( [](const T& x){ return std::floor(x); } )
					  );

        return res;
      }

      template<class T,size_t Cnt>
      vector_array<T,Cnt>	ceil( const vector_interface<T,Cnt>& v )
      {
        vector_array<T,Cnt>	res;
        std::transform( v.begin(), v.end(), res.begin()
					  , std::function<T(const T&)>( [](const T& x){ return std::ceil(x); } )
					  );
        return res;
      }

      //-----| sum

      template<class T,size_t Cnt>
      T   sum(const vector_interface<T,Cnt>& v)
      { return std::accumulate( v.begin(), v.end(), T(0) ); }


	  //-----| shifted

      template< ptrdiff_t N, size_t ResCnt, typename T, size_t Cnt>
      vector_interface<T,ResCnt>	shifted(const vector_interface<T,Cnt>& v)
      {
        return vector_interface<T,ResCnt>(v.ptr()+N);
      }

	  //-----| flipped

      template<typename T,size_t Cnt>
      vector_array<T,Cnt>	flipped(const vector_interface<T,Cnt>& v)
      {
	    vector_array<T,Cnt>	res;
        std::reverse_copy( v.begin(), v.end(), res.begin() );
	    return res;
	  }

	  //---| binary functions

	  //-----| dot product

      template<class T,size_t Cnt>
      T   dot( const vector_interface<T,Cnt>& s, const vector_interface<T,Cnt>& b )
      {
        return std::inner_product( s.begin(), s.end(), b.begin(), T(0) );
      }

	  //-----| cross product

      template<class T>
      vector_array<T,3>	cross( const vector_interface<T,3>& a, const vector_interface<T,3>& b )
      {
        vector_array<T,3> res;
        res[0]= a[1] * b[2] - b[1] * a[2];
        res[1]= a[2] * b[0] - b[2] * a[0];
        res[2]= a[0] * b[1] - b[0] * a[1];
        return res;
      }

      template<class T>
      vector_array<T,3>	cross3(const vector_interface<T,3>& a,const vector_interface<T,3>& b,const vector_interface<T,3>& c)
      { return b*dot(a,c)-c*dot(a,b); }

	  //---| distance functions

      //euklidian norm
      template<class T,size_t Cnt>
      T	l2norm( const vector_interface<T,Cnt>& v )
      {
        return std::sqrt( dot(v,v) );
      }

      template<class T,size_t Cnt>
      T   length( const vector_interface<T,Cnt>& v )
      {
        return l2norm(v);
      }

	  template< typename T >
      typename std::enable_if< std::is_fundamental<T>::value
    						  &&std::is_arithmetic<T>::value
							  &&std::is_scalar<T>::value
							  , T&
							  >::type
      length( const vector_interface<float,2>& v )
      { return std::hypot( x(v), y(v) ); }

      template<class T, size_t Dim>
      T distance( const vector_interface<T,Dim>& s, const vector_interface<T,Dim>& b )
      { return length( b - s ); }

      // normalized vector copy
      template<class T,size_t Cnt>
      vector_array<T,Cnt>	normal(const vector_interface<T,Cnt>& o)
      {
        vector_array<T,Cnt> res(o);
        return normalize(res);
      }

	} // of fixed_size::
  } // of math::
} // of utk::
