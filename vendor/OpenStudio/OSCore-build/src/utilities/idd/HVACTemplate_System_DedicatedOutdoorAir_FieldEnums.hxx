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

#ifndef UTILITIES_IDD_HVACTEMPLATE_SYSTEM_DEDICATEDOUTDOORAIR_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_SYSTEM_DEDICATEDOUTDOORAIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_System_DedicatedOutdoorAirFields
 *  \brief Enumeration of HVACTemplate:System:DedicatedOutdoorAir's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_System_DedicatedOutdoorAirFields, )
#else
class HVACTemplate_System_DedicatedOutdoorAirFields: public ::EnumBase<HVACTemplate_System_DedicatedOutdoorAirFields> {
 public: 
  enum domain 
  {
Name, SystemAvailabilityScheduleName, AirOutletType, SupplyFanFlowRate, SupplyFanTotalEfficiency, SupplyFanDeltaPressure, SupplyFanMotorEfficiency, SupplyFanMotorinAirStreamFraction, SupplyFanPlacement, CoolingCoilType, CoolingCoilAvailabilityScheduleName, CoolingCoilSetpointControlType, CoolingCoilDesignSetpoint, CoolingCoilSetpointScheduleName, CoolingCoilSetpointatOutdoorDryBulbLow, CoolingCoilResetOutdoorDryBulbLow, CoolingCoilSetpointatOutdoorDryBulbHigh, CoolingCoilResetOutdoorDryBulbHigh, DXCoolingCoilGrossRatedTotalCapacity, DXCoolingCoilGrossRatedSensibleHeatRatio, DXCoolingCoilGrossRatedCOP, HeatingCoilType, HeatingCoilAvailabilityScheduleName, HeatingCoilSetpointControlType, HeatingCoilDesignSetpoint, HeatingCoilSetpointScheduleName, HeatingCoilSetpointatOutdoorDryBulbLow, HeatingCoilResetOutdoorDryBulbLow, HeatingCoilSetpointatOutdoorDryBulbHigh, HeatingCoilResetOutdoorDryBulbHigh, GasHeatingCoilEfficiency, GasHeatingCoilParasiticElectricLoad, HeatRecoveryType, HeatRecoverySensibleEffectiveness, HeatRecoveryLatentEffectiveness, HeatRecoveryHeatExchangerType, HeatRecoveryFrostControlType, DehumidificationControlType, DehumidificationSetpoint, HumidifierType, HumidifierAvailabilityScheduleName, HumidifierRatedCapacity, HumidifierRatedElectricPower, HumidifierConstantSetpoint, DehumidificationSetpointScheduleName, HumidifierSetpointScheduleName,   };
  HVACTemplate_System_DedicatedOutdoorAirFields()
   : EnumBase<HVACTemplate_System_DedicatedOutdoorAirFields>(Name) {} 
  HVACTemplate_System_DedicatedOutdoorAirFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_System_DedicatedOutdoorAirFields>(t_name) {} 
  HVACTemplate_System_DedicatedOutdoorAirFields(int t_value) 
   : EnumBase<HVACTemplate_System_DedicatedOutdoorAirFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_System_DedicatedOutdoorAirFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_System_DedicatedOutdoorAirFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_System_DedicatedOutdoorAirFields>;
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
{ HVACTemplate_System_DedicatedOutdoorAirFields::Name, "Name", "Name"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::AirOutletType, "AirOutletType", "Air Outlet Type"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::SupplyFanFlowRate, "SupplyFanFlowRate", "Supply Fan Flow Rate"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::SupplyFanTotalEfficiency, "SupplyFanTotalEfficiency", "Supply Fan Total Efficiency"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::SupplyFanDeltaPressure, "SupplyFanDeltaPressure", "Supply Fan Delta Pressure"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::SupplyFanMotorEfficiency, "SupplyFanMotorEfficiency", "Supply Fan Motor Efficiency"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::SupplyFanMotorinAirStreamFraction, "SupplyFanMotorinAirStreamFraction", "Supply Fan Motor in Air Stream Fraction"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::SupplyFanPlacement, "SupplyFanPlacement", "Supply Fan Placement"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilAvailabilityScheduleName, "CoolingCoilAvailabilityScheduleName", "Cooling Coil Availability Schedule Name"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilSetpointControlType, "CoolingCoilSetpointControlType", "Cooling Coil Setpoint Control Type"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilDesignSetpoint, "CoolingCoilDesignSetpoint", "Cooling Coil Design Setpoint"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilSetpointScheduleName, "CoolingCoilSetpointScheduleName", "Cooling Coil Setpoint Schedule Name"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilSetpointatOutdoorDryBulbLow, "CoolingCoilSetpointatOutdoorDryBulbLow", "Cooling Coil Setpoint at Outdoor Dry-Bulb Low"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilResetOutdoorDryBulbLow, "CoolingCoilResetOutdoorDryBulbLow", "Cooling Coil Reset Outdoor Dry-Bulb Low"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilSetpointatOutdoorDryBulbHigh, "CoolingCoilSetpointatOutdoorDryBulbHigh", "Cooling Coil Setpoint at Outdoor Dry-Bulb High"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::CoolingCoilResetOutdoorDryBulbHigh, "CoolingCoilResetOutdoorDryBulbHigh", "Cooling Coil Reset Outdoor Dry-Bulb High"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::DXCoolingCoilGrossRatedTotalCapacity, "DXCoolingCoilGrossRatedTotalCapacity", "DX Cooling Coil Gross Rated Total Capacity"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::DXCoolingCoilGrossRatedSensibleHeatRatio, "DXCoolingCoilGrossRatedSensibleHeatRatio", "DX Cooling Coil Gross Rated Sensible Heat Ratio"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::DXCoolingCoilGrossRatedCOP, "DXCoolingCoilGrossRatedCOP", "DX Cooling Coil Gross Rated COP"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilType, "HeatingCoilType", "Heating Coil Type"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilAvailabilityScheduleName, "HeatingCoilAvailabilityScheduleName", "Heating Coil Availability Schedule Name"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilSetpointControlType, "HeatingCoilSetpointControlType", "Heating Coil Setpoint Control Type"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilDesignSetpoint, "HeatingCoilDesignSetpoint", "Heating Coil Design Setpoint"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilSetpointScheduleName, "HeatingCoilSetpointScheduleName", "Heating Coil Setpoint Schedule Name"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilSetpointatOutdoorDryBulbLow, "HeatingCoilSetpointatOutdoorDryBulbLow", "Heating Coil Setpoint at Outdoor Dry-Bulb Low"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilResetOutdoorDryBulbLow, "HeatingCoilResetOutdoorDryBulbLow", "Heating Coil Reset Outdoor Dry-Bulb Low"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilSetpointatOutdoorDryBulbHigh, "HeatingCoilSetpointatOutdoorDryBulbHigh", "Heating Coil Setpoint at Outdoor Dry-Bulb High"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatingCoilResetOutdoorDryBulbHigh, "HeatingCoilResetOutdoorDryBulbHigh", "Heating Coil Reset Outdoor Dry-Bulb High"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::GasHeatingCoilEfficiency, "GasHeatingCoilEfficiency", "Gas Heating Coil Efficiency"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::GasHeatingCoilParasiticElectricLoad, "GasHeatingCoilParasiticElectricLoad", "Gas Heating Coil Parasitic Electric Load"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatRecoveryType, "HeatRecoveryType", "Heat Recovery Type"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatRecoverySensibleEffectiveness, "HeatRecoverySensibleEffectiveness", "Heat Recovery Sensible Effectiveness"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatRecoveryLatentEffectiveness, "HeatRecoveryLatentEffectiveness", "Heat Recovery Latent Effectiveness"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatRecoveryHeatExchangerType, "HeatRecoveryHeatExchangerType", "Heat Recovery Heat Exchanger Type"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HeatRecoveryFrostControlType, "HeatRecoveryFrostControlType", "Heat Recovery Frost Control Type"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::DehumidificationSetpoint, "DehumidificationSetpoint", "Dehumidification Setpoint"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HumidifierType, "HumidifierType", "Humidifier Type"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HumidifierAvailabilityScheduleName, "HumidifierAvailabilityScheduleName", "Humidifier Availability Schedule Name"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HumidifierRatedCapacity, "HumidifierRatedCapacity", "Humidifier Rated Capacity"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HumidifierRatedElectricPower, "HumidifierRatedElectricPower", "Humidifier Rated Electric Power"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HumidifierConstantSetpoint, "HumidifierConstantSetpoint", "Humidifier Constant Setpoint"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::DehumidificationSetpointScheduleName, "DehumidificationSetpointScheduleName", "Dehumidification Setpoint Schedule Name"},
{ HVACTemplate_System_DedicatedOutdoorAirFields::HumidifierSetpointScheduleName, "HumidifierSetpointScheduleName", "Humidifier Setpoint Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_System_DedicatedOutdoorAirFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_System_DedicatedOutdoorAirFields> OptionalHVACTemplate_System_DedicatedOutdoorAirFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_SYSTEM_DEDICATEDOUTDOORAIR_FIELDENUMS_HXX
