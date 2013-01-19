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
				//-----use slice_layout
        //-----TODO: custom iteration schemes defined by template parameter

				template < typename Interface
								 , typename CurrentIndexVector = typename meta::integral::make_uniform_vector< index_type, Interface::layout::order, 0 >::type
								 >
				class static_iterator_base
				{
						static_assert( std::is_same< typename CurrentIndexVector::value_type, index_type >::value
 												 , "CurrentIndexVector must contain indices of index_type.");

          public:

            //:::| iteration information |:::::::::::::::::::::::::::::/

            typedef CurrentIndexVector old_index_vector;

            typedef typename std::conditional< (Interface::layout::order > 0)
                                             , CurrentIndexVector
                                               // remove dummy index
                                             , index_vector< >
                                             >::type current_indices;

          private:

						//:::| static value interface |::::::::::::::::::::::::::::/

						typedef slice_layout< typename Interface::layout, current_indices > value_layout;

            // use unmanaged storage to prevent unintentional allocations and copies
            typedef typename Interface::unmanaged_interface unmanaged;

            typedef typename change_layout< unmanaged, value_layout >::type value_interface;
						typedef typename value_interface::storage_type value_storage_type;

					public:


						//:::| container and value types |:::::::::::::::::::::::::/

						typedef value_interface value_type;

						//:::| storage interface |:::::::::::::::::::::::::::::::::/

						typename value_interface::storage_type storage;

						//:::| constructors |::::::::::::::::::::::::::::::::::::::/

						//---| constructor with storage_type
						static_iterator_base( const typename Interface::unmanaged_interface::storage_type& other_storage )
						: storage( other_storage )  { }

						//---| copy constuctor
						template< typename OtherInterface, typename OtherIndexVector >
						static_iterator_base( const static_iterator_base< OtherInterface, OtherIndexVector >& other )
						: storage( other.storage )  { }

						//:::| dereference operator |::::::::::::::::::::::::::::::/

						value_interface operator*() const
						{ return value_interface( storage ); }

						//:::| comparison operators |::::::::::::::::::::::::::::::/

						template< typename OtherInterface, typename OtherIndexVector >
						bool operator==( const static_iterator_base< OtherInterface, OtherIndexVector >& other ) const
						{
							return CurrentIndexVector::size == OtherIndexVector::size
                     and meta::integral::all< typename meta::integral::equal< OtherIndexVector, CurrentIndexVector >::type >::value
                     and storage.ptr() == other.storage.ptr();
						}

						template< typename OtherInterface, typename OtherIndexVector >
						bool operator!=( const static_iterator_base< OtherInterface, OtherIndexVector >& other ) const
						{ return not operator==( other ); }


				}; // of static_iterator_base<>



				template < typename Interface
								 , typename CurrentIndexVector = typename meta::integral::make_uniform_vector< index_type, Interface::layout::order, 0 >::type
								 >
				class static_iterator : public static_iterator_base< Interface, CurrentIndexVector >
        {
            typedef static_iterator_base< Interface, CurrentIndexVector > base;
            typedef static_iterator< Interface, CurrentIndexVector > type;
          public:

						//:::| constructors |::::::::::::::::::::::::::::::::::::::/

						//---| constructor with Interface
						static_iterator( const Interface& inter )
						: base( inter.storage )
            { std::cerr << "multidim::static_iterator (" << typename Interface::storage_tag() << " interface) | indices " << typename base::current_indices()
              << " other" << inter.storage << " new "
              << base::storage << std::endl;
            }

						//---| constructor with storage_type
						static_iterator( const typename Interface::unmanaged_interface::storage_type& other_storage )
						: base( other_storage )
            { std::cerr << "multidim::static_iterator (" << typename Interface::storage_tag() << " storage) | indices " << typename base::current_indices()
              << " other" << other_storage << " new "
              << base::storage << std::endl;
            }

						//---| copy constuctor

						static_iterator( const type& other )
						: base( other.storage )
       	    { std::cerr << "multidim::static_iterator (" << typename Interface::storage_tag() << " copy) | indices " << typename base::current_indices()
                        << " other" << other.storage << " new "
                        << base::storage << std::endl;
            }

						template< typename OtherInterface, typename OtherIndexVector >
						static_iterator( const static_iterator< OtherInterface, OtherIndexVector >& other )
						: base( other.storage )
       	    { std::cerr << "multidim::static_iterator (" << typename Interface::storage_tag() << " copy other) | indices " << typename base::current_indices()
                        << " other" << other.storage << " new "
                        << base::storage << std::endl;
            }


            //:::| derived iterator types |::::::::::::::::::::::::::::::::::::/

						static constexpr bool use_random_access_impl = 0;// TODO: 1 if is_sorted< value_layout::sizes && strides cover continuous memory range

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
									 , typename helpers::advance_digits< typename base::current_indices
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
						{ return base::operator==( other ); }

						template< typename OtherInterface, typename OtherIndexVector >
						bool operator!=( const static_iterator< OtherInterface, OtherIndexVector >& other ) const
						{ return base::operator!=( other ); }

        };

				template< typename Interface >
				class make_static_end_iterator
				{
            typedef typename std::conditional< (Interface::layout::order > 0)
                                             , typename helpers::end_iterator_indices< typename Interface::layout::sizes >::type
                                               // add dummy index - should be ignored by
                                             , index_vector< 0 >
                                             >::type end_iterator_index_vector;

            typedef Interface end_iterator_interface;

          public:

            typedef static_iterator< end_iterator_interface, end_iterator_index_vector > type;
        };


        //---| static_iterator (zero_order)
				template < typename Interface >
				class static_iterator< Interface, meta::integral::vector< index_type > >
        : public static_iterator_base< Interface, index_vector< > >
				{
            typedef static_iterator_base< Interface, index_vector< > > base;
            typedef static_iterator< Interface, index_vector< > > type;

            typedef typename make_static_end_iterator< Interface >::type end_iterator;

          public:
						//:::| constructors |::::::::::::::::::::::::::::::::::::::/

						//---| constructor with storage_type
						static_iterator( const Interface& inter )
						: base( inter.storage )
            { std::cerr << "multidim::static_iterator (" << typename Interface::storage_tag() << " interface) | END indices " << typename base::current_indices()
              << " other" << inter.storage << " new "
              << base::storage << std::endl;
            }

						//---| copy constuctor
						static_iterator( const type& other )
						: base( other.storage )
       	    { std::cerr << "multidim::static_iterator (" << typename Interface::storage_tag() << " copy) | END indices " << typename base::current_indices()
                        << " other" << other.storage << " new "
                        << base::storage << std::endl;
            }

						template< typename OtherInterface, typename OtherIndexVector >
						static_iterator( const static_iterator< OtherInterface, OtherIndexVector >& other )
						: base( other.storage )
       	    { std::cerr << "multidim::static_iterator (" << typename Interface::storage_tag() << " copy other) | END indices " << typename base::current_indices()
                        << " other" << other.storage << " new "
                        << base::storage << std::endl;
            }


						//:::| increment operator |::::::::::::::::::::::::::::::::/

						end_iterator next() const
						{ return end_iterator( base::storage ); }

						//:::| decrement operator |::::::::::::::::::::::::::::::::/
						// TODO: !!! CHECK for underrun ( mark rend() )

						end_iterator previous() const
						{ return end_iterator( base::storage ); }

						template< typename OtherInterface, typename OtherIndexVector >
						bool operator==( const static_iterator< OtherInterface, OtherIndexVector >& other ) const
						{ return base::operator==( other ); }

						template< typename OtherInterface, typename OtherIndexVector >
						bool operator!=( const static_iterator< OtherInterface, OtherIndexVector >& other ) const
						{ return base::operator!=( other ); }


				}; // of static_iterator<>

      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
