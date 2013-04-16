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

//# define DBG_FLAT_OBJ_FILE_READER
//# define DBG_FLAT_OBJ_FILE_READER_VERTEX_SAMPLE
//# define DBG_FLAT_OB_FILE_READER__READ_FACES

namespace flat
{
  //----| ObjFileReader

  template< typename Surface >
  class ObjFileReader
  {

      void read( std::istream& stream, const std::shared_ptr< Surface >& surface );

    public:

      std::string   path;

      size_pair vertex_field_size;


      ObjFileReader() = delete;

      ObjFileReader( const ObjFileReader& ) = delete;

      ObjFileReader( const std::string& path );

      std::shared_ptr< Surface > operator() ();

      std::string   get_name() const { return path; }
  };

}

//==============================================================================
// IMPLEMENTATION

template< typename Surface >
flat::ObjFileReader< Surface >::ObjFileReader( const std::string& path )
: path( path )
{ }

template< typename Surface >
std::shared_ptr< Surface > flat::ObjFileReader< Surface >::operator() ( )
{
  std::ifstream stream( path.c_str() );

  assert( stream.is_open() );

  # if defined DBG_FLAT_OBJ_FILE_READER
  std::clog << "flat::ObjFileReader< Surface >::ObjFileReader\t|" << std::endl
            << " path \"" << path << '\"'<< std::endl
            << std::endl;
  # endif

  std::shared_ptr< Surface > surface = Surface::create_with_size( 2904 );

  read( stream, surface );

  stream.close();

  return surface;
}

//:::| vertices


template< typename Surface >
void flat::ObjFileReader< Surface >::read( std::istream& stream, const std::shared_ptr< Surface >& surface )
{
  std::string line, token ;

  size_type vertex_id = 0;

  while( std::getline( stream, line ) )
  {
    std::stringstream linestream(line);

    linestream >> token;

    if( token == "v" )
    {
      flat::coord_t  x,y,z;
      linestream >> x >> y >> z;

      //typename Surface::vertex_handle vertex = surface->create_vertex( /*typename Surface::vertex_properties( flat::location_t( x, y, z ), vertex_texture_coord_t::value_type(0.) )*/ );
      surface->vertex(vertex_id++).set_location( flat::location_t( x, y, z ) );

    }else if( token == "f" )
    {
      typename Surface::vertex_descriptor  a,b,c;
      linestream >> a >> b >> c;

      a--;
      b--;
      c--;

      const std::pair<typename Surface::edge_descriptor,bool> ab = surface->edge( a, b );
      const std::pair<typename Surface::edge_descriptor,bool> bc = surface->edge( b, c );
      const std::pair<typename Surface::edge_descriptor,bool> ca = surface->edge( c, a );
      if( ab.second || bc.second || ca.second )
      {
        assert(!surface->edge( b, a ).second);
        std::swap(a,b);
      }

      # if defined DBG_FLAT_OB_FILE_READER__READ_FACES
      std::clog << "flat::ObjFileReader< Surface >::read\t| face " << a << " " << b << " " << c << std::endl;
      # endif

      surface->create_face( a, b, c );
    }
  }
}
