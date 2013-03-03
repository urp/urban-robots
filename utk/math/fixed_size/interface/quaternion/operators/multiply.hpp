// multiply.hpp
// Copyright (C) 2006-20013  Peter Urban (urp@pks.mpg.de)
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

# include	"utk/math/fixed_size/quaternion/interface.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace quaternion
      {
	//---| operator*
	//! Given two quaternions, multiply them to get a third quaternion.
	//! Multiplying quaternions to get a compound rotation is analagous to adding
	//! the resulting translations to get a compound translation.
	auto operator* ( const quaternion< T, StorageTagA >& a, const quaternion< T, StorageTagB >& b )
	-> quaternion< T, typename storage_traits< StorageTagA >::managed >
	{
	  return { a[3]*b[0] + a[0]*b[3] + a[1]*b[2] - a[2]*b[1]
		 , a[3]*b[1] + a[1]*b[3] + a[2]*b[0] - a[0]*b[2]
		 , a[3]*b[2] + a[2]*b[3] + a[0]*b[1] - a[1]*b[0]
		 , a[3]*b[3] - a[0]*b[0] - a[1]*b[1] - a[2]*b[2]
		 };
	}

      } // of quaternion::
    } // of fixed_size::
  } // of math::
} // of utk::
