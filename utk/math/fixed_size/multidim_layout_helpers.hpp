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

	template< typename > struct stride_sequence { /* unspecified */ };

	template< size_type... Sizes >
	class stride_sequence< meta::integral::vector< size_type, Sizes... > >
	{
	    // strip 'last' stride (in advance)
	    typedef typename meta::integral::pop_front< meta::integral::vector< size_type, Sizes... > >::tail tail;
	    // reverse to get stride sequences with the last stride always 1 (could be the first index, this choice is arbitrary)
	    typedef typename meta::integral::reverse< tail >::type reverse_tail;

	    typedef typename meta::integral::accumulate< reverse_tail
						       , meta::integral::multiply< stride_type, stride_type >
						       , 1
						       >::type reverse_result;
	  public:
	    // compensate above reverse
	    typedef typename meta::integral::reverse< reverse_result >::type type;
	};

	//---| total_size

	// TODO: tests
	template< typename SizeVector, typename StrideVector >
	struct total_size
	{
	  static constexpr size_type value = meta::integral::pop_front< SizeVector >::value
					     * meta::integral::at< StrideVector, 0 >::value;
	};

	// scalar case - has one elemnet!
	template< >
	struct total_size< size_vector< >, stride_vector< > >
	{ static constexpr size_type value = 1; };

      } // of helpers::
    } // of fixed_size::
  } // of math::
} // of utk::
