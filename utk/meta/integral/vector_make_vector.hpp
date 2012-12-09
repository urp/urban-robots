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

# include "utk/meta/vector.hpp"
# include "utk/meta/integral/vector.hpp"
# include "utk/meta/integral/vector_algorithms.hpp"


namespace utk
{
  namespace meta
  {
    namespace integral
    {
      //:::| vector creation |:::::::::::::::::::::::::::::::::::::::::/

      //---| make_vector (convert value type)

      template< typename T, typename Vector >
      struct make_vector { /* uspecified */ };

      template< typename T, typename T2, T2...Values >
      struct make_vector< T, vector< T2, Values... > >
      {
	typedef vector< T, T(Values)... > type;
      };

      //---| make_vector
      //-----(convert from meta::vector)
      //-----expects static constexpr ::value in every vector element

      template< typename T, typename...Types >
      struct make_vector< T, meta::vector< Types... > >
      {
	typedef vector< T, T(Types::value)... > type;
      };

      //---| make_uniform_vector

      template< typename T, index_type ElementsLeft, T Value >
      struct make_uniform_vector
      {
	typedef typename push_back< typename make_uniform_vector< T, ElementsLeft-1 , Value >::type
				  , constant< T, Value >
				  >::type type;
      };

      template< typename T, T Value >
      struct make_uniform_vector< T, 0, Value >
      {
	typedef vector< T > type;
      };

      //---| make_position_index_vector

      template< typename T, size_type Size >
      class make_position_index_vector
      {
	  typedef typename meta::integral::make_uniform_vector< T, Size-1, 1 >::type ones;

	public:

	  typedef typename meta::integral::accumulate< ones, meta::integral::add< index_type, index_type >, 0 >::type type;
      };

      template< typename T >
      struct make_position_index_vector< T, 0 >
      {
	  typedef vector< index_type > type;
      };

    } // of integral::
  } // of meta::
} // of utk::
