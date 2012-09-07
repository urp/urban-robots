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
# include <type_traits>

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


      //:::| algorithms

      //---| equal_recursion

      namespace
      {
	template< typename, typename, typename > class equal_recursion { /* unspecified */ };

	// terminate
	template< typename T, bool...Result >
	class equal_recursion< vector< T >, vector< T >, vector< bool, Result... > >
	{
	  public:
	    typedef vector< bool, Result... > type;
	};

	// compare -> continue
	template< typename T, T...A, T...B, bool...Result >
	class equal_recursion< vector< T, A... >, vector< T, B... >, vector< bool, Result... > >
	{
	    typedef integral::pop_front< vector< T, A... > > pop_A;
	    typedef integral::pop_front< vector< T, B... > > pop_B;
	  public:
	    typedef typename equal_recursion< typename pop_A::tail, typename pop_B::tail
					      , vector< bool, Result..., pop_A::value == pop_B::value >
					      >::type type;
	};

      } // of <anonymous>::

      //---| equal

      template< typename, typename > struct equal { /* unspecified */ };

      template< typename T, T...A, T...B >
      struct equal< vector< T, A... >, vector< T, B... > >
      {
	typedef typename equal_recursion< vector< T, A... >, vector< T, B... >, vector< bool > >::type type;
      };

      //---| remove_false

      namespace
      {
	template< typename, typename, typename >
	class remove_false_recursion	{ /* unspecified */ };

	// terminate
	template< typename T, T...NewValues >
	class remove_false_recursion< vector< bool >
				      , vector< T, NewValues... >
				      , vector< T >
				      >
	{
	  public:
	    typedef vector< T, NewValues... > type;
	};

	// remove if UnpackedIndex!=UnpackedSize -> continue
	// TODO: replace UnpackedIndex/Size by helpers::pop_front
	template< bool...Predicates, typename T, T... NewValues, T...OldValues >
	class remove_false_recursion< vector< bool, Predicates... >
				     , vector< T, NewValues... >
				     , vector< T, OldValues... >
				     >
	{
	    typedef integral::pop_front< vector< bool, Predicates... > > predicates;
	    typedef integral::pop_front< vector< T, OldValues... > > old_values;
	  public:
	    typedef typename std::conditional< predicates::value
					       , typename remove_false_recursion< typename predicates::tail
										 , vector< T, NewValues... , old_values::value >
										 , typename old_values::tail
										 >::type
					       , typename remove_false_recursion< typename predicates::tail
										 , vector< T, NewValues... >
										 , typename old_values::tail
										 >::type
					       >::type type;
	};

      } // of <anonymous>::

      template< typename, typename >  struct remove_false { /* unspecified */ };

      template< bool...Predicates, typename T, T...Values >
      struct remove_false< vector< T, Values... >, vector< bool, Predicates... > >
      {
	static_assert( sizeof...(Predicates) == sizeof...(Values), "Size of packs Predicates and Values must agree." );
	typedef typename remove_false_recursion< vector< bool, Predicates... >, vector< T >, vector< T, Values... > >::type type;
      };

      //---| inner_product

      //-----|terminate
      template< typename VectorA >
      static const typename VectorA::value_type inner_product( )
      { return 0; }

      //-----|accumulate
      template< typename VectorA, typename HeadTypeB, typename...TailTypesB >
      static const typename VectorA::value_type inner_product( HeadTypeB b_head, TailTypesB... b_tail )
      {
	static_assert( std::is_convertible< HeadTypeB, typename VectorA::value_type >::value
		       , "type of coordinates must be convertible to VectorA::value_type."
		       );

	typedef integral::pop_front< VectorA > A;

	return typename VectorA::value_type(b_head) * A::value + inner_product< typename A::tail >( b_tail... );
      }




    } // of integral::
  } // of math::
} // of utk::
