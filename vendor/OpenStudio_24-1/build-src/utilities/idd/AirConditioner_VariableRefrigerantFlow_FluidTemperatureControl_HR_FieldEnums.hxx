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

#ifndef UTILITIES_IDD_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_HR_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_HR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields
 *  \brief Enumeration of AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields, )
#else
class AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields: public ::EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneTerminalUnitListName, RefrigerantType, RatedEvaporativeCapacity, RatedCompressorPowerPerUnitofRatedEvaporativeCapacity, MinimumOutdoorAirTemperatureinCoolingOnlyMode, MaximumOutdoorAirTemperatureinCoolingOnlyMode, MinimumOutdoorAirTemperatureinHeatingOnlyMode, MaximumOutdoorAirTemperatureinHeatingOnlyMode, MinimumOutdoorTemperatureinHeatRecoveryMode, MaximumOutdoorTemperatureinHeatRecoveryMode, RefrigerantTemperatureControlAlgorithmforIndoorUnit, ReferenceEvaporatingTemperatureforIndoorUnit, ReferenceCondensingTemperatureforIndoorUnit, VariableEvaporatingTemperatureMinimumforIndoorUnit, VariableEvaporatingTemperatureMaximumforIndoorUnit, VariableCondensingTemperatureMinimumforIndoorUnit, VariableCondensingTemperatureMaximumforIndoorUnit, OutdoorUnitEvaporatorReferenceSuperheating, OutdoorUnitCondenserReferenceSubcooling, OutdoorUnitEvaporatorRatedBypassFactor, OutdoorUnitCondenserRatedBypassFactor, DifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode, OutdoorUnitHeatExchangerCapacityRatio, OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity, OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity, OutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName, OutdoorUnitCondensingTemperatureFunctionofSubcoolingCurveName, DiameterofMainPipeforSuctionGas, DiameterofMainPipeforDischargeGas, LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, HeightDifferenceBetweenOutdoorUnitandIndoorUnits, MainPipeInsulationThickness, MainPipeInsulationThermalConductivity, CrankcaseHeaterPowerperCompressor, NumberofCompressors, RatioofCompressorSizetoTotalCompressorCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeater, DefrostStrategy, DefrostControl, DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity, MaximumOutdoorDrybulbTemperatureforDefrostOperation, InitialHeatRecoveryCoolingCapacityFraction, HeatRecoveryCoolingCapacityTimeConstant, InitialHeatRecoveryCoolingEnergyFraction, HeatRecoveryCoolingEnergyTimeConstant, InitialHeatRecoveryHeatingCapacityFraction, HeatRecoveryHeatingCapacityTimeConstant, InitialHeatRecoveryHeatingEnergyFraction, HeatRecoveryHeatingEnergyTimeConstant, CompressormaximumdeltaPressure, CompressorInverterEfficiency, CompressorEvaporativeCapacityCorrectionFactor, NumberofCompressorLoadingIndexEntries,   };
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields()
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields>(Name) {} 
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields(const std::string &t_name) 
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields>(t_name) {} 
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields(int t_value) 
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields>(t_value) {} 
  static std::string enumName() 
  { return "AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields>::value()); }
   private:
    friend class EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields>;
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
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::Name, "Name", "Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::ZoneTerminalUnitListName, "ZoneTerminalUnitListName", "Zone Terminal Unit List Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RefrigerantType, "RefrigerantType", "Refrigerant Type"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RatedEvaporativeCapacity, "RatedEvaporativeCapacity", "Rated Evaporative Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RatedCompressorPowerPerUnitofRatedEvaporativeCapacity, "RatedCompressorPowerPerUnitofRatedEvaporativeCapacity", "Rated Compressor Power Per Unit of Rated Evaporative Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::MinimumOutdoorAirTemperatureinCoolingOnlyMode, "MinimumOutdoorAirTemperatureinCoolingOnlyMode", "Minimum Outdoor Air Temperature in Cooling Only Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::MaximumOutdoorAirTemperatureinCoolingOnlyMode, "MaximumOutdoorAirTemperatureinCoolingOnlyMode", "Maximum Outdoor Air Temperature in Cooling Only Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::MinimumOutdoorAirTemperatureinHeatingOnlyMode, "MinimumOutdoorAirTemperatureinHeatingOnlyMode", "Minimum Outdoor Air Temperature in Heating Only Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::MaximumOutdoorAirTemperatureinHeatingOnlyMode, "MaximumOutdoorAirTemperatureinHeatingOnlyMode", "Maximum Outdoor Air Temperature in Heating Only Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::MinimumOutdoorTemperatureinHeatRecoveryMode, "MinimumOutdoorTemperatureinHeatRecoveryMode", "Minimum Outdoor Temperature in Heat Recovery Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::MaximumOutdoorTemperatureinHeatRecoveryMode, "MaximumOutdoorTemperatureinHeatRecoveryMode", "Maximum Outdoor Temperature in Heat Recovery Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RefrigerantTemperatureControlAlgorithmforIndoorUnit, "RefrigerantTemperatureControlAlgorithmforIndoorUnit", "Refrigerant Temperature Control Algorithm for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::ReferenceEvaporatingTemperatureforIndoorUnit, "ReferenceEvaporatingTemperatureforIndoorUnit", "Reference Evaporating Temperature for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::ReferenceCondensingTemperatureforIndoorUnit, "ReferenceCondensingTemperatureforIndoorUnit", "Reference Condensing Temperature for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::VariableEvaporatingTemperatureMinimumforIndoorUnit, "VariableEvaporatingTemperatureMinimumforIndoorUnit", "Variable Evaporating Temperature Minimum for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::VariableEvaporatingTemperatureMaximumforIndoorUnit, "VariableEvaporatingTemperatureMaximumforIndoorUnit", "Variable Evaporating Temperature Maximum for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::VariableCondensingTemperatureMinimumforIndoorUnit, "VariableCondensingTemperatureMinimumforIndoorUnit", "Variable Condensing Temperature Minimum for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::VariableCondensingTemperatureMaximumforIndoorUnit, "VariableCondensingTemperatureMaximumforIndoorUnit", "Variable Condensing Temperature Maximum for Indoor Unit"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::OutdoorUnitEvaporatorReferenceSuperheating, "OutdoorUnitEvaporatorReferenceSuperheating", "Outdoor Unit Evaporator Reference Superheating"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::OutdoorUnitCondenserReferenceSubcooling, "OutdoorUnitCondenserReferenceSubcooling", "Outdoor Unit Condenser Reference Subcooling"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::OutdoorUnitEvaporatorRatedBypassFactor, "OutdoorUnitEvaporatorRatedBypassFactor", "Outdoor Unit Evaporator Rated Bypass Factor"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::OutdoorUnitCondenserRatedBypassFactor, "OutdoorUnitCondenserRatedBypassFactor", "Outdoor Unit Condenser Rated Bypass Factor"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode, "DifferencebetweenOutdoorUnitEvaporatingTemperatureandOutdoorAirTemperatureinHeatRecoveryMode", "Difference between Outdoor Unit Evaporating Temperature and Outdoor Air Temperature in Heat Recovery Mode"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::OutdoorUnitHeatExchangerCapacityRatio, "OutdoorUnitHeatExchangerCapacityRatio", "Outdoor Unit Heat Exchanger Capacity Ratio"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity, "OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity", "Outdoor Unit Fan Power Per Unit of Rated Evaporative Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity, "OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity", "Outdoor Unit Fan Flow Rate Per Unit of Rated Evaporative Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::OutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName, "OutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName", "Outdoor Unit Evaporating Temperature Function of Superheating Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::OutdoorUnitCondensingTemperatureFunctionofSubcoolingCurveName, "OutdoorUnitCondensingTemperatureFunctionofSubcoolingCurveName", "Outdoor Unit Condensing Temperature Function of Subcooling Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DiameterofMainPipeforSuctionGas, "DiameterofMainPipeforSuctionGas", "Diameter of Main Pipe for Suction Gas"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DiameterofMainPipeforDischargeGas, "DiameterofMainPipeforDischargeGas", "Diameter of Main Pipe for Discharge Gas"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, "LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint", "Length of Main Pipe Connecting Outdoor Unit to the First Branch Joint"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, "EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint", "Equivalent Length of Main Pipe Connecting Outdoor Unit to the First Branch Joint"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::HeightDifferenceBetweenOutdoorUnitandIndoorUnits, "HeightDifferenceBetweenOutdoorUnitandIndoorUnits", "Height Difference Between Outdoor Unit and Indoor Units"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::MainPipeInsulationThickness, "MainPipeInsulationThickness", "Main Pipe Insulation Thickness"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::MainPipeInsulationThermalConductivity, "MainPipeInsulationThermalConductivity", "Main Pipe Insulation Thermal Conductivity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::CrankcaseHeaterPowerperCompressor, "CrankcaseHeaterPowerperCompressor", "Crankcase Heater Power per Compressor"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::NumberofCompressors, "NumberofCompressors", "Number of Compressors"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::RatioofCompressorSizetoTotalCompressorCapacity, "RatioofCompressorSizetoTotalCompressorCapacity", "Ratio of Compressor Size to Total Compressor Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeater, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeater", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DefrostStrategy, "DefrostStrategy", "Defrost Strategy"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DefrostControl, "DefrostControl", "Defrost Control"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName, "DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Modifier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::DefrostTimePeriodFraction, "DefrostTimePeriodFraction", "Defrost Time Period Fraction"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::ResistiveDefrostHeaterCapacity, "ResistiveDefrostHeaterCapacity", "Resistive Defrost Heater Capacity"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::MaximumOutdoorDrybulbTemperatureforDefrostOperation, "MaximumOutdoorDrybulbTemperatureforDefrostOperation", "Maximum Outdoor Dry-bulb Temperature for Defrost Operation"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::InitialHeatRecoveryCoolingCapacityFraction, "InitialHeatRecoveryCoolingCapacityFraction", "Initial Heat Recovery Cooling Capacity Fraction"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::HeatRecoveryCoolingCapacityTimeConstant, "HeatRecoveryCoolingCapacityTimeConstant", "Heat Recovery Cooling Capacity Time Constant"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::InitialHeatRecoveryCoolingEnergyFraction, "InitialHeatRecoveryCoolingEnergyFraction", "Initial Heat Recovery Cooling Energy Fraction"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::HeatRecoveryCoolingEnergyTimeConstant, "HeatRecoveryCoolingEnergyTimeConstant", "Heat Recovery Cooling Energy Time Constant"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::InitialHeatRecoveryHeatingCapacityFraction, "InitialHeatRecoveryHeatingCapacityFraction", "Initial Heat Recovery Heating Capacity Fraction"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::HeatRecoveryHeatingCapacityTimeConstant, "HeatRecoveryHeatingCapacityTimeConstant", "Heat Recovery Heating Capacity Time Constant"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::InitialHeatRecoveryHeatingEnergyFraction, "InitialHeatRecoveryHeatingEnergyFraction", "Initial Heat Recovery Heating Energy Fraction"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::HeatRecoveryHeatingEnergyTimeConstant, "HeatRecoveryHeatingEnergyTimeConstant", "Heat Recovery Heating Energy Time Constant"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::CompressormaximumdeltaPressure, "CompressormaximumdeltaPressure", "Compressor maximum delta Pressure"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::CompressorInverterEfficiency, "CompressorInverterEfficiency", "Compressor Inverter Efficiency"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::CompressorEvaporativeCapacityCorrectionFactor, "CompressorEvaporativeCapacityCorrectionFactor", "Compressor Evaporative Capacity Correction Factor"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields::NumberofCompressorLoadingIndexEntries, "NumberofCompressorLoadingIndexEntries", "Number of Compressor Loading Index Entries"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields> OptionalAirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRFields ;
#endif

/** \class AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields
 *  \brief Enumeration of AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl:HR's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields, )
#else
class AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields: public ::EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields> {
 public: 
  enum domain 
  {
CompressorSpeedatLoadingIndex, LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName,   };
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields()
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields>(CompressorSpeedatLoadingIndex) {} 
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields(const std::string &t_name) 
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields>(t_name) {} 
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields(int t_value) 
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields>;
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
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields::CompressorSpeedatLoadingIndex, "CompressorSpeedatLoadingIndex", "Compressor Speed at Loading Index"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields::LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields::LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName, "LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName", "Loading Index Compressor Power Multiplier Function of Temperature Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields> OptionalAirConditioner_VariableRefrigerantFlow_FluidTemperatureControl_HRExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_HR_FIELDENUMS_HXX
