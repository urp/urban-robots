//  Wed Aug  5 23:46:44 2009
//  Copyright  2009  Peter Urban
//  <s9peurba@stud.uni-saarland.de>

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA

# include "surface/tri_surface/tri_surface.hpp"

# include <boost/accumulators/accumulators.hpp>
# include <boost/accumulators/statistics/min.hpp>
# include <boost/accumulators/statistics/max.hpp>
# include <boost/accumulators/statistics/sum.hpp>

using namespace flat;


TriSurface::TriSurface( const vertices_size_type  num_vertices
                      , const std::string&        name )
: PointCloud( num_vertices, name )
{
  std::clog << "flat::TriSurface::TriSurface\t|"
            << " num vertices (" << num_vertices << ')'
            << std::endl;
}

std::vector< TriSurface::vertex_pair > TriSurface::neighbors() const
{
  std::vector< vertex_pair > neighbor_pairs;
  neighbor_pairs.reserve( 3 * num_vertices() );
  for( vertex_descriptor a = 0; a < num_vertices(); ++a )
  {
    const std::vector< vertex_descriptor > local_neighbors( std::move( neighbors( a ) ) );
    std::for_each( local_neighbors.begin(), local_neighbors.end()
                 , [&] ( const vertex_descriptor b ) { assert( a < this->num_vertices() );
                                                       assert( b < this->num_vertices() );
                                                       if( a < b ) neighbor_pairs.push_back( { a, b } );
                                                     }
                 );
  }

  std::clog << "flat::TriSurface::neighbors\t| complete - " <<  neighbor_pairs.size() << " springs created" << std::endl;

  return neighbor_pairs;
}
