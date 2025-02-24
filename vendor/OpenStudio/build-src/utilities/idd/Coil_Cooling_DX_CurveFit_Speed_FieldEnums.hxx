/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_COIL_COOLING_DX_CURVEFIT_SPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_DX_CURVEFIT_SPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_DX_CurveFit_SpeedFields
 *  \brief Enumeration of Coil:Cooling:DX:CurveFit:Speed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_DX_CurveFit_SpeedFields, )
#else
class Coil_Cooling_DX_CurveFit_SpeedFields: public ::EnumBase<Coil_Cooling_DX_CurveFit_SpeedFields> {
 public: 
  enum domain 
  {
Name, GrossTotalCoolingCapacityFraction, EvaporatorAirFlowRateFraction, CondenserAirFlowRateFraction, GrossSensibleHeatRatio, GrossCoolingCOP, ActiveFractionofCoilFaceArea, RatedEvaporatorFanPowerPerVolumeFlowRate, EvaporativeCondenserPumpPowerFraction, EvaporativeCondenserEffectiveness, TotalCoolingCapacityModifierFunctionofTemperatureCurveName, TotalCoolingCapacityModifierFunctionofAirFlowFractionCurveName, EnergyInputRatioModifierFunctionofTemperatureCurveName, EnergyInputRatioModifierFunctionofAirFlowFractionCurveName, PartLoadFractionCorrelationCurveName, RatedWasteHeatFractionofPowerInput, WasteHeatModifierFunctionofTemperatureCurveName, SensibleHeatRatioModifierFunctionofTemperatureCurveName, SensibleHeatRatioModifierFunctionofFlowFractionCurveName,   };
  Coil_Cooling_DX_CurveFit_SpeedFields()
   : EnumBase<Coil_Cooling_DX_CurveFit_SpeedFields>(Name) {} 
  Coil_Cooling_DX_CurveFit_SpeedFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_CurveFit_SpeedFields>(t_name) {} 
  Coil_Cooling_DX_CurveFit_SpeedFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_CurveFit_SpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_CurveFit_SpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_CurveFit_SpeedFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_CurveFit_SpeedFields>;
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
{ Coil_Cooling_DX_CurveFit_SpeedFields::Name, "Name", "Name"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::GrossTotalCoolingCapacityFraction, "GrossTotalCoolingCapacityFraction", "Gross Total Cooling Capacity Fraction"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::EvaporatorAirFlowRateFraction, "EvaporatorAirFlowRateFraction", "Evaporator Air Flow Rate Fraction"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::CondenserAirFlowRateFraction, "CondenserAirFlowRateFraction", "Condenser Air Flow Rate Fraction"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::GrossSensibleHeatRatio, "GrossSensibleHeatRatio", "Gross Sensible Heat Ratio"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::GrossCoolingCOP, "GrossCoolingCOP", "Gross Cooling COP"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::ActiveFractionofCoilFaceArea, "ActiveFractionofCoilFaceArea", "Active Fraction of Coil Face Area"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate, "RatedEvaporatorFanPowerPerVolumeFlowRate", "Rated Evaporator Fan Power Per Volume Flow Rate"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserPumpPowerFraction, "EvaporativeCondenserPumpPowerFraction", "Evaporative Condenser Pump Power Fraction"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::TotalCoolingCapacityModifierFunctionofTemperatureCurveName, "TotalCoolingCapacityModifierFunctionofTemperatureCurveName", "Total Cooling Capacity Modifier Function of Temperature Curve Name"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::TotalCoolingCapacityModifierFunctionofAirFlowFractionCurveName, "TotalCoolingCapacityModifierFunctionofAirFlowFractionCurveName", "Total Cooling Capacity Modifier Function of Air Flow Fraction Curve Name"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::EnergyInputRatioModifierFunctionofTemperatureCurveName, "EnergyInputRatioModifierFunctionofTemperatureCurveName", "Energy Input Ratio Modifier Function of Temperature Curve Name"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::EnergyInputRatioModifierFunctionofAirFlowFractionCurveName, "EnergyInputRatioModifierFunctionofAirFlowFractionCurveName", "Energy Input Ratio Modifier Function of Air Flow Fraction Curve Name"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::RatedWasteHeatFractionofPowerInput, "RatedWasteHeatFractionofPowerInput", "Rated Waste Heat Fraction of Power Input"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::WasteHeatModifierFunctionofTemperatureCurveName, "WasteHeatModifierFunctionofTemperatureCurveName", "Waste Heat Modifier Function of Temperature Curve Name"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::SensibleHeatRatioModifierFunctionofTemperatureCurveName, "SensibleHeatRatioModifierFunctionofTemperatureCurveName", "Sensible Heat Ratio Modifier Function of Temperature Curve Name"},
{ Coil_Cooling_DX_CurveFit_SpeedFields::SensibleHeatRatioModifierFunctionofFlowFractionCurveName, "SensibleHeatRatioModifierFunctionofFlowFractionCurveName", "Sensible Heat Ratio Modifier Function of Flow Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_CurveFit_SpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_CurveFit_SpeedFields> OptionalCoil_Cooling_DX_CurveFit_SpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_DX_CURVEFIT_SPEED_FIELDENUMS_HXX
