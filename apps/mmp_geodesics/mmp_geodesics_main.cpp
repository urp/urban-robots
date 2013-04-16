// mmp_geodesics_main.cpp
//
// Copyright (C) 2011-2013 - Peter Urban
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

# include "mmp/geodesics.hpp"
# include "surface/tri_surface/tri_surface.hpp"
# include "surface/quad_surface/quad_surface.hpp"
# include "surface/generators.hpp"
# include "surface/io/pdm/pdm_file_reader.hpp"
# include "surface/io/ply/ply_file_reader.hpp"
# include "surface/io/obj/obj_file_reader.hpp"

# include <boost/program_options.hpp>

#   include "mmp/visualizer/gtk_geodesics_inspector.hpp"
#   include "surface/tri_surface/gl_drawable.hpp"


using namespace flat;

typedef boost::numeric::ublas::symmetric_matrix< distance_t, boost::numeric::ublas::upper > distance_matrix_type;

int main (int argc, char *argv[])
{

  namespace po = boost::program_options;

  std::cout << std::boolalpha;
  std::clog << std::boolalpha;
  std::cerr << std::boolalpha;

  std::cout << "mmp-geodesics - Copyright (C) Peter Urban 2011-2013" << std::endl;

  //----| parse commandline
  // Declare the supported options.

  // surface
  const char surface_file_param[]= "surface";
  const char generator_param[]   = "generator";
  const char inspector_param[]   = "inspector";
  const char source_param[] = "single-source";
  const char export_dist_param[] = "export-distances";

  //const char session_out_param[]   = "session-out";

  po::options_description desc("Program options");
  desc.add_options()
    ("help", "produce help message")
    (inspector_param, "show inspector to visualize propagation" )
    (surface_file_param, po::value< std::string >(), "loads surface and texture from the specified file" )
    (generator_param, po::value< std::string >(), "defines a surface generator" )
    (source_param, po::value< TriSurface::vertex_descriptor >(), "compute shortest path only from vertex specified by an index" )
    (export_dist_param, po::value< std::string >(), "specifies a file to which the distance matrix will be exported" )
    ;

  po::variables_map vm;
  po::store( po::parse_command_line( argc, argv, desc ), vm );
  po::notify( vm );

  //help
  if( vm.count("help") ) { std::cout << desc << std::endl; return 1; }


  std::cout << "surface options: ";

  if( vm.count( surface_file_param ) )  { std::cout << surface_file_param << " \"" << vm[ surface_file_param ].as<std::string>() << "\" "; }
  if( vm.count( generator_param ) )     { std::cout << generator_param << " \"" << vm[ generator_param ].as<std::string>() << "\" "; }

  if( vm.count( export_dist_param ) ) { std::cout << export_dist_param << " \"" << vm[ export_dist_param ].as<std::string>() << "\" "; }
  std::cout<<std::endl;



  //----| model

  //----| model - surface

  typedef flat::TriSurface	surface_t;

  std::shared_ptr<surface_t> surface;

  if( vm.count( surface_file_param ) )
  {
    //----| file readers

    std::string path( vm[ surface_file_param ].as< std::string >() );

    // TODO make filereaders polymorphic

    if(path.substr( path.find_last_of(".") + 1) == "ply")
    {
      flat::PlyFileReader< surface_t > file_reader(path);
      surface = file_reader();
    }
    else if(path.substr( path.find_last_of(".") + 1) == "obj")
    {
      flat::ObjFileReader< surface_t > file_reader(path);
      surface = file_reader();
    }
    else if(path.substr( path.find_last_of(".") + 1) == "pdm")
    {
      flat::PdmFileReader< surface_t > file_reader(path);
      surface = file_reader();
    }

    //:::| read surface from pdm file


    flat::CenterRescaleTransform transform( utk::vec3b(true), utk::vec3b(true) );

    transform( surface );

  }else
  if( vm.count( generator_param ) )
  {
    //----| surface generators

    size_pair field_size = { 10, 10 };
    surface = surface_t::create_with_size( field_size.first * field_size.second );

    flat::RegularGridTransform grid_transform( field_size );
    grid_transform( surface);

    flat::SimpleRectlinearTriangulator triangulator( field_size );
    triangulator( surface );


    if( vm[ generator_param ].as< std::string >() == "random" )
    {
      flat::DisturbTransform noise_trafo{ 0.1 };
      noise_trafo( surface );

    }
    else if( vm[ generator_param ].as< std::string >() == "wave" )
    {
      flat::WaveTransform wave_trafo;
      wave_trafo( surface );

    }else
    { std::cerr << "ERROR - unknown surface generator \"" << vm[ generator_param ].as<std::string>() << "\" specified." << std::endl;
      return 0;
    }
  } else
  { std::cerr << "ERROR - no surface specified - use one of the following arguments \"" << surface_file_param << "\", \"" << generator_param << "\" specified." << std::endl;
    return 0;
  }


  //:::| compute distances

  distance_matrix_type distance_matrix( vm.count( export_dist_param ) ? surface->num_vertices() : 0 );

  //---| single-source ?

  TriSurface::vertex_descriptor source,last_source;

  if( vm.count( source_param ) )
  {
    source = last_source = vm[ source_param ].as< TriSurface::vertex_descriptor >();
    assert( source < surface->num_vertices() );
  }else
  {
    source = 0;
    last_source = surface->num_vertices()-1;
  }


  //---| inspector ?

  std::auto_ptr< gtk::GeodesicsInspector > obs;
  std::auto_ptr< Gtk::Main > kit;

  if( vm.count( inspector_param ) )
  {
    // initialize gtkmm
    kit.reset( new Gtk::Main(argc, argv) );
    // initialize gtkglextmm.
    Gtk::GL::init(argc, argv);
  }

  for( ; source <= last_source; source++ )
  {
    mmp::Geodesics gi( *surface, source );

    //----| propagate from source
    if( vm.count( inspector_param ) )
    {
      // reuse inspector window
      if( !obs.get() ) obs.reset( gtk::GeodesicsInspector::create_propagation_observer( &gi, surface ) );
      else obs->initialize( &gi, surface );
      obs->run_propagation();

    }else
      gi.propagate_paths();

    //----| copy vertex-vertex distances from source vertex to distance matrix
    if( vm.count( export_dist_param ) )
      for( TriSurface::vertex_descriptor query = source + 1; query < surface->num_vertices(); query++)
        distance_matrix( source, query ) = gi.query_distance( query );
  }

  //----| export distance matrix
  if( vm.count( export_dist_param ) )
  {
    std::string     path( vm[export_dist_param].as<std::string>() );
    std::ofstream   distfile( path );
    std::clog << "exporting distance matrix to file \"" << path << '\"'<< std::endl;
    distfile << distance_matrix;
    distfile.close();
  }

  //----| exit
  return 1;
}
