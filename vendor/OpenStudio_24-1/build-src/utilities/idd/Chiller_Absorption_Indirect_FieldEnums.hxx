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

#ifndef UTILITIES_IDD_CHILLER_ABSORPTION_INDIRECT_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLER_ABSORPTION_INDIRECT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Chiller_Absorption_IndirectFields
 *  \brief Enumeration of Chiller:Absorption:Indirect's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Chiller_Absorption_IndirectFields, )
#else
class Chiller_Absorption_IndirectFields: public ::EnumBase<Chiller_Absorption_IndirectFields> {
 public: 
  enum domain 
  {
Name, NominalCapacity, NominalPumpingPower, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, DesignCondenserInletTemperature, CondenserInletTemperatureLowerLimit, ChilledWaterOutletTemperatureLowerLimit, DesignChilledWaterFlowRate, DesignCondenserWaterFlowRate, ChillerFlowMode, GeneratorHeatInputFunctionofPartLoadRatioCurveName, PumpElectricInputFunctionofPartLoadRatioCurveName, GeneratorInletNodeName, GeneratorOutletNodeName, CapacityCorrectionFunctionofCondenserTemperatureCurveName, CapacityCorrectionFunctionofChilledWaterTemperatureCurveName, CapacityCorrectionFunctionofGeneratorTemperatureCurveName, GeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurveName, GeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurveName, GeneratorHeatSourceType, DesignGeneratorFluidFlowRate, TemperatureLowerLimitGeneratorInlet, DegreeofSubcoolinginSteamGenerator, DegreeofSubcoolinginSteamCondensateLoop, SizingFactor,   };
  Chiller_Absorption_IndirectFields()
   : EnumBase<Chiller_Absorption_IndirectFields>(Name) {} 
  Chiller_Absorption_IndirectFields(const std::string &t_name) 
   : EnumBase<Chiller_Absorption_IndirectFields>(t_name) {} 
  Chiller_Absorption_IndirectFields(int t_value) 
   : EnumBase<Chiller_Absorption_IndirectFields>(t_value) {} 
  static std::string enumName() 
  { return "Chiller_Absorption_IndirectFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Chiller_Absorption_IndirectFields>::value()); }
   private:
    friend class EnumBase<Chiller_Absorption_IndirectFields>;
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
{ Chiller_Absorption_IndirectFields::Name, "Name", "Name"},
{ Chiller_Absorption_IndirectFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Chiller_Absorption_IndirectFields::NominalPumpingPower, "NominalPumpingPower", "Nominal Pumping Power"},
{ Chiller_Absorption_IndirectFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ Chiller_Absorption_IndirectFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ Chiller_Absorption_IndirectFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ Chiller_Absorption_IndirectFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ Chiller_Absorption_IndirectFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Chiller_Absorption_IndirectFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Chiller_Absorption_IndirectFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Chiller_Absorption_IndirectFields::DesignCondenserInletTemperature, "DesignCondenserInletTemperature", "Design Condenser Inlet Temperature"},
{ Chiller_Absorption_IndirectFields::CondenserInletTemperatureLowerLimit, "CondenserInletTemperatureLowerLimit", "Condenser Inlet Temperature Lower Limit"},
{ Chiller_Absorption_IndirectFields::ChilledWaterOutletTemperatureLowerLimit, "ChilledWaterOutletTemperatureLowerLimit", "Chilled Water Outlet Temperature Lower Limit"},
{ Chiller_Absorption_IndirectFields::DesignChilledWaterFlowRate, "DesignChilledWaterFlowRate", "Design Chilled Water Flow Rate"},
{ Chiller_Absorption_IndirectFields::DesignCondenserWaterFlowRate, "DesignCondenserWaterFlowRate", "Design Condenser Water Flow Rate"},
{ Chiller_Absorption_IndirectFields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ Chiller_Absorption_IndirectFields::GeneratorHeatInputFunctionofPartLoadRatioCurveName, "GeneratorHeatInputFunctionofPartLoadRatioCurveName", "Generator Heat Input Function of Part Load Ratio Curve Name"},
{ Chiller_Absorption_IndirectFields::PumpElectricInputFunctionofPartLoadRatioCurveName, "PumpElectricInputFunctionofPartLoadRatioCurveName", "Pump Electric Input Function of Part Load Ratio Curve Name"},
{ Chiller_Absorption_IndirectFields::GeneratorInletNodeName, "GeneratorInletNodeName", "Generator Inlet Node Name"},
{ Chiller_Absorption_IndirectFields::GeneratorOutletNodeName, "GeneratorOutletNodeName", "Generator Outlet Node Name"},
{ Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofCondenserTemperatureCurveName, "CapacityCorrectionFunctionofCondenserTemperatureCurveName", "Capacity Correction Function of Condenser Temperature Curve Name"},
{ Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofChilledWaterTemperatureCurveName, "CapacityCorrectionFunctionofChilledWaterTemperatureCurveName", "Capacity Correction Function of Chilled Water Temperature Curve Name"},
{ Chiller_Absorption_IndirectFields::CapacityCorrectionFunctionofGeneratorTemperatureCurveName, "CapacityCorrectionFunctionofGeneratorTemperatureCurveName", "Capacity Correction Function of Generator Temperature Curve Name"},
{ Chiller_Absorption_IndirectFields::GeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurveName, "GeneratorHeatInputCorrectionFunctionofCondenserTemperatureCurveName", "Generator Heat Input Correction Function of Condenser Temperature Curve Name"},
{ Chiller_Absorption_IndirectFields::GeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurveName, "GeneratorHeatInputCorrectionFunctionofChilledWaterTemperatureCurveName", "Generator Heat Input Correction Function of Chilled Water Temperature Curve Name"},
{ Chiller_Absorption_IndirectFields::GeneratorHeatSourceType, "GeneratorHeatSourceType", "Generator Heat Source Type"},
{ Chiller_Absorption_IndirectFields::DesignGeneratorFluidFlowRate, "DesignGeneratorFluidFlowRate", "Design Generator Fluid Flow Rate"},
{ Chiller_Absorption_IndirectFields::TemperatureLowerLimitGeneratorInlet, "TemperatureLowerLimitGeneratorInlet", "Temperature Lower Limit Generator Inlet"},
{ Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamGenerator, "DegreeofSubcoolinginSteamGenerator", "Degree of Subcooling in Steam Generator"},
{ Chiller_Absorption_IndirectFields::DegreeofSubcoolinginSteamCondensateLoop, "DegreeofSubcoolinginSteamCondensateLoop", "Degree of Subcooling in Steam Condensate Loop"},
{ Chiller_Absorption_IndirectFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const Chiller_Absorption_IndirectFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Chiller_Absorption_IndirectFields> OptionalChiller_Absorption_IndirectFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLER_ABSORPTION_INDIRECT_FIELDENUMS_HXX
