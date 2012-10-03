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

      template< variance_type... Variances >
      using variance_vector = integral::vector< variance_type, Variances... >;

      //-----| tensor_interface
      template < typename T, typename Layout, typename VarianceVector >
      struct tensor_interface
      :	public multidim_interface< T, Layout >
      {
	typedef multidim_interface< T, Layout > multidim;

	typedef VarianceVector variances;

	static_assert( variances::size == multidim::layout::order, "size of variances must agree with tensor order." );

	//---| constructor with storage pointer

	explicit
	tensor_interface( const typename multidim::storage_interface::pointer_type pointer ) : multidim( pointer )  {	}

	//TODO: !!!
	//template<  dsd > remove_index


	/*template< index_type Index >
	change_basis( const tensor_interface< T
					       , initial_layout< integral::at< sizes, Index >::value
							       , integral::at< sizes, Index >::value
							       >
					       , variance_vector< contravariant
								, covariant
								>
					       >& matrix_transform
		    )
	{
	  std::
	}*/

      };

    } // of fixed_size::
  } // of math::
} // of utk::
