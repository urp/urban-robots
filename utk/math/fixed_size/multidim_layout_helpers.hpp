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

# include <boost/mpl/at.hpp>


# include "utk/math/integral/integral.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      using integral::index_type;

      // TODO: move to common header?

      typedef unsigned size_type;
      typedef unsigned param_type;
      typedef unsigned stride_type;

      //-----| bool_vector

      template< bool...Bools >
      using bool_vector = integral::vector< bool, Bools... >;

      //-----| index_vector

      template< index_type... Indices >
      using index_vector = integral::vector< index_type, Indices... >;

      //-----| size_vector

      template< size_type... Sizes >
      using size_vector = integral::vector< size_type, Sizes... >;

      //-----| stride_vector

      template< size_type... Strides >
      using stride_vector = integral::vector< stride_type, Strides... >;

      namespace helpers
      {
	//---| stride_sequence

	namespace
 	{
	  template< typename, typename > struct stride_sequence_recursion { /* unspecified */ };

	  template< stride_type...Strides >
	  struct stride_sequence_recursion< integral::vector< stride_type, Strides... >, integral::vector< size_type > >
	  {
	    typedef stride_vector< Strides... > type;
	  };

	  template< stride_type...Strides, size_type...Sizes >
	  class stride_sequence_recursion< integral::vector< stride_type, Strides... >, integral::vector< size_type, Sizes... > >
	  {
	      typedef typename integral::pop_front< integral::vector< size_type, Sizes... > > stripped;

	      static const stride_type new_stride = integral::pop_back< integral::vector< stride_type, Strides... > >::value * stripped::value;

	    public:

	      typedef typename stride_sequence_recursion< integral::vector< stride_type, Strides..., new_stride >, typename stripped::tail >::type type;
	  };
	}

	template< typename > struct stride_sequence { /* unspecified */ };

	template< size_type... Sizes >
	struct stride_sequence< integral::vector< size_type, Sizes... > >
	{
	  private:
	    typedef typename integral::reverse< integral::vector< size_type, Sizes... > >::type reverse_sizes;
	    typedef typename stride_sequence_recursion< integral::vector< stride_type, 1 >
						      ,  reverse_sizes >::type reverse_result;

	  public:
	    typedef typename integral::reverse< reverse_result >::type type;
	};

      } // of helpers::

    }
  }
}
