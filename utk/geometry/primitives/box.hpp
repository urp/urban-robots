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

# include <limits>
# include "utk/math/vecn/vecn.hpp"
# include "utk/math/special_functions/clamp.hpp"
# include "utk/math/special_functions/ipow.hpp"

using namespace utk:math;

namespace utk
{
  namespace geometry
  {

    template< typename T, size_t Dim = 3 >	
    class box
    {
	  private:

        veca<T,Dim>	m_min,
	    veca<T,Dim> m_max;

      public:

    	box() : m_min(std::numeric_limits<T>::min()),
                m_max(std::numeric_limits<T>::max())	
        { 	}

        box(const vecn<T,Dim>& min,const vecn<T,Dim>& max)
        : m_min( min ), m_max( max )			
        {	}
  
        box(const box<T,Dim>& o)
        : m_min( o.min() ), m_max( o.max() )	
		{	}

        void	extend( const vecn<T,Dim>& p )
        { 
          clamp_max( m_min, p );
          clamp_min( m_max, p );
		}

        void	extend( const box<T,Dim>& b )
        { 
          extend( b.min() );
          extend( b.max() );
		}
      
        veca<T,Dim>	vertex( size_t i )  const
        { 
          assert( i < (integer_power<2,Dim>::value) );

          veca<T,Dim> result;
          typename veca<T,Dim>::iterator rit = result.begin();
          typename veca<T,Dim>::const_iterator minit = min().begin();
          typename veca<T,Dim>::const_iterator maxit = max().begin();
          for( size_t dsize = 1u; dsize < integer_power<2,Dim>::value; dsize *= 2u, ++minit, ++maxit )
            *rit++ = i & dsize ? *minit : *maxit;
          return result;
		}
			
      	veca< bool, integer_power<2,Dim>::value >	    
        classify(const utk::plane<T>& plane)	
        { 
          veca< bool, integer_power<2,Dim>::value >	clssfd;
		  for( utk::size_t i = 0; i < clssfd.size(); i++ )
			clssfd[i] = plane.classify( vertex(i) );
		  return clssfd;
		}

        vecn<T,Dim>&        min()
        { return m_min; }

      
        const vecn<T,Dim>&  min()   const	
        { return m_min; }

        vecn<T,Dim>&        max()
        { return m_max; }

        const vecn<T,Dim>&  max()   const
        { return m_max; }

        veca<T,Dim>	extent()    const	
        { return max() - min();	}
      
        veca<T,Dim> center()    const  	
        { return ( min() + max() ) * T(.5); }

    };

    template< typename T, size_t Dim >
    std::ostream& 	operator<<(std::ostream& os,const box<T,Dim>& b) 
    { os << "box"
         << " min " << b.min() 
         << " max " << b.max();
  	  return os;
    }

  }
}
