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

#ifndef UTILITIES_IDD_OS_GENERATOR_MICROTURBINE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_MICROTURBINE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_MicroTurbineFields
 *  \brief Enumeration of OS:Generator:MicroTurbine's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_MicroTurbineFields, )
#else
class OS_Generator_MicroTurbineFields: public ::EnumBase<OS_Generator_MicroTurbineFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, ReferenceElectricalPowerOutput, MinimumFullLoadElectricalPowerOutput, MaximumFullLoadElectricalPowerOutput, ReferenceElectricalEfficiencyUsingLowerHeatingValue, ReferenceCombustionAirInletTemperature, ReferenceCombustionAirInletHumidityRatio, ReferenceElevation, ElectricalPowerFunctionofTemperatureandElevationCurveName, ElectricalEfficiencyFunctionofTemperatureCurveName, ElectricalEfficiencyFunctionofPartLoadRatioCurveName, FuelType, FuelHigherHeatingValue, FuelLowerHeatingValue, StandbyPower, AncillaryPower, AncillaryPowerFunctionofFuelInputCurveName, GeneratorMicroTurbineHeatRecoveryName, CombustionAirInletNodeName, CombustionAirOutletNodeName, ReferenceExhaustAirMassFlowRate, ExhaustAirFlowRateFunctionofTemperatureCurveName, ExhaustAirFlowRateFunctionofPartLoadRatioCurveName, NominalExhaustAirOutletTemperature, ExhaustAirTemperatureFunctionofTemperatureCurveName, ExhaustAirTemperatureFunctionofPartLoadRatioCurveName,   };
  OS_Generator_MicroTurbineFields()
   : EnumBase<OS_Generator_MicroTurbineFields>(Handle) {} 
  OS_Generator_MicroTurbineFields(const std::string &t_name) 
   : EnumBase<OS_Generator_MicroTurbineFields>(t_name) {} 
  OS_Generator_MicroTurbineFields(int t_value) 
   : EnumBase<OS_Generator_MicroTurbineFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_MicroTurbineFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_MicroTurbineFields>::value()); }
   private:
    friend class EnumBase<OS_Generator_MicroTurbineFields>;
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
{ OS_Generator_MicroTurbineFields::Handle, "Handle", "Handle"},
{ OS_Generator_MicroTurbineFields::Name, "Name", "Name"},
{ OS_Generator_MicroTurbineFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Generator_MicroTurbineFields::ReferenceElectricalPowerOutput, "ReferenceElectricalPowerOutput", "Reference Electrical Power Output"},
{ OS_Generator_MicroTurbineFields::MinimumFullLoadElectricalPowerOutput, "MinimumFullLoadElectricalPowerOutput", "Minimum Full Load Electrical Power Output"},
{ OS_Generator_MicroTurbineFields::MaximumFullLoadElectricalPowerOutput, "MaximumFullLoadElectricalPowerOutput", "Maximum Full Load Electrical Power Output"},
{ OS_Generator_MicroTurbineFields::ReferenceElectricalEfficiencyUsingLowerHeatingValue, "ReferenceElectricalEfficiencyUsingLowerHeatingValue", "Reference Electrical Efficiency Using Lower Heating Value"},
{ OS_Generator_MicroTurbineFields::ReferenceCombustionAirInletTemperature, "ReferenceCombustionAirInletTemperature", "Reference Combustion Air Inlet Temperature"},
{ OS_Generator_MicroTurbineFields::ReferenceCombustionAirInletHumidityRatio, "ReferenceCombustionAirInletHumidityRatio", "Reference Combustion Air Inlet Humidity Ratio"},
{ OS_Generator_MicroTurbineFields::ReferenceElevation, "ReferenceElevation", "Reference Elevation"},
{ OS_Generator_MicroTurbineFields::ElectricalPowerFunctionofTemperatureandElevationCurveName, "ElectricalPowerFunctionofTemperatureandElevationCurveName", "Electrical Power Function of Temperature and Elevation Curve Name"},
{ OS_Generator_MicroTurbineFields::ElectricalEfficiencyFunctionofTemperatureCurveName, "ElectricalEfficiencyFunctionofTemperatureCurveName", "Electrical Efficiency Function of Temperature Curve Name"},
{ OS_Generator_MicroTurbineFields::ElectricalEfficiencyFunctionofPartLoadRatioCurveName, "ElectricalEfficiencyFunctionofPartLoadRatioCurveName", "Electrical Efficiency Function of Part Load Ratio Curve Name"},
{ OS_Generator_MicroTurbineFields::FuelType, "FuelType", "Fuel Type"},
{ OS_Generator_MicroTurbineFields::FuelHigherHeatingValue, "FuelHigherHeatingValue", "Fuel Higher Heating Value"},
{ OS_Generator_MicroTurbineFields::FuelLowerHeatingValue, "FuelLowerHeatingValue", "Fuel Lower Heating Value"},
{ OS_Generator_MicroTurbineFields::StandbyPower, "StandbyPower", "Standby Power"},
{ OS_Generator_MicroTurbineFields::AncillaryPower, "AncillaryPower", "Ancillary Power"},
{ OS_Generator_MicroTurbineFields::AncillaryPowerFunctionofFuelInputCurveName, "AncillaryPowerFunctionofFuelInputCurveName", "Ancillary Power Function of Fuel Input Curve Name"},
{ OS_Generator_MicroTurbineFields::GeneratorMicroTurbineHeatRecoveryName, "GeneratorMicroTurbineHeatRecoveryName", "Generator MicroTurbine Heat Recovery Name"},
{ OS_Generator_MicroTurbineFields::CombustionAirInletNodeName, "CombustionAirInletNodeName", "Combustion Air Inlet Node Name"},
{ OS_Generator_MicroTurbineFields::CombustionAirOutletNodeName, "CombustionAirOutletNodeName", "Combustion Air Outlet Node Name"},
{ OS_Generator_MicroTurbineFields::ReferenceExhaustAirMassFlowRate, "ReferenceExhaustAirMassFlowRate", "Reference Exhaust Air Mass Flow Rate"},
{ OS_Generator_MicroTurbineFields::ExhaustAirFlowRateFunctionofTemperatureCurveName, "ExhaustAirFlowRateFunctionofTemperatureCurveName", "Exhaust Air Flow Rate Function of Temperature Curve Name"},
{ OS_Generator_MicroTurbineFields::ExhaustAirFlowRateFunctionofPartLoadRatioCurveName, "ExhaustAirFlowRateFunctionofPartLoadRatioCurveName", "Exhaust Air Flow Rate Function of Part Load Ratio Curve Name"},
{ OS_Generator_MicroTurbineFields::NominalExhaustAirOutletTemperature, "NominalExhaustAirOutletTemperature", "Nominal Exhaust Air Outlet Temperature"},
{ OS_Generator_MicroTurbineFields::ExhaustAirTemperatureFunctionofTemperatureCurveName, "ExhaustAirTemperatureFunctionofTemperatureCurveName", "Exhaust Air Temperature Function of Temperature Curve Name"},
{ OS_Generator_MicroTurbineFields::ExhaustAirTemperatureFunctionofPartLoadRatioCurveName, "ExhaustAirTemperatureFunctionofPartLoadRatioCurveName", "Exhaust Air Temperature Function of Part Load Ratio Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_MicroTurbineFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_MicroTurbineFields> OptionalOS_Generator_MicroTurbineFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_MICROTURBINE_FIELDENUMS_HXX
