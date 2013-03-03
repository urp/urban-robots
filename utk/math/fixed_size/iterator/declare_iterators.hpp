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

# include "utk/math/fixed_size/iterator/fusion/component_iterator.hpp"
# include "utk/math/fixed_size/iterator/fusion/index_iterator.hpp"
# include "utk/math/fixed_size/iterator/stl/index_iterator.hpp"

# define UTK_MATH_FIXED_SIZE_MULTIDIM__DECLARE_ITERATORS( interface_type ) 		              \
                                                                                            \
  /*:::| static iterators |:::::::::::::::::::::::::::::::::::*/								            \
                                                                                            \
  /*---| component_iterator */       											                                  \
                                                                                            \
  typedef iterator::fusion::component_iterator< interface_type > component_iterator_begin;  \
                                                                                            \
  typedef typename iterator::fusion::make_component_end_iterator< interface_type >::type component_iterator_end; \
                                                                                            \
  component_iterator_begin begin()	            { return component_iterator_begin(*this); }	\
  const component_iterator_begin begin()  const { return component_iterator_begin(*this); }	\
                                                                                            \
  component_iterator_end 	     end() 	      { return component_iterator_end(*this); }	      \
  const component_iterator_end end() const	{ return component_iterator_end(*this); }			  \
                                                                                            \
                                                                                            \
  /*---| static_index_iterator */												                                    \
                                                                                            \
  /* static_index_iterator begin */											                                    \
                                                                                            \
  template< index_type Index >												                                      \
  using fusion_index_iterator_begin = iterator::fusion::index_iterator< interface_type, Index, 0 >;					\
                                                                                            \
  template< index_type Index >												                                      \
  using const_fusion_index_iterator_begin = const iterator::fusion::index_iterator< interface_type, Index, 0 >;			           \
                                                                                            \
  /* static_index_iterator_end */												                                    \
                                                                                            \
  template< index_type Index >												                                      \
  using fusion_index_iterator_end = iterator::fusion::index_iterator< interface_type        \
                                                                    , Index                 \
                                                                    , meta::integral::at< typename interface_type::layout::sizes, Index >::value \
                                                                    >;                      \
                                                                                            \
  template< index_type Index >												                                      \
  using const_fusion_index_iterator_end = const iterator::fusion::index_iterator< interface_type \
                                                                                , Index     \
                                                                                , meta::integral::at< typename interface_type::layout::sizes, Index >::value \
                                                                                >;          \
                                                                                            \
  /*---| begin_index */													                                            \
                                                                                            \
  template< index_type Index >												                                      \
  fusion_index_iterator_begin<Index> static_begin() { return fusion_index_iterator_begin< Index >( *this ); }		\
                                                                                            \
  template< index_type Index >												                                      \
  const_fusion_index_iterator_begin<Index> static_begin() const { return const_fusion_index_iterator_begin< Index >( *this ); } \
                                                                                            \
  /*---| end_index */													                                              \
                                                                                            \
  template< index_type Index >												                                      \
  fusion_index_iterator_end<Index> static_end() { return fusion_index_iterator_end< Index >( *this ); }			\
                                                                                            \
  template< index_type Index >												                                      \
  const_fusion_index_iterator_end<Index> static_end() const { return const_fusion_index_iterator_end< Index >( *this ); }	\
                                                                                            \
  /*:::| dynamic iterators |::::::::::::::::::::::::::::::::::*/								            \
                                                                                            \
  /*---| dynamic_index_iterator */											                                    \
                                                                                            \
  /* types */														                                                    \
                                                                                            \
  template< index_type Index >												                                      \
  using stl_index_iterator = iterator::stl::index_iterator< interface_type, Index >;		    \
                                                                                            \
  template< index_type Index >												                                      \
  using const_stl_index_iterator = const iterator::stl::index_iterator< interface_type, Index >;					\
                                                                                            \
  /*---| begin_index */													                                            \
  template< index_type Index >												                                      \
  stl_index_iterator<Index>       begin_index() { return stl_index_iterator< Index >( *this, 0 ); }				\
                                                                                            \
  template< index_type Index >												                                      \
  const_stl_index_iterator<Index> begin_index() const { return const_stl_index_iterator< Index >( *this, 0 ); }			\
                                                                                            \
  /*---| end_index */													                                              \
                                                                                            \
  template< index_type Index >												                                      \
  auto end_index( ) -> stl_index_iterator<Index>										                            \
  {															                                                            \
    constexpr index_type end_index = meta::integral::at< typename interface_type::layout::sizes, Index >::value;				\
    return stl_index_iterator< Index >( *this, end_index );		  						                \
  }															                                                            \
                                                                                            \
  template< index_type Index >												                                      \
  auto end_index( ) const -> const_stl_index_iterator<Index>									                  \
  {															                                                            \
    constexpr index_type end_index = meta::integral::at< typename interface_type::layout::sizes, Index >::value;				\
    return const_stl_index_iterator< Index >( *this, end_index );								                \
  }															                                                            \
                                                                                           \
