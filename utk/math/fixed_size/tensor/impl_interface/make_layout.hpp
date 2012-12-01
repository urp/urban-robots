/*  make_layout.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/layout.hpp"

# include "utk/math/fixed_size/tensor/impl_interface/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace tensor
      {

	template< multidim::size_type...SizeVector >
	using size_vector = multidim::size_vector< SizeVector... >;

	typedef meta::integral::constant< variance_type, contravariant > contravariant_tag;
	typedef meta::integral::constant< variance_type, covariant > covariant_tag;

	template< index_type ContravariantIndices >
	using mixed_tag = meta::integral::constant< index_type, ContravariantIndices >;


	template< typename, typename VarianceSpecifier >
	struct make_layout { /* unspecified */ };

	// add variance attribute to Layout
	template< typename Layout, variance_type...VarianceVector >
	struct make_layout< Layout, meta::integral::vector< variance_type, VarianceVector... > >
	{
	  typedef typename multidim::add_attributes< Layout, variance_vector< VarianceVector... > >::type type;
	};

	// add uniform variance attribute to Layout
	template< typename Layout, variance_type Variance >
	class make_layout< Layout, meta::integral::constant< variance_type, Variance > >
	{
	    typedef typename meta::integral::make_uniform_vector< variance_type, Layout::order, Variance >::type variance_attribute;
	  public:
	    typedef typename make_layout< Layout, variance_attribute >::type type;

	};

	// uniform plain layout
	template< size_type...SizeVector , variance_type Variance >
	class make_layout< size_vector< SizeVector... >, meta::integral::constant< variance_type, Variance > >
	{
	    typedef multidim::layout< size_vector< SizeVector... > > plain_layout;
	    typedef typename meta::integral::make_uniform_vector< variance_type, plain_layout::order, Variance >::type variance_attribute;
	  public:
	    typedef typename make_layout< plain_layout, variance_attribute >::type type;
	};

	// mixed tensor
	template< size_type...SizeVector, index_type ContravariantIndices >
	class make_layout< size_vector< SizeVector... >, meta::integral::constant< index_type, ContravariantIndices > >
	{
	    typedef multidim::layout< size_vector< SizeVector... > > plain_layout;

	    typedef typename meta::integral::make_uniform_vector< variance_type, ContravariantIndices, contravariant >::type contravar;
	    typedef typename meta::integral::make_uniform_vector< variance_type, plain_layout::order - ContravariantIndices, covariant >::type covar;
	    typedef typename meta::integral::concatinate< contravar, covar >::type variance_attribute;
	  public:
	    typedef typename make_layout< plain_layout, variance_attribute >::type type;
	};

	// mixed tensor
	template< size_type...SizeVector, variance_type...VarianceVector >
	class make_layout< meta::integral::vector< size_type, SizeVector... >, meta::integral::vector< variance_type, VarianceVector... > >
	{
	    typedef multidim::layout< size_vector< SizeVector... > > plain_layout;

	  public:
	    typedef typename make_layout< plain_layout, variance_vector< VarianceVector... > >::type type;
	};


      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
