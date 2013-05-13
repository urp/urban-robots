//buffer_data.hpp
//Copyright (C) 2006-2013  Peter Urban (peter.urban@s2003.tu-chemnitz.de)
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

# pragma once

# include <iostream>

# include <boost/multi_array/multi_array_ref.hpp>

# include "utk/vecn.h"


namespace uv
{
  //supplies discrete or interpolated values
  template< typename T
          , size_t Dim
          , size_t Cmp = 1
          , typename ValueType = utk::vecn< T, Cmp >
          >
  class buffer_data : public boost::multi_array_ref< T, Dim + 1 >
  {
      static_assert( Dim > 0, "Dimensions must be larger than 0." );
      static_assert( Cmp > 0, "Number of Components must be larger than 0." );

      static_assert( ValueType::num_components() == Cmp, "number of components in ValueType must agree with Cmp." );

      // TODO: declare as template
      friend std::ostream& operator<< ( std::ostream&, const buffer_data< T, Dim, Cmp, ValueType >& );

    public:

      static constexpr size_t num_dimensions() { return Dim; };

      static constexpr size_t num_components() { return Cmp; }

      typedef boost::multi_array_ref< T, Dim + 1 > array_base;

      typedef ValueType value_type;

      static_assert( std::is_same< typename value_type::value_type, typename array_base::element_type >::value
                   , "buffer_data::element_type must match buffer_data::value_type::value_type " );

      typedef boost::shared_ptr< std::vector< T > > pointer_type;

      typedef typename array_base::index index_type;

      // TODO: write interface
      //typedef boost::signal< void ( buffer_data& ) > data_changed_signal_type;

    private:

      pointer_type m_data_pointer;

    public:

      // TODO: check memory

      template< typename ExtentList >
      buffer_data( const pointer_type& pointer, ExtentList extents )
      : array_base( pointer ), m_data_pointer( pointer )
      {
        std::clog << "uv::buffer_data::buffer_data\t|"
                  << "dimensions " << num_dimensions()
                  << "components " << num_components() << std::endl;

        assert( array_base::shape()[ array_base::num_dimensions() ] == Cmp );
      }

      //---| copy constructor

      /*buffer_data( const buffer_data< T, Dim, Cmp, ValueType >& other )
      : m_array_ref( other.data(), other.shape() ), m_data( other.data() )
      { }*/

      template< typename OtherValueType = ValueType >
      buffer_data( const buffer_data< T, Dim, Cmp, OtherValueType >& other )
      : array_base( other.raw_data(), other.shape() ), m_data_pointer( other.data() )
      { }

      ~buffer_data() { }

      const pointer_type& data() const
      {
        return m_data_pointer;
      }

      const pointer_type& raw_data() const
      {
        return array_base::data();
      }

      /*
      template< typename... CoordTypes >
      ValueType operator()( CoordTypes... indices ) const
      {
        static_assert( sizeof...( CoordTypes ) == Dim, "coordinate dimension mismatch (last index (equals Cmp dimension Dim) must not be provided )" );
        return ValueType( &array_base::operator() ( { indices..., Cmp } ) );
      }

      template< typename IndexList >
      ValueType operator()( IndexList indices ) const
      {
        assert( indices.size() == Dim );
        indices.push_back( Cmp );

        return ValueType( &array_base::operator() ( indices ) );
      }
      */

  }; // of buffer_data<>

} // of ::uv::
