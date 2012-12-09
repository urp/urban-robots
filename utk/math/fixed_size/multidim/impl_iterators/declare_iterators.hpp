/*  interface.hpp - Copyright Peter Urban 2012

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

# include "utk/math/fixed_size/multidim/impl_iterators/static_iterator.hpp"
# include "utk/math/fixed_size/multidim/impl_iterators/static_index_iterator.hpp"
# include "utk/math/fixed_size/multidim/impl_iterators/dynamic_index_iterator.hpp"

// TODO: make only dependent on "interface_type"

# define UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ITERATORS( interface_type ) 		              \
                                                                                           \
  /*:::| static iterators |:::::::::::::::::::::::::::::::::::*/								            \
                                                                                            \
  /*---| static_iterator */       											                                    \
                                                                                            \
  typedef multidim::static_iterator< interface_type > static_iterator_begin;		            \
                                                                                            \
  typedef typename multidim::make_static_end_iterator< interface_type >::type static_iterator_end; \
                                                                                            \
  static_iterator_begin       begin()	    { return static_iterator_begin(*this); }					\
  const static_iterator_begin begin() const { return static_iterator_begin(*this); }				\
                                                                                            \
  static_iterator_end 	    end() 	{ return static_iterator_end(*this); }						      \
  const static_iterator_end end() const	{ return static_iterator_end(*this); }						  \
                                                                                            \
                                                                                            \
  /*---| static_index_iterator */												                                    \
                                                                                            \
  /* static_index_iterator begin */											                                    \
                                                                                            \
  template< index_type Index >												                                      \
  using static_index_iterator_begin = multidim::static_index_iterator< interface_type, Index, 0 >;					\
                                                                                            \
  template< index_type Index >												                                      \
  using const_static_index_iterator_begin = const multidim::static_index_iterator< interface_type, Index, 0 >;			\
                                                                                            \
  /* static_index_iterator_end */												                                    \
                                                                                            \
  template< index_type Index >												                                      \
  using static_index_iterator_end = multidim::static_index_iterator< interface_type \
                                                                   , Index \
                                                                   , meta::integral::at< typename interface_type::layout::sizes, Index >::value \
                                                                   >;                       \
                                                                                            \
  template< index_type Index >												                                      \
  using const_static_index_iterator_end = const multidim::static_index_iterator< interface_type \
                                                                               , Index \
                                                                               , meta::integral::at< typename interface_type::layout::sizes, Index >::value \
                                                                               >;           \
                                                                                            \
  /*---| begin_index */													                                            \
                                                                                            \
  template< index_type Index >												                                      \
  static_index_iterator_begin<Index> static_begin() { return static_index_iterator_begin< Index >( *this ); }		\
                                                                                            \
  template< index_type Index >												                                      \
  const_static_index_iterator_begin<Index> static_begin() const { return const_static_index_iterator_begin< Index >( *this ); } \
                                                                                            \
  /*---| end_index */													                                              \
                                                                                            \
  template< index_type Index >												                                      \
  static_index_iterator_end<Index> static_end() { return static_index_iterator_end< Index >( *this ); }			\
                                                                                            \
  template< index_type Index >												                                      \
  const_static_index_iterator_end<Index> static_end() const { return const_static_index_iterator_end< Index >( *this ); }	\
                                                                                            \
  /*:::| dynamic iterators |::::::::::::::::::::::::::::::::::*/								            \
                                                                                            \
  /*---| dynamic_index_iterator */											                                    \
                                                                                            \
  /* types */														                                                    \
                                                                                            \
  template< index_type Index >												                                      \
  using index_iterator = const multidim::dynamic_index_iterator< interface_type, Index >;		\
                                                                                            \
  template< index_type Index >												                                      \
  using const_index_iterator = const multidim::dynamic_index_iterator< interface_type, Index >;					\
                                                                                            \
  /*---| begin_index */													                                            \
  template< index_type Index >												                                      \
  index_iterator<Index> begin_index() { return index_iterator< Index >( *this, 0 ); }				\
                                                                                            \
  template< index_type Index >												                                      \
  const_index_iterator<Index> begin_index() const { return const_index_iterator< Index >( *this, 0 ); }			\
                                                                                            \
  /*---| end_index */													                                              \
                                                                                            \
  template< index_type Index >												                                      \
  auto end_index( ) -> index_iterator<Index>										                            \
  {															                                                            \
    constexpr index_type end_index = meta::integral::at< typename interface_type::layout::sizes, Index >::value;				\
    return const_index_iterator< Index >( *this, end_index );								                \
  }															                                                            \
                                                                                            \
  template< index_type Index >												                                      \
  auto end_index( ) const -> const_index_iterator<Index>									                  \
  {															                                                            \
    constexpr index_type end_index = meta::integral::at< typename interface_type::layout::sizes, Index >::value;				\
    return const_index_iterator< Index >( *this, end_index );								                \
  }															                                                            \
                                                                                           \
