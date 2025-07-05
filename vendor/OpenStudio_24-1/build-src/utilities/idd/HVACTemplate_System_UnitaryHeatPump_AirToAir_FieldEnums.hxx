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

#ifndef UTILITIES_IDD_HVACTEMPLATE_SYSTEM_UNITARYHEATPUMP_AIRTOAIR_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_SYSTEM_UNITARYHEATPUMP_AIRTOAIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_System_UnitaryHeatPump_AirToAirFields
 *  \brief Enumeration of HVACTemplate:System:UnitaryHeatPump:AirToAir's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_System_UnitaryHeatPump_AirToAirFields, )
#else
class HVACTemplate_System_UnitaryHeatPump_AirToAirFields: public ::EnumBase<HVACTemplate_System_UnitaryHeatPump_AirToAirFields> {
 public: 
  enum domain 
  {
Name, SystemAvailabilityScheduleName, ControlZoneorThermostatLocationName, CoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoLoadSupplyAirFlowRate, SupplyFanOperatingModeScheduleName, SupplyFanPlacement, SupplyFanTotalEfficiency, SupplyFanDeltaPressure, SupplyFanMotorEfficiency, SupplyFanMotorinAirStreamFraction, CoolingCoilType, CoolingCoilAvailabilityScheduleName, CoolingDesignSupplyAirTemperature, CoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedCOP, HeatPumpHeatingCoilType, HeatPumpHeatingCoilAvailabilityScheduleName, HeatingDesignSupplyAirTemperature, HeatPumpHeatingCoilGrossRatedCapacity, HeatPumpHeatingCoilRatedCOP, HeatPumpHeatingMinimumOutdoorDryBulbTemperature, HeatPumpDefrostMaximumOutdoorDryBulbTemperature, HeatPumpDefrostStrategy, HeatPumpDefrostControl, HeatPumpDefrostTimePeriodFraction, SupplementalHeatingCoilType, SupplementalHeatingCoilAvailabilityScheduleName, SupplementalHeatingCoilCapacity, SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature, SupplementalGasHeatingCoilEfficiency, SupplementalGasHeatingCoilParasiticElectricLoad, MaximumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate, MinimumOutdoorAirScheduleName, EconomizerType, EconomizerLockout, EconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitDewpointTemperature, EconomizerMinimumLimitDryBulbTemperature, SupplyPlenumName, ReturnPlenumName, NightCycleControl, NightCycleControlZoneName, HeatRecoveryType, SensibleHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness, HumidifierType, HumidifierAvailabilityScheduleName, HumidifierRatedCapacity, HumidifierRatedElectricPower, HumidifierControlZoneName, HumidifierSetpoint, ReturnFan, ReturnFanTotalEfficiency, ReturnFanDeltaPressure, ReturnFanMotorEfficiency, ReturnFanMotorinAirStreamFraction,   };
  HVACTemplate_System_UnitaryHeatPump_AirToAirFields()
   : EnumBase<HVACTemplate_System_UnitaryHeatPump_AirToAirFields>(Name) {} 
  HVACTemplate_System_UnitaryHeatPump_AirToAirFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_System_UnitaryHeatPump_AirToAirFields>(t_name) {} 
  HVACTemplate_System_UnitaryHeatPump_AirToAirFields(int t_value) 
   : EnumBase<HVACTemplate_System_UnitaryHeatPump_AirToAirFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_System_UnitaryHeatPump_AirToAirFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_System_UnitaryHeatPump_AirToAirFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_System_UnitaryHeatPump_AirToAirFields>;
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
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::Name, "Name", "Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::ControlZoneorThermostatLocationName, "ControlZoneorThermostatLocationName", "Control Zone or Thermostat Location Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplyFanOperatingModeScheduleName, "SupplyFanOperatingModeScheduleName", "Supply Fan Operating Mode Schedule Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplyFanPlacement, "SupplyFanPlacement", "Supply Fan Placement"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplyFanTotalEfficiency, "SupplyFanTotalEfficiency", "Supply Fan Total Efficiency"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplyFanDeltaPressure, "SupplyFanDeltaPressure", "Supply Fan Delta Pressure"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplyFanMotorEfficiency, "SupplyFanMotorEfficiency", "Supply Fan Motor Efficiency"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplyFanMotorinAirStreamFraction, "SupplyFanMotorinAirStreamFraction", "Supply Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::CoolingCoilAvailabilityScheduleName, "CoolingCoilAvailabilityScheduleName", "Cooling Coil Availability Schedule Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::CoolingDesignSupplyAirTemperature, "CoolingDesignSupplyAirTemperature", "Cooling Design Supply Air Temperature"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::CoolingCoilGrossRatedTotalCapacity, "CoolingCoilGrossRatedTotalCapacity", "Cooling Coil Gross Rated Total Capacity"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::CoolingCoilGrossRatedSensibleHeatRatio, "CoolingCoilGrossRatedSensibleHeatRatio", "Cooling Coil Gross Rated Sensible Heat Ratio"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::CoolingCoilGrossRatedCOP, "CoolingCoilGrossRatedCOP", "Cooling Coil Gross Rated COP"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatPumpHeatingCoilType, "HeatPumpHeatingCoilType", "Heat Pump Heating Coil Type"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatPumpHeatingCoilAvailabilityScheduleName, "HeatPumpHeatingCoilAvailabilityScheduleName", "Heat Pump Heating Coil Availability Schedule Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatingDesignSupplyAirTemperature, "HeatingDesignSupplyAirTemperature", "Heating Design Supply Air Temperature"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatPumpHeatingCoilGrossRatedCapacity, "HeatPumpHeatingCoilGrossRatedCapacity", "Heat Pump Heating Coil Gross Rated Capacity"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatPumpHeatingCoilRatedCOP, "HeatPumpHeatingCoilRatedCOP", "Heat Pump Heating Coil Rated COP"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatPumpHeatingMinimumOutdoorDryBulbTemperature, "HeatPumpHeatingMinimumOutdoorDryBulbTemperature", "Heat Pump Heating Minimum Outdoor Dry-Bulb Temperature"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatPumpDefrostMaximumOutdoorDryBulbTemperature, "HeatPumpDefrostMaximumOutdoorDryBulbTemperature", "Heat Pump Defrost Maximum Outdoor Dry-Bulb Temperature"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatPumpDefrostStrategy, "HeatPumpDefrostStrategy", "Heat Pump Defrost Strategy"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatPumpDefrostControl, "HeatPumpDefrostControl", "Heat Pump Defrost Control"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatPumpDefrostTimePeriodFraction, "HeatPumpDefrostTimePeriodFraction", "Heat Pump Defrost Time Period Fraction"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplementalHeatingCoilType, "SupplementalHeatingCoilType", "Supplemental Heating Coil Type"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplementalHeatingCoilAvailabilityScheduleName, "SupplementalHeatingCoilAvailabilityScheduleName", "Supplemental Heating Coil Availability Schedule Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplementalHeatingCoilCapacity, "SupplementalHeatingCoilCapacity", "Supplemental Heating Coil Capacity"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature, "SupplementalHeatingCoilMaximumOutdoorDryBulbTemperature", "Supplemental Heating Coil Maximum Outdoor Dry-Bulb Temperature"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplementalGasHeatingCoilEfficiency, "SupplementalGasHeatingCoilEfficiency", "Supplemental Gas Heating Coil Efficiency"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplementalGasHeatingCoilParasiticElectricLoad, "SupplementalGasHeatingCoilParasiticElectricLoad", "Supplemental Gas Heating Coil Parasitic Electric Load"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::EconomizerType, "EconomizerType", "Economizer Type"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::EconomizerMaximumLimitDryBulbTemperature, "EconomizerMaximumLimitDryBulbTemperature", "Economizer Maximum Limit Dry-Bulb Temperature"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::EconomizerMaximumLimitEnthalpy, "EconomizerMaximumLimitEnthalpy", "Economizer Maximum Limit Enthalpy"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::EconomizerMaximumLimitDewpointTemperature, "EconomizerMaximumLimitDewpointTemperature", "Economizer Maximum Limit Dewpoint Temperature"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::EconomizerMinimumLimitDryBulbTemperature, "EconomizerMinimumLimitDryBulbTemperature", "Economizer Minimum Limit Dry-Bulb Temperature"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SupplyPlenumName, "SupplyPlenumName", "Supply Plenum Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::ReturnPlenumName, "ReturnPlenumName", "Return Plenum Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::NightCycleControl, "NightCycleControl", "Night Cycle Control"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::NightCycleControlZoneName, "NightCycleControlZoneName", "Night Cycle Control Zone Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HeatRecoveryType, "HeatRecoveryType", "Heat Recovery Type"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::SensibleHeatRecoveryEffectiveness, "SensibleHeatRecoveryEffectiveness", "Sensible Heat Recovery Effectiveness"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::LatentHeatRecoveryEffectiveness, "LatentHeatRecoveryEffectiveness", "Latent Heat Recovery Effectiveness"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HumidifierType, "HumidifierType", "Humidifier Type"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HumidifierAvailabilityScheduleName, "HumidifierAvailabilityScheduleName", "Humidifier Availability Schedule Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HumidifierRatedCapacity, "HumidifierRatedCapacity", "Humidifier Rated Capacity"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HumidifierRatedElectricPower, "HumidifierRatedElectricPower", "Humidifier Rated Electric Power"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HumidifierControlZoneName, "HumidifierControlZoneName", "Humidifier Control Zone Name"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::HumidifierSetpoint, "HumidifierSetpoint", "Humidifier Setpoint"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::ReturnFan, "ReturnFan", "Return Fan"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::ReturnFanTotalEfficiency, "ReturnFanTotalEfficiency", "Return Fan Total Efficiency"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::ReturnFanDeltaPressure, "ReturnFanDeltaPressure", "Return Fan Delta Pressure"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::ReturnFanMotorEfficiency, "ReturnFanMotorEfficiency", "Return Fan Motor Efficiency"},
{ HVACTemplate_System_UnitaryHeatPump_AirToAirFields::ReturnFanMotorinAirStreamFraction, "ReturnFanMotorinAirStreamFraction", "Return Fan Motor in Air Stream Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_System_UnitaryHeatPump_AirToAirFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_System_UnitaryHeatPump_AirToAirFields> OptionalHVACTemplate_System_UnitaryHeatPump_AirToAirFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_SYSTEM_UNITARYHEATPUMP_AIRTOAIR_FIELDENUMS_HXX
