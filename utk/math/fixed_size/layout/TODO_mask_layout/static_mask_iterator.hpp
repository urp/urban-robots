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

#include <type_traits>

# include "utk/meta/integral/integral.hpp"
# include "utk/meta/vector_transform.hpp"


# include "utk/math/fixed_size/multidim/impl_layout/layout.hpp"

# pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace multidim
      {

	//!!!TODO: create mask layout use code fragments from below


	namespace /* <anonymous> */
	{
	  template< typename SizeVector >
	  struct default_iteration_index_vectors	{ /* unspecified */ };

	  template< size_type...Sizes >
	  struct default_iteration_index_vectors< meta::integral::vector< size_type, Sizes... > >
	  {
	    typedef meta::vector< typename meta::integral::make_position_index_vector< index_type, Sizes >::type... > type;
	  };

	  template< typename IterationIndexVectors >
	  struct make_iteration_mask
	  {
	    // find empty vectors
	    template< typename IntegralVector >
	    using is_empty_vector = std::is_same< IntegralVector, meta::integral::vector< index_type > >;
	    typedef typename meta::transform< IterationIndexVectors, meta::function<is_empty_vector> >::type iteration_mask;
	    // convert to meta::integral::vector<bool,...>
	    typedef typename meta::integral::make_vector< bool, iteration_mask >::type type ;
	  };

	} // of <anonymous>::

	//---| static_mask_iterator

	template < typename Interface
		 , typename CurrentIterationIndices
		 , typename IterationIndices = typename default_iteration_index_vectors< typename Interface::sizes >::type >
	class static_mask_iterator
	{
	    typedef typename make_iteration_mask< IterationIndexVectors >::type iteration_mask;

	    /*:::| static value interface |::::::::::::::::::::::::::::/

	    typedef typename fix_index< typename base::parent_layout, Index, IndexValue >::type value_layout;
	    typedef typename change_layout< typename base::parent_interface, value_layout >::type value_interface;
	    typedef typename value_interface::storage_interface value_storage_interface;
	    */
	  public:

	    //:::| container and value types |:::::::::::::::::::::::::/

	    typedef value_interface value_type;

	    //:::| iteration information |:::::::::::::::::::::::::::::/

	    static constexpr ptrdiff_t index_value = IndexValue;

	    //:::| iterator types |::::::::::::::::::::::::::::::::::::/

	    //---| random access iterator
	    template< index_type NewIndexValue >
	    using random_access_iterator = static_iterator< Interface , Index, NewIndexValue >;

	    //---| forward iterator
	    typedef random_access_iterator< IndexValue + 1 > forward_iterator;

	    //---| reverse iterator
	    typedef random_access_iterator< IndexValue - 1 > reverse_iterator;

	    //:::| constructors |::::::::::::::::::::::::::::::::::::::/

	    //---| constructor with storage_interface
	    static_iterator( const Interface& interface )
	    : base( interface )  { }

	    //---| copy constuctor
	    template< ptrdiff_t OtherIndexValue >
	    static_iterator( const static_iterator< Interface, Index, OtherIndexValue >& other )
	    : base( other )  { }

	    //:::| iterator interface
	    // TODO: ask layout for offset
	    value_interface operator*()
	    { return value_interface( value_storage_interface( base::storage.ptr() ) ); }

	    forward_iterator increment() const
	    { return forward_iterator( *this ); }

	    // TODO: !!! CHECK for underrun ( mark rend() )
	    reverse_iterator decrement() const
	    { return reverse_iterator( *this ); }

	    template< typename OtherLayout, ptrdiff_t OtherIndexValue >
	    bool operator==( const static_iterator< OtherLayout, Index, OtherIndexValue >& other ) const
	    { return OtherIndexValue == IndexValue && base::operator==(other); }

	    template< typename OtherLayout, ptrdiff_t OtherIndexValue >
	    bool operator!=( const static_iterator< OtherLayout, Index, OtherIndexValue >& other ) const
	    { return not operator==( other ); }

	}; // of static_iterator<>
      } // of multidim::
    } // of fixed_size::
  } // of math::
} // of utk::
