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

#ifndef UTILITIES_IDD_HVACTEMPLATE_SYSTEM_DUALDUCT_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_SYSTEM_DUALDUCT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_System_DualDuctFields
 *  \brief Enumeration of HVACTemplate:System:DualDuct's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_System_DualDuctFields, )
#else
class HVACTemplate_System_DualDuctFields: public ::EnumBase<HVACTemplate_System_DualDuctFields> {
 public: 
  enum domain 
  {
Name, SystemAvailabilityScheduleName, SystemConfigurationType, MainSupplyFanMaximumFlowRate, MainSupplyFanMinimumFlowFraction, MainSupplyFanTotalEfficiency, MainSupplyFanDeltaPressure, MainSupplyFanMotorEfficiency, MainSupplyFanMotorinAirStreamFraction, MainSupplyFanPartLoadPowerCoefficients, ColdDuctSupplyFanMaximumFlowRate, ColdDuctSupplyFanMinimumFlowFraction, ColdDuctSupplyFanTotalEfficiency, ColdDuctSupplyFanDeltaPressure, ColdDuctSupplyFanMotorEfficiency, ColdDuctSupplyFanMotorinAirStreamFraction, ColdDuctSupplyFanPartLoadPowerCoefficients, ColdDuctSupplyFanPlacement, HotDuctSupplyFanMaximumFlowRate, HotDuctSupplyFanMinimumFlowFraction, HotDuctSupplyFanTotalEfficiency, HotDuctSupplyFanDeltaPressure, HotDuctSupplyFanMotorEfficiency, HotDuctSupplyFanMotorinAirStreamFraction, HotDuctSupplyFanPartLoadPowerCoefficients, HotDuctSupplyFanPlacement, CoolingCoilType, CoolingCoilAvailabilityScheduleName, CoolingCoilSetpointControlType, CoolingCoilDesignSetpointTemperature, CoolingCoilSetpointScheduleName, CoolingCoilSetpointatOutdoorDryBulbLow, CoolingCoilResetOutdoorDryBulbLow, CoolingCoilSetpointatOutdoorDryBulbHigh, CoolingCoilResetOutdoorDryBulbHigh, HeatingCoilType, HeatingCoilAvailabilityScheduleName, HeatingCoilSetpointControlType, HeatingCoilDesignSetpoint, HeatingCoilSetpointScheduleName, HeatingCoilSetpointatOutdoorDryBulbLow, HeatingCoilResetOutdoorDryBulbLow, HeatingCoilSetpointatOutdoorDryBulbHigh, HeatingCoilResetOutdoorDryBulbHigh, HeatingCoilCapacity, GasHeatingCoilEfficiency, GasHeatingCoilParasiticElectricLoad, PreheatCoilType, PreheatCoilAvailabilityScheduleName, PreheatCoilDesignSetpoint, PreheatCoilSetpointScheduleName, GasPreheatCoilEfficiency, GasPreheatCoilParasiticElectricLoad, MaximumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate, MinimumOutdoorAirControlType, MinimumOutdoorAirScheduleName, EconomizerType, EconomizerLockout, EconomizerUpperTemperatureLimit, EconomizerLowerTemperatureLimit, EconomizerUpperEnthalpyLimit, EconomizerMaximumLimitDewpointTemperature, ColdSupplyPlenumName, HotSupplyPlenumName, ReturnPlenumName, NightCycleControl, NightCycleControlZoneName, HeatRecoveryType, SensibleHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness, HeatRecoveryHeatExchangerType, HeatRecoveryFrostControlType, DehumidificationControlType, DehumidificationControlZoneName, DehumidificationRelativeHumiditySetpoint, DehumidificationRelativeHumiditySetpointScheduleName, HumidifierType, HumidifierAvailabilityScheduleName, HumidifierRatedCapacity, HumidifierRatedElectricPower, HumidifierControlZoneName, HumidifierRelativeHumiditySetpoint, HumidifierRelativeHumiditySetpointScheduleName, SizingOption, ReturnFan, ReturnFanTotalEfficiency, ReturnFanDeltaPressure, ReturnFanMotorEfficiency, ReturnFanMotorinAirStreamFraction, ReturnFanPartLoadPowerCoefficients,   };
  HVACTemplate_System_DualDuctFields()
   : EnumBase<HVACTemplate_System_DualDuctFields>(Name) {} 
  HVACTemplate_System_DualDuctFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_System_DualDuctFields>(t_name) {} 
  HVACTemplate_System_DualDuctFields(int t_value) 
   : EnumBase<HVACTemplate_System_DualDuctFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_System_DualDuctFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_System_DualDuctFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_System_DualDuctFields>;
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
{ HVACTemplate_System_DualDuctFields::Name, "Name", "Name"},
{ HVACTemplate_System_DualDuctFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_System_DualDuctFields::SystemConfigurationType, "SystemConfigurationType", "System Configuration Type"},
{ HVACTemplate_System_DualDuctFields::MainSupplyFanMaximumFlowRate, "MainSupplyFanMaximumFlowRate", "Main Supply Fan Maximum Flow Rate"},
{ HVACTemplate_System_DualDuctFields::MainSupplyFanMinimumFlowFraction, "MainSupplyFanMinimumFlowFraction", "Main Supply Fan Minimum Flow Fraction"},
{ HVACTemplate_System_DualDuctFields::MainSupplyFanTotalEfficiency, "MainSupplyFanTotalEfficiency", "Main Supply Fan Total Efficiency"},
{ HVACTemplate_System_DualDuctFields::MainSupplyFanDeltaPressure, "MainSupplyFanDeltaPressure", "Main Supply Fan Delta Pressure"},
{ HVACTemplate_System_DualDuctFields::MainSupplyFanMotorEfficiency, "MainSupplyFanMotorEfficiency", "Main Supply Fan Motor Efficiency"},
{ HVACTemplate_System_DualDuctFields::MainSupplyFanMotorinAirStreamFraction, "MainSupplyFanMotorinAirStreamFraction", "Main Supply Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_DualDuctFields::MainSupplyFanPartLoadPowerCoefficients, "MainSupplyFanPartLoadPowerCoefficients", "Main Supply Fan Part-Load Power Coefficients"},
{ HVACTemplate_System_DualDuctFields::ColdDuctSupplyFanMaximumFlowRate, "ColdDuctSupplyFanMaximumFlowRate", "Cold Duct Supply Fan Maximum Flow Rate"},
{ HVACTemplate_System_DualDuctFields::ColdDuctSupplyFanMinimumFlowFraction, "ColdDuctSupplyFanMinimumFlowFraction", "Cold Duct Supply Fan Minimum Flow Fraction"},
{ HVACTemplate_System_DualDuctFields::ColdDuctSupplyFanTotalEfficiency, "ColdDuctSupplyFanTotalEfficiency", "Cold Duct Supply Fan Total Efficiency"},
{ HVACTemplate_System_DualDuctFields::ColdDuctSupplyFanDeltaPressure, "ColdDuctSupplyFanDeltaPressure", "Cold Duct Supply Fan Delta Pressure"},
{ HVACTemplate_System_DualDuctFields::ColdDuctSupplyFanMotorEfficiency, "ColdDuctSupplyFanMotorEfficiency", "Cold Duct Supply Fan Motor Efficiency"},
{ HVACTemplate_System_DualDuctFields::ColdDuctSupplyFanMotorinAirStreamFraction, "ColdDuctSupplyFanMotorinAirStreamFraction", "Cold Duct Supply Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_DualDuctFields::ColdDuctSupplyFanPartLoadPowerCoefficients, "ColdDuctSupplyFanPartLoadPowerCoefficients", "Cold Duct Supply Fan Part-Load Power Coefficients"},
{ HVACTemplate_System_DualDuctFields::ColdDuctSupplyFanPlacement, "ColdDuctSupplyFanPlacement", "Cold Duct Supply Fan Placement"},
{ HVACTemplate_System_DualDuctFields::HotDuctSupplyFanMaximumFlowRate, "HotDuctSupplyFanMaximumFlowRate", "Hot Duct Supply Fan Maximum Flow Rate"},
{ HVACTemplate_System_DualDuctFields::HotDuctSupplyFanMinimumFlowFraction, "HotDuctSupplyFanMinimumFlowFraction", "Hot Duct Supply Fan Minimum Flow Fraction"},
{ HVACTemplate_System_DualDuctFields::HotDuctSupplyFanTotalEfficiency, "HotDuctSupplyFanTotalEfficiency", "Hot Duct Supply Fan Total Efficiency"},
{ HVACTemplate_System_DualDuctFields::HotDuctSupplyFanDeltaPressure, "HotDuctSupplyFanDeltaPressure", "Hot Duct Supply Fan Delta Pressure"},
{ HVACTemplate_System_DualDuctFields::HotDuctSupplyFanMotorEfficiency, "HotDuctSupplyFanMotorEfficiency", "Hot Duct Supply Fan Motor Efficiency"},
{ HVACTemplate_System_DualDuctFields::HotDuctSupplyFanMotorinAirStreamFraction, "HotDuctSupplyFanMotorinAirStreamFraction", "Hot Duct Supply Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_DualDuctFields::HotDuctSupplyFanPartLoadPowerCoefficients, "HotDuctSupplyFanPartLoadPowerCoefficients", "Hot Duct Supply Fan Part-Load Power Coefficients"},
{ HVACTemplate_System_DualDuctFields::HotDuctSupplyFanPlacement, "HotDuctSupplyFanPlacement", "Hot Duct Supply Fan Placement"},
{ HVACTemplate_System_DualDuctFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_System_DualDuctFields::CoolingCoilAvailabilityScheduleName, "CoolingCoilAvailabilityScheduleName", "Cooling Coil Availability Schedule Name"},
{ HVACTemplate_System_DualDuctFields::CoolingCoilSetpointControlType, "CoolingCoilSetpointControlType", "Cooling Coil Setpoint Control Type"},
{ HVACTemplate_System_DualDuctFields::CoolingCoilDesignSetpointTemperature, "CoolingCoilDesignSetpointTemperature", "Cooling Coil Design Setpoint Temperature"},
{ HVACTemplate_System_DualDuctFields::CoolingCoilSetpointScheduleName, "CoolingCoilSetpointScheduleName", "Cooling Coil Setpoint Schedule Name"},
{ HVACTemplate_System_DualDuctFields::CoolingCoilSetpointatOutdoorDryBulbLow, "CoolingCoilSetpointatOutdoorDryBulbLow", "Cooling Coil Setpoint at Outdoor Dry-Bulb Low"},
{ HVACTemplate_System_DualDuctFields::CoolingCoilResetOutdoorDryBulbLow, "CoolingCoilResetOutdoorDryBulbLow", "Cooling Coil Reset Outdoor Dry-Bulb Low"},
{ HVACTemplate_System_DualDuctFields::CoolingCoilSetpointatOutdoorDryBulbHigh, "CoolingCoilSetpointatOutdoorDryBulbHigh", "Cooling Coil Setpoint at Outdoor Dry-Bulb High"},
{ HVACTemplate_System_DualDuctFields::CoolingCoilResetOutdoorDryBulbHigh, "CoolingCoilResetOutdoorDryBulbHigh", "Cooling Coil Reset Outdoor Dry-Bulb High"},
{ HVACTemplate_System_DualDuctFields::HeatingCoilType, "HeatingCoilType", "Heating Coil Type"},
{ HVACTemplate_System_DualDuctFields::HeatingCoilAvailabilityScheduleName, "HeatingCoilAvailabilityScheduleName", "Heating Coil Availability Schedule Name"},
{ HVACTemplate_System_DualDuctFields::HeatingCoilSetpointControlType, "HeatingCoilSetpointControlType", "Heating Coil Setpoint Control Type"},
{ HVACTemplate_System_DualDuctFields::HeatingCoilDesignSetpoint, "HeatingCoilDesignSetpoint", "Heating Coil Design Setpoint"},
{ HVACTemplate_System_DualDuctFields::HeatingCoilSetpointScheduleName, "HeatingCoilSetpointScheduleName", "Heating Coil Setpoint Schedule Name"},
{ HVACTemplate_System_DualDuctFields::HeatingCoilSetpointatOutdoorDryBulbLow, "HeatingCoilSetpointatOutdoorDryBulbLow", "Heating Coil Setpoint at Outdoor Dry-Bulb Low"},
{ HVACTemplate_System_DualDuctFields::HeatingCoilResetOutdoorDryBulbLow, "HeatingCoilResetOutdoorDryBulbLow", "Heating Coil Reset Outdoor Dry-Bulb Low"},
{ HVACTemplate_System_DualDuctFields::HeatingCoilSetpointatOutdoorDryBulbHigh, "HeatingCoilSetpointatOutdoorDryBulbHigh", "Heating Coil Setpoint at Outdoor Dry-Bulb High"},
{ HVACTemplate_System_DualDuctFields::HeatingCoilResetOutdoorDryBulbHigh, "HeatingCoilResetOutdoorDryBulbHigh", "Heating Coil Reset Outdoor Dry-Bulb High"},
{ HVACTemplate_System_DualDuctFields::HeatingCoilCapacity, "HeatingCoilCapacity", "Heating Coil Capacity"},
{ HVACTemplate_System_DualDuctFields::GasHeatingCoilEfficiency, "GasHeatingCoilEfficiency", "Gas Heating Coil Efficiency"},
{ HVACTemplate_System_DualDuctFields::GasHeatingCoilParasiticElectricLoad, "GasHeatingCoilParasiticElectricLoad", "Gas Heating Coil Parasitic Electric Load"},
{ HVACTemplate_System_DualDuctFields::PreheatCoilType, "PreheatCoilType", "Preheat Coil Type"},
{ HVACTemplate_System_DualDuctFields::PreheatCoilAvailabilityScheduleName, "PreheatCoilAvailabilityScheduleName", "Preheat Coil Availability Schedule Name"},
{ HVACTemplate_System_DualDuctFields::PreheatCoilDesignSetpoint, "PreheatCoilDesignSetpoint", "Preheat Coil Design Setpoint"},
{ HVACTemplate_System_DualDuctFields::PreheatCoilSetpointScheduleName, "PreheatCoilSetpointScheduleName", "Preheat Coil Setpoint Schedule Name"},
{ HVACTemplate_System_DualDuctFields::GasPreheatCoilEfficiency, "GasPreheatCoilEfficiency", "Gas Preheat Coil Efficiency"},
{ HVACTemplate_System_DualDuctFields::GasPreheatCoilParasiticElectricLoad, "GasPreheatCoilParasiticElectricLoad", "Gas Preheat Coil Parasitic Electric Load"},
{ HVACTemplate_System_DualDuctFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ HVACTemplate_System_DualDuctFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ HVACTemplate_System_DualDuctFields::MinimumOutdoorAirControlType, "MinimumOutdoorAirControlType", "Minimum Outdoor Air Control Type"},
{ HVACTemplate_System_DualDuctFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ HVACTemplate_System_DualDuctFields::EconomizerType, "EconomizerType", "Economizer Type"},
{ HVACTemplate_System_DualDuctFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
{ HVACTemplate_System_DualDuctFields::EconomizerUpperTemperatureLimit, "EconomizerUpperTemperatureLimit", "Economizer Upper Temperature Limit"},
{ HVACTemplate_System_DualDuctFields::EconomizerLowerTemperatureLimit, "EconomizerLowerTemperatureLimit", "Economizer Lower Temperature Limit"},
{ HVACTemplate_System_DualDuctFields::EconomizerUpperEnthalpyLimit, "EconomizerUpperEnthalpyLimit", "Economizer Upper Enthalpy Limit"},
{ HVACTemplate_System_DualDuctFields::EconomizerMaximumLimitDewpointTemperature, "EconomizerMaximumLimitDewpointTemperature", "Economizer Maximum Limit Dewpoint Temperature"},
{ HVACTemplate_System_DualDuctFields::ColdSupplyPlenumName, "ColdSupplyPlenumName", "Cold Supply Plenum Name"},
{ HVACTemplate_System_DualDuctFields::HotSupplyPlenumName, "HotSupplyPlenumName", "Hot Supply Plenum Name"},
{ HVACTemplate_System_DualDuctFields::ReturnPlenumName, "ReturnPlenumName", "Return Plenum Name"},
{ HVACTemplate_System_DualDuctFields::NightCycleControl, "NightCycleControl", "Night Cycle Control"},
{ HVACTemplate_System_DualDuctFields::NightCycleControlZoneName, "NightCycleControlZoneName", "Night Cycle Control Zone Name"},
{ HVACTemplate_System_DualDuctFields::HeatRecoveryType, "HeatRecoveryType", "Heat Recovery Type"},
{ HVACTemplate_System_DualDuctFields::SensibleHeatRecoveryEffectiveness, "SensibleHeatRecoveryEffectiveness", "Sensible Heat Recovery Effectiveness"},
{ HVACTemplate_System_DualDuctFields::LatentHeatRecoveryEffectiveness, "LatentHeatRecoveryEffectiveness", "Latent Heat Recovery Effectiveness"},
{ HVACTemplate_System_DualDuctFields::HeatRecoveryHeatExchangerType, "HeatRecoveryHeatExchangerType", "Heat Recovery Heat Exchanger Type"},
{ HVACTemplate_System_DualDuctFields::HeatRecoveryFrostControlType, "HeatRecoveryFrostControlType", "Heat Recovery Frost Control Type"},
{ HVACTemplate_System_DualDuctFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ HVACTemplate_System_DualDuctFields::DehumidificationControlZoneName, "DehumidificationControlZoneName", "Dehumidification Control Zone Name"},
{ HVACTemplate_System_DualDuctFields::DehumidificationRelativeHumiditySetpoint, "DehumidificationRelativeHumiditySetpoint", "Dehumidification Relative Humidity Setpoint"},
{ HVACTemplate_System_DualDuctFields::DehumidificationRelativeHumiditySetpointScheduleName, "DehumidificationRelativeHumiditySetpointScheduleName", "Dehumidification Relative Humidity Setpoint Schedule Name"},
{ HVACTemplate_System_DualDuctFields::HumidifierType, "HumidifierType", "Humidifier Type"},
{ HVACTemplate_System_DualDuctFields::HumidifierAvailabilityScheduleName, "HumidifierAvailabilityScheduleName", "Humidifier Availability Schedule Name"},
{ HVACTemplate_System_DualDuctFields::HumidifierRatedCapacity, "HumidifierRatedCapacity", "Humidifier Rated Capacity"},
{ HVACTemplate_System_DualDuctFields::HumidifierRatedElectricPower, "HumidifierRatedElectricPower", "Humidifier Rated Electric Power"},
{ HVACTemplate_System_DualDuctFields::HumidifierControlZoneName, "HumidifierControlZoneName", "Humidifier Control Zone Name"},
{ HVACTemplate_System_DualDuctFields::HumidifierRelativeHumiditySetpoint, "HumidifierRelativeHumiditySetpoint", "Humidifier Relative Humidity Setpoint"},
{ HVACTemplate_System_DualDuctFields::HumidifierRelativeHumiditySetpointScheduleName, "HumidifierRelativeHumiditySetpointScheduleName", "Humidifier Relative Humidity Setpoint Schedule Name"},
{ HVACTemplate_System_DualDuctFields::SizingOption, "SizingOption", "Sizing Option"},
{ HVACTemplate_System_DualDuctFields::ReturnFan, "ReturnFan", "Return Fan"},
{ HVACTemplate_System_DualDuctFields::ReturnFanTotalEfficiency, "ReturnFanTotalEfficiency", "Return Fan Total Efficiency"},
{ HVACTemplate_System_DualDuctFields::ReturnFanDeltaPressure, "ReturnFanDeltaPressure", "Return Fan Delta Pressure"},
{ HVACTemplate_System_DualDuctFields::ReturnFanMotorEfficiency, "ReturnFanMotorEfficiency", "Return Fan Motor Efficiency"},
{ HVACTemplate_System_DualDuctFields::ReturnFanMotorinAirStreamFraction, "ReturnFanMotorinAirStreamFraction", "Return Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_DualDuctFields::ReturnFanPartLoadPowerCoefficients, "ReturnFanPartLoadPowerCoefficients", "Return Fan Part-Load Power Coefficients"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_System_DualDuctFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_System_DualDuctFields> OptionalHVACTemplate_System_DualDuctFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_SYSTEM_DUALDUCT_FIELDENUMS_HXX
