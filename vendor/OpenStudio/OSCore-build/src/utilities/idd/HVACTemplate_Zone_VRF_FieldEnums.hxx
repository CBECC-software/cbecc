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

#ifndef UTILITIES_IDD_HVACTEMPLATE_ZONE_VRF_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_ZONE_VRF_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Zone_VRFFields
 *  \brief Enumeration of HVACTemplate:Zone:VRF's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Zone_VRFFields, )
#else
class HVACTemplate_Zone_VRFFields: public ::EnumBase<HVACTemplate_Zone_VRFFields> {
 public: 
  enum domain 
  {
ZoneName, TemplateVRFSystemName, TemplateThermostatName, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, RatedTotalHeatingCapacitySizingRatio, CoolingSupplyAirFlowRate, NoCoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoHeatingSupplyAirFlowRate, CoolingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate, OutdoorAirMethod, OutdoorAirFlowRateperPerson, OutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZone, DesignSpecificationOutdoorAirObjectName, DesignSpecificationZoneAirDistributionObjectName, SystemAvailabilityScheduleName, SupplyFanOperatingModeScheduleName, SupplyAirFanplacement, SupplyFanTotalEfficiency, SupplyFanDeltaPressure, SupplyFanMotorEfficiency, CoolingCoilType, CoolingCoilAvailabilityScheduleName, CoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedSensibleHeatRatio, HeatPumpHeatingCoilType, HeatPumpHeatingCoilAvailabilityScheduleName, HeatPumpHeatingCoilGrossRatedCapacity, ZoneTerminalUnitOnParasiticElectricEnergyUse, ZoneTerminalUnitOffParasiticElectricEnergyUse, DedicatedOutdoorAirSystemName, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperatureDifference, BaseboardHeatingType, BaseboardHeatingAvailabilityScheduleName, BaseboardHeatingCapacity,   };
  HVACTemplate_Zone_VRFFields()
   : EnumBase<HVACTemplate_Zone_VRFFields>(ZoneName) {} 
  HVACTemplate_Zone_VRFFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Zone_VRFFields>(t_name) {} 
  HVACTemplate_Zone_VRFFields(int t_value) 
   : EnumBase<HVACTemplate_Zone_VRFFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Zone_VRFFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Zone_VRFFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Zone_VRFFields>;
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
{ HVACTemplate_Zone_VRFFields::ZoneName, "ZoneName", "Zone Name"},
{ HVACTemplate_Zone_VRFFields::TemplateVRFSystemName, "TemplateVRFSystemName", "Template VRF System Name"},
{ HVACTemplate_Zone_VRFFields::TemplateThermostatName, "TemplateThermostatName", "Template Thermostat Name"},
{ HVACTemplate_Zone_VRFFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ HVACTemplate_Zone_VRFFields::ZoneCoolingSizingFactor, "ZoneCoolingSizingFactor", "Zone Cooling Sizing Factor"},
{ HVACTemplate_Zone_VRFFields::RatedTotalHeatingCapacitySizingRatio, "RatedTotalHeatingCapacitySizingRatio", "Rated Total Heating Capacity Sizing Ratio"},
{ HVACTemplate_Zone_VRFFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ HVACTemplate_Zone_VRFFields::NoCoolingSupplyAirFlowRate, "NoCoolingSupplyAirFlowRate", "No Cooling Supply Air Flow Rate"},
{ HVACTemplate_Zone_VRFFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ HVACTemplate_Zone_VRFFields::NoHeatingSupplyAirFlowRate, "NoHeatingSupplyAirFlowRate", "No Heating Supply Air Flow Rate"},
{ HVACTemplate_Zone_VRFFields::CoolingOutdoorAirFlowRate, "CoolingOutdoorAirFlowRate", "Cooling Outdoor Air Flow Rate"},
{ HVACTemplate_Zone_VRFFields::HeatingOutdoorAirFlowRate, "HeatingOutdoorAirFlowRate", "Heating Outdoor Air Flow Rate"},
{ HVACTemplate_Zone_VRFFields::NoLoadOutdoorAirFlowRate, "NoLoadOutdoorAirFlowRate", "No Load Outdoor Air Flow Rate"},
{ HVACTemplate_Zone_VRFFields::OutdoorAirMethod, "OutdoorAirMethod", "Outdoor Air Method"},
{ HVACTemplate_Zone_VRFFields::OutdoorAirFlowRateperPerson, "OutdoorAirFlowRateperPerson", "Outdoor Air Flow Rate per Person"},
{ HVACTemplate_Zone_VRFFields::OutdoorAirFlowRateperZoneFloorArea, "OutdoorAirFlowRateperZoneFloorArea", "Outdoor Air Flow Rate per Zone Floor Area"},
{ HVACTemplate_Zone_VRFFields::OutdoorAirFlowRateperZone, "OutdoorAirFlowRateperZone", "Outdoor Air Flow Rate per Zone"},
{ HVACTemplate_Zone_VRFFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ HVACTemplate_Zone_VRFFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
{ HVACTemplate_Zone_VRFFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_Zone_VRFFields::SupplyFanOperatingModeScheduleName, "SupplyFanOperatingModeScheduleName", "Supply Fan Operating Mode Schedule Name"},
{ HVACTemplate_Zone_VRFFields::SupplyAirFanplacement, "SupplyAirFanplacement", "Supply Air Fan placement"},
{ HVACTemplate_Zone_VRFFields::SupplyFanTotalEfficiency, "SupplyFanTotalEfficiency", "Supply Fan Total Efficiency"},
{ HVACTemplate_Zone_VRFFields::SupplyFanDeltaPressure, "SupplyFanDeltaPressure", "Supply Fan Delta Pressure"},
{ HVACTemplate_Zone_VRFFields::SupplyFanMotorEfficiency, "SupplyFanMotorEfficiency", "Supply Fan Motor Efficiency"},
{ HVACTemplate_Zone_VRFFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_Zone_VRFFields::CoolingCoilAvailabilityScheduleName, "CoolingCoilAvailabilityScheduleName", "Cooling Coil Availability Schedule Name"},
{ HVACTemplate_Zone_VRFFields::CoolingCoilGrossRatedTotalCapacity, "CoolingCoilGrossRatedTotalCapacity", "Cooling Coil Gross Rated Total Capacity"},
{ HVACTemplate_Zone_VRFFields::CoolingCoilGrossRatedSensibleHeatRatio, "CoolingCoilGrossRatedSensibleHeatRatio", "Cooling Coil Gross Rated Sensible Heat Ratio"},
{ HVACTemplate_Zone_VRFFields::HeatPumpHeatingCoilType, "HeatPumpHeatingCoilType", "Heat Pump Heating Coil Type"},
{ HVACTemplate_Zone_VRFFields::HeatPumpHeatingCoilAvailabilityScheduleName, "HeatPumpHeatingCoilAvailabilityScheduleName", "Heat Pump Heating Coil Availability Schedule Name"},
{ HVACTemplate_Zone_VRFFields::HeatPumpHeatingCoilGrossRatedCapacity, "HeatPumpHeatingCoilGrossRatedCapacity", "Heat Pump Heating Coil Gross Rated Capacity"},
{ HVACTemplate_Zone_VRFFields::ZoneTerminalUnitOnParasiticElectricEnergyUse, "ZoneTerminalUnitOnParasiticElectricEnergyUse", "Zone Terminal Unit On Parasitic Electric Energy Use"},
{ HVACTemplate_Zone_VRFFields::ZoneTerminalUnitOffParasiticElectricEnergyUse, "ZoneTerminalUnitOffParasiticElectricEnergyUse", "Zone Terminal Unit Off Parasitic Electric Energy Use"},
{ HVACTemplate_Zone_VRFFields::DedicatedOutdoorAirSystemName, "DedicatedOutdoorAirSystemName", "Dedicated Outdoor Air System Name"},
{ HVACTemplate_Zone_VRFFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, "ZoneCoolingDesignSupplyAirTemperatureInputMethod", "Zone Cooling Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_VRFFields::ZoneCoolingDesignSupplyAirTemperature, "ZoneCoolingDesignSupplyAirTemperature", "Zone Cooling Design Supply Air Temperature"},
{ HVACTemplate_Zone_VRFFields::ZoneCoolingDesignSupplyAirTemperatureDifference, "ZoneCoolingDesignSupplyAirTemperatureDifference", "Zone Cooling Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_VRFFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, "ZoneHeatingDesignSupplyAirTemperatureInputMethod", "Zone Heating Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_VRFFields::ZoneHeatingDesignSupplyAirTemperature, "ZoneHeatingDesignSupplyAirTemperature", "Zone Heating Design Supply Air Temperature"},
{ HVACTemplate_Zone_VRFFields::ZoneHeatingDesignSupplyAirTemperatureDifference, "ZoneHeatingDesignSupplyAirTemperatureDifference", "Zone Heating Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_VRFFields::BaseboardHeatingType, "BaseboardHeatingType", "Baseboard Heating Type"},
{ HVACTemplate_Zone_VRFFields::BaseboardHeatingAvailabilityScheduleName, "BaseboardHeatingAvailabilityScheduleName", "Baseboard Heating Availability Schedule Name"},
{ HVACTemplate_Zone_VRFFields::BaseboardHeatingCapacity, "BaseboardHeatingCapacity", "Baseboard Heating Capacity"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Zone_VRFFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Zone_VRFFields> OptionalHVACTemplate_Zone_VRFFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_ZONE_VRF_FIELDENUMS_HXX
