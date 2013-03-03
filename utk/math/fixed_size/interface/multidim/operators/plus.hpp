/*  plus.hpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/interface/generic_functions/plus.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {
        namespace multidim
        {

          //:::| operator+/+= |:::::::::::::::::::::::::::::::::::::::::

          //---| tensor

          template< typename ValueType, typename StorageTagA, typename LayoutA, typename StorageTagB, typename LayoutB >
          auto operator+=( interface< ValueType, StorageTagA, LayoutA >& A, const interface< ValueType, StorageTagB, LayoutB >& B )
          -> interface< ValueType, StorageTagA, LayoutA >&
          {
            static_assert( is_multidim_structure_equivalent< LayoutA, LayoutB >::value
                         , "Tensors must have the same order and indices (size)"
                         );

            assign_plus( A.begin(), A.end(), B.begin() );
            return A;
          }

          template< typename ValueType, typename StorageTagA, typename LayoutA, typename StorageTagB, typename LayoutB >
          auto operator+( const interface< ValueType, StorageTagA, LayoutA >& A, const interface< ValueType, StorageTagB, LayoutB >& B )
          -> typename interface_traits< interface< ValueType, StorageTagA, LayoutA > >::managed_interface
          {
            typename interface_traits< interface< ValueType, StorageTagA, LayoutA > >::managed_interface result( A );

            //assign_plus( result.begin(), result.end(), B.begin() );

            result += B;

            return result;
          }

          //---| scalar

          template< typename ValueType, typename StorageTag, typename Layout >
          auto operator+=( interface< ValueType, StorageTag, Layout >& inter, const ValueType& scalar )
          -> interface< ValueType, StorageTag, Layout >&
          {
            assign_plus_scalar( inter.begin(), inter.end(), scalar );
            return inter;
          }

          template< typename ValueType, typename StorageTag, typename Layout >
          auto operator+( const ValueType& scalar, const interface< ValueType, StorageTag, Layout >& inter )
          -> typename interface_traits< interface< ValueType, StorageTag, Layout > >::managed_interface
          {
            typename interface_traits< interface< ValueType, StorageTag, Layout > >::managed_interface result( inter );

            //assign_plus_scalar( result.begin(), result.end(), scalar );

            result += scalar;

            //std::cerr << "multidim::operator+ (scalar+multidim)\t| result " << result << std::endl;

            return result ;//+= scalar; // <- why not working
          }

          template< typename ValueType, typename StorageTag, typename Layout >
          auto operator+( const interface< ValueType, StorageTag, Layout >& inter, const ValueType& scalar )
          -> typename interface_traits< interface< ValueType, StorageTag, Layout > >::managed_interface
          {
            auto result = scalar + inter;

            std::cerr << "multidim::operator+ (multidim+scalar)\t| result " << result << std::endl;

            return result;
          }

        } // of multidim::
      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
