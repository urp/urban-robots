/*  interface.hpp - Copyright Peter Urban 2012

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

# include "utk/meta/vector_pop_back.hpp"

# include "utk/math/fixed_size/multidim/impl_layout/add_attributes.hpp"
# include "utk/math/fixed_size/multidim/impl_iterators/declare_iterators.hpp"

# include "utk/math/fixed_size/tensor/impl_interface/change_layout.hpp"
# include "utk/math/fixed_size/tensor/impl_interface/operators/assign.hpp"



# include "utk/math/fixed_size/multidim/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace tensor
      {
	typedef size_t size_type;
	typedef ptrdiff_t index_type;

	typedef enum { contravariant=false, covariant=true } variance_type;

	template< variance_type... Variances >
	using variance_vector = meta::integral::vector< variance_type, Variances... >;

	//---| interface

	template < typename ValueType, typename Layout >
	class interface
	: public multidim::interface< ValueType, Layout >
	{
	    typedef interface< ValueType, Layout > type;

	    typedef multidim::interface< ValueType, Layout > multidim_interface;

	  public:

	    typedef Layout layout;

	    typedef typename multidim_interface::storage_interface storage_interface;

	    typedef typename meta::pop_back< typename Layout::attributes >::type variances;

	    static_assert( std::is_same< typename variances::value_type, variance_type >::value
			 , "no variance index-attribute specified. Ought to be the last element in Layout::attributes" );

	    //---| constructor with storage pointer

	    explicit
	    interface( const typename storage_interface::pointer_type pointer )
	    : multidim_interface( pointer )  { }

	    explicit
	    interface( const storage_interface& storage )
	    : multidim_interface( storage )  { }


	    //template< index_type Index >
	    //change_basis( const interface< ValueType

	    //:::| assignment operator |:::::::::::::::::::::::::::::::/

	    UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ASSIGNMENT_OPERATOR( interface, ValueType, Layout )

	    //:::| iterators |:::::::::::::::::::::::::::::::::::::::::/

	    UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ITERATORS( type )

	};

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
