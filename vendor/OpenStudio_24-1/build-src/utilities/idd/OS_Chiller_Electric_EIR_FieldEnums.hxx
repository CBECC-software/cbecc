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

#ifndef UTILITIES_IDD_OS_CHILLER_ELECTRIC_EIR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CHILLER_ELECTRIC_EIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Chiller_Electric_EIRFields
 *  \brief Enumeration of OS:Chiller:Electric:EIR's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Chiller_Electric_EIRFields, )
#else
class OS_Chiller_Electric_EIRFields: public ::EnumBase<OS_Chiller_Electric_EIRFields> {
 public: 
  enum domain 
  {
Handle, Name, ReferenceCapacity, ReferenceCOP, ReferenceLeavingChilledWaterTemperature, ReferenceEnteringCondenserFluidTemperature, ReferenceChilledWaterFlowRate, ReferenceCondenserFluidFlowRate, CoolingCapacityFunctionofTemperatureCurveName, ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, MinimumUnloadingRatio, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, CondenserType, CondenserFanPowerRatio, FractionofCompressorElectricConsumptionRejectedbyCondenser, LeavingChilledWaterLowerTemperatureLimit, ChillerFlowMode, DesignHeatRecoveryWaterFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, SizingFactor, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, CondenserHeatRecoveryRelativeCapacityFraction, HeatRecoveryInletHighTemperatureLimitScheduleName, HeatRecoveryLeavingTemperatureSetpointNodeName, EndUseSubcategory,   };
  OS_Chiller_Electric_EIRFields()
   : EnumBase<OS_Chiller_Electric_EIRFields>(Handle) {} 
  OS_Chiller_Electric_EIRFields(const std::string &t_name) 
   : EnumBase<OS_Chiller_Electric_EIRFields>(t_name) {} 
  OS_Chiller_Electric_EIRFields(int t_value) 
   : EnumBase<OS_Chiller_Electric_EIRFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Chiller_Electric_EIRFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Chiller_Electric_EIRFields>::value()); }
   private:
    friend class EnumBase<OS_Chiller_Electric_EIRFields>;
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
{ OS_Chiller_Electric_EIRFields::Handle, "Handle", "Handle"},
{ OS_Chiller_Electric_EIRFields::Name, "Name", "Name"},
{ OS_Chiller_Electric_EIRFields::ReferenceCapacity, "ReferenceCapacity", "Reference Capacity"},
{ OS_Chiller_Electric_EIRFields::ReferenceCOP, "ReferenceCOP", "Reference COP"},
{ OS_Chiller_Electric_EIRFields::ReferenceLeavingChilledWaterTemperature, "ReferenceLeavingChilledWaterTemperature", "Reference Leaving Chilled Water Temperature"},
{ OS_Chiller_Electric_EIRFields::ReferenceEnteringCondenserFluidTemperature, "ReferenceEnteringCondenserFluidTemperature", "Reference Entering Condenser Fluid Temperature"},
{ OS_Chiller_Electric_EIRFields::ReferenceChilledWaterFlowRate, "ReferenceChilledWaterFlowRate", "Reference Chilled Water Flow Rate"},
{ OS_Chiller_Electric_EIRFields::ReferenceCondenserFluidFlowRate, "ReferenceCondenserFluidFlowRate", "Reference Condenser Fluid Flow Rate"},
{ OS_Chiller_Electric_EIRFields::CoolingCapacityFunctionofTemperatureCurveName, "CoolingCapacityFunctionofTemperatureCurveName", "Cooling Capacity Function of Temperature Curve Name"},
{ OS_Chiller_Electric_EIRFields::ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, "ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName", "Electric Input to Cooling Output Ratio Function of Temperature Curve Name"},
{ OS_Chiller_Electric_EIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, "ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName", "Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name"},
{ OS_Chiller_Electric_EIRFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ OS_Chiller_Electric_EIRFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ OS_Chiller_Electric_EIRFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ OS_Chiller_Electric_EIRFields::MinimumUnloadingRatio, "MinimumUnloadingRatio", "Minimum Unloading Ratio"},
{ OS_Chiller_Electric_EIRFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ OS_Chiller_Electric_EIRFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ OS_Chiller_Electric_EIRFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ OS_Chiller_Electric_EIRFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ OS_Chiller_Electric_EIRFields::CondenserType, "CondenserType", "Condenser Type"},
{ OS_Chiller_Electric_EIRFields::CondenserFanPowerRatio, "CondenserFanPowerRatio", "Condenser Fan Power Ratio"},
{ OS_Chiller_Electric_EIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser, "FractionofCompressorElectricConsumptionRejectedbyCondenser", "Fraction of Compressor Electric Consumption Rejected by Condenser"},
{ OS_Chiller_Electric_EIRFields::LeavingChilledWaterLowerTemperatureLimit, "LeavingChilledWaterLowerTemperatureLimit", "Leaving Chilled Water Lower Temperature Limit"},
{ OS_Chiller_Electric_EIRFields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ OS_Chiller_Electric_EIRFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ OS_Chiller_Electric_EIRFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ OS_Chiller_Electric_EIRFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ OS_Chiller_Electric_EIRFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ OS_Chiller_Electric_EIRFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ OS_Chiller_Electric_EIRFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ OS_Chiller_Electric_EIRFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ OS_Chiller_Electric_EIRFields::CondenserHeatRecoveryRelativeCapacityFraction, "CondenserHeatRecoveryRelativeCapacityFraction", "Condenser Heat Recovery Relative Capacity Fraction"},
{ OS_Chiller_Electric_EIRFields::HeatRecoveryInletHighTemperatureLimitScheduleName, "HeatRecoveryInletHighTemperatureLimitScheduleName", "Heat Recovery Inlet High Temperature Limit Schedule Name"},
{ OS_Chiller_Electric_EIRFields::HeatRecoveryLeavingTemperatureSetpointNodeName, "HeatRecoveryLeavingTemperatureSetpointNodeName", "Heat Recovery Leaving Temperature Setpoint Node Name"},
{ OS_Chiller_Electric_EIRFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Chiller_Electric_EIRFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Chiller_Electric_EIRFields> OptionalOS_Chiller_Electric_EIRFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CHILLER_ELECTRIC_EIR_FIELDENUMS_HXX
