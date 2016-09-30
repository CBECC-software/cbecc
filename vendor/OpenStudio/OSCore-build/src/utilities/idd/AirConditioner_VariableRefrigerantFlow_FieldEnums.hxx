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

#ifndef UTILITIES_IDD_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirConditioner_VariableRefrigerantFlowFields
 *  \brief Enumeration of AirConditioner:VariableRefrigerantFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirConditioner_VariableRefrigerantFlowFields, )
#else
class AirConditioner_VariableRefrigerantFlowFields: public ::EnumBase<AirConditioner_VariableRefrigerantFlowFields> {
 public: 
  enum domain 
  {
HeatPumpName, AvailabilityScheduleName, GrossRatedTotalCoolingCapacity, GrossRatedCoolingCOP, MinimumOutdoorTemperatureinCoolingMode, MaximumOutdoorTemperatureinCoolingMode, CoolingCapacityRatioModifierFunctionofLowTemperatureCurveName, CoolingCapacityRatioBoundaryCurveName, CoolingCapacityRatioModifierFunctionofHighTemperatureCurveName, CoolingEnergyInputRatioModifierFunctionofLowTemperatureCurveName, CoolingEnergyInputRatioBoundaryCurveName, CoolingEnergyInputRatioModifierFunctionofHighTemperatureCurveName, CoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName, CoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName, CoolingCombinationRatioCorrectionFactorCurveName, CoolingPartLoadFractionCorrelationCurveName, GrossRatedHeatingCapacity, RatedHeatingCapacitySizingRatio, GrossRatedHeatingCOP, MinimumOutdoorTemperatureinHeatingMode, MaximumOutdoorTemperatureinHeatingMode, HeatingCapacityRatioModifierFunctionofLowTemperatureCurveName, HeatingCapacityRatioBoundaryCurveName, HeatingCapacityRatioModifierFunctionofHighTemperatureCurveName, HeatingEnergyInputRatioModifierFunctionofLowTemperatureCurveName, HeatingEnergyInputRatioBoundaryCurveName, HeatingEnergyInputRatioModifierFunctionofHighTemperatureCurveName, HeatingPerformanceCurveOutdoorTemperatureType, HeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName, HeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName, HeatingCombinationRatioCorrectionFactorCurveName, HeatingPartLoadFractionCorrelationCurveName, MinimumHeatPumpPartLoadRatio, ZoneNameforMasterThermostatLocation, MasterThermostatPriorityControlType, ThermostatPriorityScheduleName, ZoneTerminalUnitListName, HeatPumpWasteHeatRecovery, EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode, VerticalHeightusedforPipingCorrectionFactor, PipingCorrectionFactorforLengthinCoolingModeCurveName, PipingCorrectionFactorforHeightinCoolingModeCoefficient, EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode, PipingCorrectionFactorforLengthinHeatingModeCurveName, PipingCorrectionFactorforHeightinHeatingModeCoefficient, CrankcaseHeaterPowerperCompressor, NumberofCompressors, RatioofCompressorSizetoTotalCompressorCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeater, DefrostStrategy, DefrostControl, DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity, MaximumOutdoorDrybulbTemperatureforDefrostOperation, CondenserType, CondenserInletNodeName, CondenserOutletNodeName, WaterCondenserVolumeFlowRate, EvaporativeCondenserEffectiveness, EvaporativeCondenserAirFlowRate, EvaporativeCondenserPumpRatedPowerConsumption, SupplyWaterStorageTankName, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, FuelType, MinimumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode, HeatRecoveryCoolingCapacityModifierCurveName, InitialHeatRecoveryCoolingCapacityFraction, HeatRecoveryCoolingCapacityTimeConstant, HeatRecoveryCoolingEnergyModifierCurveName, InitialHeatRecoveryCoolingEnergyFraction, HeatRecoveryCoolingEnergyTimeConstant, HeatRecoveryHeatingCapacityModifierCurveName, InitialHeatRecoveryHeatingCapacityFraction, HeatRecoveryHeatingCapacityTimeConstant, HeatRecoveryHeatingEnergyModifierCurveName, InitialHeatRecoveryHeatingEnergyFraction, HeatRecoveryHeatingEnergyTimeConstant,   };
  AirConditioner_VariableRefrigerantFlowFields()
   : EnumBase<AirConditioner_VariableRefrigerantFlowFields>(HeatPumpName) {} 
  AirConditioner_VariableRefrigerantFlowFields(const std::string &t_name) 
   : EnumBase<AirConditioner_VariableRefrigerantFlowFields>(t_name) {} 
  AirConditioner_VariableRefrigerantFlowFields(int t_value) 
   : EnumBase<AirConditioner_VariableRefrigerantFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "AirConditioner_VariableRefrigerantFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirConditioner_VariableRefrigerantFlowFields>::value()); }
   private:
    friend class EnumBase<AirConditioner_VariableRefrigerantFlowFields>;
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
{ AirConditioner_VariableRefrigerantFlowFields::HeatPumpName, "HeatPumpName", "Heat Pump Name"},
{ AirConditioner_VariableRefrigerantFlowFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirConditioner_VariableRefrigerantFlowFields::GrossRatedTotalCoolingCapacity, "GrossRatedTotalCoolingCapacity", "Gross Rated Total Cooling Capacity"},
{ AirConditioner_VariableRefrigerantFlowFields::GrossRatedCoolingCOP, "GrossRatedCoolingCOP", "Gross Rated Cooling COP"},
{ AirConditioner_VariableRefrigerantFlowFields::MinimumOutdoorTemperatureinCoolingMode, "MinimumOutdoorTemperatureinCoolingMode", "Minimum Outdoor Temperature in Cooling Mode"},
{ AirConditioner_VariableRefrigerantFlowFields::MaximumOutdoorTemperatureinCoolingMode, "MaximumOutdoorTemperatureinCoolingMode", "Maximum Outdoor Temperature in Cooling Mode"},
{ AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofLowTemperatureCurveName, "CoolingCapacityRatioModifierFunctionofLowTemperatureCurveName", "Cooling Capacity Ratio Modifier Function of Low Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioBoundaryCurveName, "CoolingCapacityRatioBoundaryCurveName", "Cooling Capacity Ratio Boundary Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofHighTemperatureCurveName, "CoolingCapacityRatioModifierFunctionofHighTemperatureCurveName", "Cooling Capacity Ratio Modifier Function of High Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofLowTemperatureCurveName, "CoolingEnergyInputRatioModifierFunctionofLowTemperatureCurveName", "Cooling Energy Input Ratio Modifier Function of Low Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioBoundaryCurveName, "CoolingEnergyInputRatioBoundaryCurveName", "Cooling Energy Input Ratio Boundary Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofHighTemperatureCurveName, "CoolingEnergyInputRatioModifierFunctionofHighTemperatureCurveName", "Cooling Energy Input Ratio Modifier Function of High Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName, "CoolingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName", "Cooling Energy Input Ratio Modifier Function of Low Part-Load Ratio Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::CoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName, "CoolingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName", "Cooling Energy Input Ratio Modifier Function of High Part-Load Ratio Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::CoolingCombinationRatioCorrectionFactorCurveName, "CoolingCombinationRatioCorrectionFactorCurveName", "Cooling Combination Ratio Correction Factor Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::CoolingPartLoadFractionCorrelationCurveName, "CoolingPartLoadFractionCorrelationCurveName", "Cooling Part-Load Fraction Correlation Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCapacity, "GrossRatedHeatingCapacity", "Gross Rated Heating Capacity"},
{ AirConditioner_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, "RatedHeatingCapacitySizingRatio", "Rated Heating Capacity Sizing Ratio"},
{ AirConditioner_VariableRefrigerantFlowFields::GrossRatedHeatingCOP, "GrossRatedHeatingCOP", "Gross Rated Heating COP"},
{ AirConditioner_VariableRefrigerantFlowFields::MinimumOutdoorTemperatureinHeatingMode, "MinimumOutdoorTemperatureinHeatingMode", "Minimum Outdoor Temperature in Heating Mode"},
{ AirConditioner_VariableRefrigerantFlowFields::MaximumOutdoorTemperatureinHeatingMode, "MaximumOutdoorTemperatureinHeatingMode", "Maximum Outdoor Temperature in Heating Mode"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofLowTemperatureCurveName, "HeatingCapacityRatioModifierFunctionofLowTemperatureCurveName", "Heating Capacity Ratio Modifier Function of Low Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioBoundaryCurveName, "HeatingCapacityRatioBoundaryCurveName", "Heating Capacity Ratio Boundary Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingCapacityRatioModifierFunctionofHighTemperatureCurveName, "HeatingCapacityRatioModifierFunctionofHighTemperatureCurveName", "Heating Capacity Ratio Modifier Function of High Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofLowTemperatureCurveName, "HeatingEnergyInputRatioModifierFunctionofLowTemperatureCurveName", "Heating Energy Input Ratio Modifier Function of Low Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioBoundaryCurveName, "HeatingEnergyInputRatioBoundaryCurveName", "Heating Energy Input Ratio Boundary Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofHighTemperatureCurveName, "HeatingEnergyInputRatioModifierFunctionofHighTemperatureCurveName", "Heating Energy Input Ratio Modifier Function of High Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingPerformanceCurveOutdoorTemperatureType, "HeatingPerformanceCurveOutdoorTemperatureType", "Heating Performance Curve Outdoor Temperature Type"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName, "HeatingEnergyInputRatioModifierFunctionofLowPartLoadRatioCurveName", "Heating Energy Input Ratio Modifier Function of Low Part-Load Ratio Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName, "HeatingEnergyInputRatioModifierFunctionofHighPartLoadRatioCurveName", "Heating Energy Input Ratio Modifier Function of High Part-Load Ratio Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingCombinationRatioCorrectionFactorCurveName, "HeatingCombinationRatioCorrectionFactorCurveName", "Heating Combination Ratio Correction Factor Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatingPartLoadFractionCorrelationCurveName, "HeatingPartLoadFractionCorrelationCurveName", "Heating Part-Load Fraction Correlation Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::MinimumHeatPumpPartLoadRatio, "MinimumHeatPumpPartLoadRatio", "Minimum Heat Pump Part-Load Ratio"},
{ AirConditioner_VariableRefrigerantFlowFields::ZoneNameforMasterThermostatLocation, "ZoneNameforMasterThermostatLocation", "Zone Name for Master Thermostat Location"},
{ AirConditioner_VariableRefrigerantFlowFields::MasterThermostatPriorityControlType, "MasterThermostatPriorityControlType", "Master Thermostat Priority Control Type"},
{ AirConditioner_VariableRefrigerantFlowFields::ThermostatPriorityScheduleName, "ThermostatPriorityScheduleName", "Thermostat Priority Schedule Name"},
{ AirConditioner_VariableRefrigerantFlowFields::ZoneTerminalUnitListName, "ZoneTerminalUnitListName", "Zone Terminal Unit List Name"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatPumpWasteHeatRecovery, "HeatPumpWasteHeatRecovery", "Heat Pump Waste Heat Recovery"},
{ AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode, "EquivalentPipingLengthusedforPipingCorrectionFactorinCoolingMode", "Equivalent Piping Length used for Piping Correction Factor in Cooling Mode"},
{ AirConditioner_VariableRefrigerantFlowFields::VerticalHeightusedforPipingCorrectionFactor, "VerticalHeightusedforPipingCorrectionFactor", "Vertical Height used for Piping Correction Factor"},
{ AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinCoolingModeCurveName, "PipingCorrectionFactorforLengthinCoolingModeCurveName", "Piping Correction Factor for Length in Cooling Mode Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinCoolingModeCoefficient, "PipingCorrectionFactorforHeightinCoolingModeCoefficient", "Piping Correction Factor for Height in Cooling Mode Coefficient"},
{ AirConditioner_VariableRefrigerantFlowFields::EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode, "EquivalentPipingLengthusedforPipingCorrectionFactorinHeatingMode", "Equivalent Piping Length used for Piping Correction Factor in Heating Mode"},
{ AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforLengthinHeatingModeCurveName, "PipingCorrectionFactorforLengthinHeatingModeCurveName", "Piping Correction Factor for Length in Heating Mode Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::PipingCorrectionFactorforHeightinHeatingModeCoefficient, "PipingCorrectionFactorforHeightinHeatingModeCoefficient", "Piping Correction Factor for Height in Heating Mode Coefficient"},
{ AirConditioner_VariableRefrigerantFlowFields::CrankcaseHeaterPowerperCompressor, "CrankcaseHeaterPowerperCompressor", "Crankcase Heater Power per Compressor"},
{ AirConditioner_VariableRefrigerantFlowFields::NumberofCompressors, "NumberofCompressors", "Number of Compressors"},
{ AirConditioner_VariableRefrigerantFlowFields::RatioofCompressorSizetoTotalCompressorCapacity, "RatioofCompressorSizetoTotalCompressorCapacity", "Ratio of Compressor Size to Total Compressor Capacity"},
{ AirConditioner_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeater, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeater", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater"},
{ AirConditioner_VariableRefrigerantFlowFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ AirConditioner_VariableRefrigerantFlowFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ AirConditioner_VariableRefrigerantFlowFields::DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName, "DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Modifier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ AirConditioner_VariableRefrigerantFlowFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
{ AirConditioner_VariableRefrigerantFlowFields::MaximumOutdoorDrybulbTemperatureforDefrostOperation, "MaximumOutdoorDrybulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-bulb Temperature for Defrost Operation"},
{ AirConditioner_VariableRefrigerantFlowFields::CondenserType, "CondenserType", "Condenser Type"},
{ AirConditioner_VariableRefrigerantFlowFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ AirConditioner_VariableRefrigerantFlowFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ AirConditioner_VariableRefrigerantFlowFields::WaterCondenserVolumeFlowRate, "WaterCondenserVolumeFlowRate", "Water Condenser Volume Flow Rate"},
{ AirConditioner_VariableRefrigerantFlowFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ AirConditioner_VariableRefrigerantFlowFields::EvaporativeCondenserAirFlowRate, "EvaporativeCondenserAirFlowRate", "Evaporative Condenser Air Flow Rate"},
{ AirConditioner_VariableRefrigerantFlowFields::EvaporativeCondenserPumpRatedPowerConsumption, "EvaporativeCondenserPumpRatedPowerConsumption", "Evaporative Condenser Pump Rated Power Consumption"},
{ AirConditioner_VariableRefrigerantFlowFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ AirConditioner_VariableRefrigerantFlowFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ AirConditioner_VariableRefrigerantFlowFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ AirConditioner_VariableRefrigerantFlowFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ AirConditioner_VariableRefrigerantFlowFields::FuelType, "FuelType", "Fuel Type"},
{ AirConditioner_VariableRefrigerantFlowFields::MinimumOutdoorTemperatureinHeatRecoveryMode, "MinimumOutdoorTemperatureinHeatRecoveryMode", "Minimum Outdoor Temperature in Heat Recovery Mode"},
{ AirConditioner_VariableRefrigerantFlowFields::MaximumOutdoorTemperatureinHeatRecoveryMode, "MaximumOutdoorTemperatureinHeatRecoveryMode", "Maximum Outdoor Temperature in Heat Recovery Mode"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityModifierCurveName, "HeatRecoveryCoolingCapacityModifierCurveName", "Heat Recovery Cooling Capacity Modifier Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingCapacityFraction, "InitialHeatRecoveryCoolingCapacityFraction", "Initial Heat Recovery Cooling Capacity Fraction"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingCapacityTimeConstant, "HeatRecoveryCoolingCapacityTimeConstant", "Heat Recovery Cooling Capacity Time Constant"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyModifierCurveName, "HeatRecoveryCoolingEnergyModifierCurveName", "Heat Recovery Cooling Energy Modifier Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryCoolingEnergyFraction, "InitialHeatRecoveryCoolingEnergyFraction", "Initial Heat Recovery Cooling Energy Fraction"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryCoolingEnergyTimeConstant, "HeatRecoveryCoolingEnergyTimeConstant", "Heat Recovery Cooling Energy Time Constant"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityModifierCurveName, "HeatRecoveryHeatingCapacityModifierCurveName", "Heat Recovery Heating Capacity Modifier Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingCapacityFraction, "InitialHeatRecoveryHeatingCapacityFraction", "Initial Heat Recovery Heating Capacity Fraction"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingCapacityTimeConstant, "HeatRecoveryHeatingCapacityTimeConstant", "Heat Recovery Heating Capacity Time Constant"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyModifierCurveName, "HeatRecoveryHeatingEnergyModifierCurveName", "Heat Recovery Heating Energy Modifier Curve Name"},
{ AirConditioner_VariableRefrigerantFlowFields::InitialHeatRecoveryHeatingEnergyFraction, "InitialHeatRecoveryHeatingEnergyFraction", "Initial Heat Recovery Heating Energy Fraction"},
{ AirConditioner_VariableRefrigerantFlowFields::HeatRecoveryHeatingEnergyTimeConstant, "HeatRecoveryHeatingEnergyTimeConstant", "Heat Recovery Heating Energy Time Constant"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirConditioner_VariableRefrigerantFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirConditioner_VariableRefrigerantFlowFields> OptionalAirConditioner_VariableRefrigerantFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
