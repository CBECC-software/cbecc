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

#ifndef UTILITIES_IDD_HVACTEMPLATE_SYSTEM_UNITARYSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_SYSTEM_UNITARYSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_System_UnitarySystemFields
 *  \brief Enumeration of HVACTemplate:System:UnitarySystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_System_UnitarySystemFields, )
#else
class HVACTemplate_System_UnitarySystemFields: public ::EnumBase<HVACTemplate_System_UnitarySystemFields> {
 public: 
  enum domain 
  {
Name, SystemAvailabilityScheduleName, ControlType, ControlZoneorThermostatLocationName, CoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoLoadSupplyAirFlowRate, SupplyFanOperatingModeScheduleName, SupplyFanPlacement, SupplyFanTotalEfficiency, SupplyFanDeltaPressure, SupplyFanMotorEfficiency, SupplyFanMotorinAirStreamFraction, CoolingCoilType, NumberofSpeedsforCooling, CoolingCoilAvailabilityScheduleName, CoolingDesignSupplyAirTemperature, DXCoolingCoilGrossRatedTotalCapacity, DXCoolingCoilGrossRatedSensibleHeatRatio, DXCoolingCoilGrossRatedCOP, HeatingCoilType, NumberofSpeedsorStagesforHeating, HeatingCoilAvailabilityScheduleName, HeatingDesignSupplyAirTemperature, HeatingCoilGrossRatedCapacity, GasHeatingCoilEfficiency, GasHeatingCoilParasiticElectricLoad, HeatPumpHeatingCoilGrossRatedCOP, HeatPumpHeatingMinimumOutdoorDryBulbTemperature, HeatPumpDefrostMaximumOutdoorDryBulbTemperature, HeatPumpDefrostStrategy, HeatPumpDefrostControl, HeatPumpDefrostTimePeriodFraction, SupplementalHeatingorReheatCoilType, SupplementalHeatingorReheatCoilAvailabilityScheduleName, SupplementalHeatingorReheatCoilCapacity, SupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature, SupplementalGasHeatingorReheatCoilEfficiency, SupplementalGasHeatingorReheatCoilParasiticElectricLoad, MaximumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate, MinimumOutdoorAirScheduleName, EconomizerType, EconomizerLockout, EconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitDewpointTemperature, EconomizerMinimumLimitDryBulbTemperature, SupplyPlenumName, ReturnPlenumName, HeatRecoveryType, SensibleHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness, HeatRecoveryHeatExchangerType, HeatRecoveryFrostControlType, DehumidificationControlType, DehumidificationRelativeHumiditySetpoint, DehumidificationRelativeHumiditySetpointScheduleName, HumidifierType, HumidifierAvailabilityScheduleName, HumidifierRatedCapacity, HumidifierRatedElectricPower, HumidifierControlZoneName, HumidifierRelativeHumiditySetpoint, HumidifierRelativeHumiditySetpointScheduleName, SizingOption, ReturnFan, ReturnFanTotalEfficiency, ReturnFanDeltaPressure, ReturnFanMotorEfficiency, ReturnFanMotorinAirStreamFraction,   };
  HVACTemplate_System_UnitarySystemFields()
   : EnumBase<HVACTemplate_System_UnitarySystemFields>(Name) {} 
  HVACTemplate_System_UnitarySystemFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_System_UnitarySystemFields>(t_name) {} 
  HVACTemplate_System_UnitarySystemFields(int t_value) 
   : EnumBase<HVACTemplate_System_UnitarySystemFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_System_UnitarySystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_System_UnitarySystemFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_System_UnitarySystemFields>;
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
{ HVACTemplate_System_UnitarySystemFields::Name, "Name", "Name"},
{ HVACTemplate_System_UnitarySystemFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_System_UnitarySystemFields::ControlType, "ControlType", "Control Type"},
{ HVACTemplate_System_UnitarySystemFields::ControlZoneorThermostatLocationName, "ControlZoneorThermostatLocationName", "Control Zone or Thermostat Location Name"},
{ HVACTemplate_System_UnitarySystemFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ HVACTemplate_System_UnitarySystemFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ HVACTemplate_System_UnitarySystemFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ HVACTemplate_System_UnitarySystemFields::SupplyFanOperatingModeScheduleName, "SupplyFanOperatingModeScheduleName", "Supply Fan Operating Mode Schedule Name"},
{ HVACTemplate_System_UnitarySystemFields::SupplyFanPlacement, "SupplyFanPlacement", "Supply Fan Placement"},
{ HVACTemplate_System_UnitarySystemFields::SupplyFanTotalEfficiency, "SupplyFanTotalEfficiency", "Supply Fan Total Efficiency"},
{ HVACTemplate_System_UnitarySystemFields::SupplyFanDeltaPressure, "SupplyFanDeltaPressure", "Supply Fan Delta Pressure"},
{ HVACTemplate_System_UnitarySystemFields::SupplyFanMotorEfficiency, "SupplyFanMotorEfficiency", "Supply Fan Motor Efficiency"},
{ HVACTemplate_System_UnitarySystemFields::SupplyFanMotorinAirStreamFraction, "SupplyFanMotorinAirStreamFraction", "Supply Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_UnitarySystemFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_System_UnitarySystemFields::NumberofSpeedsforCooling, "NumberofSpeedsforCooling", "Number of Speeds for Cooling"},
{ HVACTemplate_System_UnitarySystemFields::CoolingCoilAvailabilityScheduleName, "CoolingCoilAvailabilityScheduleName", "Cooling Coil Availability Schedule Name"},
{ HVACTemplate_System_UnitarySystemFields::CoolingDesignSupplyAirTemperature, "CoolingDesignSupplyAirTemperature", "Cooling Design Supply Air Temperature"},
{ HVACTemplate_System_UnitarySystemFields::DXCoolingCoilGrossRatedTotalCapacity, "DXCoolingCoilGrossRatedTotalCapacity", "DX Cooling Coil Gross Rated Total Capacity"},
{ HVACTemplate_System_UnitarySystemFields::DXCoolingCoilGrossRatedSensibleHeatRatio, "DXCoolingCoilGrossRatedSensibleHeatRatio", "DX Cooling Coil Gross Rated Sensible Heat Ratio"},
{ HVACTemplate_System_UnitarySystemFields::DXCoolingCoilGrossRatedCOP, "DXCoolingCoilGrossRatedCOP", "DX Cooling Coil Gross Rated COP"},
{ HVACTemplate_System_UnitarySystemFields::HeatingCoilType, "HeatingCoilType", "Heating Coil Type"},
{ HVACTemplate_System_UnitarySystemFields::NumberofSpeedsorStagesforHeating, "NumberofSpeedsorStagesforHeating", "Number of Speeds or Stages for Heating"},
{ HVACTemplate_System_UnitarySystemFields::HeatingCoilAvailabilityScheduleName, "HeatingCoilAvailabilityScheduleName", "Heating Coil Availability Schedule Name"},
{ HVACTemplate_System_UnitarySystemFields::HeatingDesignSupplyAirTemperature, "HeatingDesignSupplyAirTemperature", "Heating Design Supply Air Temperature"},
{ HVACTemplate_System_UnitarySystemFields::HeatingCoilGrossRatedCapacity, "HeatingCoilGrossRatedCapacity", "Heating Coil Gross Rated Capacity"},
{ HVACTemplate_System_UnitarySystemFields::GasHeatingCoilEfficiency, "GasHeatingCoilEfficiency", "Gas Heating Coil Efficiency"},
{ HVACTemplate_System_UnitarySystemFields::GasHeatingCoilParasiticElectricLoad, "GasHeatingCoilParasiticElectricLoad", "Gas Heating Coil Parasitic Electric Load"},
{ HVACTemplate_System_UnitarySystemFields::HeatPumpHeatingCoilGrossRatedCOP, "HeatPumpHeatingCoilGrossRatedCOP", "Heat Pump Heating Coil Gross Rated COP"},
{ HVACTemplate_System_UnitarySystemFields::HeatPumpHeatingMinimumOutdoorDryBulbTemperature, "HeatPumpHeatingMinimumOutdoorDryBulbTemperature", "Heat Pump Heating Minimum Outdoor Dry-Bulb Temperature"},
{ HVACTemplate_System_UnitarySystemFields::HeatPumpDefrostMaximumOutdoorDryBulbTemperature, "HeatPumpDefrostMaximumOutdoorDryBulbTemperature", "Heat Pump Defrost Maximum Outdoor Dry-Bulb Temperature"},
{ HVACTemplate_System_UnitarySystemFields::HeatPumpDefrostStrategy, "HeatPumpDefrostStrategy", "Heat Pump Defrost Strategy"},
{ HVACTemplate_System_UnitarySystemFields::HeatPumpDefrostControl, "HeatPumpDefrostControl", "Heat Pump Defrost Control"},
{ HVACTemplate_System_UnitarySystemFields::HeatPumpDefrostTimePeriodFraction, "HeatPumpDefrostTimePeriodFraction", "Heat Pump Defrost Time Period Fraction"},
{ HVACTemplate_System_UnitarySystemFields::SupplementalHeatingorReheatCoilType, "SupplementalHeatingorReheatCoilType", "Supplemental Heating or Reheat Coil Type"},
{ HVACTemplate_System_UnitarySystemFields::SupplementalHeatingorReheatCoilAvailabilityScheduleName, "SupplementalHeatingorReheatCoilAvailabilityScheduleName", "Supplemental Heating or Reheat Coil Availability Schedule Name"},
{ HVACTemplate_System_UnitarySystemFields::SupplementalHeatingorReheatCoilCapacity, "SupplementalHeatingorReheatCoilCapacity", "Supplemental Heating or Reheat Coil Capacity"},
{ HVACTemplate_System_UnitarySystemFields::SupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature, "SupplementalHeatingorReheatCoilMaximumOutdoorDryBulbTemperature", "Supplemental Heating or Reheat Coil Maximum Outdoor Dry-Bulb Temperature"},
{ HVACTemplate_System_UnitarySystemFields::SupplementalGasHeatingorReheatCoilEfficiency, "SupplementalGasHeatingorReheatCoilEfficiency", "Supplemental Gas Heating or Reheat Coil Efficiency"},
{ HVACTemplate_System_UnitarySystemFields::SupplementalGasHeatingorReheatCoilParasiticElectricLoad, "SupplementalGasHeatingorReheatCoilParasiticElectricLoad", "Supplemental Gas Heating or Reheat Coil Parasitic Electric Load"},
{ HVACTemplate_System_UnitarySystemFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ HVACTemplate_System_UnitarySystemFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ HVACTemplate_System_UnitarySystemFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ HVACTemplate_System_UnitarySystemFields::EconomizerType, "EconomizerType", "Economizer Type"},
{ HVACTemplate_System_UnitarySystemFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
{ HVACTemplate_System_UnitarySystemFields::EconomizerMaximumLimitDryBulbTemperature, "EconomizerMaximumLimitDryBulbTemperature", "Economizer Maximum Limit Dry-Bulb Temperature"},
{ HVACTemplate_System_UnitarySystemFields::EconomizerMaximumLimitEnthalpy, "EconomizerMaximumLimitEnthalpy", "Economizer Maximum Limit Enthalpy"},
{ HVACTemplate_System_UnitarySystemFields::EconomizerMaximumLimitDewpointTemperature, "EconomizerMaximumLimitDewpointTemperature", "Economizer Maximum Limit Dewpoint Temperature"},
{ HVACTemplate_System_UnitarySystemFields::EconomizerMinimumLimitDryBulbTemperature, "EconomizerMinimumLimitDryBulbTemperature", "Economizer Minimum Limit Dry-Bulb Temperature"},
{ HVACTemplate_System_UnitarySystemFields::SupplyPlenumName, "SupplyPlenumName", "Supply Plenum Name"},
{ HVACTemplate_System_UnitarySystemFields::ReturnPlenumName, "ReturnPlenumName", "Return Plenum Name"},
{ HVACTemplate_System_UnitarySystemFields::HeatRecoveryType, "HeatRecoveryType", "Heat Recovery Type"},
{ HVACTemplate_System_UnitarySystemFields::SensibleHeatRecoveryEffectiveness, "SensibleHeatRecoveryEffectiveness", "Sensible Heat Recovery Effectiveness"},
{ HVACTemplate_System_UnitarySystemFields::LatentHeatRecoveryEffectiveness, "LatentHeatRecoveryEffectiveness", "Latent Heat Recovery Effectiveness"},
{ HVACTemplate_System_UnitarySystemFields::HeatRecoveryHeatExchangerType, "HeatRecoveryHeatExchangerType", "Heat Recovery Heat Exchanger Type"},
{ HVACTemplate_System_UnitarySystemFields::HeatRecoveryFrostControlType, "HeatRecoveryFrostControlType", "Heat Recovery Frost Control Type"},
{ HVACTemplate_System_UnitarySystemFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ HVACTemplate_System_UnitarySystemFields::DehumidificationRelativeHumiditySetpoint, "DehumidificationRelativeHumiditySetpoint", "Dehumidification Relative Humidity Setpoint"},
{ HVACTemplate_System_UnitarySystemFields::DehumidificationRelativeHumiditySetpointScheduleName, "DehumidificationRelativeHumiditySetpointScheduleName", "Dehumidification Relative Humidity Setpoint Schedule Name"},
{ HVACTemplate_System_UnitarySystemFields::HumidifierType, "HumidifierType", "Humidifier Type"},
{ HVACTemplate_System_UnitarySystemFields::HumidifierAvailabilityScheduleName, "HumidifierAvailabilityScheduleName", "Humidifier Availability Schedule Name"},
{ HVACTemplate_System_UnitarySystemFields::HumidifierRatedCapacity, "HumidifierRatedCapacity", "Humidifier Rated Capacity"},
{ HVACTemplate_System_UnitarySystemFields::HumidifierRatedElectricPower, "HumidifierRatedElectricPower", "Humidifier Rated Electric Power"},
{ HVACTemplate_System_UnitarySystemFields::HumidifierControlZoneName, "HumidifierControlZoneName", "Humidifier Control Zone Name"},
{ HVACTemplate_System_UnitarySystemFields::HumidifierRelativeHumiditySetpoint, "HumidifierRelativeHumiditySetpoint", "Humidifier Relative Humidity Setpoint"},
{ HVACTemplate_System_UnitarySystemFields::HumidifierRelativeHumiditySetpointScheduleName, "HumidifierRelativeHumiditySetpointScheduleName", "Humidifier Relative Humidity Setpoint Schedule Name"},
{ HVACTemplate_System_UnitarySystemFields::SizingOption, "SizingOption", "Sizing Option"},
{ HVACTemplate_System_UnitarySystemFields::ReturnFan, "ReturnFan", "Return Fan"},
{ HVACTemplate_System_UnitarySystemFields::ReturnFanTotalEfficiency, "ReturnFanTotalEfficiency", "Return Fan Total Efficiency"},
{ HVACTemplate_System_UnitarySystemFields::ReturnFanDeltaPressure, "ReturnFanDeltaPressure", "Return Fan Delta Pressure"},
{ HVACTemplate_System_UnitarySystemFields::ReturnFanMotorEfficiency, "ReturnFanMotorEfficiency", "Return Fan Motor Efficiency"},
{ HVACTemplate_System_UnitarySystemFields::ReturnFanMotorinAirStreamFraction, "ReturnFanMotorinAirStreamFraction", "Return Fan Motor in Air Stream Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_System_UnitarySystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_System_UnitarySystemFields> OptionalHVACTemplate_System_UnitarySystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_SYSTEM_UNITARYSYSTEM_FIELDENUMS_HXX
