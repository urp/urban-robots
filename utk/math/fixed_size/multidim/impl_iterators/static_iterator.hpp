/*  static_permutation_iterator.hpp - Copyright Peter Urban 2012

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

# include <type_traits>

# include "utk/math/fixed_size/multidim/impl_slice_layout/slice_layout.hpp"
# include "utk/math/fixed_size/multidim/impl_interface/change_layout.hpp"

# include "utk/math/fixed_size/multidim/impl_iterators/static_iterator_helpers.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {

				//---| static_iterator
				//---| use slice_layout

				template < typename Interface
								 , typename CurrentIndexVector = typename meta::integral::make_uniform_vector< index_type, Interface::layout::order, 0 >::type
								 >
				class static_iterator
				{
						static_assert( std::is_same< typename CurrentIndexVector::value_type, index_type >::value
 												 , "CurrentIndexVector must contain indices of index_type.");

						//:::| static value interface |::::::::::::::::::::::::::::/

						typedef slice_layout< typename Interface::layout, CurrentIndexVector  > value_layout;
						typedef typename change_layout< typename Interface::reference_interface, value_layout >::type value_interface;
						typedef typename value_interface::storage_interface value_storage_interface;

					public:

						//:::| iteration information |:::::::::::::::::::::::::::::/

						typedef CurrentIndexVector current_indices;

						//:::| container and value types |:::::::::::::::::::::::::/

						typedef value_interface value_type;

						//:::| iterator types |::::::::::::::::::::::::::::::::::::/

						static constexpr bool use_random_access_impl = 0;// TODO: 1 if is_sorted< value_layout::sizes && strides cover managed memory

						template< index_type IndexDelta, int impl  >
						struct random_access_iterator_impl { /* unspecified */ };

						//---| random access iterator ( general implementation )
						//-----!enabled if other impl is not applicable!
						//-----directly count through the indices

						template< index_type IndexDelta >
						struct random_access_iterator_impl< IndexDelta, 0 >
						{
							typedef static_iterator< Interface
										 // TODO: only implemented for IndexDelta +/-1 and 0
									 , typename helpers::advance_digits< current_indices
														 , typename Interface::layout::sizes
														 , IndexDelta
														 >::type
									 > type;
						};

						/*---| random access iterator ( index_to_indices implementation )
						//-----!enabled if other impl is not applicable!
						//-----directly count through the indices

						template< index_type IndexDelta >
						struct random_access_iterator_impl< IndexDelta, 1 >
						{
							static constexpr stride_type linear_index = value_layout::static_offset();
							typedef static_iterator< Interface
									 , typename helpers::index_to_indices< typename Interface::layout::strides
												 , linear_index + IndexDelta
												 >::type
									 > type;
						};*/

						//---| random access iterator
						template< index_type IndexDelta >
						using random_access_iterator = typename random_access_iterator_impl< IndexDelta, use_random_access_impl >::type;

						//---| forward iterator
						typedef random_access_iterator<  1 > forward_iterator;

						//---| reverse iterator
						typedef random_access_iterator< -1 > reverse_iterator;


						//:::| storage interface |:::::::::::::::::::::::::::::::::/

						typename value_interface::storage_interface storage;

						//:::| constructors |::::::::::::::::::::::::::::::::::::::/

						//---| constructor with storage_interface
						static_iterator( const Interface& inter )
						: storage( inter.storage )  { }

						//---| copy constuctor
						template< typename OtherInterface, typename OtherIndexVector >
						static_iterator( const static_iterator< OtherInterface, OtherIndexVector >& other )
						: storage( other.storage )  { }

						//:::| dereference operator |::::::::::::::::::::::::::::::/

						value_interface operator*() const
						{ return value_interface( storage ); }

						//:::| increment operator |::::::::::::::::::::::::::::::::/

						forward_iterator next() const
						{ return forward_iterator( *this ); }

						//:::| decrement operator |::::::::::::::::::::::::::::::::/
						// TODO: !!! CHECK for underrun ( mark rend() )

						reverse_iterator previous() const
						{ return reverse_iterator( *this ); }

						//:::| comparison operators |::::::::::::::::::::::::::::::/

						template< typename OtherInterface, typename OtherIndexVector >
						bool operator==( const static_iterator< OtherInterface, OtherIndexVector >& other ) const
						{
							assert( storage.ptr() == other.storage.ptr() );
							return meta::integral::all< typename meta::integral::equal< OtherIndexVector, CurrentIndexVector >::type >::value;
						}

						template< typename OtherInterface, typename OtherIndexVector >
						bool operator!=( const static_iterator< OtherInterface, OtherIndexVector >& other ) const
						{ return not operator==( other ); }

				}; // of static_iterator<>

				template< typename Interface >
				struct make_static_end_iterator
				{
						typedef static_iterator< Interface
								 , typename helpers::end_iterator_indices< typename Interface::layout::sizes >::type
								 > type;
				};

      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
