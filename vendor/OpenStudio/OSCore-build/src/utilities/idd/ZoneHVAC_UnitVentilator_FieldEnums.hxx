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

#ifndef UTILITIES_IDD_ZONEHVAC_UNITVENTILATOR_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_UNITVENTILATOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_UnitVentilatorFields
 *  \brief Enumeration of ZoneHVAC:UnitVentilator's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_UnitVentilatorFields, )
#else
class ZoneHVAC_UnitVentilatorFields: public ::EnumBase<ZoneHVAC_UnitVentilatorFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, MaximumSupplyAirFlowRate, OutdoorAirControlType, MinimumOutdoorAirFlowRate, MinimumOutdoorAirScheduleName, MaximumOutdoorAirFlowRate, MaximumOutdoorAirFractionorTemperatureScheduleName, AirInletNodeName, AirOutletNodeName, OutdoorAirNodeName, ExhaustAirNodeName, MixedAirNodeName, SupplyAirFanObjectType, SupplyAirFanName, CoilOption, SupplyAirFanOperatingModeScheduleName, HeatingCoilObjectType, HeatingCoilName, HeatingConvergenceTolerance, CoolingCoilObjectType, CoolingCoilName, CoolingConvergenceTolerance, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName,   };
  ZoneHVAC_UnitVentilatorFields()
   : EnumBase<ZoneHVAC_UnitVentilatorFields>(Name) {} 
  ZoneHVAC_UnitVentilatorFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_UnitVentilatorFields>(t_name) {} 
  ZoneHVAC_UnitVentilatorFields(int t_value) 
   : EnumBase<ZoneHVAC_UnitVentilatorFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_UnitVentilatorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_UnitVentilatorFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_UnitVentilatorFields>;
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
{ ZoneHVAC_UnitVentilatorFields::Name, "Name", "Name"},
{ ZoneHVAC_UnitVentilatorFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, "MaximumSupplyAirFlowRate", "Maximum Supply Air Flow Rate"},
{ ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType, "OutdoorAirControlType", "Outdoor Air Control Type"},
{ ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFractionorTemperatureScheduleName, "MaximumOutdoorAirFractionorTemperatureScheduleName", "Maximum Outdoor Air Fraction or Temperature Schedule Name"},
{ ZoneHVAC_UnitVentilatorFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ ZoneHVAC_UnitVentilatorFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ ZoneHVAC_UnitVentilatorFields::OutdoorAirNodeName, "OutdoorAirNodeName", "Outdoor Air Node Name"},
{ ZoneHVAC_UnitVentilatorFields::ExhaustAirNodeName, "ExhaustAirNodeName", "Exhaust Air Node Name"},
{ ZoneHVAC_UnitVentilatorFields::MixedAirNodeName, "MixedAirNodeName", "Mixed Air Node Name"},
{ ZoneHVAC_UnitVentilatorFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_UnitVentilatorFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_UnitVentilatorFields::CoilOption, "CoilOption", "Coil Option"},
{ ZoneHVAC_UnitVentilatorFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ ZoneHVAC_UnitVentilatorFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ ZoneHVAC_UnitVentilatorFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ ZoneHVAC_UnitVentilatorFields::HeatingConvergenceTolerance, "HeatingConvergenceTolerance", "Heating Convergence Tolerance"},
{ ZoneHVAC_UnitVentilatorFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ ZoneHVAC_UnitVentilatorFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ ZoneHVAC_UnitVentilatorFields::CoolingConvergenceTolerance, "CoolingConvergenceTolerance", "Cooling Convergence Tolerance"},
{ ZoneHVAC_UnitVentilatorFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_UnitVentilatorFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_UnitVentilatorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_UnitVentilatorFields> OptionalZoneHVAC_UnitVentilatorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_UNITVENTILATOR_FIELDENUMS_HXX
