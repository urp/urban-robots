/*  io.hpp - Copyright Peter Urban 2012

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

	template< typename ValueType, typename Storage, typename Layout >
	std::ostream& operator<< ( std::ostream& os, const interface< ValueType, Storage, Layout >& t )
	{
	  // header
	  os << "fixed_size::tensor::interface\t|" << std::endl
	     << "  value_type " << typeid(ValueType).name()
	     << "  data " << t.storage.ptr() << std::endl
	     << "  layout " << Layout() << std::endl;
	  // content
	  return print_components( os << "  ", t ) << std::endl;
	}

	// scalar

	template< typename ValueType, typename Storage, typename Layout >
	auto print_components ( std::ostream& os, const interface< ValueType, Storage, Layout >& t )
	-> typename std::enable_if< Layout::order == 0, std::ostream& >::type
	{
	  return os << at( t );
	}

	// 1d
	template< typename ValueType, typename Storage, typename Layout >
	auto print_components ( std::ostream& os, const interface< ValueType, Storage, Layout >& t )
	-> typename std::enable_if< Layout::order == 1,	std::ostream& >::type
	{
	  os << "( ";
	  std::for_each( t.template begin_index<0>(), t.template end_index<0>()
		       , [&os] (const ValueType& value)
		       { os << value << " "; }
		       );
	  return os << ")";
	}

	// 2d +
	template< typename ValueType, typename Storage, typename Layout >
	auto print_components ( std::ostream& os, const interface< ValueType, Storage, Layout >& t )
	-> typename std::enable_if< (Layout::order > 1), std::ostream& >::type
	{
	  typedef interface< ValueType, Storage, Layout > tensor_interface;

	  constexpr size_type size0 = meta::integral::pop_front< typename Layout::sizes >::value;

	  os << " <"
	     << boost::lexical_cast< std::string >( size0 ) << " ";

	  std::for_each( t.template begin_index<0>(), t.template end_index<0>()
		       , [&os] (const typename tensor_interface::template const_index_iterator<0>::value_type& small_tensor )
			 { print_components( os, small_tensor ); }
		       );
	  return os << "> ";
	}

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
