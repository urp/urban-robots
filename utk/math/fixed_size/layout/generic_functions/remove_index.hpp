/*  remove_index.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/index_types.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace layout
      {
        //---| remove_index
        //-----returns a new layout with Index fixed (to Value)

        template< typename Layout, index_type Index >
        struct remove_index
        { /* unspecified */ };

        //---| remove_indices
        //-----remove a list of indices from Layout

        template< typename Layout, typename IndexVector >
        struct remove_indices
        { /* unspecified */ };

        // terminate
        template< typename FullLayout >
        struct remove_indices< FullLayout, meta::integral::vector< index_type > >
        {
          typedef FullLayout type;
        };

        // start -> recurse
        template< typename FullLayout, index_type...Indices >
        class remove_indices< FullLayout, meta::integral::vector< index_type, Indices... > >
        {
            typedef typename meta::integral::pop_front< meta::integral::vector< index_type, Indices... > > indices_pop;
            typedef typename remove_indices< FullLayout, typename indices_pop::tail >::type tail;
          public:
            typedef typename remove_index< tail, indices_pop::value >::type type;
        };


      } // of layout::
    } // of fixed_size::
  } // of math::
} // of utk::
