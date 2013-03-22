/***************************************************************************
 *            surface-generators.h
 *
 *  Fri Jan 28 14:37:40 2011
 *  Copyright  2011  Peter Urban
 *  <s9peurba@stud.uni-saarland.de>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

# pragma once

# include "common.hpp"

# include "surface/generators.hpp"


# include <boost/lexical_cast.hpp>

# include <fstream>

# include <sstream>

# define DBG_FLAT_PDM_FILE_READER
//# define DBG_FLAT_PDM_FILE_READER_VERTEX_SAMPLE
//# define DBG_FLAT_PDM_FILE_READER_TEXTURE_SAMPLE

namespace flat
{
  //----| PdmFileReader

  template< typename Surface >
  class PdmFileReader
  {
    public:

      struct unknown_magic_number_exception : public std::exception
      {
        std::string m_magic_number, m_file;

        unknown_magic_number_exception( const std::string& magic_number, const std::string& file )
        : m_magic_number( magic_number ), m_file( file ) {  }

        virtual ~unknown_magic_number_exception() throw() { };

        const char* what() const throw()
        { return std::string( "unknown magic number \"" + m_magic_number + "\" in file \"" + m_file + "\"" ).c_str(); }
      };

    private:

      void read_file_header( std::istream& stream );

      void read_sample( std::istream& stream, const std::shared_ptr< Surface >&, size_t ) const;

    public:

      std::string   path;

      size_pair vertex_field_size;


      PdmFileReader() = delete;

      PdmFileReader( const PdmFileReader& ) = delete;

      PdmFileReader( const std::string& path ) throw( unknown_magic_number_exception );

      std::shared_ptr< Surface > operator() ();

      std::string   get_name() const { return path; }
  };

}

//==============================================================================
// IMPLEMENTATION

template< typename Surface >
flat::PdmFileReader< Surface >::PdmFileReader( const std::string& path ) throw( unknown_magic_number_exception )
: path( path ), vertex_field_size{ 0, 0 }
{ }

template< typename Surface >
void flat::PdmFileReader< Surface >::read_file_header( std::istream& stream )
{
  std::string   token;

  // check magic number
  stream >> token;
  if( token != "P9" )
  {
    throw unknown_magic_number_exception( token, path );
  }

  size_pair field_size{ 0, 0 };
  // read grid dimensions
  stream >> token >> token >> get<1>( vertex_field_size ) >> get<0>( vertex_field_size ) >> token;

  # if defined DBG_FLAT_PDM_FILE_READER
  std::clog << "flat::PdmFileReader< Surface >::PdmFileReader\t|" << " size (" << get<0>( vertex_field_size ) << ',' << get<1>( vertex_field_size ) << ')' << std::endl;
  # endif

  assert( get<0>( vertex_field_size ) > 1 && get<1>( vertex_field_size ) > 1 );

  stream.ignore( 256, '\n' );

}

template< typename Surface >
void flat::PdmFileReader< Surface >::read_sample( std::istream& stream, const std::shared_ptr< Surface >& surface, size_t index ) const
{
  std::string token;
  location_t                          vertex_location;
  vertex_texture_coord_t::value_type  vertex_texture_coordinate;

  std::getline( stream, token, '\n' );

  std::istringstream ss( token );

  ss >> vertex_location[0] >> vertex_location[1] >> vertex_location[2];

  // skip color info
  ss >> token >> token >> token;
  //ss >> texture_color[0] >> texture_color[1] >> texture_color[2];

  // set vertex info in surface

  vertex_texture_coordinate[0] = ( index % get<0>( vertex_field_size ) ) / ( get<0>(vertex_field_size) - 1. );
  vertex_texture_coordinate[1] = ( index / get<0>( vertex_field_size ) ) / ( get<1>(vertex_field_size) - 1. );

  typename Surface::vertex_handle vertex = surface->vertex( index );
  vertex.set_location( vertex_location );
  vertex.set_texture_coordinate( vertex_texture_coordinate );

  # if defined DBG_FLAT_PDM_FILE_READER_VERTEX_SAMPLE
  std::clog << "flat::PdmFileReader< Surface >()\t| " << " sample " << index
            << current_vertex  << std::endl;
  # endif

}


template< typename Surface >
std::shared_ptr< Surface > flat::PdmFileReader< Surface >::operator() ( )
{
  # if defined DBG_FLAT_PDM_FILE_READER
  std::clog << "flat::PdmFileReader< Surface >::PdmFileReader\t|" << " path \"" << path << '\"' << std::endl;
  # endif

  size_t index = 0;

  std::ifstream stream;

  stream.exceptions( std::ifstream::failbit | std::ifstream::badbit );

  stream.open( path.c_str() );

  read_file_header( stream );

  const size_t num_vertices = get<0>( vertex_field_size ) * get<1>( vertex_field_size );

  std::shared_ptr< Surface > surface = Surface::create_with_size( num_vertices );

  do { read_sample( stream, surface, index ); }
  while( ++index < num_vertices );

  stream.close();

  flat::SimpleRectlinearTriangulator triangulator( vertex_field_size );

  triangulator( surface );

  return surface;
}
