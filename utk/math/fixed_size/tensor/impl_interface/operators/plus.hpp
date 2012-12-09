/*  plus.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/tensor/impl_interface/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace tensor
      {

        namespace static_impl
        {
            //---| assign_multipy scalar

            // terminate
            template< typename StaticEndIterator >
            auto plus_assign_scalar( StaticEndIterator it, StaticEndIterator end, const typename StaticEndIterator::value_type::value_type& scalar ) -> void
            { static_assert(it==end, "BUG"); }

            // general case
            template< typename StaticIterator, typename StaticEndIterator >
            auto plus_assign_scalar( StaticIterator it, StaticEndIterator end, const typename StaticIterator::value_type::value_type& scalar ) -> void
            {
              (*it) += scalar;
              assign_plus_scalar( it.next(), end, scalar );
            }
        }


        template< template< typename,typename > class Interface, typename T, typename Layout >
        auto operator+( const T& scalar, const Interface< T, Layout >& inter )
        -> array< T, Layout >
        {
          array< T, Layout > result( inter );
          plus_assign_scalar( result.begin(), result.end(), scalar );
          return result;
        }

        template< template< typename,typename > class Interface, typename T, typename Layout >
        auto operator+( const Interface< T, Layout >& inter, const T& scalar )
        -> array< T, Layout >
        {
          return scalar + inter;
        }


      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
