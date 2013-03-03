// interface.hpp
// Copyright (C) 2006-20013  Peter Urban (urp@pks.mpg.de)
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

#pragma once
#include	"utk/math/fixed_size/vector.hpp"
#include	"matn.h"
#include	"geometry.h"
#include	<cmath>
#include	<iostream>

#pragma GCC visibility push(default)

namespace utk
{
  namespace math
  {
    namespace fixed_size
    {
      namespace quaternion
      {
	template<class T>
	vector::array<T,4> get_axis_angle_from_trackball( const vector::interface<T,2>& pos1
							, const vector::interface<T,2>& pos2
							, const T& tbsize = T(.8)
							);

	template< typename T > class quaternion;

	template< typename T, StorageTag >
	std::ostream& operator<<( std::ostream&, const quaternion< T, StorageTag >& );

	template< typename T, typename StorageTag >
	class quaternion : public typename storage_traits< StorageTag >::type< T, 4 > //vector::array< T, 4 >
	{
	  public:

	    typedef typename storage_traits< StorageTag >::type storage_type< T, 4 >; //vector::array< T, 4 >

	    quaternion()
	    : storage_type{ T(0),T(0),T(0),T(1) }
	    {  }

	    //!make quaternion from rotation about t (rad) around normal n
	    quaternion( const vector::interface<T,3>& n
		      , const T& t )
	    { set_axis_angle( n, t ); }

	    explicit
	    quaternion( const matn<T,3>& a );

	    explicit
	    quaternion( const vector::interface<T,4> four_vector )
	    : storage_type( four_vector )
	    {  }

	    template< typename OtherStorageTag >
	    quaternion( const quaternion< T, OtherStorageTag >& other )
	    : storage_type( other )
	    {	}

	    template< typename S = storage_tag
		    , typename = std::enable_if< std::is_same< S, typename storage_traits< S >::unmanaged >::type
		    >
	    quaternion( T x, T y, T z, T w )
	    :vector::array<T,4>( x, y, z, w )
	    {	}

	    template< typename S = storage_tag
		    , typename = std::enable_if< std::is_same< S, typename storage_traits< S >::unmanaged >::type
		    >
	    array( std::initializer_list<T> seq ) : interface<T,Cnt>(arr)
	    {
	      assert( seq.size() == Cnt );
	      std::copy(seq.begin(), seq.end(), arr);
	    }


	    quaternion<T>&		operator= (const quaternion<T>& q) 	{ vector::array<T,4>::operator=(q); return *this; }

	    quaternion<T>&		operator+=(const quaternion<T>& q)	{ return vector::interface<T,4>::operator+=(q); }

	    quaternion<T>&		operator-=(const quaternion<T>& q)	{ return vector::interface<T,4>::operator-=(q); }

	    quaternion<T>&		operator*=(const quaternion<T>& q)	{ return operator=(operator*(q)); } //optimize

	    quaternion<T>		conjugated()			const 	{ return quaternion(-vector::interface<T,4>::x(),-vector::interface<T,4>::y(),-vector::interface<T,4>::z(),vector::interface<T,4>::w()); }

	    void			set_axis_angle(const utk::vector::interface<T,3>& a,const T& t);

	    vector::array<T,4>			get_axis_angle()		const	{ T ts=T(1.f)/sqrt(T(1.f)-utk::sqr(vector::interface<T,4>::w()));
										return vector::array<T,4>(vector::interface<T,4>::x()*ts,vector::interface<T,4>::y()*ts,vector::interface<T,4>::z()*ts,T(2.f)*acos(vector::interface<T,4>::w()));
									      }

	    mata<T,3>			rot_matrix()			const	{ mata<T,3>	m;
										T	 dx=T(2.f)*vector::interface<T,4>::x(), dy=T(2.f)*vector::interface<T,4>::y(), dz=T(2.f)*vector::interface<T,4>::z(),
										       wx=dx*vector::interface<T,4>::w(), xx=dx*vector::interface<T,4>::x(), yy=dy*vector::interface<T,4>::y(),
										       wy=dy*vector::interface<T,4>::w(), xy=dy*vector::interface<T,4>::x(), yz=dz*vector::interface<T,4>::y(),
										       wz=dz*vector::interface<T,4>::w(), xz=dz*vector::interface<T,4>::x(), zz=dz*vector::interface<T,4>::z();

										m(0,0)=T(1)-(yy+zz);  	m(1,0)=xy+wz;		m(2,0)=xz-wy;
										m(0,1)=xy-wz;		m(1,1)=T(1.f)-(xx+zz);	m(2,1)=yz+wx;
										m(0,2)=xz+wy;		m(1,2)=yz-wx;		m(2,2)=T(1.f)-(xx+yy);
										return m;
									      }
	    void      		normalize()				{ const T len = vector::interface<T,4>::length();
										if( (len-T(1))>std::numeric_limits<T>::epsilon() ) vector::interface<T,4>::operator/=(len);
									      }
	    friend std::ostream&	operator<< <>(std::ostream&,const quaternion<T>&);
	};


	//______________
	//Implementation
	////////////////

	template<class T>
	quaternion<T>::quaternion(const matn<T,3>& a)		//make quaternion from rotation matrix
		      :vector::array<T,4>()
	{ T trace = a[0][0] + a[1][1] + a[2][2] + T(1.f);

	  if( trace > 1e-6 )
	  { T s = T(.5f) / sqrt(trace);
	    vector::interface<T,4>::w() = T(.25f) / s;
	    vector::interface<T,4>::x() = ( a[2][1] - a[1][2] ) * s;
	    vector::interface<T,4>::y() = ( a[0][2] - a[2][0] ) * s;
	    vector::interface<T,4>::z() = ( a[1][0] - a[0][1] ) * s;
	  }else
	  { if( a[0][0] > a[1][1] && a[0][0] > a[2][2] )
	    { T s = 2. * sqrtf( T(1.f) + a[0][0] - a[1][1] - a[2][2]);
	      vector::interface<T,4>::x()	= T(.25f) * s;
	      vector::interface<T,4>::y()	= (a[0][1] + a[1][0] ) / s;
	      vector::interface<T,4>::z()	= (a[0][2] + a[2][0] ) / s;
	      vector::interface<T,4>::w()	= (a[1][2] - a[2][1] ) / s;
	    }else
	    { if(a[1][1] > a[2][2])
	      { T s = T(2.f) * sqrtf( T(1.f) + a[1][1] - a[0][0] - a[2][2]);
		vector::interface<T,4>::x() = (a[0][1] + a[1][0] ) / s;
		vector::interface<T,4>::y() = T(.25f) * s;
		vector::interface<T,4>::z() = (a[1][2] + a[2][1] ) / s;
		vector::interface<T,4>::w() = (a[0][2] - a[2][0] ) / s;
	      }else
	      { T s = T(2.f) * sqrtf( T(1.f) + a[2][2] - a[0][0] - a[1][1] );
		vector::interface<T,4>::x() = (a[0][2] + a[2][0] ) / s;
		vector::interface<T,4>::y() = (a[1][2] + a[2][1] ) / s;
		vector::interface<T,4>::z() = T(.25f) * s;
		vector::interface<T,4>::w() = (a[0][1] - a[1][0] ) / s;
	      }
	    }
	  }
	  /* vector::interface<T,4>::w()=T(.5)*sqrt(m.get_diag().sum()+T(1));
	  vector::interface<T,4>::x()=(m(2,1)-m(1,2))/(vector::interface<T,4>::w()*T(4));
	  vector::interface<T,4>::y()=(m(0,2)-m(2,0))/(vector::interface<T,4>::w()*T(4));
	  vector::interface<T,4>::z()=(m(1,0)-m(0,1))/(vector::interface<T,4>::w()*T(4));*/
	  utk::vector::interface<T,4>::normalize();
	}

	template<class T>
	void	  quaternion<T>::set_axis_angle(const utk::vector::interface<T,3>& a,const T& t)
	{ vector::interface<T,3> imag=vector::interface<T,4>::xyz();
	  imag=a;
	  imag.normalize();
	  imag*=sin(T(.5f)*t);
	  vector::interface<T,4>::w()=cos(T(.5f)*t);
	}

	template<class T>
	vector::array<T,4>			get_axis_angle_from_trackball(const utk::vector::interface<T,2>& pos1,const utk::vector::interface<T,2>& pos2,const T& tbsize)
	{
	  utk::vector::array<T,4>  res;

	  //std::cerr<<"utk::get_axis_angle_trackball\t|pos1 "<<pos1<<" pos2 "<<pos2<<std::endl;
	  if( ((pos1 == pos2)==true) )
	  {
	    //Zero rotation
	    //std::cerr<<"utk::get_axis_angle_trackball\t|zero rotation"<<std::endl;
	    res.xyz()=T(0.f);
	    res[3]  =T(1.f);
	    return res;
	  }

	  //First, figure out z-coordinates for projection of P1 and P2 to deformed sphere
	  utk::vector::array<T,3>  p1(pos1[0],pos1[1],project_to_sphere(tbsize,pos1));	  //intersection of the first mouse point with the trackball
	  utk::vector::array<T,3>  p2(pos2[0],pos2[1],project_to_sphere(tbsize,pos2));	  //the second one

	  //rotation - axis angle
	  res.xyz() = utk::cross(p2,p1);

	  //Figure out how much to rotate around that axis.
	  p1	-= p2;
	  T t  = p1.length()/(T(2.f)*tbsize);

	  //Avoid problems with out-of-control values...
	  utk::clamp(t,T(-1.f),T(1.f));

	  res[3] = T(2.f) * asin(t);

	  res.xyz().normalize();
	  //std::cerr<<"utk::get_axis_angle_from_trackball\t|p1 "<<p1<<"\t|p2 "<<p2<<"\t|t "<<t<<"\t|axis "<<res.xyz()<<"\t|angle "<<res[3]<<std::endl;

	  return res;
	}

	template<class T>
	std::ostream&			operator<<(std::ostream& os,const quaternion<T>& q)
	{ os<<"utk::quat:\t| "<< vector::interface<T,4>(q) << "\t|aa " << q.get_axis_angle();
	  return os;
	}

      }

#pragma GCC visibility pop
