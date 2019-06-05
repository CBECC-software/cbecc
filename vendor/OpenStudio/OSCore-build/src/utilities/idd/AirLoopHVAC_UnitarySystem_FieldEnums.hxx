/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_UNITARYSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_UNITARYSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_UnitarySystemFields
 *  \brief Enumeration of AirLoopHVAC:UnitarySystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_UnitarySystemFields, )
#else
class AirLoopHVAC_UnitarySystemFields: public ::EnumBase<AirLoopHVAC_UnitarySystemFields> {
 public: 
  enum domain 
  {
Name, ControlType, ControllingZoneorThermostatLocation, DehumidificationControlType, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, SupplyFanObjectType, SupplyFanName, FanPlacement, SupplyAirFanOperatingModeScheduleName, HeatingCoilObjectType, HeatingCoilName, DXHeatingCoilSizingRatio, CoolingCoilObjectType, CoolingCoilName, UseDOASDXCoolingCoil, MinimumSupplyAirTemperature, LatentLoadControl, SupplementalHeatingCoilObjectType, SupplementalHeatingCoilName, CoolingSupplyAirFlowRateMethod, CoolingSupplyAirFlowRate, CoolingSupplyAirFlowRatePerFloorArea, CoolingFractionofAutosizedCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRatePerUnitofCapacity, HeatingSupplyAirFlowRateMethod, HeatingSupplyAirFlowRate, HeatingSupplyAirFlowRatePerFloorArea, HeatingFractionofAutosizedHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRatePerUnitofCapacity, NoLoadSupplyAirFlowRateMethod, NoLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRatePerFloorArea, NoLoadFractionofAutosizedCoolingSupplyAirFlowRate, NoLoadFractionofAutosizedHeatingSupplyAirFlowRate, NoLoadSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation, NoLoadSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation, MaximumSupplyAirTemperature, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, OutdoorDryBulbTemperatureSensorNodeName, MaximumCyclingRate, HeatPumpTimeConstant, FractionofOnCyclePowerUse, HeatPumpFanDelayTime, AncillaryOnCycleElectricPower, AncillaryOffCycleElectricPower, DesignHeatRecoveryWaterFlowRate, MaximumTemperatureforHeatRecovery, HeatRecoveryWaterInletNodeName, HeatRecoveryWaterOutletNodeName, DesignSpecificationMultispeedObjectType, DesignSpecificationMultispeedObjectName,   };
  AirLoopHVAC_UnitarySystemFields()
   : EnumBase<AirLoopHVAC_UnitarySystemFields>(Name) {} 
  AirLoopHVAC_UnitarySystemFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_UnitarySystemFields>(t_name) {} 
  AirLoopHVAC_UnitarySystemFields(int t_value) 
   : EnumBase<AirLoopHVAC_UnitarySystemFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_UnitarySystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_UnitarySystemFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_UnitarySystemFields>;
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
{ AirLoopHVAC_UnitarySystemFields::Name, "Name", "Name"},
{ AirLoopHVAC_UnitarySystemFields::ControlType, "ControlType", "Control Type"},
{ AirLoopHVAC_UnitarySystemFields::ControllingZoneorThermostatLocation, "ControllingZoneorThermostatLocation", "Controlling Zone or Thermostat Location"},
{ AirLoopHVAC_UnitarySystemFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ AirLoopHVAC_UnitarySystemFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirLoopHVAC_UnitarySystemFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ AirLoopHVAC_UnitarySystemFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ AirLoopHVAC_UnitarySystemFields::SupplyFanObjectType, "SupplyFanObjectType", "Supply Fan Object Type"},
{ AirLoopHVAC_UnitarySystemFields::SupplyFanName, "SupplyFanName", "Supply Fan Name"},
{ AirLoopHVAC_UnitarySystemFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ AirLoopHVAC_UnitarySystemFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ AirLoopHVAC_UnitarySystemFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ AirLoopHVAC_UnitarySystemFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ AirLoopHVAC_UnitarySystemFields::DXHeatingCoilSizingRatio, "DXHeatingCoilSizingRatio", "DX Heating Coil Sizing Ratio"},
{ AirLoopHVAC_UnitarySystemFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ AirLoopHVAC_UnitarySystemFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ AirLoopHVAC_UnitarySystemFields::UseDOASDXCoolingCoil, "UseDOASDXCoolingCoil", "Use DOAS DX Cooling Coil"},
{ AirLoopHVAC_UnitarySystemFields::MinimumSupplyAirTemperature, "MinimumSupplyAirTemperature", "Minimum Supply Air Temperature"},
{ AirLoopHVAC_UnitarySystemFields::LatentLoadControl, "LatentLoadControl", "Latent Load Control"},
{ AirLoopHVAC_UnitarySystemFields::SupplementalHeatingCoilObjectType, "SupplementalHeatingCoilObjectType", "Supplemental Heating Coil Object Type"},
{ AirLoopHVAC_UnitarySystemFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRateMethod, "CoolingSupplyAirFlowRateMethod", "Cooling Supply Air Flow Rate Method"},
{ AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerFloorArea, "CoolingSupplyAirFlowRatePerFloorArea", "Cooling Supply Air Flow Rate Per Floor Area"},
{ AirLoopHVAC_UnitarySystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, "CoolingFractionofAutosizedCoolingSupplyAirFlowRate", "Cooling Fraction of Autosized Cooling Supply Air Flow Rate"},
{ AirLoopHVAC_UnitarySystemFields::CoolingSupplyAirFlowRatePerUnitofCapacity, "CoolingSupplyAirFlowRatePerUnitofCapacity", "Cooling Supply Air Flow Rate Per Unit of Capacity"},
{ AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRateMethod, "HeatingSupplyAirFlowRateMethod", "Heating Supply Air Flow Rate Method"},
{ AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerFloorArea, "HeatingSupplyAirFlowRatePerFloorArea", "Heating Supply Air Flow Rate Per Floor Area"},
{ AirLoopHVAC_UnitarySystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate, "HeatingFractionofAutosizedHeatingSupplyAirFlowRate", "Heating Fraction of Autosized Heating Supply Air Flow Rate"},
{ AirLoopHVAC_UnitarySystemFields::HeatingSupplyAirFlowRatePerUnitofCapacity, "HeatingSupplyAirFlowRatePerUnitofCapacity", "Heating Supply Air Flow Rate Per Unit of Capacity"},
{ AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRateMethod, "NoLoadSupplyAirFlowRateMethod", "No Load Supply Air Flow Rate Method"},
{ AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerFloorArea, "NoLoadSupplyAirFlowRatePerFloorArea", "No Load Supply Air Flow Rate Per Floor Area"},
{ AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedCoolingSupplyAirFlowRate, "NoLoadFractionofAutosizedCoolingSupplyAirFlowRate", "No Load Fraction of Autosized Cooling Supply Air Flow Rate"},
{ AirLoopHVAC_UnitarySystemFields::NoLoadFractionofAutosizedHeatingSupplyAirFlowRate, "NoLoadFractionofAutosizedHeatingSupplyAirFlowRate", "No Load Fraction of Autosized Heating Supply Air Flow Rate"},
{ AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation, "NoLoadSupplyAirFlowRatePerUnitofCapacityDuringCoolingOperation", "No Load Supply Air Flow Rate Per Unit of Capacity During Cooling Operation"},
{ AirLoopHVAC_UnitarySystemFields::NoLoadSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation, "NoLoadSupplyAirFlowRatePerUnitofCapacityDuringHeatingOperation", "No Load Supply Air Flow Rate Per Unit of Capacity During Heating Operation"},
{ AirLoopHVAC_UnitarySystemFields::MaximumSupplyAirTemperature, "MaximumSupplyAirTemperature", "Maximum Supply Air Temperature"},
{ AirLoopHVAC_UnitarySystemFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ AirLoopHVAC_UnitarySystemFields::OutdoorDryBulbTemperatureSensorNodeName, "OutdoorDryBulbTemperatureSensorNodeName", "Outdoor Dry-Bulb Temperature Sensor Node Name"},
{ AirLoopHVAC_UnitarySystemFields::MaximumCyclingRate, "MaximumCyclingRate", "Maximum Cycling Rate"},
{ AirLoopHVAC_UnitarySystemFields::HeatPumpTimeConstant, "HeatPumpTimeConstant", "Heat Pump Time Constant"},
{ AirLoopHVAC_UnitarySystemFields::FractionofOnCyclePowerUse, "FractionofOnCyclePowerUse", "Fraction of On-Cycle Power Use"},
{ AirLoopHVAC_UnitarySystemFields::HeatPumpFanDelayTime, "HeatPumpFanDelayTime", "Heat Pump Fan Delay Time"},
{ AirLoopHVAC_UnitarySystemFields::AncillaryOnCycleElectricPower, "AncillaryOnCycleElectricPower", "Ancillary On-Cycle Electric Power"},
{ AirLoopHVAC_UnitarySystemFields::AncillaryOffCycleElectricPower, "AncillaryOffCycleElectricPower", "Ancillary Off-Cycle Electric Power"},
{ AirLoopHVAC_UnitarySystemFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ AirLoopHVAC_UnitarySystemFields::MaximumTemperatureforHeatRecovery, "MaximumTemperatureforHeatRecovery", "Maximum Temperature for Heat Recovery"},
{ AirLoopHVAC_UnitarySystemFields::HeatRecoveryWaterInletNodeName, "HeatRecoveryWaterInletNodeName", "Heat Recovery Water Inlet Node Name"},
{ AirLoopHVAC_UnitarySystemFields::HeatRecoveryWaterOutletNodeName, "HeatRecoveryWaterOutletNodeName", "Heat Recovery Water Outlet Node Name"},
{ AirLoopHVAC_UnitarySystemFields::DesignSpecificationMultispeedObjectType, "DesignSpecificationMultispeedObjectType", "Design Specification Multispeed Object Type"},
{ AirLoopHVAC_UnitarySystemFields::DesignSpecificationMultispeedObjectName, "DesignSpecificationMultispeedObjectName", "Design Specification Multispeed Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_UnitarySystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_UnitarySystemFields> OptionalAirLoopHVAC_UnitarySystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_UNITARYSYSTEM_FIELDENUMS_HXX
