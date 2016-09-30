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

#ifndef UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirLoopHVAC_UnitarySystemFields
 *  \brief Enumeration of OS:AirLoopHVAC:UnitarySystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_UnitarySystemFields, )
#else
class OS_AirLoopHVAC_UnitarySystemFields: public ::EnumBase<OS_AirLoopHVAC_UnitarySystemFields> {
 public: 
  enum domain 
  {
Handle, Name, ControlType, ControllingZoneorThermostatLocation, DehumidificationControlType, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, SupplyFanName, FanPlacement, SupplyAirFanOperatingModeScheduleName, HeatingCoilName, DXHeatingCoilSizingRatio, CoolingCoilName, UseDOASDXCoolingCoil, DOASDXCoolingCoilLeavingMinimumAirTemperature, LatentLoadControl, SupplementalHeatingCoilName, SupplyAirFlowRateMethodDuringCoolingOperation, SupplyAirFlowRateDuringCoolingOperation, SupplyAirFlowRatePerFloorAreaDuringCoolingOperation, FractionofAutosizedDesignCoolingSupplyAirFlowRate, DesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation, SupplyAirFlowRateMethodDuringHeatingOperation, SupplyAirFlowRateDuringHeatingOperation, SupplyAirFlowRatePerFloorAreaduringHeatingOperation, FractionofAutosizedDesignHeatingSupplyAirFlowRate, DesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation, SupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired, SupplyAirFlowRateWhenNoCoolingorHeatingisRequired, SupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired, FractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired, FractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired, DesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired, DesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired, MaximumSupplyAirTemperature, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, OutdoorDryBulbTemperatureSensorNodeName, MaximumCyclingRate, HeatPumpTimeConstant, FractionofOnCyclePowerUse, HeatPumpFanDelayTime, AncilliaryOnCycleElectricPower, AncilliaryOffCycleElectricPower, DesignHeatRecoveryWaterFlowRate, MaximumTemperatureforHeatRecovery, HeatRecoveryWaterInletNodeName, HeatRecoveryWaterOutletNodeName, DesignSpecificationMultispeedHeatPumpObjectName,   };
  OS_AirLoopHVAC_UnitarySystemFields()
   : EnumBase<OS_AirLoopHVAC_UnitarySystemFields>(Handle) {} 
  OS_AirLoopHVAC_UnitarySystemFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_UnitarySystemFields>(t_name) {} 
  OS_AirLoopHVAC_UnitarySystemFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_UnitarySystemFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_UnitarySystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_UnitarySystemFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_UnitarySystemFields>;
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
{ OS_AirLoopHVAC_UnitarySystemFields::Handle, "Handle", "Handle"},
{ OS_AirLoopHVAC_UnitarySystemFields::Name, "Name", "Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::ControlType, "ControlType", "Control Type"},
{ OS_AirLoopHVAC_UnitarySystemFields::ControllingZoneorThermostatLocation, "ControllingZoneorThermostatLocation", "Controlling Zone or Thermostat Location"},
{ OS_AirLoopHVAC_UnitarySystemFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ OS_AirLoopHVAC_UnitarySystemFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyFanName, "SupplyFanName", "Supply Fan Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::DXHeatingCoilSizingRatio, "DXHeatingCoilSizingRatio", "DX Heating Coil Sizing Ratio"},
{ OS_AirLoopHVAC_UnitarySystemFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::UseDOASDXCoolingCoil, "UseDOASDXCoolingCoil", "Use DOAS DX Cooling Coil"},
{ OS_AirLoopHVAC_UnitarySystemFields::DOASDXCoolingCoilLeavingMinimumAirTemperature, "DOASDXCoolingCoilLeavingMinimumAirTemperature", "DOAS DX Cooling Coil Leaving Minimum Air Temperature"},
{ OS_AirLoopHVAC_UnitarySystemFields::LatentLoadControl, "LatentLoadControl", "Latent Load Control"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyAirFlowRateMethodDuringCoolingOperation, "SupplyAirFlowRateMethodDuringCoolingOperation", "Supply Air Flow Rate Method During Cooling Operation"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyAirFlowRateDuringCoolingOperation, "SupplyAirFlowRateDuringCoolingOperation", "Supply Air Flow Rate During Cooling Operation"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyAirFlowRatePerFloorAreaDuringCoolingOperation, "SupplyAirFlowRatePerFloorAreaDuringCoolingOperation", "Supply Air Flow Rate Per Floor Area During Cooling Operation"},
{ OS_AirLoopHVAC_UnitarySystemFields::FractionofAutosizedDesignCoolingSupplyAirFlowRate, "FractionofAutosizedDesignCoolingSupplyAirFlowRate", "Fraction of Autosized Design Cooling Supply Air Flow Rate"},
{ OS_AirLoopHVAC_UnitarySystemFields::DesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation, "DesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation", "Design Supply Air Flow Rate Per Unit of Capacity During Cooling Operation"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyAirFlowRateMethodDuringHeatingOperation, "SupplyAirFlowRateMethodDuringHeatingOperation", "Supply Air Flow Rate Method During Heating Operation"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyAirFlowRateDuringHeatingOperation, "SupplyAirFlowRateDuringHeatingOperation", "Supply Air Flow Rate During Heating Operation"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyAirFlowRatePerFloorAreaduringHeatingOperation, "SupplyAirFlowRatePerFloorAreaduringHeatingOperation", "Supply Air Flow Rate Per Floor Area during Heating Operation"},
{ OS_AirLoopHVAC_UnitarySystemFields::FractionofAutosizedDesignHeatingSupplyAirFlowRate, "FractionofAutosizedDesignHeatingSupplyAirFlowRate", "Fraction of Autosized Design Heating Supply Air Flow Rate"},
{ OS_AirLoopHVAC_UnitarySystemFields::DesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation, "DesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation", "Design Supply Air Flow Rate Per Unit of Capacity During Heating Operation"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired, "SupplyAirFlowRateMethodWhenNoCoolingorHeatingisRequired", "Supply Air Flow Rate Method When No Cooling or Heating is Required"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyAirFlowRateWhenNoCoolingorHeatingisRequired, "SupplyAirFlowRateWhenNoCoolingorHeatingisRequired", "Supply Air Flow Rate When No Cooling or Heating is Required"},
{ OS_AirLoopHVAC_UnitarySystemFields::SupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired, "SupplyAirFlowRatePerFloorAreaWhenNoCoolingorHeatingisRequired", "Supply Air Flow Rate Per Floor Area When No Cooling or Heating is Required"},
{ OS_AirLoopHVAC_UnitarySystemFields::FractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired, "FractionofAutosizedDesignCoolingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired", "Fraction of Autosized Design Cooling Supply Air Flow Rate When No Cooling or Heating is Required"},
{ OS_AirLoopHVAC_UnitarySystemFields::FractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired, "FractionofAutosizedDesignHeatingSupplyAirFlowRateWhenNoCoolingorHeatingisRequired", "Fraction of Autosized Design Heating Supply Air Flow Rate When No Cooling or Heating is Required"},
{ OS_AirLoopHVAC_UnitarySystemFields::DesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired, "DesignSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperationWhenNoCoolingorHeatingisRequired", "Design Supply Air Flow Rate Per Unit of Capacity During Cooling Operation When No Cooling or Heating is Required"},
{ OS_AirLoopHVAC_UnitarySystemFields::DesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired, "DesignSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperationWhenNoCoolingorHeatingisRequired", "Design Supply Air Flow Rate Per Unit of Capacity During Heating Operation When No Cooling or Heating is Required"},
{ OS_AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, "MaximumSupplyAirTemperature", "Maximum Supply Air Temperature"},
{ OS_AirLoopHVAC_UnitarySystemFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ OS_AirLoopHVAC_UnitarySystemFields::OutdoorDryBulbTemperatureSensorNodeName, "OutdoorDryBulbTemperatureSensorNodeName", "Outdoor Dry-Bulb Temperature Sensor Node Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::MaximumCyclingRate, "MaximumCyclingRate", "Maximum Cycling Rate"},
{ OS_AirLoopHVAC_UnitarySystemFields::HeatPumpTimeConstant, "HeatPumpTimeConstant", "Heat Pump Time Constant"},
{ OS_AirLoopHVAC_UnitarySystemFields::FractionofOnCyclePowerUse, "FractionofOnCyclePowerUse", "Fraction of On-Cycle Power Use"},
{ OS_AirLoopHVAC_UnitarySystemFields::HeatPumpFanDelayTime, "HeatPumpFanDelayTime", "Heat Pump Fan Delay Time"},
{ OS_AirLoopHVAC_UnitarySystemFields::AncilliaryOnCycleElectricPower, "AncilliaryOnCycleElectricPower", "Ancilliary On-Cycle Electric Power"},
{ OS_AirLoopHVAC_UnitarySystemFields::AncilliaryOffCycleElectricPower, "AncilliaryOffCycleElectricPower", "Ancilliary Off-Cycle Electric Power"},
{ OS_AirLoopHVAC_UnitarySystemFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ OS_AirLoopHVAC_UnitarySystemFields::MaximumTemperatureforHeatRecovery, "MaximumTemperatureforHeatRecovery", "Maximum Temperature for Heat Recovery"},
{ OS_AirLoopHVAC_UnitarySystemFields::HeatRecoveryWaterInletNodeName, "HeatRecoveryWaterInletNodeName", "Heat Recovery Water Inlet Node Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::HeatRecoveryWaterOutletNodeName, "HeatRecoveryWaterOutletNodeName", "Heat Recovery Water Outlet Node Name"},
{ OS_AirLoopHVAC_UnitarySystemFields::DesignSpecificationMultispeedHeatPumpObjectName, "DesignSpecificationMultispeedHeatPumpObjectName", "Design Specification Multispeed Heat Pump Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_UnitarySystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_UnitarySystemFields> OptionalOS_AirLoopHVAC_UnitarySystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYSYSTEM_FIELDENUMS_HXX
