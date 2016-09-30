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

#ifndef UTILITIES_IDD_ZONEHVAC_WINDOWAIRCONDITIONER_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_WINDOWAIRCONDITIONER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_WindowAirConditionerFields
 *  \brief Enumeration of ZoneHVAC:WindowAirConditioner's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_WindowAirConditionerFields, )
#else
class ZoneHVAC_WindowAirConditionerFields: public ::EnumBase<ZoneHVAC_WindowAirConditionerFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, MaximumSupplyAirFlowRate, MaximumOutdoorAirFlowRate, AirInletNodeName, AirOutletNodeName, OutdoorAirMixerObjectType, OutdoorAirMixerName, SupplyAirFanObjectType, SupplyAirFanName, CoolingCoilObjectType, DXCoolingCoilName, SupplyAirFanOperatingModeScheduleName, FanPlacement, CoolingConvergenceTolerance, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName,   };
  ZoneHVAC_WindowAirConditionerFields()
   : EnumBase<ZoneHVAC_WindowAirConditionerFields>(Name) {} 
  ZoneHVAC_WindowAirConditionerFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_WindowAirConditionerFields>(t_name) {} 
  ZoneHVAC_WindowAirConditionerFields(int t_value) 
   : EnumBase<ZoneHVAC_WindowAirConditionerFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_WindowAirConditionerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_WindowAirConditionerFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_WindowAirConditionerFields>;
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
{ ZoneHVAC_WindowAirConditionerFields::Name, "Name", "Name"},
{ ZoneHVAC_WindowAirConditionerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_WindowAirConditionerFields::MaximumSupplyAirFlowRate, "MaximumSupplyAirFlowRate", "Maximum Supply Air Flow Rate"},
{ ZoneHVAC_WindowAirConditionerFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ ZoneHVAC_WindowAirConditionerFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ ZoneHVAC_WindowAirConditionerFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ ZoneHVAC_WindowAirConditionerFields::OutdoorAirMixerObjectType, "OutdoorAirMixerObjectType", "Outdoor Air Mixer Object Type"},
{ ZoneHVAC_WindowAirConditionerFields::OutdoorAirMixerName, "OutdoorAirMixerName", "Outdoor Air Mixer Name"},
{ ZoneHVAC_WindowAirConditionerFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_WindowAirConditionerFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_WindowAirConditionerFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ ZoneHVAC_WindowAirConditionerFields::DXCoolingCoilName, "DXCoolingCoilName", "DX Cooling Coil Name"},
{ ZoneHVAC_WindowAirConditionerFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ ZoneHVAC_WindowAirConditionerFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ ZoneHVAC_WindowAirConditionerFields::CoolingConvergenceTolerance, "CoolingConvergenceTolerance", "Cooling Convergence Tolerance"},
{ ZoneHVAC_WindowAirConditionerFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_WindowAirConditionerFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_WindowAirConditionerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_WindowAirConditionerFields> OptionalZoneHVAC_WindowAirConditionerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_WINDOWAIRCONDITIONER_FIELDENUMS_HXX
