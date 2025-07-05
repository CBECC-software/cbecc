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

#ifndef UTILITIES_IDD_OS_HEATPUMP_PLANTLOOP_EIR_HEATING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_HEATPUMP_PLANTLOOP_EIR_HEATING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_HeatPump_PlantLoop_EIR_HeatingFields
 *  \brief Enumeration of OS:HeatPump:PlantLoop:EIR:Heating's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_HeatPump_PlantLoop_EIR_HeatingFields, )
#else
class OS_HeatPump_PlantLoop_EIR_HeatingFields: public ::EnumBase<OS_HeatPump_PlantLoop_EIR_HeatingFields> {
 public: 
  enum domain 
  {
Handle, Name, LoadSideInletNodeName, LoadSideOutletNodeName, CondenserType, SourceSideInletNodeName, SourceSideOutletNodeName, CompanionHeatPumpName, LoadSideReferenceFlowRate, SourceSideReferenceFlowRate, ReferenceCapacity, ReferenceCoefficientofPerformance, SizingFactor, CapacityModifierFunctionofTemperatureCurveName, ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName, HeatingToCoolingCapacitySizingRatio, HeatPumpSizingMethod, ControlType, FlowMode, MinimumPartLoadRatio, MinimumSourceInletTemperature, MaximumSourceInletTemperature, MinimumSupplyWaterTemperatureCurveName, MaximumSupplyWaterTemperatureCurveName, DryOutdoorCorrectionFactorCurveName, MaximumOutdoorDryBulbTemperatureForDefrostOperation, HeatPumpDefrostControl, HeatPumpDefrostTimePeriodFraction, DefrostEnergyInputRatioFunctionofTemperatureCurveName, TimedEmpiricalDefrostFrequencyCurveName, TimedEmpiricalDefrostHeatLoadPenaltyCurveName, TimedEmpiricalDefrostHeatInputEnergyFractionCurveName,   };
  OS_HeatPump_PlantLoop_EIR_HeatingFields()
   : EnumBase<OS_HeatPump_PlantLoop_EIR_HeatingFields>(Handle) {} 
  OS_HeatPump_PlantLoop_EIR_HeatingFields(const std::string &t_name) 
   : EnumBase<OS_HeatPump_PlantLoop_EIR_HeatingFields>(t_name) {} 
  OS_HeatPump_PlantLoop_EIR_HeatingFields(int t_value) 
   : EnumBase<OS_HeatPump_PlantLoop_EIR_HeatingFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_HeatPump_PlantLoop_EIR_HeatingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_HeatPump_PlantLoop_EIR_HeatingFields>::value()); }
   private:
    friend class EnumBase<OS_HeatPump_PlantLoop_EIR_HeatingFields>;
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
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::Handle, "Handle", "Handle"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::Name, "Name", "Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::CondenserType, "CondenserType", "Condenser Type"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::CompanionHeatPumpName, "CompanionHeatPumpName", "Companion Heat Pump Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::LoadSideReferenceFlowRate, "LoadSideReferenceFlowRate", "Load Side Reference Flow Rate"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::SourceSideReferenceFlowRate, "SourceSideReferenceFlowRate", "Source Side Reference Flow Rate"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCapacity, "ReferenceCapacity", "Reference Capacity"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::ReferenceCoefficientofPerformance, "ReferenceCoefficientofPerformance", "Reference Coefficient of Performance"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::CapacityModifierFunctionofTemperatureCurveName, "CapacityModifierFunctionofTemperatureCurveName", "Capacity Modifier Function of Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName, "ElectricInputtoOutputRatioModifierFunctionofTemperatureCurveName", "Electric Input to Output Ratio Modifier Function of Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName, "ElectricInputtoOutputRatioModifierFunctionofPartLoadRatioCurveName", "Electric Input to Output Ratio Modifier Function of Part Load Ratio Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::HeatingToCoolingCapacitySizingRatio, "HeatingToCoolingCapacitySizingRatio", "Heating To Cooling Capacity Sizing Ratio"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpSizingMethod, "HeatPumpSizingMethod", "Heat Pump Sizing Method"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::ControlType, "ControlType", "Control Type"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::FlowMode, "FlowMode", "Flow Mode"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::MinimumSourceInletTemperature, "MinimumSourceInletTemperature", "Minimum Source Inlet Temperature"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::MaximumSourceInletTemperature, "MaximumSourceInletTemperature", "Maximum Source Inlet Temperature"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::MinimumSupplyWaterTemperatureCurveName, "MinimumSupplyWaterTemperatureCurveName", "Minimum Supply Water Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::MaximumSupplyWaterTemperatureCurveName, "MaximumSupplyWaterTemperatureCurveName", "Maximum Supply Water Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::DryOutdoorCorrectionFactorCurveName, "DryOutdoorCorrectionFactorCurveName", "Dry Outdoor Correction Factor Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::MaximumOutdoorDryBulbTemperatureForDefrostOperation, "MaximumOutdoorDryBulbTemperatureForDefrostOperation", "Maximum Outdoor Dry Bulb Temperature For Defrost Operation"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostControl, "HeatPumpDefrostControl", "Heat Pump Defrost Control"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::HeatPumpDefrostTimePeriodFraction, "HeatPumpDefrostTimePeriodFraction", "Heat Pump Defrost Time Period Fraction"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::DefrostEnergyInputRatioFunctionofTemperatureCurveName, "DefrostEnergyInputRatioFunctionofTemperatureCurveName", "Defrost Energy Input Ratio Function of Temperature Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostFrequencyCurveName, "TimedEmpiricalDefrostFrequencyCurveName", "Timed Empirical Defrost Frequency Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostHeatLoadPenaltyCurveName, "TimedEmpiricalDefrostHeatLoadPenaltyCurveName", "Timed Empirical Defrost Heat Load Penalty Curve Name"},
{ OS_HeatPump_PlantLoop_EIR_HeatingFields::TimedEmpiricalDefrostHeatInputEnergyFractionCurveName, "TimedEmpiricalDefrostHeatInputEnergyFractionCurveName", "Timed Empirical Defrost Heat Input Energy Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_HeatPump_PlantLoop_EIR_HeatingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_HeatPump_PlantLoop_EIR_HeatingFields> OptionalOS_HeatPump_PlantLoop_EIR_HeatingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_HEATPUMP_PLANTLOOP_EIR_HEATING_FIELDENUMS_HXX
