//           quad-surface.cpp
//  Sun Oct 11 14:13:29 2009
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

# include "surface/quad_surface/quad_surface.hpp"

# include <cairomm/context.h>
# include <cairomm/surface.h>

using namespace flat;

std::vector< TriSurface::vertex_pair > QuadSurface::neighbors() const
{
  const size_t& m  = std::get<0>( vertex_field_size );
  const size_t& n  = std::get<1>( vertex_field_size );
  assert( m > 1 && n > 1 );

  const size_t num_pairs = ( /*interior*/ 8 * (m-2)*(n-2) + /*boundaries*/ 5 * (2*m+2*n-8)  + /*corners*/ 3 * 4 ) / 2;

  std::clog<<"flat::QuadSurface::neighbors\t|creating " << num_pairs << " pairs..." << std::endl;

  // TODO optimize

  std::vector< vertex_pair > pairs;
  pairs.reserve( num_pairs );

  // TODO: remove "vertex_pair" from initializer lists
  for( vertex_descriptor upper = 0; upper < m-1; ++upper )
  { // upper
    const vertex_pair nbs[] = { vertex_pair{upper, upper + 1} };
    pairs.insert( pairs.end(), nbs, nbs + sizeof(nbs)/sizeof(*nbs) );
  }

  for( vertex_descriptor j = 1 ; j < n; ++j )
  {
    { // left
      const vertex_descriptor v = j * m;
      const vertex_pair nbs[]   = { vertex_pair{ v, v - m }, vertex_pair{ v, v + 1 - m }, vertex_pair{ v, v + 1 } };
      pairs.insert( pairs.end(), nbs, nbs + sizeof(nbs)/sizeof(*nbs) );
    }
    for( vertex_descriptor i = 1; i < m-1; ++i )
    { // interior
      const vertex_descriptor v = i + j * m;
      const vertex_pair nbs[]   = { vertex_pair{ v, v - 1 - m }, vertex_pair{ v, v - m }, vertex_pair{ v, v + 1 - m }, vertex_pair{ v, v + 1 } };
      pairs.insert( pairs.end(), nbs, nbs + sizeof(nbs)/sizeof(*nbs) );
    }
    { // right
      const vertex_descriptor v = j * m + m -1 ;
      const vertex_pair nbs[]   = { vertex_pair{ v, v - 1 - m }, vertex_pair{ v, v - m } };
      pairs.insert( pairs.end(), nbs, nbs + sizeof(nbs)/sizeof(*nbs) );
    }

  }

  assert( pairs.size() == num_pairs );

  std::clog << "flat::QuadSurface::neighbors\t|completed" << std::endl;

  return std::move( pairs );
}
