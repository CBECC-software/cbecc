/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_HVACTEMPLATE_ZONE_PTHP_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_ZONE_PTHP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Zone_PTHPFields
 *  \brief Enumeration of HVACTemplate:Zone:PTHP's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Zone_PTHPFields, )
#else
class HVACTemplate_Zone_PTHPFields: public ::EnumBase<HVACTemplate_Zone_PTHPFields> {
 public: 
  enum domain 
  {
ZoneName, TemplateThermostatName, CoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoLoadSupplyAirFlowRate, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, OutdoorAirMethod, OutdoorAirFlowRateperPerson, OutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZone, SystemAvailabilityScheduleName, SupplyFanOperatingModeScheduleName, SupplyFanPlacement, SupplyFanTotalEfficiency, SupplyFanDeltaPressure, SupplyFanMotorEfficiency, CoolingCoilType, CoolingCoilAvailabilityScheduleName, CoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedCOP, HeatPumpHeatingCoilType, HeatPumpHeatingCoilAvailabilityScheduleName, HeatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilGrossRatedCOP, HeatPumpHeatingMinimumOutdoorDryBulbTemperature, HeatPumpDefrostMaximumOutdoorDryBulbTemperature, HeatPumpDefrostStrategy, HeatPumpDefrostControl, HeatPumpDefrostTimePeriodFraction, SupplementalHeatingCoilType, SupplementalHeatingCoilAvailabilityScheduleName, SupplementalHeatingCoilCapacity, SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature, SupplementalGasHeatingCoilEfficiency, SupplementalGasHeatingCoilParasiticElectricLoad, DedicatedOutdoorAirSystemName, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperatureDifference, DesignSpecificationOutdoorAirObjectName, DesignSpecificationZoneAirDistributionObjectName, BaseboardHeatingType, BaseboardHeatingAvailabilityScheduleName, BaseboardHeatingCapacity, CapacityControlMethod,   };
  HVACTemplate_Zone_PTHPFields()
   : EnumBase<HVACTemplate_Zone_PTHPFields>(ZoneName) {} 
  HVACTemplate_Zone_PTHPFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Zone_PTHPFields>(t_name) {} 
  HVACTemplate_Zone_PTHPFields(int t_value) 
   : EnumBase<HVACTemplate_Zone_PTHPFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Zone_PTHPFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Zone_PTHPFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Zone_PTHPFields>;
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
{ HVACTemplate_Zone_PTHPFields::ZoneName, "ZoneName", "Zone Name"},
{ HVACTemplate_Zone_PTHPFields::TemplateThermostatName, "TemplateThermostatName", "Template Thermostat Name"},
{ HVACTemplate_Zone_PTHPFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ HVACTemplate_Zone_PTHPFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ HVACTemplate_Zone_PTHPFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ HVACTemplate_Zone_PTHPFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ HVACTemplate_Zone_PTHPFields::ZoneCoolingSizingFactor, "ZoneCoolingSizingFactor", "Zone Cooling Sizing Factor"},
{ HVACTemplate_Zone_PTHPFields::OutdoorAirMethod, "OutdoorAirMethod", "Outdoor Air Method"},
{ HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperPerson, "OutdoorAirFlowRateperPerson", "Outdoor Air Flow Rate per Person"},
{ HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperZoneFloorArea, "OutdoorAirFlowRateperZoneFloorArea", "Outdoor Air Flow Rate per Zone Floor Area"},
{ HVACTemplate_Zone_PTHPFields::OutdoorAirFlowRateperZone, "OutdoorAirFlowRateperZone", "Outdoor Air Flow Rate per Zone"},
{ HVACTemplate_Zone_PTHPFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_Zone_PTHPFields::SupplyFanOperatingModeScheduleName, "SupplyFanOperatingModeScheduleName", "Supply Fan Operating Mode Schedule Name"},
{ HVACTemplate_Zone_PTHPFields::SupplyFanPlacement, "SupplyFanPlacement", "Supply Fan Placement"},
{ HVACTemplate_Zone_PTHPFields::SupplyFanTotalEfficiency, "SupplyFanTotalEfficiency", "Supply Fan Total Efficiency"},
{ HVACTemplate_Zone_PTHPFields::SupplyFanDeltaPressure, "SupplyFanDeltaPressure", "Supply Fan Delta Pressure"},
{ HVACTemplate_Zone_PTHPFields::SupplyFanMotorEfficiency, "SupplyFanMotorEfficiency", "Supply Fan Motor Efficiency"},
{ HVACTemplate_Zone_PTHPFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_Zone_PTHPFields::CoolingCoilAvailabilityScheduleName, "CoolingCoilAvailabilityScheduleName", "Cooling Coil Availability Schedule Name"},
{ HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedTotalCapacity, "CoolingCoilGrossRatedTotalCapacity", "Cooling Coil Gross Rated Total Capacity"},
{ HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedSensibleHeatRatio, "CoolingCoilGrossRatedSensibleHeatRatio", "Cooling Coil Gross Rated Sensible Heat Ratio"},
{ HVACTemplate_Zone_PTHPFields::CoolingCoilGrossRatedCOP, "CoolingCoilGrossRatedCOP", "Cooling Coil Gross Rated COP"},
{ HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilType, "HeatPumpHeatingCoilType", "Heat Pump Heating Coil Type"},
{ HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilAvailabilityScheduleName, "HeatPumpHeatingCoilAvailabilityScheduleName", "Heat Pump Heating Coil Availability Schedule Name"},
{ HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCapacity, "HeatPumpHeatingCoilGrossRatedCapacity", "Heat Pump Heating Coil Gross Rated Capacity"},
{ HVACTemplate_Zone_PTHPFields::HeatPumpHeatingCoilGrossRatedCOP, "HeatPumpHeatingCoilGrossRatedCOP", "Heat Pump Heating Coil Gross Rated COP"},
{ HVACTemplate_Zone_PTHPFields::HeatPumpHeatingMinimumOutdoorDryBulbTemperature, "HeatPumpHeatingMinimumOutdoorDryBulbTemperature", "Heat Pump Heating Minimum Outdoor Dry-Bulb Temperature"},
{ HVACTemplate_Zone_PTHPFields::HeatPumpDefrostMaximumOutdoorDryBulbTemperature, "HeatPumpDefrostMaximumOutdoorDryBulbTemperature", "Heat Pump Defrost Maximum Outdoor Dry-Bulb Temperature"},
{ HVACTemplate_Zone_PTHPFields::HeatPumpDefrostStrategy, "HeatPumpDefrostStrategy", "Heat Pump Defrost Strategy"},
{ HVACTemplate_Zone_PTHPFields::HeatPumpDefrostControl, "HeatPumpDefrostControl", "Heat Pump Defrost Control"},
{ HVACTemplate_Zone_PTHPFields::HeatPumpDefrostTimePeriodFraction, "HeatPumpDefrostTimePeriodFraction", "Heat Pump Defrost Time Period Fraction"},
{ HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilType, "SupplementalHeatingCoilType", "Supplemental Heating Coil Type"},
{ HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilAvailabilityScheduleName, "SupplementalHeatingCoilAvailabilityScheduleName", "Supplemental Heating Coil Availability Schedule Name"},
{ HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilCapacity, "SupplementalHeatingCoilCapacity", "Supplemental Heating Coil Capacity"},
{ HVACTemplate_Zone_PTHPFields::SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature, "SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature", "Supplemental Heating Coil Maximum Outdoor Dry-Bulb Temperature"},
{ HVACTemplate_Zone_PTHPFields::SupplementalGasHeatingCoilEfficiency, "SupplementalGasHeatingCoilEfficiency", "Supplemental Gas Heating Coil Efficiency"},
{ HVACTemplate_Zone_PTHPFields::SupplementalGasHeatingCoilParasiticElectricLoad, "SupplementalGasHeatingCoilParasiticElectricLoad", "Supplemental Gas Heating Coil Parasitic Electric Load"},
{ HVACTemplate_Zone_PTHPFields::DedicatedOutdoorAirSystemName, "DedicatedOutdoorAirSystemName", "Dedicated Outdoor Air System Name"},
{ HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, "ZoneCoolingDesignSupplyAirTemperatureInputMethod", "Zone Cooling Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperature, "ZoneCoolingDesignSupplyAirTemperature", "Zone Cooling Design Supply Air Temperature"},
{ HVACTemplate_Zone_PTHPFields::ZoneCoolingDesignSupplyAirTemperatureDifference, "ZoneCoolingDesignSupplyAirTemperatureDifference", "Zone Cooling Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, "ZoneHeatingDesignSupplyAirTemperatureInputMethod", "Zone Heating Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperature, "ZoneHeatingDesignSupplyAirTemperature", "Zone Heating Design Supply Air Temperature"},
{ HVACTemplate_Zone_PTHPFields::ZoneHeatingDesignSupplyAirTemperatureDifference, "ZoneHeatingDesignSupplyAirTemperatureDifference", "Zone Heating Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_PTHPFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ HVACTemplate_Zone_PTHPFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
{ HVACTemplate_Zone_PTHPFields::BaseboardHeatingType, "BaseboardHeatingType", "Baseboard Heating Type"},
{ HVACTemplate_Zone_PTHPFields::BaseboardHeatingAvailabilityScheduleName, "BaseboardHeatingAvailabilityScheduleName", "Baseboard Heating Availability Schedule Name"},
{ HVACTemplate_Zone_PTHPFields::BaseboardHeatingCapacity, "BaseboardHeatingCapacity", "Baseboard Heating Capacity"},
{ HVACTemplate_Zone_PTHPFields::CapacityControlMethod, "CapacityControlMethod", "Capacity Control Method"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Zone_PTHPFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Zone_PTHPFields> OptionalHVACTemplate_Zone_PTHPFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_ZONE_PTHP_FIELDENUMS_HXX
