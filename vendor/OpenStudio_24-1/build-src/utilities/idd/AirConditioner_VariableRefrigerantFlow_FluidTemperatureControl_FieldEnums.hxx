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
Name, AvailabilityScheduleName, ZoneTerminalUnitListName, RefrigerantType, RatedEvaporativeCapacity, RatedCompressorPowerPerUnitofRatedEvaporativeCapacity, MinimumOutdoorAirTemperatureinCoolingMode, MaximumOutdoorAirTemperatureinCoolingMode, MinimumOutdoorAirTemperatureinHeatingMode, MaximumOutdoorAirTemperatureinHeatingMode, ReferenceOutdoorUnitSuperheating, ReferenceOutdoorUnitSubcooling, RefrigerantTemperatureControlAlgorithmforIndoorUnit, ReferenceEvaporatingTemperatureforIndoorUnit, ReferenceCondensingTemperatureforIndoorUnit, VariableEvaporatingTemperatureMinimumforIndoorUnit, VariableEvaporatingTemperatureMaximumforIndoorUnit, VariableCondensingTemperatureMinimumforIndoorUnit, VariableCondensingTemperatureMaximumforIndoorUnit, OutdoorUnitFanPowerPerUnitofRatedEvaporativeCapacity, OutdoorUnitFanFlowRatePerUnitofRatedEvaporativeCapacity, OutdoorUnitEvaporatingTemperatureFunctionofSuperheatingCurveName, OutdoorUnitCondensingTemperatureFunctionofSubcoolingCurveName, DiameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, HeightDifferenceBetweenOutdoorUnitandIndoorUnits, MainPipeInsulationThickness, MainPipeInsulationThermalConductivity, CrankcaseHeaterPowerperCompressor, NumberofCompressors, RatioofCompressorSizetoTotalCompressorCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeater, DefrostStrategy, DefrostControl, DefrostEnergyInputRatioModifierFunctionofTemperatureCurveName, DefrostTimePeriodFraction, ResistiveDefrostHeaterCapacity, MaximumOutdoorDrybulbTemperatureforDefrostOperation, CompressormaximumdeltaPressure, NumberofCompressorLoadingIndexEntries,   };
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields()
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields>(Name) {} 
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
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::Name, "Name", "Name"},
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
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::DiameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, "DiameterofMainPipeConnectingOutdoorUnittotheFirstBranchJoint", "Diameter of Main Pipe Connecting Outdoor Unit to the First Branch Joint"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, "LengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint", "Length of Main Pipe Connecting Outdoor Unit to the First Branch Joint"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlFields::EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint, "EquivalentLengthofMainPipeConnectingOutdoorUnittotheFirstBranchJoint", "Equivalent Length of Main Pipe Connecting Outdoor Unit to the First Branch Joint"},
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

/** \class AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields
 *  \brief Enumeration of AirConditioner:VariableRefrigerantFlow:FluidTemperatureControl's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields, )
#else
class AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields: public ::EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields> {
 public: 
  enum domain 
  {
CompressorSpeedatLoadingIndex, LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName, LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName,   };
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields()
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields>(CompressorSpeedatLoadingIndex) {} 
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields(const std::string &t_name) 
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields>(t_name) {} 
  AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields(int t_value) 
   : EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields>::value()); }
   private:
    friend class EnumBase<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields>;
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
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::CompressorSpeedatLoadingIndex, "CompressorSpeedatLoadingIndex", "Compressor Speed at Loading Index"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName, "LoadingIndexEvaporativeCapacityMultiplierFunctionofTemperatureCurveName", "Loading Index Evaporative Capacity Multiplier Function of Temperature Curve Name"},
{ AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields::LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName, "LoadingIndexCompressorPowerMultiplierFunctionofTemperatureCurveName", "Loading Index Compressor Power Multiplier Function of Temperature Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields> OptionalAirConditioner_VariableRefrigerantFlow_FluidTemperatureControlExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRCONDITIONER_VARIABLEREFRIGERANTFLOW_FLUIDTEMPERATURECONTROL_FIELDENUMS_HXX
