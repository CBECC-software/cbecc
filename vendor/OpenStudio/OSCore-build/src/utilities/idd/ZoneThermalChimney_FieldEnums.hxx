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

#ifndef UTILITIES_IDD_ZONETHERMALCHIMNEY_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONETHERMALCHIMNEY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneThermalChimneyFields
 *  \brief Enumeration of ZoneThermalChimney's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneThermalChimneyFields, )
#else
class ZoneThermalChimneyFields: public ::EnumBase<ZoneThermalChimneyFields> {
 public: 
  enum domain 
  {
Name, ZoneName, AvailabilityScheduleName, WidthoftheAbsorberWall, CrossSectionalAreaofAirChannelOutlet, DischargeCoefficient,   };
  ZoneThermalChimneyFields()
   : EnumBase<ZoneThermalChimneyFields>(Name) {} 
  ZoneThermalChimneyFields(const std::string &t_name) 
   : EnumBase<ZoneThermalChimneyFields>(t_name) {} 
  ZoneThermalChimneyFields(int t_value) 
   : EnumBase<ZoneThermalChimneyFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneThermalChimneyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneThermalChimneyFields>::value()); }
   private:
    friend class EnumBase<ZoneThermalChimneyFields>;
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
{ ZoneThermalChimneyFields::Name, "Name", "Name"},
{ ZoneThermalChimneyFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneThermalChimneyFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneThermalChimneyFields::WidthoftheAbsorberWall, "WidthoftheAbsorberWall", "Width of the Absorber Wall"},
{ ZoneThermalChimneyFields::CrossSectionalAreaofAirChannelOutlet, "CrossSectionalAreaofAirChannelOutlet", "Cross Sectional Area of Air Channel Outlet"},
{ ZoneThermalChimneyFields::DischargeCoefficient, "DischargeCoefficient", "Discharge Coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneThermalChimneyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneThermalChimneyFields> OptionalZoneThermalChimneyFields ;
#endif

/** \class ZoneThermalChimneyExtensibleFields
 *  \brief Enumeration of ZoneThermalChimney's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneThermalChimneyExtensibleFields, )
#else
class ZoneThermalChimneyExtensibleFields: public ::EnumBase<ZoneThermalChimneyExtensibleFields> {
 public: 
  enum domain 
  {
ZoneName, DistancefromTopofThermalChimneytoInlet, RelativeRatiosofAirFlowRatesPassingthroughZone, CrossSectionalAreasofAirChannelInlet,   };
  ZoneThermalChimneyExtensibleFields()
   : EnumBase<ZoneThermalChimneyExtensibleFields>(ZoneName) {} 
  ZoneThermalChimneyExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneThermalChimneyExtensibleFields>(t_name) {} 
  ZoneThermalChimneyExtensibleFields(int t_value) 
   : EnumBase<ZoneThermalChimneyExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneThermalChimneyExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneThermalChimneyExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneThermalChimneyExtensibleFields>;
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
{ ZoneThermalChimneyExtensibleFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneThermalChimneyExtensibleFields::DistancefromTopofThermalChimneytoInlet, "DistancefromTopofThermalChimneytoInlet", "Distance from Top of Thermal Chimney to Inlet"},
{ ZoneThermalChimneyExtensibleFields::RelativeRatiosofAirFlowRatesPassingthroughZone, "RelativeRatiosofAirFlowRatesPassingthroughZone", "Relative Ratios of Air Flow Rates Passing through Zone"},
{ ZoneThermalChimneyExtensibleFields::CrossSectionalAreasofAirChannelInlet, "CrossSectionalAreasofAirChannelInlet", "Cross Sectional Areas of Air Channel Inlet"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneThermalChimneyExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneThermalChimneyExtensibleFields> OptionalZoneThermalChimneyExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONETHERMALCHIMNEY_FIELDENUMS_HXX
