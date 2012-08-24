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
  namespace geometry
  {

    // generalize to a shere??
    /* enbedd in higher dimensional spaces
    template<class T, size_t Dim>
    class circle
    {
      public:
    }*/


    template< typename T >
    class circle
    {
      public:
        typedef veca<T, 2>         center_t;
        typedef vecn<T, 2>&        center_reference;
        typedef const vecn<T, 2>&  const_center_reference;

        typedef T                  radius_t;
        typedef T&                 radius_reference;
        typedef const T&           const_radius_reference;
    
      private:

        center_t	m_center;
        radius_t	m_radius;
        
      public:
		
		circle( const_center_reference center, const_radius_reference radius )
        : m_center( center ), m_radius( radius )
		{   }

        circle(const_center_reference center, const_center_reference circle_point)
        : m_center( center ), m_radius( length(center - circle_point) )
        {   }

        center_reference		center()
        { return m_center; }

        const_center_reference  center()	const
		{ return m_center; }

        radius_reference        radius()
		{ return m_radius; }

        const_radius_reference  radius()	const
		{ return m_radius; }

  };

  template< typename T >
  std::ostream& 	operator<<(std::ostream& os,const circle<T>& c) 
  { os << "circle"
       << " center " << c.center() 
       << " radius " << c.radius();
	return os;
  }
