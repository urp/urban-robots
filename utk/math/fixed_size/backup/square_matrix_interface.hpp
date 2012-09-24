//libutk - a utility library 
//Copyright (C) 2006  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
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
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

# pragma once

# include "utk/math/fixed_size/vector_interface.hpp"

# pragma GCC visibility push(default)

namespace utk
{ 
  namespace math
  {
	namespace fixed_size
	{

      //numerical matrix interface with column major layout (fast access with last index)
      template< typename T, size_t Cnt >
      class matn	: public vector_interface<T,Cnt*Cnt>
      {
  
		  typedef vector_interface<T,Cnt*Cnt> storage_base;
  
        protected:
        
          T*	val(size_t m,size_t n) const
          { return storage_base::ptr() + ( m * Cnt + n ); }
  
        public:
  
		  //typedef T value_type;
          //typedef typename vector_interface<T,Cnt*Cnt>::iterator	iterator;
          typedef vector_interface<T,Cnt>							column_iterator;
          typedef typename vector_interface<T,Cnt>::iterator		row_iterator;
  
		  // use base class constructors
		  // waits for gcc support
		  //using vector_interface<T,Cnt*Cnt>::vector_interface;
  
		  static const matn<T,Cnt>	invalid;
		  
          explicit
          matn( T* arr ) : storage_base( arr )
          {   }
	      
		  matn( const matn<T,Cnt>& other ) : storage_base( other )
		  {	}
  
          virtual ~matn() {	}
  
          matn<T,Cnt>&	operator= (const matn<T,Cnt>& other)
          {
		    std::copy( other.begin(), other.end(), storage_base::begin() ); 
		    return *this;
		  }
  
          /*template< size_t Cnt2 > 
          matn<T,Cnt>&	operator= (const matn<T,Cnt2>& other)
          {
		    const ptrdiff_t cnt = std::min( Cnt, Cnt2 );
		    std::copy( other.begin(), other.begin() + cnt*cnt, storage_base::begin() );
		    return *this;
	      }*/
  
          
          constexpr size_t size1() { return Cnt; }
          constexpr size_t size2() { return Cnt; }
  
          matn<T,Cnt>&	shift( ptrdiff_t elements )
          {
		    storage_base::shift( elements );
		    return *this;
		  }
  
          matn<T,Cnt>&	shift_columns( ptrdiff_t columns )
          {
			return shift( columns * Cnt );
		  }
		  
		  //-----| dereference operator
  
		  column_iterator operator*()
		  { return column_iterator( storage_base::ptr() ); }
		  
		  const column_iterator operator*() const
		  { return column_iterator( storage_base::ptr() ); }
  
		  //column_iterator operator->()		{ return column_iterator( storage_base::ptr() ); }
  
		  //---| data access
    
          column_iterator			operator[] ( const size_t m )
          {
			assert( m < Cnt );
			return column_iterator( val( m, 0 ) );
		  }
          
          const column_iterator	operator[] (const size_t m) const
          {
			assert( m < Cnt );
			return column_iterator( val( m, 0 ) );
		  }
      
          T&			operator() (const size_t m,const size_t n)
          {
			assert( m < Cnt && n < Cnt );
			return *val( m, n );
		  }
          
          const T&	operator() (const size_t m,const size_t n) const
          {
			assert( m < Cnt && n < Cnt );
			return *val( m, n );
		  }
  
          T&			at(const size_t m,const size_t n )
          {
			if( m >= Cnt || n >= Cnt )
			  throw std::out_of_range( "index ("
								      + boost::lexical_cast<std::string>( m ) + ","
								      + boost::lexical_cast<std::string>( n )
								      + ") exceeds vector dimension ("
								      + boost::lexical_cast<std::string>( Cnt ) + ","
								      + boost::lexical_cast<std::string>( Cnt ) + ")"
								      );
			return *val( m, n );
		  }
          
          const T&	at( const size_t m,const size_t n ) const
          {
            if( m >= Cnt || n >= Cnt )
              throw std::out_of_range( "index ("
								      + boost::lexical_cast<std::string>( m ) + ","
								      + boost::lexical_cast<std::string>( n )
								      + ") exceeds vector dimension ("
								      + boost::lexical_cast<std::string>( Cnt ) + ","
								      + boost::lexical_cast<std::string>( Cnt ) + ")"
								      );
			return *val( m, n );
		  }
		  
          column_iterator	col_begin()	const
          { return storage_base::ptr(); }
          
          column_iterator	col_end()	const
          { return storage_base::ptr() + storage_base::size(); }
		  
  
          row_iterator	row_begin( size_t col ) const
          {
			assert( col < Cnt );
			return row_iterator( val( col, 0) ).begin();
		  }
          
          row_iterator	row_end( size_t col )	const
          {
			assert( col < Cnt );
			return row_iterator( val( col, 0) ).end();
		  }
  
		  //---| unity
          
          constexpr matn<T,Cnt>	unity()	{ return matn<T,Cnt>(T(1),T(0)); }
         
      };
      
      template< typename T > class	matn<T,0> {	};
  
      //---| invalid matrix
      
      template<typename T,size_t Cnt>
      const matn<T,Cnt> matn<T,Cnt>::invalid = matn<T,Cnt>( nullptr );
	} // of fixed_size::
  } // of utk::
} // of math::

#pragma GCC visibility pop
