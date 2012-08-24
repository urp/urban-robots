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

# include <utility>

namespace utk
{
  namespace math
  {

    //clamp scalar to [min,max]
    template< typename T >
    typename std::enable_if< std::is_fundamental<T>::value
    						&&std::is_arithmetic<T>::value
							&&std::is_scalar<T>::value
							, T&
							>::type
    clamp( T& value, const T& min = T(0), const T& max = T(1) )
    { if( value < min ) return value = min; 
      if( value > max ) return value = max;
      return value;
    }

    //clamp scalar to [min,max]
    template< typename T>
    typename std::enable_if< std::is_fundamental<T>::value
    						&&std::is_arithmetic<T>::value
							&&std::is_scalar<T>::value
							, T&
							>::type
    clamp( T& value, const std::pair< T, T >& interval = std::pair< T, T >{ T(0), T(1) } )
    { 
      return clamp( value, interval );
    }

	//---| clamp to upper/lower boundary

	// template<T> clamp_xxx( T&, const T& ) prevents other specializations

	//-----| clamp_min
	
    //clamp scalar to lower boundary
	template< typename T>
    typename std::enable_if< std::is_fundamental<T>::value
    						&&std::is_arithmetic<T>::value
							&&std::is_scalar<T>::value
							, T&
							>::type
    clamp_min( T& val, const T& min = T(0) )
    { if(val<min) return val=min; 
      return val;
    }

    /*inline float&	clamp_min(float& val,const float& min=0.f)
    { if(val<min) return val=min; 
      return val;
    }
    inline double& clamp_min(double& val,const double& min=0.)
    { if(val<min) return val=min; 
      return val;
    }
    inline int&    clamp_min(int& val,const int& min=0)
    { if(val<min) return val=min; 
      return val;
    }
    inline unsigned int&	clamp_min(unsigned int& val,const unsigned int& min=0u)
    { if(val<min) return val=min; 
      return val;
    }*/

    //-----| clamp_max
  
    //clamp scalar to upper boundary
	template< typename T >
    typename std::enable_if< std::is_fundamental<T>::value
    						&&std::is_arithmetic<T>::value
							&&std::is_scalar<T>::value
							, T&
							>::type
    clamp_max( T& val,const T& max = T(1) )
    { if(val>max) return val=max; 
      return val;
    }
	/*
    inline float&			clamp_max(float& val,const float& max=1.f)
    { if(val>max) return val=max; 
      return val;
    }
    
    inline double&		clamp_max(double& val,const double& max=1.)
    { if(val>max) return val=max; 
      return val;
    }
    inline int&			clamp_max(int& val,const int& max=1)
    { if(val>max) return val=max; 
      return val;
    }
    inline unsigned int&	clamp_max(unsigned int& val,const unsigned int& max=1u)
    { if(val>max) return val=max; 
      return val;
    }*/
  }
}

