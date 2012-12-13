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

# include "utk/math/fixed_size/vector/vector.hpp"
# include "utk/math/fixed_size/vector/at.hpp"

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

	struct unmanaged_tag {};
	struct managed_tag {};

	struct default_storage
	{
	  typedef unmanaged_tag unmanaged;

	  typedef managed_tag managed;
	};


	template< typename Storage >
	struct storage_traits
	{ /* unspecified */ };

	template< >
	struct storage_traits< unmanaged_tag >
	: public default_storage
	{
	  template< typename ValueType, size_type Size >
	  using type = fixed_size::vector::interface< ValueType, Size >;
	};

	template< >
	struct storage_traits< managed_tag >
	: public default_storage
	{
	  template< typename ValueType, size_type Size >
	  using type = fixed_size::vector::array< ValueType, Size >;
	};

	template < typename T, typename Storage, typename Layout >
	struct interface
	{
	    typedef interface< T, Storage, Layout > type;

	    typedef T value_type;

	    typedef Layout layout;

	    //---| storage

	    typedef typename storage_traits< Storage >::template type< T, layout::total_size > storage_type;

	    typedef typename storage_traits< Storage >::unmanaged unmanaged_storage_tag;
	    typedef typename storage_traits< Storage >::managed   managed_storage_tag;

	    typedef typename storage_traits< unmanaged_storage_tag >::template type< T, layout::total_size > unmanaged_storage;
	    typedef typename storage_traits< managed_storage_tag   >::template type< T, layout::total_size >   managed_storage;

	    typedef interface< T, unmanaged_storage_tag, Layout > unmanaged_interface;
	    typedef interface< T, managed_storage_tag  , Layout > managed_interface;

	    storage_type storage;

	    static constexpr index_type order = layout::order;

	    //:::| constructors |::::::::::::::::::::::::::::::::::::::::/

	    //---| default constructor
	    //-----| enable if storage is managed

	    //template< typename S = storage_type
	    //	    , typename = typename std::enable_if< std::is_same< S, typename storage_traits< S >::managed >::value, void >::type
	    //	    >
	    explicit interface()
	    : storage()  { }


	    //---| constructor with storage pointer
	    //-----| enable if storage is unmanaged

	    //template< typename S = storage_type
	    //	    , typename = typename std::enable_if< std::is_same< storage_type, typename storage_traits< storage_type >::unmanaged >::value, void >::type
	    //	    >
	    explicit interface( const typename unmanaged_storage::pointer_type pointer )
	    : storage( pointer )  { }

	    // either copies or handles values depending on storage_type
	    explicit
	    interface( const unmanaged_storage& s )
	    : storage( s )
	    { }

	    //:::| iterators |:::::::::::::::::::::::::::::::::::::::::::/

	    UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ITERATORS( type )

	    //:::| conversion operators TODO Replace with macro

	    //---| scalar component

	    template< size_type order = layout::order, typename = typename std::enable_if< order==0, void >::type >
	    operator value_type& ()
	    {
	      std::cerr << "multidim::interface::operator value_type\t|"
			<<" offset  " << layout::static_offset()
			<<" storage " << storage << std::endl;

	      return at( storage, layout::static_offset() );
	    }

	    template< size_type order = layout::order, typename = typename std::enable_if< order==0, void >::type >
	    operator const value_type& () const
	    {
	      std::cerr << "multidim::interface::operator const value_type\t|"
			<<" offset  " << layout::static_offset()
			<<" storage " << storage << std::endl;
	      return at( storage, layout::static_offset() );
	    }

	};

	template< typename T, typename Storage, typename Layout >
	constexpr index_type interface< T, Storage, Layout >::order;

      } // of multidim:
    } // of fixed_size::
  } // of math::
} // of utk::
