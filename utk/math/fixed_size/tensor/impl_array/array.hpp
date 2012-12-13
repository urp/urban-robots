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

# include "utk/math/fixed_size/tensor/impl_interface/interface.hpp"
# include "utk/math/fixed_size/vector/array.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace tensor
      {
	//-----| array

	template < typename ValueType, typename Layout >
	struct array
	: public interface< ValueType, Layout >
	{
	    typedef array<ValueType, Layout> type;

	    typedef interface < ValueType, Layout > reference_interface;

	    typedef vector::array< ValueType, reference_interface::layout::total_size > storage_array;

	  private:

	    //---| data m_array
	    storage_array m_array;

	  public:

	    //---| constructor (create with uninitialized data)

	    explicit array()
	    : reference_interface( nullptr ), m_array()
	    { reference_interface::storage.ref( m_array.ptr() ); }

	    //---| constructor (copy raw data)

	    explicit array( const typename reference_interface::storage_interface::pointer_type& p )
	    : reference_interface(nullptr), m_array( p, p + reference_interface::layout::total_size )
	    { reference_interface::storage.ref( m_array.ptr() ); }

	    //---| constructor (copy)

	    explicit array( const typename reference_interface::storage_interface& s )
	    : reference_interface(nullptr), m_array(s) { reference_interface::storage.ref( m_array.ptr() ); }


	    auto array_data() const -> const storage_array& { return m_array; }

	    UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ASSIGNMENT_OPERATOR( array, ValueType, Layout )

	    UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ITERATORS( type )



	};

      } // of tensor::
    } // of fixed_size::
  } // of math::
} // of utk::

# pragma GCC visibility pop
