/*  bla.h - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim_interface.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      typedef enum { contravariant=false, covariant=true } variance_type;

      //-----| tensor_interface

      template< typename, typename, typename > struct tensor_interface
      { /* unspecified */ };

      template < typename T, typename...LayoutData, variance_type...Variances >
      struct tensor_interface< T, multidim_layout< LayoutData... >, integral::vector< variance_type, Variances... > >
      :	public multidim_interface< T, multidim_layout< LayoutData... > >
      {

	typedef multidim_interface< T, multidim_layout< LayoutData... > > multidim_base;

	typedef integral::vector< variance_type, Variances... > variances;

	static_assert( variances::size == multidim_base::rank(), "size of variances must agree with tensor rank." );

	//---| constructor with storage pointer

	explicit
	tensor_interface( typename multidim_base::storage_base::pointer_type pointer ) : multidim_base( pointer )  {	}
      };

    } // of fixed_size::
  } // of math::
} // of utk::
