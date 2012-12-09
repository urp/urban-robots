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


namespace static_impl
{
  // terminate
  template< typename ItEndA, typename ItB >
  auto assign_md( ItEndA ita, const ItEndA& itenda, const ItB& itb) -> void
  { }

  // general case
  template< typename ItA, typename ItEndA, typename ItB >
  auto assign_md( ItA ita, const ItEndA& itenda, const ItB& itb) -> void
  {
    *ita = *itb;
    assign_md( ita.next(), itenda, itb.next() );
  }
}


# define UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ASSIGNMENT_OPERATOR( interface_template, prim_type, layout_type ) 		\
                                                                                                                    \
  template< typename OtherLayout > 								                                                                  \
  auto operator=( const interface_template< prim_type, OtherLayout >& other)				                                \
  -> typename std::enable_if< interface_template< prim_type, layout_type >::layout::order == interface_template< prim_type, OtherLayout >::layout::order 	\
			      and meta::integral::all< typename meta::integral::equal< typename interface_template< prim_type, layout_type >::layout::sizes \
										     , typename interface_template< prim_type, OtherLayout >::layout::sizes                     \
										     >::type 	                                                                                  \
						     >::value 					                                                                                \
			    , interface_template< prim_type, layout_type >&			                                                      \
			    >::type 								                                                                                  \
  { 												                                                                                        \
    static_impl::assign_md( begin(), end(), other.begin() ); 					                                              \
    return *this; 										                                                                              \
  }												                                                                                          \
