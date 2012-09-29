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

//# include <array>
# include <type_traits>

# include "utk/math/integral/constant.hpp"
# include "utk/math/integral/vector.hpp"
# include "utk/math/integral/vector_functions.hpp"

namespace utk
{
  namespace math
  {
    namespace integral
    {

      //:::| algorithms

      //---| transform

      template< typename, typename > struct transform { /* unspecified */ };

      template< typename T, typename UnaryScalarOperator >
      struct transform< vector< T >, UnaryScalarOperator >
      {
	typedef vector< typename UnaryScalarOperator::value_type > type;
      };

      template< typename T, T...Input, typename UnaryScalarOperator >
      class transform< vector< T, Input... >, UnaryScalarOperator >
      {
	  typedef pop_front< vector< T, Input... > > input;

	  typedef typename transform< typename input::tail, UnaryScalarOperator >::type results;

	public:
	  typedef typename push_front< results
				       , constant< T, UnaryScalarOperator::template apply< input::value >::value >
				       >::type type;
      };


      //:::| unary operators

      //---| negate ( scalar -> scalar )

      template< typename T >
      struct negate
      {
	typedef decltype( !T() ) value_type;

	template< T Value >
	struct apply
	{ static constexpr value_type value = !Value; };

      };

      //---| negate ( vector -> vector )

      template< typename T, T...Values >
      struct negate< vector< T, Values... > >
      : public transform< vector< T, Values... >, negate< T > >
      {	};

      //---| is_true ( scalar -> scalar )

      template< typename T >
      struct is_true
      {
	typedef bool value_type;

	template< T Value >
	struct apply
	{ static constexpr value_type value = bool( Value ); };

      };

      //---| negate ( vector -> vector )

      template< typename T, T...Values >
      struct is_true< vector< T, Values... > >
      : public transform< vector< T, Values... >, is_true< T > >
      {	};


      //---| binary apply

      template< typename, typename, typename > struct binary_apply { /* unspecified */ };

      template< typename T1, typename T2, typename BinaryScalarOperator >
      struct binary_apply< vector< T1 >, vector< T2 >, BinaryScalarOperator >
      {
	typedef vector< typename BinaryScalarOperator::value_type > type;
      };

      template< typename T1, T1...Values1, typename T2, T2...Values2 , typename BinaryScalarOperator >
      class binary_apply< vector< T1, Values1... >, vector< T2, Values2... >, BinaryScalarOperator >
      {
	  typedef pop_front< vector< T1, Values1... > > input1;
	  typedef pop_front< vector< T2, Values2... > > input2;

	  typedef typename binary_apply< typename input1::tail
					   , typename input2::tail
					   , BinaryScalarOperator
					   >::type results;

	public:
	  typedef typename push_front< results
				       , constant< typename BinaryScalarOperator::value_type
						  , BinaryScalarOperator::template apply< input1::value
											 , input2::value
											 >::value
						  >
				       >::type type;
      };

      //---| accumulate

      template< typename
	      , typename BinaryScalarOperator
	      , typename BinaryScalarOperator::value_type InitialValue = 0
	      >
      struct accumulate { /* unspecified */ };

      // return scalar -> terminate
      template< typename T
	      , typename BinaryScalarOperator
	      , typename BinaryScalarOperator::value_type InitialValue
	      >
      struct accumulate< vector< T >, BinaryScalarOperator, InitialValue >
      {
        typedef typename BinaryScalarOperator::value_type value_type;
	static constexpr value_type value = value_type( InitialValue );
      };

      // accumulate -> continue
      template< typename T
	      , T...Input
	      , typename BinaryScalarOperator
	      , typename BinaryScalarOperator::value_type InitialValue
	      >
      class accumulate< vector< T, Input... >, BinaryScalarOperator, InitialValue >
      {
	  typedef pop_front< vector< T, Input... > > input;
	  typedef accumulate< typename input::tail, BinaryScalarOperator, InitialValue > accum;
	  static constexpr typename accum::value_type old_value = accum::value;

	public:

	  typedef typename BinaryScalarOperator::value_type value_type;
	  static constexpr value_type value = BinaryScalarOperator::template apply< input::value, old_value >::value;
      };


      //:::| binary operators


      //:::::arithmetic

      //---| multiply ( scalar x scalar -> scalar )

      template< typename T1, typename T2 >
      struct multiply
      {
	typedef decltype( T1(1)*T2(1) ) value_type;

	template< T1 Value1, T2 Value2 >
	struct apply
	{
	  static constexpr value_type value = Value1 * Value2;
	};

      };

      //---| multiply ( vector x vector -> vector )

      template< typename T1, T1...Values1, typename T2, T2...Values2 >
      struct multiply< vector< T1, Values1... >, vector< T2, Values2... > >
      : public binary_apply< vector< T1, Values1... >, vector< T2, Values2... >, multiply< T1, T2 > >
      {	};

      //---| add ( scalar x scalar -> scalar )

      template< typename T1, typename T2 >
      struct add
      {
	typedef decltype( T1(1)+T2(1) ) value_type;

	template< T1 Value1, T2 Value2 >
	struct apply
	{
	  static constexpr value_type value = Value1 + Value2;
	};

      };

      //---| add ( vector x vector -> vector )

      template< typename T1, T1...Values1, typename T2, T2...Values2 >
      struct add< vector< T1, Values1... >, vector< T2, Values2... > >
      : public binary_apply< vector< T1, Values1... >, vector< T2, Values2... >, add< T1, T2 > >
      {	};


      //:::::| logical operarators

      //---| conjunction ( scalar x scalar -> scalar )

      template< typename T1, typename T2 >
      struct conjunction
      {
	typedef decltype( T1() && T2() ) value_type;

	template< T1 Value1, T2 Value2 >
	struct apply
	{
	  static constexpr value_type value = Value1 && Value2;
	};
      };

      //---| conjunction ( vector x vector -> vector )

      template< typename T1, T1...Values1, typename T2, T2...Values2 >
      struct conjunction< vector< T1, Values1... >, vector< T2, Values2... > >
      : public binary_apply< vector< T1, Values1... >, vector< T2, Values2... >, conjunction< T1, T2 > >
      {	};


      //:::::| comparison operators

      //---| equal ( scalar x scalar -> scalar )

      template< typename T1, typename T2 >
      struct equal
      {
	typedef decltype( T1()==T2() ) value_type;

	template< T1 Value1, T2 Value2 >
	struct apply
	{
	  static constexpr value_type value = Value1 == Value2;
	};

      };

      //---| equal ( vector x vector -> vector )

      template< typename T1, T1...Values1, typename T2, T2...Values2 >
      struct equal< vector< T1, Values1... >, vector< T2, Values2... > >
      : public binary_apply< vector< T1, Values1... >, vector< T2, Values2... >, equal< T1, T2 > >
      {	};

      //:::| miscellianous

      //---| all ( vector -> scalar )

      template< typename Vector, typename Predicate = is_true< typename Vector::value_type > >
      struct all { /* unspecified */ };

      template< typename T, T...Values, typename Predicate >
      struct all< vector< T, Values... >, Predicate >
      : public accumulate< typename transform< vector< T, Values... >, Predicate >::type
			 , conjunction< typename Predicate::value_type, typename Predicate::value_type >
			 , true
			 >
      {	};

      //---| TODO: any

      //---| reverse

      template< typename > struct reverse { /* unspecified */ };

      template< typename T >
      struct reverse< vector< T > >
      {
	typedef vector< T > type;
      };

      template< typename T, T...Values >
      class reverse< vector< T, Values... > >
      {
	  typedef pop_front< vector< T, Values... > > values;
	  typedef typename reverse< typename values::tail >::type reverse_tail;
	public:
	  typedef typename push_back< reverse_tail, constant< T, values::value > >::type type;
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

      //:::| inner_product

      template< typename, typename > struct inner_product { /* unspecified */ };

      template< typename T1, T1...Values1, typename T2, T2...Values2 >
      struct inner_product< vector< T1, Values1... >, vector< T2, Values2... > >
      {
	typedef typename binary_apply< vector< T1, Values1... >, vector< T2, Values2... >, multiply< T1,T2 > >::type mult;
	typedef accumulate< mult, add< T1, T2 > > accum;
	static constexpr typename accum::value_type value = accum::value;
      };

      //---| inner_product_with_arguments

      //-----|terminate
      template< typename VectorA >
      static const typename VectorA::value_type inner_product_with_arguments( )
      { return 0; }

      //-----|accumulate
      template< typename VectorA, typename HeadTypeB, typename...TailTypesB >
      static const typename VectorA::value_type inner_product_with_arguments( HeadTypeB b_head, TailTypesB... b_tail )
      {
	static_assert( std::is_convertible< HeadTypeB, typename VectorA::value_type >::value
		       , "type of coordinates must be convertible to VectorA::value_type."
		       );

	typedef integral::pop_front< VectorA > A;

	return A::value * typename VectorA::value_type(b_head) + inner_product_with_arguments< typename A::tail >( b_tail... );
      }

    } // of integral::
  } // of math::
} // of utk::
