/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATPUMP_WATERTOAIR_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATPUMP_WATERTOAIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_UnitaryHeatPump_WaterToAirFields
 *  \brief Enumeration of AirLoopHVAC:UnitaryHeatPump:WaterToAir's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_UnitaryHeatPump_WaterToAirFields, )
#else
class AirLoopHVAC_UnitaryHeatPump_WaterToAirFields: public ::EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, SupplyAirFlowRate, ControllingZoneorThermostatLocation, SupplyAirFanObjectType, SupplyAirFanName, HeatingCoilObjectType, HeatingCoilName, HeatingConvergence, CoolingCoilObjectType, CoolingCoilName, CoolingConvergence, MaximumCyclingRate, HeatPumpTimeConstant, FractionofOnCyclePowerUse, HeatPumpFanDelayTime, SupplementalHeatingCoilObjectType, SupplementalHeatingCoilName, MaximumSupplyAirTemperaturefromSupplementalHeater, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, OutdoorDryBulbTemperatureSensorNodeName, FanPlacement, SupplyAirFanOperatingModeScheduleName, DehumidificationControlType, HeatPumpCoilWaterFlowMode,   };
  AirLoopHVAC_UnitaryHeatPump_WaterToAirFields()
   : EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields>(Name) {} 
  AirLoopHVAC_UnitaryHeatPump_WaterToAirFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields>(t_name) {} 
  AirLoopHVAC_UnitaryHeatPump_WaterToAirFields(int t_value) 
   : EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_UnitaryHeatPump_WaterToAirFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields>;
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
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::Name, "Name", "Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFlowRate, "SupplyAirFlowRate", "Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::ControllingZoneorThermostatLocation, "ControllingZoneorThermostatLocation", "Controlling Zone or Thermostat Location"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingConvergence, "HeatingConvergence", "Heating Convergence"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingConvergence, "CoolingConvergence", "Cooling Convergence"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumCyclingRate, "MaximumCyclingRate", "Maximum Cycling Rate"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatPumpTimeConstant, "HeatPumpTimeConstant", "Heat Pump Time Constant"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::FractionofOnCyclePowerUse, "FractionofOnCyclePowerUse", "Fraction of On-Cycle Power Use"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatPumpFanDelayTime, "HeatPumpFanDelayTime", "Heat Pump Fan Delay Time"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplementalHeatingCoilObjectType, "SupplementalHeatingCoilObjectType", "Supplemental Heating Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "MaximumSupplyAirTemperaturefromSupplementalHeater", "Maximum Supply Air Temperature from Supplemental Heater"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::OutdoorDryBulbTemperatureSensorNodeName, "OutdoorDryBulbTemperatureSensorNodeName", "Outdoor Dry-Bulb Temperature Sensor Node Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatPumpCoilWaterFlowMode, "HeatPumpCoilWaterFlowMode", "Heat Pump Coil Water Flow Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_UnitaryHeatPump_WaterToAirFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields> OptionalAirLoopHVAC_UnitaryHeatPump_WaterToAirFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATPUMP_WATERTOAIR_FIELDENUMS_HXX
