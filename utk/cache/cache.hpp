
/***************************************************************************
 *            cache.h
 *
 *  Fri Sep 11 16:31:48 2009
 *  Copyright  2009  Peter Urban
 *  <s9peurba@stud.uni-saarland.de>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#pragma once

# include <stdexcept>

namespace utk
{
  namespace cache
  {

    struct invalid_access_error : public std::logic_error
    { invalid_access_error() : std::logic_error("access to invalidated cache-value") {  } };

    template<class T>
    class Cache
    {
        mutable T value;		
        mutable bool valid;
      public:
        Cache() : value(),valid(false)	{	}

        explicit Cache(const T& val) : value(val), valid(true)	{	}
  
        void invalidate() { valid=false; }
  
        const bool is_valid() const	{ return valid; }

        const Cache&	operator=(const T& val)	const	
        { 
          value = val;
          valid = true;
	      return *this;
        }
	
        operator T&()	const	throw(invalid_access_error) 
        { 
          if( !is_valid() ) throw invalid_access_error();
          return value;
        }
    };

  } // of cache
} // of utk 
