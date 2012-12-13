/*  at.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/slice_layout.hpp"
# include "utk/math/fixed_size/multidim/impl_interface/change_layout.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {
	//:::| access components |:::::::::::::::::::::::::::::::::::::/

	//TODO: out of range checks! thrwo exception?
	template< typename T
		, typename Storage
		, typename Layout
		, typename...CoordTypes
		>
	auto at( interface< T, Storage, Layout >& inter, CoordTypes...coords )
	-> typename interface< T, Storage, Layout >::value_type&
	{
	  typedef interface< T, Storage, Layout > interface_type;

	  const size_t storage_index = interface_type::layout::index_offset( coords... )
				       + interface_type::layout::static_offset();

	  std::cout << "utk::math::fixed_size::multidim::at (dynamic)| "
	  	    << " storage_index " << storage_index
		    << "(" << interface_type::layout::index_offset( coords... )
		    << ", "<< interface_type::layout::static_offset() << ")"
		    << " storage "<< inter.storage << std::endl;

	  return at( inter.storage, storage_index );
	}

	// const

	template< typename T, typename Storage, typename Layout, typename...CoordTypes >
	auto at( const interface< T, Storage, Layout >& inter, CoordTypes...coords )
	-> const typename interface< T, Storage, Layout >::value_type&
	{
	  typedef interface< T, Storage, Layout > interface_type;

	  //TODO: checks
	  const size_t storage_index = interface_type::layout::index_offset( coords... )
				       + interface_type::layout::static_offset();

	  std::cout << "utk::math::fixed_size::multidim::at (const dynamic)| "
	  	    << " storage_index " << storage_index
		    << "(" << interface_type::layout::index_offset( coords... )
		    << ", "<< interface_type::layout::static_offset() << ")"
		    << " storage "<< inter.storage << std::endl;

	  return at( inter.storage, storage_index );
	}

	//:::| constexpr coords... |:::::::::::::::::::::::::::::::::::/

	//:::| complete set of indices |:::::::::::::::::::::::::::::::/

	//const

	template< typename Interface, typename Indices >
	struct at_leftover_type
	{
	  // construct full_index_mask
	  // use Indices, fill up with 'visible' indices
	  typedef typename meta::integral::split< typename Interface::layout::sizes, Indices::size >::second free_indices_tmp;
	  typedef typename meta::integral::make_vector< index_type, free_indices_tmp >::type free_indices;
	  typedef typename meta::integral::concatinate< Indices, free_indices >::type index_mask;
	  typedef slice_layout< typename Interface::layout, index_mask > new_layout;

	  // use unmanaged storage to prevent unintended allocations and copies
	  typedef typename Interface::unmanaged_interface unmanaged;

	  typedef typename change_layout< Interface, new_layout >::type type;
	};

	//TODO: use static version (template) for layout::index_offset
	template< typename T, typename Storage, typename Layout, index_type...Indices >
	auto at( interface<T, Storage, Layout>& inter, const meta::integral::vector< index_type, Indices... >& coords )
	-> typename at_leftover_type< interface< T, Storage, Layout>
				    , meta::integral::vector< index_type, Indices... >
				    >::type
	{
	  typedef typename at_leftover_type< interface< T, Storage, Layout >
					   , index_vector< Indices... >
					   >::type return_type;

	  std::cout << "utk::math::fixed_size::multidim::at (static) | indices " << index_vector< Indices... >()
		    << " storage " << inter.storage << std::endl;

	  return return_type( inter.storage );
	}

	//TODO: use static version (template) for layout::index_offset
	template< typename T, typename Storage, typename Layout, index_type...Indices >
	auto at( const interface< T, Storage, Layout >& inter, const meta::integral::vector< index_type, Indices... >& coords )
	-> const typename at_leftover_type< interface< T, Storage, Layout >
					  , meta::integral::vector< index_type, Indices... >
					  >::type
	{
	  typedef const typename at_leftover_type< interface< T, Storage, Layout >
						 , meta::integral::vector< index_type, Indices... >
						 >::type return_type;

	  std::cout << "utk::math::fixed_size::multidim::at (static const) | indices " << index_vector< Indices... >()
		    << " storage " << inter.storage << std::endl;

	  return return_type( inter.storage );
	}


      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
