/*  interface.hpp - Copyright Peter Urban 2012-2013

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

# include "utk/math/fixed_size/layout/generic_functions/is_memory_structure_equivalent.hpp"

# include "utk/math/fixed_size/interface/generic_functions/storage_traits.hpp"
# include "utk/math/fixed_size/interface/generic_functions/interface_traits.hpp"

# include "utk/math/fixed_size/interface/multidim/functions/change_layout.hpp"
# include "utk/math/fixed_size/interface/multidim/functions/assign.hpp"

# include "utk/math/fixed_size/iterator/declare_iterators.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {
	namespace multidim
	{

	  template< typename Layout, typename OtherLayout >
	  class is_multidim_structure_equivalent
	  {
	      // trim attributes
	      static constexpr size_type min_size = Layout::order > OtherLayout::order ? OtherLayout::order : Layout::order;

	      typedef typename meta::integral::split< typename Layout::sizes, min_size >::first trimmed_size1;
	      typedef typename meta::integral::split< typename OtherLayout::sizes, min_size >::first trimmed_size2;

	    public:

	      // compare order, sizes and variances for equality
	      static constexpr bool value = Layout::order == OtherLayout::order
					    and meta::integral::all< typename meta::integral::equal< trimmed_size1
												   , trimmed_size2 >::type >::value;
	  };


	  template < typename ValueType	// the Field on which the tensor is defined
		   , typename StorageTag  // defines a memory-wrapper class: tags with fully defined interfaces::storage_traits< StorageTag > like interfaces::vector::[un]managed_tag.
		   , typename Layout 	// Glues component access (via indices) to storage access.
		   >
	  class interface
	  {
	      typedef interface< ValueType, StorageTag, Layout > type;

	    public:

	      typedef ValueType value_type;

	      typedef StorageTag storage_tag;

	      typedef Layout layout;

	      //---| storage
	      typedef typename storage_traits< storage_tag >::template type< ValueType, layout::total_size > storage_type;

	      storage_type storage;

	      static constexpr index_type order = layout::order;

	      //:::| constructors |:::::::::::::::::::::::::::::::::::::::

	      //---| default constructor
	      //-----| enable if storage is managed

	      template< typename S = storage_tag
		      , typename = typename std::enable_if< std::is_same< S, typename interface_traits< type >::managed_storage_tag >::value >::type
		      >
	      explicit interface()
	      : storage()  { }


	      //---| constructor with storage pointer
	      //-----| enable if storage is unmanaged

	      template< typename S = storage_tag
		      , typename = typename std::enable_if< std::is_same< S, typename interface_traits< type >::unmanaged_storage_tag >::value >::type
		      >
	      explicit interface( const typename interface_traits< type >::unmanaged_storage::pointer_type pointer )
	      : storage( pointer )  { }

	      // either copies or handles values depending on storage_type
	      explicit
	      interface( const typename interface_traits< type >::unmanaged_storage& s )
	      : storage( s )
	      { }

	      // copy
	      template< typename OtherStorage, typename OtherLayout
/*		      , bool SameTensorStructure = is_tensor_structure_equivalent< layout, typename interface< ValueType, OtherStorage, OtherLayout >::layout >::value
		      , bool SameMemoryStructure = is_memory_structure_equivalent< layout, typename interface< ValueType, OtherStorage, OtherLayout >::layout >::value
		      // can not copy if using unmanaged storage with and other tensor that has different memory structure
		      , typename S = typename base::storage_tag
		      , typename = typename std::enable_if< not ( std::is_same< S, typename storage_traits< S >::unmanaged_tag >::value
								  and not SameMemoryStructure
								) and SameTensorStructure
							  , void
							  >::type*/
		    >
	      interface( const interface< ValueType, OtherStorage, OtherLayout >& other)
	      : storage( other.storage ) // TODO: make two seperate constructors?
	      {
		//NEW
		typedef interface< ValueType, OtherStorage, OtherLayout > other_type;

		static constexpr bool same_multidim_structure = is_multidim_structure_equivalent< layout, typename other_type::layout >::value;
		static constexpr bool same_memory_structure = fixed_size::layout::is_memory_structure_equivalent< layout, typename other_type::layout >::value;
		static_assert( not ( std::is_same< storage_tag, typename storage_traits< storage_tag >::unmanaged_tag >::value
				     and not same_memory_structure )  and same_multidim_structure
			     , "can not copy to unmanaged storage from tensor that has different memory structure"
			     );
		//NEW


		if( std::is_same< storage_tag, typename storage_traits< storage_tag >::unmanaged_tag >::value )
		  storage.ref( other.storage.ptr() );
		else // managed storage
		  assign_w_static_iterators( other.begin(), other.end(), begin() );

		std::cerr << "multidim::interface::inferface (copy) | " << storage << " other " << storage << " (" << storage_tag() << ")" << std::endl;
	      }

	      interface( const type& other)
	      : storage( other.storage )
	      {
		std::cerr << "multidim::interface::inferface (type copy) | " << storage  << " other " << other.storage << " (" << storage_tag() << ")" << std::endl;
	      }


	      //---| assignment operator
	      //-----enable if order and index sizes agree

	      template< typename OtherStorage, typename OtherLayout >
	      auto operator=( const interface< ValueType, OtherStorage, OtherLayout >& other)
	      -> typename std::enable_if< is_multidim_structure_equivalent< layout
									  , typename interface< ValueType, OtherStorage, OtherLayout >::layout
									  >::value
					, type&
					>::type
	      {
		assign_w_static_iterators( begin(), end(), other.begin() );
		return *this;
	      }


	      //:::| iterators |::::::::::::::::::::::::::::::::::::::::::

	      UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ITERATORS( type )

	      //:::| conversion operators TODO Replace with macro

	      //---| scalar component

	      template< size_type order = layout::order, typename = typename std::enable_if< order==0, void >::type >
	      operator value_type& ()
	      {
		/*std::cerr << "multidim::interface::operator value_type\t|"
			  <<" offset  " << layout::static_offset()
			  <<" storage " << storage << std::endl;*/

		return at( storage, layout::static_offset() );
	      }

	      template< size_type order = layout::order, typename = typename std::enable_if< order==0, void >::type >
	      operator const value_type& () const
	      {
		/*std::cerr << "multidim::interface::operator const value_type\t|"
			  <<" offset  " << layout::static_offset()
			  <<" storage " << storage << std::endl;*/
		return at( storage, layout::static_offset() );
	      }

	  };

	  template< typename ValueType, typename Storage, typename Layout >
	  constexpr index_type interface< ValueType, Storage, Layout >::order;

	} // of multidim::

	//:::| interface_traits |:::::::::::::::::::::::::::::::::::::::::

	template< typename ValueType, typename StorageTag, typename Layout >
	struct interface_traits< multidim::interface< ValueType, StorageTag, Layout > >
	{
	  typedef StorageTag storage_tag;
	  typedef typename storage_traits< StorageTag >::unmanaged_tag unmanaged_storage_tag;
	  typedef typename storage_traits< StorageTag >::managed_tag     managed_storage_tag;

	  // determine unmanaged storage type with propper size
	  typedef typename storage_traits< unmanaged_storage_tag >::template type< ValueType, Layout::total_size > unmanaged_storage;
	  typedef typename storage_traits<   managed_storage_tag >::template type< ValueType, Layout::total_size >   managed_storage;

	  // determine multidim::interface with (un-)managed storage
	  typedef multidim::interface< ValueType, unmanaged_storage_tag, Layout > unmanaged_interface;
	  typedef multidim::interface< ValueType,   managed_storage_tag, Layout >   managed_interface;

	  static const std::string class_name()	{ return "multidim::interface"; }

	  static constexpr bool is_specified = true;
	};

      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
