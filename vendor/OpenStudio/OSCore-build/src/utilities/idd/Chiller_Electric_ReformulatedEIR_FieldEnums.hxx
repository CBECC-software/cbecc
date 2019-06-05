/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_CHILLER_ELECTRIC_REFORMULATEDEIR_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLER_ELECTRIC_REFORMULATEDEIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Chiller_Electric_ReformulatedEIRFields
 *  \brief Enumeration of Chiller:Electric:ReformulatedEIR's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Chiller_Electric_ReformulatedEIRFields, )
#else
class Chiller_Electric_ReformulatedEIRFields: public ::EnumBase<Chiller_Electric_ReformulatedEIRFields> {
 public: 
  enum domain 
  {
Name, ReferenceCapacity, ReferenceCOP, ReferenceLeavingChilledWaterTemperature, ReferenceLeavingCondenserWaterTemperature, ReferenceChilledWaterFlowRate, ReferenceCondenserWaterFlowRate, CoolingCapacityFunctionofTemperatureCurveName, ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType, ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, MinimumUnloadingRatio, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, FractionofCompressorElectricConsumptionRejectedbyCondenser, LeavingChilledWaterLowerTemperatureLimit, ChillerFlowModeType, DesignHeatRecoveryWaterFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, SizingFactor, CondenserHeatRecoveryRelativeCapacityFraction, HeatRecoveryInletHighTemperatureLimitScheduleName, HeatRecoveryLeavingTemperatureSetpointNodeName, EndUseSubcategory,   };
  Chiller_Electric_ReformulatedEIRFields()
   : EnumBase<Chiller_Electric_ReformulatedEIRFields>(Name) {} 
  Chiller_Electric_ReformulatedEIRFields(const std::string &t_name) 
   : EnumBase<Chiller_Electric_ReformulatedEIRFields>(t_name) {} 
  Chiller_Electric_ReformulatedEIRFields(int t_value) 
   : EnumBase<Chiller_Electric_ReformulatedEIRFields>(t_value) {} 
  static std::string enumName() 
  { return "Chiller_Electric_ReformulatedEIRFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Chiller_Electric_ReformulatedEIRFields>::value()); }
   private:
    friend class EnumBase<Chiller_Electric_ReformulatedEIRFields>;
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
{ Chiller_Electric_ReformulatedEIRFields::Name, "Name", "Name"},
{ Chiller_Electric_ReformulatedEIRFields::ReferenceCapacity, "ReferenceCapacity", "Reference Capacity"},
{ Chiller_Electric_ReformulatedEIRFields::ReferenceCOP, "ReferenceCOP", "Reference COP"},
{ Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingChilledWaterTemperature, "ReferenceLeavingChilledWaterTemperature", "Reference Leaving Chilled Water Temperature"},
{ Chiller_Electric_ReformulatedEIRFields::ReferenceLeavingCondenserWaterTemperature, "ReferenceLeavingCondenserWaterTemperature", "Reference Leaving Condenser Water Temperature"},
{ Chiller_Electric_ReformulatedEIRFields::ReferenceChilledWaterFlowRate, "ReferenceChilledWaterFlowRate", "Reference Chilled Water Flow Rate"},
{ Chiller_Electric_ReformulatedEIRFields::ReferenceCondenserWaterFlowRate, "ReferenceCondenserWaterFlowRate", "Reference Condenser Water Flow Rate"},
{ Chiller_Electric_ReformulatedEIRFields::CoolingCapacityFunctionofTemperatureCurveName, "CoolingCapacityFunctionofTemperatureCurveName", "Cooling Capacity Function of Temperature Curve Name"},
{ Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, "ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName", "Electric Input to Cooling Output Ratio Function of Temperature Curve Name"},
{ Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType, "ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveType", "Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Type"},
{ Chiller_Electric_ReformulatedEIRFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, "ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName", "Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name"},
{ Chiller_Electric_ReformulatedEIRFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Chiller_Electric_ReformulatedEIRFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Chiller_Electric_ReformulatedEIRFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Chiller_Electric_ReformulatedEIRFields::MinimumUnloadingRatio, "MinimumUnloadingRatio", "Minimum Unloading Ratio"},
{ Chiller_Electric_ReformulatedEIRFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ Chiller_Electric_ReformulatedEIRFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ Chiller_Electric_ReformulatedEIRFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ Chiller_Electric_ReformulatedEIRFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ Chiller_Electric_ReformulatedEIRFields::FractionofCompressorElectricConsumptionRejectedbyCondenser, "FractionofCompressorElectricConsumptionRejectedbyCondenser", "Fraction of Compressor Electric Consumption Rejected by Condenser"},
{ Chiller_Electric_ReformulatedEIRFields::LeavingChilledWaterLowerTemperatureLimit, "LeavingChilledWaterLowerTemperatureLimit", "Leaving Chilled Water Lower Temperature Limit"},
{ Chiller_Electric_ReformulatedEIRFields::ChillerFlowModeType, "ChillerFlowModeType", "Chiller Flow Mode Type"},
{ Chiller_Electric_ReformulatedEIRFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ Chiller_Electric_ReformulatedEIRFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ Chiller_Electric_ReformulatedEIRFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ Chiller_Electric_ReformulatedEIRFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ Chiller_Electric_ReformulatedEIRFields::CondenserHeatRecoveryRelativeCapacityFraction, "CondenserHeatRecoveryRelativeCapacityFraction", "Condenser Heat Recovery Relative Capacity Fraction"},
{ Chiller_Electric_ReformulatedEIRFields::HeatRecoveryInletHighTemperatureLimitScheduleName, "HeatRecoveryInletHighTemperatureLimitScheduleName", "Heat Recovery Inlet High Temperature Limit Schedule Name"},
{ Chiller_Electric_ReformulatedEIRFields::HeatRecoveryLeavingTemperatureSetpointNodeName, "HeatRecoveryLeavingTemperatureSetpointNodeName", "Heat Recovery Leaving Temperature Setpoint Node Name"},
{ Chiller_Electric_ReformulatedEIRFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const Chiller_Electric_ReformulatedEIRFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Chiller_Electric_ReformulatedEIRFields> OptionalChiller_Electric_ReformulatedEIRFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLER_ELECTRIC_REFORMULATEDEIR_FIELDENUMS_HXX
