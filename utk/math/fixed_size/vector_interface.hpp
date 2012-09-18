//libutk-vector_interface fixed size vector interface
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

//# include <tuple>

# include <cassert>
# include <stdexcept>

# include <boost/lexical_cast.hpp>

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      // stl-compliant fixed size numeric vector with unmanaged pointer access to its components
      template<typename T,size_t Size>
      class	vector_interface
      {
          T*	val;

          // leave memory uninitialized (use vector_interface<T,Size>::invalid you need it)
	  vector_interface() : val(nullptr)	{	}

        public:

	  typedef T*	pointer_type;

	  // stl iterator interface
          typedef T  			value_type;
          typedef pointer_type	iterator;
          typedef pointer_type	const_iterator;

          static const vector_interface<T,Size>	invalid;

          // number of elements stored in the vector
          constexpr static const size_t size()	{ return Size; }

          // constructs s vector_interface interface for an array.
          // the memory is NOT deleted by the destructor
          explicit
          vector_interface( pointer_type pointer ) : val( pointer )
          {	}

	  // TODO: needs LOVE (conditional?)
          // constructs the interface from s second vector_interface with larger or equal size
          template<size_t D2>
          vector_interface(const vector_interface<T,D2>& o) : val(o.ptr())
          { static_assert( Size <= D2, "copy" ); }

          // copy interface
          vector_interface(const vector_interface<T,Size>& o) : val(o.ptr())
          {	}

          // destructor
          // the memory is NOT deleted on destruction
          virtual
          ~vector_interface()
          {  	}

          template<size_t D2>
          vector_interface<T,Size>&		operator= (const vector_interface<T,D2>& o)
	  {
	    std::copy( o.ptr(), o.ptr()+std::min(Size,D2), begin() );
	    return *this;
	  }

          vector_interface<T,Size>&		operator= (const vector_interface<T,Size>& o)
          {
            std::copy( o.begin(), o.end(), begin() );
	    return *this;
	  }

          vector_interface<T,Size>&		operator= (const T& v)
          {
            std::fill( begin(), end(), v );
	    return *this;
	  }

	  //---| pointer interface

          // use data from pointer location
          void	ref(T* ptr) { val = ptr; }

          // invalidate interface
          void	unref()		{ val = 0; }

	  // indicates if a storage is attached
	  const bool is_valid() const { return bool(val); }

	  // returns storage pointer
          T*	ptr() const	{ return val; }

	  //---| iterator interface

          //-----| shift operators
          //-------add offset to the storage pointer
	  // TODO: make non-member, maybe?
          vector_interface<T,Size>&	shift( ptrdiff_t elements)
          {
	    val += elements;
	    return *this;
	  }

		  /*
          vector_interface<T,Size>&	operator++()
          {
		    val += Size;
		    return *this;
		  }

          vector_interface<T,Size>&	operator--()
          {
		    val -= Size;
		    return *this;
		  }

          vector_interface<T,Size>		operator++(int)
          {
		    val += Size;
		    return vector_interface<T,Size>(val-Size);
		  }

          vector_interface<T,Size>		operator--(int)
          {
		    val -= Size;
		    return vector_interface<T,Size>(val+Size);
		  }

		  //-----| dereference operator

          // enable only for Size==1 ? with template< size_t C = Size, typename = typename std::enable_if< C==1  >::type >

		  T&			operator*()		{ return *ptr(); }

		  const T& 	operator*() const	{ return *ptr(); }

		  T*			operator&() const { return ptr(); }

		  T* 			operator->()		{ return ptr(); }
		  */

          //---| data access

          iterator			begin()			{ return val; }
          const_iterator	begin()	const	{ return val; }
          iterator			end()			{ return val+Size; }
          const_iterator	end() 	const	{ return val+Size; }

	  // TODO: make non-member
          T& at(const size_t i) throw( std::out_of_range )
	  {
            if(i>=Size)
              throw std::out_of_range( "index "
				      + boost::lexical_cast<std::string>(i)
				      + " exceeds vector dimension"
				      + boost::lexical_cast<std::string>(Size)
				      );
            return val[i];
          }

          const T&	at(const size_t i) const throw( std::out_of_range )
          {
            if(i>=Size)
              throw std::out_of_range( "index "
				      + boost::lexical_cast<std::string>(i)
				      + " exceeds vector dimension"
				      + boost::lexical_cast<std::string>(Size)
				      );
            return val[i];
    	  }

          T& operator() (const size_t i)
	  {
            assert(i<Size);
            return val[i];
          }

          const T& operator() (const size_t i) const
          {
            assert(i<Size);
            return val[i];
    	  }


          T& operator[] (const size_t i)
	  {
            assert(i<Size);
            return val[i];
          }

          const T& operator[] (const size_t i) const
          {
            assert(i<Size);
            return val[i];
    	  }

	  //---| type-conversion operators

	  //-----| T
	  //-------enabled only if Size==1.
	  //-------crazy trick from http://stackoverflow.com/questions/7693703/can-i-use-something-like-enable-if-with-an-implicit-conversion-operator

          // we need to 'duplicate' the template parameters
          // because SFINAE will only work for deduced parameters
          // and defaulted parameters count as deduced
          template< size_t C = Size, typename = typename std::enable_if< C==1 >::type >// C++11 allows the use of SFINAE right here!
	  operator T&() { return val[0]; }

          template< size_t C = Size, typename = typename std::enable_if< C==1 >::type >// C++11 allows the use of SFINAE right here!
	  operator const T&() const { return val[0]; }

	  //-----| bool
	  //-------enabled only if Size > 1 AND value_type == bool.
	  //-------return true if all elements compare as equal to T(true)
	  template< typename TT = T, size_t C = Size
		   , typename = typename std::enable_if< (C > 1) && ( std::is_same<T,bool>::value ) >::type >
	  operator bool() const
	  {
	    return std::all_of( begin(), end(), std::bind2nd( std::equal_to<T>(), true ) );
	  }

      };

      //---| invalid vector

      template<typename T,size_t Size>
      const vector_interface<T,Size> vector_interface<T,Size>::invalid = vector_interface<T,Size>( nullptr );

    } // of fixed_size::
  } // end of math::
} // end of utk::

#pragma GCC visibility pop
