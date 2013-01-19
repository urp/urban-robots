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
            //---| assign_plus

            // terminate
            template< typename StaticEndIteratorA, typename StaticIteratorB >
            auto assign_plus( StaticEndIteratorA itA, StaticEndIteratorA endA, StaticIteratorB itB ) -> void
            { }

            // general case
            template< typename StaticIteratorA, typename StaticEndIteratorA, typename StaticIteratorB >
            auto assign_plus( StaticIteratorA itA, StaticEndIteratorA endA, StaticIteratorB itB ) -> void
            {
              std::cerr << "tensor::static_impl::assign_plus\t| itA " << (*itA) << std::endl;
              std::cerr << "tensor::static_impl::assign_plus\t| itB " << (*itB) << std::endl;

              static_cast< typename StaticIteratorA::value_type::value_type& >(*itA) += at(*itB);
              assign_plus( itA.next(), endA, itB.next() );
            }


            //---| assign_plus_scalar

            // terminate
            template< typename StaticEndIterator >
            auto assign_plus_scalar( StaticEndIterator it, StaticEndIterator end, const typename StaticEndIterator::value_type::value_type& scalar ) -> void
            { }

            // general case
            template< typename StaticIterator, typename StaticEndIterator >
            auto assign_plus_scalar( StaticIterator it, StaticEndIterator end, const typename StaticIterator::value_type::value_type& scalar ) -> void
            {
              (*it) += scalar;
              assign_plus_scalar( it.next(), end, scalar );
            }
        }

        //:::| tensor

        template< typename T, typename StorageA, typename LayoutA, typename StorageB, typename LayoutB >
        auto operator+=( interface< T, StorageA, LayoutA >& A, const interface< T, StorageB, LayoutB >& B )
        -> interface< T, StorageA, LayoutA >&
        {
          static_assert( is_tensor_structure_equivalent< LayoutA, LayoutB >::value
                       , "Tensors must have the same order and indices (size,variance)"
                       );

          static_impl::assign_plus( A.begin(), A.end(), B.begin() );
          return A;
        }

        template< typename T, typename StorageA, typename LayoutA, typename StorageB, typename LayoutB >
        auto operator+( const interface< T, StorageA, LayoutA >& A, const interface< T, StorageB, LayoutB >& B )
        -> typename interface< T, StorageA, LayoutA >::managed_interface
        {
          typename interface< T, StorageA, LayoutA >::managed_interface result( A );

          static_impl::assign_plus( result.begin(), result.end(), B.begin() );
          return result;
        }


        //:::| scalar

        template< typename T, typename Storage, typename Layout >
        auto operator+=( interface< T, Storage, Layout >& inter, const T& scalar )
        -> interface< T, Storage, Layout >&
        {
          static_impl::assign_plus_scalar( inter.begin(), inter.end(), scalar );
          return inter;
        }

        template< typename T, typename Storage, typename Layout >
        auto operator+( const T& scalar, const interface< T, Storage, Layout >& inter )
        -> typename interface< T, Storage, Layout >::managed_interface
        {
          typename interface< T, Storage, Layout >::managed_interface result( inter.storage );
          return result += scalar;
        }

        template< typename T, typename Storage, typename Layout >
        auto operator+( const interface< T, Storage, Layout >& inter, const T& scalar )
        -> typename interface< T, Storage, Layout >::managed_interface
        {
          return scalar + inter;
        }

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
