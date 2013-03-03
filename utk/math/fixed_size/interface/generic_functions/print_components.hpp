/*  io.hpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/interface/generic_functions/interface_traits.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {

	// scalar

	template< template< typename,typename,typename > class Interface
		, typename ValueType, typename Storage, typename Layout >
	auto print_components ( std::ostream& os, const Interface< ValueType, Storage, Layout >& t )
	-> typename std::enable_if< Layout::order == 0, std::ostream& >::type
	{
	  return os << ValueType( t );
	}

	// 1d
	template< template< typename,typename,typename > class Interface
		, typename ValueType, typename Storage, typename Layout >
	auto print_components ( std::ostream& os, const Interface< ValueType, Storage, Layout >& t )
	-> typename std::enable_if< Layout::order == 1, std::ostream& >::type
	{
	  os << "( ";
	  std::for_each( t.template begin_index<0>(), t.template end_index<0>()
		       , [&os] (const ValueType& value)
		       { os << ValueType( value ) << " "; }
		       );
	  return os << ")";
	}

	// 2d +
	template< template< typename,typename,typename > class Interface
		, typename ValueType, typename Storage, typename Layout >
	auto print_components ( std::ostream& os, const Interface< ValueType, Storage, Layout >& t )
	-> typename std::enable_if< (Layout::order > 1), std::ostream& >::type
	{
	  typedef Interface< ValueType, Storage, Layout > type;

	  constexpr size_type size0 = meta::integral::pop_front< typename Layout::sizes >::value;

	  os << " <"
	     << boost::lexical_cast< std::string >( size0 ) << " ";

	  std::for_each( t.template begin_index<0>(), t.template end_index<0>()
		       , [&os] (const typename type::template const_stl_index_iterator<0>::value_type& small_tensor )
			 { print_components( os, small_tensor ); }
		       );
	  return os << "> ";
	}

      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
