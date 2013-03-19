/***************************************************************************
 *            surface.h
 *
 *  Wed Aug  5 23:46:44 2009
 *  Copyright  2009  Peter Urban
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
# include "surface/he/mesh.hpp"

namespace flat
{

  template< class MeshT > class VertexHandle;

  // additional vertex properties
  struct vertex_texture_coord_t { typedef boost::vertex_property_tag kind;
				  typedef utk::veca< float, 2 > type;
				};
  template< typename MeshT >
  std::ostream&   operator<<( std::ostream&, flat::VertexHandle<MeshT> const& );

  // vertex handle
  template< class MeshT >
  class VertexHandle : public he::DefaultVertexHandle< MeshT >
  {
    public:

      typedef typename MeshT::vertex_descriptor vertex_descriptor;
      typedef typename MeshT::vertex_handle     vertex_handle;
      typedef typename MeshT::edge_handle       edge_handle;

      typedef typename boost::property_map<typename MeshT::graph_t, vertex_texture_coord_t >::const_type  const_texture_coord_map_t;

      typedef typename boost::property_traits<const_texture_coord_map_t>::value_type  color_t;

      friend std::ostream& operator<< <MeshT>( std::ostream&, VertexHandle<MeshT> const& );

    public:


      VertexHandle( const vertex_descriptor& v, const MeshT& m )
      : he::DefaultVertexHandle<MeshT>(v,m)
      { }

      VertexHandle( const he::DefaultVertexHandle< MeshT >& o )
      : he::DefaultVertexHandle<MeshT>(o)
      { }

      const vertex_texture_coord_t::type& texture_coordinate()	const
      {
        return this->mesh().template get_property_map< vertex_texture_coord_t >() [ *this ];
      }

      void set_texture_coordinate( const vertex_texture_coord_t::type& value )
      {
        return this->mesh().template put< vertex_texture_coord_t >( this->descriptor(), value );
      }
  };

  template< typename MeshT >
  std::ostream&   operator<<( std::ostream& os, flat::VertexHandle<MeshT> const& vertex )
  {
    os << "vertex "    << vertex.descriptor()
       << " location " << vertex.location()
       << " texcoord " << vertex.texture_coordinate();
    return os;
  }

  //---| point_cloud

  // the mesh type
  typedef he::Mesh< VertexHandle, he::DefaultEdgeHandle, he::DefaultFaceHandle
		  , boost::property< vertex_texture_coord_t, vertex_texture_coord_t::type >
                  , boost::no_property, boost::no_property >
	  surface_mesh_t;


  // a mesh without edges and faces, only vertices.
  class PointCloud : public surface_mesh_t
  {
    private:

      mutable location_t m_min_location;
      mutable location_t m_max_location;

      void comp_min_max_xy()	const;
      void comp_min_max_z()	const;

    public:

      std::string  name;

    protected:

	  PointCloud( vertices_size_type vertex_count, const std::string& name = "Untitled PointCloud" )
	  : surface_mesh_t( vertex_count )
	  , m_min_location(   std::numeric_limits<coord_t>::infinity() )
	  , m_max_location( - std::numeric_limits<coord_t>::infinity() )
	  , name(name)
	  {	}

    public:

      virtual   ~PointCloud()	{	}

      const distance_t	distance( vertex_descriptor a, vertex_descriptor b)	const
      { return utk::distance( vertex( a ).location(), vertex( b ).location() ); }

      virtual void prepare_step()  { set_min_max(); }


      void set_min_max( const location_ref_t& min = location_t( std::numeric_limits<coord_t>::infinity())
		       , const location_ref_t& max = location_t(-std::numeric_limits<coord_t>::infinity()) )
      { m_min_location = min;
	m_max_location = max;
      }

      void set_min_max_z( const coord_t min =  std::numeric_limits<coord_t>::infinity()
			, const coord_t max = -std::numeric_limits<coord_t>::infinity() )
      { m_min_location.z() = min;
	m_max_location.z() = max;
      }

      const coord_t& min_height()    const
      {
	if( m_min_location.z() == std::numeric_limits<coord_t>::infinity() )
          comp_min_max_z();
        return m_min_location.z();
      }

      const coord_t& max_height()	const
      {
	if( m_max_location.z() == - std::numeric_limits<coord_t>::infinity() )
          comp_min_max_z();
        return m_max_location.z();
      }

      // TODO use bounding box interface
      location_t min_location()	const
      {
	if( ( m_min_location.xy() == std::numeric_limits<coord_t>::infinity() ) == true )
	  comp_min_max_xy();
	if( m_min_location.z() == std::numeric_limits<coord_t>::infinity() )
          comp_min_max_z();
        return m_min_location;
      }

      location_t max_location()  const
      {
	if( ( m_max_location.xy() == - std::numeric_limits<coord_t>::infinity() ) == true )
          comp_min_max_xy();
        if( m_max_location.z() == - std::numeric_limits<coord_t>::infinity() )
          comp_min_max_z();
        return m_max_location;
      }

  };

}
