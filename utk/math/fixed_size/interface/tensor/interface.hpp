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

# include "utk/math/fixed_size/interface/multidim/interface.hpp"

# include "utk/math/fixed_size/interface/generic_functions/change_layout.hpp"
# include "utk/math/fixed_size/interface/generic_functions/assign.hpp"

# include "utk/math/fixed_size/iterator/declare_iterators.hpp"

# include "utk/meta/vector_pop_back.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace interface
      {
	namespace tensor
	{

	  typedef enum { contravariant=false, covariant=true } variance_type;

	  template< variance_type... Variances >
	  using variance_vector = meta::integral::vector< variance_type, Variances... >;


	  template< typename Layout, typename OtherLayout >
	  class is_tensor_structure_equivalent
	  {
	      // trim attributes
	      static constexpr size_type min_size = Layout::order > OtherLayout::order ? OtherLayout::order : Layout::order;

	      typedef typename meta::pop_back< typename Layout::attributes >::type var1;
	      typedef typename meta::pop_back< typename OtherLayout::attributes >::type var2;

	      typedef typename meta::integral::split< var1, min_size >::first trimmed_variances1;
	      typedef typename meta::integral::split< var2, min_size >::first trimmed_variances2;

	    public:

	      // compare order, sizes and variances for equality
	      static constexpr bool value = interface::multidim::is_multidim_structure_equivalent< Layout, OtherLayout >::value
					    and meta::integral::all< typename meta::integral::equal< trimmed_variances1
												   , trimmed_variances2 >::type >::value;
	  };

	  //---| interface
	  //-----| handles the variance attribute in multidim::layout
	  template < typename ValueType, typename StorageTag, typename Layout >
	  class interface
	  : public multidim::interface< ValueType, StorageTag, Layout >
	  {
	      typedef interface< ValueType, StorageTag, Layout > type;

	      typedef multidim::interface< ValueType, StorageTag, Layout > base;

	    public:


	      typedef Layout layout;

	      typedef typename meta::pop_back< typename Layout::attributes >::type variances;

	      static_assert( std::is_same< typename variances::value_type, variance_type >::value
			   , "Expected an index attribute of type 'fixed_size::tensor::variance_type' as the last element in Layout::attributes" );

	      //---| default constructor
	      //-----| enable if storage is managed

	      template< typename S = typename type::storage_tag
		      , typename = typename std::enable_if< std::is_same< S, typename storage_traits< typename base::storage_tag >::managed_tag >::value >::type
		      >
	      explicit interface() : base()
	      {
		std::cerr << "tensor::interface::interface (default) |" << base::storage << std::endl;
	      }


	      //---| constructor with storage pointer
	      //-----| enable if storage is unmanaged

	      template< typename S = typename type::storage_tag
		      , typename = typename std::enable_if< std::is_same< S, typename storage_traits< S >::unmanaged_tag >::value >::type
		      >
	      explicit interface( const typename interface_traits< base >::unmanaged_storage::pointer_type pointer )
	      : base( pointer )
	      {
		std::cerr << "tensor::interface::interface (pointer) | " << base::storage << std::endl;
	      }


	      // either copies or handles values depending on storage_type
	      explicit
	      interface( const typename interface_traits< base >::unmanaged_storage& storage )
	      : base( storage )
	      {
		std::cerr << "tensor::interface::interface (storage) | " << base::storage << " (" << StorageTag() << ") total size " << layout::total_size  << std::endl;
	      }


	      // copy
	      template< typename OtherStorage, typename OtherLayout
  /*		    , bool SameTensorStructure = is_tensor_structure_equivalent< layout, typename interface< ValueType, OtherStorage, OtherLayout >::layout >::value
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
	      : base( other.storage ) // TODO: make two seperate constructors?
	      {
		//NEW
		typedef interface< ValueType, OtherStorage, OtherLayout > other_type;

		static constexpr bool same_tensor_structure = is_tensor_structure_equivalent< layout, typename other_type::layout >::value;
		static constexpr bool same_memory_structure = fixed_size::layout::is_memory_structure_equivalent< layout, typename other_type::layout >::value;
		static_assert( not ( std::is_same< typename base::storage_tag, typename storage_traits< typename base::storage_tag >::unmanaged_tag >::value
				     and not same_memory_structure )  and same_tensor_structure
			     , "can not copy to unmanaged storage from tensor that has different memory structure"
			     );
		//NEW


		if( std::is_same< typename base::storage_tag
				, typename storage_traits< typename base::storage_tag >::unmanaged_tag >::value )
		  base::storage.ref( other.storage.ptr() );
		else // managed storage
		  assign_w_static_iterators( other.begin(), other.end(), begin() );

		std::cerr << "tensor::interface::inferface (copy) | " << base::storage << " other " << other.storage << " (" << typename base::storage_tag() << ")" << std::endl;
	      }

	      interface( const type& other)
	      : base( other.storage )
	      {
		std::cerr << "tensor::interface::inferface (type copy) | " << base::storage << base::storage << " other " << other.storage << " (" << typename base::storage_tag() << ")" << std::endl;
	      }


	      //template< index_type Index >
	      //change_basis( const interface< ValueType


	      //---| assignment operator
	      //-----enable if order, index dimensions (sizes) and ValueType agree

	      template< typename OtherStorage, typename OtherLayout >
	      auto operator=( const interface< ValueType, OtherStorage, OtherLayout >& other)
	      -> typename std::enable_if< is_tensor_structure_equivalent< layout
									, typename interface< ValueType, OtherStorage, OtherLayout >::layout
									>::value
					, type&
					>::type
	      {
		assign_w_static_iterators( begin(), end(), other.begin() );
		return *this;
	      }

	      //:::| iterators |:::::::::::::::::::::::::::::::::::::::::/

	      UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ITERATORS( type )

	      //:::| type conversion operators:::::::::::::::::::::::::::/
	      // NEW
	      /*operator typename base::unmanaged_interface()
	      {
		return base::unmanaged_interface( *this );
	      }*/

	  }; // of interface<>

	} // of tensor::

	//:::| interface_traits |:::::::::::::::::::::::::::::::::::::::::

	template< typename ValueType, typename StorageTag, typename Layout >
	class interface_traits< tensor::interface< ValueType, StorageTag, Layout > >
	: public interface_traits< multidim::interface< ValueType, StorageTag, Layout > >
	{
	    typedef interface_traits< multidim::interface< ValueType, StorageTag, Layout > > base;

	  public:
	    // determine tensor::interface with (un-)managed storage
	    typedef tensor::interface< ValueType, typename base::unmanaged_storage_tag, Layout > unmanaged_interface;
	    typedef tensor::interface< ValueType, typename base::  managed_storage_tag, Layout >   managed_interface;

	    static const std::string class_name()	{ return "tensor::interface"; }
	};

      } // of interface::
    } // of fixed_size::
  } // of math::
} // of utk::
