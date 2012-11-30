/*  vector_remove.hpp - Copyright Peter Urban 2012

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

# include "utk/meta/integral/vector.hpp"

# include "utk/meta/integral/vector_functions.hpp"
# include "utk/meta/integral/vector_algorithms.hpp"

# include "utk/meta/integral/vector_make_vector.hpp"

namespace utk
{
  namespace meta
  {
    namespace integral
    {

      //---| remove_false

      template< typename, typename >
      struct remove_false { /* unspecified */ };

      // terminate
      template< typename T >
      struct remove_false< vector< T >, vector< bool > >
      {
	typedef vector< T > type;
      };

      // recurse
      template< typename T, T...Values, bool...Predicates >
      class remove_false< vector< T, Values... >, vector< bool, Predicates... > >
      {
	  typedef pop_front< vector< bool, Predicates... > > predicates;
	  typedef pop_front< vector< T, Values... > > values;

	  typedef typename remove_false< typename values::tail
				       , typename predicates::tail
				       >::type tail;

	public:
	  typedef typename std::conditional< predicates::value
					   , typename push_front< tail, constant< T, values::value > >::type
					   , tail
					   >::type type;
      };

      //---| remove_at

      template< typename Container, index_type Index >  struct remove_at { /* unspecified */ };

      template< typename T, T...Values, index_type Index >
      class remove_at< vector< T, Values... >, Index >
      {
	  static_assert( Index < sizeof...(Values), "Size of packs Predicates and Values must agree." );
	  typedef typename make_uniform_vector< bool, sizeof...(Values), true >::type false_vector;
	  typedef typename assign< false_vector, Index, constant< bool, false > >::type mask_predicate;
	public:
	  typedef typename remove_false< vector< T, Values... >, mask_predicate >::type type;
      };

    } // of integral::
  } // of meta::
} // of utk::
