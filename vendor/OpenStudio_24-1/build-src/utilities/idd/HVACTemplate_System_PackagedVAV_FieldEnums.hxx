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

#ifndef UTILITIES_IDD_HVACTEMPLATE_SYSTEM_PACKAGEDVAV_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_SYSTEM_PACKAGEDVAV_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_System_PackagedVAVFields
 *  \brief Enumeration of HVACTemplate:System:PackagedVAV's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_System_PackagedVAVFields, )
#else
class HVACTemplate_System_PackagedVAVFields: public ::EnumBase<HVACTemplate_System_PackagedVAVFields> {
 public: 
  enum domain 
  {
Name, SystemAvailabilityScheduleName, SupplyFanMaximumFlowRate, SupplyFanMinimumFlowRate, SupplyFanPlacement, SupplyFanTotalEfficiency, SupplyFanDeltaPressure, SupplyFanMotorEfficiency, SupplyFanMotorinAirStreamFraction, CoolingCoilType, CoolingCoilAvailabilityScheduleName, CoolingCoilSetpointScheduleName, CoolingCoilDesignSetpoint, CoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedCOP, HeatingCoilType, HeatingCoilAvailabilityScheduleName, HeatingCoilSetpointScheduleName, HeatingCoilDesignSetpoint, HeatingCoilCapacity, GasHeatingCoilEfficiency, GasHeatingCoilParasiticElectricLoad, MaximumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate, MinimumOutdoorAirControlType, MinimumOutdoorAirScheduleName, EconomizerType, EconomizerLockout, EconomizerMaximumLimitDryBulbTemperature, EconomizerMaximumLimitEnthalpy, EconomizerMaximumLimitDewpointTemperature, EconomizerMinimumLimitDryBulbTemperature, SupplyPlenumName, ReturnPlenumName, SupplyFanPartLoadPowerCoefficients, NightCycleControl, NightCycleControlZoneName, HeatRecoveryType, SensibleHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness, CoolingCoilSetpointResetType, HeatingCoilSetpointResetType, DehumidificationControlType, DehumidificationControlZoneName, DehumidificationSetpoint, HumidifierType, HumidifierAvailabilityScheduleName, HumidifierRatedCapacity, HumidifierRatedElectricPower, HumidifierControlZoneName, HumidifierSetpoint, SizingOption, ReturnFan, ReturnFanTotalEfficiency, ReturnFanDeltaPressure, ReturnFanMotorEfficiency, ReturnFanMotorinAirStreamFraction, ReturnFanPartLoadPowerCoefficients,   };
  HVACTemplate_System_PackagedVAVFields()
   : EnumBase<HVACTemplate_System_PackagedVAVFields>(Name) {} 
  HVACTemplate_System_PackagedVAVFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_System_PackagedVAVFields>(t_name) {} 
  HVACTemplate_System_PackagedVAVFields(int t_value) 
   : EnumBase<HVACTemplate_System_PackagedVAVFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_System_PackagedVAVFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_System_PackagedVAVFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_System_PackagedVAVFields>;
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
{ HVACTemplate_System_PackagedVAVFields::Name, "Name", "Name"},
{ HVACTemplate_System_PackagedVAVFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_System_PackagedVAVFields::SupplyFanMaximumFlowRate, "SupplyFanMaximumFlowRate", "Supply Fan Maximum Flow Rate"},
{ HVACTemplate_System_PackagedVAVFields::SupplyFanMinimumFlowRate, "SupplyFanMinimumFlowRate", "Supply Fan Minimum Flow Rate"},
{ HVACTemplate_System_PackagedVAVFields::SupplyFanPlacement, "SupplyFanPlacement", "Supply Fan Placement"},
{ HVACTemplate_System_PackagedVAVFields::SupplyFanTotalEfficiency, "SupplyFanTotalEfficiency", "Supply Fan Total Efficiency"},
{ HVACTemplate_System_PackagedVAVFields::SupplyFanDeltaPressure, "SupplyFanDeltaPressure", "Supply Fan Delta Pressure"},
{ HVACTemplate_System_PackagedVAVFields::SupplyFanMotorEfficiency, "SupplyFanMotorEfficiency", "Supply Fan Motor Efficiency"},
{ HVACTemplate_System_PackagedVAVFields::SupplyFanMotorinAirStreamFraction, "SupplyFanMotorinAirStreamFraction", "Supply Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_PackagedVAVFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_System_PackagedVAVFields::CoolingCoilAvailabilityScheduleName, "CoolingCoilAvailabilityScheduleName", "Cooling Coil Availability Schedule Name"},
{ HVACTemplate_System_PackagedVAVFields::CoolingCoilSetpointScheduleName, "CoolingCoilSetpointScheduleName", "Cooling Coil Setpoint Schedule Name"},
{ HVACTemplate_System_PackagedVAVFields::CoolingCoilDesignSetpoint, "CoolingCoilDesignSetpoint", "Cooling Coil Design Setpoint"},
{ HVACTemplate_System_PackagedVAVFields::CoolingCoilGrossRatedTotalCapacity, "CoolingCoilGrossRatedTotalCapacity", "Cooling Coil Gross Rated Total Capacity"},
{ HVACTemplate_System_PackagedVAVFields::CoolingCoilGrossRatedSensibleHeatRatio, "CoolingCoilGrossRatedSensibleHeatRatio", "Cooling Coil Gross Rated Sensible Heat Ratio"},
{ HVACTemplate_System_PackagedVAVFields::CoolingCoilGrossRatedCOP, "CoolingCoilGrossRatedCOP", "Cooling Coil Gross Rated COP"},
{ HVACTemplate_System_PackagedVAVFields::HeatingCoilType, "HeatingCoilType", "Heating Coil Type"},
{ HVACTemplate_System_PackagedVAVFields::HeatingCoilAvailabilityScheduleName, "HeatingCoilAvailabilityScheduleName", "Heating Coil Availability Schedule Name"},
{ HVACTemplate_System_PackagedVAVFields::HeatingCoilSetpointScheduleName, "HeatingCoilSetpointScheduleName", "Heating Coil Setpoint Schedule Name"},
{ HVACTemplate_System_PackagedVAVFields::HeatingCoilDesignSetpoint, "HeatingCoilDesignSetpoint", "Heating Coil Design Setpoint"},
{ HVACTemplate_System_PackagedVAVFields::HeatingCoilCapacity, "HeatingCoilCapacity", "Heating Coil Capacity"},
{ HVACTemplate_System_PackagedVAVFields::GasHeatingCoilEfficiency, "GasHeatingCoilEfficiency", "Gas Heating Coil Efficiency"},
{ HVACTemplate_System_PackagedVAVFields::GasHeatingCoilParasiticElectricLoad, "GasHeatingCoilParasiticElectricLoad", "Gas Heating Coil Parasitic Electric Load"},
{ HVACTemplate_System_PackagedVAVFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ HVACTemplate_System_PackagedVAVFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ HVACTemplate_System_PackagedVAVFields::MinimumOutdoorAirControlType, "MinimumOutdoorAirControlType", "Minimum Outdoor Air Control Type"},
{ HVACTemplate_System_PackagedVAVFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ HVACTemplate_System_PackagedVAVFields::EconomizerType, "EconomizerType", "Economizer Type"},
{ HVACTemplate_System_PackagedVAVFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
{ HVACTemplate_System_PackagedVAVFields::EconomizerMaximumLimitDryBulbTemperature, "EconomizerMaximumLimitDryBulbTemperature", "Economizer Maximum Limit Dry-Bulb Temperature"},
{ HVACTemplate_System_PackagedVAVFields::EconomizerMaximumLimitEnthalpy, "EconomizerMaximumLimitEnthalpy", "Economizer Maximum Limit Enthalpy"},
{ HVACTemplate_System_PackagedVAVFields::EconomizerMaximumLimitDewpointTemperature, "EconomizerMaximumLimitDewpointTemperature", "Economizer Maximum Limit Dewpoint Temperature"},
{ HVACTemplate_System_PackagedVAVFields::EconomizerMinimumLimitDryBulbTemperature, "EconomizerMinimumLimitDryBulbTemperature", "Economizer Minimum Limit Dry-Bulb Temperature"},
{ HVACTemplate_System_PackagedVAVFields::SupplyPlenumName, "SupplyPlenumName", "Supply Plenum Name"},
{ HVACTemplate_System_PackagedVAVFields::ReturnPlenumName, "ReturnPlenumName", "Return Plenum Name"},
{ HVACTemplate_System_PackagedVAVFields::SupplyFanPartLoadPowerCoefficients, "SupplyFanPartLoadPowerCoefficients", "Supply Fan Part-Load Power Coefficients"},
{ HVACTemplate_System_PackagedVAVFields::NightCycleControl, "NightCycleControl", "Night Cycle Control"},
{ HVACTemplate_System_PackagedVAVFields::NightCycleControlZoneName, "NightCycleControlZoneName", "Night Cycle Control Zone Name"},
{ HVACTemplate_System_PackagedVAVFields::HeatRecoveryType, "HeatRecoveryType", "Heat Recovery Type"},
{ HVACTemplate_System_PackagedVAVFields::SensibleHeatRecoveryEffectiveness, "SensibleHeatRecoveryEffectiveness", "Sensible Heat Recovery Effectiveness"},
{ HVACTemplate_System_PackagedVAVFields::LatentHeatRecoveryEffectiveness, "LatentHeatRecoveryEffectiveness", "Latent Heat Recovery Effectiveness"},
{ HVACTemplate_System_PackagedVAVFields::CoolingCoilSetpointResetType, "CoolingCoilSetpointResetType", "Cooling Coil Setpoint Reset Type"},
{ HVACTemplate_System_PackagedVAVFields::HeatingCoilSetpointResetType, "HeatingCoilSetpointResetType", "Heating Coil Setpoint Reset Type"},
{ HVACTemplate_System_PackagedVAVFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ HVACTemplate_System_PackagedVAVFields::DehumidificationControlZoneName, "DehumidificationControlZoneName", "Dehumidification Control Zone Name"},
{ HVACTemplate_System_PackagedVAVFields::DehumidificationSetpoint, "DehumidificationSetpoint", "Dehumidification Setpoint"},
{ HVACTemplate_System_PackagedVAVFields::HumidifierType, "HumidifierType", "Humidifier Type"},
{ HVACTemplate_System_PackagedVAVFields::HumidifierAvailabilityScheduleName, "HumidifierAvailabilityScheduleName", "Humidifier Availability Schedule Name"},
{ HVACTemplate_System_PackagedVAVFields::HumidifierRatedCapacity, "HumidifierRatedCapacity", "Humidifier Rated Capacity"},
{ HVACTemplate_System_PackagedVAVFields::HumidifierRatedElectricPower, "HumidifierRatedElectricPower", "Humidifier Rated Electric Power"},
{ HVACTemplate_System_PackagedVAVFields::HumidifierControlZoneName, "HumidifierControlZoneName", "Humidifier Control Zone Name"},
{ HVACTemplate_System_PackagedVAVFields::HumidifierSetpoint, "HumidifierSetpoint", "Humidifier Setpoint"},
{ HVACTemplate_System_PackagedVAVFields::SizingOption, "SizingOption", "Sizing Option"},
{ HVACTemplate_System_PackagedVAVFields::ReturnFan, "ReturnFan", "Return Fan"},
{ HVACTemplate_System_PackagedVAVFields::ReturnFanTotalEfficiency, "ReturnFanTotalEfficiency", "Return Fan Total Efficiency"},
{ HVACTemplate_System_PackagedVAVFields::ReturnFanDeltaPressure, "ReturnFanDeltaPressure", "Return Fan Delta Pressure"},
{ HVACTemplate_System_PackagedVAVFields::ReturnFanMotorEfficiency, "ReturnFanMotorEfficiency", "Return Fan Motor Efficiency"},
{ HVACTemplate_System_PackagedVAVFields::ReturnFanMotorinAirStreamFraction, "ReturnFanMotorinAirStreamFraction", "Return Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_PackagedVAVFields::ReturnFanPartLoadPowerCoefficients, "ReturnFanPartLoadPowerCoefficients", "Return Fan Part-Load Power Coefficients"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_System_PackagedVAVFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_System_PackagedVAVFields> OptionalHVACTemplate_System_PackagedVAVFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_SYSTEM_PACKAGEDVAV_FIELDENUMS_HXX
