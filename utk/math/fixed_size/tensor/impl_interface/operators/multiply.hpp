/*  multiply.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/tensor/impl_interface/io.hpp"


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
            auto assign_multiply_scalar( StaticEndIterator it, StaticEndIterator end, const typename StaticEndIterator::value_type::value_type& scalar ) -> void
            { }

            // general case
            template< typename StaticIterator, typename StaticEndIterator >
            auto assign_multiply_scalar( StaticIterator it, StaticEndIterator end, const typename StaticIterator::value_type::value_type& scalar ) -> void
            {

              (*it) *= scalar;
              std::cerr << "tensor::assign_multiply_scalar| index " << typename StaticIterator::current_indices() << std::endl;
              assign_multiply_scalar( it.next(), end, scalar );
            }
        }


        template< typename T, typename Storage, typename Layout >
        auto operator*( const T& scalar, const interface< T, Storage, Layout >& inter )
        -> typename interface< T, Storage, Layout >::managed_interface
        {
          typename interface< T, Storage, Layout >::managed_interface result( inter.storage );

          static_impl::assign_multiply_scalar( result.begin(), result.end(), scalar );

          return result;
        }

        template< typename T, typename Storage, typename Layout >
        auto operator*( const interface< T, Storage, Layout >& inter, const T& scalar )
        -> typename interface< T, Storage, Layout >::managed_interface
        {
          return scalar * inter;
        }

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
