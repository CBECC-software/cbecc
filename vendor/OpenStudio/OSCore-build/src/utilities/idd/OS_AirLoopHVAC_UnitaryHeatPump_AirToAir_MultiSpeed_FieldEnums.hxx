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

#ifndef UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYHEATPUMP_AIRTOAIR_MULTISPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYHEATPUMP_AIRTOAIR_MULTISPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields
 *  \brief Enumeration of OS:AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields, )
#else
class OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields: public ::EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, AirInletNode, AirOutletNode, ControllingZoneorThermostatLocation, SupplyAirFan, SupplyAirFanPlacement, SupplyAirFanOperatingModeSchedule, HeatingCoil, MinimumOutdoorDryBulbTemperatureforCompressorOperation, CoolingCoil, SupplementalHeatingCoil, MaximumSupplyAirTemperaturefromSupplementalHeater, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, AuxiliaryOnCycleElectricPower, AuxiliaryOffCycleElectricPower, DesignHeatRecoveryWaterFlowRate, MaximumTemperatureforHeatRecovery, HeatRecoveryWaterInletNode, HeatRecoveryWaterOutletNode, SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, NumberofSpeedsforHeating, NumberofSpeedsforCooling, Speed1SupplyAirFlowRateDuringHeatingOperation, Speed2SupplyAirFlowRateDuringHeatingOperation, Speed3SupplyAirFlowRateDuringHeatingOperation, Speed4SupplyAirFlowRateDuringHeatingOperation, Speed1SupplyAirFlowRateDuringCoolingOperation, Speed2SupplyAirFlowRateDuringCoolingOperation, Speed3SupplyAirFlowRateDuringCoolingOperation, Speed4SupplyAirFlowRateDuringCoolingOperation,   };
  OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields()
   : EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields>(Handle) {} 
  OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields>(t_name) {} 
  OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields>;
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
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Handle, "Handle", "Handle"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Name, "Name", "Name"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AirInletNode, "AirInletNode", "Air Inlet Node"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AirOutletNode, "AirOutletNode", "Air Outlet Node"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::ControllingZoneorThermostatLocation, "ControllingZoneorThermostatLocation", "Controlling Zone or Thermostat Location"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFan, "SupplyAirFan", "Supply Air Fan"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanPlacement, "SupplyAirFanPlacement", "Supply Air Fan Placement"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanOperatingModeSchedule, "SupplyAirFanOperatingModeSchedule", "Supply Air Fan Operating Mode Schedule"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingCoil, "HeatingCoil", "Heating Coil"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingCoil, "CoolingCoil", "Cooling Coil"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplementalHeatingCoil, "SupplementalHeatingCoil", "Supplemental Heating Coil"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "MaximumSupplyAirTemperaturefromSupplementalHeater", "Maximum Supply Air Temperature from Supplemental Heater"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOnCycleElectricPower, "AuxiliaryOnCycleElectricPower", "Auxiliary On-Cycle Electric Power"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOffCycleElectricPower, "AuxiliaryOffCycleElectricPower", "Auxiliary Off-Cycle Electric Power"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumTemperatureforHeatRecovery, "MaximumTemperatureforHeatRecovery", "Maximum Temperature for Heat Recovery"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatRecoveryWaterInletNode, "HeatRecoveryWaterInletNode", "Heat Recovery Water Inlet Node"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatRecoveryWaterOutletNode, "HeatRecoveryWaterOutletNode", "Heat Recovery Water Outlet Node"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, "SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded", "Supply Air Flow Rate When No Cooling or Heating is Needed"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforHeating, "NumberofSpeedsforHeating", "Number of Speeds for Heating"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforCooling, "NumberofSpeedsforCooling", "Number of Speeds for Cooling"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Speed1SupplyAirFlowRateDuringHeatingOperation, "Speed1SupplyAirFlowRateDuringHeatingOperation", "Speed 1 Supply Air Flow Rate During Heating Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Speed2SupplyAirFlowRateDuringHeatingOperation, "Speed2SupplyAirFlowRateDuringHeatingOperation", "Speed 2 Supply Air Flow Rate During Heating Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Speed3SupplyAirFlowRateDuringHeatingOperation, "Speed3SupplyAirFlowRateDuringHeatingOperation", "Speed 3 Supply Air Flow Rate During Heating Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Speed4SupplyAirFlowRateDuringHeatingOperation, "Speed4SupplyAirFlowRateDuringHeatingOperation", "Speed 4 Supply Air Flow Rate During Heating Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Speed1SupplyAirFlowRateDuringCoolingOperation, "Speed1SupplyAirFlowRateDuringCoolingOperation", "Speed 1 Supply Air Flow Rate During Cooling Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Speed2SupplyAirFlowRateDuringCoolingOperation, "Speed2SupplyAirFlowRateDuringCoolingOperation", "Speed 2 Supply Air Flow Rate During Cooling Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Speed3SupplyAirFlowRateDuringCoolingOperation, "Speed3SupplyAirFlowRateDuringCoolingOperation", "Speed 3 Supply Air Flow Rate During Cooling Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Speed4SupplyAirFlowRateDuringCoolingOperation, "Speed4SupplyAirFlowRateDuringCoolingOperation", "Speed 4 Supply Air Flow Rate During Cooling Operation"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields> OptionalOS_AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYHEATPUMP_AIRTOAIR_MULTISPEED_FIELDENUMS_HXX
