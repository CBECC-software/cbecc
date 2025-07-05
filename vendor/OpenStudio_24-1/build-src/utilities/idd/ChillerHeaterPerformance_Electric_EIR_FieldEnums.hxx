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

#ifndef UTILITIES_IDD_CHILLERHEATERPERFORMANCE_ELECTRIC_EIR_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLERHEATERPERFORMANCE_ELECTRIC_EIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ChillerHeaterPerformance_Electric_EIRFields
 *  \brief Enumeration of ChillerHeaterPerformance:Electric:EIR's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ChillerHeaterPerformance_Electric_EIRFields, )
#else
class ChillerHeaterPerformance_Electric_EIRFields: public ::EnumBase<ChillerHeaterPerformance_Electric_EIRFields> {
 public: 
  enum domain 
  {
Name, ReferenceCoolingModeEvaporatorCapacity, ReferenceCoolingModeCOP, ReferenceCoolingModeLeavingChilledWaterTemperature, ReferenceCoolingModeEnteringCondenserFluidTemperature, ReferenceCoolingModeLeavingCondenserWaterTemperature, ReferenceHeatingModeCoolingCapacityRatio, ReferenceHeatingModeCoolingPowerInputRatio, ReferenceHeatingModeLeavingChilledWaterTemperature, ReferenceHeatingModeLeavingCondenserWaterTemperature, ReferenceHeatingModeEnteringCondenserFluidTemperature, HeatingModeEnteringChilledWaterTemperatureLowLimit, ChilledWaterFlowModeType, DesignChilledWaterFlowRate, DesignCondenserWaterFlowRate, DesignHotWaterFlowRate, CompressorMotorEfficiency, CondenserType, CoolingModeTemperatureCurveCondenserWaterIndependentVariable, CoolingModeCoolingCapacityFunctionofTemperatureCurveName, CoolingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, CoolingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, CoolingModeCoolingCapacityOptimumPartLoadRatio, HeatingModeTemperatureCurveCondenserWaterIndependentVariable, HeatingModeCoolingCapacityFunctionofTemperatureCurveName, HeatingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, HeatingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, HeatingModeCoolingCapacityOptimumPartLoadRatio, SizingFactor,   };
  ChillerHeaterPerformance_Electric_EIRFields()
   : EnumBase<ChillerHeaterPerformance_Electric_EIRFields>(Name) {} 
  ChillerHeaterPerformance_Electric_EIRFields(const std::string &t_name) 
   : EnumBase<ChillerHeaterPerformance_Electric_EIRFields>(t_name) {} 
  ChillerHeaterPerformance_Electric_EIRFields(int t_value) 
   : EnumBase<ChillerHeaterPerformance_Electric_EIRFields>(t_value) {} 
  static std::string enumName() 
  { return "ChillerHeaterPerformance_Electric_EIRFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ChillerHeaterPerformance_Electric_EIRFields>::value()); }
   private:
    friend class EnumBase<ChillerHeaterPerformance_Electric_EIRFields>;
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
{ ChillerHeaterPerformance_Electric_EIRFields::Name, "Name", "Name"},
{ ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeEvaporatorCapacity, "ReferenceCoolingModeEvaporatorCapacity", "Reference Cooling Mode Evaporator Capacity"},
{ ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeCOP, "ReferenceCoolingModeCOP", "Reference Cooling Mode COP"},
{ ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeLeavingChilledWaterTemperature, "ReferenceCoolingModeLeavingChilledWaterTemperature", "Reference Cooling Mode Leaving Chilled Water Temperature"},
{ ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeEnteringCondenserFluidTemperature, "ReferenceCoolingModeEnteringCondenserFluidTemperature", "Reference Cooling Mode Entering Condenser Fluid Temperature"},
{ ChillerHeaterPerformance_Electric_EIRFields::ReferenceCoolingModeLeavingCondenserWaterTemperature, "ReferenceCoolingModeLeavingCondenserWaterTemperature", "Reference Cooling Mode Leaving Condenser Water Temperature"},
{ ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeCoolingCapacityRatio, "ReferenceHeatingModeCoolingCapacityRatio", "Reference Heating Mode Cooling Capacity Ratio"},
{ ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeCoolingPowerInputRatio, "ReferenceHeatingModeCoolingPowerInputRatio", "Reference Heating Mode Cooling Power Input Ratio"},
{ ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeLeavingChilledWaterTemperature, "ReferenceHeatingModeLeavingChilledWaterTemperature", "Reference Heating Mode Leaving Chilled Water Temperature"},
{ ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeLeavingCondenserWaterTemperature, "ReferenceHeatingModeLeavingCondenserWaterTemperature", "Reference Heating Mode Leaving Condenser Water Temperature"},
{ ChillerHeaterPerformance_Electric_EIRFields::ReferenceHeatingModeEnteringCondenserFluidTemperature, "ReferenceHeatingModeEnteringCondenserFluidTemperature", "Reference Heating Mode Entering Condenser Fluid Temperature"},
{ ChillerHeaterPerformance_Electric_EIRFields::HeatingModeEnteringChilledWaterTemperatureLowLimit, "HeatingModeEnteringChilledWaterTemperatureLowLimit", "Heating Mode Entering Chilled Water Temperature Low Limit"},
{ ChillerHeaterPerformance_Electric_EIRFields::ChilledWaterFlowModeType, "ChilledWaterFlowModeType", "Chilled Water Flow Mode Type"},
{ ChillerHeaterPerformance_Electric_EIRFields::DesignChilledWaterFlowRate, "DesignChilledWaterFlowRate", "Design Chilled Water Flow Rate"},
{ ChillerHeaterPerformance_Electric_EIRFields::DesignCondenserWaterFlowRate, "DesignCondenserWaterFlowRate", "Design Condenser Water Flow Rate"},
{ ChillerHeaterPerformance_Electric_EIRFields::DesignHotWaterFlowRate, "DesignHotWaterFlowRate", "Design Hot Water Flow Rate"},
{ ChillerHeaterPerformance_Electric_EIRFields::CompressorMotorEfficiency, "CompressorMotorEfficiency", "Compressor Motor Efficiency"},
{ ChillerHeaterPerformance_Electric_EIRFields::CondenserType, "CondenserType", "Condenser Type"},
{ ChillerHeaterPerformance_Electric_EIRFields::CoolingModeTemperatureCurveCondenserWaterIndependentVariable, "CoolingModeTemperatureCurveCondenserWaterIndependentVariable", "Cooling Mode Temperature Curve Condenser Water Independent Variable"},
{ ChillerHeaterPerformance_Electric_EIRFields::CoolingModeCoolingCapacityFunctionofTemperatureCurveName, "CoolingModeCoolingCapacityFunctionofTemperatureCurveName", "Cooling Mode Cooling Capacity Function of Temperature Curve Name"},
{ ChillerHeaterPerformance_Electric_EIRFields::CoolingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, "CoolingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName", "Cooling Mode Electric Input to Cooling Output Ratio Function of Temperature Curve Name"},
{ ChillerHeaterPerformance_Electric_EIRFields::CoolingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, "CoolingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName", "Cooling Mode Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name"},
{ ChillerHeaterPerformance_Electric_EIRFields::CoolingModeCoolingCapacityOptimumPartLoadRatio, "CoolingModeCoolingCapacityOptimumPartLoadRatio", "Cooling Mode Cooling Capacity Optimum Part Load Ratio"},
{ ChillerHeaterPerformance_Electric_EIRFields::HeatingModeTemperatureCurveCondenserWaterIndependentVariable, "HeatingModeTemperatureCurveCondenserWaterIndependentVariable", "Heating Mode Temperature Curve Condenser Water Independent Variable"},
{ ChillerHeaterPerformance_Electric_EIRFields::HeatingModeCoolingCapacityFunctionofTemperatureCurveName, "HeatingModeCoolingCapacityFunctionofTemperatureCurveName", "Heating Mode Cooling Capacity Function of Temperature Curve Name"},
{ ChillerHeaterPerformance_Electric_EIRFields::HeatingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, "HeatingModeElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName", "Heating Mode Electric Input to Cooling Output Ratio Function of Temperature Curve Name"},
{ ChillerHeaterPerformance_Electric_EIRFields::HeatingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, "HeatingModeElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName", "Heating Mode Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name"},
{ ChillerHeaterPerformance_Electric_EIRFields::HeatingModeCoolingCapacityOptimumPartLoadRatio, "HeatingModeCoolingCapacityOptimumPartLoadRatio", "Heating Mode Cooling Capacity Optimum Part Load Ratio"},
{ ChillerHeaterPerformance_Electric_EIRFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const ChillerHeaterPerformance_Electric_EIRFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ChillerHeaterPerformance_Electric_EIRFields> OptionalChillerHeaterPerformance_Electric_EIRFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLERHEATERPERFORMANCE_ELECTRIC_EIR_FIELDENUMS_HXX
