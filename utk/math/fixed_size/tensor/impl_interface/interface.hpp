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

# include "utk/math/fixed_size/tensor/impl_interface/specialized_functions.hpp"

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

	  public:

	    typedef multidim::interface< ValueType, Layout > multidim_interface;

	    typedef typename meta::pop_back< typename Layout::attributes >::type variances;

	    static_assert( std::is_same< typename variances::value_type, variance_type >::value
			 , "no variance index-attribute specified. Ought to be the last element in Layout::attributes" );

	    //---| constructor with storage pointer

	    explicit
	    interface( const typename multidim_interface::storage_interface::pointer_type pointer )
	    : multidim_interface( pointer )  {	}

	    explicit
	    interface( const typename multidim_interface::storage_interface& storage ) : multidim_interface( storage )
	    { }


	    /*template< index_type Index >
	    change_basis( const interface< ValueType
						   , initial_layout< meta::integral::at< sizes, Index >::value
								   , meta::integral::at< sizes, Index >::value
								   >
						   , variance_vector< contravariant
								    , covariant
								    >
						   >& matrix_transform
			)
	    {
	      std::
	    }*/

	    //:::| dynamic iterator interface |::::::::::::::::::::::::::/

	    //:::::| declare iterators

	    // TODO: !!! these aliases make gcc-4.7 crash

	    template< index_type Index >
	    using iterator = const multidim::dynamic_iterator< type, Index >;

	    template< index_type Index >
	    using const_iterator = const multidim::dynamic_iterator< type, Index >;

	    //---| begin
	    //---| TODO: test iterator interface
	    template< index_type Index >
	    iterator<Index> begin() { return iterator< Index >( *this, 0 ); }

	    template< index_type Index >
	    const_iterator<Index> begin() const { return const_iterator< Index >( *this, 0 ); }

	    //---| end

	    template< index_type Index >
	    auto end( ) -> iterator<Index>
	    {
	      constexpr index_type end_index = meta::integral::at< typename Layout::sizes, Index>::value;
	      return const_iterator< Index >( *this, end_index );

	    }

	    template< index_type Index >
	    auto end( ) const -> const_iterator<Index>
	    {
	      constexpr index_type end_index = meta::integral::at< typename Layout::sizes, Index>::value;
	      return const_iterator< Index >( *this, end_index );
	    }

	};

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::
