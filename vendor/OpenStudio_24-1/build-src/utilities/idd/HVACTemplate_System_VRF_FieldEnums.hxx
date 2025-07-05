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

#ifndef UTILITIES_IDD_HVACTEMPLATE_SYSTEM_VRF_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_SYSTEM_VRF_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_System_VRFFields
 *  \brief Enumeration of HVACTemplate:System:VRF's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_System_VRFFields, )
#else
class HVACTemplate_System_VRFFields: public ::EnumBase<HVACTemplate_System_VRFFields> {
 public: 
  enum domain 
  {
Name, SystemAvailabilityScheduleName, GrossRatedTotalCoolingCapacity, GrossRatedCoolingCOP, MinimumOutdoorTemperatureinCoolingMode, MaximumOutdoorTemperatureinCoolingMode, GrossRatedHeatingCapacity, RatedHeatingCapacitySizingRatio, GrossRatedHeatingCOP, MinimumOutdoorTemperatureinHeatingMode, MaximumOutdoorTemperatureinHeatingMode, MinimumHeatPumpPartLoadRatio, ZoneNameforMasterThermostatLocation, MasterThermostatPriorityControlType, ThermostatPriorityScheduleName, HeatPumpWasteHeatRecovery, EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode, VerticalHeightusedforPipingCorrectionFactor, EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode, CrankcaseHeaterPowerperCompressor, NumberofCompressors, RatioofCompressorSizetoTotalCompressorCapacity, MaximumOutdoorDrybulbTemperatureforCrankcaseHeater, DefrostStrategy, DefrostControl, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity, MaximumOutdoorDrybulbTemperatureforDefrostOperation, CondenserType, WaterCondenserVolumeFlowRate, EvaporativeCondenserEffectiveness, EvaporativeCondenserAirFlowRate, EvaporativeCondenserPumpRatedPowerConsumption, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, FuelType, MinimumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode,   };
  HVACTemplate_System_VRFFields()
   : EnumBase<HVACTemplate_System_VRFFields>(Name) {} 
  HVACTemplate_System_VRFFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_System_VRFFields>(t_name) {} 
  HVACTemplate_System_VRFFields(int t_value) 
   : EnumBase<HVACTemplate_System_VRFFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_System_VRFFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_System_VRFFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_System_VRFFields>;
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
{ HVACTemplate_System_VRFFields::Name, "Name", "Name"},
{ HVACTemplate_System_VRFFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_System_VRFFields::GrossRatedTotalCoolingCapacity, "GrossRatedTotalCoolingCapacity", "Gross Rated Total Cooling Capacity"},
{ HVACTemplate_System_VRFFields::GrossRatedCoolingCOP, "GrossRatedCoolingCOP", "Gross Rated Cooling COP"},
{ HVACTemplate_System_VRFFields::MinimumOutdoorTemperatureinCoolingMode, "MinimumOutdoorTemperatureinCoolingMode", "Minimum Outdoor Temperature in Cooling Mode"},
{ HVACTemplate_System_VRFFields::MaximumOutdoorTemperatureinCoolingMode, "MaximumOutdoorTemperatureinCoolingMode", "Maximum Outdoor Temperature in Cooling Mode"},
{ HVACTemplate_System_VRFFields::GrossRatedHeatingCapacity, "GrossRatedHeatingCapacity", "Gross Rated Heating Capacity"},
{ HVACTemplate_System_VRFFields::RatedHeatingCapacitySizingRatio, "RatedHeatingCapacitySizingRatio", "Rated Heating Capacity Sizing Ratio"},
{ HVACTemplate_System_VRFFields::GrossRatedHeatingCOP, "GrossRatedHeatingCOP", "Gross Rated Heating COP"},
{ HVACTemplate_System_VRFFields::MinimumOutdoorTemperatureinHeatingMode, "MinimumOutdoorTemperatureinHeatingMode", "Minimum Outdoor Temperature in Heating Mode"},
{ HVACTemplate_System_VRFFields::MaximumOutdoorTemperatureinHeatingMode, "MaximumOutdoorTemperatureinHeatingMode", "Maximum Outdoor Temperature in Heating Mode"},
{ HVACTemplate_System_VRFFields::MinimumHeatPumpPartLoadRatio, "MinimumHeatPumpPartLoadRatio", "Minimum Heat Pump Part-Load Ratio"},
{ HVACTemplate_System_VRFFields::ZoneNameforMasterThermostatLocation, "ZoneNameforMasterThermostatLocation", "Zone Name for Master Thermostat Location"},
{ HVACTemplate_System_VRFFields::MasterThermostatPriorityControlType, "MasterThermostatPriorityControlType", "Master Thermostat Priority Control Type"},
{ HVACTemplate_System_VRFFields::ThermostatPriorityScheduleName, "ThermostatPriorityScheduleName", "Thermostat Priority Schedule Name"},
{ HVACTemplate_System_VRFFields::HeatPumpWasteHeatRecovery, "HeatPumpWasteHeatRecovery", "Heat Pump Waste Heat Recovery"},
{ HVACTemplate_System_VRFFields::EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode, "EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode", "Equivalent Piping Length used for Piping Correction Factor in Cooling Mode"},
{ HVACTemplate_System_VRFFields::VerticalHeightusedforPipingCorrectionFactor, "VerticalHeightusedforPipingCorrectionFactor", "Vertical Height used for Piping Correction Factor"},
{ HVACTemplate_System_VRFFields::EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode, "EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode", "Equivalent Piping Length used for Piping Correction Factor in Heating Mode"},
{ HVACTemplate_System_VRFFields::CrankcaseHeaterPowerperCompressor, "CrankcaseHeaterPowerperCompressor", "Crankcase Heater Power per Compressor"},
{ HVACTemplate_System_VRFFields::NumberofCompressors, "NumberofCompressors", "Number of Compressors"},
{ HVACTemplate_System_VRFFields::RatioofCompressorSizetoTotalCompressorCapacity, "RatioofCompressorSizetoTotalCompressorCapacity", "Ratio of Compressor Size to Total Compressor Capacity"},
{ HVACTemplate_System_VRFFields::MaximumOutdoorDrybulbTemperatureforCrankcaseHeater, "MaximumOutdoorDrybulbTemperatureforCrankcaseHeater", "Maximum Outdoor Dry-bulb Temperature for Crankcase Heater"},
{ HVACTemplate_System_VRFFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ HVACTemplate_System_VRFFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ HVACTemplate_System_VRFFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ HVACTemplate_System_VRFFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
{ HVACTemplate_System_VRFFields::MaximumOutdoorDrybulbTemperatureforDefrostOperation, "MaximumOutdoorDrybulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-bulb Temperature for Defrost Operation"},
{ HVACTemplate_System_VRFFields::CondenserType, "CondenserType", "Condenser Type"},
{ HVACTemplate_System_VRFFields::WaterCondenserVolumeFlowRate, "WaterCondenserVolumeFlowRate", "Water Condenser Volume Flow Rate"},
{ HVACTemplate_System_VRFFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ HVACTemplate_System_VRFFields::EvaporativeCondenserAirFlowRate, "EvaporativeCondenserAirFlowRate", "Evaporative Condenser Air Flow Rate"},
{ HVACTemplate_System_VRFFields::EvaporativeCondenserPumpRatedPowerConsumption, "EvaporativeCondenserPumpRatedPowerConsumption", "Evaporative Condenser Pump Rated Power Consumption"},
{ HVACTemplate_System_VRFFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ HVACTemplate_System_VRFFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ HVACTemplate_System_VRFFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ HVACTemplate_System_VRFFields::FuelType, "FuelType", "Fuel Type"},
{ HVACTemplate_System_VRFFields::MinimumOutdoorTemperatureinHeatRecoveryMode, "MinimumOutdoorTemperatureinHeatRecoveryMode", "Minimum Outdoor Temperature in Heat Recovery Mode"},
{ HVACTemplate_System_VRFFields::MaximumOutdoorTemperatureinHeatRecoveryMode, "MaximumOutdoorTemperatureinHeatRecoveryMode", "Maximum Outdoor Temperature in Heat Recovery Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_System_VRFFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_System_VRFFields> OptionalHVACTemplate_System_VRFFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_SYSTEM_VRF_FIELDENUMS_HXX
