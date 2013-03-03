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

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {
        // terminate
        template< typename ItEndA, typename ItB >
        auto assign_w_static_iterators( ItEndA ita, const ItEndA& itenda, const ItB& itb) -> void
        { }

        // general case
        template< typename ItA, typename ItEndA, typename ItB >
        auto assign_w_static_iterators( ItA ita, const ItEndA& itenda, const ItB& itb) -> void
        {
          typedef typename ItA::value_type::value_type value_typeA;
          typedef typename ItB::value_type::value_type value_typeB;

          value_typeA& a_comp = *ita;
          const value_typeB& b_comp = *itb;
          std::cerr << "static_impl::assign_md\t| before"
                    << " a " << a_comp << "("<< (&a_comp) << ")"
                    << " b " << b_comp << "("<< (&b_comp) << ")" << std::endl;

          a_comp = b_comp;

          std::cerr << "static_impl::assign_md\t| after"
                    << " a " << a_comp << "("<< (&a_comp) << ")"
                    << " b " << b_comp << "("<< (&b_comp) << ")" << std::endl;

          assign_w_static_iterators( ita.next(), itenda, itb.next() );
        }

      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
