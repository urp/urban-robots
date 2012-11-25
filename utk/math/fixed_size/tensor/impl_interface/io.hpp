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

# include "utk/meta/integral/integral.hpp"

# include "utk/math/fixed_size/tensor/impl_interface/interface.hpp"
# include "utk/math/fixed_size/tensor/impl_interface/change_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace tensor
      {

	template< typename ValueType, typename Layout, typename VarianceVector >
	std::ostream& operator<< ( std::ostream& os, const interface< ValueType, Layout, VarianceVector >& t )
	{
	  // header
	  os << "utk::math::fixed_size::tensor\t|" << std::endl
	     << " value_type " << typeid(ValueType).name() << std::endl
	     ;//<< " layout : " << Layout() << std::endl;
	  // content
	  return print_components( os, t );
	}

	template< typename ValueType, typename Layout, typename VarianceVector >
	auto print_components ( std::ostream& os, const interface< ValueType, Layout, VarianceVector >& t )
	-> typename std::enable_if< Layout::order == 0, std::ostream& >::type
	{
	  return os << t.at() << std::endl;
	}

	template< typename ValueType, typename Layout, typename VarianceVector >
	auto print_components ( std::ostream& os, const interface< ValueType, Layout, VarianceVector >& t )
	-> typename std::enable_if< Layout::order == 1,	std::ostream& >::type
	{
	  os << "( ";
	  std::for_each( t.template begin<0>(), t.template end<0>()
		       , [&os] (const ValueType& value)
		       { os << value << "\t"; }
		       );
	  return os << ")";
	}

	template< typename ValueType, typename Layout, typename VarianceVector >
	auto print_components ( std::ostream& os, const interface< ValueType, Layout, VarianceVector >& t )
	-> typename std::enable_if< Layout::order == 2, std::ostream& >::type
	{
	  typedef interface< ValueType, Layout, VarianceVector > tensor_interface;

	  typedef tensor_interface::template const_iterator<0> cit0;

	  static_assert( cit0::value_type::order == 1, "something is strange here" );

	  print_components( os, *t.template begin<0>() );
	  /*
	  std::for_each( t.template begin<0>(), t.template end<0>()
		       , [&os] (typename tensor_interface::template const_iterator<0>& it )
			 {
			   auto tensor1d( *it );
			   print_components1( os, tensor1d );
			   os << std::endl;
			 }
		       );*/
	  return os << "end (tensor components)" << std::endl;
	}
/*
	template< typename Tensor >
	struct TensorIndex2dOutput
	{
	  typedef typename Tensor::value_type value_type;

	  std::ostream& output_stream;
	  const Tensor& output_tensor;

	  auto default_format() -> std::ostream& { }

	  TensorIndexOutput( std::ostream& os, const Tensor& t )

	  template< typename IndexVector >
	  void apply()
	  {
	    output_stream << print_components(output_tensor.at<IndexVector>()) << value_delimiter;
	  }
	};

	template< typename ValueType, typename Layout, typename VarianceVector >
	auto print_components ( std::ostream& os, const interface< ValueType, Layout, VarianceVector >& t )
	-> std::enable_if< typename Layout::order > 2, std::ostream& >::type
	{
	  typedef meta::pop_back< typename meta::pop_back< typename Layout::sizes >::tail >::tail sizes_2d;
	  typedef index_range< sizes_2d >::type indices;
	  meta::apply< indices, TensorIndex2dOutput >
	}
*/



      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
