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

//# include <boost/lexical_cast.hpp>

# include "utk/math/fixed_size/multidim/impl_layout/io.hpp"
# include "utk/math/fixed_size/multidim/impl_slice_layout/slice_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {

	template< typename FullLayout, typename FullIndexMask, typename...NewIndexAttributes >
	std::ostream& operator<< ( std::ostream& os, const slice_layout< FullLayout, FullIndexMask >& l )
	{
	  typedef slice_layout< FullLayout, FullIndexMask > type;

	  // header
	  os << "fixed_size::multidim::slice_layout\t|" << std::endl
	     << "  masked\t: " << typename type::layout() << std::endl
	     << "  mask\t" << FullIndexMask() << "  offset " << type::static_offset()
	     << ( sizeof...(NewIndexAttributes) > 0
		  ? "  new attributes " + boost::lexical_cast<std::string>( sizeof...(NewIndexAttributes) - 2 )
		  : ""
		) << std::endl
	     << "  full\t" << FullLayout();
	  return os;
	}
	/*
	template< typename ValueType, typename Layout >
	auto print_components ( std::ostream& os, const interface< ValueType, Layout >& t )
	-> typename std::enable_if< Layout::order == 0, std::ostream& >::type
	{
	  return os << t.at() << std::endl;
	}

	template< typename ValueType, typename Layout >
	auto print_components ( std::ostream& os, const interface< ValueType, Layout >& t )
	-> typename std::enable_if< Layout::order == 1,	std::ostream& >::type
	{
	  os << "( ";
	  std::for_each( t.template begin<0>(), t.template end<0>()
		       , [&os] (const ValueType& value)
		       { os << value << "\t"; }
		       );
	  return os << ")";
	}

	// 2d +
	template< typename ValueType, typename Layout >
	auto print_components ( std::ostream& os, const interface< ValueType, Layout >& t )
	-> typename std::enable_if< (Layout::order > 1), std::ostream& >::type
	{
	  typedef interface< ValueType, Layout > tensor_interface;

	  constexpr size_type size0 = meta::integral::pop_front< typename Layout::sizes >::value;

	  os << " <"
	     << boost::lexical_cast< std::string >( size0 );

	  std::for_each( t.template begin<0>(), t.template end<0>()
		       , [&os] (const typename tensor_interface::template const_iterator<0>::value_type& small_tensor )
			 { print_components( os, small_tensor ); }
		       );
	  return os << "> ";
	}*/

	/* 3d++
	template< typename ValueType, typename Layout >
	auto print_components ( std::ostream& os, const interface< ValueType, Layout >& t )
	-> typename std::enable_if< typename Layout::order > 2, std::ostream& >::type
	{
	  typedef meta::pop_back< typename meta::pop_back< typename Layout::sizes >::tail >::tail sizes_2d;
	  typedef index_range< sizes_2d >::type indices;
	  meta::apply< indices, TensorIndex2dOutput >
	}*/



      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
