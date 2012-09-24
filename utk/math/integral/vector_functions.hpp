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
# include "utk/math/integral/constant.hpp"
# include "utk/math/integral/vector.hpp"

namespace utk
{
  namespace math
  {
    namespace integral
    {

      // TODO: bad
      typedef unsigned index_type;

      //:::| data access

      //---| make_uniform_vector

      namespace
      {
	template< typename T, index_type, T, typename > struct make_uniform_recursion { /* unspecified */ };

	template< typename T, T Value, T... Values >
	struct make_uniform_recursion< T, 0, Value, vector< T, Values... > >
	{
	  typedef vector< T, Values... > type;
	};

	template< typename T, index_type ElementsLeft, T Value, T... Values >
	struct make_uniform_recursion< T, ElementsLeft, Value, vector< T, Values... > >
	{
	  typedef typename make_uniform_recursion< T, ElementsLeft-1 , Value, vector< T, Value, Values... > >::type type;
	};
      }

      template< typename T, index_type Size, T Value >
      struct make_uniform_vector
      {
	// TODO: initialize with size and empty vector (gcc-4.7 error)
	typedef typename make_uniform_recursion< T, Size-1, Value, vector< T, Value > >::type type;
      };

      //---| make_array

      template< typename > struct make_array { /* unspecified */ };

      template< typename T, T...Values >
      struct make_array< vector< T, Values... > >
      {
	typedef std::array< T, sizeof...(Values) > type;

	constexpr static type value = type{ {Values...} };
      };

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

      //---| assign_recursion

      namespace
      {
	template< index_type, typename ,typename, typename >
	struct assign_recurse { /* unspecified */ };

	// assign -> terminate
	template< typename T, T NewValue, T Unpacked, T...NewPack, T...OldPack >
	struct assign_recurse< 0
				, constant< T, NewValue >
				, vector< T, NewPack... >
				, vector< T, Unpacked, OldPack... >
				>
	{
	  typedef vector< T, NewPack..., NewValue , OldPack... > type;
	};

	// move value to result -> recurse
	template< typename T, index_type Index, T NewValue, T...NewPack, T Unpacked, T...OldPack  >
	struct assign_recurse< Index, constant< T, NewValue >, vector< T, NewPack... >, vector< T, Unpacked, OldPack... > >
	{ typedef typename assign_recurse< Index-1
					     , constant< T, NewValue >
					     , vector< T, NewPack..., Unpacked >
					     , vector< T, OldPack... >
					     >::type type;
	};

      } // of <anonymous>::

      //---| assign
      template< typename, index_type, typename > struct assign { /* unspecified */ };

      template< typename T, index_type Index, T NewValue, T...OldPack >
      struct assign< vector< T, OldPack... >, Index, constant< T, NewValue > >
      {
	static_assert( Index < sizeof...(OldPack), "Index must be smaller than vector size" );
	typedef typename assign_recurse< Index
					   , constant< T, NewValue >
					   , vector< T >
					   , vector< T, OldPack... >
					   >::type type;
      };

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
  } // of math::
} // of utk::
