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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATPUMP_AIRTOAIR_MULTISPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATPUMP_AIRTOAIR_MULTISPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields
 *  \brief Enumeration of AirLoopHVAC:UnitaryHeatPump:AirToAir:MultiSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields, )
#else
class AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields: public ::EnumBase<AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, ControllingZoneorThermostatLocation, SupplyAirFanObjectType, SupplyAirFanName, SupplyAirFanPlacement, SupplyAirFanOperatingModeScheduleName, HeatingCoilObjectType, HeatingCoilName, MinimumOutdoorDryBulbTemperatureforCompressorOperation, CoolingCoilObjectType, CoolingCoilName, SupplementalHeatingCoilObjectType, SupplementalHeatingCoilName, MaximumSupplyAirTemperaturefromSupplementalHeater, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, AuxiliaryOnCycleElectricPower, AuxiliaryOffCycleElectricPower, DesignHeatRecoveryWaterFlowRate, MaximumTemperatureforHeatRecovery, HeatRecoveryWaterInletNodeName, HeatRecoveryWaterOutletNodeName, NoLoadSupplyAirFlowRate, NumberofSpeedsforHeating, NumberofSpeedsforCooling, HeatingSpeed1SupplyAirFlowRate, HeatingSpeed2SupplyAirFlowRate, HeatingSpeed3SupplyAirFlowRate, HeatingSpeed4SupplyAirFlowRate, CoolingSpeed1SupplyAirFlowRate, CoolingSpeed2SupplyAirFlowRate, CoolingSpeed3SupplyAirFlowRate, CoolingSpeed4SupplyAirFlowRate,   };
  AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields()
   : EnumBase<AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields>(Name) {} 
  AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields>(t_name) {} 
  AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields(int t_value) 
   : EnumBase<AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields>;
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
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::Name, "Name", "Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::ControllingZoneorThermostatLocation, "ControllingZoneorThermostatLocation", "Controlling Zone or Thermostat Location"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanPlacement, "SupplyAirFanPlacement", "Supply Air Fan Placement"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplementalHeatingCoilObjectType, "SupplementalHeatingCoilObjectType", "Supplemental Heating Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "MaximumSupplyAirTemperaturefromSupplementalHeater", "Maximum Supply Air Temperature from Supplemental Heater"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOnCycleElectricPower, "AuxiliaryOnCycleElectricPower", "Auxiliary On-Cycle Electric Power"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::AuxiliaryOffCycleElectricPower, "AuxiliaryOffCycleElectricPower", "Auxiliary Off-Cycle Electric Power"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::MaximumTemperatureforHeatRecovery, "MaximumTemperatureforHeatRecovery", "Maximum Temperature for Heat Recovery"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatRecoveryWaterInletNodeName, "HeatRecoveryWaterInletNodeName", "Heat Recovery Water Inlet Node Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatRecoveryWaterOutletNodeName, "HeatRecoveryWaterOutletNodeName", "Heat Recovery Water Outlet Node Name"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforHeating, "NumberofSpeedsforHeating", "Number of Speeds for Heating"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::NumberofSpeedsforCooling, "NumberofSpeedsforCooling", "Number of Speeds for Cooling"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed1SupplyAirFlowRate, "HeatingSpeed1SupplyAirFlowRate", "Heating Speed 1 Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed2SupplyAirFlowRate, "HeatingSpeed2SupplyAirFlowRate", "Heating Speed 2 Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed3SupplyAirFlowRate, "HeatingSpeed3SupplyAirFlowRate", "Heating Speed 3 Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::HeatingSpeed4SupplyAirFlowRate, "HeatingSpeed4SupplyAirFlowRate", "Heating Speed 4 Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed1SupplyAirFlowRate, "CoolingSpeed1SupplyAirFlowRate", "Cooling Speed 1 Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed2SupplyAirFlowRate, "CoolingSpeed2SupplyAirFlowRate", "Cooling Speed 2 Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed3SupplyAirFlowRate, "CoolingSpeed3SupplyAirFlowRate", "Cooling Speed 3 Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields::CoolingSpeed4SupplyAirFlowRate, "CoolingSpeed4SupplyAirFlowRate", "Cooling Speed 4 Supply Air Flow Rate"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields> OptionalAirLoopHVAC_UnitaryHeatPump_AirToAir_MultiSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATPUMP_AIRTOAIR_MULTISPEED_FIELDENUMS_HXX
