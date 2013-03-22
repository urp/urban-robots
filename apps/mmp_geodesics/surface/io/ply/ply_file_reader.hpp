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

# include "surface/io/ply/ply.hpp"


# include <boost/lexical_cast.hpp>

# include <fstream>

# include <sstream>

# define DBG_FLAT_PLY_FILE_READER
//# define DBG_FLAT_PLY_FILE_READER_VERTEX_SAMPLE
//# define DBG_FLAT_PLY_FILE_READER_TEXTURE_SAMPLE

namespace flat
{
  //----| PlyFileReader

  template< typename Surface >
  class PlyFileReader
  {

    private:

      std::shared_ptr< Surface > read_vertices( PlyFile* in_file );
      void read_tristrips( PlyFile* in_file, const std::shared_ptr< Surface >& surface );
    public:

      std::string   path;

      size_pair vertex_field_size;


      PlyFileReader() = delete;

      PlyFileReader( const PlyFileReader& ) = delete;

      PlyFileReader( const std::string& path );

      std::shared_ptr< Surface > operator() ();

      std::string   get_name() const { return path; }
  };

}

//==============================================================================
// IMPLEMENTATION

template< typename Surface >
flat::PlyFileReader< Surface >::PlyFileReader( const std::string& path )
: path( path )
{ }

template< typename Surface >
std::shared_ptr< Surface > flat::PlyFileReader< Surface >::operator() ( )
{
  FILE* c_file = std::fopen( path.c_str() ,"r" );
  PlyFile* in_file = read_ply( c_file );

  assert( in_file );

  # if defined DBG_FLAT_PLY_FILE_READER
  std::clog << "flat::PlyFileReader< Surface >::PlyFileReader\t|" << std::endl
            << " path \"" << path << '\"'<< std::endl
            << ( in_file->file_type ? "asci" : " binary" ) << std::endl
            << "version " << in_file->version << std::endl
            << " num elements " << in_file->num_elem_types << std::endl
            << " elements: ";

  std::for_each( in_file->elems, in_file->elems + in_file->num_elem_types
               , []( PlyElement* elem) { std::clog << elem->name << " "; }
               );

  std::clog << std::endl;
  # endif

  std::shared_ptr< Surface > surface = read_vertices( in_file );

  read_tristrips( in_file, surface );

  close_ply( in_file );

  //delete in_file;

  return surface;
}

//:::| tristrips

struct ply_vertex
{
    flat::coord_t  x,y,z;
};

template< typename Surface >
std::shared_ptr< Surface > flat::PlyFileReader< Surface >::read_vertices( PlyFile* in_file )
{
  PlyElement** element = std::find_if( in_file->elems, in_file->elems + in_file->num_elem_types
                                     , [](PlyElement* elem){ return equal_strings( elem->name, "vertex" ); }
                                     );

  std::size_t pos = std::distance( in_file->elems, element );

  if( pos == in_file->num_elem_types )
  {
    std::cout << "flat::PlyFileReader::read_vertices\t| no vertex elements" << std::endl;
    assert( false );
  }

  int num_vertices;

  setup_element_read_ply( in_file, pos, &num_vertices );

  # if defined DBG_FLAT_PLY_FILE_READER
  std::cout << "flat::PlyFileReader::read_vertices\t| reading " << num_vertices << " vertices " << std::endl;
  # endif

  std::shared_ptr< Surface > surface = Surface::create_with_size( num_vertices );

  PlyProperty vert_props[] = { /* list of property information for a vertex */
                               {"x", Float32, Float64, offsetof(ply_vertex,x), 0, 0, 0, 0},
                               {"y", Float32, Float64, offsetof(ply_vertex,y), 0, 0, 0, 0},
                               {"z", Float32, Float64, offsetof(ply_vertex,z), 0, 0, 0, 0},
                             };

  setup_property_ply (in_file, &vert_props[0]);
  setup_property_ply (in_file, &vert_props[1]);
  setup_property_ply (in_file, &vert_props[2]);

  for( int vert = 0; vert < num_vertices; vert++ )
  {
    ply_vertex vertex;
    ply_get_element( in_file, static_cast< void* >( &vertex ) );
    surface->vertex( vert ).set_location( flat::location_t( vertex.x, vertex.y, vertex.z ) );
  }

  return surface;
}

//:::| tristrips

struct ply_tristrip
{
    int  num_vertices;
    int* vertex_indices;
};

template< typename Surface >
void flat::PlyFileReader< Surface >::read_tristrips( PlyFile* in_file, const std::shared_ptr< Surface >& surface )
{
  PlyElement** element = std::find_if( in_file->elems, in_file->elems + in_file->num_elem_types
                                     , [](PlyElement* elem){ return equal_strings( elem->name, "tristrips" ); }
                                     );

  std::size_t pos = std::distance( in_file->elems, element );

  if( pos == in_file->num_elem_types )
  {
    std::cout << "flat::PlyFileReader::read_tristrips\t| no tristrip elements" << std::endl;
    assert( false );
  }

  int num_tristrips;

  setup_element_read_ply( in_file, pos, &num_tristrips );

  # if defined DBG_FLAT_PLY_FILE_READER
  std::cout << "flat::PlyFileReader::read_tristrips\t| reading " << num_tristrips << " tristrips " << std::endl;
  # endif

  static constexpr PlyProperty tristrip_props[1] = { /* list of property information for a tristrip */
                                                     {"vertex_indices", Int32, Int32, offsetof(ply_tristrip,vertex_indices)
                                                     , 1              , Int32, Int32, offsetof(ply_tristrip,num_vertices)
                                                     }
                                                   };


  setup_property_ply (in_file, const_cast< PlyProperty* >(&tristrip_props[0]) );

  for( int vert = 0; vert < num_tristrips; vert++ )
  {
    ply_tristrip strip;
    ply_get_element( in_file, static_cast< void* >( &strip ) );

    # if defined DBG_FLAT_PLY_FILE_READER
    std::cout << "flat::PlyFileReader::read_tristrips\t| got " << strip.num_vertices << " vertex indices " << std::endl;
    # endif

    assert( strip.num_vertices > 3 );

    for( int* index = strip.vertex_indices; index < strip.vertex_indices + strip.num_vertices - 2; index++ )
    {
      if( *(index+2) == -1 )
      {
        index += 2;
        std::clog << "starting new tristrip..." << std::endl;
      }else
      {
        std::clog << "a " << (*index) << " b " << *(index+1) << " c " << *(index+2) << std::endl;

        int a = *(index);
        int b = *(index+1);
        int c = *(index+2);

        const std::pair<typename Surface::edge_descriptor,bool> ab = surface->edge( a, b );
        if( ab.second )
        {
          const std::pair<typename Surface::edge_descriptor,bool> ba = surface->edge( b, a );
          assert(!ba.second);

          std::swap(a,b);
        }

        surface->create_face( a, b, c );
      }
    }
  }

}
