//io.hpp
//Copyright (C) 2006-2012 Peter Urban (peter.urban@s2003.tu-chemnitz.de)
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

# include <boost/filesystem.hpp>

# include <iostream>
# include <stdexcept>
# include <string>
# include <limits>

//# pragma GCC visibility push(default)

namespace utk
{
  namespace io
  {
    // exceptions
    struct stream_insertion_error : public std::out_of_range
    {
        stream_insertion_error()
        : std::out_of_range("could not insert value into stream") {   }
    };


    struct stream_extraction_error : public std::out_of_range
    {
        stream_extraction_error()
        : std::out_of_range("could not extract value from stream") {   }
    };


    static const char get_preferred_slash()
    {
      boost::filesystem::path slash("/");
      std::string preferred = slash.make_preferred().native();
      //static_assert( preferred.length() == 1, "Directory seperator should be only one character wide" );
      return preferred[0];
    }

    static const char	directory_delimiter = get_preferred_slash();

    template<class It>
    std::istream&	sequence_from_stream(std::istream& is,It bi,It ei)
    throw(stream_extraction_error)
    {
      It it=bi;
      while(it!=ei && is>>*it) it++;

      if( it!=ei ) throw stream_extraction_error();
      return is;
    }

    //reads values from input stream and ignore delimiter between values
    template<class It>
    std::istream&	sequence_from_stream(std::istream& is,It bi,It ei,char delim)
    throw(stream_extraction_error)
    {
      It it=bi;
      while(it!=ei && is>>*it)
        if(++it!=ei) is.ignore(std::numeric_limits<std::streamsize>::max(),delim);

      if( it!=ei ) throw stream_extraction_error();
      return is;
    }

    template<class It>
    std::ostream&	sequence_to_stream(std::ostream& os,It bi,It ei,std::string delim="\n")
    throw(stream_insertion_error)
    {
      It it=bi;
      while(it!=ei && os<<*it)
        if(++it!=ei) os<<delim;

      if( it!=ei ) throw stream_insertion_error();
      return os;
    }
  }
}

//#pragma GCC visibility pop
