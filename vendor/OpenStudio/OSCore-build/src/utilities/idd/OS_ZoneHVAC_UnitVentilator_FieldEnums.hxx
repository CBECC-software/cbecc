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

#ifndef UTILITIES_IDD_OS_ZONEHVAC_UNITVENTILATOR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEHVAC_UNITVENTILATOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneHVAC_UnitVentilatorFields
 *  \brief Enumeration of OS:ZoneHVAC:UnitVentilator's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneHVAC_UnitVentilatorFields, )
#else
class OS_ZoneHVAC_UnitVentilatorFields: public ::EnumBase<OS_ZoneHVAC_UnitVentilatorFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, MaximumSupplyAirFlowRate, OutdoorAirControlType, MinimumOutdoorAirFlowRate, MinimumOutdoorAirScheduleName, MaximumOutdoorAirFlowRate, MaximumOutdoorAirFractionorTemperatureScheduleName, AirInletNodeName, AirOutletNodeName, SupplyAirFanName, SupplyAirFanOperatingModeScheduleName, HeatingCoilName, HeatingConvergenceTolerance, CoolingCoilName, CoolingConvergenceTolerance, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName,   };
  OS_ZoneHVAC_UnitVentilatorFields()
   : EnumBase<OS_ZoneHVAC_UnitVentilatorFields>(Handle) {} 
  OS_ZoneHVAC_UnitVentilatorFields(const std::string &t_name) 
   : EnumBase<OS_ZoneHVAC_UnitVentilatorFields>(t_name) {} 
  OS_ZoneHVAC_UnitVentilatorFields(int t_value) 
   : EnumBase<OS_ZoneHVAC_UnitVentilatorFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneHVAC_UnitVentilatorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneHVAC_UnitVentilatorFields>::value()); }
   private:
    friend class EnumBase<OS_ZoneHVAC_UnitVentilatorFields>;
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
{ OS_ZoneHVAC_UnitVentilatorFields::Handle, "Handle", "Handle"},
{ OS_ZoneHVAC_UnitVentilatorFields::Name, "Name", "Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, "MaximumSupplyAirFlowRate", "Maximum Supply Air Flow Rate"},
{ OS_ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType, "OutdoorAirControlType", "Outdoor Air Control Type"},
{ OS_ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ OS_ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ OS_ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFractionorTemperatureScheduleName, "MaximumOutdoorAirFractionorTemperatureScheduleName", "Maximum Outdoor Air Fraction or Temperature Schedule Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::HeatingConvergenceTolerance, "HeatingConvergenceTolerance", "Heating Convergence Tolerance"},
{ OS_ZoneHVAC_UnitVentilatorFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::CoolingConvergenceTolerance, "CoolingConvergenceTolerance", "Cooling Convergence Tolerance"},
{ OS_ZoneHVAC_UnitVentilatorFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ OS_ZoneHVAC_UnitVentilatorFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneHVAC_UnitVentilatorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneHVAC_UnitVentilatorFields> OptionalOS_ZoneHVAC_UnitVentilatorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEHVAC_UNITVENTILATOR_FIELDENUMS_HXX
