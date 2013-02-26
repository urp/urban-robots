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

# include "utk/math/fixed_size/tensor/impl_interface/operators/io.hpp"


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
              std::cerr << "tensor::assign_multiply_scalar| index " << typename StaticIterator::current_indices() << " res " << *it << std::endl;

              (*it) *= scalar;

              std::cerr << "tensor::assign_multiply_scalar| index " << typename StaticIterator::current_indices() << " res " << *it << std::endl;

              //std::cerr << "tensor::assign_multiply_scalar| index " << typename StaticIterator::current_indices() << " res " << *it << std::endl;


              assign_multiply_scalar( it.next(), end, scalar );
            }
        }


        template< typename ValueType, typename StorageTag, typename Layout >
        auto operator*( const ValueType& scalar, const interface< ValueType, StorageTag, Layout >& inter )
        -> typename interface_traits< interface< ValueType, StorageTag, Layout > >::managed_interface
        {
          typename interface_traits< interface< ValueType, StorageTag, Layout > >::managed_interface result( inter.storage );

          static_impl::assign_multiply_scalar( result.begin(), result.end(), scalar );

          return result;
        }

        template< typename ValueType, typename StorageTag, typename Layout >
        auto operator*( const interface< ValueType, StorageTag, Layout >& inter, const ValueType& scalar )
        -> typename interface_traits< interface< ValueType, StorageTag, Layout > >::managed_interface
        {
          return scalar * inter;
        }

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
