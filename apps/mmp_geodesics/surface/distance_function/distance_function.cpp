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

# include "surface/distance_function/distance_function.hpp"
# include "mmp/geodesics.hpp"

using namespace flat;


void distance_function::compute_all_to_all( const std::shared_ptr< TriSurface >& surface )
{
  if( neighborhood & ALL ) return;

  //mmp::vertex_pair_check( surface, 1e-4 );

  for( TriSurface::vertex_descriptor source = 0; source < surface->num_vertices(); source++ )
  {
    mmp::Geodesics gi( *surface, source );
    // TODO: prevent propagation to vertices which allready have distance information (j <= i )
    //       ??? by removing (boundary) vertices

    gi.propagate_paths();

    for( TriSurface::vertex_descriptor query = source + 1; query < surface->num_vertices(); query++)
      distance_matrix( source, query ) = gi.query_distance( query );
  }

  neighborhood |= ALL;
}

void distance_function::compute_all_to_neighbors( const std::shared_ptr< TriSurface >& surface )
{
  if( neighborhood & NEIGHBORS ) return;

  const std::vector< TriSurface::vertex_pair >   pairs( std::move( surface->neighbors() ) );

  std::for_each( pairs.begin(), pairs.end()
               , [&]( const TriSurface::vertex_pair& pair )
                 { distance_matrix( pair.first, pair.second ) = surface->distance( pair.first, pair.second ); }
               );
  neighborhood |= NEIGHBORS;
}


void distance_function::compute( const std::shared_ptr< TriSurface >& surface, neighborhood_mask_type nb )
{
  std::clog << "flat::TriSurface::compute_distances"
            << std::endl;

  std::time_t start_time = std::clock();

  if( distance_matrix.size1() != surface->num_vertices() )
    distance_matrix.resize( surface->num_vertices() );

  if( nb & NEIGHBORS ) compute_all_to_neighbors( surface );
  else if( nb & ALL )  compute_all_to_all( surface );
  else assert( false );

  std::time_t end_time = std::clock();

  std::clog << "flat::TriSurface::compute_distances\t|"
            << "complete - after " << ( (end_time - start_time)/double(CLOCKS_PER_SEC) )
            << std::endl;
}
