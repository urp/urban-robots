//libutk - a utility library 
//Copyright (C) 2006-2009  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
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

# include <valarray>
# include <iostream>
# include <iomanip>
# include <numeric>
# include <cmath>
# include <cstdint>


# pragma GCC visibility push(default)

namespace utk
{  
  # ifdef _WIN32
  typedef	char			int8_t;
  typedef	short			int16_t;
  typedef	int				int32_t;
  //typedef	int64_t			int64_t;

  typedef	unsigned char	uint8_t;  
  typedef	unsigned short	uint16_t;
  typedef	unsigned int	uint32_t;
  //typedef	uint64_t		uint64_t;
  # else
  typedef	int8_t			int8_t;
  typedef	int16_t			int16_t;
  typedef	int32_t			int32_t;
  typedef	int64_t			int64_t;

  typedef	uint8_t			uint8_t;  
  typedef	uint16_t		uint16_t;
  typedef	uint32_t		uint32_t;
  typedef	uint64_t		uint64_t;
  #endif
  typedef	uint32_t		size_t;

}
#pragma GCC visibility pop


