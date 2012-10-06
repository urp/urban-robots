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


# include "utk/meta/integral/integral.hpp"

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {

      //using meta::integral::index_type;
      typedef ptrdiff_t index_type;
      // TODO: move to common header?

      typedef size_t size_type;
      typedef ptrdiff_t stride_type;

      //-----| bool_vector

      template< bool...Bools >
      using bool_vector = meta::integral::vector< bool, Bools... >;

      //-----| index_vector

      template< index_type... Indices >
      using index_vector = meta::integral::vector< index_type, Indices... >;

      //-----| size_vector

      template< size_type... Sizes >
      using size_vector = meta::integral::vector< size_type, Sizes... >;

      //-----| stride_vector

      template< size_type... Strides >
      using stride_vector = meta::integral::vector< stride_type, Strides... >;

      namespace helpers
      {
	//---| stride_sequence

	namespace
 	{
	  template< typename, typename > struct stride_sequence_recursion { /* unspecified */ };

	  template< stride_type...Strides >
	  struct stride_sequence_recursion< meta::integral::vector< stride_type, Strides... >, meta::integral::vector< size_type > >
	  {
	    typedef stride_vector< Strides... > type;
	  };

	  template< stride_type...Strides, size_type...Sizes >
	  class stride_sequence_recursion< meta::integral::vector< stride_type, Strides... >, meta::integral::vector< size_type, Sizes... > >
	  {
	      typedef typename meta::integral::pop_front< meta::integral::vector< size_type, Sizes... > > stripped;

	      static const stride_type new_stride = meta::integral::pop_back< meta::integral::vector< stride_type, Strides... > >::value * stripped::value;

	    public:

	      typedef typename stride_sequence_recursion< meta::integral::vector< stride_type, Strides..., new_stride >, typename stripped::tail >::type type;
	  };
	}

	template< typename > struct stride_sequence { /* unspecified */ };

	template< size_type... Sizes >
	struct stride_sequence< meta::integral::vector< size_type, Sizes... > >
	{
	  private:
	    typedef typename meta::integral::reverse< meta::integral::vector< size_type, Sizes... > >::type reverse_sizes;

	    typedef typename stride_sequence_recursion< meta::integral::vector< stride_type, 1 >
						      ,  reverse_sizes >::type reverse_result;

	    // strip last stride
	    typedef typename meta::integral::pop_back< reverse_result >::tail reverse_stripped_result;
	  public:
	    typedef typename meta::integral::reverse< reverse_stripped_result >::type type;
	};

	//---| total_size
	// TODO: tests
	template< typename SizeVector, typename StrideVector > struct total_size
	{ static constexpr size_type value = meta::integral::pop_front< SizeVector >::value * meta::integral::at< StrideVector, 0 >::value; };

	// scalar
	template< > struct total_size< size_vector< >, stride_vector< > > { static constexpr size_type value = 1; };

      } // of helpers::


    }
  }
}
