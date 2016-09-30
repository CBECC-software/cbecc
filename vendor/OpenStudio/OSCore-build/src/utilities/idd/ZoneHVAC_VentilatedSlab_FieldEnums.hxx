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

#ifndef UTILITIES_IDD_ZONEHVAC_VENTILATEDSLAB_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_VENTILATEDSLAB_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_VentilatedSlabFields
 *  \brief Enumeration of ZoneHVAC:VentilatedSlab's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_VentilatedSlabFields, )
#else
class ZoneHVAC_VentilatedSlabFields: public ::EnumBase<ZoneHVAC_VentilatedSlabFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, SurfaceNameorRadiantSurfaceGroupName, MaximumAirFlowRate, OutdoorAirControlType, MinimumOutdoorAirFlowRate, MinimumOutdoorAirScheduleName, MaximumOutdoorAirFlowRate, MaximumOutdoorAirFractionorTemperatureScheduleName, SystemConfigurationType, HollowCoreInsideDiameter, HollowCoreLength, NumberofCores, TemperatureControlType, HeatingHighAirTemperatureScheduleName, HeatingLowAirTemperatureScheduleName, HeatingHighControlTemperatureScheduleName, HeatingLowControlTemperatureScheduleName, CoolingHighAirTemperatureScheduleName, CoolingLowAirTemperatureScheduleName, CoolingHighControlTemperatureScheduleName, CoolingLowControlTemperatureScheduleName, ReturnAirNodeName, SlabInNodeName, ZoneSupplyAirNodeName, OutdoorAirNodeName, ReliefAirNodeName, OutdoorAirMixerOutletNodeName, FanOutletNodeName, FanName, CoilOptionType, HeatingCoilObjectType, HeatingCoilName, HotWaterorSteamInletNodeName, CoolingCoilObjectType, CoolingCoilName, ColdWaterInletNodeName, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName,   };
  ZoneHVAC_VentilatedSlabFields()
   : EnumBase<ZoneHVAC_VentilatedSlabFields>(Name) {} 
  ZoneHVAC_VentilatedSlabFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_VentilatedSlabFields>(t_name) {} 
  ZoneHVAC_VentilatedSlabFields(int t_value) 
   : EnumBase<ZoneHVAC_VentilatedSlabFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_VentilatedSlabFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_VentilatedSlabFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_VentilatedSlabFields>;
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
{ ZoneHVAC_VentilatedSlabFields::Name, "Name", "Name"},
{ ZoneHVAC_VentilatedSlabFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneHVAC_VentilatedSlabFields::SurfaceNameorRadiantSurfaceGroupName, "SurfaceNameorRadiantSurfaceGroupName", "Surface Name or Radiant Surface Group Name"},
{ ZoneHVAC_VentilatedSlabFields::MaximumAirFlowRate, "MaximumAirFlowRate", "Maximum Air Flow Rate"},
{ ZoneHVAC_VentilatedSlabFields::OutdoorAirControlType, "OutdoorAirControlType", "Outdoor Air Control Type"},
{ ZoneHVAC_VentilatedSlabFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ ZoneHVAC_VentilatedSlabFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ ZoneHVAC_VentilatedSlabFields::MaximumOutdoorAirFractionorTemperatureScheduleName, "MaximumOutdoorAirFractionorTemperatureScheduleName", "Maximum Outdoor Air Fraction or Temperature Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::SystemConfigurationType, "SystemConfigurationType", "System Configuration Type"},
{ ZoneHVAC_VentilatedSlabFields::HollowCoreInsideDiameter, "HollowCoreInsideDiameter", "Hollow Core Inside Diameter"},
{ ZoneHVAC_VentilatedSlabFields::HollowCoreLength, "HollowCoreLength", "Hollow Core Length"},
{ ZoneHVAC_VentilatedSlabFields::NumberofCores, "NumberofCores", "Number of Cores"},
{ ZoneHVAC_VentilatedSlabFields::TemperatureControlType, "TemperatureControlType", "Temperature Control Type"},
{ ZoneHVAC_VentilatedSlabFields::HeatingHighAirTemperatureScheduleName, "HeatingHighAirTemperatureScheduleName", "Heating High Air Temperature Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::HeatingLowAirTemperatureScheduleName, "HeatingLowAirTemperatureScheduleName", "Heating Low Air Temperature Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::HeatingHighControlTemperatureScheduleName, "HeatingHighControlTemperatureScheduleName", "Heating High Control Temperature Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::HeatingLowControlTemperatureScheduleName, "HeatingLowControlTemperatureScheduleName", "Heating Low Control Temperature Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::CoolingHighAirTemperatureScheduleName, "CoolingHighAirTemperatureScheduleName", "Cooling High Air Temperature Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::CoolingLowAirTemperatureScheduleName, "CoolingLowAirTemperatureScheduleName", "Cooling Low Air Temperature Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::CoolingHighControlTemperatureScheduleName, "CoolingHighControlTemperatureScheduleName", "Cooling High Control Temperature Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::CoolingLowControlTemperatureScheduleName, "CoolingLowControlTemperatureScheduleName", "Cooling Low Control Temperature Schedule Name"},
{ ZoneHVAC_VentilatedSlabFields::ReturnAirNodeName, "ReturnAirNodeName", "Return Air Node Name"},
{ ZoneHVAC_VentilatedSlabFields::SlabInNodeName, "SlabInNodeName", "Slab In Node Name"},
{ ZoneHVAC_VentilatedSlabFields::ZoneSupplyAirNodeName, "ZoneSupplyAirNodeName", "Zone Supply Air Node Name"},
{ ZoneHVAC_VentilatedSlabFields::OutdoorAirNodeName, "OutdoorAirNodeName", "Outdoor Air Node Name"},
{ ZoneHVAC_VentilatedSlabFields::ReliefAirNodeName, "ReliefAirNodeName", "Relief Air Node Name"},
{ ZoneHVAC_VentilatedSlabFields::OutdoorAirMixerOutletNodeName, "OutdoorAirMixerOutletNodeName", "Outdoor Air Mixer Outlet Node Name"},
{ ZoneHVAC_VentilatedSlabFields::FanOutletNodeName, "FanOutletNodeName", "Fan Outlet Node Name"},
{ ZoneHVAC_VentilatedSlabFields::FanName, "FanName", "Fan Name"},
{ ZoneHVAC_VentilatedSlabFields::CoilOptionType, "CoilOptionType", "Coil Option Type"},
{ ZoneHVAC_VentilatedSlabFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ ZoneHVAC_VentilatedSlabFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ ZoneHVAC_VentilatedSlabFields::HotWaterorSteamInletNodeName, "HotWaterorSteamInletNodeName", "Hot Water or Steam Inlet Node Name"},
{ ZoneHVAC_VentilatedSlabFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ ZoneHVAC_VentilatedSlabFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ ZoneHVAC_VentilatedSlabFields::ColdWaterInletNodeName, "ColdWaterInletNodeName", "Cold Water Inlet Node Name"},
{ ZoneHVAC_VentilatedSlabFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_VentilatedSlabFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_VentilatedSlabFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_VentilatedSlabFields> OptionalZoneHVAC_VentilatedSlabFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_VENTILATEDSLAB_FIELDENUMS_HXX
