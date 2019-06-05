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

#ifndef UTILITIES_IDD_CHILLER_ABSORPTION_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLER_ABSORPTION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Chiller_AbsorptionFields
 *  \brief Enumeration of Chiller:Absorption's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Chiller_AbsorptionFields, )
#else
class Chiller_AbsorptionFields: public ::EnumBase<Chiller_AbsorptionFields> {
 public: 
  enum domain 
  {
Name, NominalCapacity, NominalPumpingPower, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, DesignCondenserInletTemperature, DesignChilledWaterFlowRate, DesignCondenserWaterFlowRate, Coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve, Coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve, Coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve, Coefficient1ofthePumpElectricUsePartLoadRatioCurve, Coefficient2ofthePumpElectricUsePartLoadRatioCurve, Coefficient3ofthePumpElectricUsePartLoadRatioCurve, ChilledWaterOutletTemperatureLowerLimit, GeneratorInletNodeName, GeneratorOutletNodeName, ChillerFlowMode, GeneratorHeatSourceType, DesignGeneratorFluidFlowRate, DegreeofSubcoolinginSteamGenerator, SizingFactor,   };
  Chiller_AbsorptionFields()
   : EnumBase<Chiller_AbsorptionFields>(Name) {} 
  Chiller_AbsorptionFields(const std::string &t_name) 
   : EnumBase<Chiller_AbsorptionFields>(t_name) {} 
  Chiller_AbsorptionFields(int t_value) 
   : EnumBase<Chiller_AbsorptionFields>(t_value) {} 
  static std::string enumName() 
  { return "Chiller_AbsorptionFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Chiller_AbsorptionFields>::value()); }
   private:
    friend class EnumBase<Chiller_AbsorptionFields>;
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
{ Chiller_AbsorptionFields::Name, "Name", "Name"},
{ Chiller_AbsorptionFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Chiller_AbsorptionFields::NominalPumpingPower, "NominalPumpingPower", "Nominal Pumping Power"},
{ Chiller_AbsorptionFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ Chiller_AbsorptionFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ Chiller_AbsorptionFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ Chiller_AbsorptionFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ Chiller_AbsorptionFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Chiller_AbsorptionFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Chiller_AbsorptionFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Chiller_AbsorptionFields::DesignCondenserInletTemperature, "DesignCondenserInletTemperature", "Design Condenser Inlet Temperature"},
{ Chiller_AbsorptionFields::DesignChilledWaterFlowRate, "DesignChilledWaterFlowRate", "Design Chilled Water Flow Rate"},
{ Chiller_AbsorptionFields::DesignCondenserWaterFlowRate, "DesignCondenserWaterFlowRate", "Design Condenser Water Flow Rate"},
{ Chiller_AbsorptionFields::Coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve, "Coefficient1oftheHotWaterorSteamUsePartLoadRatioCurve", "Coefficient 1 of the Hot Water or Steam Use Part Load Ratio Curve"},
{ Chiller_AbsorptionFields::Coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve, "Coefficient2oftheHotWaterorSteamUsePartLoadRatioCurve", "Coefficient 2 of the Hot Water or Steam Use Part Load Ratio Curve"},
{ Chiller_AbsorptionFields::Coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve, "Coefficient3oftheHotWaterorSteamUsePartLoadRatioCurve", "Coefficient 3 of the Hot Water or Steam Use Part Load Ratio Curve"},
{ Chiller_AbsorptionFields::Coefficient1ofthePumpElectricUsePartLoadRatioCurve, "Coefficient1ofthePumpElectricUsePartLoadRatioCurve", "Coefficient 1 of the Pump Electric Use Part Load Ratio Curve"},
{ Chiller_AbsorptionFields::Coefficient2ofthePumpElectricUsePartLoadRatioCurve, "Coefficient2ofthePumpElectricUsePartLoadRatioCurve", "Coefficient 2 of the Pump Electric Use Part Load Ratio Curve"},
{ Chiller_AbsorptionFields::Coefficient3ofthePumpElectricUsePartLoadRatioCurve, "Coefficient3ofthePumpElectricUsePartLoadRatioCurve", "Coefficient 3 of the Pump Electric Use Part Load Ratio Curve"},
{ Chiller_AbsorptionFields::ChilledWaterOutletTemperatureLowerLimit, "ChilledWaterOutletTemperatureLowerLimit", "Chilled Water Outlet Temperature Lower Limit"},
{ Chiller_AbsorptionFields::GeneratorInletNodeName, "GeneratorInletNodeName", "Generator Inlet Node Name"},
{ Chiller_AbsorptionFields::GeneratorOutletNodeName, "GeneratorOutletNodeName", "Generator Outlet Node Name"},
{ Chiller_AbsorptionFields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ Chiller_AbsorptionFields::GeneratorHeatSourceType, "GeneratorHeatSourceType", "Generator Heat Source Type"},
{ Chiller_AbsorptionFields::DesignGeneratorFluidFlowRate, "DesignGeneratorFluidFlowRate", "Design Generator Fluid Flow Rate"},
{ Chiller_AbsorptionFields::DegreeofSubcoolinginSteamGenerator, "DegreeofSubcoolinginSteamGenerator", "Degree of Subcooling in Steam Generator"},
{ Chiller_AbsorptionFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const Chiller_AbsorptionFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Chiller_AbsorptionFields> OptionalChiller_AbsorptionFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLER_ABSORPTION_FIELDENUMS_HXX
