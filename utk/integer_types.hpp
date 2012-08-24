/*  bla.h - Copyright Peter Urban 2009

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

namespace utk
{
  namespace math
  {

#   ifdef _WIN32
    typedef	char			int8_t;
    typedef	short			int16_t;
    typedef	int				int32_t;
    typedef	int64_t			int64_t;

    typedef	unsigned char	uint8_t;  
    typedef	unsigned short	uint16_t;
    typedef	unsigned int	uint32_t;
    typedef	uint64_t		uint64_t;
#   else
    typedef	int8_t			int8_t;
    typedef	int16_t			int16_t;
    typedef	int32_t			int32_t;
    typedef	int64_t			int64_t;

    typedef	uint8_t			uint8_t;  
    typedef	uint16_t		uint16_t;
    typedef	uint32_t		uint32_t;
    typedef	uint64_t		uint64_t;
#   endif
    typedef	uint32_t		size_t;


