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

# include "surface/point_cloud/point_cloud.hpp"

# include <boost/accumulators/accumulators.hpp>
# include <boost/accumulators/statistics/min.hpp>
# include <boost/accumulators/statistics/max.hpp>

using namespace flat;

void	flat::PointCloud::comp_min_max_xy()	const
{
  using namespace boost::accumulators;

  accumulator_set< coord_t, features< tag::min, tag::max > > xacc,yacc;

  for( auto vertex_it = vertex_handles(); vertex_it.first != vertex_it.second; vertex_it.first++ )
  {
    xacc( vertex_it.first->location()[0] );
    yacc( vertex_it.first->location()[1] );
  }

  m_min_location[0] = min(xacc);
  m_min_location[1] = min(yacc);
  m_max_location[0] = max(xacc);
  m_max_location[1] = max(yacc);
}

void	flat::PointCloud::comp_min_max_z()	const
{
  using namespace boost::accumulators;

  accumulator_set< coord_t, features< tag::min, tag::max > > zacc;

  for( auto vertex_it = vertex_handles(); vertex_it.first != vertex_it.second; vertex_it.first++ )
    zacc( vertex_it.first->location()[2] );

  m_min_location[2] = min( zacc );
  m_max_location[2] = max( zacc );
}
