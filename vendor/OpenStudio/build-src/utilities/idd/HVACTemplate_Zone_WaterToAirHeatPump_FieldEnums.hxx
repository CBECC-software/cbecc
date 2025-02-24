/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_HVACTEMPLATE_ZONE_WATERTOAIRHEATPUMP_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_ZONE_WATERTOAIRHEATPUMP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Zone_WaterToAirHeatPumpFields
 *  \brief Enumeration of HVACTemplate:Zone:WaterToAirHeatPump's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Zone_WaterToAirHeatPumpFields, )
#else
class HVACTemplate_Zone_WaterToAirHeatPumpFields: public ::EnumBase<HVACTemplate_Zone_WaterToAirHeatPumpFields> {
 public: 
  enum domain 
  {
ZoneName, TemplateThermostatName, CoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoLoadSupplyAirFlowRate, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, OutdoorAirMethod, OutdoorAirFlowRateperPerson, OutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZone, SystemAvailabilityScheduleName, SupplyFanOperatingModeScheduleName, SupplyFanPlacement, SupplyFanTotalEfficiency, SupplyFanDeltaPressure, SupplyFanMotorEfficiency, CoolingCoilType, CoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedCOP, HeatPumpHeatingCoilType, HeatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilGrossRatedCOP, SupplementalHeatingCoilAvailabilityScheduleName, SupplementalHeatingCoilCapacity, MaximumCyclingRate, HeatPumpTimeConstant, FractionofOnCyclePowerUse, HeatPumpFanDelayTime, DedicatedOutdoorAirSystemName, SupplementalHeatingCoilType, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperatureDifference, HeatPumpCoilWaterFlowMode, DesignSpecificationOutdoorAirObjectName, DesignSpecificationZoneAirDistributionObjectName, BaseboardHeatingType, BaseboardHeatingAvailabilityScheduleName, BaseboardHeatingCapacity,   };
  HVACTemplate_Zone_WaterToAirHeatPumpFields()
   : EnumBase<HVACTemplate_Zone_WaterToAirHeatPumpFields>(ZoneName) {} 
  HVACTemplate_Zone_WaterToAirHeatPumpFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Zone_WaterToAirHeatPumpFields>(t_name) {} 
  HVACTemplate_Zone_WaterToAirHeatPumpFields(int t_value) 
   : EnumBase<HVACTemplate_Zone_WaterToAirHeatPumpFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Zone_WaterToAirHeatPumpFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Zone_WaterToAirHeatPumpFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Zone_WaterToAirHeatPumpFields>;
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
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneName, "ZoneName", "Zone Name"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::TemplateThermostatName, "TemplateThermostatName", "Template Thermostat Name"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingSizingFactor, "ZoneCoolingSizingFactor", "Zone Cooling Sizing Factor"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirMethod, "OutdoorAirMethod", "Outdoor Air Method"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperPerson, "OutdoorAirFlowRateperPerson", "Outdoor Air Flow Rate per Person"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperZoneFloorArea, "OutdoorAirFlowRateperZoneFloorArea", "Outdoor Air Flow Rate per Zone Floor Area"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::OutdoorAirFlowRateperZone, "OutdoorAirFlowRateperZone", "Outdoor Air Flow Rate per Zone"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanOperatingModeScheduleName, "SupplyFanOperatingModeScheduleName", "Supply Fan Operating Mode Schedule Name"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanPlacement, "SupplyFanPlacement", "Supply Fan Placement"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanTotalEfficiency, "SupplyFanTotalEfficiency", "Supply Fan Total Efficiency"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanDeltaPressure, "SupplyFanDeltaPressure", "Supply Fan Delta Pressure"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplyFanMotorEfficiency, "SupplyFanMotorEfficiency", "Supply Fan Motor Efficiency"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedTotalCapacity, "CoolingCoilGrossRatedTotalCapacity", "Cooling Coil Gross Rated Total Capacity"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedSensibleHeatRatio, "CoolingCoilGrossRatedSensibleHeatRatio", "Cooling Coil Gross Rated Sensible Heat Ratio"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::CoolingCoilGrossRatedCOP, "CoolingCoilGrossRatedCOP", "Cooling Coil Gross Rated COP"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilType, "HeatPumpHeatingCoilType", "Heat Pump Heating Coil Type"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCapacity, "HeatPumpHeatingCoilGrossRatedCapacity", "Heat Pump Heating Coil Gross Rated Capacity"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpHeatingCoilGrossRatedCOP, "HeatPumpHeatingCoilGrossRatedCOP", "Heat Pump Heating Coil Gross Rated COP"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilAvailabilityScheduleName, "SupplementalHeatingCoilAvailabilityScheduleName", "Supplemental Heating Coil Availability Schedule Name"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilCapacity, "SupplementalHeatingCoilCapacity", "Supplemental Heating Coil Capacity"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::MaximumCyclingRate, "MaximumCyclingRate", "Maximum Cycling Rate"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpTimeConstant, "HeatPumpTimeConstant", "Heat Pump Time Constant"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::FractionofOnCyclePowerUse, "FractionofOnCyclePowerUse", "Fraction of On-Cycle Power Use"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpFanDelayTime, "HeatPumpFanDelayTime", "Heat Pump Fan Delay Time"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::DedicatedOutdoorAirSystemName, "DedicatedOutdoorAirSystemName", "Dedicated Outdoor Air System Name"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::SupplementalHeatingCoilType, "SupplementalHeatingCoilType", "Supplemental Heating Coil Type"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, "ZoneCoolingDesignSupplyAirTemperatureInputMethod", "Zone Cooling Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperature, "ZoneCoolingDesignSupplyAirTemperature", "Zone Cooling Design Supply Air Temperature"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneCoolingDesignSupplyAirTemperatureDifference, "ZoneCoolingDesignSupplyAirTemperatureDifference", "Zone Cooling Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, "ZoneHeatingDesignSupplyAirTemperatureInputMethod", "Zone Heating Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperature, "ZoneHeatingDesignSupplyAirTemperature", "Zone Heating Design Supply Air Temperature"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::ZoneHeatingDesignSupplyAirTemperatureDifference, "ZoneHeatingDesignSupplyAirTemperatureDifference", "Zone Heating Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, "HeatPumpCoilWaterFlowMode", "Heat Pump Coil Water Flow Mode"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingType, "BaseboardHeatingType", "Baseboard Heating Type"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingAvailabilityScheduleName, "BaseboardHeatingAvailabilityScheduleName", "Baseboard Heating Availability Schedule Name"},
{ HVACTemplate_Zone_WaterToAirHeatPumpFields::BaseboardHeatingCapacity, "BaseboardHeatingCapacity", "Baseboard Heating Capacity"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Zone_WaterToAirHeatPumpFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Zone_WaterToAirHeatPumpFields> OptionalHVACTemplate_Zone_WaterToAirHeatPumpFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_ZONE_WATERTOAIRHEATPUMP_FIELDENUMS_HXX
