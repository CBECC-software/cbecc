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

#ifndef UTILITIES_IDD_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields
 *  \brief Enumeration of AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields, )
#else
class AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields: public ::EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields> {
 public: 
  enum domain 
  {
HeatPumpName, AvailabilityScheduleName, ZoneTerminalUnitListName, RefrigerantType, RatedEvaporativeCapacity, RatedCompressorPowerPerUnitofRatedEvaporativeCapacity, MinimumOutdoorAirTemperatureinCoolingMode, MaximumOutdoorAirTemperatureinCoolingMode, MinimumOutdoorAirTemperatureinHeatingMode, MaximumOutdoorAirTemperatureinHeatingMode, ReferenceOutdoorUnitSuperheating, ReferenceOutdoorUnitSubcooling, RefrigerantTemperatureControlAlgorithmforIndoorUnit, ReferenceEvaporatingTemperatureforIndoorUnit, ReferenceCondensingTemperatureforIndoorUnit, VariableEvaporatingTemperatureMinimumforIndoorUnit, VariableEvaporatingTemperatureMaximumforIndoorUnit, VariableCondensingTemperatureMinimumforIndoorUnit, VariableCondensingTemperatureMaximumforIndoorUnit, OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity, OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity, OutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName, OutdoorUnitCondensingTemperatureFunctionofSubcoolingCurveName, DiameterofMainPipeConnectingOutdoorUnittoIndoorUnits, LengthofMainPipeConnectingOutdoorUnittoIndoorUnits, EquivalentLengthofMainPipeConnectingOutdoorUnittoIndoorUnits, HeightDifferenceBetweenOutdoorUnitandIndoorUnits, MainPipeInsulationThickness, MainPipeInsulationThermalConductivity, CrankcaseHeaterPowerperCompressor, NumberofCompressors, RatioofCompressorSizetoTotalCompressorCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeater, DefrostStrategy, DefrostControl, DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity, MaximumOutdoorDrybulbTemperatureforDefrostOperation, CompressormaximumdeltaPressure, NumberofCompressorLoadingIndexEntries, CompressorSpeedatLoadingIndex1, LoadingIndex1EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndex1CompressorPowerMultiplierFunctionofTemperatureCurveName, CompressorSpeedatLoadingIndex2, LoadingIndex2EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndex2CompressorPowerMultiplierFunctionofTemperatureCurveName, CompressorSpeedatLoadingIndex3, LoadingIndex3EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndex3CompressorPowerMultiplierFunctionofTemperatureCurveName, CompressorSpeedatLoadingIndex4, LoadingIndex4EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndex4CompressorPowerMultiplierFunctionofTemperatureCurveName, CompressorSpeedatLoadingIndex5, LoadingIndex5EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndex5CompressorPowerMultiplierFunctionofTemperatureCurveName, CompressorSpeedatLoadingIndex6, LoadingIndex6EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndex6CompressorPowerMultiplierFunctionofTemperatureCurveName, CompressorSpeedatLoadingIndex7, LoadingIndex7EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndex7list, CompressorSpeedatLoadingIndex8, LoadingIndex8EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndex8CompressorPowerMultiplierFunctionofTemperatureCurveName, CompressorSpeedatLoadingIndex9, LoadingIndex9EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndex9CompressorPowerMultiplierFunctionofTemperatureCurveName,   };
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields()
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields>(HeatPumpName) {} 
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields(const std::string &t_name) 
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields>(t_name) {} 
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields(int t_value) 
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields>(t_value) {} 
  static std::string enumName() 
  { return "AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields>::value()); }
   private:
    friend class EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields>;
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
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::HeatPumpName, "HeatPumpName", "Heat Pump Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ZoneTerminalUnitListName, "ZoneTerminalUnitListName", "Zone Terminal Unit List Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RefrigerantType, "RefrigerantType", "Refrigerant Type"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedEvaporativeCapacity, "RatedEvaporativeCapacity", "Rated Evaporative Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatedCompressorPowerPerUnitofRatedEvaporativeCapacity, "RatedCompressorPowerPerUnitofRatedEvaporativeCapacity", "Rated Compressor Power Per Unit of Rated Evaporative Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MinimumOutdoorAirTemperatureinCoolingMode, "MinimumOutdoorAirTemperatureinCoolingMode", "Minimum Outdoor Air Temperature in Cooling Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorAirTemperatureinCoolingMode, "MaximumOutdoorAirTemperatureinCoolingMode", "Maximum Outdoor Air Temperature in Cooling Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MinimumOutdoorAirTemperatureinHeatingMode, "MinimumOutdoorAirTemperatureinHeatingMode", "Minimum Outdoor Air Temperature in Heating Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorAirTemperatureinHeatingMode, "MaximumOutdoorAirTemperatureinHeatingMode", "Maximum Outdoor Air Temperature in Heating Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceOutdoorUnitSuperheating, "ReferenceOutdoorUnitSuperheating", "Reference Outdoor Unit Superheating"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceOutdoorUnitSubcooling, "ReferenceOutdoorUnitSubcooling", "Reference Outdoor Unit Subcooling"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RefrigerantTemperatureControlAlgorithmforIndoorUnit, "RefrigerantTemperatureControlAlgorithmforIndoorUnit", "Refrigerant Temperature Control Algorithm for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceEvaporatingTemperatureforIndoorUnit, "ReferenceEvaporatingTemperatureforIndoorUnit", "Reference Evaporating Temperature for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ReferenceCondensingTemperatureforIndoorUnit, "ReferenceCondensingTemperatureforIndoorUnit", "Reference Condensing Temperature for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableEvaporatingTemperatureMinimumforIndoorUnit, "VariableEvaporatingTemperatureMinimumforIndoorUnit", "Variable Evaporating Temperature Minimum for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableEvaporatingTemperatureMaximumforIndoorUnit, "VariableEvaporatingTemperatureMaximumforIndoorUnit", "Variable Evaporating Temperature Maximum for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableCondensingTemperatureMinimumforIndoorUnit, "VariableCondensingTemperatureMinimumforIndoorUnit", "Variable Condensing Temperature Minimum for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::VariableCondensingTemperatureMaximumforIndoorUnit, "VariableCondensingTemperatureMaximumforIndoorUnit", "Variable Condensing Temperature Maximum for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity, "OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity", "Outdoor Unit Fan Power Per Unit of Rated Evaporative Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity, "OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity", "Outdoor Unit Fan Flow Rate Per Unit of Rated Evaporative Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::OutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName, "OutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName", "Outdoor Unit Evaporating Temperature Function of Superheating Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::OutdoorUnitCondensingTemperatureFunctionofSubcoolingCurveName, "OutdoorUnitCondensingTemperatureFunctionofSubcoolingCurveName", "Outdoor Unit Condensing Temperature Function of Subcooling Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DiameterofMainPipeConnectingOutdoorUnittoIndoorUnits, "DiameterofMainPipeConnectingOutdoorUnittoIndoorUnits", "Diameter of Main Pipe Connecting Outdoor Unit to Indoor Units"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LengthofMainPipeConnectingOutdoorUnittoIndoorUnits, "LengthofMainPipeConnectingOutdoorUnittoIndoorUnits", "Length of Main Pipe Connecting Outdoor Unit to Indoor Units"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::EquivalentLengthofMainPipeConnectingOutdoorUnittoIndoorUnits, "EquivalentLengthofMainPipeConnectingOutdoorUnittoIndoorUnits", "Equivalent Length of Main Pipe Connecting Outdoor Unit to Indoor Units"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::HeightDifferenceBetweenOutdoorUnitandIndoorUnits, "HeightDifferenceBetweenOutdoorUnitandIndoorUnits", "Height Difference Between Outdoor Unit and Indoor Units"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MainPipeInsulationThickness, "MainPipeInsulationThickness", "Main Pipe Insulation Thickness"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MainPipeInsulationThermalConductivity, "MainPipeInsulationThermalConductivity", "Main Pipe Insulation Thermal Conductivity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CrankcaseHeaterPowerperCompressor, "CrankcaseHeaterPowerperCompressor", "Crankcase Heater Power per Compressor"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::NumberofCompressors, "NumberofCompressors", "Number of Compressors"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::RatioofCompressorSizetoTotalCompressorCapacity, "RatioofCompressorSizetoTotalCompressorCapacity", "Ratio of Compressor Size to Total Compressor Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeater, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeater", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName, "DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Modifier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::MaximumOutdoorDrybulbTemperatureforDefrostOperation, "MaximumOutdoorDrybulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-bulb Temperature for Defrost Operation"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressormaximumdeltaPressure, "CompressormaximumdeltaPressure", "Compressor maximum delta Pressure"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::NumberofCompressorLoadingIndexEntries, "NumberofCompressorLoadingIndexEntries", "Number of Compressor Loading Index Entries"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressorSpeedatLoadingIndex1, "CompressorSpeedatLoadingIndex1", "Compressor Speed at Loading Index 1"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex1EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndex1EvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index 1 Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex1CompressorPowerMultiplierFunctionofTemperatureCurveName, "LoadingIndex1CompressorPowerMultiplierFunctionofTemperatureCurveName", "Loading Index 1 Compressor Power Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressorSpeedatLoadingIndex2, "CompressorSpeedatLoadingIndex2", "Compressor Speed at Loading Index 2"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex2EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndex2EvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index 2 Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex2CompressorPowerMultiplierFunctionofTemperatureCurveName, "LoadingIndex2CompressorPowerMultiplierFunctionofTemperatureCurveName", "Loading Index 2 Compressor Power Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressorSpeedatLoadingIndex3, "CompressorSpeedatLoadingIndex3", "Compressor Speed at Loading Index 3"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex3EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndex3EvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index 3 Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex3CompressorPowerMultiplierFunctionofTemperatureCurveName, "LoadingIndex3CompressorPowerMultiplierFunctionofTemperatureCurveName", "Loading Index 3 Compressor Power Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressorSpeedatLoadingIndex4, "CompressorSpeedatLoadingIndex4", "Compressor Speed at Loading Index 4"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex4EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndex4EvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index 4 Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex4CompressorPowerMultiplierFunctionofTemperatureCurveName, "LoadingIndex4CompressorPowerMultiplierFunctionofTemperatureCurveName", "Loading Index 4 Compressor Power Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressorSpeedatLoadingIndex5, "CompressorSpeedatLoadingIndex5", "Compressor Speed at Loading Index 5"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex5EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndex5EvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index 5 Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex5CompressorPowerMultiplierFunctionofTemperatureCurveName, "LoadingIndex5CompressorPowerMultiplierFunctionofTemperatureCurveName", "Loading Index 5 Compressor Power Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressorSpeedatLoadingIndex6, "CompressorSpeedatLoadingIndex6", "Compressor Speed at Loading Index 6"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex6EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndex6EvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index 6 Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex6CompressorPowerMultiplierFunctionofTemperatureCurveName, "LoadingIndex6CompressorPowerMultiplierFunctionofTemperatureCurveName", "Loading Index 6 Compressor Power Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressorSpeedatLoadingIndex7, "CompressorSpeedatLoadingIndex7", "Compressor Speed at Loading Index 7"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex7EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndex7EvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index 7 Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex7list, "LoadingIndex7list", "Loading Index 7 list"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressorSpeedatLoadingIndex8, "CompressorSpeedatLoadingIndex8", "Compressor Speed at Loading Index 8"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex8EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndex8EvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index 8 Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex8CompressorPowerMultiplierFunctionofTemperatureCurveName, "LoadingIndex8CompressorPowerMultiplierFunctionofTemperatureCurveName", "Loading Index 8 Compressor Power Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::CompressorSpeedatLoadingIndex9, "CompressorSpeedatLoadingIndex9", "Compressor Speed at Loading Index 9"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex9EvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndex9EvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index 9 Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LoadingIndex9CompressorPowerMultiplierFunctionofTemperatureCurveName, "LoadingIndex9CompressorPowerMultiplierFunctionofTemperatureCurveName", "Loading Index 9 Compressor Power Multiplier Function of Temperature Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields> OptionalAirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_FIELDENUMS_HXX
