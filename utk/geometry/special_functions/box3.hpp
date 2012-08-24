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

namespace utk
{
  namespace geometry
  {
	//coordinates corresponding to vertex index i 
    vecn3s	box3_vertex(unsigned int);
	//the 6 voxel neighbourhood in relative coordinates 
	vecn3i	box3_nb6(unsigned int);
	//the 26 voxel neighbourhood in relative coordinates 
	vec3i	box3_nb26(unsigned int);
	//the 3 neighbourhood vertices
	vec3s	box3_vertex_nb(unsigned int);	
  }
}
