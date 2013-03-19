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

# include "surface/tri_surface/tri_surface.hpp"

# include <boost/lexical_cast.hpp>

# include <fstream>

# include <sstream>

# define DBG_FLAT_PDM_FILE_READER
//# define DBG_FLAT_PDM_FILE_READER_VERTEX_SAMPLE
//# define DBG_FLAT_PDM_FILE_READER_TEXTURE_SAMPLE

namespace flat
{
  //----| PdmFileReader

  class PdmFileReader : public RectlinearFieldGenerator, public TextureGenerator
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

      typedef enum { END = 4 }  sample_type_t;
      typedef int   sample_mask_t;

      std::string   m_filename;
      std::ifstream m_stream;

      size_t m_index;

      size_pair m_field_size;

      rgba_color_t                 	texture_color;
      location_t                    vertex_location;
      vertex_texture_coord_t::type  vertex_texture_coordinate;

      void next_sample();

      bool advance_index()  { return ++m_index < ( get<0>(m_field_size) * get<1>(m_field_size) ); }

      bool read_sample();

    public:

      PdmFileReader() = delete;

      PdmFileReader( const PdmFileReader& ) = delete;

      PdmFileReader( const std::string& path ) throw( unknown_magic_number_exception );

      ~PdmFileReader() { m_stream.close(); }

      void operator() ( const std::shared_ptr< TriSurface >& surface );

      std::string   get_name() const { return m_filename; }
  };

}

//==============================================================================
// IMPLEMENTATION


flat::PdmFileReader::PdmFileReader( const std::string& path ) throw( unknown_magic_number_exception )
: RectlinearFieldGenerator( { 0, 0 } ), TextureGenerator( { 0, 0 } )
, m_filename( path ), m_stream()
, m_index( 0 ), m_field_size( 0, 0 ), texture_color( 1. )
{
  m_stream.exceptions( std::ifstream::failbit | std::ifstream::badbit );

  m_stream.open( path.c_str() );

  std::string   token;

  # if defined DBG_FLAT_PDM_FILE_READER
  std::clog << "flat::PdmFileReader::PdmFileReader\t|" << " path \"" << path << '\"' << std::endl;
  # endif

  // check magic number
  m_stream >> token;
  if( token != "P9" )
  {
    m_stream.close();
    throw unknown_magic_number_exception( token, path );
  }

  size_pair field_size{ 0, 0 };
  // read grid dimensions
  m_stream >> token >> token >> get<1>( m_field_size ) >> get<0>( m_field_size ) >> token;

  # if defined DBG_FLAT_PDM_FILE_READER
  std::clog << "flat::PdmFileReader::PdmFileReader\t|" << " size (" << get<0>( m_field_size ) << ',' << get<1>( m_field_size ) << ')' << std::endl;
  # endif

  assert( get<0>( m_field_size ) > 1 && get<1>( m_field_size ) > 1 );

  // resize storage
  m_vertices_size = m_field_size;
  m_texture_size  = m_field_size;

  m_stream.ignore( 256, '\n' );

}


void flat::PdmFileReader::operator() ( const std::shared_ptr< TriSurface >& surface )
{
  assert( num_vertices() == surface->num_vertices() );

  size_t vertex_index = 0, texture_index = 0;

  do // iterate over all samples in file
  {
    next_sample();

    TriSurface::vertex_handle current_vertex = surface->vertex( vertex_index++ );
    current_vertex.set_location( vertex_location );
    current_vertex.set_texture_coordinate( vertex_texture_coordinate );

    # if defined DBG_FLAT_PDM_FILE_READER_VERTEX_SAMPLE
    std::clog << "flat::PdmFileReader()\t| " << " sample " << m_index
              << current_vertex  << std::endl;
    # endif

    surface->texture().set_pixel( texture_index++, texture_color );

    # if defined DBG_FLAT_PDM_FILE_READER_TEXTURE_SAMPLE
    std::clog << "flat::PdmFileReader()\t| " << " sample " << m_index
              << " pixel " + boost::lexical_cast< std::string >( texture_index )
              << " " << texture_color << std::endl;
    # endif

  } while( advance_index() );// of while next sample

}


void flat::PdmFileReader::next_sample()
{
  read_sample();
}


bool flat::PdmFileReader::read_sample()
{
  std::string token;

  // reading line from file
  std::getline( m_stream, token, '\n' );

  // extract position and color
  std::istringstream ss( token );

  ss >> vertex_location[0] >> vertex_location[1] >> vertex_location[2];
  ss >> texture_color[0] >> texture_color[1] >> texture_color[2];

  vertex_texture_coordinate[0] = ( m_index % get<0>( m_field_size ) ) / ( get<0>(m_field_size) - 1. );
  vertex_texture_coordinate[1] = ( m_index / get<0>( m_field_size ) ) / ( get<1>(m_field_size) - 1. );

  return true;
}
