/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_OS_REFRIGERATION_WALKIN_ZONEBOUNDARY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_REFRIGERATION_WALKIN_ZONEBOUNDARY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Refrigeration_WalkIn_ZoneBoundaryFields
 *  \brief Enumeration of OS:Refrigeration:WalkIn:ZoneBoundary's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Refrigeration_WalkIn_ZoneBoundaryFields, )
#else
class OS_Refrigeration_WalkIn_ZoneBoundaryFields: public ::EnumBase<OS_Refrigeration_WalkIn_ZoneBoundaryFields> {
 public: 
  enum domain 
  {
Handle, Name, ZoneName, TotalInsulatedSurfaceAreaFacingZone, InsulatedSurfaceUValueFacingZone, AreaofGlassReachInDoorsFacingZone, HeightofGlassReachInDoorsFacingZone, GlassReachInDoorUValueFacingZone, GlassReachInDoorOpeningScheduleNameFacingZone, AreaofStockingDoorsFacingZone, HeightofStockingDoorsFacingZone, StockingDoorUValueFacingZone, StockingDoorOpeningScheduleNameFacingZone, StockingDoorOpeningProtectionTypeFacingZone,   };
  OS_Refrigeration_WalkIn_ZoneBoundaryFields()
   : EnumBase<OS_Refrigeration_WalkIn_ZoneBoundaryFields>(Handle) {} 
  OS_Refrigeration_WalkIn_ZoneBoundaryFields(const std::string &t_name) 
   : EnumBase<OS_Refrigeration_WalkIn_ZoneBoundaryFields>(t_name) {} 
  OS_Refrigeration_WalkIn_ZoneBoundaryFields(int t_value) 
   : EnumBase<OS_Refrigeration_WalkIn_ZoneBoundaryFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Refrigeration_WalkIn_ZoneBoundaryFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Refrigeration_WalkIn_ZoneBoundaryFields>::value()); }
   private:
    friend class EnumBase<OS_Refrigeration_WalkIn_ZoneBoundaryFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::Handle, "Handle", "Handle"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::Name, "Name", "Name"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::ZoneName, "ZoneName", "Zone Name"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::TotalInsulatedSurfaceAreaFacingZone, "TotalInsulatedSurfaceAreaFacingZone", "Total Insulated Surface Area Facing Zone"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::InsulatedSurfaceUValueFacingZone, "InsulatedSurfaceUValueFacingZone", "Insulated Surface U-Value Facing Zone"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::AreaofGlassReachInDoorsFacingZone, "AreaofGlassReachInDoorsFacingZone", "Area of Glass Reach In Doors Facing Zone"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::HeightofGlassReachInDoorsFacingZone, "HeightofGlassReachInDoorsFacingZone", "Height of Glass Reach In Doors Facing Zone"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::GlassReachInDoorUValueFacingZone, "GlassReachInDoorUValueFacingZone", "Glass Reach In Door U Value Facing Zone"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::GlassReachInDoorOpeningScheduleNameFacingZone, "GlassReachInDoorOpeningScheduleNameFacingZone", "Glass Reach In Door Opening Schedule Name Facing Zone"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::AreaofStockingDoorsFacingZone, "AreaofStockingDoorsFacingZone", "Area of Stocking Doors Facing Zone"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::HeightofStockingDoorsFacingZone, "HeightofStockingDoorsFacingZone", "Height of Stocking Doors Facing Zone"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::StockingDoorUValueFacingZone, "StockingDoorUValueFacingZone", "Stocking Door U Value Facing Zone"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::StockingDoorOpeningScheduleNameFacingZone, "StockingDoorOpeningScheduleNameFacingZone", "Stocking Door Opening Schedule Name Facing Zone"},
{ OS_Refrigeration_WalkIn_ZoneBoundaryFields::StockingDoorOpeningProtectionTypeFacingZone, "StockingDoorOpeningProtectionTypeFacingZone", "Stocking Door Opening Protection Type Facing Zone"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const OS_Refrigeration_WalkIn_ZoneBoundaryFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Refrigeration_WalkIn_ZoneBoundaryFields> OptionalOS_Refrigeration_WalkIn_ZoneBoundaryFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_REFRIGERATION_WALKIN_ZONEBOUNDARY_FIELDENUMS_HXX
