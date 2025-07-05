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

#ifndef UTILITIES_IDD_OS_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirConditioner_VariableRefrigerantFlowFields
 *  \brief Enumeration of OS:AirConditioner:VariableRefrigerantFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirConditioner_VariableRefrigerantFlowFields, )
#else
class OS_AirConditioner_VariableRefrigerantFlowFields: public ::EnumBase<OS_AirConditioner_VariableRefrigerantFlowFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, GrossRatedTotalCoolingCapacity, GrossRatedCoolingCOP, MinimumOutdoorTemperatureinCoolingMode, MaximumOutdoorTemperatureinCoolingMode, CoolingCapacityRatioModifierFunctionofLowTemperatureCurveName, CoolingCapacityRatioBoundaryCurveName, CoolingCapacityRatioModifierFunctionofHighTemperatureCurveName, CoolingEnergyInputRatioModifierFunctionofLowTemperatureCurveName, CoolingEnergyInputRatioBoundaryCurveName, CoolingEnergyInputRatioModifierFunctionofHighTemperatureCurveName, CoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName, CoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName, CoolingCombinationRatioCorrectionFactorCurveName, CoolingPartLoadFractionCorrelationCurveName, GrossRatedHeatingCapacity, RatedHeatingCapacitySizingRatio, RatedHeatingCOP, MinimumOutdoorTemperatureinHeatingMode, MaximumOutdoorTemperatureinHeatingMode, HeatingCapacityRatioModifierFunctionofLowTemperatureCurveName, HeatingCapacityRatioBoundaryCurveName, HeatingCapacityRatioModifierFunctionofHighTemperatureCurveName, HeatingEnergyInputRatioModifierFunctionofLowTemperatureCurveName, HeatingEnergyInputRatioBoundaryCurveName, HeatingEnergyInputRatioModifierFunctionofHighTemperatureCurveName, HeatingPerformanceCurveOutdoorTemperatureType, HeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName, HeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName, HeatingCombinationRatioCorrectionFactorCurveName, HeatingPartLoadFractionCorrelationCurveName, MinimumHeatPumpPartLoadRatio, ZoneNameforMasterThermostatLocation, MasterThermostatPriorityControlType, ThermostatPrioritySchedule, ZoneTerminalUnitList, HeatPumpWasteHeatRecovery, EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode, VerticalHeightusedforPipingCorrectionFactor, PipingCorrectionFactorforLengthinCoolingModeCurveName, PipingCorrectionFactorforHeightinCoolingModeCoefficient, EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode, PipingCorrectionFactorforLengthinHeatingModeCurveName, PipingCorrectionFactorforHeightinHeatingModeCoefficient, CrankcaseHeaterPowerperCompressor, NumberofCompressors, RatioofCompressorSizetoTotalCompressorCapacity, MaximumOutdoorDrybulbTemperatureforCrankcaseHeater, DefrostStrategy, DefrostControl, DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity, MaximumOutdoorDrybulbTemperatureforDefrostOperation, CondenserType, CondenserInletNode, CondenserOutletNode, WaterCondenserVolumeFlowRate, EvaporativeCondenserEffectiveness, EvaporativeCondenserAirFlowRate, EvaporativeCondenserPumpRatedPowerConsumption, SupplyWaterStorageTank, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingSchedule, FuelType, MinimumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode, HeatRecoveryCoolingCapacityModifierCurveName, InitialHeatRecoveryCoolingCapacityFraction, HeatRecoveryCoolingCapacityTimeConstant, HeatRecoveryCoolingEnergyModifierCurveName, InitialHeatRecoveryCoolingEnergyFraction, HeatRecoveryCoolingEnergyTimeConstant, HeatRecoveryHeatingCapacityModifierCurveName, InitialHeatRecoveryHeatingCapacityFraction, HeatRecoveryHeatingCapacityTimeConstant, HeatRecoveryHeatingEnergyModifierCurveName, InitialHeatRecoveryHeatingEnergyFraction, HeatRecoveryHeatingEnergyTimeConstant,   };
  OS_AirConditioner_VariableRefrigerantFlowFields()
   : EnumBase<OS_AirConditioner_VariableRefrigerantFlowFields>(Handle) {} 
  OS_AirConditioner_VariableRefrigerantFlowFields(const std::string &t_name) 
   : EnumBase<OS_AirConditioner_VariableRefrigerantFlowFields>(t_name) {} 
  OS_AirConditioner_VariableRefrigerantFlowFields(int t_value) 
   : EnumBase<OS_AirConditioner_VariableRefrigerantFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirConditioner_VariableRefrigerantFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirConditioner_VariableRefrigerantFlowFields>::value()); }
   private:
    friend class EnumBase<OS_AirConditioner_VariableRefrigerantFlowFields>;
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
{ OS_AirConditioner_VariableRefrigerantFlowFields::Handle, "Handle", "Handle"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::Name, "Name", "Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, "GrossRatedTotalCoolingCapacity", "Gross Rated Total Cooling Capacity"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::GrossRatedCoolingCOP, "GrossRatedCoolingCOP", "Gross Rated Cooling COP"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::MinimumOutdoorTemperatureinCoolingMode, "MinimumOutdoorTemperatureinCoolingMode", "Minimum Outdoor Temperature in Cooling Mode"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::MaximumOutdoorTemperatureinCoolingMode, "MaximumOutdoorTemperatureinCoolingMode", "Maximum Outdoor Temperature in Cooling Mode"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofLowTemperatureCurveName, "CoolingCapacityRatioModifierFunctionofLowTemperatureCurveName", "Cooling Capacity Ratio Modifier Function of Low Temperature Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioBoundaryCurveName, "CoolingCapacityRatioBoundaryCurveName", "Cooling Capacity Ratio Boundary Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofHighTemperatureCurveName, "CoolingCapacityRatioModifierFunctionofHighTemperatureCurveName", "Cooling Capacity Ratio Modifier Function of High Temperature Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofLowTemperatureCurveName, "CoolingEnergyInputRatioModifierFunctionofLowTemperatureCurveName", "Cooling Energy Input Ratio Modifier Function of Low Temperature Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioBoundaryCurveName, "CoolingEnergyInputRatioBoundaryCurveName", "Cooling Energy Input Ratio Boundary Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofHighTemperatureCurveName, "CoolingEnergyInputRatioModifierFunctionofHighTemperatureCurveName", "Cooling Energy Input Ratio Modifier Function of High Temperature Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName, "CoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName", "Cooling Energy Input Ratio Modifier Function of Low Part-Load Ratio Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName, "CoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName", "Cooling Energy Input Ratio Modifier Function of High Part-Load Ratio Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CoolingCombinationRatioCorrectionFactorCurveName, "CoolingCombinationRatioCorrectionFactorCurveName", "Cooling Combination Ratio Correction Factor Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CoolingPartLoadFractionCorrelationCurveName, "CoolingPartLoadFractionCorrelationCurveName", "Cooling Part-Load Fraction Correlation Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, "GrossRatedHeatingCapacity", "Gross Rated Heating Capacity"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, "RatedHeatingCapacitySizingRatio", "Rated Heating Capacity Sizing Ratio"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::RatedHeatingCOP, "RatedHeatingCOP", "Rated Heating COP"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::MinimumOutdoorTemperatureinHeatingMode, "MinimumOutdoorTemperatureinHeatingMode", "Minimum Outdoor Temperature in Heating Mode"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::MaximumOutdoorTemperatureinHeatingMode, "MaximumOutdoorTemperatureinHeatingMode", "Maximum Outdoor Temperature in Heating Mode"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofLowTemperatureCurveName, "HeatingCapacityRatioModifierFunctionofLowTemperatureCurveName", "Heating Capacity Ratio Modifier Function of Low Temperature Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioBoundaryCurveName, "HeatingCapacityRatioBoundaryCurveName", "Heating Capacity Ratio Boundary Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofHighTemperatureCurveName, "HeatingCapacityRatioModifierFunctionofHighTemperatureCurveName", "Heating Capacity Ratio Modifier Function of High Temperature Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofLowTemperatureCurveName, "HeatingEnergyInputRatioModifierFunctionofLowTemperatureCurveName", "Heating Energy Input Ratio Modifier Function of Low Temperature Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioBoundaryCurveName, "HeatingEnergyInputRatioBoundaryCurveName", "Heating Energy Input Ratio Boundary Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofHighTemperatureCurveName, "HeatingEnergyInputRatioModifierFunctionofHighTemperatureCurveName", "Heating Energy Input Ratio Modifier Function of High Temperature Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingPerformanceCurveOutdoorTemperatureType, "HeatingPerformanceCurveOutdoorTemperatureType", "Heating Performance Curve Outdoor Temperature Type"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName, "HeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName", "Heating Energy Input Ratio Modifier Function of Low Part-Load Ratio Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName, "HeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName", "Heating Energy Input Ratio Modifier Function of High Part-Load Ratio Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingCombinationRatioCorrectionFactorCurveName, "HeatingCombinationRatioCorrectionFactorCurveName", "Heating Combination Ratio Correction Factor Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatingPartLoadFractionCorrelationCurveName, "HeatingPartLoadFractionCorrelationCurveName", "Heating Part-Load Fraction Correlation Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::MinimumHeatPumpPartLoadRatio, "MinimumHeatPumpPartLoadRatio", "Minimum Heat Pump Part-Load Ratio"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::ZoneNameforMasterThermostatLocation, "ZoneNameforMasterThermostatLocation", "Zone Name for Master Thermostat Location"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::MasterThermostatPriorityControlType, "MasterThermostatPriorityControlType", "Master Thermostat Priority Control Type"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::ThermostatPrioritySchedule, "ThermostatPrioritySchedule", "Thermostat Priority Schedule"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitList, "ZoneTerminalUnitList", "Zone Terminal Unit List"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatPumpWasteHeatRecovery, "HeatPumpWasteHeatRecovery", "Heat Pump Waste Heat Recovery"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode, "EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode", "Equivalent Piping Length used for Piping Correction Factor in Cooling Mode"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::VerticalHeightusedforPipingCorrectionFactor, "VerticalHeightusedforPipingCorrectionFactor", "Vertical Height used for Piping Correction Factor"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinCoolingModeCurveName, "PipingCorrectionFactorforLengthinCoolingModeCurveName", "Piping Correction Factor for Length in Cooling Mode Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinCoolingModeCoefficient, "PipingCorrectionFactorforHeightinCoolingModeCoefficient", "Piping Correction Factor for Height in Cooling Mode Coefficient"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode, "EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode", "Equivalent Piping Length used for Piping Correction Factor in Heating Mode"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinHeatingModeCurveName, "PipingCorrectionFactorforLengthinHeatingModeCurveName", "Piping Correction Factor for Length in Heating Mode Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinHeatingModeCoefficient, "PipingCorrectionFactorforHeightinHeatingModeCoefficient", "Piping Correction Factor for Height in Heating Mode Coefficient"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CrankcaseHeaterPowerperCompressor, "CrankcaseHeaterPowerperCompressor", "Crankcase Heater Power per Compressor"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::NumberofCompressors, "NumberofCompressors", "Number of Compressors"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::RatioofCompressorSizetoTotalCompressorCapacity, "RatioofCompressorSizetoTotalCompressorCapacity", "Ratio of Compressor Size to Total Compressor Capacity"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::MaximumOutdoorDrybulbTemperatureforCrankcaseHeater, "MaximumOutdoorDrybulbTemperatureforCrankcaseHeater", "Maximum Outdoor Dry-bulb Temperature for Crankcase Heater"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName, "DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Modifier Function of Temperature Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::MaximumOutdoorDrybulbTemperatureforDefrostOperation, "MaximumOutdoorDrybulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-bulb Temperature for Defrost Operation"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CondenserType, "CondenserType", "Condenser Type"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CondenserInletNode, "CondenserInletNode", "Condenser Inlet Node"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::CondenserOutletNode, "CondenserOutletNode", "Condenser Outlet Node"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::WaterCondenserVolumeFlowRate, "WaterCondenserVolumeFlowRate", "Water Condenser Volume Flow Rate"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::EvaporativeCondenserAirFlowRate, "EvaporativeCondenserAirFlowRate", "Evaporative Condenser Air Flow Rate"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::EvaporativeCondenserPumpRatedPowerConsumption, "EvaporativeCondenserPumpRatedPowerConsumption", "Evaporative Condenser Pump Rated Power Consumption"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::SupplyWaterStorageTank, "SupplyWaterStorageTank", "Supply Water Storage Tank"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::BasinHeaterOperatingSchedule, "BasinHeaterOperatingSchedule", "Basin Heater Operating Schedule"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::FuelType, "FuelType", "Fuel Type"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::MinimumOutdoorTemperatureinHeatRecoveryMode, "MinimumOutdoorTemperatureinHeatRecoveryMode", "Minimum Outdoor Temperature in Heat Recovery Mode"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::MaximumOutdoorTemperatureinHeatRecoveryMode, "MaximumOutdoorTemperatureinHeatRecoveryMode", "Maximum Outdoor Temperature in Heat Recovery Mode"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityModifierCurveName, "HeatRecoveryCoolingCapacityModifierCurveName", "Heat Recovery Cooling Capacity Modifier Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingCapacityFraction, "InitialHeatRecoveryCoolingCapacityFraction", "Initial Heat Recovery Cooling Capacity Fraction"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityTimeConstant, "HeatRecoveryCoolingCapacityTimeConstant", "Heat Recovery Cooling Capacity Time Constant"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyModifierCurveName, "HeatRecoveryCoolingEnergyModifierCurveName", "Heat Recovery Cooling Energy Modifier Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingEnergyFraction, "InitialHeatRecoveryCoolingEnergyFraction", "Initial Heat Recovery Cooling Energy Fraction"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyTimeConstant, "HeatRecoveryCoolingEnergyTimeConstant", "Heat Recovery Cooling Energy Time Constant"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityModifierCurveName, "HeatRecoveryHeatingCapacityModifierCurveName", "Heat Recovery Heating Capacity Modifier Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingCapacityFraction, "InitialHeatRecoveryHeatingCapacityFraction", "Initial Heat Recovery Heating Capacity Fraction"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityTimeConstant, "HeatRecoveryHeatingCapacityTimeConstant", "Heat Recovery Heating Capacity Time Constant"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyModifierCurveName, "HeatRecoveryHeatingEnergyModifierCurveName", "Heat Recovery Heating Energy Modifier Curve Name"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingEnergyFraction, "InitialHeatRecoveryHeatingEnergyFraction", "Initial Heat Recovery Heating Energy Fraction"},
{ OS_AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyTimeConstant, "HeatRecoveryHeatingEnergyTimeConstant", "Heat Recovery Heating Energy Time Constant"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirConditioner_VariableRefrigerantFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirConditioner_VariableRefrigerantFlowFields> OptionalOS_AirConditioner_VariableRefrigerantFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
