// expDaylitArea.cpp - 
//
/**********************************************************************
 *  Copyright (c) 2012-2017, California Energy Commission
 *  Copyright (c) 2012-2017, Wrightsoft Corporation
 *  All rights reserved.
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  - Neither the name of the California Energy Commission nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *  DISCLAIMER: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL CALIFORNIA ENERGY COMMISSION,
 *  WRIGHTSOFT CORPORATION, ITRON, INC. OR ANY OTHER AUTHOR OR COPYRIGHT HOLDER OF
 *  THIS SOFTWARE (COLLECTIVELY, THE "AUTHORS") BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 *  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  EACH LICENSEE AND SUBLICENSEE OF THE
 *  SOFTWARE AGREES NOT TO ASSERT ANY CLAIM AGAINST ANY OF THE AUTHORS RELATING TO
 *  THIS SOFTWARE, WHETHER DUE TO PERFORMANCE ISSUES, TITLE OR INFRINGEMENT ISSUES,
 *  STRICT LIABILITY OR OTHERWISE.
 **********************************************************************/

#include "stdafx.h"
#include "expRuleList.h"
#include "BEMProcI.h"
#include "BEMProc.h"
#include "BEMClass.h"
#include "BEMPropertyType.h"

#undef BOOST_UBLAS_TYPE_CHECK
#pragma warning(disable : 4100 4189 4702 4996)
#include <boost/geometry/geometry.hpp>
#pragma warning(default : 4100 4189 4702 4996)
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/multi/geometries/multi_point.hpp>
#include <boost/geometry/multi/geometries/multi_polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
//#include <boost/geometry/algorithms/make.hpp>
//#include <boost/geometry/algorithms/simplify.hpp>
//#include <boost/geometry/geometries/point.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/foreach.hpp>
#include <boost/geometry/io/svg/svg_mapper.hpp>

#include <fstream>

typedef boost::geometry::model::d2::point_xy<double> BEMPoint;
typedef boost::geometry::model::multi_point< boost::geometry::model::d2::point_xy<double> > BEMMultiPoint;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > BEMPoly;
typedef boost::geometry::model::multi_polygon< boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > > BEMMultiPoly;

static double sdPi        = acos(-1.0);
static double sd2Pi       = 2.0 * sdPi;
static double sdHalfPi    = asin(1.0);
static double sd3HalfPi   = 3.0 * sdHalfPi;
static double sdQtrPi     = atan2(1.0,1.0);
static double sd3QtrPi    = atan2(1.0,-1.0);

static inline double LineAngle( double dX1, double dX2, double dY1, double dY2, double dMargin )
{	if (WithinMargin( dY1, dY2, dMargin ))
	{	if (dX2 > dX1)
			return 0.0;
		else
			return sdPi;
	}
	else if (WithinMargin( dX1, dX2, dMargin ))
	{	if (dY2 > dY1)
			return sdHalfPi;
		else
			return sd3HalfPi;
	}
	double dAng = atan2( (dY2-dY1), (dX2-dX1) );
	return (dAng < -0.000005 ? dAng + sd2Pi : dAng);
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


//namespace boost {
//namespace geometry {
//namespace detail { 
//
//template <typename Point1, typename Point2, typename Point3>
//static inline bool point_is_spike_or_equal_BEM(Point1 const& last_point, Point2 const& segment_a, Point3 const& segment_b)
//{
//  // adapted from point_is_spike_or_equal to include tolerance checking
//
//  // segment_a is at the begining
//  // segment_b is in the middle
//  // last_point is at the end
//
//  // segment_b is being considered for deletion
//
//  double normTol = 0.1;	// 0.001; // 1 mm
//  double tol = 0.1;		// 0.001; // relative to 1
//    
//  double diff1_x = last_point.x()-segment_b.x();
//  double diff1_y = last_point.y()-segment_b.y();
//  double norm1 = sqrt(pow(diff1_x, 2) + pow(diff1_y, 2));
//  if (norm1 > normTol){
//    diff1_x = diff1_x/norm1;
//    diff1_y = diff1_y/norm1;
//  }else{
//    // last point is too close to segement b
//    return true;
//  }
//
//  double diff2_x = segment_b.x()-segment_a.x();
//  double diff2_y = segment_b.y()-segment_a.y();
//  double norm2 = sqrt(pow(diff2_x, 2) + pow(diff2_y, 2));
//  if (norm2 > normTol){
//    diff2_x = diff2_x/norm2;
//    diff2_y = diff2_y/norm2;
//  }else{
//    // segement b is too close to segement a
//    return true;
//  }
//
//  double crossProduct = diff1_x*diff2_y-diff1_y*diff2_x;
//  if (abs(crossProduct) < tol){
//    double dotProduct = diff1_x*diff2_x+diff1_y*diff2_y;
//    if (dotProduct <= -1.0 + tol){
//      // reversal
//      return true;
//    }
//  }
//
//  return false;
//}
//
//namespace remove_spikes {
//
//template <typename Range>
//struct range_remove_spikes
//{
//    typedef typename strategy::side::services::default_strategy
//    <
//        typename cs_tag<Range>::type
//    >::type side_strategy;
//
//    typedef typename coordinate_type<Range>::type coordinate_type;
//    typedef typename point_type<Range>::type point_type;
//
//    static inline void apply(Range& range)
//    {
//        std::size_t n = boost::size(range);
//        std::size_t const min_num_points = core_detail::closure::minimum_ring_size
//            <
//                geometry::closure<Range>::value
//            >::value;
//        if (n < min_num_points)
//        {
//            return;
//        }
//
//        typedef typename boost::range_iterator<Range>::type iterator;
//
//        std::deque<point_type> cleaned;
//        for (typename boost::range_iterator<Range const>::type it = boost::begin(range);
//            it != boost::end(range); ++it)
//        {
//            // Add point
//            cleaned.push_back(*it);
//
//            while(cleaned.size() >= 3
//                    && detail::point_is_spike_or_equal_BEM(cleaned.back(), *(cleaned.end() - 3), *(cleaned.end() - 2)))
//            {
//                // Remove pen-ultimate point causing the spike (or which was equal)
//                cleaned.erase(cleaned.end() - 2);
//            }
//        }
//
//        // For a closed-polygon, remove closing point, this makes checking first point(s) easier and consistent
//        if (geometry::closure<Range>::value == geometry::closed)
//        {
//            cleaned.pop_back();
//        }
//
//        bool found = false;
//        do
//        {
//            found = false;
//            // Check for spike in first point
//            int const penultimate = 2;
//            while(cleaned.size() > 3 && detail::point_is_spike_or_equal_BEM(cleaned.front(), *(cleaned.end() - penultimate), cleaned.back()))
//            {
//                cleaned.pop_back();
//                found = true;
//            }
//            // Check for spike in second point
//            while(cleaned.size() > 3 && detail::point_is_spike_or_equal_BEM(*(cleaned.begin() + 1), cleaned.back(), cleaned.front()))
//            {
//                cleaned.pop_front();
//                found = true;
//            }
//        }
//        while (found);
//
//        // Close if necessary
//        if (geometry::closure<Range>::value == geometry::closed)
//        {
//            cleaned.push_back(cleaned.front());
//        }
//
//        // Copy output
//        geometry::clear(range);
//        std::copy(cleaned.begin(), cleaned.end(), std::back_inserter(range));
//    }
//};
//
//}} // namespace detail::remove_spikes
//
//namespace dispatch
//{
//
//
//template
//<
//    typename Geometry,
//    typename Tag = typename tag<Geometry>::type
//>
//struct remove_spikes
//{
//    static inline void apply(Geometry&)
//    {}
//};
//
//
//template <typename Ring>
//struct remove_spikes<Ring, ring_tag>
//    : detail::remove_spikes::range_remove_spikes<Ring>
//{};
//
//
//
////template <typename Polygon>
////struct remove_spikes<Polygon, polygon_tag>
////    : detail::remove_spikes::polygon_remove_spikes<Polygon>
////{};
//
//
//
//} // namespace dispatch
//
//template <typename Geometry>
//inline void remove_spikes(Geometry& geometry)
//{
//    concept::check<Geometry>();
//
//    dispatch::remove_spikes<Geometry>::apply(geometry);
//}
//
//
//}} // namespace boost::geometry
//
//
////typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > BEMPoly;
////typedef boost::geometry::model::multi_polygon< boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > > BEMMultiPoly;
//
////  std::vector<BEMPoly> removeSpikes(const std::vector<BEMPoly>& polygons)
////  {
////    std::vector<BEMPoly> result;
////    BOOST_FOREACH(const BEMPoly& polygon, polygons){
////      BEMPoly temp(polygon);
////      boost::geometry::remove_spikes(temp);
////      result.push_back(temp);
////    }
////    return result;
////  }
//  BEMMultiPoly removeSpikes(const BEMMultiPoly& polygons)
//  {
//    BEMMultiPoly result;
//    BOOST_FOREACH(const BEMPoly& polygon, polygons){
//      BEMPoly temp(polygon);
//      boost::geometry::remove_spikes(temp);
//      result.push_back(temp);
//    }
//    return result;
//  }
//  BEMPoly removeSpikes(const BEMPoly& polygon)
//  {
//    BEMPoly result(polygon);
//    boost::geometry::remove_spikes(result);
//    return result;
//  }
//
//
////		{	BEMMultiPoly outputInt;
////			boost::geometry::intersection( m_polyFinalDaylit[(bSecondaryArea?1:0)], pDaylitArea->m_polyFinalDaylit[i], outputInt );		// calculate intersection of 2 daylit areaa
////			outputInt = removeSpikes( outputInt );
//////  std::vector<BEMPoly> removeSpikes(const std::vector<BEMPoly>& polygons)
////
////			BEMPoly polyInt;
////	//		BEMMultiPoly polyInt;
////			int iNumIntPolys = 0;
////			BOOST_FOREACH(BEMPoly const& p, outputInt)
////			{	iNumIntPolys++;
////				if (boost::geometry::area(p) > dIntersectArea[i])
//
//
//----------------------------------------------------------------------------------------
// old version from Dan @ NREL above - still doesn't work
// version below replaced the above ~10/26/13, reportedly fixing problem we are having
//----------------------------------------------------------------------------------------

namespace boost {
namespace geometry {
namespace detail { 

template <typename Point1, typename Point2, typename Point3>
static inline bool point_is_spike_or_equal_BEM(Point1 const& last_point, Point2 const& segment_a, Point3 const& segment_b)
{
  // adapted from point_is_spike_or_equal to include tolerance checking

  // segment_a is at the begining
  // segment_b is in the middle
  // last_point is at the end

  // segment_b is being considered for deletion

  double normTol = 0.1;	// 0.001; // 1 mm
  double tol = 0.1;		// 0.001; // relative to 1
    
  double diff1_x = last_point.x()-segment_b.x();
  double diff1_y = last_point.y()-segment_b.y();
  double norm1 = sqrt(pow(diff1_x, 2) + pow(diff1_y, 2));
  if (norm1 > normTol){
    diff1_x = diff1_x/norm1;
    diff1_y = diff1_y/norm1;
  }else{
    // last point is too close to segement b
    return true;
  }

  double diff2_x = segment_b.x()-segment_a.x();
  double diff2_y = segment_b.y()-segment_a.y();
  double norm2 = sqrt(pow(diff2_x, 2) + pow(diff2_y, 2));
  if (norm2 > normTol){
    diff2_x = diff2_x/norm2;
    diff2_y = diff2_y/norm2;
  }else{
    // segement b is too close to segement a
    return true;
  }

  double crossProduct = diff1_x*diff2_y-diff1_y*diff2_x;
  if (abs(crossProduct) < tol){
    double dotProduct = diff1_x*diff2_x+diff1_y*diff2_y;
    if (dotProduct <= -1.0 + tol){
      // reversal
      return true;
    }
  }

  return false;
}

}}} // namespace boost:geometry::detail

// -------------------- SAC - based on: boost/geometry/algorithms/remove_spikes.hpp  -------------------- 
#ifndef BOOST_GEOMETRY_ALGORITHMS_REMOVE_SPIKES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_REMOVE_SPIKES_HPP

#include <deque>

#include <boost/range.hpp>
#include <boost/typeof/typeof.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/algorithms/detail/point_is_spike_or_equal.hpp>
#include <boost/geometry/algorithms/clear.hpp>


/*
Remove spikes from a ring/polygon.
Ring (having 8 vertices, including closing vertex)
+------+
| |
| +--+
| | ^this "spike" is removed, can be located outside/inside the ring
+------+
(the actualy determination if it is removed is done by a strategy)

*/


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace remove_spikes
{


template <typename Range>
struct range_remove_spikes
{
 typedef typename strategy::side::services::default_strategy
 <
 typename cs_tag<Range>::type
 >::type side_strategy;

 typedef typename coordinate_type<Range>::type coordinate_type;
 typedef typename point_type<Range>::type point_type;


 static inline void apply(Range& range)
 {
 std::size_t n = boost::size(range);
 std::size_t const min_num_points = core_detail::closure::minimum_ring_size
 <
 geometry::closure<Range>::value
 >::value;
 if (n < min_num_points)
 {
 return;
 }

 typedef typename boost::range_iterator<Range>::type iterator;

 std::deque<point_type> cleaned;
 for (typename boost::range_iterator<Range const>::type it = boost::begin(range);
 it != boost::end(range); ++it)
 {
 // Add point
 cleaned.push_back(*it);

 while(cleaned.size() >= 3
 && detail::point_is_spike_or_equal_BEM(cleaned.back(), *(cleaned.end() - 3), *(cleaned.end() - 2)))
 {
 // Remove pen-ultimate point causing the spike (or which was equal)
 cleaned.erase(cleaned.end() - 2);
 }
 }

 // For a closed-polygon, remove closing point, this makes checking first point(s) easier and consistent
 if (geometry::closure<Range>::value == geometry::closed)
 {
 cleaned.pop_back();
 }

 bool found = false;
 do
 {
 found = false;
 // Check for spike in first point
 int const penultimate = 2;
 while(cleaned.size() > 3 && detail::point_is_spike_or_equal_BEM(cleaned.front(), *(cleaned.end() - penultimate), cleaned.back()))
 {
 cleaned.pop_back();
 found = true;
 }
 // Check for spike in second point
 while(cleaned.size() > 3 && detail::point_is_spike_or_equal_BEM(*(cleaned.begin() + 1), cleaned.back(), cleaned.front()))
 {
 cleaned.pop_front();
 found = true;
 }
 }
 while (found);

 // Close if necessary
 if (geometry::closure<Range>::value == geometry::closed)
 {
 cleaned.push_back(cleaned.front());
 }

 // Copy output
 geometry::clear(range);
 std::copy(cleaned.begin(), cleaned.end(), std::back_inserter(range));
 }
};


template <typename Polygon>
struct polygon_remove_spikes
{
 static inline void apply(Polygon& polygon)
 {
 typedef typename geometry::ring_type<Polygon>::type ring_type;

 typedef range_remove_spikes<ring_type> per_range;
 per_range::apply(exterior_ring(polygon));

 typename interior_return_type<Polygon>::type rings
 = interior_rings(polygon);
 for (BOOST_AUTO_TPL(it, boost::begin(rings)); it != boost::end(rings); ++it)
 {
 per_range::apply(*it);
 }
 }
};


}} // namespace detail::remove_spikes
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
 typename Geometry,
 typename Tag = typename tag<Geometry>::type
>
struct remove_spikes
{
 static inline void apply(Geometry&)
 {}
};


template <typename Ring>
struct remove_spikes<Ring, ring_tag>
 : detail::remove_spikes::range_remove_spikes<Ring>
{};



template <typename Polygon>
struct remove_spikes<Polygon, polygon_tag>
 : detail::remove_spikes::polygon_remove_spikes<Polygon>
{};



} // namespace dispatch
#endif


/*!
 \ingroup remove_spikes
 \tparam Geometry geometry type
 \param geometry the geometry to make remove_spikes
*/
template <typename Geometry>
inline void remove_spikes(Geometry& geometry)
{
 concept::check<Geometry>();

 dispatch::remove_spikes<Geometry>::apply(geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_REMOVE_SPIKES_HPP
// -------------------- SAC - end of code based on: boost/geometry/algorithms/remove_spikes.hpp --------------------


// -------------------- SAC - based on: boost/geometry/multi/algorithms/remove_spikes.hpp --------------------
#ifndef BOOST_GEOMETRY_MULTI_ALGORITHMS_REMOVE_SPIKES_HPP
#define BOOST_GEOMETRY_MULTI_ALGORITHMS_REMOVE_SPIKES_HPP


#include <boost/geometry/multi/core/closure.hpp>
#include <boost/geometry/multi/core/point_order.hpp>
#include <boost/geometry/multi/core/tags.hpp>
#include <boost/geometry/multi/geometries/concepts/check.hpp>

//SAC #include <boost/geometry/algorithms/remove_spikes.hpp>
#include "memLkRpt.h"


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace remove_spikes
{

template <typename MultiGeometry, typename SingleVersion>
struct multi_remove_spikes
{
 static inline void apply(MultiGeometry& multi)
 {
 for (typename boost::range_iterator<MultiGeometry>::type
 it = boost::begin(multi);
 it != boost::end(multi);
 ++it)
 {
 SingleVersion::apply(*it);
 }
 }
};



}} // namespace detail::remove_spikes
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename MultiPolygon>
struct remove_spikes<MultiPolygon, multi_polygon_tag>
 : detail::remove_spikes::multi_remove_spikes
 <
 MultiPolygon,
 detail::remove_spikes::polygon_remove_spikes
 <
 typename boost::range_value<MultiPolygon>::type
 >
 >
{};


} // namespace dispatch
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_MULTI_ALGORITHMS_REMOVE_SPIKES_HPP
// -------------------- SAC - end of code based on: boost/geometry/multi/algorithms/remove_spikes.hpp --------------------

BEMMultiPoly removeSpikes(const BEMMultiPoly& polygons)
{
  BEMMultiPoly result;
  BOOST_FOREACH(const BEMPoly& polygon, polygons){
    BEMPoly temp(polygon);
    boost::geometry::remove_spikes(temp);
    result.push_back(temp);
  }
  return result;
}
BEMPoly removeSpikes(const BEMPoly& polygon)
{
  BEMPoly result(polygon);
  boost::geometry::remove_spikes(result);
  return result;
}


////////////////////////////////////////////////////////////////////////////////

BEMPoly removeDupVerts(const BEMPoly& polygon, double dMargin)
{
	BEMPoly result;
	BEMPoint ptLast;		bool bFirstPt = true;
	for (BOOST_AUTO(	it, boost::begin(boost::geometry::exterior_ring(polygon)));
							it != boost::end(boost::geometry::exterior_ring(polygon));  ++it)
	{	if (bFirstPt)
		{	boost::geometry::append( result, *it );  //boost::tuples::make_tuple( RoundDbl( dPrimX2, 24.0 ), RoundDbl( dPrimY2, 24.0 ) ));
			bFirstPt = false;
		}
		else if (	boost::geometry::get<0>( *it ) <= (boost::geometry::get<0>( ptLast ) + dMargin) &&
						boost::geometry::get<0>( *it ) >= (boost::geometry::get<0>( ptLast ) - dMargin) &&
						boost::geometry::get<1>( *it ) <= (boost::geometry::get<1>( ptLast ) + dMargin) &&
						boost::geometry::get<1>( *it ) >= (boost::geometry::get<1>( ptLast ) - dMargin) )
		{	// points are dups - do NOT add this point back into the polygon
		}
		else
			boost::geometry::append( result, *it );  //boost::tuples::make_tuple( RoundDbl( dPrimX2, 24.0 ), RoundDbl( dPrimY2, 24.0 ) ));
		ptLast = *it;
	}
  return result;
}
BEMMultiPoly removeDupVerts(const BEMMultiPoly& polygons, double dMargin)		// SAC 11/21/15 - added to remove duplicate vertices, as they crash some boost::geometry routines (tic 1276)
{
  BEMMultiPoly result;
  BOOST_FOREACH(const BEMPoly& polygon, polygons){
    BEMPoly temp = removeDupVerts(polygon, dMargin);
    result.push_back(temp);
  }
  return result;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void EchoPolys( QString& str, const char* pszPolyDescrip, const BEMMultiPoly& polygons )
{
//  BOOST_FOREACH(const BEMPoly& polygon, polygons){
//    BEMPoly temp(polygon);
//
//    boost::geometry::remove_spikes(temp);
	int iPIdx=0;		QString sTemp;			str = QString( "      %1" ).arg( pszPolyDescrip );
	BOOST_FOREACH(BEMPoly const& p, polygons)
	{
		BEMPoint ptPCenter;		boost::geometry::centroid( p, ptPCenter );
		sTemp = QString( "            Poly%1  /  area %2  /  centroid ( %3, %4 )\n" ).arg( QString::number(++iPIdx), 3 ).arg( QString::number(boost::geometry::area(p)),
																				QString::number(boost::geometry::get<0>( ptPCenter )), QString::number(boost::geometry::get<1>( ptPCenter )) );
		str += sTemp;		bool bFirstPt = true;
		for (BOOST_AUTO(	it, boost::begin(boost::geometry::exterior_ring(p)));
								it != boost::end(boost::geometry::exterior_ring(p));  ++it)
		{	if (bFirstPt)
				bFirstPt = false;
			else
			{	sTemp = QString( "                  ( %1, %2 )\n" ).arg( QString::number(boost::geometry::get<0>( *it ), 'f', 4 ), 9 ).arg(
																						QString::number(boost::geometry::get<1>( *it ), 'f', 4 ), 9 );
				str += sTemp;
		}	}
	}
	return;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class BEMSpaceDaylitArea;

class BEMDaylitArea
{
public:
	BEMSpaceDaylitArea* m_pParentSpace;
	GeomDBIDs*	m_pGeomDBIDs;
	int			m_i1ObjClass;
	int			m_i0ObjIdx;
	int			m_i0PolyLpObjIdx;
	BEMPoly		m_polyGlazing;					//	polygon representing glazing itself
	BEMPoint		m_ptGlazingCentroid;
	double		m_fGlazingArea;				//	area of glazing
	double		m_fGlazingVisTrans;			// visible transmittance of glazing
	double		m_dDistFromParentCentroid;	// distance from center of glazing to center of parent  (used to decide which daylit area to keep intersecting daylit areas in)

	double		m_fDegreesFromSouth;			// -1 for toplit
	double		m_fEffectiveAperture[2];	// [Prim,Sec]

	BEMPoly		m_polyOrigDaylitArea[2];			//	initial daylit areas, INCLUDING all overlaps w/ other daylit areas and NOT clipped to Space polygon
	BEMPoly		m_polyOrigDaylitInSpc[2];			//	initial daylit areas, INCLUDING all overlaps w/ other daylit areas but clipped to Space polygon
	double		m_dOriginalAreaInSpc[2];			// areas BEFORE EXCLUDING/MERGING overlapping daylit areas (but area only inside Spc poly)

	std::vector<BEMDaylitArea*> m_paIntersectingDaylitAreas;	// array of pointers
	BEMMultiPoly	m_polyFinalDaylit[2];		//	daylit areas AFTER EXCLUDING/MERGING overlapping daylit areas
	double			m_dFinalArea[2];				// areas AFTER EXCLUDING/MERGING overlapping daylit areas

	bool			m_bDLRefPntValid[2];			// whether or not the dayltg ref points were successfully positioned
	bool			m_bDLRefPntInStdLoc[2];		// whether or not the dayltg ref points are positioned in there generic locations or required special re-positioning
	BEMPoint		m_pntDayltgRefPnts[2];		//	daylighting reference points (one for each m_polyFinalDaylit[])
	double		m_dRefPntToSpcCenterDist[2];	// distance from daylighting reference point to the center of the (grandparent) space
	double		m_fRelativeDayltPotential[2];	// [Prim,Sec]
	double		m_dAdjRefPtWinAngle;				// SAC 11/1/16 - new member needed to facilitate latest SecDaylitAreaRefPnt mods

public:
	BEMDaylitArea( BEMSpaceDaylitArea* pParentSpc=NULL, GeomDBIDs* pGeomDBIDs=NULL, int i1ObjClass=0, int i0ObjIdx=-1, double dParentZ=0.0 )
			{	m_pParentSpace = pParentSpc;
				m_pGeomDBIDs = pGeomDBIDs;		m_i1ObjClass = i1ObjClass;		m_i0ObjIdx = i0ObjIdx;		m_i0PolyLpObjIdx = -1;
				bool bAreaOK = false;
				m_dDistFromParentCentroid = 99999;
				m_fGlazingArea = 0;
				m_fGlazingVisTrans = 0;
				if (m_pGeomDBIDs && m_i1ObjClass > 0 && m_i0ObjIdx >= 0 && InitPolyLp() && (IsSidelitArea() || IsToplitArea()))
				{	
					BEMObject* pFenConsObj = NULL;
					if (BEMPX_GetObject( (IsSidelitArea() ? pGeomDBIDs->m_lDBID_Win_FenConsRef :
																			  pGeomDBIDs->m_lDBID_Skylt_FenConsRef), pFenConsObj, BEMP_Obj, m_i0ObjIdx ) && pFenConsObj)
					{	int iFenConsObjIdx = BEMPX_GetObjectIndex( pFenConsObj->getClass(), pFenConsObj );
						if (iFenConsObjIdx < 0)
						{	assert( FALSE );
						}
						else if (!BEMPX_GetFloat( pGeomDBIDs->m_lDBID_FenCons_VT, m_fGlazingVisTrans, 0, BEMP_Flt, iFenConsObjIdx ) || m_fGlazingVisTrans <= 0)
						{	//assert( FALSE );
						}
						else
						{	boost::geometry::clear(m_polyGlazing);
							boost::geometry::clear(m_polyOrigDaylitArea[0]);
							boost::geometry::clear(m_polyOrigDaylitArea[1]);
							boost::geometry::clear(m_polyOrigDaylitInSpc[0]);
							boost::geometry::clear(m_polyOrigDaylitInSpc[1]);
							boost::geometry::clear(m_polyFinalDaylit[0]);
							boost::geometry::clear(m_polyFinalDaylit[1]);
							m_dOriginalAreaInSpc[0] = 0.0;			m_dOriginalAreaInSpc[1] = 0.0;
							m_dFinalArea[0] = 0.0;						m_dFinalArea[1] = 0.0;
							m_bDLRefPntValid[0] = false;				m_bDLRefPntValid[1] = false;
							m_bDLRefPntInStdLoc[0] = false;			m_bDLRefPntInStdLoc[1] = false;
							m_dRefPntToSpcCenterDist[0] = 9999.;	m_dRefPntToSpcCenterDist[1] = 9999.;
							m_fRelativeDayltPotential[0] = -9999;	m_fRelativeDayltPotential[1] = -9999;
							if (IsSidelitArea())
							{	bAreaOK = InitSideDaylitAreas( dParentZ );			assert( bAreaOK );
							}
							else if (IsToplitArea())
							{	bAreaOK = InitTopDaylitArea( dParentZ );			assert( bAreaOK );
							}
							else
								bAreaOK = false;
					}	}
				}
				if (!bAreaOK)
				{	m_fDegreesFromSouth = -9;
					m_fEffectiveAperture[0] = 0;		m_fEffectiveAperture[1] = 0;
					boost::geometry::clear(m_polyGlazing);
					boost::geometry::clear(m_polyOrigDaylitArea[0]);
					boost::geometry::clear(m_polyOrigDaylitArea[1]);
					boost::geometry::clear(m_polyOrigDaylitInSpc[0]);
					boost::geometry::clear(m_polyOrigDaylitInSpc[1]);
					boost::geometry::clear(m_polyFinalDaylit[0]);
					boost::geometry::clear(m_polyFinalDaylit[1]);
					m_dOriginalAreaInSpc[0] = 0.0;			m_dOriginalAreaInSpc[1] = 0.0;
					m_dFinalArea[0] = 0.0;						m_dFinalArea[1] = 0.0;
					m_dDistFromParentCentroid = 99999;
					m_bDLRefPntValid[0] = false;				m_bDLRefPntValid[1] = false;
					m_bDLRefPntInStdLoc[0] = false;			m_bDLRefPntInStdLoc[1] = false;
					m_dRefPntToSpcCenterDist[0] = 9999.;	m_dRefPntToSpcCenterDist[1] = 9999.;
					m_fRelativeDayltPotential[0] = -9999;	m_fRelativeDayltPotential[1] = -9999;
				}
			};

	bool IsValid()		{	return (m_dFinalArea[0] > 0.1 || m_dFinalArea[1] > 0.1);	};
	double PrimArea()	{	return m_dFinalArea[0];	};
	double SecArea()	{	return m_dFinalArea[1];	};

	bool InitPolyLp();
	bool InitSideDaylitAreas(	double dParentZ );
	bool InitTopDaylitArea(		double dParentZ );

	bool AdjustReferencePoint( int idx, BEMSpaceDaylitArea* pSpcDLAs=NULL );
	bool AdjustSecondarySideDaylitRefPnt( BEMSpaceDaylitArea& spcDLAs );		// SAC 11/1/16

	double DistanceFromClosestWindow( BEMPoint& ptChkRefPt, double dMargin, BEMDaylitArea* pDAChk );

	bool IsSidelitArea()	{	return (m_pGeomDBIDs && m_i1ObjClass == m_pGeomDBIDs->m_iOID_Win  );	};
	bool IsToplitArea()	{	return (m_pGeomDBIDs && m_i1ObjClass == m_pGeomDBIDs->m_iOID_Skylt);	};

	double AddressIntersection( BEMDaylitArea* pDaylitArea, bool bSecondaryArea, const char* pszDbgSVGPathFile, BEMPoly& spcPoly, bool bClipSecOnly );

	double GetDaylitArea( int iType /*0-Top/1-PrimSide/2-SecSide*/ )
						{	return  (m_fDegreesFromSouth==-1 ?	(iType==0 ? PrimArea() : 0.0) :
																			(iType==1 ? PrimArea() : (iType==2 ? SecArea() : 0.0)));		};
};


class BEMSpaceDaylitArea
{
public:
	string	m_sSpcName;
	int		m_iSpcObjIdx;
	BEMPoly	m_polySpace;
	BEMPoint m_ptSpcCenter;
	double	m_daSpaceExtremes[4];	// XMin, XMax, YMin, YMax
	bool     m_bRDPCoefsOK;
	double   m_daSpcSkylitRDPCoefs[2];		// RDP = ([0] * EffAp) + [1]
	double   m_daSpcPriSideRDPCoefs[3];		// RDP = ([0] * EffAp) + ([1] * SrcOrient) + [2]
	double   m_daSpcSecSideRDPCoefs[3];		// RDP = ([0] * EffAp) + ([1] * SrcOrient) + [2]
	std::vector<BEMDaylitArea> m_daylitAreas;
	BEMDaylitArea m_dlaTop;
	BEMDaylitArea m_dlaPrim;
	BEMDaylitArea m_dlaSec;
};


////////////////////////////////////////////////////////////////////////////////

//template <typename Geometry1, typename Geometry2>
//void create_svg( const char* filename, Geometry1 const& a, Geometry2 const& b )
//{
//    typedef typename boost::geometry::point_type<Geometry1>::type point_type;
//    std::ofstream svg(filename);  //filename.c_str());
//
//    boost::geometry::svg_mapper<point_type> mapper(svg, 400, 400);
//    mapper.add(a);
//    mapper.add(b);
//
//    mapper.map(a, "fill-rule:nonzero;fill-opacity:0.5;fill:rgb(153,204,0);stroke:rgb(153,204,0);stroke-width:2;");
//    mapper.map(b, "opacity:0.8;fill:none;stroke:rgb(255,128,0);stroke-width:4;stroke-dasharray:1,7;stroke-linecap:round");
//}

template <typename Geometry1>
void CreateSpaceDayltSVG( const char* filename, Geometry1 const& spcPoly, std::vector<BEMDaylitArea>& daylitAreas, int iWhatToPlot )
{
	typedef typename boost::geometry::point_type<Geometry1>::type point_type;
	std::ofstream svg(filename);  //filename.c_str());

	boost::geometry::svg_mapper<point_type> mapper(svg, 800, 540);

	if (daylitAreas.size() > 0)
	{	for (std::vector<BEMDaylitArea>::iterator chk1=daylitAreas.begin(); chk1!=daylitAreas.end(); ++chk1)
		{	BEMDaylitArea* pChk1 = &(*chk1);
			if (pChk1)
			{	int iLpTo = (pChk1->IsToplitArea() ? 1 : 2);
				for (int i=0; i<iLpTo; i++)
				{	switch (iWhatToPlot)
					{	case  0 :	mapper.add( pChk1->m_polyOrigDaylitInSpc[i] );		break;
						case  1 :	//mapper.add( pChk1->m_polyFinalDaylit[0] );	break;
										BOOST_FOREACH(BEMPoly const& p, pChk1->m_polyFinalDaylit[i])
										{	mapper.add( p );
											//if (boost::geometry::area(p) > 0)
										}	break;
					}
					mapper.add( pChk1->m_polyGlazing );
			}	}
	}	}
	mapper.add( spcPoly );

	if (daylitAreas.size() > 0)
	{	for (std::vector<BEMDaylitArea>::iterator chk1=daylitAreas.begin(); chk1!=daylitAreas.end(); ++chk1)
		{	BEMDaylitArea* pChk1 = &(*chk1);
			if (pChk1)
			{	int iLpTo = (pChk1->IsToplitArea() ? 1 : 2);
				for (int i=0; i<iLpTo; i++)
				{	switch (iWhatToPlot)
					{	case  0 :	mapper.map( pChk1->m_polyOrigDaylitInSpc[i],	"fill-rule:nonzero;fill-opacity:0.3;fill:rgb(200,200,0);stroke:rgb(200,200,0);stroke-width:2;");		break;
						case  1 :	//mapper.map( pChk1->m_polyFinalDaylit[0],	"fill-rule:nonzero;fill-opacity:0.3;fill:rgb(200,200,0);stroke:rgb(200,200,0);stroke-width:2;");		break;
										BOOST_FOREACH(BEMPoly const& p, pChk1->m_polyFinalDaylit[i])
										{	mapper.map( p,	"fill-rule:nonzero;fill-opacity:0.3;fill:rgb(200,200,0);stroke:rgb(200,200,0);stroke-width:2;");
										}	break;
					}
					if (pChk1->IsToplitArea())
						mapper.map( pChk1->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(0,220,220);stroke:rgb(0,220,220);stroke-width:1;");
					else
						mapper.map( pChk1->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(0,220,220);stroke:rgb(0,220,220);stroke-width:3;");
			}	}
	}	}
	mapper.map( spcPoly, "opacity:0.8;fill:none;stroke:rgb(128,128,128);stroke-width:3;stroke-dasharray:1,7;stroke-linecap:round");

// SAC 12/10/13 - added daylit area labels
	if (daylitAreas.size() > 0)
	{	for (std::vector<BEMDaylitArea>::iterator chk1=daylitAreas.begin(); chk1!=daylitAreas.end(); ++chk1)
		{	BEMDaylitArea* pChk1 = &(*chk1);
			if (pChk1)
			{	BEMPoint ptAreaCenter;
				string sAreaLbl;
				int iLpTo = (pChk1->IsToplitArea() ? 1 : 2);
				for (int i=0; i<iLpTo; i++)
				{	switch (iWhatToPlot)
					{	case  0 :	boost::geometry::centroid( pChk1->m_polyOrigDaylitInSpc[i], ptAreaCenter );
										//sAreaLbl.Format( "%.1f", boost::geometry::area( pChk1->m_polyOrigDaylitInSpc[i] ) );
										sAreaLbl = boost::str( boost::format( "%.1f" ) % boost::geometry::area( pChk1->m_polyOrigDaylitInSpc[i] ) );
										mapper.text( ptAreaCenter, sAreaLbl, "font-family:sans-serif;font-size:20;text-anchor:middle;fill:rgb(128,0,0)", 0 /*offset_x*/, 5 /*offset_y*/ );		break;
						case  1 :	BOOST_FOREACH(BEMPoly const& p, pChk1->m_polyFinalDaylit[i])
										{	boost::geometry::centroid( p, ptAreaCenter );
											//sAreaLbl.Format( "%.1f", boost::geometry::area( p ) );
											sAreaLbl = boost::str( boost::format( "%.1f" ) % boost::geometry::area( p ) );
											mapper.text( ptAreaCenter, sAreaLbl, "font-family:sans-serif;font-size:20;text-anchor:middle;fill:rgb(128,0,0)", 0 /*offset_x*/, 5 /*offset_y*/ );
										}	break;
			}	}	}
	}	}
}

template <typename Geom1>
void CreateSpaceDayltIntersectSVG( const char* filename, const char* descrip, Geom1 const& spcPoly, BEMDaylitArea* pDLA1, BEMDaylitArea* pDLA2, int iDL1, int iDL2 )
{
	typedef typename boost::geometry::point_type<Geom1>::type point_type;

	QString sFN;
	sFN = QString( "%1 - %2%3-%4%5-%6.svg" ).arg( filename,	QString::number(pDLA1->m_i0ObjIdx), (pDLA1->IsToplitArea() ? "top" : (iDL1==0 ? "pri" : "sec")),
																			QString::number(pDLA2->m_i0ObjIdx), (pDLA2->IsToplitArea() ? "top" : (iDL2==0 ? "pri" : "sec")), descrip );
	std::ofstream svg( sFN );  //filename.c_str());
	boost::geometry::svg_mapper<point_type> mapper(svg, 800, 540);

	//mapper.add( pDLA1->m_polyFinalDaylit[0] );
	//mapper.add( pDLA2->m_polyFinalDaylit[0] );
	BOOST_FOREACH(BEMPoly const& p1, pDLA1->m_polyFinalDaylit[iDL1])
	{	mapper.add( p1 );
	}
	BOOST_FOREACH(BEMPoly const& p2, pDLA2->m_polyFinalDaylit[iDL2])
	{	mapper.add( p2 );
	}
	mapper.add( pDLA1->m_polyGlazing );
	mapper.add( pDLA2->m_polyGlazing );
	mapper.add( spcPoly );

	//mapper.map( pDLA1->m_polyFinalDaylit[0],   "fill-rule:nonzero;fill-opacity:0.4;fill:rgb(200,200,0);stroke:rgb(200,200,0);stroke-width:2;");
	//mapper.map( pDLA2->m_polyFinalDaylit[0],   "fill-rule:nonzero;fill-opacity:0.2;fill:rgb(200,200,0);stroke:rgb(200,200,0);stroke-width:2;");
	BOOST_FOREACH(BEMPoly const& p1, pDLA1->m_polyFinalDaylit[iDL1])
	{	mapper.map( p1, "fill-rule:nonzero;fill-opacity:0.4;fill:rgb(200,200,0);stroke:rgb(200,200,0);stroke-width:2;" );
	}
	BOOST_FOREACH(BEMPoly const& p2, pDLA2->m_polyFinalDaylit[iDL2])
	{	mapper.map( p2, "fill-rule:nonzero;fill-opacity:0.2;fill:rgb(200,200,0);stroke:rgb(200,200,0);stroke-width:2;" );
	}
	if (pDLA1->IsToplitArea())
		mapper.map( pDLA1->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(0,220,220);stroke:rgb(0,220,220);stroke-width:1;");
	else
		mapper.map( pDLA1->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(0,220,220);stroke:rgb(0,220,220);stroke-width:3;");
	if (pDLA2->IsToplitArea())
		mapper.map( pDLA2->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(0,220,220);stroke:rgb(0,220,220);stroke-width:1;");
	else
		mapper.map( pDLA2->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(0,220,220);stroke:rgb(0,220,220);stroke-width:3;");
	mapper.map( spcPoly, "opacity:0.8;fill:none;stroke:rgb(128,128,128);stroke-width:3;stroke-dasharray:1,7;stroke-linecap:round");

// SAC 12/10/13 - added daylit area labels
	BEMPoint ptAreaCenter;
	string sAreaLbl;
	boost::geometry::centroid( pDLA1->m_polyFinalDaylit[iDL1], ptAreaCenter );
	sAreaLbl = boost::str( boost::format( "%.1f" ) % boost::geometry::area( pDLA1->m_polyFinalDaylit[iDL1] ) );
	mapper.text( ptAreaCenter, sAreaLbl, "font-family:sans-serif;font-size:20;text-anchor:middle;fill:rgb(128,0,0)", 0 /*offset_x*/, 5 /*offset_y*/ );
	boost::geometry::centroid( pDLA2->m_polyFinalDaylit[iDL2], ptAreaCenter );
	sAreaLbl = boost::str( boost::format( "%.1f" ) % boost::geometry::area( pDLA2->m_polyFinalDaylit[iDL2] ) );
	mapper.text( ptAreaCenter, sAreaLbl, "font-family:sans-serif;font-size:20;text-anchor:middle;fill:rgb(128,0,0)", 0 /*offset_x*/, 5 /*offset_y*/ );
}


////////////////////////////////////////////////////////////////////////////////

bool ClosestToParentCenter( BEMDaylitArea i, BEMDaylitArea j )
{ return (i.m_dDistFromParentCentroid < j.m_dDistFromParentCentroid);
}

bool ClosestToParentCenterPtr1( BEMDaylitArea* p1, BEMDaylitArea* p2 )
{ return (p1->m_dRefPntToSpcCenterDist[0] < p2->m_dRefPntToSpcCenterDist[0]);
}
bool ClosestToParentCenterPtr2( BEMDaylitArea* p1, BEMDaylitArea* p2 )
{ return (p1->m_dRefPntToSpcCenterDist[1] < p2->m_dRefPntToSpcCenterDist[1]);
}

static inline double RoundDbl( double dVal, double dDivPerUnit )
{	return (dDivPerUnit <= 0.0 ? 0.0 : floor( ((dVal * dDivPerUnit) + 0.5) ) / dDivPerUnit);
}

bool BEMDaylitArea::InitPolyLp()
{	bool bRetVal = false;
	int iNumChildPolyLps = (int) BEMPX_GetNumChildren( m_i1ObjClass, m_i0ObjIdx, BEMO_User, m_pGeomDBIDs->m_iOID_PolyLp );
	if (iNumChildPolyLps < 1)
	{	//dDaylitArea = -1;
		//sErrMsg.Format( "Space PolyLp not found for space '%s'", pszSpcName );
	}
	else if (iNumChildPolyLps > 1)
	{	//dDaylitArea = -2;
		//sErrMsg.Format( "Too many space PolyLp objects found (%d, should be only 1) for space '%s'", QString::number(iNumSpcPolyLps), pszSpcName );
	}
	else
	{	int iError;
		BEM_ObjType eObjType = BEMO_User;
		m_i0PolyLpObjIdx = BEMPX_GetChildObjectIndex( m_i1ObjClass, m_pGeomDBIDs->m_iOID_PolyLp, iError, eObjType, 1, m_i0ObjIdx );		assert( m_i0PolyLpObjIdx >= 0 );
		bRetVal = (m_i0PolyLpObjIdx >= 0);
	}
	return bRetVal;
}

//	int LoadReferencePoint( BEMPoint& pntRefPnt, BEMPoly& polySpace, BEMPoint& ptSpcCenter, BEMPoint& ptGlzCenter, BEMPoint& ptRef1, BEMPoint& ptRef2 ) 
//	{	int iRetVal = 0;
//		bool bPt1InSpc = boost::geometry::within( ptRef1, polySpace );
//		bool bPt2InSpc = boost::geometry::within( ptRef2, polySpace );
//		double dDistPt1SpcCtr = boost::geometry::distance( ptRef1, ptSpcCenter );
//		double dDistPt2SpcCtr = boost::geometry::distance( ptRef2, ptSpcCenter );
//		if (bPt1InSpc && (!bPt2InSpc || (dDistPt1SpcCtr <= dDistPt2SpcCtr)))
//		{	pntRefPnt = ptRef1;
//			iRetVal = 1;
//		}
//		else if (bPt2InSpc && (!bPt1InSpc || (dDistPt2SpcCtr <= dDistPt1SpcCtr)))
//		{	assert( FALSE );  // just checking to see if this ever happens !!
//			pntRefPnt = ptRef2;
//			iRetVal = 2;
//		}
//		else
//		{	// NEITHER point is inside the space
//	//		assert( FALSE );  // TO DO
//											pntRefPnt = ptRef1;
//			iRetVal = 3;  // => m_bDLRefPntInStdLoc[*] flag should get set to false (else true)
//		}
//		return iRetVal;
//	}

// SAC 11/1/16 - mods to ensure that SecSideDaylitRefPnts are NOT located inside Primary side daylit areas (of other glazings)
bool PointInPrimSideDaylitArea( BEMPoint& pt, BEMSpaceDaylitArea* pSpcDLAs )
{	bool bRetVal = false;
	for (std::vector<BEMDaylitArea>::iterator chk1=pSpcDLAs->m_daylitAreas.begin(); (!bRetVal && chk1!=pSpcDLAs->m_daylitAreas.end()); ++chk1)
	{	BEMDaylitArea* pChk1 = &(*chk1);
		if (pChk1 && pChk1->IsSidelitArea() && pChk1->m_dFinalArea[0] >= 0.1)
			bRetVal = boost::geometry::within( pt, pChk1->m_polyOrigDaylitArea[0] );
	}
	return bRetVal;
}

typedef boost::geometry::model::linestring<BEMPoint> BEMLine;

bool BEMDaylitArea::AdjustReferencePoint( int idx, BEMSpaceDaylitArea* pSpcDLAs )
{	bool bRetVal = false;
	double dRefPtX = boost::geometry::get<0>( m_pntDayltgRefPnts[idx] );
	double dRefPtY = boost::geometry::get<1>( m_pntDayltgRefPnts[idx] );
	if (IsSidelitArea())
	{	
		try		// SAC 6/10/15 - catch bugs in boost::geometry
		{
	// first attempt - simply move the point 3" toward window, which should help if the ref pt is right on the border of the space
		m_pntDayltgRefPnts[idx].set<0>( (dRefPtX + (0.25 * cos( m_dAdjRefPtWinAngle ))) );
		m_pntDayltgRefPnts[idx].set<1>( (dRefPtY + (0.25 * sin( m_dAdjRefPtWinAngle ))) );
		if (boost::geometry::within( m_pntDayltgRefPnts[idx], m_pParentSpace->m_polySpace ) &&
			 (idx==0 || !PointInPrimSideDaylitArea( m_pntDayltgRefPnts[idx], pSpcDLAs )))	// SAC 11/1/16
			bRetVal = true;
		else
		{	BEMPoint ptOrigDaylitAreaCenter;
	// Second attempt - find an intersection between a line connecting the glazing centroid and the default dayltg ref point and the space boundary, and if found, move point 3" in from space boundary
			boost::geometry::centroid( m_polyOrigDaylitArea[idx], ptOrigDaylitAreaCenter );
			BEMLine mptRefPtLine;
			if (idx == 0)	// SAC 6/21/16 - revised mptRefPtLine to go from dayltg ref point to glazing centroid - prev version was ref pt to daylit area centroid, which doesn't work for spaces narrower than 1/2 daylit area depth (tic #1717)
				boost::geometry::append( mptRefPtLine, m_ptGlazingCentroid );
			else
				boost::geometry::append( mptRefPtLine, ptOrigDaylitAreaCenter );
			boost::geometry::append( mptRefPtLine, BEMPoint( dRefPtX, dRefPtY ) );

			std::deque<BEMPoint> ptaIntPts;
			boost::geometry::intersection( m_pParentSpace->m_polySpace, mptRefPtLine, ptaIntPts );		// calculate intersection of space and ref point line segment
			double dMaxDistFromGlz = 0.;
			BEMPoint ptNewRefPt;
			BOOST_FOREACH(BEMPoint const& p, ptaIntPts)
			{	if (boost::geometry::distance( p, m_ptGlazingCentroid ) > dMaxDistFromGlz)
				{	ptNewRefPt = p;
					dMaxDistFromGlz = boost::geometry::distance( p, m_ptGlazingCentroid );
			}	}
			if (dMaxDistFromGlz > 0.3)
			{	m_pntDayltgRefPnts[idx].set<0>( (boost::geometry::get<0>( ptNewRefPt ) + (0.25 * cos( m_dAdjRefPtWinAngle ))) );
				m_pntDayltgRefPnts[idx].set<1>( (boost::geometry::get<1>( ptNewRefPt ) + (0.25 * sin( m_dAdjRefPtWinAngle ))) );
				if (boost::geometry::within( m_pntDayltgRefPnts[idx], m_pParentSpace->m_polySpace ) &&
					 (idx==0 || !PointInPrimSideDaylitArea( m_pntDayltgRefPnts[idx], pSpcDLAs )))	// SAC 11/1/16
					bRetVal = true;
			}

			if (!bRetVal && m_dFinalArea[idx] > 0)
			{
	// Last resort => find points 6" in (toward daylit area centroid) from each daylit area vertex and return the furthest of those from the glazing centroid
				BEMPoint ptTemp, ptCurDaylitAreaCenter;
				double dTemp, dFurthestDist = 0.;
				boost::geometry::centroid( m_polyFinalDaylit[idx], ptCurDaylitAreaCenter );
				BOOST_FOREACH(BEMPoly const& p, m_polyFinalDaylit[idx])
				{	for (BOOST_AUTO(	it, boost::begin(boost::geometry::exterior_ring(p)));
											it != boost::end(boost::geometry::exterior_ring(p));  ++it)
					{	double dAngVertToCtr = LineAngle(	boost::geometry::get<0>( *it ), boost::geometry::get<0>( ptCurDaylitAreaCenter ),
																		boost::geometry::get<1>( *it ), boost::geometry::get<1>( ptCurDaylitAreaCenter ), 0.01 );
						// SAC 6/21/16 - revised point from 3" into space to 6" (tic #1717)
						ptTemp.set<0>( (boost::geometry::get<0>( *it ) + (0.5 * cos( dAngVertToCtr ))) );  // move point 6" toward centroid of daylit area
						ptTemp.set<1>( (boost::geometry::get<1>( *it ) + (0.5 * sin( dAngVertToCtr ))) );
						dTemp = boost::geometry::distance( ptTemp, m_ptGlazingCentroid );
						if (dTemp > dFurthestDist && boost::geometry::within( ptTemp, m_pParentSpace->m_polySpace ) &&
							 (idx==0 || !PointInPrimSideDaylitArea( ptTemp, pSpcDLAs )))	// SAC 11/1/16
						{	dFurthestDist = dTemp;
							m_pntDayltgRefPnts[idx] = ptTemp;
							bRetVal = true;
				}	}	}
			}
			assert( (bRetVal || idx > 0) );		// other re-positioning required ??   - this CAN happen for an individual glazing Sec daylit area that overlaps w/ Prim daylit area of other glazings
		}


		}
		catch (std::exception& e)
		{	QString sErrMsg;
			if (m_pParentSpace)
				sErrMsg = QString( "BEMDaylitArea::AdjustReferencePoint() error processing space '%1':  %2" ).arg( m_pParentSpace->m_sSpcName.c_str(), e.what() );
			else
				sErrMsg = QString( "BEMDaylitArea::AdjustReferencePoint() error:  %1" ).arg( e.what() );
			BEMPX_WriteLogFile( sErrMsg );
			bRetVal = false;
		}
		catch (...)
		{	QString sErrMsg;
			if (m_pParentSpace)
				sErrMsg = QString( "BEMDaylitArea::AdjustReferencePoint() error processing space '%2':  suspect boost::geometry library error" ).arg( m_pParentSpace->m_sSpcName.c_str() );
			else
				sErrMsg = "BEMDaylitArea::AdjustReferencePoint() error:  suspect boost::geometry library error";
			BEMPX_WriteLogFile( sErrMsg );
			bRetVal = false;
		}
	}
	else
	{
// TO DO
			assert( bRetVal );
	// for each of the four default ref pnts - find an intersection between the line connecting the glazing centroid and the ref point and the space boundary.
	//			Choose the line/space intersection furthest from the glazing centroid (or using the following priority if multiple identical distances: S-W-E-N) 
	//			and move the ref point 3" in from space boundary
	}

	if (bRetVal)
	{	m_bDLRefPntValid[idx]		= true;					// whether or not the dayltg ref point was successfully positioned
		m_bDLRefPntInStdLoc[idx]	= false;					// whether or not the dayltg ref point is positioned in its generic location or required special re-positioning
	}

	return bRetVal;
}

bool BEMDaylitArea::AdjustSecondarySideDaylitRefPnt( BEMSpaceDaylitArea& spcDLAs )		// SAC 11/1/16
{
		// SAC 11/1/16 - moved following code into AdjustSecondarySideDaylitRefPnt() in order to ensure SecSideDaylitRefPnts are NOT located inside Primary side daylit areas (of other glazings)
					if (boost::geometry::within( m_pntDayltgRefPnts[1], m_pParentSpace->m_polySpace ) &&
						 !PointInPrimSideDaylitArea( m_pntDayltgRefPnts[1], &spcDLAs ))	// SAC 11/1/16
					{	m_bDLRefPntValid[1]		= true;					// whether or not the dayltg ref point was successfully positioned
						m_bDLRefPntInStdLoc[1]	= true;					// whether or not the dayltg ref point is positioned in its generic location or required special re-positioning
					}
					else
						AdjustReferencePoint( 1, &spcDLAs );
					if (m_bDLRefPntValid[1])
						m_dRefPntToSpcCenterDist[1] = boost::geometry::distance( m_pntDayltgRefPnts[1], m_pParentSpace->m_ptSpcCenter );
	return m_bDLRefPntValid[1];
}

bool BEMDaylitArea::InitSideDaylitAreas( double dParentZ )
{	bool bRetVal = false;
	int iError;
	BEM_ObjType eObjType = BEMO_User;
	double fCoords[3];
	vector<double> faWinX, faWinY, faWinZ;
	double dMinZ=99999., dMaxZ=-99999.;
//	dAvgZ = dZRange = 0.0;
	double dX1=0.0, dX2=0.0, dY1=0.0, dY2=0.0;
	m_fRelativeDayltPotential[0] = -9999;
	m_fRelativeDayltPotential[1] = -9999;
	bool bFound1=false, bFound2=false;
	int iNumPts = (int) BEMPX_GetNumChildren( m_pGeomDBIDs->m_iOID_PolyLp, m_i0PolyLpObjIdx, BEMO_User, m_pGeomDBIDs->m_iOID_CartesianPt );								assert( iNumPts == 4 );
	for (int i=0; i < iNumPts; i++)
	{	
		int iCartPtObjIdx = BEMPX_GetChildObjectIndex( m_pGeomDBIDs->m_iOID_PolyLp, m_pGeomDBIDs->m_iOID_CartesianPt, iError, eObjType, i+1, m_i0PolyLpObjIdx );		assert( iCartPtObjIdx >= 0 );
		if (iCartPtObjIdx >= 0)
		{	int iNumCoords = BEMPX_GetFloatArray( m_pGeomDBIDs->m_lDBID_CartesianPt_Coord, fCoords, 3, 0, BEMP_Flt, iCartPtObjIdx );											assert( iNumCoords == 3 );
			if (iNumCoords == 3)
			{	if (fCoords[2] > dMaxZ)
					dMaxZ = (double) fCoords[2];
				if (fCoords[2] < (dMinZ - 0.1))
				{	bFound1 = true;		bFound2 = false;
					dX1 = (double) fCoords[0];
					dY1 = (double) fCoords[1];
					dMinZ = (double) fCoords[2];
				}
				else if (fCoords[2] < (dMinZ + 0.1))
				{	assert( bFound1 && !bFound2 );
					bFound2 = true;
					dX2 = (double) fCoords[0];
					dY2 = (double) fCoords[1];
				}
				faWinX.push_back( fCoords[0] );	faWinY.push_back( fCoords[1] );	faWinZ.push_back( fCoords[2] );
	}	}	}
	if (bFound1 && bFound2)
	{	double dWinHeadHt = dMaxZ - dParentZ;
		double dWinWidth = sqrt( ((dX2-dX1)*(dX2-dX1)) + ((dY2-dY1)*(dY2-dY1)) );
		double dWinArea = (dMaxZ - dMinZ) * dWinWidth;
		if (dWinHeadHt <= 0.1)
		{	assert( FALSE );
// Error: invalid window head height
		}
		else if (dWinWidth < 0.1)
		{	assert( FALSE );
// Error: invalid window width
		}
		else if (dWinArea < 0.1)
		{	assert( FALSE );
// Error: invalid window area
		}
		else if (m_pParentSpace == NULL)
		{	assert( FALSE );
// Error: invalid space object pointer
		}
		else
		{	double dWinAngle    = LineAngle( dX1, dX2, dY1, dY2, 0.01 );
			double dWinAngleOpp = dWinAngle + (dWinAngle >= sdPi ? -sdPi : sdPi);
			double dX1a = dX1 + (dWinHeadHt * 0.5 * cos( dWinAngleOpp ));
			double dY1a = dY1 + (dWinHeadHt * 0.5 * sin( dWinAngleOpp ));
			double dX2a = dX2 + (dWinHeadHt * 0.5 * cos( dWinAngle    ));
			double dY2a = dY2 + (dWinHeadHt * 0.5 * sin( dWinAngle    ));
			double dWinAnglePerp1 = dWinAngle + (dWinAngle >= sdHalfPi ? -sdHalfPi : sd3HalfPi);

			try		// SAC 6/10/15 - catch bugs in boost::geometry
			{
		// store narrow polygon along 2D line representing cross-section of window - about 1" thick
			boost::geometry::append(  m_polyGlazing, boost::tuples::make_tuple( (dX2 + (0.04 * cos( dWinAnglePerp1 ))), (dY2 + (0.04 * sin( dWinAnglePerp1 ))) ));
			boost::geometry::append(  m_polyGlazing, boost::tuples::make_tuple( (dX1 + (0.04 * cos( dWinAnglePerp1 ))), (dY1 + (0.04 * sin( dWinAnglePerp1 ))) ));
			boost::geometry::append(  m_polyGlazing, boost::tuples::make_tuple( (dX1 - (0.04 * cos( dWinAnglePerp1 ))), (dY1 - (0.04 * sin( dWinAnglePerp1 ))) ));
			boost::geometry::append(  m_polyGlazing, boost::tuples::make_tuple( (dX2 - (0.04 * cos( dWinAnglePerp1 ))), (dY2 - (0.04 * sin( dWinAnglePerp1 ))) ));
			boost::geometry::correct( m_polyGlazing );	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed
// this boost poly NOT valid for glazing area calc, as it is a 2-D representation of a 3-D glazing
//			m_fGlazingArea = (double) boost::geometry::area( m_polyGlazing );
			m_fGlazingArea = PolygonArea( faWinX, faWinY, faWinZ );
		// set distance from centroid of primary daylit area to centroid of parent surface
//			BEMPoint glazCentroid;
	//		boost::geometry::centroid( m_polyGlazing, glazCentroid );
	// SAC 12/11/13 - for some reason, the centroid routine fails for windows - perhaps having to do w/ how thin the poly is?? - easy to calc manually though (below)
			m_ptGlazingCentroid.set<0>( (dX1+dX2)/2 );
			m_ptGlazingCentroid.set<1>( (dY1+dY2)/2 );

			m_dDistFromParentCentroid = boost::geometry::distance( m_ptGlazingCentroid, m_pParentSpace->m_ptSpcCenter );
//			m_dDistFromParentCentroid = sqrt( ((dParentCentroidX-glazCentroid.x)*(dParentCentroidX-glazCentroid.x)) + ((dParentCentroidY-glazCentroid.y)*(dParentCentroidY-glazCentroid.y)) );

			BEMPoly polyTemp;
			double dPrimX1 = (dX2a + (dWinHeadHt * cos( dWinAnglePerp1 ))),		dPrimY1 = (dY2a + (dWinHeadHt * sin( dWinAnglePerp1 )));
			double dPrimX2 = (dX1a + (dWinHeadHt * cos( dWinAnglePerp1 ))),		dPrimY2 = (dY1a + (dWinHeadHt * sin( dWinAnglePerp1 )));
			double dPrimX3 = (dX1a - (dWinHeadHt * cos( dWinAnglePerp1 ))),		dPrimY3 = (dY1a - (dWinHeadHt * sin( dWinAnglePerp1 )));
			double dPrimX4 = (dX2a - (dWinHeadHt * cos( dWinAnglePerp1 ))),		dPrimY4 = (dY2a - (dWinHeadHt * sin( dWinAnglePerp1 )));

			double dInOutMult = 1.0;
			BEMPoint ptPosSide, ptNegSide;
			ptPosSide.set<0>( (((dX1+dX2)/2) + (0.75 * cos( dWinAnglePerp1 ))) );
			ptPosSide.set<1>( (((dY1+dY2)/2) + (0.75 * sin( dWinAnglePerp1 ))) );
			ptNegSide.set<0>( (((dX1+dX2)/2) - (0.75 * cos( dWinAnglePerp1 ))) );
			ptNegSide.set<1>( (((dY1+dY2)/2) - (0.75 * sin( dWinAnglePerp1 ))) );
			if (boost::geometry::within( ptPosSide, m_pParentSpace->m_polySpace ) && !boost::geometry::within( ptNegSide, m_pParentSpace->m_polySpace ))
			{	boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl( dPrimX1, 24.0 ), RoundDbl( dPrimY1, 24.0 ) ));    // rounds to nearest 0.05 (half inch)
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl( dPrimX2, 24.0 ), RoundDbl( dPrimY2, 24.0 ) ));
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl(    dX1a, 24.0 ), RoundDbl(    dY1a, 24.0 ) ));
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl(    dX2a, 24.0 ), RoundDbl(    dY2a, 24.0 ) ));
			}
			else if (!boost::geometry::within( ptPosSide, m_pParentSpace->m_polySpace ) && boost::geometry::within( ptNegSide, m_pParentSpace->m_polySpace ))
			{	dInOutMult = -1.0;
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl(    dX2a, 24.0 ), RoundDbl(    dY2a, 24.0 ) ));    // rounds to nearest 0.05 (half inch)
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl(    dX1a, 24.0 ), RoundDbl(    dY1a, 24.0 ) ));
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl( dPrimX3, 24.0 ), RoundDbl( dPrimY3, 24.0 ) ));
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl( dPrimX4, 24.0 ), RoundDbl( dPrimY4, 24.0 ) ));
			}
			else
			{	assert( FALSE );  // points perpendicular to window and offset 0.5 ft from win centroid should NOT both be inside or both be outside window!!
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl( dPrimX1, 24.0 ), RoundDbl( dPrimY1, 24.0 ) ));    // rounds to nearest 0.05 (half inch)
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl( dPrimX2, 24.0 ), RoundDbl( dPrimY2, 24.0 ) ));
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl( dPrimX3, 24.0 ), RoundDbl( dPrimY3, 24.0 ) ));
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl( dPrimX4, 24.0 ), RoundDbl( dPrimY4, 24.0 ) ));
			}
			boost::geometry::correct( polyTemp );	// polygon should contain clockwise vertices (but vertex order is one of the things corrected via correct() call)
			m_polyOrigDaylitArea[0] = polyTemp;

			std::deque<BEMPoly> output;
			boost::geometry::intersection( m_pParentSpace->m_polySpace, polyTemp, output );		// calculate intersection of space and daylit area
			int iNumPolys = 0;
			BOOST_FOREACH(BEMPoly const& p, output)
			{	iNumPolys++;
				if (boost::geometry::area(p) > m_dFinalArea[0])
				{	m_polyOrigDaylitInSpc[0] = p;
					m_dFinalArea[0] = boost::geometry::area(p);
				}
			}	assert( iNumPolys == 1 );
	// ??? effective aperture based on total target daylit area, or intersection of daylit area and space polygon
	//		m_fEffectiveAperture[0] = (double) (m_dFinalArea[0] <= 0 ? 0 : (dWinArea * fVisTrans) / m_dFinalArea[0]);
			m_dOriginalAreaInSpc[0] = m_dFinalArea[0];
			//m_polyFinalDaylit[0] = m_polyOrigDaylitInSpc[0];
			m_polyFinalDaylit[0].push_back( m_polyOrigDaylitInSpc[0] );

			if (m_dFinalArea[0] < 0.1)		// don't bother calc'ing secondary sidelit area if no primary area found
			{	boost::geometry::clear( m_polyOrigDaylitArea[1] );
				boost::geometry::clear( m_polyOrigDaylitInSpc[1] );
				m_dFinalArea[1] = 0.0;
				m_dOriginalAreaInSpc[1] = 0.0;
				m_fEffectiveAperture[1] = 0.0;
				boost::geometry::clear( m_pntDayltgRefPnts[0] );
				boost::geometry::clear( m_pntDayltgRefPnts[1] );
			}
			else
			{	m_dAdjRefPtWinAngle = dWinAnglePerp1;
				if (dInOutMult > 0)
					m_dAdjRefPtWinAngle += (sdPi * (m_dAdjRefPtWinAngle >= sdPi ? -1.0 : 1.0));
			//	daylighting reference points (one for each m_polyFinalDaylit[])
		//		BEMPoint	ptRef1, ptRef2;
		//		ptRef1.set<0>( (dPrimX3 + dPrimX4) / 2.0 );
		//		ptRef1.set<1>( (dPrimY3 + dPrimY4) / 2.0 );
		//		ptRef2.set<0>( (dPrimX1 + dPrimX2) / 2.0 );
		//		ptRef2.set<1>( (dPrimY1 + dPrimY2) / 2.0 );
		//		int iLRPRet = LoadReferencePoint( m_pntDayltgRefPnts[0], m_pParentSpace->m_polySpace, m_pParentSpace->m_ptSpcCenter, glazCentroid, ptRef1, ptRef2 );
		//		m_bDLRefPntValid[0]		= (iLRPRet == 1 || iLRPRet == 2);	// whether or not the dayltg ref points were successfully positioned
		//		m_bDLRefPntInStdLoc[0]	= (iLRPRet != 3);							// whether or not the dayltg ref points are positioned in there generic locations or required special re-positioning
				if (dInOutMult < 0.)
				{	m_pntDayltgRefPnts[0].set<0>( (dPrimX3 + dPrimX4) / 2.0 );
					m_pntDayltgRefPnts[0].set<1>( (dPrimY3 + dPrimY4) / 2.0 );
				}
				else
				{	m_pntDayltgRefPnts[0].set<0>( (dPrimX1 + dPrimX2) / 2.0 );
					m_pntDayltgRefPnts[0].set<1>( (dPrimY1 + dPrimY2) / 2.0 );
				}
				if (boost::geometry::within( m_pntDayltgRefPnts[0], m_pParentSpace->m_polySpace ))
				{	m_bDLRefPntValid[0]		= true;					// whether or not the dayltg ref point was successfully positioned
					m_bDLRefPntInStdLoc[0]	= true;					// whether or not the dayltg ref point is positioned in its generic location or required special re-positioning
				}
				else
					AdjustReferencePoint( 0 );
				if (m_bDLRefPntValid[0])
					m_dRefPntToSpcCenterDist[0] = boost::geometry::distance( m_pntDayltgRefPnts[0], m_pParentSpace->m_ptSpcCenter );

		//		BEMPoly polyTempSec;
		//		double dSecX1,	dSecY1, dSecX2, dSecY2, dSecX3, dSecY3, dSecX4, dSecY4;
		//		dSecX1 = (dX2a + (dWinHeadHt*2 * cos( dWinAnglePerp1 )));		dSecY1 = (dY2a + (dWinHeadHt*2 * sin( dWinAnglePerp1 )));
		//		dSecX2 = (dX1a + (dWinHeadHt*2 * cos( dWinAnglePerp1 )));		dSecY2 = (dY1a + (dWinHeadHt*2 * sin( dWinAnglePerp1 )));
		//		dSecX3 = (dX1a - (dWinHeadHt*2 * cos( dWinAnglePerp1 )));		dSecY3 = (dY1a - (dWinHeadHt*2 * sin( dWinAnglePerp1 )));
		//		dSecX4 = (dX2a - (dWinHeadHt*2 * cos( dWinAnglePerp1 )));		dSecY4 = (dY2a - (dWinHeadHt*2 * sin( dWinAnglePerp1 )));
				double dSecX1,	dSecY1, dSecX2, dSecY2;
				if (dInOutMult < 0.)
				{	dSecX1 = (dX1a - (dWinHeadHt*2 * cos( dWinAnglePerp1 )));		dSecY1 = (dY1a - (dWinHeadHt*2 * sin( dWinAnglePerp1 )));
					dSecX2 = (dX2a - (dWinHeadHt*2 * cos( dWinAnglePerp1 )));		dSecY2 = (dY2a - (dWinHeadHt*2 * sin( dWinAnglePerp1 )));
					boost::geometry::append(  m_polyOrigDaylitArea[1], boost::tuples::make_tuple( RoundDbl(  dSecX1, 24.0 ), RoundDbl(  dSecY1, 24.0 ) ));     // rounds to nearest 0.05 (half inch)
					boost::geometry::append(  m_polyOrigDaylitArea[1], boost::tuples::make_tuple( RoundDbl(  dSecX2, 24.0 ), RoundDbl(  dSecY2, 24.0 ) ));
					boost::geometry::append(  m_polyOrigDaylitArea[1], boost::tuples::make_tuple( RoundDbl( dPrimX4, 24.0 ), RoundDbl( dPrimY4, 24.0 ) ));
					boost::geometry::append(  m_polyOrigDaylitArea[1], boost::tuples::make_tuple( RoundDbl( dPrimX3, 24.0 ), RoundDbl( dPrimY3, 24.0 ) ));
				}
				else
				{	dSecX1 = (dX2a + (dWinHeadHt*2 * cos( dWinAnglePerp1 )));		dSecY1 = (dY2a + (dWinHeadHt*2 * sin( dWinAnglePerp1 )));
					dSecX2 = (dX1a + (dWinHeadHt*2 * cos( dWinAnglePerp1 )));		dSecY2 = (dY1a + (dWinHeadHt*2 * sin( dWinAnglePerp1 )));
					boost::geometry::append(  m_polyOrigDaylitArea[1], boost::tuples::make_tuple( RoundDbl(  dSecX1, 24.0 ), RoundDbl(  dSecY1, 24.0 ) ));     // rounds to nearest 0.05 (half inch)
					boost::geometry::append(  m_polyOrigDaylitArea[1], boost::tuples::make_tuple( RoundDbl(  dSecX2, 24.0 ), RoundDbl(  dSecY2, 24.0 ) ));
					boost::geometry::append(  m_polyOrigDaylitArea[1], boost::tuples::make_tuple( RoundDbl( dPrimX2, 24.0 ), RoundDbl( dPrimY2, 24.0 ) ));
					boost::geometry::append(  m_polyOrigDaylitArea[1], boost::tuples::make_tuple( RoundDbl( dPrimX1, 24.0 ), RoundDbl( dPrimY1, 24.0 ) ));
				}

				// polygon should contain clockwise vertices (but vertex order is one of the things corrected via correct() call)
		//		boost::geometry::append(  polyTempSec, boost::tuples::make_tuple( RoundDbl(  dSecX1, 24.0 ), RoundDbl(  dSecY1, 24.0 ) ));     // rounds to nearest 0.05 (half inch)
		//		boost::geometry::append(  polyTempSec, boost::tuples::make_tuple( RoundDbl(  dSecX2, 24.0 ), RoundDbl(  dSecY2, 24.0 ) ));
		//		boost::geometry::append(  polyTempSec, boost::tuples::make_tuple( RoundDbl( dPrimX2, 24.0 ), RoundDbl( dPrimY2, 24.0 ) ));
		//		boost::geometry::append(  polyTempSec, boost::tuples::make_tuple( RoundDbl( dPrimX1, 24.0 ), RoundDbl( dPrimY1, 24.0 ) ));
		//		boost::geometry::correct( polyTempSec );	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed
		//		m_polyOrigDaylitArea[1] = polyTempSec;
				boost::geometry::correct( m_polyOrigDaylitArea[1] );	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed

				std::deque<BEMPoly> outputSec;
				boost::geometry::intersection( m_pParentSpace->m_polySpace, m_polyOrigDaylitArea[1], outputSec );		// calculate intersection of space and daylit area
				int iNumSecPolys = 0;
				BOOST_FOREACH(BEMPoly const& p, outputSec)
				{	iNumSecPolys++;
					if (boost::geometry::area(p) > m_dFinalArea[1])
					{	m_polyOrigDaylitInSpc[1] = p;
						m_dFinalArea[1] = boost::geometry::area(p);
					}
				}	assert( iNumSecPolys <= 1 );
		//	// AND ALSO try opposing secondary daylit area --
		//		boost::geometry::clear( polyTempSec );
		//		//boost::geometry::append(  polyTempSec, boost::tuples::make_tuple(  dSecX3,  dSecY3 ));
		//		//boost::geometry::append(  polyTempSec, boost::tuples::make_tuple(  dSecX4,  dSecY4 ));
		//		//boost::geometry::append(  polyTempSec, boost::tuples::make_tuple( dPrimX4, dPrimY4 ));
		//		//boost::geometry::append(  polyTempSec, boost::tuples::make_tuple( dPrimX3, dPrimY3 ));
		//		boost::geometry::append(  polyTempSec, boost::tuples::make_tuple( RoundDbl(  dSecX3, 24.0 ), RoundDbl(  dSecY3, 24.0 ) ));     // rounds to nearest 0.05 (half inch)
		//		boost::geometry::append(  polyTempSec, boost::tuples::make_tuple( RoundDbl(  dSecX4, 24.0 ), RoundDbl(  dSecY4, 24.0 ) ));
		//		boost::geometry::append(  polyTempSec, boost::tuples::make_tuple( RoundDbl( dPrimX4, 24.0 ), RoundDbl( dPrimY4, 24.0 ) ));
		//		boost::geometry::append(  polyTempSec, boost::tuples::make_tuple( RoundDbl( dPrimX3, 24.0 ), RoundDbl( dPrimY3, 24.0 ) ));
		//		boost::geometry::correct( polyTempSec );	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed
      //
		//		std::deque<BEMPoly> outputSec2;
		//		boost::geometry::intersection( m_pParentSpace->m_polySpace, polyTempSec, outputSec2 );		// calculate intersection of space and daylit area
		//		int iNumSec2Polys = 0;
		//		BOOST_FOREACH(BEMPoly const& p, outputSec2)
		//		{	iNumSec2Polys++;
		//			if (boost::geometry::area(p) > m_dFinalArea[1])
		//			{	m_polyOrigDaylitInSpc[1] = p;
		//				m_dFinalArea[1] = boost::geometry::area(p);
		//			}
		//		}	assert( iNumSec2Polys <= 1 );
		//		assert( (iNumSecPolys + iNumSec2Polys) == 1 );

		//		m_fEffectiveAperture[1] = ((m_dFinalArea[0]+m_dFinalArea[1]) <= 0 ? 0 : (dWinArea * fVisTrans) / (m_dFinalArea[0]+m_dFinalArea[1]));
				m_dOriginalAreaInSpc[1] = m_dFinalArea[1];
				//m_polyFinalDaylit[1] = m_polyOrigDaylitInSpc[1];
				m_polyFinalDaylit[1].push_back( m_polyOrigDaylitInSpc[1] );

				if (m_dFinalArea[1] < 0.1)		// clear out secondary sideltg ref pt if no secondary area found
					boost::geometry::clear( m_pntDayltgRefPnts[1] );
				else
				{
				//	daylighting reference points (one for each m_polyFinalDaylit[])
		//			ptRef1.set<0>( (dSecX3 + dSecX4) / 2.0 );
		//			ptRef1.set<1>( (dSecY3 + dSecY4) / 2.0 );
		//			ptRef2.set<0>( (dSecX1 + dSecX2) / 2.0 );
		//			ptRef2.set<1>( (dSecY1 + dSecY2) / 2.0 );
		//			iLRPRet = LoadReferencePoint( m_pntDayltgRefPnts[1], m_pParentSpace->m_polySpace, m_pParentSpace->m_ptSpcCenter, glazCentroid, ptRef1, ptRef2 );
		//			m_bDLRefPntValid[1]		= (iLRPRet == 1 || iLRPRet == 2);	// whether or not the dayltg ref points were successfully positioned
		//			m_bDLRefPntInStdLoc[1]	= (iLRPRet != 3);							// whether or not the dayltg ref points are positioned in there generic locations or required special re-positioning
					m_pntDayltgRefPnts[1].set<0>( (dSecX1 + dSecX2) / 2.0 );
					m_pntDayltgRefPnts[1].set<1>( (dSecY1 + dSecY2) / 2.0 );

		// SAC 11/1/16 - moved following code into AdjustSecondarySideDaylitRefPnt() in order to ensure SecSideDaylitRefPnts are NOT located inside Primary side daylit areas (of other glazings)
		//			if (boost::geometry::within( m_pntDayltgRefPnts[1], m_pParentSpace->m_polySpace ))
		//			{	m_bDLRefPntValid[1]		= true;					// whether or not the dayltg ref point was successfully positioned
		//				m_bDLRefPntInStdLoc[1]	= true;					// whether or not the dayltg ref point is positioned in its generic location or required special re-positioning
		//			}
		//			else
		//				AdjustReferencePoint( 1 );
		//			if (m_bDLRefPntValid[1])
		//				m_dRefPntToSpcCenterDist[1] = boost::geometry::distance( m_pntDayltgRefPnts[1], m_pParentSpace->m_ptSpcCenter );
				}

				bRetVal = true;
			}

			}
			catch (std::exception& e)
			{	std::string strErrMsg = boost::str( boost::format("InitSideDaylitAreas() error processing space '%s':  %s" ) % (m_pParentSpace)->m_sSpcName % e.what() );
				BEMPX_WriteLogFile( strErrMsg.c_str() );
				bRetVal = false;
			}
			catch (...)
			{	std::string strErrMsg = boost::str( boost::format("InitSideDaylitAreas() error processing space '%s':  suspect boost::geometry library error" ) % (m_pParentSpace)->m_sSpcName );
				BEMPX_WriteLogFile( strErrMsg.c_str() );
				bRetVal = false;
			}
		}
	}

	return bRetVal;
}


double BEMDaylitArea::DistanceFromClosestWindow( BEMPoint& ptChkRefPt, double dMargin, BEMDaylitArea* pDAChk )
{	double dRetVal = 999;
	if (m_pParentSpace && m_pParentSpace->m_daylitAreas.size() > 0)
	{	// loop over all sidelit daylt areas and find the one w/ the closest glazing
		for (std::vector<BEMDaylitArea>::iterator chk1=m_pParentSpace->m_daylitAreas.begin(); chk1!=m_pParentSpace->m_daylitAreas.end(); ++chk1)
		{	BEMDaylitArea* pChk1 = &(*chk1);
			if (pChk1 && (pDAChk==NULL || pChk1 != pDAChk) && pChk1->IsSidelitArea())
			{	double dMaxGlzVertDist=0;
				BEMPoint ptExtGlzCoord[2];
				std::deque<BEMPoint> ptaGlazPolyPts;
				boost::geometry::intersection( pChk1->m_polyGlazing, pChk1->m_polyGlazing, ptaGlazPolyPts );
				BOOST_FOREACH(BEMPoint const& p, ptaGlazPolyPts)
				{	BOOST_FOREACH(BEMPoint const& p2, ptaGlazPolyPts)
					{	if (dMaxGlzVertDist < boost::geometry::distance( p, p2 ))
						{	dMaxGlzVertDist = boost::geometry::distance( p, p2 );
							ptExtGlzCoord[0] = p;
							ptExtGlzCoord[1] = p2;
				}	}	}
				if (boost::geometry::distance( pChk1->m_ptGlazingCentroid, ptChkRefPt ) < (dMaxGlzVertDist * 0.6)+dMargin)
				{	// check for distance only if the point being checked is within 60%+ of the glazing centroid
					double dAngExtToChk = LineAngle(	boost::geometry::get<0>( ptExtGlzCoord[0] ), boost::geometry::get<0>( ptChkRefPt ),
																boost::geometry::get<1>( ptExtGlzCoord[0] ), boost::geometry::get<1>( ptChkRefPt ), 0.01 );
					double dAngExtToExt = LineAngle(	boost::geometry::get<0>( ptExtGlzCoord[0] ), boost::geometry::get<0>( ptExtGlzCoord[1] ),
																boost::geometry::get<1>( ptExtGlzCoord[0] ), boost::geometry::get<1>( ptExtGlzCoord[1] ), 0.01 );
					double dAngDelta = fabs( dAngExtToChk - dAngExtToExt );
					double dDistExtToChk = fabs( boost::geometry::distance( ptExtGlzCoord[0], ptChkRefPt ) );
					double dDistChkToGlz = fabs( dDistExtToChk * sin( dAngDelta ) );
					if (dRetVal > dDistChkToGlz)
						dRetVal = dDistChkToGlz;	// closest glazing so far...
				}

//	BEMPoly		m_polyGlazing;					//	polygon representing glazing itself

//			std::deque<BEMPoint> ptaIntPts;
//			boost::geometry::intersection( m_pParentSpace->m_polySpace, mptRefPtLine, ptaIntPts );		// calculate intersection of space and ref point line segment
//			double dMaxDistFromGlz = 0.;
//			BEMPoint ptNewRefPt;
//			BOOST_FOREACH(BEMPoint const& p, ptaIntPts)
//			{	if (boost::geometry::distance( p, m_ptGlazingCentroid ) > dMaxDistFromGlz)
//				{	ptNewRefPt = p;
//					dMaxDistFromGlz = boost::geometry::distance( p, m_ptGlazingCentroid );
//			}	}

//						std::deque<BEMPoint> ptaSpcEdgePts, ptaGlzEdgePts;
//						boost::geometry::intersection( m_pParentSpace->m_polySpace, lineCtrlGlaz, ptaSpcEdgePts );		// calculate intersection of space poly and CtrlGlaz line segment

		}	}
	}
	return dRetVal;

//	m_dDistFromParentCentroid = boost::geometry::distance( m_ptGlazingCentroid, m_pParentSpace->m_ptSpcCenter );

//	if (daylitAreas.size() > 0)
//	{	for (std::vector<BEMDaylitArea>::iterator chk1=daylitAreas.begin(); chk1!=daylitAreas.end(); ++chk1)
//		{	BEMDaylitArea* pChk1 = &(*chk1);
//			if (pChk1)
//			{	int iLpTo = (pChk1->IsToplitArea() ? 1 : 2);
//				for (int i=0; i<iLpTo; i++)
//				{	switch (iWhatToPlot)
//					{	case  0 :	mapper.add( pChk1->m_polyOrigDaylitInSpc[i] );		break;
//						case  1 :	//mapper.add( pChk1->m_polyFinalDaylit[0] );	break;
//										BOOST_FOREACH(BEMPoly const& p, pChk1->m_polyFinalDaylit[i])
//										{	mapper.add( p );
//											//if (boost::geometry::area(p) > 0)
//										}	break;
//					}
//					mapper.add( pChk1->m_polyGlazing );
//			}	}
//	}	}

}


bool BEMDaylitArea::InitTopDaylitArea( double dParentZ )
{	bool bRetVal = false;
	m_fDegreesFromSouth = -1;		// constant for toplit areas
	int iError, iC;
	BEM_ObjType eObjType = BEMO_User;
	double fCoords[3];
	vector<double> faSkyltX, faSkyltY, faSkyltZ;
	double dMinXYZ[3] = {  99999.,  99999.,  99999. };
	double dMaxXYZ[3] = { -99999., -99999., -99999. };
	double dAvgZ=0.0, dCenterX=0.0, dCenterY=0.0;
	m_fRelativeDayltPotential[0] = -9999;
	std::vector<double> skyltX, skyltY;
	int iNumPtsInSkylt = 0;
	int iNumPts = (int) BEMPX_GetNumChildren( m_pGeomDBIDs->m_iOID_PolyLp, m_i0PolyLpObjIdx, BEMO_User, m_pGeomDBIDs->m_iOID_CartesianPt );								assert( iNumPts == 4 );
	for (int i=0; i < iNumPts; i++)
	{	int iCartPtObjIdx = BEMPX_GetChildObjectIndex( m_pGeomDBIDs->m_iOID_PolyLp, m_pGeomDBIDs->m_iOID_CartesianPt, iError, eObjType, i+1, m_i0PolyLpObjIdx );		assert( iCartPtObjIdx >= 0 );
		if (iCartPtObjIdx >= 0)
		{	int iNumCoords = BEMPX_GetFloatArray( m_pGeomDBIDs->m_lDBID_CartesianPt_Coord, fCoords, 3, 0, BEMP_Flt, iCartPtObjIdx );										assert( iNumCoords == 3 );
			if (iNumCoords == 3)
			{	for (iC=0; iC<3; iC++)
				{	if (fCoords[iC] > dMaxXYZ[iC])
						dMaxXYZ[iC] = (double) fCoords[iC];
					if (fCoords[iC] < dMinXYZ[iC])
						dMinXYZ[iC] = (double) fCoords[iC];
				}
				skyltX.push_back( (double) fCoords[0] );
				skyltY.push_back( (double) fCoords[1] );
				faSkyltX.push_back( fCoords[0] );	faSkyltY.push_back( fCoords[1] );	faSkyltZ.push_back( fCoords[2] );
				boost::geometry::append( m_polyGlazing, boost::tuples::make_tuple( skyltX[iNumPtsInSkylt], skyltY[iNumPtsInSkylt] ));
				iNumPtsInSkylt++;
			}
	}	}
	if (iNumPtsInSkylt != 4)
	{	assert( FALSE );
// Error: invalid number of skylt vertices
	}
	else
	{	dAvgZ = (dMinXYZ[2] + dMaxXYZ[2]) / 2.0;
		if (dAvgZ <= dParentZ)
		{	assert( FALSE );
// Error: invalid Z position (not above space floor)
		}
		else if (m_pParentSpace == NULL)
		{	assert( FALSE );
// Error: invalid space object pointer
		}
		else
		{
			try		// SAC 6/10/15 - catch bugs in boost::geometry
			{
			boost::geometry::correct( m_polyGlazing );	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed
// this boost poly NOT valid for glazing area calc, as it is a 2-D representation of a 3-D glazing
//			m_fGlazingArea = (double) boost::geometry::area( m_polyGlazing );
			m_fGlazingArea = PolygonArea( faSkyltX, faSkyltY, faSkyltZ );
		// set distance from centroid of primary daylit area to centroid of parent surface
//			BEMPoint glazCentroid;
			boost::geometry::centroid( m_polyGlazing, m_ptGlazingCentroid );
			m_dDistFromParentCentroid = boost::geometry::distance( m_ptGlazingCentroid, m_pParentSpace->m_ptSpcCenter );
//			m_dDistFromParentCentroid = sqrt( ((dParentCentroidX-glazCentroid.x)*(dParentCentroidX-glazCentroid.x)) + ((dParentCentroidY-glazCentroid.y)*(dParentCentroidY-glazCentroid.y)) );

			dCenterX = (dMinXYZ[0] + dMaxXYZ[0]) / 2.0;
			dCenterY = (dMinXYZ[1] + dMaxXYZ[1]) / 2.0;
			int i;
			BEMPoly polyTemp;
			double dToplitAreaWd = (dAvgZ - dParentZ) * 0.7;  // ACM section 5.4.5 - toplit area width = 70% of height of skylt above space floor
			double dLenSegPtToOuter = sqrt( (2.0*dToplitAreaWd*dToplitAreaWd) );
			for (i=0; i<iNumPtsInSkylt; i++)
			{	//int j = (i==0 ? iNumPts-1 : i-1);
				//double dLineMidX = (skyltX[i] + skyltX[j]) / 2, dLineMidY = (skyltY[i] + skyltY[j]) / 2;
				double dAngleCentToPt = LineAngle( dCenterX, skyltX[i], dCenterY, skyltY[i], 0.01 );
				double dCentToOutPtLen = sqrt( ((dCenterX-skyltX[i])*(dCenterX-skyltX[i])) + ((dCenterY-skyltY[i])*(dCenterY-skyltY[i])) ) + dLenSegPtToOuter;
				double dX = dCentToOutPtLen * cos( dAngleCentToPt );
				double dY = dCentToOutPtLen * sin( dAngleCentToPt );
				//boost::geometry::append( polyTemp, boost::tuples::make_tuple( (dCenterX+dX), (dCenterY+dY) ));
				boost::geometry::append( polyTemp, boost::tuples::make_tuple( RoundDbl( (dCenterX+dX), 24.0 ), RoundDbl( (dCenterY+dY), 24.0 ) ));     // rounds to nearest 0.05 (half inch)
			}
			boost::geometry::correct( polyTemp );	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed
			m_polyOrigDaylitArea[0] = polyTemp;

			std::deque<BEMPoly> output;
			boost::geometry::intersection( m_pParentSpace->m_polySpace, polyTemp, output );		// calculate intersection of space and daylit area
			int iNumPolys = 0;
			BOOST_FOREACH(BEMPoly const& p, output)
			{	iNumPolys++;
				if (boost::geometry::area(p) > m_dFinalArea[0])
				{	m_polyOrigDaylitInSpc[0] = p;
					m_dFinalArea[0] = boost::geometry::area(p);
				}
			}	assert( iNumPolys == 1 );
	// ??? effective aperture based on total target daylit area, or intersection of daylit area and space polygon
	//		m_fEffectiveAperture[0] = (m_dFinalArea[0] <= 0 ? 0 : (boost::geometry::area(m_polyGlazing) * fVisTrans * 0.85) / m_dFinalArea[0]);
			m_dOriginalAreaInSpc[0] = m_dFinalArea[0];
			//m_polyFinalDaylit[0] = m_polyOrigDaylitInSpc[0];
			m_polyFinalDaylit[0].push_back( m_polyOrigDaylitInSpc[0] );

			if (m_dFinalArea[0] >= 0.1)
			{
				BEMPoint ptChkRefPt;
				double dDistToSpcCentroid = 99999., dDistPtOutsdToSpcEdge = 0.;
			// find dayltg ref pnt that is INSIDE the space and CLOSEST to the space centroid
				for (i=0; i<iNumPtsInSkylt; i++)
				{	int i2 = (i==0 ? iNumPts-1 : i-1);
					double dAngleCentToPt = LineAngle( dCenterX, skyltX[i], dCenterY, skyltY[i], 0.01 );
					double dCentToOutPtLen = sqrt( ((dCenterX-skyltX[i])*(dCenterX-skyltX[i])) + ((dCenterY-skyltY[i])*(dCenterY-skyltY[i])) ) + dLenSegPtToOuter;
					double dX = dCentToOutPtLen * cos( dAngleCentToPt );
					double dY = dCentToOutPtLen * sin( dAngleCentToPt );

					double dAngleCentToPt2 = LineAngle( dCenterX, skyltX[i2], dCenterY, skyltY[i2], 0.01 );
					double dCentToOutPtLen2 = sqrt( ((dCenterX-skyltX[i2])*(dCenterX-skyltX[i2])) + ((dCenterY-skyltY[i2])*(dCenterY-skyltY[i2])) ) + dLenSegPtToOuter;
					double dX2 = dCentToOutPtLen2 * cos( dAngleCentToPt2 );
					double dY2 = dCentToOutPtLen2 * sin( dAngleCentToPt2 );

					ptChkRefPt.set<0>( (dCenterX+dX + dCenterX+dX2) / 2.0 );
					ptChkRefPt.set<1>( (dCenterY+dY + dCenterY+dY2) / 2.0 );
					double dThisDist = boost::geometry::distance( ptChkRefPt, m_pParentSpace->m_ptSpcCenter );
					if (!boost::geometry::within( ptChkRefPt, m_pParentSpace->m_polySpace ))
					{	// daylighting ctrl (ptChkRefPt) lies OUTSIDE the space boundary
						BEMLine lineCtrlGlaz;		// line between reference pt and glazing centroid
						boost::geometry::append( lineCtrlGlaz, m_ptGlazingCentroid );
						boost::geometry::append( lineCtrlGlaz, ptChkRefPt );
						std::deque<BEMPoint> ptaSpcEdgePts, ptaGlzEdgePts;
						boost::geometry::intersection( m_pParentSpace->m_polySpace, lineCtrlGlaz, ptaSpcEdgePts );		// calculate intersection of space poly and CtrlGlaz line segment
						boost::geometry::intersection(               m_polyGlazing, lineCtrlGlaz, ptaGlzEdgePts );		// calculate intersection of glazing poly and CtrlGlaz line segment
																		assert( !ptaSpcEdgePts.empty() && !ptaGlzEdgePts.empty() );
						if (!ptaSpcEdgePts.empty() && !ptaGlzEdgePts.empty())
						{	dThisDist = boost::geometry::distance( ptaSpcEdgePts[0], ptaGlzEdgePts[0] );
				//			if (dThisDist > dDistPtOutsdToSpcEdge)
				//			{	dDistPtOutsdToSpcEdge = dThisDist;
								// reset ref pt to be 3" inside Space boundary toward glazing centroid
								double dAngVertToCtr = LineAngle(	boost::geometry::get<0>( ptaSpcEdgePts[0] ), boost::geometry::get<0>( ptaGlzEdgePts[0] ),
																				boost::geometry::get<1>( ptaSpcEdgePts[0] ), boost::geometry::get<1>( ptaGlzEdgePts[0] ), 0.01 );
								ptChkRefPt.set<0>( (boost::geometry::get<0>( ptaSpcEdgePts[0] ) + (0.25 * cos( dAngVertToCtr ))) );  // move point 3" toward centroid of skylight
								ptChkRefPt.set<1>( (boost::geometry::get<1>( ptaSpcEdgePts[0] ) + (0.25 * sin( dAngVertToCtr ))) );
				//				ptaSpcEdgePts[0].set<0>( (boost::geometry::get<0>( ptaSpcEdgePts[0] ) + (0.25 * cos( dAngVertToCtr ))) );  // move point 3" toward centroid of skylight
				//				ptaSpcEdgePts[0].set<1>( (boost::geometry::get<1>( ptaSpcEdgePts[0] ) + (0.25 * sin( dAngVertToCtr ))) );
				//				m_pntDayltgRefPnts[0] = ptaSpcEdgePts[0];
				//				m_bDLRefPntValid[0]		= true;		// whether or not the dayltg ref points were successfully positioned
				//				m_bDLRefPntInStdLoc[0]	= true;		// whether or not the dayltg ref points are positioned in there generic locations or required special re-positioning
				//			}
						}

	// Last resort => find points 3" in (toward daylit area centroid) from each daylit area vertex and return the furthest of those from the glazing centroid
//				BEMPoint ptTemp, ptCurDaylitAreaCenter;
//				double dTemp, dFurthestDist = 0.;
//				boost::geometry::centroid( m_polyFinalDaylit[idx], ptCurDaylitAreaCenter );
//				BOOST_FOREACH(BEMPoly const& p, m_polyFinalDaylit[idx])
//				{	for (BOOST_AUTO(	it, boost::begin(boost::geometry::exterior_ring(p)));
//											it != boost::end(boost::geometry::exterior_ring(p));  ++it)
//					{	double dAngVertToCtr = LineAngle(	boost::geometry::get<0>( *it ), boost::geometry::get<0>( ptCurDaylitAreaCenter ),
//																		boost::geometry::get<1>( *it ), boost::geometry::get<1>( ptCurDaylitAreaCenter ), 0.01 );
//						ptTemp.set<0>( (boost::geometry::get<0>( *it ) + (0.25 * cos( dAngVertToCtr ))) );  // move point 3" toward centroid of daylit area
//						ptTemp.set<1>( (boost::geometry::get<1>( *it ) + (0.25 * sin( dAngVertToCtr ))) );
//						dTemp = boost::geometry::distance( ptTemp, m_ptGlazingCentroid );
//						if (dTemp > dFurthestDist && boost::geometry::within( ptTemp, m_pParentSpace->m_polySpace ))
//						{	dFurthestDist = dTemp;
//							m_pntDayltgRefPnts[idx] = ptTemp;
//							bRetVal = true;
//				}	}	}


//						if (dThisDist < dDistPtOutsdToSpcCentroid)
//						{	if (dDistToSpcCentroid > 99998.)
//								m_pntDayltgRefPnts[0] = ptChkRefPt;
//							dDistPtOutsdToSpcCentroid = dThisDist;
//							m_bDLRefPntValid[0]		= true;		// whether or not the dayltg ref points were successfully positioned
//							m_bDLRefPntInStdLoc[0]	= true;		// whether or not the dayltg ref points are positioned in there generic locations or required special re-positioning
//					//		if (m_bDLRefPntValid[0])
//					//			m_dRefPntToSpcCenterDist[0] = boost::geometry::distance( m_pntDayltgRefPnts[0], m_pParentSpace->m_ptSpcCenter );
//						}
					}

					if (dThisDist < dDistToSpcCentroid)
					{	m_pntDayltgRefPnts[0] = ptChkRefPt;
						dDistToSpcCentroid = dThisDist;
						m_bDLRefPntValid[0]		= true;		// whether or not the dayltg ref points were successfully positioned
						m_bDLRefPntInStdLoc[0]	= true;		// whether or not the dayltg ref points are positioned in there generic locations or required special re-positioning
					}

				}																		assert( dDistToSpcCentroid < 99998. || dDistPtOutsdToSpcEdge > 0. );
				if (dDistToSpcCentroid > 99998. && dDistPtOutsdToSpcEdge < 0.0001)
				{	assert( FALSE );
	// TO DO - ALL dayltg ref pnts outside space, so start w/ the one closest to the spc center and move in toward skylt...
				}
				if (m_bDLRefPntValid[0])
					m_dRefPntToSpcCenterDist[0] = boost::geometry::distance( m_pntDayltgRefPnts[0], m_pParentSpace->m_ptSpcCenter );
			}

			bRetVal = true;

			}
			catch (std::exception& e)
			{	QString sErrMsg;
				if (m_pParentSpace)
					sErrMsg = QString( "BEMDaylitArea::InitTopDaylitArea() error processing space '%1':  %2" ).arg( m_pParentSpace->m_sSpcName.c_str(), e.what() );
				else
					sErrMsg = QString( "BEMDaylitArea::InitTopDaylitArea() error:  %1" ).arg( e.what() );
				BEMPX_WriteLogFile( sErrMsg );
				bRetVal = false;
			}
			catch (...)
			{	QString sErrMsg;
				if (m_pParentSpace)
					sErrMsg = QString( "BEMDaylitArea::InitTopDaylitArea() error processing space '%1':  suspect boost::geometry library error" ).arg( m_pParentSpace->m_sSpcName.c_str() );
				else
					sErrMsg = "BEMDaylitArea::InitTopDaylitArea() error:  suspect boost::geometry library error";
				BEMPX_WriteLogFile( sErrMsg );
				bRetVal = false;
			}
	}	}

	return bRetVal;
}


double BEMDaylitArea::AddressIntersection( BEMDaylitArea* pDaylitArea, bool bSecondaryArea, const char* pszDbgSVGPathFile, BEMPoly& spcPoly, bool bClipSecOnly )
{	double dIntersectArea[2] = { 0.0, 0.0 };
	int iOperationBeingPerformed = 0;		QString sDbgMsg, sD2;

	try		// SAC 6/10/15 - catch bugs in boost::geometry
	{
//	for (int i=(bSecondaryArea?1:0); i<2; i++)
	for (int i=(bClipSecOnly?1:0); i<2; i++)
		if (pDaylitArea->m_dFinalArea[i])
	//	{	std::deque<BEMPoly> outputInt;
	//		boost::geometry::intersection( m_polyFinalDaylit[(bSecondaryArea?1:0)], pDaylitArea->m_polyFinalDaylit[i], outputInt );		// calculate intersection of 2 daylit areaa
//		{	BEMMultiPoly messyInt, outputInt;
//			boost::geometry::intersection( m_polyFinalDaylit[(bSecondaryArea?1:0)], pDaylitArea->m_polyFinalDaylit[i], messyInt );		// calculate intersection of 2 daylit areaa
//// try out use of simplify() routine
//			boost::geometry::simplify( messyInt, outputInt, 1 );
		{	BEMMultiPoly outputInt;
						m_polyFinalDaylit[(bSecondaryArea?1:0)] = removeDupVerts( m_polyFinalDaylit[(bSecondaryArea?1:0)], 0.01 );		// SAC 11/21/15 - added to remove duplicate vertices, as they crash intersection() routine (tic 1276)
						pDaylitArea->m_polyFinalDaylit[i]       = removeDupVerts( pDaylitArea->m_polyFinalDaylit[i], 0.01 );
			iOperationBeingPerformed = 1;		//		EchoPolys( sDbgMsg, "int poly #1:\n", m_polyFinalDaylit[(bSecondaryArea?1:0)] );
														//		EchoPolys( sD2    , "int poly #2:\n", pDaylitArea->m_polyFinalDaylit[i] );		sDbgMsg += sD2;
			boost::geometry::intersection( m_polyFinalDaylit[(bSecondaryArea?1:0)], pDaylitArea->m_polyFinalDaylit[i], outputInt );		// calculate intersection of 2 daylit areaa

//			outputInt = removeSpikes( outputInt );
//
//			BEMPoly polyInt;
//	//		BEMMultiPoly polyInt;
//			int iNumIntPolys = 0;
//			BOOST_FOREACH(BEMPoly const& p, outputInt)
//			{	iNumIntPolys++;
//				if (boost::geometry::area(p) > dIntersectArea[i])
//				{	boost::geometry::clear( polyInt );
//					polyInt = p;
//	//				boost::geometry::convert( p, polyInt );
//					dIntersectArea[i] = boost::geometry::area(p);
//				}
//			}	assert( iNumIntPolys <= 1 );
//			if (iNumIntPolys > 0)
//			{	boost::geometry::correct( polyInt );	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed
//// try out use of simplify() routine
//	//			BEMPoly simplified;
//	//			BEMMultiPoly simplified;
//	//			boost::geometry::simplify( polyInt, simplified, 0.01 );
//	//			if (boost::size( simplified ) > 2)
//	//				polyInt = simplified;

			iOperationBeingPerformed = 2;
			outputInt = removeSpikes( outputInt );
			iOperationBeingPerformed = 3;
			boost::geometry::correct( outputInt );	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed
			iOperationBeingPerformed = 4;
			dIntersectArea[i] = boost::geometry::area( outputInt );

			if (dIntersectArea[i] >= 0.1)
			{

#ifdef _DEBUG
// toggled OFF debug output of SVG files...
//				if (pszDbgSVGPathFile)
//					CreateSpaceDayltIntersectSVG( pszDbgSVGPathFile, "init", spcPoly, this, pDaylitArea, (bSecondaryArea?1:0), i );
#endif
				pszDbgSVGPathFile;	spcPoly;
			}

// ADJUST SENSITIVITY
			if (dIntersectArea[i] >= 0.1)
//			{	BEMMultiPoly messyDiff, outputDiff;
//				boost::geometry::difference( pDaylitArea->m_polyFinalDaylit[i], polyInt, messyDiff );		// calculate difference between daylit area intersection and the second daylit area
//// try out use of simplify() routine
//				boost::geometry::simplify( messyDiff, outputDiff, 1 );
			{	BEMMultiPoly outputDiff;
				//boost::geometry::difference( pDaylitArea->m_polyFinalDaylit[i], polyInt, outputDiff );		// calculate difference between daylit area intersection and the second daylit area
					//	boost::geometry::correct( pDaylitArea->m_polyFinalDaylit[i] );
					//	boost::geometry::correct( outputInt );
						pDaylitArea->m_polyFinalDaylit[i] = removeDupVerts( pDaylitArea->m_polyFinalDaylit[i], 0.01 );		// SAC 11/21/15 - added to remove duplicate vertices, as they crash difference() routine (tic 1276)
						outputInt                         = removeDupVerts( outputInt, 0.01 );
				iOperationBeingPerformed = 5;		//		EchoPolys( sDbgMsg, "diff poly #1:\n", pDaylitArea->m_polyFinalDaylit[i] );
															//		EchoPolys( sD2    , "diff poly #2:\n", outputInt );		sDbgMsg += sD2;
				boost::geometry::difference( pDaylitArea->m_polyFinalDaylit[i], outputInt, outputDiff );		// calculate difference between daylit area intersection and the second daylit area
				iOperationBeingPerformed = 6;
				outputDiff = removeSpikes( outputDiff );

//				BEMPoly polyDiff;
//				double dRemainingArea = 0.0;
//				int iNumDiffPolys = 0;
//				BOOST_FOREACH(BEMPoly const& p, outputDiff)
//				{	iNumDiffPolys++;
//					if (boost::geometry::area(p) > dRemainingArea)
//					{	boost::geometry::clear( polyDiff );
//						polyDiff = p;
//						dRemainingArea = boost::geometry::area(p);
//					}
//				}	//assert( iNumDiffPolys == 1 );
//				boost::geometry::clear( pDaylitArea->m_polyFinalDaylit[i] );
//				if (iNumDiffPolys < 1 || dRemainingArea < 0.1)
//					pDaylitArea->m_dFinalArea[i] = 0.0;

				iOperationBeingPerformed = 7;
				boost::geometry::correct( outputDiff );	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed
				iOperationBeingPerformed = 8;
				double dRemainingArea = boost::geometry::area( outputDiff );

		//		assert( WithinMargin( (dIntersectArea[i] + dRemainingArea), pDaylitArea->m_dFinalArea[i], 5.0 ) );
				if (!WithinMargin( (dIntersectArea[i] + dRemainingArea), pDaylitArea->m_dFinalArea[i], 5.0 ))
				{	bool bIntAndRemainExceeds = ((dIntersectArea[i] + dRemainingArea) > pDaylitArea->m_dFinalArea[i]);
#ifdef _DEBUG
					QString sLogMsg, sSVGFN, sLogTemp;
					if (m_pParentSpace && m_pParentSpace->m_sSpcName.size() > 0)
						sLogTemp = QString( "Daylit area intersection error:  space '%1' (idx %2) " ).arg( m_pParentSpace->m_sSpcName.c_str(), QString::number(m_pParentSpace->m_iSpcObjIdx) );
					if (pszDbgSVGPathFile)
					{	sSVGFN = pszDbgSVGPathFile;
						int iSpcNmIdx = sSVGFN.indexOf( " - Spc-" ) + 3;
						if (iSpcNmIdx > 4)
						{	if (!sLogTemp.isEmpty())
							{	int iNxtSpcIdx = sSVGFN.indexOf( " ", iSpcNmIdx+1 ) + 1;
								sLogTemp += sSVGFN.mid( iNxtSpcIdx, (sSVGFN.length() - iNxtSpcIdx - 4) );
							}
							else
								sLogTemp = QString( "Daylit area intersection error:  %1 " ).arg( sSVGFN.mid( iSpcNmIdx, (sSVGFN.length() - iSpcNmIdx - 4) ) );
					}	}
					if (sLogTemp.isEmpty())
						sLogTemp = QString( "Daylit area intersection error:  Objs: %1-%2" ).arg( QString::number(m_i0ObjIdx), QString::number(pDaylitArea->m_i0ObjIdx) );
					sLogTemp += (IsSidelitArea() ? " sidelit" : " toplit");
					if (bIntAndRemainExceeds)
						sLogMsg = QString( "%1 intersection + difference areas (%2 + %3) exceed area checking against (%4) - blasting area checking against" ).arg( sLogTemp,
														QString::number(dIntersectArea[i], 'f', 1), QString::number(dRemainingArea, 'f', 1), QString::number(pDaylitArea->m_dFinalArea[i], 'f', 1) );
					else
						sLogMsg = QString( "%1 intersection + difference areas (%2 + %3) less than area checking against (%4) - leaving area checked unchanged" ).arg( sLogTemp,
														QString::number(dIntersectArea[i], 'f', 1), QString::number(dRemainingArea, 'f', 1), QString::number(pDaylitArea->m_dFinalArea[i], 'f', 1) );
					BEMPX_WriteLogFile( sLogMsg );
#endif
					if (bIntAndRemainExceeds)
					{	// no explanation for case where intersection + remaining exceeds initial daylit area - clearly an error, so blast daylit area being checked against to prevent double-counting
						dRemainingArea = 0.0;
				}	}

				iOperationBeingPerformed = 9;
				boost::geometry::clear( pDaylitArea->m_polyFinalDaylit[i] );
				if (dRemainingArea < 0.1)
					pDaylitArea->m_dFinalArea[i] = 0.0;
				else
				{

//		// ROTATE POLYGON AND RE-SIMPLIFY TO ELIMINATE SLIVERS @ FIRST/LAST POINT OF POLYGON !!
//					BEMPoly rotDiff;
//					std::vector<boost::geometry::model::d2::point_xy<double> > const& points = polyDiff.outer();
//					if (points.size() < 3)
//					{	assert( FALSE );
//						pDaylitArea->m_dFinalArea[i] = 0.0;
//					}
//					else
//					{	for (std::vector<boost::geometry::model::d2::point_xy<double> >::size_type iP = 2; iP < (points.size()-1); ++iP)  // first load points 3-N (NOT the very last point which is a duplicate
//							boost::geometry::append(rotDiff, points[iP] );
//						boost::geometry::append(rotDiff, points[0] );	// then load first two points
//						boost::geometry::append(rotDiff, points[1] );
//						boost::geometry::clear( polyDiff );
//						boost::geometry::simplify( rotDiff, polyDiff, 1 );
//						boost::geometry::correct( polyDiff );

//		// ROTATE POLYGON AND RE-SIMPLIFY TO ELIMINATE SLIVERS @ FIRST/LAST POINT OF POLYGON !!
//					if (polyDiff.outer().size() > 5)  // if there are more than 4 unique points...
//					{	BEMPoly rotDiff;
//						std::vector<boost::geometry::model::d2::point_xy<double> > const& points = polyDiff.outer();
//						if (points.size() < 4)
//						{	assert( FALSE );
//							pDaylitArea->m_dFinalArea[i] = 0.0;
//						}
//						else
//						{	for (std::vector<boost::geometry::model::d2::point_xy<double> >::size_type iP = 2; iP < (points.size()-1); ++iP)  // first load points 3-N (NOT the very last point which is a duplicate
//								boost::geometry::append(rotDiff, points[iP] );
//							boost::geometry::append(rotDiff, points[0] );	// then load first two points
//							boost::geometry::append(rotDiff, points[1] );
//							boost::geometry::clear( polyDiff );
//
//			//				boost::geometry::simplify( rotDiff, polyDiff, 1 );
//							polyDiff = removeSpikes( rotDiff );
//							boost::geometry::correct( polyDiff );
//						}
//					}

						//pDaylitArea->m_polyFinalDaylit[i] = polyDiff;
						pDaylitArea->m_polyFinalDaylit[i] = outputDiff;
						pDaylitArea->m_dFinalArea[i] = dRemainingArea;

#ifdef _DEBUG
// toggled OFF debug output of SVG files...
//						if (pszDbgSVGPathFile)
//							CreateSpaceDayltIntersectSVG( pszDbgSVGPathFile, "post", spcPoly, this, pDaylitArea, (bSecondaryArea?1:0), i );
#endif
//					}
				}
			}
		}

	}
	catch (std::exception& e)
	{	QString sErrMsg, sOperStr;
		switch( iOperationBeingPerformed )
		{	case  1 :  sOperStr = "oper 1: boost::geometry::intersection( m_polyFinalDaylit[(bSecondaryArea?1:0)], pDaylitArea->m_polyFinalDaylit[i], outputInt )";		break;
			case  2 :  sOperStr = "oper 2: removeSpikes( outputInt )";		break;
			case  3 :  sOperStr = "oper 3: boost::geometry::correct( outputInt )";		break;
			case  4 :  sOperStr = "oper 4: boost::geometry::area( outputInt )";		break;
			case  5 :  sOperStr = "oper 5: boost::geometry::difference( pDaylitArea->m_polyFinalDaylit[i], outputInt, outputDiff )";		break;
			case  6 :  sOperStr = "oper 6: removeSpikes( outputDiff )";		break;
			case  7 :  sOperStr = "oper 7: boost::geometry::correct( outputDiff )";		break;
			case  8 :  sOperStr = "oper 8: boost::geometry::area( outputDiff )";		break;
			case  9 :  sOperStr = "oper 9: boost::geometry::clear( pDaylitArea->m_polyFinalDaylit[i] )";		break;
			default :  sOperStr = QString( "oper %1: <unknown>" ).arg( QString::number(iOperationBeingPerformed) );		break;
		}
		if (pDaylitArea && pDaylitArea->m_pParentSpace)
			sErrMsg = QString( "BEMDaylitArea::AddressIntersection() error processing space '%1':  %2 -- %3" ).arg( pDaylitArea->m_pParentSpace->m_sSpcName.c_str(), e.what(), sOperStr );
		else
			sErrMsg = QString( "BEMDaylitArea::AddressIntersection() error:  %1 -- %2" ).arg( e.what(), sOperStr );
		if (!sDbgMsg.isEmpty())
			sErrMsg += QString("\n") + sDbgMsg;
		BEMPX_WriteLogFile( sErrMsg );
		dIntersectArea[0] = 0.0;		dIntersectArea[1] = 0.0;
	}
	catch (...)
	{	QString sErrMsg, sOperStr;
		switch( iOperationBeingPerformed )
		{	case  1 :  sOperStr = "oper 1: boost::geometry::intersection( m_polyFinalDaylit[(bSecondaryArea?1:0)], pDaylitArea->m_polyFinalDaylit[i], outputInt )";		break;
			case  2 :  sOperStr = "oper 2: removeSpikes( outputInt )";		break;
			case  3 :  sOperStr = "oper 3: boost::geometry::correct( outputInt )";		break;
			case  4 :  sOperStr = "oper 4: boost::geometry::area( outputInt )";		break;
			case  5 :  sOperStr = "oper 5: boost::geometry::difference( pDaylitArea->m_polyFinalDaylit[i], outputInt, outputDiff )";		break;
			case  6 :  sOperStr = "oper 6: removeSpikes( outputDiff )";		break;
			case  7 :  sOperStr = "oper 7: boost::geometry::correct( outputDiff )";		break;
			case  8 :  sOperStr = "oper 8: boost::geometry::area( outputDiff )";		break;
			case  9 :  sOperStr = "oper 9: boost::geometry::clear( pDaylitArea->m_polyFinalDaylit[i] )";		break;
			default :  sOperStr = QString( "oper %1: <unknown>" ).arg( QString::number(iOperationBeingPerformed) );		break;
		}
		if (pDaylitArea && pDaylitArea->m_pParentSpace)
			sErrMsg = QString( "BEMDaylitArea::AddressIntersection() error processing space '%1':  suspect boost::geometry library error -- %2" ).arg( pDaylitArea->m_pParentSpace->m_sSpcName.c_str(), sOperStr );
		else
			sErrMsg = QString( "BEMDaylitArea::AddressIntersection() error:  suspect boost::geometry library error -- %1" ).arg( sOperStr );
		if (!sDbgMsg.isEmpty())
			sErrMsg += QString("\n") + sDbgMsg;
		BEMPX_WriteLogFile( sErrMsg );
		dIntersectArea[0] = 0.0;		dIntersectArea[1] = 0.0;
	}

	return (dIntersectArea[0] + dIntersectArea[1]);
}


////////////////////////////////////////////////////////////////////////////////


//			#define  DCPS_SidelitOnly_IgnoreSkylights  0
//			#define  DCPS_SidelitOnly_AvoidSkylights   1
//			#define  DCPS_ToplitOnly_IgnoreWindows     2
//			#define  DCPS_ToplitOnly_AvoidWindows      3
//			#define  DCPS_SideAndToplit                4


int PolyLpToBEMPoly( BEMPoly& bemPoly, double& dAvgZ, double& dZRange, BEMPoint& ptCenter, int iPolyLpObjIdx, double* pdExtremes )
{  int iNumPolyVerts = 0, iError, iC;
	BEM_ObjType eObjType = BEMO_User;
	double fCoords[3];
	double dCoords[3];
	double dMinXYZ[3] = {  99999.,  99999.,  99999. };
	double dMaxXYZ[3] = { -99999., -99999., -99999. };
	dAvgZ = dZRange = 0.0;
	boost::geometry::clear(bemPoly);
	int iNumPts = (int) BEMPX_GetNumChildren( ruleSet.getGeomIDs()->m_iOID_PolyLp, iPolyLpObjIdx, BEMO_User, ruleSet.getGeomIDs()->m_iOID_CartesianPt );			assert( iNumPts > 2 );
	for (int i=0; i < iNumPts; i++)
	{	
		int iCartPtObjIdx = BEMPX_GetChildObjectIndex( ruleSet.getGeomIDs()->m_iOID_PolyLp, ruleSet.getGeomIDs()->m_iOID_CartesianPt, iError, eObjType, i+1, iPolyLpObjIdx );		assert( iCartPtObjIdx >= 0 );
		if (iCartPtObjIdx >= 0)
		{	int iNumCoords = BEMPX_GetFloatArray( ruleSet.getGeomIDs()->m_lDBID_CartesianPt_Coord, fCoords, 3, 0, BEMP_Flt, iCartPtObjIdx );											assert( iNumCoords == 3 );
			if (iNumCoords == 3)
			{
// ROUND vertices before loading them into BEMPoly objects
				for (iC=0; iC<3; iC++)
					dCoords[iC] = RoundDbl( (double) fCoords[iC], 24.0 );		// rounds to nearest 0.05 (half inch)

		//		boost::geometry::append(bemPoly, boost::tuples::make_tuple( (double) fCoords[0], (double) fCoords[1] ));
				boost::geometry::append(bemPoly, boost::tuples::make_tuple( dCoords[0], dCoords[1] ));
				for (iC=0; iC<3; iC++)
				{	if (dCoords[iC] > dMaxXYZ[iC])
						dMaxXYZ[iC] = dCoords[iC];
					if (dCoords[iC] < dMinXYZ[iC])
						dMinXYZ[iC] = dCoords[iC];
				}
				iNumPolyVerts++;
			}
	}	}
	if (iNumPolyVerts > 2)
	{	boost::geometry::correct(bemPoly);	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed
		//dCentroidX /= iNumPolyVerts;
		//dCentroidY /= iNumPolyVerts;
		ptCenter.set<0>( (dMinXYZ[0] + dMaxXYZ[0]) / 2.0 );
		ptCenter.set<1>( (dMinXYZ[1] + dMaxXYZ[1]) / 2.0 );
		dAvgZ   = (dMinXYZ[2] + dMaxXYZ[2]) / 2.0;
		dZRange =  dMaxXYZ[2] - dMinXYZ[2] ;
	}
	if (pdExtremes)
	{	if (iNumPolyVerts > 2)
		{	pdExtremes[0] = dMinXYZ[0];   // XMin, XMax, YMin, YMax
			pdExtremes[1] = dMaxXYZ[0];
			pdExtremes[2] = dMinXYZ[1];
			pdExtremes[3] = dMaxXYZ[1];
		}
		else
		{	pdExtremes[0] =  99999.;
			pdExtremes[1] = -99999.;
			pdExtremes[2] =  99999.;
			pdExtremes[3] = -99999.;
	}	}
	return iNumPolyVerts;
}


double SetupSpaceDaylighting( BEMSpaceDaylitArea& spcDLAs, GeomDBIDs* pGeomIDs, const char* pszSpcName, QString& sErrMsg, int iDayltMethod )  // SAC 7/29/18 - added iDayltMethod for 2019 (Win/Skylt:DisableDayltgImpact)
{
	double dDaylitArea = 0.0;
	double dDLAreaByType[3] = { 0.0, 0.0, 0.0 };		// Top / PrimSide / SecSide
	int iError;
	BEM_ObjType eObjType = BEMO_User;
// debugging
//QString qsDbgMsg = QString( "   SetupSpaceDaylighting( spc '%1', iDayltMethod %2, pGeomIDs->m_lDBID_Win_DisableDayltgImpact %3 )" ).arg( pszSpcName, QString::number(iDayltMethod), QString::number(pGeomIDs->m_lDBID_Win_DisableDayltgImpact) );	BEMPX_WriteLogFile( qsDbgMsg );

	// start by checking for existence of a single, child PolyLp for this Spc
	int iNumSpcPolyLps = (int) BEMPX_GetNumChildren( pGeomIDs->m_iOID_Spc, spcDLAs.m_iSpcObjIdx, BEMO_User, pGeomIDs->m_iOID_PolyLp );
	if (iNumSpcPolyLps < 1)
	{	dDaylitArea = -1;
		sErrMsg = QString( "Space PolyLp not found for space '%1'" ).arg( pszSpcName );
	}
	else if (iNumSpcPolyLps > 1)
	{	dDaylitArea = -2;
		sErrMsg = QString( "Too many space PolyLp objects found (%1, should be only 1) for space '%2'" ).arg( QString::number(iNumSpcPolyLps), pszSpcName );
	}
	else
	{
		spcDLAs.m_sSpcName = pszSpcName;
		int iSpcPolyLpObjIdx = BEMPX_GetChildObjectIndex( pGeomIDs->m_iOID_Spc, pGeomIDs->m_iOID_PolyLp, iError, eObjType, 1, spcDLAs.m_iSpcObjIdx );		assert( iSpcPolyLpObjIdx >= 0 );
		spcDLAs.m_bRDPCoefsOK = (	BEMPX_GetFloatArray( pGeomIDs->m_lDBID_Spc_SkylitRDPCoefs , &spcDLAs.m_daSpcSkylitRDPCoefs[ 0], 2, 0, -1, spcDLAs.m_iSpcObjIdx ) == 2 &&
											BEMPX_GetFloatArray( pGeomIDs->m_lDBID_Spc_PriSideRDPCoefs, &spcDLAs.m_daSpcPriSideRDPCoefs[0], 3, 0, -1, spcDLAs.m_iSpcObjIdx ) == 3 &&
											BEMPX_GetFloatArray( pGeomIDs->m_lDBID_Spc_SecSideRDPCoefs, &spcDLAs.m_daSpcSecSideRDPCoefs[0], 3, 0, -1, spcDLAs.m_iSpcObjIdx ) == 3 );			assert( spcDLAs.m_bRDPCoefsOK );
		//spcDLAs.m_pdlaTop = NULL;
		//spcDLAs.m_pdlaPrim = NULL;
		//spcDLAs.m_pdlaSec = NULL;

//		BEMPoly polySpace;
//		BEMPoint ptSpcCenter;
		double dSpcAvgZ=0., dSpcZRange=0.;  //, dCentroidX=0., dCentroidY=0.;
		int iPL2BP = PolyLpToBEMPoly( spcDLAs.m_polySpace, dSpcAvgZ, dSpcZRange, spcDLAs.m_ptSpcCenter, iSpcPolyLpObjIdx, &spcDLAs.m_daSpaceExtremes[0] );		assert( iPL2BP > 2 );
		assert( dSpcZRange < 1 );		// expect space polygons to be horizontal

		//std::vector<BEMDaylitArea> daylitAreas;
		int iNumExtWallChildren = (int) BEMPX_GetNumChildren( pGeomIDs->m_iOID_Spc, spcDLAs.m_iSpcObjIdx, BEMO_User, pGeomIDs->m_iOID_ExtWall );
		for (int iEWall=1; iEWall <= iNumExtWallChildren; iEWall++)
		{	int iEWallObjIdx = BEMPX_GetChildObjectIndex( pGeomIDs->m_iOID_Spc, pGeomIDs->m_iOID_ExtWall, iError, eObjType, iEWall, spcDLAs.m_iSpcObjIdx );		assert( iEWallObjIdx >= 0 );
			if (iEWallObjIdx >= 0)
			{
				int iNumWinChildren = (int) BEMPX_GetNumChildren( pGeomIDs->m_iOID_ExtWall, iEWallObjIdx, BEMO_User, pGeomIDs->m_iOID_Win );
				if (iNumWinChildren > 0)
				{
			// load wall geometry
					BEMPoint ptEWallCenter;
					double fWallAz, fDegFromS = -1;
					int iNumEWallPolyLps = (int) BEMPX_GetNumChildren( pGeomIDs->m_iOID_ExtWall, iEWallObjIdx, BEMO_User, pGeomIDs->m_iOID_PolyLp );
					if (iNumEWallPolyLps < 1 || iNumEWallPolyLps > 1)
					{	assert( FALSE );
						//sErrMsg.Format( "Space PolyLp not found for space '%s'", pszSpcName );
						//sErrMsg.Format( "Too many space PolyLp objects found (%d, should be only 1) for space '%s'", QString::number(iNumEWallPolyLps), pszSpcName );
					}
					else
					{	int iEWallPolyLpObjIdx = BEMPX_GetChildObjectIndex( pGeomIDs->m_iOID_ExtWall, pGeomIDs->m_iOID_PolyLp, iError, eObjType, 1, iEWallObjIdx );		assert( iEWallPolyLpObjIdx >= 0 );
						BEMPoly polyEWall;
						double dEWallAvgZ=0., dEWallZRange=0.;
						iPL2BP = PolyLpToBEMPoly( polyEWall, dEWallAvgZ, dEWallZRange, ptEWallCenter, iEWallPolyLpObjIdx, NULL );		assert( iPL2BP > 2 );
						assert( dEWallZRange > 0.1 );		// expect EWall polygons to be NON-horizontal

						if (BEMPX_GetFloat( pGeomIDs->m_lDBID_ExtWall_Az, fWallAz, 0, BEMP_Flt, iEWallObjIdx ))
						{	while (fWallAz < 0)
								fWallAz += 360;
							while (fWallAz >= 360)
								fWallAz -= 360;
							//if (fWallAz <= 180)
							//	fDegFromN = fWallAz;
							//else
							//	fDegFromN = (360 - fWallAz);
							fDegFromS = fabs( 180 - fWallAz );
						}
					}
			// create daylit area objects for each child window
					for (int iWin=1; (fDegFromS > -0.01 && iWin <= iNumWinChildren); iWin++)
					{	int iWinObjIdx = BEMPX_GetChildObjectIndex( pGeomIDs->m_iOID_ExtWall, pGeomIDs->m_iOID_Win, iError, eObjType, iWin, iEWallObjIdx );		assert( iWinObjIdx >= 0 );
						if (iWinObjIdx >= 0 && iDayltMethod >= 2 && pGeomIDs->m_lDBID_Win_DisableDayltgImpact > 0)
						{	long lDisableDayltgImpact=0;
							if (BEMPX_GetInteger( pGeomIDs->m_lDBID_Win_DisableDayltgImpact, lDisableDayltgImpact, 0, BEMP_Int, iWinObjIdx ) && lDisableDayltgImpact > 0)
								iWinObjIdx = -1;  // SAC 7/29/18 - skip this window if Win:DisableDayltgImpact flag set (iff iDayltMethod >= 2)
										// debugging
										//QString qsDbgMsg = QString( "      win %1 / lDisableDayltgImpact %2" ).arg( QString::number(iWinObjIdx), QString::number(lDisableDayltgImpact) );	BEMPX_WriteLogFile( qsDbgMsg );
						}
						if (iWinObjIdx >= 0)
						{	BEMDaylitArea winDaylitArea( &spcDLAs, pGeomIDs, pGeomIDs->m_iOID_Win, iWinObjIdx, dSpcAvgZ );
							if (winDaylitArea.IsValid())
							{	winDaylitArea.m_fDegreesFromSouth = fDegFromS;
								spcDLAs.m_daylitAreas.push_back( winDaylitArea );
			}	}	}	}	}
		}

		int iNumRoofChildren = (int) BEMPX_GetNumChildren( pGeomIDs->m_iOID_Spc, spcDLAs.m_iSpcObjIdx, BEMO_User, pGeomIDs->m_iOID_Roof );
		for (int iRoof=1; iRoof <= iNumRoofChildren; iRoof++)
		{	int iRoofObjIdx = BEMPX_GetChildObjectIndex( pGeomIDs->m_iOID_Spc, pGeomIDs->m_iOID_Roof, iError, eObjType, iRoof, spcDLAs.m_iSpcObjIdx );			assert( iRoofObjIdx >= 0 );
			if (iRoofObjIdx >= 0)
			{
				int iNumSkyltChildren = (int) BEMPX_GetNumChildren( pGeomIDs->m_iOID_Roof, iRoofObjIdx, BEMO_User, pGeomIDs->m_iOID_Skylt );
				if (iNumSkyltChildren > 0)
				{
			// load roof geometry
					BEMPoint ptRoofCenter;
					int iNumRoofPolyLps = (int) BEMPX_GetNumChildren( pGeomIDs->m_iOID_Roof, iRoofObjIdx, BEMO_User, pGeomIDs->m_iOID_PolyLp );
					if (iNumRoofPolyLps < 1 || iNumRoofPolyLps > 1)
					{	assert( FALSE );
						//sErrMsg.Format( "Space PolyLp not found for space '%s'", pszSpcName );
						//sErrMsg.Format( "Too many space PolyLp objects found (%d, should be only 1) for space '%s'", QString::number(iNumRoofPolyLps), pszSpcName );
					}
					else
					{
						int iRoofPolyLpObjIdx = BEMPX_GetChildObjectIndex( pGeomIDs->m_iOID_Roof, pGeomIDs->m_iOID_PolyLp, iError, eObjType, 1, iRoofObjIdx );		assert( iRoofPolyLpObjIdx >= 0 );
						BEMPoly polyRoof;
						double dRoofAvgZ=0., dRoofZRange=0.;
						iPL2BP = PolyLpToBEMPoly( polyRoof, dRoofAvgZ, dRoofZRange, ptRoofCenter, iRoofPolyLpObjIdx, NULL );		assert( iPL2BP > 2 );
					}
			// create daylit area objects for each child skylight
					for (int iSkylt=1; iSkylt <= iNumSkyltChildren; iSkylt++)
					{	int iSkyltObjIdx = BEMPX_GetChildObjectIndex( pGeomIDs->m_iOID_Roof, pGeomIDs->m_iOID_Skylt, iError, eObjType, iSkylt, iRoofObjIdx );		assert( iSkyltObjIdx >= 0 );
						if (iSkyltObjIdx >= 0 && iDayltMethod >= 2 && pGeomIDs->m_lDBID_Skylt_DisableDayltgImpact > 0)
						{	long lDisableDayltgImpact=0;
							if (BEMPX_GetInteger( pGeomIDs->m_lDBID_Skylt_DisableDayltgImpact, lDisableDayltgImpact, 0, BEMP_Int, iSkyltObjIdx ) && lDisableDayltgImpact > 0)
								iSkyltObjIdx = -1;  // SAC 7/29/18 - skip this skylt if Skylt:DisableDayltgImpact flag set (iff iDayltMethod >= 2)
						}
						if (iSkyltObjIdx >= 0)
						{	BEMDaylitArea skyltDaylitArea( &spcDLAs, pGeomIDs, pGeomIDs->m_iOID_Skylt, iSkyltObjIdx, dSpcAvgZ );
							if (skyltDaylitArea.IsValid())
								spcDLAs.m_daylitAreas.push_back( skyltDaylitArea );
					}	}
			}	}
		}

#ifdef _DEBUG
// toggled OFF debug output of SVG files...
//		if (dDaylitArea >= 0 && spcDLAs.m_daylitAreas.size() > 0)
//		{	QString sDbgDayltTemp, sDbgDayltSVG;
//			sDbgDayltTemp = BEMPX_GetLogFilename( false /*bCSVLog*/ );
//			sDbgDayltTemp = sDbgDayltTemp.left( sDbgDayltTemp.lastIndexOf('.') );
//			sDbgDayltSVG.Format( "%s - DayltInit Spc-%d Ply-%d.svg", sDbgDayltTemp, QString::number(spcDLAs.m_iSpcObjIdx), QString::number(iSpcPolyLpObjIdx) );
//			CreateSpaceDayltSVG( sDbgDayltSVG, spcDLAs.m_polySpace, spcDLAs.m_daylitAreas, 0 /*Init*/ );
//		}
#endif

		if (dDaylitArea >= 0 && spcDLAs.m_daylitAreas.size() > 0)
		{
		// Mods to ensure secondary side daylit area reference points are not inside any primary sidelit areas (of different glazings)
			for (std::vector<BEMDaylitArea>::iterator chk1=spcDLAs.m_daylitAreas.begin(); chk1!=spcDLAs.m_daylitAreas.end(); ++chk1)
			{	BEMDaylitArea* pChk1 = &(*chk1);

			// code to ensure that NO dayltg ctrl position is wihtin 6" of any window - SAC 8/21/17
				if (pChk1 && pChk1->m_dFinalArea[0] >= 0.1 && pChk1->m_bDLRefPntValid[0])
				{	int iWinDistLoop = 0;
					while (pChk1->DistanceFromClosestWindow( pChk1->m_pntDayltgRefPnts[0], 0.5, (pChk1->IsSidelitArea() ? pChk1 : NULL) ) <= 0.5 && ++iWinDistLoop < 10)
					{	// this dayltg ref pt within 6" of nearest window, so pull it in toward skylt centroid by 3"
						double dAngPtToCtr = LineAngle(	boost::geometry::get<0>( pChk1->m_pntDayltgRefPnts[0] ), boost::geometry::get<0>( pChk1->m_ptGlazingCentroid ),
																	boost::geometry::get<1>( pChk1->m_pntDayltgRefPnts[0] ), boost::geometry::get<1>( pChk1->m_ptGlazingCentroid ), 0.01 );
						pChk1->m_pntDayltgRefPnts[0].set<0>( (boost::geometry::get<0>( pChk1->m_pntDayltgRefPnts[0] ) + (0.25 * cos( dAngPtToCtr ))) );  // move point 3" toward centroid of glazing
						pChk1->m_pntDayltgRefPnts[0].set<1>( (boost::geometry::get<1>( pChk1->m_pntDayltgRefPnts[0] ) + (0.25 * sin( dAngPtToCtr ))) );
					}
					if (iWinDistLoop > 1)
						pChk1->m_bDLRefPntInStdLoc[0]	= false;		// whether or not the dayltg ref points are positioned in there generic locations or required special re-positioning
					if (iWinDistLoop >= 10)
						pChk1->m_bDLRefPntValid[0]		= false;		// whether or not the dayltg ref points were successfully positioned
				}
				if (pChk1 && pChk1->IsSidelitArea() && pChk1->m_dFinalArea[1] >= 0.1 && pChk1->m_bDLRefPntValid[1])
				{	int iWinDistLoop = 0;
					while (pChk1->DistanceFromClosestWindow( pChk1->m_pntDayltgRefPnts[1], 0.5, pChk1 ) <= 0.5 && ++iWinDistLoop < 10)
					{	// this dayltg ref pt within 6" of nearest window, so pull it in toward skylt centroid by 3"
						double dAngPtToCtr = LineAngle(	boost::geometry::get<0>( pChk1->m_pntDayltgRefPnts[1] ), boost::geometry::get<0>( pChk1->m_ptGlazingCentroid ),
																	boost::geometry::get<1>( pChk1->m_pntDayltgRefPnts[1] ), boost::geometry::get<1>( pChk1->m_ptGlazingCentroid ), 0.01 );
						pChk1->m_pntDayltgRefPnts[1].set<0>( (boost::geometry::get<0>( pChk1->m_pntDayltgRefPnts[1] ) + (0.25 * cos( dAngPtToCtr ))) );  // move point 3" toward centroid of glazing
						pChk1->m_pntDayltgRefPnts[1].set<1>( (boost::geometry::get<1>( pChk1->m_pntDayltgRefPnts[1] ) + (0.25 * sin( dAngPtToCtr ))) );
					}
					if (iWinDistLoop > 1)
						pChk1->m_bDLRefPntInStdLoc[1]	= false;		// whether or not the dayltg ref points are positioned in there generic locations or required special re-positioning
					if (iWinDistLoop >= 10)
						pChk1->m_bDLRefPntValid[1]		= false;		// whether or not the dayltg ref points were successfully positioned
				}

				if (pChk1 && pChk1->IsSidelitArea() && pChk1->m_dFinalArea[1] >= 0.1)
					pChk1->AdjustSecondarySideDaylitRefPnt( spcDLAs );
			}

			if (spcDLAs.m_daylitAreas.size() > 1)
			{	QString sDbgDayltTemp, sDbgSVGPathFile;
				sDbgDayltTemp = BEMPX_GetLogFilename( false /*bCSVLog*/ );
				sDbgDayltTemp = sDbgDayltTemp.left( sDbgDayltTemp.lastIndexOf('.') );
				int iAddIntCount = 0;

			// first SORT all daylit area objects from closest to furthest from centroid of its parent surface
				std::sort( spcDLAs.m_daylitAreas.begin(), spcDLAs.m_daylitAreas.end(), ClosestToParentCenter );
			// first of several iterations through daylit area objects
			// 1st ROUND address overlaps between toplit areas only
				for (std::vector<BEMDaylitArea>::iterator chk1=spcDLAs.m_daylitAreas.begin(); chk1!=spcDLAs.m_daylitAreas.end(); ++chk1)
				{	BEMDaylitArea* pChk1 = &(*chk1);
					if (pChk1 && pChk1->IsToplitArea())
					{	for (std::vector<BEMDaylitArea>::iterator chk2=chk1+1; chk2!=spcDLAs.m_daylitAreas.end(); ++chk2)
						{	BEMDaylitArea* pChk2 = &(*chk2);
							if (pChk2 && pChk2->IsToplitArea())
							{	sDbgSVGPathFile = QString( "%1 - Spc-%2 DayltInt1 %3" ).arg( sDbgDayltTemp, QString::number(spcDLAs.m_iSpcObjIdx) ).arg( QString::number(++iAddIntCount), 5 );
								double dIntersectArea = pChk1->AddressIntersection( pChk2, false, sDbgSVGPathFile.toLocal8Bit().constData(), spcDLAs.m_polySpace, false );		dIntersectArea;
						}	}
				}	}

			// 2nd ROUND address overlaps between toplit areas and sidelit (prim & sec) areas
				for (std::vector<BEMDaylitArea>::iterator chk1=spcDLAs.m_daylitAreas.begin(); chk1!=spcDLAs.m_daylitAreas.end(); ++chk1)
				{	BEMDaylitArea* pChk1 = &(*chk1);
					if (pChk1 && pChk1->IsToplitArea())
					{	for (std::vector<BEMDaylitArea>::iterator chk2=spcDLAs.m_daylitAreas.begin(); chk2!=spcDLAs.m_daylitAreas.end(); ++chk2)
						{	BEMDaylitArea* pChk2 = &(*chk2);
							if (pChk2 && pChk2->IsSidelitArea())
							{	sDbgSVGPathFile = QString( "%1 - Spc-%2 DayltInt2 %3" ).arg( sDbgDayltTemp, QString::number(spcDLAs.m_iSpcObjIdx) ).arg( QString::number(++iAddIntCount), 5 );
								double dIntersectArea = pChk1->AddressIntersection( pChk2, false, sDbgSVGPathFile.toLocal8Bit().constData(), spcDLAs.m_polySpace, false );		dIntersectArea;
						}	}
				}	}

			// 3rd ROUND address overlaps between primary sidelit and secondary sidelit areas
				for (std::vector<BEMDaylitArea>::iterator chk1=spcDLAs.m_daylitAreas.begin(); chk1!=spcDLAs.m_daylitAreas.end(); ++chk1)
				{	BEMDaylitArea* pChk1 = &(*chk1);
					if (pChk1 && pChk1->IsSidelitArea())
					{	for (std::vector<BEMDaylitArea>::iterator chk2=spcDLAs.m_daylitAreas.begin(); chk2!=spcDLAs.m_daylitAreas.end(); ++chk2)
						{	BEMDaylitArea* pChk2 = &(*chk2);
							if (pChk2 && pChk1 != pChk2 && pChk2->IsSidelitArea())
							{	sDbgSVGPathFile = QString( "%1 - Spc-%2 DayltInt3 %3" ).arg( sDbgDayltTemp, QString::number(spcDLAs.m_iSpcObjIdx) ).arg( QString::number(++iAddIntCount), 5 );
								double dIntersectArea = pChk1->AddressIntersection( pChk2, false, sDbgSVGPathFile.toLocal8Bit().constData(), spcDLAs.m_polySpace, true );		dIntersectArea;
						}	}
				}	}

			// 4th ROUND clip primary & secondary daylit areas that intersect w/ (closer to centroid) primary daylit areas
				for (std::vector<BEMDaylitArea>::iterator chk1=spcDLAs.m_daylitAreas.begin(); chk1!=spcDLAs.m_daylitAreas.end(); ++chk1)
				{	BEMDaylitArea* pChk1 = &(*chk1);
					if (pChk1 && pChk1->IsSidelitArea())
					{	for (std::vector<BEMDaylitArea>::iterator chk2=chk1+1; chk2!=spcDLAs.m_daylitAreas.end(); ++chk2)
						{	BEMDaylitArea* pChk2 = &(*chk2);
							if (pChk2 && pChk2->IsSidelitArea())
							{	sDbgSVGPathFile = QString( "%1 - Spc-%2 DayltInt4 %3" ).arg( sDbgDayltTemp, QString::number(spcDLAs.m_iSpcObjIdx) ).arg( QString::number(++iAddIntCount), 5 );
								double dIntersectArea = pChk1->AddressIntersection( pChk2, false, sDbgSVGPathFile.toLocal8Bit().constData(), spcDLAs.m_polySpace, false );		dIntersectArea;
						}	}
				}	}

			// 5th ROUND clip secondary daylit areas that intersect w/ (closer to centroid) secondary daylit areas
				for (std::vector<BEMDaylitArea>::iterator chk1=spcDLAs.m_daylitAreas.begin(); chk1!=spcDLAs.m_daylitAreas.end(); ++chk1)
				{	BEMDaylitArea* pChk1 = &(*chk1);
					if (pChk1 && pChk1->IsSidelitArea() && pChk1->SecArea() > 0.01)
					{	for (std::vector<BEMDaylitArea>::iterator chk2=chk1+1; chk2!=spcDLAs.m_daylitAreas.end(); ++chk2)
						{	BEMDaylitArea* pChk2 = &(*chk2);
							if (pChk2 && pChk2->IsSidelitArea() && pChk2->SecArea() > 0.01)
							{	sDbgSVGPathFile = QString( "%1 - Spc-%2 DayltInt5 %3" ).arg( sDbgDayltTemp, QString::number(spcDLAs.m_iSpcObjIdx) ).arg( QString::number(++iAddIntCount), 5 );
								double dIntersectArea = pChk1->AddressIntersection( pChk2, true, sDbgSVGPathFile.toLocal8Bit().constData(), spcDLAs.m_polySpace, true );		dIntersectArea;
						}	}
				}	}
			}

			try		// SAC 6/10/15 - catch bugs in boost::geometry
			{
		// Next step - calculate effective aperture for each dayltg reference point, which involves identification of all daylit areas that this dayltg ref point is within
			for (std::vector<BEMDaylitArea>::iterator chk1=spcDLAs.m_daylitAreas.begin(); chk1!=spcDLAs.m_daylitAreas.end(); ++chk1)
			{	BEMDaylitArea* pChk1 = &(*chk1);
				if (pChk1 && pChk1->m_bDLRefPntValid[0] && boost::geometry::area( pChk1->m_polyOrigDaylitArea[0] ) > 0)
				{
			// calculate effective aperture of PRIMARY daylit area
					pChk1->m_fEffectiveAperture[0] = (pChk1->m_fGlazingVisTrans * pChk1->m_fGlazingArea);
					for (std::vector<BEMDaylitArea>::iterator chk2=spcDLAs.m_daylitAreas.begin(); chk2!=spcDLAs.m_daylitAreas.end(); ++chk2)
					{	BEMDaylitArea* pChk2 = &(*chk2);
						if (pChk2 && pChk1 != pChk2 && boost::geometry::within( pChk1->m_pntDayltgRefPnts[0], pChk2->m_polyOrigDaylitArea[0] ))
						{	// Chk1's RefPt is INSIDE the primary daylit area of Chk2
							BEMMultiPoly intersect;
							boost::geometry::intersection( pChk1->m_polyOrigDaylitArea[0], pChk2->m_polyOrigDaylitArea[0], intersect );		// calculate intersection of the two prim daylit area
							double dIntArea = boost::geometry::area( intersect );					assert( dIntArea > 0 && boost::geometry::area( pChk2->m_polyOrigDaylitArea[0] ) > 0 );
							if (dIntArea > 0 && boost::geometry::area( pChk2->m_polyOrigDaylitArea[0] ) > 0)
								pChk1->m_fEffectiveAperture[0] += (pChk2->m_fGlazingVisTrans * pChk2->m_fGlazingArea * dIntArea / boost::geometry::area( pChk2->m_polyOrigDaylitArea[0] ));
					}	}
					pChk1->m_fEffectiveAperture[0] /= boost::geometry::area( pChk1->m_polyOrigDaylitArea[0] );
				}

				if (pChk1 && pChk1->m_bDLRefPntValid[1] && boost::geometry::area( pChk1->m_polyOrigDaylitArea[1] ) > 0)
				{
			// calculate effective aperture of SECONDARY daylit area
					pChk1->m_fEffectiveAperture[1] = (pChk1->m_fGlazingVisTrans * pChk1->m_fGlazingArea);
					for (std::vector<BEMDaylitArea>::iterator chk2=spcDLAs.m_daylitAreas.begin(); chk2!=spcDLAs.m_daylitAreas.end(); ++chk2)
					{	BEMDaylitArea* pChk2 = &(*chk2);
						if (pChk2 && pChk1 != pChk2 && boost::geometry::within( pChk1->m_pntDayltgRefPnts[1], pChk2->m_polyOrigDaylitArea[0] ))
						{	// Chk1's sec RefPt is INSIDE the primary daylit area of Chk2
							BEMMultiPoly intersect;
							boost::geometry::intersection( pChk1->m_polyOrigDaylitArea[1], pChk2->m_polyOrigDaylitArea[0], intersect );		// calculate intersection of the two prim daylit area
							double dIntArea = boost::geometry::area( intersect );					assert( boost::geometry::area( pChk2->m_polyOrigDaylitArea[0] ) > 0 );	// dIntArea CAN = 0
							if (dIntArea > 0 && boost::geometry::area( pChk2->m_polyOrigDaylitArea[0] ) > 0)
								pChk1->m_fEffectiveAperture[1] += (pChk2->m_fGlazingVisTrans * pChk2->m_fGlazingArea * dIntArea / boost::geometry::area( pChk2->m_polyOrigDaylitArea[0] ));
						}
						else if (pChk2 && pChk1 != pChk2 && boost::geometry::within( pChk1->m_pntDayltgRefPnts[1], pChk2->m_polyOrigDaylitArea[1] ))
						{	// Chk1's sec RefPt is INSIDE the secondary daylit area of Chk2
							BEMMultiPoly intersect;
							boost::geometry::intersection( pChk1->m_polyOrigDaylitArea[1], pChk2->m_polyOrigDaylitArea[1], intersect );		// calculate intersection of the two prim daylit area
							double dIntArea = boost::geometry::area( intersect );					assert( boost::geometry::area( pChk2->m_polyOrigDaylitArea[1] ) > 0 );	// dIntArea CAN = 0
							if (dIntArea > 0 && boost::geometry::area( pChk2->m_polyOrigDaylitArea[1] ) > 0)
								pChk1->m_fEffectiveAperture[1] += (pChk2->m_fGlazingVisTrans * pChk2->m_fGlazingArea * dIntArea / boost::geometry::area( pChk2->m_polyOrigDaylitArea[1] ));
					}	}
					pChk1->m_fEffectiveAperture[1] /= boost::geometry::area( pChk1->m_polyOrigDaylitArea[1] );
				}
			}

		// Next Step - Calculate RDP (relative daylighting potential) for each valid daylighting reference point & keep track of DaylitAreas of each type w/ maximum RDPs
			std::vector<BEMDaylitArea*> paDLATopStdLoc, paDLATopOthLoc, paDLAPrimStdLoc, paDLAPrimOthLoc, paDLASecStdLoc, paDLASecOthLoc;
			double fMaxRDPTopStdLoc=-9999, fMaxRDPTopOthLoc=-9999, fMaxRDPPrimStdLoc=-9999, fMaxRDPPrimOthLoc=-9999, fMaxRDPSecStdLoc=-9999, fMaxRDPSecOthLoc=-9999;
			double dDLArea;
			for (std::vector<BEMDaylitArea>::iterator chk1=spcDLAs.m_daylitAreas.begin(); chk1!=spcDLAs.m_daylitAreas.end(); ++chk1)
			{	BEMDaylitArea* pChk1 = &(*chk1);
				if (pChk1)
				{	dDLArea = pChk1->GetDaylitArea(0);		// Top
					if (dDLArea > 0)
						dDLAreaByType[0] += dDLArea;
					if (pChk1->m_fDegreesFromSouth == -1 && pChk1->m_bDLRefPntValid[0])
					{	pChk1->m_fRelativeDayltPotential[0] = ((pChk1->m_fEffectiveAperture[0] * spcDLAs.m_daSpcSkylitRDPCoefs[0]) + spcDLAs.m_daSpcSkylitRDPCoefs[1]);
						if (pChk1->m_bDLRefPntInStdLoc[0])
						{	if (pChk1->m_fRelativeDayltPotential[0] > fMaxRDPTopStdLoc)
							{	paDLATopStdLoc.clear();
								fMaxRDPTopStdLoc = pChk1->m_fRelativeDayltPotential[0];
							}
							if (pChk1->m_fRelativeDayltPotential[0] >= fMaxRDPTopStdLoc)
								paDLATopStdLoc.push_back( pChk1 );
						}
						else
						{	if (pChk1->m_fRelativeDayltPotential[0] > fMaxRDPTopOthLoc)
							{	paDLATopOthLoc.clear();
								fMaxRDPTopOthLoc = pChk1->m_fRelativeDayltPotential[0];
							}
							if (pChk1->m_fRelativeDayltPotential[0] >= fMaxRDPTopOthLoc)
								paDLATopOthLoc.push_back( pChk1 );
					}	}

					dDLArea = pChk1->GetDaylitArea(1);		// PrimSide
					if (dDLArea > 0)
						dDLAreaByType[1] += dDLArea;
					if (pChk1->m_fDegreesFromSouth >= 0 && pChk1->m_bDLRefPntValid[0])
					{	pChk1->m_fRelativeDayltPotential[0] = ((pChk1->m_fEffectiveAperture[0] * spcDLAs.m_daSpcPriSideRDPCoefs[0]) + (pChk1->m_fDegreesFromSouth * spcDLAs.m_daSpcPriSideRDPCoefs[1]) + spcDLAs.m_daSpcPriSideRDPCoefs[2]);
						if (pChk1->m_bDLRefPntInStdLoc[0])
						{	if (pChk1->m_fRelativeDayltPotential[0] > fMaxRDPPrimStdLoc)
							{	paDLAPrimStdLoc.clear();
								fMaxRDPPrimStdLoc = pChk1->m_fRelativeDayltPotential[0];
							}
							if (pChk1->m_fRelativeDayltPotential[0] >= fMaxRDPPrimStdLoc)
								paDLAPrimStdLoc.push_back( pChk1 );
						}
						else
						{	if (pChk1->m_fRelativeDayltPotential[0] > fMaxRDPPrimOthLoc)
							{	paDLAPrimOthLoc.clear();
								fMaxRDPPrimOthLoc = pChk1->m_fRelativeDayltPotential[0];
							}
							if (pChk1->m_fRelativeDayltPotential[0] >= fMaxRDPPrimOthLoc)
								paDLAPrimOthLoc.push_back( pChk1 );
					}	}

					dDLArea = pChk1->GetDaylitArea(2);		// SecSide
					if (dDLArea > 0)
						dDLAreaByType[2] += dDLArea;
					if (pChk1->m_fDegreesFromSouth >= 0 && pChk1->m_bDLRefPntValid[1])
					{	pChk1->m_fRelativeDayltPotential[1] = ((pChk1->m_fEffectiveAperture[1] * spcDLAs.m_daSpcSecSideRDPCoefs[0]) + (pChk1->m_fDegreesFromSouth * spcDLAs.m_daSpcSecSideRDPCoefs[1]) + spcDLAs.m_daSpcSecSideRDPCoefs[2]);
						if (pChk1->m_bDLRefPntInStdLoc[1])
						{	if (pChk1->m_fRelativeDayltPotential[1] > fMaxRDPSecStdLoc)
							{	paDLASecStdLoc.clear();
								fMaxRDPSecStdLoc = pChk1->m_fRelativeDayltPotential[1];
							}
							if (pChk1->m_fRelativeDayltPotential[1] >= fMaxRDPSecStdLoc)
								paDLASecStdLoc.push_back( pChk1 );
						}
						else
						{	if (pChk1->m_fRelativeDayltPotential[1] > fMaxRDPSecOthLoc)
							{	paDLASecOthLoc.clear();
								fMaxRDPSecOthLoc = pChk1->m_fRelativeDayltPotential[1];
							}
							if (pChk1->m_fRelativeDayltPotential[1] >= fMaxRDPSecOthLoc)
								paDLASecOthLoc.push_back( pChk1 );
					}	}
			}	}
			dDaylitArea = dDLAreaByType[0] + dDLAreaByType[1] + dDLAreaByType[2];

		// Next Step - Sort DaylitArea groups (w/ max RDP values) by distance from space centroid and store a pointer to the closest of each type
			if (paDLATopStdLoc.size() > 0)
			{	// we HAVE toplit areas w/ a "standard" location ref pt, so choose one of those
				if (paDLATopStdLoc.size() == 1)
					spcDLAs.m_dlaTop = *paDLATopStdLoc[0];  // only one w/ max RDP, so choose that one
				else
				{	// once here, SORT array of max RDP daylit areas
					std::sort( paDLATopStdLoc.begin(), paDLATopStdLoc.end(), ClosestToParentCenterPtr1 );
					spcDLAs.m_dlaTop = *paDLATopStdLoc[0];  // choose the first one in the list - should be closest to the space centroid
					//for (std::vector<BEMDaylitArea*>::iterator chk1=paDLATopStdLoc.begin(); chk1!=paDLATopStdLoc.end(); ++chk1)
					//{	BEMDaylitArea* pChk1 = *chk1;
					//	if (pChk1)
					//		spcDLAs.m_pdlaTop = paDLATopStdLoc[0];  // only one w/ max RDP, so choose that one
					//}
				}	assert( spcDLAs.m_dlaTop.m_bDLRefPntValid[0] );
			}
			else if (paDLATopOthLoc.size() > 0)
			{	// no toplit areas w/ standard locations, so choose the best "other" location ref pts
				if (paDLATopOthLoc.size() == 1)
					spcDLAs.m_dlaTop = *paDLATopOthLoc[0];  // only one w/ max RDP, so choose that one
				else
				{	// once here, SORT array of max RDP daylit areas
					std::sort( paDLATopOthLoc.begin(), paDLATopOthLoc.end(), ClosestToParentCenterPtr1 );
					spcDLAs.m_dlaTop = *paDLATopOthLoc[0];  // choose the first one in the list - should be closest to the space centroid
				}	assert( spcDLAs.m_dlaTop.m_bDLRefPntValid[0] );
			}

			if (paDLAPrimStdLoc.size() > 0)
			{	// we HAVE primary sidelit areas w/ a "standard" location ref pt, so choose one of those
				if (paDLAPrimStdLoc.size() == 1)
					spcDLAs.m_dlaPrim = *paDLAPrimStdLoc[0];  // only one w/ max RDP, so choose that one
				else
				{	// once here, SORT array of max RDP daylit areas
					std::sort( paDLAPrimStdLoc.begin(), paDLAPrimStdLoc.end(), ClosestToParentCenterPtr1 );
					spcDLAs.m_dlaPrim = *paDLAPrimStdLoc[0];  // choose the first one in the list - should be closest to the space centroid
				}	assert( spcDLAs.m_dlaPrim.m_bDLRefPntValid[0] );
			}
			else if (paDLAPrimOthLoc.size() > 0)
			{	// no primary sidelit areas w/ standard locations, so choose the best "other" location ref pts
				if (paDLAPrimOthLoc.size() == 1)
					spcDLAs.m_dlaPrim = *paDLAPrimOthLoc[0];  // only one w/ max RDP, so choose that one
				else
				{	// once here, SORT array of max RDP daylit areas
					std::sort( paDLAPrimOthLoc.begin(), paDLAPrimOthLoc.end(), ClosestToParentCenterPtr1 );
					spcDLAs.m_dlaPrim = *paDLAPrimOthLoc[0];  // choose the first one in the list - should be closest to the space centroid
				}	assert( spcDLAs.m_dlaPrim.m_bDLRefPntValid[0] );
			}

			if (paDLASecStdLoc.size() > 0)
			{	// we HAVE secondary sidelit areas w/ a "standard" location ref pt, so choose one of those
				if (paDLASecStdLoc.size() == 1)
					spcDLAs.m_dlaSec = *paDLASecStdLoc[0];  // only one w/ max RDP, so choose that one
				else
				{	// once here, SORT array of max RDP daylit areas
					std::sort( paDLASecStdLoc.begin(), paDLASecStdLoc.end(), ClosestToParentCenterPtr1 );
					spcDLAs.m_dlaSec = *paDLASecStdLoc[0];  // choose the first one in the list - should be closest to the space centroid
				}	assert( spcDLAs.m_dlaSec.m_bDLRefPntValid[0] );
			}
			else if (paDLASecOthLoc.size() > 0)
			{	// no secondary sidelit areas w/ standard locations, so choose the best "other" location ref pts
				if (paDLASecOthLoc.size() == 1)
					spcDLAs.m_dlaSec = *paDLASecOthLoc[0];  // only one w/ max RDP, so choose that one
				else
				{	// once here, SORT array of max RDP daylit areas
					std::sort( paDLASecOthLoc.begin(), paDLASecOthLoc.end(), ClosestToParentCenterPtr1 );
					spcDLAs.m_dlaSec = *paDLASecOthLoc[0];  // choose the first one in the list - should be closest to the space centroid
				}	assert( spcDLAs.m_dlaSec.m_bDLRefPntValid[0] );
			}

//			std::vector<BEMDaylitArea*> paDLATopStdLoc, paDLATopOthLoc, paDLAPrimStdLoc, paDLAPrimOthLoc, paDLASecStdLoc, paDLASecOthLoc;
//			double fMaxRDPTopStdLoc=0, fMaxRDPTopOthLoc=0, fMaxRDPPrimStdLoc=0, fMaxRDPPrimOthLoc=0, fMaxRDPSecStdLoc=0, fMaxRDPSecOthLoc=0;
//
//		spcDLAs.m_pdlaTop = NULL;
//		spcDLAs.m_pdlaPrim = NULL;
//		spcDLAs.m_pdlaSec = NULL;

//			std::vector<BEMDaylitArea*> paDLATopStdLoc, paDLATopOthLoc, paDLAPrimStdLoc, paDLAPrimOthLoc, paDLASecStdLoc, paDLASecOthLoc;
//			double fMaxRDPTopStdLoc=0, fMaxRDPTopOthLoc=0, fMaxRDPPrimStdLoc=0, fMaxRDPPrimOthLoc=0, fMaxRDPSecStdLoc=0, fMaxRDPSecOthLoc=0;



//			std::vector<BEMDaylitArea*> paDLATopStdLoc, paDLATopOthLoc, paDLAPrimStdLoc, paDLAPrimOthLoc, paDLASecStdLoc, paDLASecStdLoc;
//			double fMaxRDPTopStdLoc=0, fMaxRDPTopOthLoc=0, fMaxRDPPrimStdLoc=0, fMaxRDPPrimOthLoc=0, fMaxRDPSecStdLoc=0, fMaxRDPSecStdLoc=0;


//	double		m_fRelativeDayltPotential[2];	// [Prim,Sec]
//					pChk1->m_fEffectiveAperture[1] /= boost::geometry::area( pChk1->m_polyOrigDaylitArea[1] );
//	double			m_fDegreesFromSouth;			// -1 for toplit


//					iLRPRet = LoadReferencePoint( m_pntDayltgRefPnts[1], m_pParentSpace->m_polySpace, m_pParentSpace->m_ptSpcCenter, glazCentroid, ptRef1, ptRef2 );
//					m_bDLRefPntValid[1]		= (iLRPRet == 1 || iLRPRet == 2);	// whether or not the dayltg ref points were successfully positioned
//					m_bDLRefPntInStdLoc[1]	= (iLRPRet != 3);							// whether or not the dayltg ref points are positioned in there generic locations or required special re-positioning


//	BEMSpaceDaylitArea* m_pParentSpace;
//	double    m_daSpcSkylitRDPCoefs[2];		// RDP = ([0] * EffAp) + [1]
//	double    m_daSpcPriSideRDPCoefs[3];		// RDP = ([0] * EffAp) + ([1] * SrcOrient) + [2]
//	double    m_daSpcSecSideRDPCoefs[3];		// RDP = ([0] * EffAp) + ([1] * SrcOrient) + [2]




//				std::sort( spcDLAs.m_daylitAreas.begin(), spcDLAs.m_daylitAreas.end(), ClosestToParentCenter );
//
//
//							m_bDLRefPntValid[0]		= true;		// whether or not the dayltg ref points were successfully positioned
//							m_bDLRefPntInStdLoc[0]	= true;		// whether or not the dayltg ref points are positioned in there generic locations or required special re-positioning
//
//
//class BEMDaylitArea
//	double		m_dDistFromParentCentroid;	// distance from center of glazing to center of parent  (used to decide which daylit area to keep intersecting daylit areas in)
//	BEMPoly		m_polyGlazing;					//	polygon representing glazing itself
//	double			m_fGlazingArea;				//	area of glazing
//	double			m_fGlazingVisTrans;			// visible transmittance of glazing
//
//	double			m_fDegreesFromSouth;			// -1 for toplit
//	double		m_fEffectiveAperture[2];	// [Prim,Sec]
//
//	double			m_dFinalArea[2];				// areas AFTER EXCLUDING/MERGING overlapping daylit areas
//
//	BEMPoint		m_pntDayltgRefPnts[2];		//	daylighting reference points (one for each m_polyFinalDaylit[])
//	double		m_fRelativeDayltPotential[2];	// [Prim,Sec]
//
//
//	double    m_daSpcSkylitRDPCoefs[2];		// RDP = ([0] * EffAp) + [1]
//	double    m_daSpcPriSideRDPCoefs[3];		// RDP = ([0] * EffAp) + ([1] * SrcOrient) + [2]
//	double    m_daSpcSecSideRDPCoefs[3];		// RDP = ([0] * EffAp) + ([1] * SrcOrient) + [2]
//
//	BEMPoly		m_polyOrigDaylitArea[2];			//	initial daylit areas, INCLUDING all overlaps w/ other daylit areas and NOT clipped to Space polygon


			}
			catch (std::exception& e)
			{	sErrMsg = QString( "SetupSpaceDaylighting() error processing space '%1':  %2" ).arg( pszSpcName, e.what() );
				dDaylitArea = -3;
			}
			catch (...)
			{	sErrMsg = QString( "SetupSpaceDaylighting() error processing space '%1':  suspect boost::geometry library error" ).arg( pszSpcName );
				dDaylitArea = -3;
			}
		}

#ifdef _DEBUG
//		if (dDaylitArea >= 0 && spcDLAs.m_daylitAreas.size() > 0)
//		{	QString sDbgDayltTemp, sDbgDayltSVG;
//			sDbgDayltTemp = BEMPX_GetLogFilename( false /*bCSVLog*/ );
//			sDbgDayltTemp = sDbgDayltTemp.left( sDbgDayltTemp.lastIndexOf('.') );
//			sDbgDayltSVG.Format( "%s - DayltPost Spc-%d Ply-%d.svg", sDbgDayltTemp, QString::number(spcDLAs.m_iSpcObjIdx), QString::number(iSpcPolyLpObjIdx) );
//			CreateSpaceDayltSVG( sDbgDayltSVG, spcDLAs.m_polySpace, spcDLAs.m_daylitAreas, 1 /*Final*/ );
//		}
#endif
	}

	return dDaylitArea;
}


/// old version...
							// Return Values:
							//		  >= 0 : Amount of daylightable area
							//			 -1 : No Space PolyLp objects found
							//			 -2 : Too many Space PolyLp objects found (must be only 1)
							//			 -3 : 
							//			 -4 : Error positioning daylighting control(s)
							//			 -5 : Error setting View Azimuth
							//			 -6 : Error initializing dayltg calc data - Floor object
							//			 -7 : Error initializing dayltg calc data - Space object
							//			 -8 : Error initializing dayltg calc data - Wall object
							//			 -9 : Error initializing dayltg calc data - Glazing object
							//			-10 : Error initializing dayltg calc data - Space geometry
							//			-11 : Error initializing dayltg calc data - Window geometry
double CalcDaylighting( int iDayltMethod, int iSpcObjIdx, const char* pszSpcName, ExpEvalStruct* pEval, ExpError* /*pError*/ )
{
	double dDaylitArea = 0.0;
	double dDLAreaByType[3] = { 0.0, 0.0, 0.0 };		// Top / PrimSide / SecSide
	QString sErrMsg;
	int iError;

	assert( (iDayltMethod == 1 || iDayltMethod == 2) );			iDayltMethod;
	BEMSpaceDaylitArea spcDLAs;  // moved daylit area arrays to parent class
	spcDLAs.m_iSpcObjIdx = iSpcObjIdx;
	dDaylitArea = SetupSpaceDaylighting( spcDLAs, ruleSet.getGeomIDs(), pszSpcName, sErrMsg, iDayltMethod );

	if (dDaylitArea >= 0 && spcDLAs.m_daylitAreas.size() > 0)
	{
		if (spcDLAs.m_daylitAreas.size() == 1)
		{	dDLAreaByType[0] = spcDLAs.m_daylitAreas[0].GetDaylitArea(0);		// Top
			dDLAreaByType[1] = spcDLAs.m_daylitAreas[0].GetDaylitArea(1);		// PrimSide
			dDLAreaByType[2] = spcDLAs.m_daylitAreas[0].GetDaylitArea(2);		// SecSide
		}
		else
			for (std::vector<BEMDaylitArea>::iterator chk1=spcDLAs.m_daylitAreas.begin(); chk1!=spcDLAs.m_daylitAreas.end(); ++chk1)
			{	BEMDaylitArea* pChk1 = &(*chk1);
				if (pChk1)
				{	dDLAreaByType[0] += pChk1->GetDaylitArea(0);		// Top
					dDLAreaByType[1] += pChk1->GetDaylitArea(1);		// PrimSide
					dDLAreaByType[2] += pChk1->GetDaylitArea(2);		// SecSide
			}	}
	}


// final step - set data directly to BEMBase - array elements 2-4 of Spc:DaylitArea[] - REGARDLESS of routine's success
	if (ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitDaylitArea > 0)
	{  // construct debug message when verbose logging activated
		double fSpcFlrArea = 0, fDayltAreaExceeds = 0;
		double fDLAreaByType[3] = { dDLAreaByType[0], dDLAreaByType[1], dDLAreaByType[2] };
		double fTotDaylitArea = fDLAreaByType[0] + fDLAreaByType[1] + fDLAreaByType[2];
		if (BEMPX_GetFloat( ruleSet.getGeomIDs()->m_lDBID_Spc_FlrArea, fSpcFlrArea, 0, BEMP_Flt, iSpcObjIdx ) && fSpcFlrArea > 0.01 && fTotDaylitArea > 0.01)
		{

// debugging
//BEMObject* pDbgObj2 = BEMPX_GetObjectByClass( ruleSet.getGeomIDs()->m_iOID_Spc, iError, iSpcObjIdx );
//QString sDbg2 = QString( "Spc '%1' FlrArea = %2 / fTotDaylitArea = %3 (Toplit: %4, PrimSidelit: %5, SecSidelit: %6)" ).arg( pDbgObj2->getName(), QString::number(fSpcFlrArea), QString::number(fTotDaylitArea), QString::number(fDLAreaByType[0]), QString::number(fDLAreaByType[1]), QString::number(fDLAreaByType[2]) );
//BEMPX_WriteLogFile( sDbg2 );

	// ERROR - total calced daylit area larger than space (by a margin not likely to be attributable to decimal precision)
			// SAC 3/19/19 - revise error check to allow for daylit area sum to exceed fSpcFlrArea by as much as 1% (similar to other area check margins)
			if (fTotDaylitArea > (fSpcFlrArea * 1.01))
				fDayltAreaExceeds = fTotDaylitArea - fSpcFlrArea;
			if (fTotDaylitArea > fSpcFlrArea)
			{	// adjust daylit areas proportionally to fit into Space area
				double fDLAreaAdj = fTotDaylitArea - fSpcFlrArea;
				double faDLAdjByType[3] = {  fDLAreaByType[0] * fDLAreaAdj / fTotDaylitArea,  fDLAreaByType[1] * fDLAreaAdj / fTotDaylitArea,  fDLAreaByType[2] * fDLAreaAdj / fTotDaylitArea };
			// SAC 6/4/15 - fixed bug where adjustment was applied as a multiplier when it is actually already scaled and therefore should simply be subtracted from the original value(s)
				if (fDLAreaByType[1] >= fDLAreaByType[0] && fDLAreaByType[1] >= fDLAreaByType[2])
				{	// main adjustment out of PrimSidelit
					fDLAreaByType[0] -= faDLAdjByType[0];
					fDLAreaByType[2] -= faDLAdjByType[2];
					fDLAreaByType[1]  = fSpcFlrArea - fDLAreaByType[0] - fDLAreaByType[2];
				}
				else if (fDLAreaByType[0] >= fDLAreaByType[1] && fDLAreaByType[0] >= fDLAreaByType[2])
				{	// main adjustment out of Toplit
					fDLAreaByType[1] -= faDLAdjByType[1];
					fDLAreaByType[2] -= faDLAdjByType[2];
					fDLAreaByType[0]  = fSpcFlrArea - fDLAreaByType[1] - fDLAreaByType[2];
				}
				else
				{	// main adjustment out of SecSidelit
					fDLAreaByType[0] -= faDLAdjByType[0];
					fDLAreaByType[1] -= faDLAdjByType[1];
					fDLAreaByType[2]  = fSpcFlrArea - fDLAreaByType[0] - fDLAreaByType[1];
				}
				assert( (fDLAreaByType[0] + fDLAreaByType[1] + fDLAreaByType[2]) < (fSpcFlrArea + 0.1) );
		}	}

		QString sDebug, sDebug2;
		BOOL bWrtMsgToLog = (pEval->bVerboseOutput || pEval->bEvalItemADebugTarget || fDayltAreaExceeds > 0.5);
#ifdef _DEBUG
		bWrtMsgToLog = TRUE;
#endif
		if (bWrtMsgToLog)
		{	if (!pEval->bVerboseOutput && !pEval->bRuleIDLogged)
				sDebug = QString( "      %1  '" ).arg( pEval->pRuleBeingEvaled->getID() );
			else
				sDebug  = "                   '";
			BEMObject* pObj = BEMPX_GetObjectByClass( ruleSet.getGeomIDs()->m_iOID_Spc /*BEMPX_GetClassID( pEval->lLocDBID )*/, iError, iSpcObjIdx /*pEval->iLocObjIdx*/ );  //, pEval->eLocObjType );
			if (pObj && !pObj->getName().isEmpty())
				sDebug += pObj->getName();
			else
				sDebug += "<unknown>";
			sDebug += "' ";
			// BEMPX_DBIDToDBCompParamString( pEval->lLocDBID, sDebug2 );
			// sDebug += sDebug2;
			sDebug += "(data set directly to Spc:DaylitArea[2-4] by CalcDaylighting())";
			sDebug += " -> ";
			if (fDayltAreaExceeds > 0.1 && fSpcFlrArea > 0)
				// SAC 3/19/19 - modified error message to reference original (not adjusted) daylit areas (dDLArea.. vs. fDLArea...)
				sDebug2 = QString( "Toplit: %1 (%2%) / PrimSidelit: %3 (%4%) / SecSidelit: %5 (%6%) / Overall: %7 (%8%) - ERROR: calced daylit areas exceeded Spc:FlrArea by %9" ).arg( QString::number(dDLAreaByType[0]),
										QString::number((dDLAreaByType[0] * 100 / fSpcFlrArea), 'f', 0), QString::number(dDLAreaByType[1]), QString::number((dDLAreaByType[1] * 100 / fSpcFlrArea), 'f', 0), QString::number(dDLAreaByType[2]),
										QString::number((dDLAreaByType[2] * 100 / fSpcFlrArea), 'f', 0), QString::number(fTotDaylitArea  ), QString::number((fTotDaylitArea   * 100 / fSpcFlrArea), 'f', 0), QString::number(fDayltAreaExceeds, 'f', 1) );
			else if (fTotDaylitArea > 0.1 && fSpcFlrArea > 0)
				sDebug2 = QString( "Toplit: %1 (%2%) / PrimSidelit: %3 (%4%) / SecSidelit: %5 (%6%) / Overall: %7 (%8%)" ).arg(   QString::number(fDLAreaByType[0]), QString::number((fDLAreaByType[0] * 100 / fSpcFlrArea), 'f', 0),
									QString::number(fDLAreaByType[1]), QString::number((fDLAreaByType[1] * 100 / fSpcFlrArea), 'f', 0), QString::number(fDLAreaByType[2]), QString::number((fDLAreaByType[2] * 100 / fSpcFlrArea), 'f', 0),
									QString::number(fTotDaylitArea), QString::number((fTotDaylitArea     * 100 / fSpcFlrArea), 'f', 0) );
			else
				sDebug2 = QString( "Toplit: %1 / PrimSidelit: %2 / SecSidelit: %3" ).arg( QString::number(fDLAreaByType[0]), QString::number(fDLAreaByType[1]), QString::number(fDLAreaByType[2]) );
			sDebug += sDebug2;
	      BEMPX_WriteLogFile( sDebug );
		}

		//double fData;
		int iSetRetVal[3] = {-1,-1,-1};
		for (int iT=0; iT<3; iT++)
		{	//fData = dDLAreaByType[iT];
			//int iSetRetVal = BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_DaylitArea+iT+1 /*pEval->lLocDBID*/, BEMP_Flt, (void*) &fData, BEMO_User /*pEval->eNewObjType*/,
			long lDBID_DLArea = 	(iT==0 ? ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitDaylitArea  :
										(iT==1 ? ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideDaylitArea :
													ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideDaylitArea	));
			iSetRetVal[iT] = BEMPX_SetBEMData( lDBID_DLArea, BEMP_Flt, (void*) &fDLAreaByType[iT], BEMO_User /*pEval->eNewObjType*/,
													iSpcObjIdx /*pEval->iLocObjIdx*/, pEval->eLocStatus, pEval->eLocObjType, TRUE /*bPerformSetBEMDataResets*/ );				assert( iSetRetVal >= 0 );
													// , -1 /*iBEMProcIdx*/, pEval->bImportUniqueRuleLibObjects, pEval->sImportRuleLibParentName, pszSetBEMData_ErrMsg, SetBEMData_ErrMsgLen );
		}
		if (iSetRetVal[0] >= 0)
	//	{	if (spcDLAs.m_pdlaTop == NULL)
		{	if (!spcDLAs.m_dlaTop.m_bDLRefPntValid[0])
			{	BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitDayltgRefPtCoordX   , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitDayltgRefPtCoordY   , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitRDP                 , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitDayltgRefPtEffAp    , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitDayltgRefPtSrcOrient, iError, iSpcObjIdx );
			}
			else
			{	double fRefPtX = boost::geometry::get<0>( spcDLAs.m_dlaTop.m_pntDayltgRefPnts[0] );
				double fRefPtY = boost::geometry::get<1>( spcDLAs.m_dlaTop.m_pntDayltgRefPnts[0] );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitDayltgRefPtCoordX   , BEMP_Flt, (void*) &fRefPtX													, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitDayltgRefPtCoordY   , BEMP_Flt, (void*) &fRefPtY													, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitRDP                 , BEMP_Flt, (void*) &spcDLAs.m_dlaTop.m_fRelativeDayltPotential[0], BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitDayltgRefPtEffAp    , BEMP_Flt, (void*) &spcDLAs.m_dlaTop.m_fEffectiveAperture[0]    	, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSkylitDayltgRefPtSrcOrient, BEMP_Flt, (void*) &spcDLAs.m_dlaTop.m_fDegreesFromSouth        	, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
		}	}
		if (iSetRetVal[1] >= 0)
	//	{	if (spcDLAs.m_pdlaPrim == NULL)
		{	if (!spcDLAs.m_dlaPrim.m_bDLRefPntValid[0])
			{	BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideDayltgRefPtCoordX   , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideDayltgRefPtCoordY   , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideRDP                 , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideDayltgRefPtEffAp    , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideDayltgRefPtSrcOrient, iError, iSpcObjIdx );
			}
			else
			{	double fRefPtX = boost::geometry::get<0>( spcDLAs.m_dlaPrim.m_pntDayltgRefPnts[0] );
				double fRefPtY = boost::geometry::get<1>( spcDLAs.m_dlaPrim.m_pntDayltgRefPnts[0] );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideDayltgRefPtCoordX   , BEMP_Flt, (void*) &fRefPtX														, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideDayltgRefPtCoordY   , BEMP_Flt, (void*) &fRefPtY														, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideRDP                 , BEMP_Flt, (void*) &spcDLAs.m_dlaPrim.m_fRelativeDayltPotential[0]	, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideDayltgRefPtEffAp    , BEMP_Flt, (void*) &spcDLAs.m_dlaPrim.m_fEffectiveAperture[0]    	, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarPriSideDayltgRefPtSrcOrient, BEMP_Flt, (void*) &spcDLAs.m_dlaPrim.m_fDegreesFromSouth        	, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
		}	}
		if (iSetRetVal[2] >= 0)
	//	{	if (spcDLAs.m_pdlaSec == NULL)
		{	if (!spcDLAs.m_dlaSec.m_bDLRefPntValid[0])
			{	BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideDayltgRefPtCoordX   , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideDayltgRefPtCoordY   , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideRDP                 , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideDayltgRefPtEffAp    , iError, iSpcObjIdx );
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideDayltgRefPtSrcOrient, iError, iSpcObjIdx );
			}
			else
			{	double fRefPtX = boost::geometry::get<0>( spcDLAs.m_dlaSec.m_pntDayltgRefPnts[1] );
				double fRefPtY = boost::geometry::get<1>( spcDLAs.m_dlaSec.m_pntDayltgRefPnts[1] );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideDayltgRefPtCoordX   , BEMP_Flt, (void*) &fRefPtX														, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideDayltgRefPtCoordY   , BEMP_Flt, (void*) &fRefPtY														, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideRDP                 , BEMP_Flt, (void*) &spcDLAs.m_dlaSec.m_fRelativeDayltPotential[1]	, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideDayltgRefPtEffAp    , BEMP_Flt, (void*) &spcDLAs.m_dlaSec.m_fEffectiveAperture[1]    	, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_Spc_SrcVarSecSideDayltgRefPtSrcOrient, BEMP_Flt, (void*) &spcDLAs.m_dlaSec.m_fDegreesFromSouth        	, BEMO_User, iSpcObjIdx, pEval->eLocStatus, pEval->eLocObjType, TRUE );
		}	}


//   long  m_lDBID_Spc_SrcVarSkylitDayltgRefPtCoord      // Flt,  3,  NInp,  "ft",   0,                              "SkylitDaylightingReferencePointCoordinate" 
//   long  m_lDBID_Spc_SrcVarSkylitDayltgRefPtCoord      // Flt,  3,  NInp,  "ft",   0,                              "SkylitDaylightingReferencePointCoordinate" 
//   long  m_lDBID_Spc_SrcVarSkylitRDP                   // Flt,  1,  NInp, "",                                      "SkylitRelativeDaylightPotential"
//   long  m_lDBID_Spc_SrcVarSkylitDayltgRefPtEffAp        // Flt, 1, NInp, "",                                      "SkylitDaylightingReferencePointEffectiveAperture" 
//   long  m_lDBID_Spc_SrcVarSkylitDayltgRefPtSrcOrient    // Flt, 1, NInp, "deg",                                   "SkylitDaylightingReferencePointSourceOrientation" 


//   long  m_lDBID_Spc_SrcVarPriSideDayltgRefPtCoord;   // Flt,  3,  NInp,  "ft",   0,                              "PrimarySideDaylightingReferencePointCoordinate" 
//   long  m_lDBID_Spc_SrcVarSecSideDayltgRefPtCoord;   // Flt,  3,  NInp,  "ft",   0,                              "SecondarySideDaylightingReferencePointCoordinate" 
//
//   long  m_lDBID_Spc_SrcVarPriSideRDP;                // Flt,  1,  NInp, "",                                      "SkylitRelativeDaylightPotential"
//   long  m_lDBID_Spc_SrcVarSecSideRDP;                // Flt,  1,  NInp, "",                                      "SkylitRelativeDaylightPotential"
//
//   long  m_lDBID_Spc_SrcVarPriSideDayltgRefPtEffAp;     // Flt, 1, NInp, "",                                      "PrimarySideDaylightingReferencePointEffectiveAperture" 
//   long  m_lDBID_Spc_SrcVarPriSideDayltgRefPtSrcOrient; // Flt, 1, NInp, "deg",                                   "PrimarySideDaylightingReferencePointSourceOrientation" 
//   long  m_lDBID_Spc_SrcVarSecSideDayltgRefPtEffAp;     // Flt, 1, NInp, "",                                      "SecondarySideDaylightingReferencePointEffectiveAperture" 
//   long  m_lDBID_Spc_SrcVarSecSideDayltgRefPtSrcOrient; // Flt, 1, NInp, "deg",                                   "SecondarySideDaylightingReferencePointSourceOrientation" 


//		spcDLAs.m_pdlaTop = NULL;
//		spcDLAs.m_pdlaPrim = NULL;
//		spcDLAs.m_pdlaSec = NULL;

	}

	return dDaylitArea;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//	iWhatToPlot options:
//			  0 : view space boundaries, glazings and initial daylit areas & control positions (ignoring intersections)
//			  1 : (default) view space boundaries, glazings and final daylit areas & control positions
//			  2 : view space boundaries & glazings only
//			  3 : view space boundaries only
//			  4 : view space boundaries, glazings and initial daylit areas (not clipped by space) & setpoints (ignoring intersections) w/ glazing source orientation & effective apertures labeled
//			  5 : view space boundaries, glazings and initial daylit areas (not clipped by space) & setpoints (ignoring intersections) w/ relative daylighting potentials labeled
// Return Values:
//		  >= 0 : Success (# objects exported)
//			 -1 : Error initializing GeomDBIDs data
//			 -2 : Unrecognized object type (expecting Story or Spc)
//			 -3 : No space footprint data found
int BEMPX_ExportSVG( const char* pszSVGFileName, int iBEMClass, int iObjIdx /*=-1*/, int iWhatToPlot /*=1*/,   //, ExpEvalStruct* pEval, ExpError* /*pError*/ )
							int iDayltMethod /*=1*/ )
{	int iRetVal = 0;
	GeomDBIDs	geomIDs;
	int iError;
	BEM_ObjType eObjType = BEMO_User;

	if (!geomIDs.Init( NULL /*ExpEvalStruct**/, NULL /*ExpError**/ ))
		iRetVal = -1;
	else if (iBEMClass != geomIDs.m_iOID_Story && iBEMClass != geomIDs.m_iOID_Spc)
		iRetVal = -2;
	else
	{	if (iObjIdx < 0)
			iObjIdx = BEMPX_GetObjectIndex( BEMPX_GetClass( iBEMClass, iError ) );

		std::vector<BEMSpaceDaylitArea> spcDaylitAreas;
		double dMinXY[2] = {  99999.,  99999. };
		double dMaxXY[2] = { -99999., -99999. };
		QString sSpcName, sErrMsg, sPgLblName;
		std::string sPageLabel;
		BEMPX_GetString( BEMPX_GetDatabaseID( "Name", iBEMClass ), sPgLblName, FALSE, 0, -1, iObjIdx );			assert( !sPgLblName.isEmpty() );
		int iNumSpcs = 1;
		if (iBEMClass == geomIDs.m_iOID_Story)
		{	iNumSpcs = (int) BEMPX_GetNumChildren( geomIDs.m_iOID_Story, iObjIdx, BEMO_User, geomIDs.m_iOID_Spc );
			sPgLblName = "BuildingStory '" + sPgLblName;
		}
		else
			sPgLblName = "Space '" + sPgLblName;
		switch (iWhatToPlot)
		{	case  0 :	sPageLabel = boost::str( boost::format( "%s':  glazings and initial daylit areas and control positions (ignoring intersections)"	 ) % sPgLblName.toLocal8Bit().constData() );	break;
			case  1 :	sPageLabel = boost::str( boost::format( "%s':  glazings and final daylit areas and control positions"										 ) % sPgLblName.toLocal8Bit().constData() );   break;
			case  2 :	sPageLabel = boost::str( boost::format( "%s':  space boundaries and glazings"																		 ) % sPgLblName.toLocal8Bit().constData() );   break;
			case  3 :	sPageLabel = boost::str( boost::format( "%s'"																												 ) % sPgLblName.toLocal8Bit().constData() );   break;
			case  4 :	sPageLabel = boost::str( boost::format( "%s':  glazings, unclipped daylit areas and control positions w/ glazing source orientation and effective apertures" ) % sPgLblName.toLocal8Bit().constData() );   break;
			case  5 :	sPageLabel = boost::str( boost::format( "%s':  glazings, unclipped daylit areas and control positions w/ relative daylighting potentials"							 ) % sPgLblName.toLocal8Bit().constData() );   break;
		}
		for (int i=0; i < iNumSpcs; i++)
		{	
			int iSpcObjIdx = iObjIdx;
			if (iBEMClass == geomIDs.m_iOID_Story)
				iSpcObjIdx = BEMPX_GetChildObjectIndex( geomIDs.m_iOID_Story, geomIDs.m_iOID_Spc, iError, eObjType, i+1, iObjIdx );
			assert( iSpcObjIdx >= 0 );
			if (iSpcObjIdx >= 0)
			{
				BEMSpaceDaylitArea spcDLA;  // moved daylit area arrays to parent class
				spcDLA.m_iSpcObjIdx = iSpcObjIdx;
				BEMPX_GetString( BEMPX_GetDatabaseID( "Name", geomIDs.m_iOID_Spc ), sSpcName, FALSE, 0, -1, iSpcObjIdx );		assert( !sSpcName.isEmpty() );
				if (SetupSpaceDaylighting( spcDLA, &geomIDs, sSpcName.toLocal8Bit().constData(), sErrMsg, iDayltMethod ) >= 0)
				{
					if (spcDLA.m_daSpaceExtremes[0] < dMinXY[0])
						dMinXY[0] = spcDLA.m_daSpaceExtremes[0];
					if (spcDLA.m_daSpaceExtremes[1] > dMaxXY[0])
						dMaxXY[0] = spcDLA.m_daSpaceExtremes[1];
					if (spcDLA.m_daSpaceExtremes[2] < dMinXY[1])
						dMinXY[1] = spcDLA.m_daSpaceExtremes[2];
					if (spcDLA.m_daSpaceExtremes[3] > dMaxXY[1])
						dMaxXY[1] = spcDLA.m_daSpaceExtremes[3];
					spcDaylitAreas.push_back( spcDLA );
				}
				else
				{	assert( FALSE );
				}
			}
		}

		bool bHaveBoundingBox = (dMinXY[0] < 99999. && dMinXY[1] < 99999. && dMaxXY[0] > -99999. && dMaxXY[1] > -99999.);
double dBoxMargin = 5.;
double dPageLabelHt = 8.;
		double dX=100., dY=100.;
		BEMPoly bemPolyBox;
		if (bHaveBoundingBox)
		{	boost::geometry::append(  bemPolyBox, boost::tuples::make_tuple( (dMinXY[0] - dBoxMargin), (dMinXY[1] - dBoxMargin) ));
			boost::geometry::append(  bemPolyBox, boost::tuples::make_tuple( (dMinXY[0] - dBoxMargin), (dMaxXY[1] + dBoxMargin) ));
			boost::geometry::append(  bemPolyBox, boost::tuples::make_tuple( (dMaxXY[0] + dBoxMargin), (dMaxXY[1] + dBoxMargin) ));
			boost::geometry::append(  bemPolyBox, boost::tuples::make_tuple( (dMaxXY[0] + dBoxMargin), (dMinXY[1] - dBoxMargin) ));
			boost::geometry::correct( bemPolyBox );	// will both close the poly (first & last vertex should be equal) and correct winding direction if needed
			dX = dMaxXY[0] - dMinXY[0] + (dBoxMargin * 2.);
			dY = dMaxXY[1] - dMinXY[1] + (dBoxMargin * 2.) + dPageLabelHt;
		}

		if (spcDaylitAreas.size() < 1)
			iRetVal = -3;
		else
		{	//typedef typename boost::geometry::point_type<Geometry1>::type point_type;
			std::ofstream svg( pszSVGFileName );
			boost::geometry::svg_mapper<BEMPoint> mapper( svg, (int) (dX * 5.), (int) (dY * 5.) );

			if (bHaveBoundingBox)
				mapper.add( bemPolyBox );
		// first round - daylit areas & glazings
			for (std::vector<BEMSpaceDaylitArea>::iterator spc1=spcDaylitAreas.begin(); spc1!=spcDaylitAreas.end(); ++spc1)
			{	BEMSpaceDaylitArea* pSpc1 = &(*spc1);
				if (pSpc1)
				{	if (iWhatToPlot != 3 && pSpc1->m_daylitAreas.size() > 0)
					{	for (std::vector<BEMDaylitArea>::iterator chk1=pSpc1->m_daylitAreas.begin(); chk1!=pSpc1->m_daylitAreas.end(); ++chk1)
						{	BEMDaylitArea* pChk1 = &(*chk1);
							if (pChk1)
							{	for (int id=0; (iWhatToPlot != 2 && id < (pChk1->IsSidelitArea() ? 2 : 1)); id++)
								{	switch (iWhatToPlot)
									{	case  0 :	if (pChk1->m_dOriginalAreaInSpc[id] > 0)
															mapper.add( pChk1->m_polyOrigDaylitInSpc[id] );
														break;
										case  1 :	if (pChk1->m_dFinalArea[id] > 0)
															//mapper.add( pChk1->m_polyFinalDaylit[id] );
															BOOST_FOREACH(BEMPoly const& p, pChk1->m_polyFinalDaylit[id])
															{	mapper.add( p );
															}
														break;
										case  4 :
										case  5 :	if (boost::geometry::area( pChk1->m_polyOrigDaylitArea[id] ) > 0)
															mapper.add( pChk1->m_polyOrigDaylitArea[id] );
														break;
								}	}
								mapper.add( pChk1->m_polyGlazing );
			}	}	}	}	}

		// second round - dayltg reference points
			for (std::vector<BEMSpaceDaylitArea>::iterator spc1=spcDaylitAreas.begin(); spc1!=spcDaylitAreas.end(); ++spc1)
			{	BEMSpaceDaylitArea* pSpc1 = &(*spc1);
				if (pSpc1)
				{	if (iWhatToPlot == 1)
					{	for (int id=0; id < 3; id++)
						{	BEMDaylitArea* pDLA = (id==0 ? &pSpc1->m_dlaTop : (id==1 ? &pSpc1->m_dlaPrim : &pSpc1->m_dlaSec));
							int id2 = (id==2 ? 1 : 0);
							if (pDLA && pDLA->m_bDLRefPntValid[id2])
								mapper.add( pDLA->m_pntDayltgRefPnts[id2] );
					}	}
					else if ((iWhatToPlot == 0 || iWhatToPlot == 4 || iWhatToPlot == 5) && pSpc1->m_daylitAreas.size() > 0)
					{	for (std::vector<BEMDaylitArea>::iterator chk1=pSpc1->m_daylitAreas.begin(); chk1!=pSpc1->m_daylitAreas.end(); ++chk1)
						{	BEMDaylitArea* pChk1 = &(*chk1);
							if (pChk1)
							{	for (int id=0; id < (pChk1->IsSidelitArea() ? 2 : 1); id++)
								{	if (pChk1->m_bDLRefPntValid[id])
										mapper.add( pChk1->m_pntDayltgRefPnts[id] );
								}
			}	}	}	}	}

		// third round - space boundaries
			for (std::vector<BEMSpaceDaylitArea>::iterator spc1=spcDaylitAreas.begin(); spc1!=spcDaylitAreas.end(); ++spc1)
			{	BEMSpaceDaylitArea* pSpc1 = &(*spc1);
				if (pSpc1)
				{	mapper.add( pSpc1->m_polySpace );
//					mapper.add( pSpc1->m_ptSpcCenter );
			}	}


			if (bHaveBoundingBox)
				mapper.map( bemPolyBox, "opacity:0.8;fill:none;stroke:rgb(205,205,205);stroke-width:1;stroke-linecap:square");
		// first round - daylit areas & glazings
			for (std::vector<BEMSpaceDaylitArea>::iterator spc1=spcDaylitAreas.begin(); spc1!=spcDaylitAreas.end(); ++spc1)
			{	BEMSpaceDaylitArea* pSpc1 = &(*spc1);
				if (pSpc1)
				{	if (iWhatToPlot != 3 && pSpc1->m_daylitAreas.size() > 0)
					{	for (std::vector<BEMDaylitArea>::iterator chk1=pSpc1->m_daylitAreas.begin(); chk1!=pSpc1->m_daylitAreas.end(); ++chk1)
						{	BEMDaylitArea* pChk1 = &(*chk1);
							if (pChk1)
							{	for (int id=0; (iWhatToPlot != 2 && id < (pChk1->IsSidelitArea() ? 2 : 1)); id++)
								{	switch (iWhatToPlot)
									{	case  0 :	if (pChk1->m_dOriginalAreaInSpc[id] > 0)
														{	if (id == 0)
//																mapper.map( pChk1->m_polyOrigDaylitInSpc[id], "fill-rule:nonzero;fill-opacity:0.3;fill:rgb(200,200,0);stroke:rgb(200,200,0);stroke-width:2;" );
																mapper.map( pChk1->m_polyOrigDaylitInSpc[id], "fill-rule:nonzero;fill-opacity:0.3;fill:rgb(255,255,64);stroke:rgb(255,255,64);stroke-width:2;" );
															else
//																mapper.map( pChk1->m_polyOrigDaylitInSpc[id], "fill-rule:nonzero;fill-opacity:0.3;fill:rgb(100,200,0);stroke:rgb(100,200,0);stroke-width:2;" );
																mapper.map( pChk1->m_polyOrigDaylitInSpc[id], "fill-rule:nonzero;fill-opacity:0.3;fill:rgb(192,192,48);stroke:rgb(192,192,48);stroke-width:2;" );
														}
														break;
										case  1 :	if (pChk1->m_dFinalArea[id] > 0)
														{	//if (id == 0)
//															//	mapper.map( pChk1->m_polyFinalDaylit[id],	"fill-rule:nonzero;fill-opacity:0.3;fill:rgb(200,200,0);stroke:rgb(200,200,0);stroke-width:2;" );
															//	mapper.map( pChk1->m_polyFinalDaylit[id],	"fill-rule:nonzero;fill-opacity:0.3;fill:rgb(255,255,64);stroke:rgb(255,255,64);stroke-width:2;" );
															//else
//															//	mapper.map( pChk1->m_polyFinalDaylit[id],	"fill-rule:nonzero;fill-opacity:0.3;fill:rgb(100,200,0);stroke:rgb(100,200,0);stroke-width:2;" );
															//	mapper.map( pChk1->m_polyFinalDaylit[id],	"fill-rule:nonzero;fill-opacity:0.3;fill:rgb(192,192,48);stroke:rgb(192,192,48);stroke-width:2;" );
															BOOST_FOREACH(BEMPoly const& p, pChk1->m_polyFinalDaylit[id])
															{	if (id == 0)
																	mapper.map( p, "fill-rule:nonzero;fill-opacity:0.3;fill:rgb(255,255,64);stroke:rgb(255,255,64);stroke-width:2;" );
																else
																	mapper.map( p, "fill-rule:nonzero;fill-opacity:0.3;fill:rgb(192,192,48);stroke:rgb(192,192,48);stroke-width:2;" );
															}
														}
														break;
										case  4 :
										case  5 :	if (boost::geometry::area( pChk1->m_polyOrigDaylitArea[id] ) > 0)
														{	if (id == 0)
																mapper.map( pChk1->m_polyOrigDaylitArea[id], "fill-rule:nonzero;fill-opacity:0.3;fill:rgb(255,255,64);stroke:rgb(255,255,64);stroke-width:2;" );
															else
//																mapper.map( pChk1->m_polyOrigDaylitArea[id], "fill-rule:nonzero;fill-opacity:0.3;fill:rgb(192,192,48);stroke:rgb(192,192,48);stroke-width:2;" );
																mapper.map( pChk1->m_polyOrigDaylitArea[id], "fill-rule:nonzero;fill-opacity:0.3;fill:rgb(220,220,0);stroke:rgb(220,220,0);stroke-width:2;" );
														}
														break;
								}	}
//								mapper.map( pChk1->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(0,220,220);stroke:rgb(0,220,220);stroke-width:1;");
								if (iWhatToPlot == 4)		// lighter colored glazings when labeling effective apertures & source angles
								{	if (pChk1->IsSidelitArea())
										mapper.map( pChk1->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(64,192,255);stroke:rgb(64,192,255);stroke-width:3;");
									else
										mapper.map( pChk1->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(64,192,255);stroke:rgb(64,192,255);stroke-width:1;");
								}
								else
								{	if (pChk1->IsSidelitArea())
										mapper.map( pChk1->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(0,128,255);stroke:rgb(0,128,255);stroke-width:3;");
									else
										mapper.map( pChk1->m_polyGlazing, "fill-rule:nonzero;fill-opacity:0.7;fill:rgb(0,128,255);stroke:rgb(0,128,255);stroke-width:1;");
								}
					}	}	}
					iRetVal++;
			}	}

		// second round - dayltg reference points
			for (std::vector<BEMSpaceDaylitArea>::iterator spc1=spcDaylitAreas.begin(); spc1!=spcDaylitAreas.end(); ++spc1)
			{	BEMSpaceDaylitArea* pSpc1 = &(*spc1);
				if (pSpc1)
				{	if (iWhatToPlot == 1)
					{	for (int id=0; id < 3; id++)
						{	BEMDaylitArea* pDLA = (id==0 ? &pSpc1->m_dlaTop : (id==1 ? &pSpc1->m_dlaPrim : &pSpc1->m_dlaSec));
							int id2 = (id==2 ? 1 : 0);
							if (pDLA && pDLA->m_bDLRefPntValid[id2])
							{	if (pDLA->m_bDLRefPntInStdLoc[id2])
									mapper.map( pDLA->m_pntDayltgRefPnts[id2], "fill-opacity:0.5;fill:rgb(0,96,0);stroke:rgb(0,96,0);stroke-width:1", (id2==0 ? 3 : 2) );
								else
									mapper.map( pDLA->m_pntDayltgRefPnts[id2], "fill-opacity:0.5;fill:rgb(96,64,0);stroke:rgb(96,64,0);stroke-width:1", (id2==0 ? 3 : 2) );
					}	}	}
					else if ((iWhatToPlot == 0 || iWhatToPlot == 4 || iWhatToPlot == 5) && pSpc1->m_daylitAreas.size() > 0)
					{	for (std::vector<BEMDaylitArea>::iterator chk1=pSpc1->m_daylitAreas.begin(); chk1!=pSpc1->m_daylitAreas.end(); ++chk1)
						{	BEMDaylitArea* pChk1 = &(*chk1);
							if (pChk1)
							{	for (int id=0; id < (pChk1->IsSidelitArea() ? 2 : 1); id++)
								{	if (pChk1->m_bDLRefPntValid[id])
									{	if (iWhatToPlot == 5)   // LIGHTER dayltg ref point colors when overwriting them w/ RDP values
										{	if (pChk1->m_bDLRefPntInStdLoc[id])
												mapper.map( pChk1->m_pntDayltgRefPnts[id], "fill-opacity:0.5;fill:rgb(64,192,64);stroke:rgb(64,192,64);stroke-width:1", (id==0 ? 3 : 2) );
											else
												mapper.map( pChk1->m_pntDayltgRefPnts[id], "fill-opacity:0.5;fill:rgb(192,128,64);stroke:rgb(192,128,64);stroke-width:1", (id==0 ? 3 : 2) );
										}
										else
										{	if (pChk1->m_bDLRefPntInStdLoc[id])
												mapper.map( pChk1->m_pntDayltgRefPnts[id], "fill-opacity:0.5;fill:rgb(0,96,0);stroke:rgb(0,96,0);stroke-width:1", (id==0 ? 3 : 2) );
											else
												mapper.map( pChk1->m_pntDayltgRefPnts[id], "fill-opacity:0.5;fill:rgb(96,64,0);stroke:rgb(96,64,0);stroke-width:1", (id==0 ? 3 : 2) );
										}
									}
			}	}	}	}	}	}

		// third round - space boundaries
			for (std::vector<BEMSpaceDaylitArea>::iterator spc1=spcDaylitAreas.begin(); spc1!=spcDaylitAreas.end(); ++spc1)
			{	BEMSpaceDaylitArea* pSpc1 = &(*spc1);
				if (pSpc1)
				{	mapper.map( pSpc1->m_polySpace, "opacity:0.8;fill:none;stroke:rgb(128,128,128);stroke-width:2;stroke-dasharray:1,7;stroke-linecap:round");
//					mapper.map( pSpc1->m_ptSpcCenter, "fill-opacity:0.5;fill:rgb(153,204,0);stroke:rgb(153,204,0);stroke-width:2", 3 );
			}	}

	// write labels LAST to ensure that they are placed on top of all areas/lines/points

		// Dayltg area & ref pt labels
			std::string sLabel;
			BEMPoint ptLabel;
			if (iWhatToPlot == 4 || iWhatToPlot == 5)
			{	for (std::vector<BEMSpaceDaylitArea>::iterator spc1=spcDaylitAreas.begin(); spc1!=spcDaylitAreas.end(); ++spc1)
				{	BEMSpaceDaylitArea* pSpc1 = &(*spc1);
					if (pSpc1 && pSpc1->m_daylitAreas.size() > 0)
					{	for (std::vector<BEMDaylitArea>::iterator chk1=pSpc1->m_daylitAreas.begin(); chk1!=pSpc1->m_daylitAreas.end(); ++chk1)
						{	BEMDaylitArea* pChk1 = &(*chk1);
							if (pChk1 && (pChk1->m_bDLRefPntValid[0] || pChk1->m_bDLRefPntValid[1]))
							{	// daylit area source orientation
								if (iWhatToPlot == 4 && pChk1->m_fDegreesFromSouth >= 0)
//								{	sLabel = boost::str( boost::format( "SO: %.0f°" ) % pChk1->m_fDegreesFromSouth );
								{	sLabel = boost::str( boost::format( "SO: %.0f" ) % pChk1->m_fDegreesFromSouth );
									boost::geometry::centroid( pChk1->m_polyGlazing, ptLabel );
									mapper.text( ptLabel, sLabel, "font-family:sans-serif;font-size:8px;text-anchor:middle;fill:rgb(128,0,0)", 0 /*offset_x*/, 5 /*offset_y*/ );  // , lineheight=10
								}

								for (int id=0; id < (pChk1->IsSidelitArea() ? 2 : 1); id++)
								{	if (iWhatToPlot == 4 && boost::geometry::area( pChk1->m_polyOrigDaylitArea[id] ) > 0)
									{  // daylit area effective aperture
										sLabel = boost::str( boost::format( "EA: %.3f" ) % pChk1->m_fEffectiveAperture[id] );
										boost::geometry::centroid( pChk1->m_polyOrigDaylitArea[id], ptLabel );
										mapper.text( ptLabel, sLabel, "font-family:sans-serif;font-size:8px;text-anchor:middle;fill:rgb(128,0,0)", 0 /*offset_x*/, 5 /*offset_y*/ );  // , lineheight=10
									}
									if (iWhatToPlot == 5 && pChk1->m_bDLRefPntValid[id])
									{  // relative daylighting potential
										sLabel = boost::str( boost::format( "%.0f" ) % pChk1->m_fRelativeDayltPotential[id] );
										mapper.text( pChk1->m_pntDayltgRefPnts[id], sLabel, "font-family:sans-serif;font-size:8px;font-weight:bold;text-anchor:middle;fill:rgb(128,0,0)", 0 /*offset_x*/, 10 /*offset_y*/ );  // , lineheight=10
								}	}
			}	}	}	}	}

		// Space Name labels
			if (iWhatToPlot != 4 && iWhatToPlot != 5)
			{	for (std::vector<BEMSpaceDaylitArea>::iterator spc1=spcDaylitAreas.begin(); spc1!=spcDaylitAreas.end(); ++spc1)
				{	BEMSpaceDaylitArea* pSpc1 = &(*spc1);
					if (pSpc1 && pSpc1->m_sSpcName.size() > 0)
						mapper.text( pSpc1->m_ptSpcCenter, pSpc1->m_sSpcName, "font-family:sans-serif;font-size:16px;text-anchor:middle;fill:rgb(128,0,0)", 0 /*offset_x*/, 5 /*offset_y*/ );  // , lineheight=10
			}	}

		// Page label
			if (bHaveBoundingBox)
			{	ptLabel.set<0>( (dMinXY[0] - dBoxMargin + 1) );
				ptLabel.set<1>( (dMaxXY[1] + dBoxMargin + 1) );
//				mapper.text( ptLabel, sPageLabel, "font-family:sans-serif;font-size:20px;text-anchor:start;fill:rgb(128,0,0)", 0 /*offset_x*/, 0 /*offset_y*/ );  // , lineheight=10
				if (iWhatToPlot == 4 || iWhatToPlot == 5)
					mapper.text( ptLabel, sPageLabel, "font-family:sans-serif;font-size:12px;fill:rgb(128,0,0)", 0 /*offset_x*/, 0 /*offset_y*/ );  // , lineheight=10
				else
					mapper.text( ptLabel, sPageLabel, "font-family:sans-serif;font-size:16px;fill:rgb(128,0,0)", 0 /*offset_x*/, 0 /*offset_y*/ );  // , lineheight=10
			}
		}
	}

	return iRetVal;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> BEM3Dpoint;
typedef boost::geometry::model::linestring<BEM3Dpoint> BEM3Dline;

// Return Values:
//		  >= 0 : PolyLp area
//			 -1 : Invalid GeomDBIDs data
//			 -2 : PolyLp object not found
//			 -3 : Unable to find three unique, non-collinear poygon vertices to calculate normal vector from (within forst 10 polygon vertices)
//			 -4 : Error posting PolyLp data to BEMBase
//			 -5 : Error (assertion thrown) by boost::geometry library
double InitPolyLoop( int iPolyLpObjIdx, ExpEvalStruct* /*pEval*/, ExpError* /*pError*/ )
{	double dPolyLpArea = 0.0;
	if (ruleSet.getGeomIDs()->m_iOID_PolyLp < 1 || ruleSet.getGeomIDs()->m_lDBID_PolyLp_Area < 1)
		dPolyLpArea = -1;
	else if (iPolyLpObjIdx < 0 || iPolyLpObjIdx >= BEMPX_GetNumObjects( ruleSet.getGeomIDs()->m_iOID_PolyLp ))
		dPolyLpArea = -2;
	else
	{
		try		// SAC 6/10/15 - catch bugs in boost::geometry
		{
// much of this a copy of PolyLpToBEMPoly()
	//	BEMPoly bemPoly;
		int iNumPolyVerts = 0;
		int iError, iC;
		BEM_ObjType eObjType = BEMO_User;
		double fCoords[3];
		double fPolyLineCoords[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };
		double dPerim=0.0;	double faLastCoord[3] = {0,0,0};		// SAC 6/5/15
		double dMinXYZ[3] = {  99999.,  99999.,  99999. };
		double dMaxXYZ[3] = { -99999., -99999., -99999. };
		int iPlnVert2=0, iPlnVert3=0;
		vector<double> faX, faY, faZ;
		vector<double> faX3, faY3, faZ3;
		long iNumPts = (int) BEMPX_GetNumChildren( ruleSet.getGeomIDs()->m_iOID_PolyLp, iPolyLpObjIdx, BEMO_User, ruleSet.getGeomIDs()->m_iOID_CartesianPt );			assert( iNumPts > 2 );
		for (int i=0; i < iNumPts; i++)
		{	int iCartPtObjIdx = BEMPX_GetChildObjectIndex( ruleSet.getGeomIDs()->m_iOID_PolyLp, ruleSet.getGeomIDs()->m_iOID_CartesianPt, iError, eObjType, i+1, iPolyLpObjIdx );		assert( iCartPtObjIdx >= 0 );
			if (iCartPtObjIdx >= 0)
			{	int iNumCoords = BEMPX_GetFloatArray( ruleSet.getGeomIDs()->m_lDBID_CartesianPt_Coord, fCoords, 3, 0, BEMP_Flt, iCartPtObjIdx );											assert( iNumCoords == 3 );
				if (iNumCoords == 3)
				{
	//				boost::geometry::append(bemPoly, boost::tuples::make_tuple( (double) fCoords[0], (double) fCoords[1] ));
					for (iC=0; iC<3; iC++)
					{	if (fCoords[iC] > dMaxXYZ[iC])
							dMaxXYZ[iC] = (double) fCoords[iC];
						if (fCoords[iC] < dMinXYZ[iC])
							dMinXYZ[iC] = (double) fCoords[iC];
					}

				// find three poly points suitable for defining the plane of the polygon
					if (iNumPolyVerts == 0)
					{	fPolyLineCoords[0][0] = fCoords[0];
						fPolyLineCoords[0][1] = fCoords[1];
						fPolyLineCoords[0][2] = fCoords[2];
						faX3.push_back( fCoords[0] );
						faY3.push_back( fCoords[1] );
						faZ3.push_back( fCoords[2] );
					}
					else if (iPlnVert2==0 && (	!WithinMargin(fPolyLineCoords[0][0], fCoords[0], 0.001) ||
														!WithinMargin(fPolyLineCoords[0][1], fCoords[1], 0.001) ||
														!WithinMargin(fPolyLineCoords[0][2], fCoords[2], 0.001) ))
					{	fPolyLineCoords[1][0] = fCoords[0];
						fPolyLineCoords[1][1] = fCoords[1];
						fPolyLineCoords[1][2] = fCoords[2];
						faX3.push_back( fCoords[0] );
						faY3.push_back( fCoords[1] );
						faZ3.push_back( fCoords[2] );
						iPlnVert2 = iNumPolyVerts;
					}
					else if (iPlnVert2 > 0 && iPlnVert3 == 0)
					{	// check to see if this vertex when combined w/ previous two unique vertices create two non-collinear segments
						//boost::geometry::model::linestring<BEMPoint> polyLine;
						//boost::geometry::append(polyLine, boost::tuples::make_tuple( (double) fCoords[0], (double) fCoords[1] ));

						BEM3Dline line3d;
						line3d.push_back(BEM3Dpoint( fPolyLineCoords[0][0], fPolyLineCoords[0][1], fPolyLineCoords[0][2] ));
						line3d.push_back(BEM3Dpoint( fPolyLineCoords[1][0], fPolyLineCoords[1][1], fPolyLineCoords[1][2] ));
						line3d.push_back(BEM3Dpoint( fCoords[0], fCoords[1], fCoords[2] ));
				//		line3d.push_back(make<BEM3Dpoint>( fPolyLineCoords[0][0], fPolyLineCoords[0][1], fPolyLineCoords[0][2] ));
				//		line3d.push_back(make<BEM3Dpoint>( fPolyLineCoords[1][0], fPolyLineCoords[1][1], fPolyLineCoords[1][2] ));
				//		line3d.push_back(make<BEM3Dpoint>( fCoords[0], fCoords[1], fCoords[2] ));
						BEM3Dline simplified;
						boost::geometry::simplify( line3d, simplified, 0.01 );
						if (boost::size( simplified ) == 3)
						{	fPolyLineCoords[2][0] = fCoords[0];
							fPolyLineCoords[2][1] = fCoords[1];
							fPolyLineCoords[2][2] = fCoords[2];
							faX3.push_back( fCoords[0] );
							faY3.push_back( fCoords[1] );
							faZ3.push_back( fCoords[2] );
							iPlnVert3 = iNumPolyVerts;
						}
					}
					faX.push_back( fCoords[0] );
					faY.push_back( fCoords[1] );
					faZ.push_back( fCoords[2] );
					iNumPolyVerts++;

					if (iNumPolyVerts > 1)		// SAC 6/5/15
						dPerim += sqrt(	((fCoords[0]-faLastCoord[0])*(fCoords[0]-faLastCoord[0])) +
												((fCoords[1]-faLastCoord[1])*(fCoords[1]-faLastCoord[1])) +
												((fCoords[2]-faLastCoord[2])*(fCoords[2]-faLastCoord[2])) );
					faLastCoord[0] = fCoords[0];		faLastCoord[1] = fCoords[1];		faLastCoord[2] = fCoords[2];
				}
		}	}
					if (iNumPolyVerts > 1)		// SAC 6/5/15
						dPerim += sqrt(	((fPolyLineCoords[0][0]-faLastCoord[0])*(fPolyLineCoords[0][0]-faLastCoord[0])) +
												((fPolyLineCoords[0][1]-faLastCoord[1])*(fPolyLineCoords[0][1]-faLastCoord[1])) +
												((fPolyLineCoords[0][2]-faLastCoord[2])*(fPolyLineCoords[0][2]-faLastCoord[2])) );

	// store NumOfPts regardless of success of Area calcs or validity of PolyLp
		BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_NumOfPts, BEMP_Int, (void*) &iNumPts, BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault );   // pEval->eLocStatus, pEval->eLocObjType, TRUE

		if (iNumPolyVerts < 3 || iPlnVert3 < 1)
			dPolyLpArea = -3;
		else
		{
			dPolyLpArea = (double) PolygonArea_OrderDependent( faX, faY, faZ );
			double dPolyLpArea3 = (double) PolygonArea_OrderDependent( faX3, faY3, faZ3 );
   		double fOutNormalMult = (((dPolyLpArea > 0 && dPolyLpArea3 > 0) ||
											  (dPolyLpArea < 0 && dPolyLpArea3 < 0)) ? 1 : -1);	// SAC 11/21/13 - used to ensure outward normal is in correct direction - 
			dPolyLpArea = fabs( dPolyLpArea );
	//		float fOutNormalMult = 1;
	//		dPolyLpArea = (double) PolygonArea( faX, faY, faZ );			assert( dPolyLpArea > 0 );

			double fXYLen			= sqrt( ((dMaxXYZ[0]-dMinXYZ[0])*(dMaxXYZ[0]-dMinXYZ[0])) + ((dMaxXYZ[1]-dMinXYZ[1])*(dMaxXYZ[1]-dMinXYZ[1])) );
			double fPerim			= dPerim;
			double fZBottom		= dMinXYZ[2];
			double fZTop			= dMaxXYZ[2];
			double fZHgt			= fZTop - fZBottom;
			double fXCenter		= ((dMinXYZ[0] + dMaxXYZ[0]) / 2.0);
			double fYCenter		= ((dMinXYZ[1] + dMaxXYZ[1]) / 2.0);

					double fVector1i = fPolyLineCoords[1][0]-fPolyLineCoords[0][0];
					double fVector1j = fPolyLineCoords[1][1]-fPolyLineCoords[0][1];
					double fVector1k = fPolyLineCoords[1][2]-fPolyLineCoords[0][2];
					double fVector2i = fPolyLineCoords[2][0]-fPolyLineCoords[1][0];
					double fVector2j = fPolyLineCoords[2][1]-fPolyLineCoords[1][1];
					double fVector2k = fPolyLineCoords[2][2]-fPolyLineCoords[1][2];
			double fVectorOi		= fOutNormalMult * (fVector1j*fVector2k - fVector1k*fVector2j);
			double fVectorOj		= fOutNormalMult * (fVector1k*fVector2i - fVector1i*fVector2k);
			double fVectorOk		= fOutNormalMult * (fVector1i*fVector2j - fVector1j*fVector2i);
			double fVectorOLen	= sqrt( (fVectorOi*fVectorOi) + (fVectorOj*fVectorOj) + (fVectorOk*fVectorOk) );
			double fUnitVectorOi	= (fVectorOLen > 0 ? fVectorOi / fVectorOLen : 0.0);
			double fUnitVectorOj	= (fVectorOLen > 0 ? fVectorOj / fVectorOLen : 0.0);
			double fUnitVectorOk	= (fVectorOLen > 0 ? fVectorOk / fVectorOLen : 0.0);
			double fVectorPLen	= sqrt( (fVectorOi*fVectorOi) + (fVectorOj*fVectorOj) );
			double fUnitVectorPi	= (fVectorPLen > 0 ? fVectorOi / fVectorPLen : 0.0);
			double fUnitVectorPj	= (fVectorPLen > 0 ? fVectorOj / fVectorPLen : 0.0);
			string sRngMsg;
			if (WithinMargin( dMinXYZ[2], dMaxXYZ[2], 0.001 ))
				sRngMsg = boost::str( boost::format( "Z = %g" ) % dMinXYZ[2] );
			else
				sRngMsg = boost::str( boost::format( "Z: %g - %g" ) % dMinXYZ[2] % dMaxXYZ[2] );

			QString sParentInfrm;
			BEMObject* pPLObj = BEMPX_GetObjectByClass( ruleSet.getGeomIDs()->m_iOID_PolyLp, iError, iPolyLpObjIdx );
			if (pPLObj && pPLObj->getParent() && pPLObj->getParent()->getClass())
				sParentInfrm = QString( "Parent:  %1  '%2'" ).arg( pPLObj->getParent()->getClass()->getShortName(), pPLObj->getParent()->getName() );
			if (!sParentInfrm.isEmpty())
				BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_ParentInfrm, BEMP_Str, (void*) sParentInfrm.toLocal8Bit().constData(), BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault );   // pEval->eLocStatus, pEval->eLocObjType, TRUE
			else
				BEMPX_DefaultProperty( ruleSet.getGeomIDs()->m_lDBID_PolyLp_ParentInfrm, iError, iPolyLpObjIdx );

			if (	BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_XYLen       , BEMP_Flt, (void*) &fXYLen        , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||   // pEval->eLocStatus, pEval->eLocObjType, TRUE
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_Perim       , BEMP_Flt, (void*) &fPerim        , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||   // SAC 6/5/15
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_ZBottom     , BEMP_Flt, (void*) &fZBottom      , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_ZTop        , BEMP_Flt, (void*) &fZTop         , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_ZHgt        , BEMP_Flt, (void*) &fZHgt         , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_ZRngMessage , BEMP_Str, (void*) sRngMsg.c_str(), BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_XCenter     , BEMP_Flt, (void*) &fXCenter      , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_YCenter     , BEMP_Flt, (void*) &fYCenter      , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_VectorOi    , BEMP_Flt, (void*) &fVectorOi     , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_VectorOj    , BEMP_Flt, (void*) &fVectorOj     , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_VectorOk    , BEMP_Flt, (void*) &fVectorOk     , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_VectorOLen  , BEMP_Flt, (void*) &fVectorOLen   , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_UnitVectorOi, BEMP_Flt, (void*) &fUnitVectorOi , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_UnitVectorOj, BEMP_Flt, (void*) &fUnitVectorOj , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_UnitVectorOk, BEMP_Flt, (void*) &fUnitVectorOk , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_VectorPLen  , BEMP_Flt, (void*) &fVectorPLen   , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_UnitVectorPi, BEMP_Flt, (void*) &fUnitVectorPi , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0  ||
					BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_UnitVectorPj, BEMP_Flt, (void*) &fUnitVectorPj , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault ) < 0 )
				dPolyLpArea = -4;
			else
			{	if (ruleSet.getGeomIDs()->m_lDBID_PolyLp_TiltAngle > 0)
				{	double dTiltAngle=-999.0;
					if (fVectorOLen <= 0)
					   dTiltAngle = -999;
					else if (fUnitVectorOk == 1)
					   dTiltAngle =    0;
					else if (fUnitVectorOk == -1)
					   dTiltAngle =  180;
					else 
					   dTiltAngle = acos( fUnitVectorOk ) * 180/3.14159265395;
					if (dTiltAngle != -999.0)
						BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_TiltAngle, BEMP_Flt, (void*) &dTiltAngle , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault );
				}
				if (ruleSet.getGeomIDs()->m_lDBID_PolyLp_Azimuth > 0)
				{	double dAzimuth=-999.0;
					double fBldgUnitVectorNi = 0.0;   // Bldg:UnitVectorNi in Com - X coordinate of unit vector defining true north
					double fBldgUnitVectorNj = 1.0;   // Bldg:UnitVectorNj in Com - Y coordinate of unit vector defining true north
					if (fVectorPLen <= 0)
						dAzimuth = -999.0;
					// NOTE - this Azimuth does not adjust for BUILDING Azimuth
					else if (( fUnitVectorPi * fBldgUnitVectorNi +
								  fUnitVectorPj * fBldgUnitVectorNj ) == 1 )
						dAzimuth =    0;		// due north
					else if (( fUnitVectorPi * fBldgUnitVectorNi +
								  fUnitVectorPj * fBldgUnitVectorNj ) == -1 )
						dAzimuth =  180;		// due south
					else if (( fBldgUnitVectorNi * fUnitVectorPj -
								  fBldgUnitVectorNj * fUnitVectorPi ) < 0 )
						dAzimuth = acos( fUnitVectorPi * fBldgUnitVectorNi +
											  fUnitVectorPj * fBldgUnitVectorNj ) * 180/3.14159265359;	// postive rotation 
					else
						dAzimuth = 360 - ( acos( fUnitVectorPi * fBldgUnitVectorNi +
														 fUnitVectorPj * fBldgUnitVectorNj ) * 180/3.14159265359 );	// negative rotation
					if (dAzimuth != -999.0)
						BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_PolyLp_Azimuth, BEMP_Flt, (void*) &dAzimuth , BEMO_User, iPolyLpObjIdx, BEMS_ProgDefault );
			}	}
		}

		}
		catch (std::exception& e)
		{	QString sPolyLpName;
			BEMPX_GetString( BEMPX_GetDatabaseID( "Name", ruleSet.getGeomIDs()->m_iOID_PolyLp ), sPolyLpName, FALSE, 0, -1, iPolyLpObjIdx );			assert( !sPolyLpName.isEmpty() );
			std::string strErrMsg = boost::str( boost::format("InitPolyLoop() error processing PolyLp '%s':  %s" ) % sPolyLpName.toLocal8Bit().constData() % e.what() );
			BEMPX_WriteLogFile( strErrMsg.c_str() );
			dPolyLpArea = -5;
		}
		catch (...)
		{	QString sPolyLpName;
			BEMPX_GetString( BEMPX_GetDatabaseID( "Name", ruleSet.getGeomIDs()->m_iOID_PolyLp ), sPolyLpName, FALSE, 0, -1, iPolyLpObjIdx );			assert( !sPolyLpName.isEmpty() );
			std::string strErrMsg = boost::str( boost::format("InitPolyLoop() error processing PolyLp '%s':  suspect boost::geometry library error" ) % sPolyLpName.toLocal8Bit().constData() );
			BEMPX_WriteLogFile( strErrMsg.c_str() );
			dPolyLpArea = -5;
		}
	}

	return dPolyLpArea;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// SAC 2/18/14 - routine to create a PolyLp based on various 2D geometry inputs
//				Arg usage based on iPolyType:			dArg6			dArg7
//				---------------------------------------------------------
// 	iPolyType values:		0 => generic	=>		Unused		Unused
//									1 => Wall		=> 	WallHgt		Unused
//									2 => Window		=>		WallHgt		WallArea
//									3 => Door		=>		WallHgt		WallArea
//									4 => Shade		=>		PolyHgt		Shape			also dCentX/Y/Z
//									5 => Shade		=>		PolyHgt		Shape			also lower-left X/Y
//
//		return value:	>= 0 : 0-based object index of newly created PolyLp
//							  -1 : Area not > 0
//							  -2 : Azimuth not in range 0-360
//							  -3 : Tilt not in range 0-180
//							  -4 : PolyType not recognized
//							  -5 : Error creating PolyLp object
//							  -6 : Error retrieving index of newly created PolyLp
//							  -7 : Error creating CartesianPt object
//							  -8 : Error retrieving index of newly created CartesianPt
//							  -9 : Error setting coordinate to new CartesianPt object
//							 -11 : Wall height (Arg6) <= 0
//							 -12 : Wall height (Arg6) >= wall area
//							 -13 : Wall area (Arg7) <= 0 or < window/door area
//							 -14 : PolyLp shape (Arg7) < 0 or > 1 (0-Rectangle, 1-Octagon)
//
int BEMPX_CreatePolyLoop(	double dArea, double dAzimuth, double dTilt, double dZ, int iPolyType /*=0*/,
									double dArg6 /*=-1*/, double dArg7 /*=-1*/, int iBEMProcIdx /*=-1*/, double* pdFurthestFromXYOrig /*=NULL*/,
									double dDX /*=0*/, double dDY /*=0*/, double dDZ /*=0*/, double dChldHgt /*=-1*/, double dChldX /*=-1*/, double dChldY /*=-1*/,
									double dCentX /*=-999*/, double dCentY /*=-999*/, double dCentZ /*=-999*/ )
{	int iPolyLpObjIdx = -999;
	if (dArea <= 0)
		iPolyLpObjIdx = -1;
//	else if (dAzimuth < 0 || dAzimuth > 360)
//		iPolyLpObjIdx = -2;
	else if (dTilt < 0 || dTilt > 180)
		iPolyLpObjIdx = -3;
	else if (iPolyType < 0 || iPolyType > 5)
		iPolyLpObjIdx = -4;

	else if ((iPolyType >= 1 && iPolyType <= 5) &&  dArg6 <= 0    )						// wall, window or door => Arg6 = Wall Ht <= 0
		iPolyLpObjIdx = -11;
	else if ( iPolyType == 1                    &&  dArg6 >= dArea)						// wall, window or door => Arg6 = Wall Ht >= Wall Area
		iPolyLpObjIdx = -12;

	else if ((iPolyType >= 2 && iPolyType <= 3) && (dArg7 <= 0 || dArg7 < dArea))		// window or door => Arg7 = Parent Wall Area <= 0 or < Win/Dr Area
		iPolyLpObjIdx = -13;
	else if ((iPolyType >= 2 && iPolyType <= 3) &&  dArg7 <= dArg6)						// window or door => Arg7 = Parent Wall Ht > Wall Area
		iPolyLpObjIdx = -12;  // same error as above

	else if ((iPolyType == 4 || iPolyType == 5) && (dArg7 < 0 || dArg7 > 1))		// shape options:  0-Rectangle, 1-Octagon
		iPolyLpObjIdx = -14;

	else
	{
// ALLOW Azimuths to lie outside the range of 0-360 (as long as we are using the "fan" method to prevent exact object overlaps)
		while (dAzimuth < 0)
			dAzimuth += 360.;
		while (dAzimuth > 360)
			dAzimuth -= 360.;

		// apply default rounding to dDX/Y/Z to avoid resulting PolyLp containing higher than desired decimal precision
		RoundDbl( dDX, 1000. );   RoundDbl( dDY, 1000. );   RoundDbl( dDZ, 1000. );

		bool bPntsOK = false;
		double daPnts[4][3] = { {	0., 0., dZ },
										{	0., 0., dZ },
										{	0., 0., dZ },
										{	0., 0., dZ } };
// note: following convention in SketchUp/OpenStudio where first vertex is TOP LEFT corner of wall
		double dPolyHgt = ((iPolyType == 1 || iPolyType == 4 || iPolyType == 5) ? dArg6 : sqrt(dArea));					assert( dPolyHgt > 0 );
		if (iPolyType == 2 || iPolyType == 3)
		{	double dWallHt   = dArg6;
			double dWallArea = dArg7;
			double dWallWd   = dWallArea / dWallHt;

			if (dChldHgt > 0.01)		// SAC 1/10/15 - option to 
				dPolyHgt = dChldHgt;
			else if (WithinMargin( dArea, dWallArea, 0.1 ))	// win/door ht = wall height if equal areas
				dPolyHgt = dWallHt;
			else if (iPolyType == 2)
			{		// WINDOW
				if (dWallHt <= 10 && dPolyHgt > 4 && (dArea / 5.0) < dWallWd)			// try 5' window for wall <= 10' tall
					dPolyHgt = 5.0;
				else if (dWallHt <= 12 && dPolyHgt > 6 && (dArea / 8.0) < dWallWd)	// try 8' window for wall <= 12' tall
					dPolyHgt = 8.0;
			}
			else	// DOOR
			{	if (dWallHt <= 8.5 && dPolyHgt > 4 && dPolyHgt < 8.5 && (dArea / 6.5) < dWallWd)  			// try 6'6" door for wall <= 8'6" tall
					dPolyHgt = 6.5;
				else if (dWallHt <= 10 && dPolyHgt > 4.5 && dPolyHgt < 9.5 && (dArea / 7.0) < dWallWd)		// try 7' door for wall <= 10' tall
					dPolyHgt = 7.0;
			}
		// SAC 6/2/15 - new if statement to prevent win/door exceeding parent wall height
			if (dPolyHgt > dWallHt)
				dPolyHgt = dWallHt;
			if ((dArea / dPolyHgt) >= dWallWd)		// make sure win/door wd (= sqrt( door area )) not too wide for wall
				dPolyHgt = dArea * dWallHt / dWallArea;	// else use same aspect ration for door as wall
		}

		double dPolyLen = dArea / dPolyHgt;
		double dSeg1Ang = (180. - dAzimuth + (dAzimuth > 180. ? 360. : 0.)) * sdPi / 180.;
		if (dChldX >= 0 && dChldY >= 0)
		{	assert( iPolyType == 2 || iPolyType == 3 );		// SAC 1/10/15 - adjust first vertex and all Z coord.s based on window/door X/Y
			daPnts[0][0] = RoundDbl( ( dChldX * cos( dSeg1Ang ) ), 1000. );	// minor rounding to prevent excessive decimal precision (and 0.0 weirdness)
			daPnts[0][1] = RoundDbl( ( dChldX * sin( dSeg1Ang ) ), 1000. );
			if (WithinMargin( dTilt, 90., 0.001 ))		// VERTICAL
				daPnts[0][2] += dChldY;
			else
			{	double dHorizLen = dChldY * cos( (sdPi * dTilt / 180.) );
				double dSeg2Ang  = dSeg1Ang + sdHalfPi - (dSeg1Ang > sd3HalfPi ? sd2Pi : 0.);
				daPnts[0][0] = RoundDbl( (daPnts[0][0] + (dHorizLen * cos(  dSeg2Ang             ))), 1000. );
				daPnts[0][1] = RoundDbl( (daPnts[0][1] + (dHorizLen * sin(  dSeg2Ang             ))), 1000. );
				daPnts[0][2] = RoundDbl( (daPnts[0][2] + (dChldY    * sin( (sdPi * dTilt / 180.) ))), 1000. );
			}
			daPnts[1][2] = daPnts[2][2] = daPnts[3][2] = daPnts[0][2];
		}

		daPnts[1][0] = RoundDbl( (daPnts[0][0] + ( dPolyLen * cos( dSeg1Ang ) )), 1000. );	// minor rounding to prevent excessive decimal precision (and 0.0 weirdness)
		daPnts[1][1] = RoundDbl( (daPnts[0][1] + ( dPolyLen * sin( dSeg1Ang ) )), 1000. );
		if (WithinMargin( dTilt, 90., 0.001 ))		// VERTICAL
		{	daPnts[2][0]  = daPnts[1][0];
			daPnts[2][1]  = daPnts[1][1];
			daPnts[2][2] += dPolyHgt;
			daPnts[3][0]  = daPnts[0][0];
			daPnts[3][1]  = daPnts[0][1];
			daPnts[3][2]  = daPnts[2][2];
			bPntsOK = true;
		}
		else
		{	double dHorizLen = dPolyHgt * cos( (sdPi * dTilt / 180.) );
			double dSeg2Ang  = dSeg1Ang + sdHalfPi - (dSeg1Ang > sd3HalfPi ? sd2Pi : 0.);
			daPnts[2][0] = RoundDbl( (daPnts[1][0] + (dHorizLen * cos(  dSeg2Ang             ))), 1000. );
			daPnts[2][1] = RoundDbl( (daPnts[1][1] + (dHorizLen * sin(  dSeg2Ang             ))), 1000. );
			daPnts[2][2] = RoundDbl( (daPnts[1][2] + (dPolyHgt  * sin( (sdPi * dTilt / 180.) ))), 1000. );
			daPnts[3][0] = RoundDbl( (daPnts[0][0] + (dHorizLen * cos(  dSeg2Ang             ))), 1000. );
			daPnts[3][1] = RoundDbl( (daPnts[0][1] + (dHorizLen * sin(  dSeg2Ang             ))), 1000. );
			daPnts[3][2] = daPnts[2][2];
			bPntsOK = true;
		}

		if (bPntsOK && pdFurthestFromXYOrig)	// SAC 1/7/15
		{	for (int iPt=0; iPt<4; iPt++)
				*pdFurthestFromXYOrig = std::max( *pdFurthestFromXYOrig, sqrt( ((daPnts[iPt][0]+dDX)*(daPnts[iPt][0]+dDX)) + ((daPnts[iPt][1]+dDY)*(daPnts[iPt][1]+dDY)) ) );
		}

		if (bPntsOK && dCentX != -999 && dCentY != -999 && dCentZ != -999)	// SAC 3/1/17
		{	double dPtMin[3] = { 9999.0, 9999.0, 9999.0 };		double dPtMax[3] = { -9999.0, -9999.0, -9999.0 };
			double dOrigCent[3] = { 0.0, 0.0, 0.0 };		int iPt;
			// calculate current poly centroid
			for (iPt=0; iPt<4; iPt++)
			{	dPtMin[0] = std::min( dPtMin[0], daPnts[iPt][0] );		dPtMin[1] = std::min( dPtMin[1], daPnts[iPt][1] );		dPtMin[2] = std::min( dPtMin[2], daPnts[iPt][2] );
				dPtMax[0] = std::max( dPtMax[0], daPnts[iPt][0] );		dPtMax[1] = std::max( dPtMax[1], daPnts[iPt][1] );		dPtMax[2] = std::max( dPtMax[2], daPnts[iPt][2] );
			}
			// set adjustment to poly points
				dOrigCent[0] = dCentX - ((dPtMin[0]+dPtMax[0])/2.0);	dOrigCent[1] = dCentY - ((dPtMin[1]+dPtMax[1])/2.0);	dOrigCent[2] = dCentZ - ((dPtMin[2]+dPtMax[2])/2.0);
			// adjust all points to shift poly to specified centroid
			for (iPt=0; iPt<4; iPt++)
			{	daPnts[iPt][0] += RoundDbl( dOrigCent[0], 1000. );		daPnts[iPt][1] += RoundDbl( dOrigCent[1], 1000. );		daPnts[iPt][2] += RoundDbl( dOrigCent[2], 1000. );
			}
		}

		if (bPntsOK)
		{	// CREATE PolyLp
			BEMObject* pPolyLpObj = BEMPX_CreateObject( ruleSet.getGeomIDs()->m_iOID_PolyLp, NULL /*lpszName*/, NULL /*pParent*/,
																		BEMO_User /*objType*/, false /*bDefaultParent*/, true /*bAutoCreate*/, iBEMProcIdx );
			if (pPolyLpObj == NULL || pPolyLpObj->getClass() == NULL)
			{	assert( FALSE );
				iPolyLpObjIdx = -5;
			}
			else
			{	iPolyLpObjIdx = BEMPX_GetObjectIndex( pPolyLpObj->getClass(), pPolyLpObj, iBEMProcIdx );
				if (iPolyLpObjIdx < 0)
				{	assert( FALSE );
					iPolyLpObjIdx = -6;
				}
				else
				{	for (int iP=0; (iPolyLpObjIdx >= 0 && iP < 4); iP++)
					{	BEMObject* pCartPtObj = BEMPX_CreateObject( ruleSet.getGeomIDs()->m_iOID_CartesianPt, NULL /*lpszName*/, pPolyLpObj /*pParent*/,
																					BEMO_User /*objType*/, false /*bDefaultParent*/, true /*bAutoCreate*/, iBEMProcIdx );
						if (pCartPtObj == NULL || pCartPtObj->getClass() == NULL)
						{	assert( FALSE );
							iPolyLpObjIdx = -7;
						}
						else
						{	int iCartPtObjIdx = BEMPX_GetObjectIndex( pCartPtObj->getClass(), pCartPtObj, iBEMProcIdx );
							if (iCartPtObjIdx < 0)
							{	assert( FALSE );
								iPolyLpObjIdx = -8;
							}
							else
							{	for (int iC=0; (iPolyLpObjIdx >= 0 && iC < 3); iC++)
								{	double fC = (daPnts[iP][iC] + (iC==0 ? dDX : (iC==1 ? dDY : dDZ)));
									if (BEMPX_SetBEMData( ruleSet.getGeomIDs()->m_lDBID_CartesianPt_Coord + iC, BEMP_Flt, (void*) &fC, BEMO_User, iCartPtObjIdx ) < 0)
									{	assert( FALSE );
										iPolyLpObjIdx = -9;		// Error setting coordinate to new CartesianPt object
									}
								}
						}	}
					}
		}	}	}
	}
	return iPolyLpObjIdx;
}
