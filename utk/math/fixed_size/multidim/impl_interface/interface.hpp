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

# include "utk/math/fixed_size/storage_traits.hpp"
# include "utk/math/fixed_size/interface_traits.hpp"

# include "utk/math/fixed_size/multidim/impl_layout/helpers.hpp" // for index_type, ...

# include "utk/math/fixed_size/multidim/impl_interface/change_layout.hpp"
# include "utk/math/fixed_size/multidim/impl_iterators/declare_iterators.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {

	template < typename ValueType, typename StorageTag, typename Layout >
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

	    //:::| constructors |::::::::::::::::::::::::::::::::::::::::/

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



	    //:::| iterators |:::::::::::::::::::::::::::::::::::::::::::/

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

      } // of multidim:

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

      };

    } // of fixed_size::
  } // of math::
} // of utk::
