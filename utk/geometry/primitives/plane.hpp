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

#pragma once

namespace utk
{
  namespace geometry
  {
	
    template< typename T, size_t Dim = 3u >
    class plane
    {
        static_assert(Dim > 0, "Dimension must be greater than zero.");

      public:

        typedef veca<T, Dim+1>        value_type;
        typedef vecn<T, Dim+1>&       value_reference;
        typedef const vecn<T, Dim+1>& const_value_reference;

        typedef veca<T, Dim>          direction_type;
        typedef vecn<T, Dim>&         direction_reference;
        typedef const vecn<T, Dim>&   const_direction_reference;

        typedef vecn<T, Dim>          normal_reference;
     
        typedef T                     distance_type;
        typedef T&                    distance_reference;
        typedef const T&              const_distance_reference;

	  private:
    
		// normal and distance
        value_type            m_nd;

      public:
	
        plane(const_direction_reference norm, const_distance_reference dist) : m_nd(norm)				
        { m_nd[Dim] = dist; }
      
        plane() : m_nd(0)
        { m_nd[Dim-1] =	T(1); }
      
        // returns the outward pointing normal
        normal_reference      normal()	const	
        { return m_nd; }
					
        distance_reference    distance()					
        { return m_nd[Dim]; }
      
        const_distance_reference
							  distance()	const	
        { return m_nd[Dim]; }

        // the halfspace containing the normal is defined to be OUTSIDE
        classification_t      classify(const_direction_reference point)	const	
        { const distance_type d = dot( point , normal() );
	      if( d == distance() ) 
	        return ONTO;
	      if( d < distance() ) 
	        return INSIDE;
	      return OUTSIDE; 
	    }
			
        value_reference	    data()			                            const	
        { return m_nd; }

    // TODO: plane_from_spanning_vectors

  }
}
