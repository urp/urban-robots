/***************************************************************************
 *            surface.h
 *
 *  Wed Aug  5 23:46:44 2009
 *  Copyright  2009  Peter Urban
 *  <s9peurba@stud.uni-saarland.de>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */


# pragma once

# include "common.hpp"
# include "surface/tri_surface/tri_surface.hpp"

namespace flat
{

  struct distance_function
  {
    typedef boost::numeric::ublas::symmetric_matrix< distance_t, boost::numeric::ublas::upper > distance_matrix_type;

    typedef enum { NONE = 0, NEIGHBORS = 1, ALL = 2 } neighborhood_type;
    typedef int neighborhood_mask_type;

    neighborhood_mask_type  neighborhood;

    distance_matrix_type distance_matrix;

    distance_function( const distance_function& d ) : neighborhood( d.neighborhood ), distance_matrix( d.distance_matrix ) { }

    //TODO move construction
    //TODO: distance_function( distance_function&& d ) : neighborhood( d.neighborhood ), distance_matrix( d.distance_matrix ) { }

    distance_function() : neighborhood( NONE )  {   }

    void compute( const std::shared_ptr<TriSurface>&, neighborhood_mask_type );

    distance_matrix_type::const_reference operator() ( TriSurface::vertex_descriptor a, TriSurface::vertex_descriptor b )   const
    {
      return distance_matrix(a,b);
    }

    void set_distances( const distance_matrix_type& matrix, neighborhood_mask_type neighbors )
    { distance_matrix = matrix;
      neighborhood = neighbors;
    }

    private:
      void compute_all_to_all( const std::shared_ptr< TriSurface >& );
      void compute_all_to_neighbors( const std::shared_ptr< TriSurface >& );
  };

   inline std::ostream&   operator<<( std::ostream& os, distance_function const& distances  )
   {
     os << "nb " << distances.neighborhood << ' ' << distances.distance_matrix;
     return os;
   }

   inline std::istream&   operator>>( std::istream& is, distance_function& distances  )
   {
     std::string token;
     is >> token;
     if( token != "nb" )
       std::cerr << "ERROR in distance function input operator - "
                 << "expected token \"nb\" at the beginning of the stream." << std::endl;
     is >> distances.neighborhood >> distances.distance_matrix;
     return is;
   }

}
