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

//# include "utk/math/fixed_size/interface/tensor/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {

          //---| assign_plus
          // TODO: !!! Make generic !!!

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
            static_cast< typename StaticIterator::value_type::value_type& >(*it) += scalar;
            assign_plus_scalar( it.next(), end, scalar );
          }


      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
