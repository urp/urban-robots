//libutk-interface fixed size vector interface
//Copyright (C) 2006-2012  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received s copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

# pragma once

# include <cassert>
# include <algorithm>

# include "utk/math/fixed_size/vector/storage_traits.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace vector
      {
        typedef std::size_t size_type;

				// stl-compliant fixed size numeric vector with unmanaged pointer access to its components
				// TODO: conform with stl container concept
				template< typename T, size_type Size >
				class interface
				{
						T*	val;

						// leave memory unassigned (use interface<T,Size>::invalid if you need it)
						interface() : val( nullptr ) { }

					public:

						typedef T* pointer_type;

						// stl iterator interface
						typedef T value_type;
						typedef pointer_type	iterator;
						typedef pointer_type	const_iterator;


						// number of elements stored in the vector
						static constexpr size_type size = Size;

						typedef interface< value_type, size > type;

						// invalid vector
						static const type invalid;

						// constructs a interface interface for the provided pointer.
						// the memory is NOT deleted by the destructor
						explicit
						interface( pointer_type pointer ) : val( pointer ) { }

						// TODO: needs LOVE (conditional?)
						// constructs the interface from second interface with larger or equal size
						template< size_type Size2 >
						interface( const interface< value_type, Size2 >& o ) : val( o.ptr() )
						{ static_assert( size <= Size2, "copy constructor (vector to short to initialize with)." ); }

						// copy interface ( which refers to the same piece of memory )
						interface( const type& o ) : val( o.ptr() ) { }

						// destructor
						// note:the memory is NOT deleted on destruction
						virtual ~interface() { }

						template< size_type OtherSize >
						type& operator= ( const interface< value_type, OtherSize >& other )
						{
							std::copy( other.ptr(), other.ptr() + std::min( size, OtherSize ), begin() );
							return *this;
						}

						type& operator= ( const type& other)
						{
							std::copy( other.begin(), other.end(), begin() );
							return *this;
						}

						type& operator= ( const T& scalar )
						{
							std::fill( begin(), end(), scalar );
							return *this;
						}

						//---| pointer interface

						// use data from pointer location
						void	ref( pointer_type pointer ) { val = pointer; }

						// invalidate interface
						void	unref()	{ val = 0; }

						// indicates if a storage is attached
						const bool is_valid() const { return bool(val); }

						// returns storage pointer
						pointer_type	ptr() const { return val; }

						//---| iterator interface

						//-----| shift operators
						//-------add offset to the storage pointer
						// TODO: make non-member, maybe?
						type& shift( std::ptrdiff_t elements)
						{
							val += elements;
							return *this;
						}

						//---| data access

						iterator	 begin() 	{ return val; }
						const_iterator begin() const 	{ return val; }
						iterator	 end() 		{ return val + size; }
						const_iterator end() const 	{ return val + size; }

						value_type& operator() ( const size_type i )
						{
							assert(i<Size);
							return val[i];
						}

						const value_type& operator() ( const size_type i ) const
						{
							assert(i<Size);
							return val[i];
						}


						value_type& operator[] ( const size_type i )
						{
							assert( i < size );
							return val[i];
						}

						const value_type& operator[] ( const size_type i ) const
						{
							assert( i < size );
							return val[i];
						}

						//---| type-conversion operators

						//-----| T
						//-------enabled only if Size==1.
						//-------nice trick from http://stackoverflow.com/questions/7693703/can-i-use-something-like-enable-if-with-an-implicit-conversion-operator

						// we need to 'duplicate' the template parameters
						// because SFINAE will only work for deduced parameters
						// and defaulted parameters count as deduced
						template< size_type C = Size, typename = typename std::enable_if< C==1 >::type >
						operator value_type&() { return val[0]; }

						template< size_type C = Size, typename = typename std::enable_if< C==1 >::type >
						operator const value_type&() const { return val[0]; }

						//-----| bool
						//-------enabled only if Size > 1 AND value_type == bool.
						//-------return true if all elements compare as equal to T(true)
						template< typename TT = T, size_type C = Size
                    , typename = typename std::enable_if< (C > 1) && ( std::is_same<T,bool>::value ) >::type >
						operator bool() const
						{
							return std::all_of( begin(), end(), std::bind2nd( std::equal_to<T>(), true ) );
						}

				};

				//---| invalid vector

				template< typename T, size_type Size >
				const typename interface< T, Size >::type interface< T, Size >::invalid = interface< T, Size >( nullptr );

				//---| size

				template< typename T, size_type Size >
				constexpr size_type interface< T, Size >::size;

      } // of vector::



      //:::| storage_traits |:::::::::::::::::::::::::::::::::::::::::::

      template< >
      struct storage_traits< vector::unmanaged_tag > : public vector::default_storage_tags
      {
        template< typename ValueType, vector::size_type Size >
        using type = vector::interface< ValueType, Size >;
      };



    } // of fixed_size::
  } // end of math::
} // end of utk::

#pragma GCC visibility pop
