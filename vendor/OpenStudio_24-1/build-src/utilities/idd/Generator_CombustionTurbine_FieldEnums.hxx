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

#ifndef UTILITIES_IDD_GENERATOR_COMBUSTIONTURBINE_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_COMBUSTIONTURBINE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_CombustionTurbineFields
 *  \brief Enumeration of Generator:CombustionTurbine's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_CombustionTurbineFields, )
#else
class Generator_CombustionTurbineFields: public ::EnumBase<Generator_CombustionTurbineFields> {
 public: 
  enum domain 
  {
Name, RatedPowerOutput, ElectricCircuitNodeName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, PartLoadBasedFuelInputCurveName, TemperatureBasedFuelInputCurveName, ExhaustFlowCurveName, PartLoadBasedExhaustTemperatureCurveName, TemperatureBasedExhaustTemperatureCurveName, HeatRecoveryLubeEnergyCurveName, Coefficient1ofUFactorTimesAreaCurve, Coefficient2ofUFactorTimesAreaCurve, MaximumExhaustFlowperUnitofPowerOutput, DesignMinimumExhaustTemperature, DesignAirInletTemperature, FuelHigherHeatingValue, DesignHeatRecoveryWaterFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, FuelType, HeatRecoveryMaximumTemperature, OutdoorAirInletNodeName,   };
  Generator_CombustionTurbineFields()
   : EnumBase<Generator_CombustionTurbineFields>(Name) {} 
  Generator_CombustionTurbineFields(const std::string &t_name) 
   : EnumBase<Generator_CombustionTurbineFields>(t_name) {} 
  Generator_CombustionTurbineFields(int t_value) 
   : EnumBase<Generator_CombustionTurbineFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_CombustionTurbineFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_CombustionTurbineFields>::value()); }
   private:
    friend class EnumBase<Generator_CombustionTurbineFields>;
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
{ Generator_CombustionTurbineFields::Name, "Name", "Name"},
{ Generator_CombustionTurbineFields::RatedPowerOutput, "RatedPowerOutput", "Rated Power Output"},
{ Generator_CombustionTurbineFields::ElectricCircuitNodeName, "ElectricCircuitNodeName", "Electric Circuit Node Name"},
{ Generator_CombustionTurbineFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Generator_CombustionTurbineFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Generator_CombustionTurbineFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Generator_CombustionTurbineFields::PartLoadBasedFuelInputCurveName, "PartLoadBasedFuelInputCurveName", "Part Load Based Fuel Input Curve Name"},
{ Generator_CombustionTurbineFields::TemperatureBasedFuelInputCurveName, "TemperatureBasedFuelInputCurveName", "Temperature Based Fuel Input Curve Name"},
{ Generator_CombustionTurbineFields::ExhaustFlowCurveName, "ExhaustFlowCurveName", "Exhaust Flow Curve Name"},
{ Generator_CombustionTurbineFields::PartLoadBasedExhaustTemperatureCurveName, "PartLoadBasedExhaustTemperatureCurveName", "Part Load Based Exhaust Temperature Curve Name"},
{ Generator_CombustionTurbineFields::TemperatureBasedExhaustTemperatureCurveName, "TemperatureBasedExhaustTemperatureCurveName", "Temperature Based Exhaust Temperature Curve Name"},
{ Generator_CombustionTurbineFields::HeatRecoveryLubeEnergyCurveName, "HeatRecoveryLubeEnergyCurveName", "Heat Recovery Lube Energy Curve Name"},
{ Generator_CombustionTurbineFields::Coefficient1ofUFactorTimesAreaCurve, "Coefficient1ofUFactorTimesAreaCurve", "Coefficient 1 of U-Factor Times Area Curve"},
{ Generator_CombustionTurbineFields::Coefficient2ofUFactorTimesAreaCurve, "Coefficient2ofUFactorTimesAreaCurve", "Coefficient 2 of U-Factor Times Area Curve"},
{ Generator_CombustionTurbineFields::MaximumExhaustFlowperUnitofPowerOutput, "MaximumExhaustFlowperUnitofPowerOutput", "Maximum Exhaust Flow per Unit of Power Output"},
{ Generator_CombustionTurbineFields::DesignMinimumExhaustTemperature, "DesignMinimumExhaustTemperature", "Design Minimum Exhaust Temperature"},
{ Generator_CombustionTurbineFields::DesignAirInletTemperature, "DesignAirInletTemperature", "Design Air Inlet Temperature"},
{ Generator_CombustionTurbineFields::FuelHigherHeatingValue, "FuelHigherHeatingValue", "Fuel Higher Heating Value"},
{ Generator_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ Generator_CombustionTurbineFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ Generator_CombustionTurbineFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ Generator_CombustionTurbineFields::FuelType, "FuelType", "Fuel Type"},
{ Generator_CombustionTurbineFields::HeatRecoveryMaximumTemperature, "HeatRecoveryMaximumTemperature", "Heat Recovery Maximum Temperature"},
{ Generator_CombustionTurbineFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_CombustionTurbineFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_CombustionTurbineFields> OptionalGenerator_CombustionTurbineFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_COMBUSTIONTURBINE_FIELDENUMS_HXX
