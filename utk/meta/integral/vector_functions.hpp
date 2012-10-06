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

# include <array>
# include <iostream>
# include <iomanip>

# include "utk/io/io.hpp"
# include "utk/meta/integral/constant.hpp"
# include "utk/meta/integral/vector.hpp"

namespace utk
{
  namespace meta
  {
    namespace integral
    {

      //:::| sequence manipulators

      //---| push_front
      template< typename, typename > struct push_front { /* unspecified */ };

      template< typename T, T... Values, T Front >
      struct push_front< vector< T, Values... >, constant< T, Front > >
      {
	typedef vector< T, Front, Values... > type;
      };

      //---| push_back

      template< typename, typename > struct push_back { /* unspecified */ };

      template< typename T, T... Values, T Back >
      struct push_back< vector< T, Values... >, constant< T, Back > >
      {
	typedef vector< T, Values..., Back > type;
      };

      //---| pop_front
      //-----splits non-type template sequences

      template< typename > struct pop_front { /* unspecified */ };

      template< typename T, T Unpacked, T...Pack >
      struct pop_front< vector< T, Unpacked, Pack... > >
      {
	static const T value = Unpacked;

	typedef vector< T, Pack... > tail;
      };

      //---| pop_back
      //-----splits non-type template sequences

      template< typename >  struct pop_back { /* unspecified */ };

      // terminate
      template< typename T, T Back >
      struct pop_back< vector< T, Back > >
      {
	static const T value = Back;

	typedef vector< T > tail;
      };

      // pop first value and continue
      template< typename T, T Unpacked , T...Pack >
      class pop_back< vector< T, Unpacked, Pack... > >
      {
	  typedef pop_back< vector< T, Pack... > > popped;

	public:

	  static const T value = popped::value;

	  typedef typename push_front< typename popped::tail, constant< T, Unpacked > >::type tail;
      };

      //:::| vector creators

      //---| make_vector


      template< typename T, typename Vector >
      struct make_vector { /* uspecified */ };

      template< typename T, typename T2, T2...Values >
      struct make_vector< T, vector< T2, Values... > >
      {

	typedef vector< T, T(Values)... > type;
      };


      //---| make_uniform_vector

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

      //---| make_array

      template< typename > struct make_array { /* unspecified */ };

      template< typename T, T...Values >
      struct make_array< vector< T, Values... > >
      {
	typedef std::array< T, sizeof...(Values) > type;

	constexpr static type value = type{ {Values...} };
      };

      //:::| element access

      //---| at

      template< typename, index_type > struct at { /* unspecified */ };

      template< typename T, T Unpacked, T...Pack >
      struct at< vector< T, Unpacked, Pack... >, 0 >
      {
	static const T value = Unpacked;
      };

      template< index_type DimIndex, typename T, T Unpacked, T...Pack >
      struct at< vector< T, Unpacked, Pack... >, DimIndex >
      {
	static_assert( DimIndex < sizeof...(Pack)+1, "Index must be smaller than vector size" );
	typedef T value_type;
	static const T value = at< vector< T, Pack... >, DimIndex-1 >::value;
      };


      //---| assign

      template< typename Vector, index_type Index, typename > struct assign { /* unspecified */ };

      template< typename T, T OldValue, T...OldTail, index_type Index, T NewValue >
      class assign< vector< T, OldValue,OldTail... >, Index, constant<T,NewValue> >
      {
	  static_assert( Index < sizeof...(OldTail)+1, "Index must be smaller than vector size" );

	  typedef typename assign< vector< T, OldTail... >, Index-1, constant< T, NewValue > >::type tail;

	public:

	  typedef typename push_front< tail, constant< T, OldValue > >::type type;
      };

      template< typename T, T OldValue, T...OldTail, T NewValue >
      struct assign< vector< T, OldValue,OldTail... >, 0, constant< T, NewValue > >
      {
	typedef vector< T, NewValue, OldTail... > type;
      };


      //---| concatinate
      template< typename, typename > struct concatinate { /* unspecified */ };

      template< typename T, T... ValuesA, T... ValuesB >
      struct concatinate< vector< T, ValuesA... >, vector< T, ValuesB... > >
      {
	typedef vector< T, ValuesA... , ValuesB... > type;
      };


      //---| io-stream insertion operator

      template< typename T, T...Values >
      std::ostream& operator<<( std::ostream& os, const vector< T, Values... >& vec )
      {
	std::array< T, sizeof...(Values) > arr = make_array< vector< T, Values... > >::value;
	os << '{' << utk::io::sequence_to_stream( os, arr.begin(), arr.end(), "," ) << '}' << std::endl;
	return os;
      }

    } // of integral::
  } // of meta::
} // of utk::
