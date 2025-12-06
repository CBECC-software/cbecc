/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_COOLING_DX_CURVEFIT_SPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_DX_CURVEFIT_SPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_DX_CurveFit_SpeedFields
 *  \brief Enumeration of OS:Coil:Cooling:DX:CurveFit:Speed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_DX_CurveFit_SpeedFields, )
#else
class OS_Coil_Cooling_DX_CurveFit_SpeedFields: public ::EnumBase<OS_Coil_Cooling_DX_CurveFit_SpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, GrossTotalCoolingCapacityFraction, EvaporatorAirFlowRateFraction, CondenserAirFlowRateFraction, GrossSensibleHeatRatio, GrossCoolingCOP, ActiveFractionofCoilFaceArea, RatedEvaporatorFanPowerPerVolumeFlowRate2017, RatedEvaporatorFanPowerPerVolumeFlowRate2023, EvaporativeCondenserPumpPowerFraction, EvaporativeCondenserEffectiveness, TotalCoolingCapacityModifierFunctionofTemperatureCurve, TotalCoolingCapacityModifierFunctionofAirFlowFractionCurve, EnergyInputRatioModifierFunctionofTemperatureCurve, EnergyInputRatioModifierFunctionofAirFlowFractionCurve, PartLoadFractionCorrelationCurve, RatedWasteHeatFractionofPowerInput, WasteHeatModifierFunctionofTemperatureCurve, SensibleHeatRatioModifierFunctionofTemperatureCurve, SensibleHeatRatioModifierFunctionofFlowFractionCurve,   };
  OS_Coil_Cooling_DX_CurveFit_SpeedFields()
   : EnumBase<OS_Coil_Cooling_DX_CurveFit_SpeedFields>(Handle) {} 
  OS_Coil_Cooling_DX_CurveFit_SpeedFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_DX_CurveFit_SpeedFields>(t_name) {} 
  OS_Coil_Cooling_DX_CurveFit_SpeedFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_DX_CurveFit_SpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_DX_CurveFit_SpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_DX_CurveFit_SpeedFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_DX_CurveFit_SpeedFields>;
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
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::GrossTotalCoolingCapacityFraction, "GrossTotalCoolingCapacityFraction", "Gross Total Cooling Capacity Fraction"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::EvaporatorAirFlowRateFraction, "EvaporatorAirFlowRateFraction", "Evaporator Air Flow Rate Fraction"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::CondenserAirFlowRateFraction, "CondenserAirFlowRateFraction", "Condenser Air Flow Rate Fraction"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::GrossSensibleHeatRatio, "GrossSensibleHeatRatio", "Gross Sensible Heat Ratio"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::GrossCoolingCOP, "GrossCoolingCOP", "Gross Cooling COP"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::ActiveFractionofCoilFaceArea, "ActiveFractionofCoilFaceArea", "Active Fraction of Coil Face Area"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2017, "RatedEvaporatorFanPowerPerVolumeFlowRate2017", "Rated Evaporator Fan Power Per Volume Flow Rate 2017"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate2023, "RatedEvaporatorFanPowerPerVolumeFlowRate2023", "Rated Evaporator Fan Power Per Volume Flow Rate 2023"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserPumpPowerFraction, "EvaporativeCondenserPumpPowerFraction", "Evaporative Condenser Pump Power Fraction"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::TotalCoolingCapacityModifierFunctionofTemperatureCurve, "TotalCoolingCapacityModifierFunctionofTemperatureCurve", "Total Cooling Capacity Modifier Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::TotalCoolingCapacityModifierFunctionofAirFlowFractionCurve, "TotalCoolingCapacityModifierFunctionofAirFlowFractionCurve", "Total Cooling Capacity Modifier Function of Air Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::EnergyInputRatioModifierFunctionofTemperatureCurve, "EnergyInputRatioModifierFunctionofTemperatureCurve", "Energy Input Ratio Modifier Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::EnergyInputRatioModifierFunctionofAirFlowFractionCurve, "EnergyInputRatioModifierFunctionofAirFlowFractionCurve", "Energy Input Ratio Modifier Function of Air Flow Fraction Curve"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::PartLoadFractionCorrelationCurve, "PartLoadFractionCorrelationCurve", "Part Load Fraction Correlation Curve"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::RatedWasteHeatFractionofPowerInput, "RatedWasteHeatFractionofPowerInput", "Rated Waste Heat Fraction of Power Input"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::WasteHeatModifierFunctionofTemperatureCurve, "WasteHeatModifierFunctionofTemperatureCurve", "Waste Heat Modifier Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::SensibleHeatRatioModifierFunctionofTemperatureCurve, "SensibleHeatRatioModifierFunctionofTemperatureCurve", "Sensible Heat Ratio Modifier Function of Temperature Curve"},
{ OS_Coil_Cooling_DX_CurveFit_SpeedFields::SensibleHeatRatioModifierFunctionofFlowFractionCurve, "SensibleHeatRatioModifierFunctionofFlowFractionCurve", "Sensible Heat Ratio Modifier Function of Flow Fraction Curve"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_DX_CurveFit_SpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_DX_CurveFit_SpeedFields> OptionalOS_Coil_Cooling_DX_CurveFit_SpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_DX_CURVEFIT_SPEED_FIELDENUMS_HXX
