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

#ifndef UTILITIES_IDD_HVACTEMPLATE_SYSTEM_VAV_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_SYSTEM_VAV_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_System_VAVFields
 *  \brief Enumeration of HVACTemplate:System:VAV's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_System_VAVFields, )
#else
class HVACTemplate_System_VAVFields: public ::EnumBase<HVACTemplate_System_VAVFields> {
 public: 
  enum domain 
  {
Name, SystemAvailabilityScheduleName, SupplyFanMaximumFlowRate, SupplyFanMinimumFlowRate, SupplyFanTotalEfficiency, SupplyFanDeltaPressure, SupplyFanMotorEfficiency, SupplyFanMotorinAirStreamFraction, CoolingCoilType, CoolingCoilAvailabilityScheduleName, CoolingCoilSetpointScheduleName, CoolingCoilDesignSetpoint, HeatingCoilType, HeatingCoilAvailabilityScheduleName, HeatingCoilSetpointScheduleName, HeatingCoilDesignSetpoint, GasHeatingCoilEfficiency, GasHeatingCoilParasiticElectricLoad, PreheatCoilType, PreheatCoilAvailabilityScheduleName, PreheatCoilSetpointScheduleName, PreheatCoilDesignSetpoint, GasPreheatCoilEfficiency, GasPreheatCoilParasiticElectricLoad, MaximumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate, MinimumOutdoorAirControlType, MinimumOutdoorAirScheduleName, EconomizerType, EconomizerLockout, EconomizerUpperTemperatureLimit, EconomizerLowerTemperatureLimit, EconomizerUpperEnthalpyLimit, EconomizerMaximumLimitDewpointTemperature, SupplyPlenumName, ReturnPlenumName, SupplyFanPlacement, SupplyFanPartLoadPowerCoefficients, NightCycleControl, NightCycleControlZoneName, HeatRecoveryType, SensibleHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness, CoolingCoilSetpointResetType, HeatingCoilSetpointResetType, DehumidificationControlType, DehumidificationControlZoneName, DehumidificationSetpoint, HumidifierType, HumidifierAvailabilityScheduleName, HumidifierRatedCapacity, HumidifierRatedElectricPower, HumidifierControlZoneName, HumidifierSetpoint, SizingOption, ReturnFan, ReturnFanTotalEfficiency, ReturnFanDeltaPressure, ReturnFanMotorEfficiency, ReturnFanMotorinAirStreamFraction, ReturnFanPartLoadPowerCoefficients,   };
  HVACTemplate_System_VAVFields()
   : EnumBase<HVACTemplate_System_VAVFields>(Name) {} 
  HVACTemplate_System_VAVFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_System_VAVFields>(t_name) {} 
  HVACTemplate_System_VAVFields(int t_value) 
   : EnumBase<HVACTemplate_System_VAVFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_System_VAVFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_System_VAVFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_System_VAVFields>;
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
{ HVACTemplate_System_VAVFields::Name, "Name", "Name"},
{ HVACTemplate_System_VAVFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_System_VAVFields::SupplyFanMaximumFlowRate, "SupplyFanMaximumFlowRate", "Supply Fan Maximum Flow Rate"},
{ HVACTemplate_System_VAVFields::SupplyFanMinimumFlowRate, "SupplyFanMinimumFlowRate", "Supply Fan Minimum Flow Rate"},
{ HVACTemplate_System_VAVFields::SupplyFanTotalEfficiency, "SupplyFanTotalEfficiency", "Supply Fan Total Efficiency"},
{ HVACTemplate_System_VAVFields::SupplyFanDeltaPressure, "SupplyFanDeltaPressure", "Supply Fan Delta Pressure"},
{ HVACTemplate_System_VAVFields::SupplyFanMotorEfficiency, "SupplyFanMotorEfficiency", "Supply Fan Motor Efficiency"},
{ HVACTemplate_System_VAVFields::SupplyFanMotorinAirStreamFraction, "SupplyFanMotorinAirStreamFraction", "Supply Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_VAVFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_System_VAVFields::CoolingCoilAvailabilityScheduleName, "CoolingCoilAvailabilityScheduleName", "Cooling Coil Availability Schedule Name"},
{ HVACTemplate_System_VAVFields::CoolingCoilSetpointScheduleName, "CoolingCoilSetpointScheduleName", "Cooling Coil Setpoint Schedule Name"},
{ HVACTemplate_System_VAVFields::CoolingCoilDesignSetpoint, "CoolingCoilDesignSetpoint", "Cooling Coil Design Setpoint"},
{ HVACTemplate_System_VAVFields::HeatingCoilType, "HeatingCoilType", "Heating Coil Type"},
{ HVACTemplate_System_VAVFields::HeatingCoilAvailabilityScheduleName, "HeatingCoilAvailabilityScheduleName", "Heating Coil Availability Schedule Name"},
{ HVACTemplate_System_VAVFields::HeatingCoilSetpointScheduleName, "HeatingCoilSetpointScheduleName", "Heating Coil Setpoint Schedule Name"},
{ HVACTemplate_System_VAVFields::HeatingCoilDesignSetpoint, "HeatingCoilDesignSetpoint", "Heating Coil Design Setpoint"},
{ HVACTemplate_System_VAVFields::GasHeatingCoilEfficiency, "GasHeatingCoilEfficiency", "Gas Heating Coil Efficiency"},
{ HVACTemplate_System_VAVFields::GasHeatingCoilParasiticElectricLoad, "GasHeatingCoilParasiticElectricLoad", "Gas Heating Coil Parasitic Electric Load"},
{ HVACTemplate_System_VAVFields::PreheatCoilType, "PreheatCoilType", "Preheat Coil Type"},
{ HVACTemplate_System_VAVFields::PreheatCoilAvailabilityScheduleName, "PreheatCoilAvailabilityScheduleName", "Preheat Coil Availability Schedule Name"},
{ HVACTemplate_System_VAVFields::PreheatCoilSetpointScheduleName, "PreheatCoilSetpointScheduleName", "Preheat Coil Setpoint Schedule Name"},
{ HVACTemplate_System_VAVFields::PreheatCoilDesignSetpoint, "PreheatCoilDesignSetpoint", "Preheat Coil Design Setpoint"},
{ HVACTemplate_System_VAVFields::GasPreheatCoilEfficiency, "GasPreheatCoilEfficiency", "Gas Preheat Coil Efficiency"},
{ HVACTemplate_System_VAVFields::GasPreheatCoilParasiticElectricLoad, "GasPreheatCoilParasiticElectricLoad", "Gas Preheat Coil Parasitic Electric Load"},
{ HVACTemplate_System_VAVFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ HVACTemplate_System_VAVFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ HVACTemplate_System_VAVFields::MinimumOutdoorAirControlType, "MinimumOutdoorAirControlType", "Minimum Outdoor Air Control Type"},
{ HVACTemplate_System_VAVFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ HVACTemplate_System_VAVFields::EconomizerType, "EconomizerType", "Economizer Type"},
{ HVACTemplate_System_VAVFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
{ HVACTemplate_System_VAVFields::EconomizerUpperTemperatureLimit, "EconomizerUpperTemperatureLimit", "Economizer Upper Temperature Limit"},
{ HVACTemplate_System_VAVFields::EconomizerLowerTemperatureLimit, "EconomizerLowerTemperatureLimit", "Economizer Lower Temperature Limit"},
{ HVACTemplate_System_VAVFields::EconomizerUpperEnthalpyLimit, "EconomizerUpperEnthalpyLimit", "Economizer Upper Enthalpy Limit"},
{ HVACTemplate_System_VAVFields::EconomizerMaximumLimitDewpointTemperature, "EconomizerMaximumLimitDewpointTemperature", "Economizer Maximum Limit Dewpoint Temperature"},
{ HVACTemplate_System_VAVFields::SupplyPlenumName, "SupplyPlenumName", "Supply Plenum Name"},
{ HVACTemplate_System_VAVFields::ReturnPlenumName, "ReturnPlenumName", "Return Plenum Name"},
{ HVACTemplate_System_VAVFields::SupplyFanPlacement, "SupplyFanPlacement", "Supply Fan Placement"},
{ HVACTemplate_System_VAVFields::SupplyFanPartLoadPowerCoefficients, "SupplyFanPartLoadPowerCoefficients", "Supply Fan Part-Load Power Coefficients"},
{ HVACTemplate_System_VAVFields::NightCycleControl, "NightCycleControl", "Night Cycle Control"},
{ HVACTemplate_System_VAVFields::NightCycleControlZoneName, "NightCycleControlZoneName", "Night Cycle Control Zone Name"},
{ HVACTemplate_System_VAVFields::HeatRecoveryType, "HeatRecoveryType", "Heat Recovery Type"},
{ HVACTemplate_System_VAVFields::SensibleHeatRecoveryEffectiveness, "SensibleHeatRecoveryEffectiveness", "Sensible Heat Recovery Effectiveness"},
{ HVACTemplate_System_VAVFields::LatentHeatRecoveryEffectiveness, "LatentHeatRecoveryEffectiveness", "Latent Heat Recovery Effectiveness"},
{ HVACTemplate_System_VAVFields::CoolingCoilSetpointResetType, "CoolingCoilSetpointResetType", "Cooling Coil Setpoint Reset Type"},
{ HVACTemplate_System_VAVFields::HeatingCoilSetpointResetType, "HeatingCoilSetpointResetType", "Heating Coil Setpoint Reset Type"},
{ HVACTemplate_System_VAVFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ HVACTemplate_System_VAVFields::DehumidificationControlZoneName, "DehumidificationControlZoneName", "Dehumidification Control Zone Name"},
{ HVACTemplate_System_VAVFields::DehumidificationSetpoint, "DehumidificationSetpoint", "Dehumidification Setpoint"},
{ HVACTemplate_System_VAVFields::HumidifierType, "HumidifierType", "Humidifier Type"},
{ HVACTemplate_System_VAVFields::HumidifierAvailabilityScheduleName, "HumidifierAvailabilityScheduleName", "Humidifier Availability Schedule Name"},
{ HVACTemplate_System_VAVFields::HumidifierRatedCapacity, "HumidifierRatedCapacity", "Humidifier Rated Capacity"},
{ HVACTemplate_System_VAVFields::HumidifierRatedElectricPower, "HumidifierRatedElectricPower", "Humidifier Rated Electric Power"},
{ HVACTemplate_System_VAVFields::HumidifierControlZoneName, "HumidifierControlZoneName", "Humidifier Control Zone Name"},
{ HVACTemplate_System_VAVFields::HumidifierSetpoint, "HumidifierSetpoint", "Humidifier Setpoint"},
{ HVACTemplate_System_VAVFields::SizingOption, "SizingOption", "Sizing Option"},
{ HVACTemplate_System_VAVFields::ReturnFan, "ReturnFan", "Return Fan"},
{ HVACTemplate_System_VAVFields::ReturnFanTotalEfficiency, "ReturnFanTotalEfficiency", "Return Fan Total Efficiency"},
{ HVACTemplate_System_VAVFields::ReturnFanDeltaPressure, "ReturnFanDeltaPressure", "Return Fan Delta Pressure"},
{ HVACTemplate_System_VAVFields::ReturnFanMotorEfficiency, "ReturnFanMotorEfficiency", "Return Fan Motor Efficiency"},
{ HVACTemplate_System_VAVFields::ReturnFanMotorinAirStreamFraction, "ReturnFanMotorinAirStreamFraction", "Return Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_VAVFields::ReturnFanPartLoadPowerCoefficients, "ReturnFanPartLoadPowerCoefficients", "Return Fan Part-Load Power Coefficients"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_System_VAVFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_System_VAVFields> OptionalHVACTemplate_System_VAVFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_SYSTEM_VAV_FIELDENUMS_HXX
