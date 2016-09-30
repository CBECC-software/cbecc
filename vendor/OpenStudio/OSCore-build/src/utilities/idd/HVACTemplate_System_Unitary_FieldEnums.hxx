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

#ifndef UTILITIES_IDD_HVACTEMPLATE_SYSTEM_UNITARY_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_SYSTEM_UNITARY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_System_UnitaryFields
 *  \brief Enumeration of HVACTemplate:System:Unitary's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_System_UnitaryFields, )
#else
class HVACTemplate_System_UnitaryFields: public ::EnumBase<HVACTemplate_System_UnitaryFields> {
 public: 
  enum domain 
  {
Name, SystemAvailabilityScheduleName, ControlZoneorThermostatLocationName, SupplyFanMaximumFlowRate, SupplyFanOperatingModeScheduleName, SupplyFanTotalEfficiency, SupplyFanDeltaPressure, SupplyFanMotorEfficiency, SupplyFanMotorinAirStreamFraction, CoolingCoilType, CoolingCoilAvailabilityScheduleName, CoolingDesignSupplyAirTemperature, CoolingCoilGrossRatedTotalCapacity, CoolingCoilGrossRatedSensibleHeatRatio, CoolingCoilGrossRatedCOP, HeatingCoilType, HeatingCoilAvailabilityScheduleName, HeatingDesignSupplyAirTemperature, HeatingCoilCapacity, GasHeatingCoilEfficiency, GasHeatingCoilParasiticElectricLoad, MaximumOutdoorAirFlowRate, MinimumOutdoorAirFlowRate, MinimumOutdoorAirScheduleName, EconomizerType, EconomizerLockout, EconomizerUpperTemperatureLimit, EconomizerLowerTemperatureLimit, EconomizerUpperEnthalpyLimit, EconomizerMaximumLimitDewpointTemperature, SupplyPlenumName, ReturnPlenumName, SupplyFanPlacement, NightCycleControl, NightCycleControlZoneName, HeatRecoveryType, SensibleHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness, DehumidificationControlType, DehumidificationControlZoneName, DehumidificationSetpoint, HumidifierType, HumidifierAvailabilityScheduleName, HumidifierRatedCapacity, HumidifierRatedElectricPower, HumidifierControlZoneName, HumidifierSetpoint, ReturnFan, ReturnFanTotalEfficiency, ReturnFanDeltaPressure, ReturnFanMotorEfficiency, ReturnFanMotorinAirStreamFraction,   };
  HVACTemplate_System_UnitaryFields()
   : EnumBase<HVACTemplate_System_UnitaryFields>(Name) {} 
  HVACTemplate_System_UnitaryFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_System_UnitaryFields>(t_name) {} 
  HVACTemplate_System_UnitaryFields(int t_value) 
   : EnumBase<HVACTemplate_System_UnitaryFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_System_UnitaryFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_System_UnitaryFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_System_UnitaryFields>;
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
{ HVACTemplate_System_UnitaryFields::Name, "Name", "Name"},
{ HVACTemplate_System_UnitaryFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_System_UnitaryFields::ControlZoneorThermostatLocationName, "ControlZoneorThermostatLocationName", "Control Zone or Thermostat Location Name"},
{ HVACTemplate_System_UnitaryFields::SupplyFanMaximumFlowRate, "SupplyFanMaximumFlowRate", "Supply Fan Maximum Flow Rate"},
{ HVACTemplate_System_UnitaryFields::SupplyFanOperatingModeScheduleName, "SupplyFanOperatingModeScheduleName", "Supply Fan Operating Mode Schedule Name"},
{ HVACTemplate_System_UnitaryFields::SupplyFanTotalEfficiency, "SupplyFanTotalEfficiency", "Supply Fan Total Efficiency"},
{ HVACTemplate_System_UnitaryFields::SupplyFanDeltaPressure, "SupplyFanDeltaPressure", "Supply Fan Delta Pressure"},
{ HVACTemplate_System_UnitaryFields::SupplyFanMotorEfficiency, "SupplyFanMotorEfficiency", "Supply Fan Motor Efficiency"},
{ HVACTemplate_System_UnitaryFields::SupplyFanMotorinAirStreamFraction, "SupplyFanMotorinAirStreamFraction", "Supply Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_UnitaryFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_System_UnitaryFields::CoolingCoilAvailabilityScheduleName, "CoolingCoilAvailabilityScheduleName", "Cooling Coil Availability Schedule Name"},
{ HVACTemplate_System_UnitaryFields::CoolingDesignSupplyAirTemperature, "CoolingDesignSupplyAirTemperature", "Cooling Design Supply Air Temperature"},
{ HVACTemplate_System_UnitaryFields::CoolingCoilGrossRatedTotalCapacity, "CoolingCoilGrossRatedTotalCapacity", "Cooling Coil Gross Rated Total Capacity"},
{ HVACTemplate_System_UnitaryFields::CoolingCoilGrossRatedSensibleHeatRatio, "CoolingCoilGrossRatedSensibleHeatRatio", "Cooling Coil Gross Rated Sensible Heat Ratio"},
{ HVACTemplate_System_UnitaryFields::CoolingCoilGrossRatedCOP, "CoolingCoilGrossRatedCOP", "Cooling Coil Gross Rated COP"},
{ HVACTemplate_System_UnitaryFields::HeatingCoilType, "HeatingCoilType", "Heating Coil Type"},
{ HVACTemplate_System_UnitaryFields::HeatingCoilAvailabilityScheduleName, "HeatingCoilAvailabilityScheduleName", "Heating Coil Availability Schedule Name"},
{ HVACTemplate_System_UnitaryFields::HeatingDesignSupplyAirTemperature, "HeatingDesignSupplyAirTemperature", "Heating Design Supply Air Temperature"},
{ HVACTemplate_System_UnitaryFields::HeatingCoilCapacity, "HeatingCoilCapacity", "Heating Coil Capacity"},
{ HVACTemplate_System_UnitaryFields::GasHeatingCoilEfficiency, "GasHeatingCoilEfficiency", "Gas Heating Coil Efficiency"},
{ HVACTemplate_System_UnitaryFields::GasHeatingCoilParasiticElectricLoad, "GasHeatingCoilParasiticElectricLoad", "Gas Heating Coil Parasitic Electric Load"},
{ HVACTemplate_System_UnitaryFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ HVACTemplate_System_UnitaryFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ HVACTemplate_System_UnitaryFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ HVACTemplate_System_UnitaryFields::EconomizerType, "EconomizerType", "Economizer Type"},
{ HVACTemplate_System_UnitaryFields::EconomizerLockout, "EconomizerLockout", "Economizer Lockout"},
{ HVACTemplate_System_UnitaryFields::EconomizerUpperTemperatureLimit, "EconomizerUpperTemperatureLimit", "Economizer Upper Temperature Limit"},
{ HVACTemplate_System_UnitaryFields::EconomizerLowerTemperatureLimit, "EconomizerLowerTemperatureLimit", "Economizer Lower Temperature Limit"},
{ HVACTemplate_System_UnitaryFields::EconomizerUpperEnthalpyLimit, "EconomizerUpperEnthalpyLimit", "Economizer Upper Enthalpy Limit"},
{ HVACTemplate_System_UnitaryFields::EconomizerMaximumLimitDewpointTemperature, "EconomizerMaximumLimitDewpointTemperature", "Economizer Maximum Limit Dewpoint Temperature"},
{ HVACTemplate_System_UnitaryFields::SupplyPlenumName, "SupplyPlenumName", "Supply Plenum Name"},
{ HVACTemplate_System_UnitaryFields::ReturnPlenumName, "ReturnPlenumName", "Return Plenum Name"},
{ HVACTemplate_System_UnitaryFields::SupplyFanPlacement, "SupplyFanPlacement", "Supply Fan Placement"},
{ HVACTemplate_System_UnitaryFields::NightCycleControl, "NightCycleControl", "Night Cycle Control"},
{ HVACTemplate_System_UnitaryFields::NightCycleControlZoneName, "NightCycleControlZoneName", "Night Cycle Control Zone Name"},
{ HVACTemplate_System_UnitaryFields::HeatRecoveryType, "HeatRecoveryType", "Heat Recovery Type"},
{ HVACTemplate_System_UnitaryFields::SensibleHeatRecoveryEffectiveness, "SensibleHeatRecoveryEffectiveness", "Sensible Heat Recovery Effectiveness"},
{ HVACTemplate_System_UnitaryFields::LatentHeatRecoveryEffectiveness, "LatentHeatRecoveryEffectiveness", "Latent Heat Recovery Effectiveness"},
{ HVACTemplate_System_UnitaryFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ HVACTemplate_System_UnitaryFields::DehumidificationControlZoneName, "DehumidificationControlZoneName", "Dehumidification Control Zone Name"},
{ HVACTemplate_System_UnitaryFields::DehumidificationSetpoint, "DehumidificationSetpoint", "Dehumidification Setpoint"},
{ HVACTemplate_System_UnitaryFields::HumidifierType, "HumidifierType", "Humidifier Type"},
{ HVACTemplate_System_UnitaryFields::HumidifierAvailabilityScheduleName, "HumidifierAvailabilityScheduleName", "Humidifier Availability Schedule Name"},
{ HVACTemplate_System_UnitaryFields::HumidifierRatedCapacity, "HumidifierRatedCapacity", "Humidifier Rated Capacity"},
{ HVACTemplate_System_UnitaryFields::HumidifierRatedElectricPower, "HumidifierRatedElectricPower", "Humidifier Rated Electric Power"},
{ HVACTemplate_System_UnitaryFields::HumidifierControlZoneName, "HumidifierControlZoneName", "Humidifier Control Zone Name"},
{ HVACTemplate_System_UnitaryFields::HumidifierSetpoint, "HumidifierSetpoint", "Humidifier Setpoint"},
{ HVACTemplate_System_UnitaryFields::ReturnFan, "ReturnFan", "Return Fan"},
{ HVACTemplate_System_UnitaryFields::ReturnFanTotalEfficiency, "ReturnFanTotalEfficiency", "Return Fan Total Efficiency"},
{ HVACTemplate_System_UnitaryFields::ReturnFanDeltaPressure, "ReturnFanDeltaPressure", "Return Fan Delta Pressure"},
{ HVACTemplate_System_UnitaryFields::ReturnFanMotorEfficiency, "ReturnFanMotorEfficiency", "Return Fan Motor Efficiency"},
{ HVACTemplate_System_UnitaryFields::ReturnFanMotorinAirStreamFraction, "ReturnFanMotorinAirStreamFraction", "Return Fan Motor in Air Stream Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_System_UnitaryFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_System_UnitaryFields> OptionalHVACTemplate_System_UnitaryFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_SYSTEM_UNITARY_FIELDENUMS_HXX
