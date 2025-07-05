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

#ifndef UTILITIES_IDD_GENERATOR_MICROCHP_NONNORMALIZEDPARAMETERS_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_MICROCHP_NONNORMALIZEDPARAMETERS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_MicroCHP_NonNormalizedParametersFields
 *  \brief Enumeration of Generator:MicroCHP:NonNormalizedParameters's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_MicroCHP_NonNormalizedParametersFields, )
#else
class Generator_MicroCHP_NonNormalizedParametersFields: public ::EnumBase<Generator_MicroCHP_NonNormalizedParametersFields> {
 public: 
  enum domain 
  {
Name, MaximumElectricPower, MinimumElectricPower, MinimumCoolingWaterFlowRate, MaximumCoolingWaterTemperature, ElectricalEfficiencyCurveName, ThermalEfficiencyCurveName, CoolingWaterFlowRateMode, CoolingWaterFlowRateCurveName, AirFlowRateCurveName, MaximumNetElectricalPowerRateofChange, MaximumFuelFlowRateofChange, HeatExchangerUFactorTimesAreaValue, SkinLossUFactorTimesAreaValue, SkinLossRadiativeFraction, AggregatedThermalMassofEnergyConversionPortionofGenerator, AggregatedThermalMassofHeatRecoveryPortionofGenerator, StandbyPower, WarmUpMode, WarmUpFuelFlowRateCoefficient, NominalEngineOperatingTemperature, WarmUpPowerCoefficient, WarmUpFuelFlowRateLimitRatio, WarmUpDelayTime, CoolDownPower, CoolDownDelayTime, RestartMode,   };
  Generator_MicroCHP_NonNormalizedParametersFields()
   : EnumBase<Generator_MicroCHP_NonNormalizedParametersFields>(Name) {} 
  Generator_MicroCHP_NonNormalizedParametersFields(const std::string &t_name) 
   : EnumBase<Generator_MicroCHP_NonNormalizedParametersFields>(t_name) {} 
  Generator_MicroCHP_NonNormalizedParametersFields(int t_value) 
   : EnumBase<Generator_MicroCHP_NonNormalizedParametersFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_MicroCHP_NonNormalizedParametersFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_MicroCHP_NonNormalizedParametersFields>::value()); }
   private:
    friend class EnumBase<Generator_MicroCHP_NonNormalizedParametersFields>;
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
{ Generator_MicroCHP_NonNormalizedParametersFields::Name, "Name", "Name"},
{ Generator_MicroCHP_NonNormalizedParametersFields::MaximumElectricPower, "MaximumElectricPower", "Maximum Electric Power"},
{ Generator_MicroCHP_NonNormalizedParametersFields::MinimumElectricPower, "MinimumElectricPower", "Minimum Electric Power"},
{ Generator_MicroCHP_NonNormalizedParametersFields::MinimumCoolingWaterFlowRate, "MinimumCoolingWaterFlowRate", "Minimum Cooling Water Flow Rate"},
{ Generator_MicroCHP_NonNormalizedParametersFields::MaximumCoolingWaterTemperature, "MaximumCoolingWaterTemperature", "Maximum Cooling Water Temperature"},
{ Generator_MicroCHP_NonNormalizedParametersFields::ElectricalEfficiencyCurveName, "ElectricalEfficiencyCurveName", "Electrical Efficiency Curve Name"},
{ Generator_MicroCHP_NonNormalizedParametersFields::ThermalEfficiencyCurveName, "ThermalEfficiencyCurveName", "Thermal Efficiency Curve Name"},
{ Generator_MicroCHP_NonNormalizedParametersFields::CoolingWaterFlowRateMode, "CoolingWaterFlowRateMode", "Cooling Water Flow Rate Mode"},
{ Generator_MicroCHP_NonNormalizedParametersFields::CoolingWaterFlowRateCurveName, "CoolingWaterFlowRateCurveName", "Cooling Water Flow Rate Curve Name"},
{ Generator_MicroCHP_NonNormalizedParametersFields::AirFlowRateCurveName, "AirFlowRateCurveName", "Air Flow Rate Curve Name"},
{ Generator_MicroCHP_NonNormalizedParametersFields::MaximumNetElectricalPowerRateofChange, "MaximumNetElectricalPowerRateofChange", "Maximum Net Electrical Power Rate of Change"},
{ Generator_MicroCHP_NonNormalizedParametersFields::MaximumFuelFlowRateofChange, "MaximumFuelFlowRateofChange", "Maximum Fuel Flow Rate of Change"},
{ Generator_MicroCHP_NonNormalizedParametersFields::HeatExchangerUFactorTimesAreaValue, "HeatExchangerUFactorTimesAreaValue", "Heat Exchanger U-Factor Times Area Value"},
{ Generator_MicroCHP_NonNormalizedParametersFields::SkinLossUFactorTimesAreaValue, "SkinLossUFactorTimesAreaValue", "Skin Loss U-Factor Times Area Value"},
{ Generator_MicroCHP_NonNormalizedParametersFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
{ Generator_MicroCHP_NonNormalizedParametersFields::AggregatedThermalMassofEnergyConversionPortionofGenerator, "AggregatedThermalMassofEnergyConversionPortionofGenerator", "Aggregated Thermal Mass of Energy Conversion Portion of Generator"},
{ Generator_MicroCHP_NonNormalizedParametersFields::AggregatedThermalMassofHeatRecoveryPortionofGenerator, "AggregatedThermalMassofHeatRecoveryPortionofGenerator", "Aggregated Thermal Mass of Heat Recovery Portion of Generator"},
{ Generator_MicroCHP_NonNormalizedParametersFields::StandbyPower, "StandbyPower", "Standby Power"},
{ Generator_MicroCHP_NonNormalizedParametersFields::WarmUpMode, "WarmUpMode", "Warm Up Mode"},
{ Generator_MicroCHP_NonNormalizedParametersFields::WarmUpFuelFlowRateCoefficient, "WarmUpFuelFlowRateCoefficient", "Warm Up Fuel Flow Rate Coefficient"},
{ Generator_MicroCHP_NonNormalizedParametersFields::NominalEngineOperatingTemperature, "NominalEngineOperatingTemperature", "Nominal Engine Operating Temperature"},
{ Generator_MicroCHP_NonNormalizedParametersFields::WarmUpPowerCoefficient, "WarmUpPowerCoefficient", "Warm Up Power Coefficient"},
{ Generator_MicroCHP_NonNormalizedParametersFields::WarmUpFuelFlowRateLimitRatio, "WarmUpFuelFlowRateLimitRatio", "Warm Up Fuel Flow Rate Limit Ratio"},
{ Generator_MicroCHP_NonNormalizedParametersFields::WarmUpDelayTime, "WarmUpDelayTime", "Warm Up Delay Time"},
{ Generator_MicroCHP_NonNormalizedParametersFields::CoolDownPower, "CoolDownPower", "Cool Down Power"},
{ Generator_MicroCHP_NonNormalizedParametersFields::CoolDownDelayTime, "CoolDownDelayTime", "Cool Down Delay Time"},
{ Generator_MicroCHP_NonNormalizedParametersFields::RestartMode, "RestartMode", "Restart Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_MicroCHP_NonNormalizedParametersFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_MicroCHP_NonNormalizedParametersFields> OptionalGenerator_MicroCHP_NonNormalizedParametersFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_MICROCHP_NONNORMALIZEDPARAMETERS_FIELDENUMS_HXX
