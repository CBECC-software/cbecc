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

#ifndef UTILITIES_IDD_GENERATOR_INTERNALCOMBUSTIONENGINE_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_INTERNALCOMBUSTIONENGINE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_InternalCombustionEngineFields
 *  \brief Enumeration of Generator:InternalCombustionEngine's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_InternalCombustionEngineFields, )
#else
class Generator_InternalCombustionEngineFields: public ::EnumBase<Generator_InternalCombustionEngineFields> {
 public: 
  enum domain 
  {
Name, RatedPowerOutput, ElectricCircuitNodeName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, ShaftPowerCurveName, JacketHeatRecoveryCurveName, LubeHeatRecoveryCurveName, TotalExhaustEnergyCurveName, ExhaustTemperatureCurveName, Coefficient1ofUFactorTimesAreaCurve, Coefficient2ofUFactorTimesAreaCurve, MaximumExhaustFlowperUnitofPowerOutput, DesignMinimumExhaustTemperature, FuelHigherHeatingValue, DesignHeatRecoveryWaterFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, FuelType, HeatRecoveryMaximumTemperature,   };
  Generator_InternalCombustionEngineFields()
   : EnumBase<Generator_InternalCombustionEngineFields>(Name) {} 
  Generator_InternalCombustionEngineFields(const std::string &t_name) 
   : EnumBase<Generator_InternalCombustionEngineFields>(t_name) {} 
  Generator_InternalCombustionEngineFields(int t_value) 
   : EnumBase<Generator_InternalCombustionEngineFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_InternalCombustionEngineFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_InternalCombustionEngineFields>::value()); }
   private:
    friend class EnumBase<Generator_InternalCombustionEngineFields>;
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
{ Generator_InternalCombustionEngineFields::Name, "Name", "Name"},
{ Generator_InternalCombustionEngineFields::RatedPowerOutput, "RatedPowerOutput", "Rated Power Output"},
{ Generator_InternalCombustionEngineFields::ElectricCircuitNodeName, "ElectricCircuitNodeName", "Electric Circuit Node Name"},
{ Generator_InternalCombustionEngineFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Generator_InternalCombustionEngineFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Generator_InternalCombustionEngineFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Generator_InternalCombustionEngineFields::ShaftPowerCurveName, "ShaftPowerCurveName", "Shaft Power Curve Name"},
{ Generator_InternalCombustionEngineFields::JacketHeatRecoveryCurveName, "JacketHeatRecoveryCurveName", "Jacket Heat Recovery Curve Name"},
{ Generator_InternalCombustionEngineFields::LubeHeatRecoveryCurveName, "LubeHeatRecoveryCurveName", "Lube Heat Recovery Curve Name"},
{ Generator_InternalCombustionEngineFields::TotalExhaustEnergyCurveName, "TotalExhaustEnergyCurveName", "Total Exhaust Energy Curve Name"},
{ Generator_InternalCombustionEngineFields::ExhaustTemperatureCurveName, "ExhaustTemperatureCurveName", "Exhaust Temperature Curve Name"},
{ Generator_InternalCombustionEngineFields::Coefficient1ofUFactorTimesAreaCurve, "Coefficient1ofUFactorTimesAreaCurve", "Coefficient 1 of U-Factor Times Area Curve"},
{ Generator_InternalCombustionEngineFields::Coefficient2ofUFactorTimesAreaCurve, "Coefficient2ofUFactorTimesAreaCurve", "Coefficient 2 of U-Factor Times Area Curve"},
{ Generator_InternalCombustionEngineFields::MaximumExhaustFlowperUnitofPowerOutput, "MaximumExhaustFlowperUnitofPowerOutput", "Maximum Exhaust Flow per Unit of Power Output"},
{ Generator_InternalCombustionEngineFields::DesignMinimumExhaustTemperature, "DesignMinimumExhaustTemperature", "Design Minimum Exhaust Temperature"},
{ Generator_InternalCombustionEngineFields::FuelHigherHeatingValue, "FuelHigherHeatingValue", "Fuel Higher Heating Value"},
{ Generator_InternalCombustionEngineFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ Generator_InternalCombustionEngineFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ Generator_InternalCombustionEngineFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ Generator_InternalCombustionEngineFields::FuelType, "FuelType", "Fuel Type"},
{ Generator_InternalCombustionEngineFields::HeatRecoveryMaximumTemperature, "HeatRecoveryMaximumTemperature", "Heat Recovery Maximum Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_InternalCombustionEngineFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_InternalCombustionEngineFields> OptionalGenerator_InternalCombustionEngineFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_INTERNALCOMBUSTIONENGINE_FIELDENUMS_HXX
