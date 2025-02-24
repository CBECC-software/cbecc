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

#ifndef UTILITIES_IDD_OS_PUMP_VARIABLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PUMP_VARIABLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Pump_VariableSpeedFields
 *  \brief Enumeration of OS:Pump:VariableSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Pump_VariableSpeedFields, )
#else
class OS_Pump_VariableSpeedFields: public ::EnumBase<OS_Pump_VariableSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, InletNodeName, OutletNodeName, RatedFlowRate, RatedPumpHead, RatedPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, Coefficient1ofthePartLoadPerformanceCurve, Coefficient2ofthePartLoadPerformanceCurve, Coefficient3ofthePartLoadPerformanceCurve, Coefficient4ofthePartLoadPerformanceCurve, MinimumFlowRate, PumpControlType, PumpFlowRateScheduleName, PumpCurveName, ImpellerDiameter, VFDControlType, PumpRPMScheduleName, MinimumPressureSchedule, MaximumPressureSchedule, MinimumRPMSchedule, MaximumRPMSchedule, ZoneName, SkinLossRadiativeFraction, DesignPowerSizingMethod, DesignElectricPowerperUnitFlowRate, DesignShaftPowerperUnitFlowRateperUnitHead, DesignMinimumFlowRateFraction, EndUseSubcategory,   };
  OS_Pump_VariableSpeedFields()
   : EnumBase<OS_Pump_VariableSpeedFields>(Handle) {} 
  OS_Pump_VariableSpeedFields(const std::string &t_name) 
   : EnumBase<OS_Pump_VariableSpeedFields>(t_name) {} 
  OS_Pump_VariableSpeedFields(int t_value) 
   : EnumBase<OS_Pump_VariableSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Pump_VariableSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Pump_VariableSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_Pump_VariableSpeedFields>;
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
{ OS_Pump_VariableSpeedFields::Handle, "Handle", "Handle"},
{ OS_Pump_VariableSpeedFields::Name, "Name", "Name"},
{ OS_Pump_VariableSpeedFields::InletNodeName, "InletNodeName", "Inlet Node Name"},
{ OS_Pump_VariableSpeedFields::OutletNodeName, "OutletNodeName", "Outlet Node Name"},
{ OS_Pump_VariableSpeedFields::RatedFlowRate, "RatedFlowRate", "Rated Flow Rate"},
{ OS_Pump_VariableSpeedFields::RatedPumpHead, "RatedPumpHead", "Rated Pump Head"},
{ OS_Pump_VariableSpeedFields::RatedPowerConsumption, "RatedPowerConsumption", "Rated Power Consumption"},
{ OS_Pump_VariableSpeedFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ OS_Pump_VariableSpeedFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ OS_Pump_VariableSpeedFields::Coefficient1ofthePartLoadPerformanceCurve, "Coefficient1ofthePartLoadPerformanceCurve", "Coefficient 1 of the Part Load Performance Curve"},
{ OS_Pump_VariableSpeedFields::Coefficient2ofthePartLoadPerformanceCurve, "Coefficient2ofthePartLoadPerformanceCurve", "Coefficient 2 of the Part Load Performance Curve"},
{ OS_Pump_VariableSpeedFields::Coefficient3ofthePartLoadPerformanceCurve, "Coefficient3ofthePartLoadPerformanceCurve", "Coefficient 3 of the Part Load Performance Curve"},
{ OS_Pump_VariableSpeedFields::Coefficient4ofthePartLoadPerformanceCurve, "Coefficient4ofthePartLoadPerformanceCurve", "Coefficient 4 of the Part Load Performance Curve"},
{ OS_Pump_VariableSpeedFields::MinimumFlowRate, "MinimumFlowRate", "Minimum Flow Rate"},
{ OS_Pump_VariableSpeedFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ OS_Pump_VariableSpeedFields::PumpFlowRateScheduleName, "PumpFlowRateScheduleName", "Pump Flow Rate Schedule Name"},
{ OS_Pump_VariableSpeedFields::PumpCurveName, "PumpCurveName", "Pump Curve Name"},
{ OS_Pump_VariableSpeedFields::ImpellerDiameter, "ImpellerDiameter", "Impeller Diameter"},
{ OS_Pump_VariableSpeedFields::VFDControlType, "VFDControlType", "VFD Control Type"},
{ OS_Pump_VariableSpeedFields::PumpRPMScheduleName, "PumpRPMScheduleName", "Pump RPM Schedule Name"},
{ OS_Pump_VariableSpeedFields::MinimumPressureSchedule, "MinimumPressureSchedule", "Minimum Pressure Schedule"},
{ OS_Pump_VariableSpeedFields::MaximumPressureSchedule, "MaximumPressureSchedule", "Maximum Pressure Schedule"},
{ OS_Pump_VariableSpeedFields::MinimumRPMSchedule, "MinimumRPMSchedule", "Minimum RPM Schedule"},
{ OS_Pump_VariableSpeedFields::MaximumRPMSchedule, "MaximumRPMSchedule", "Maximum RPM Schedule"},
{ OS_Pump_VariableSpeedFields::ZoneName, "ZoneName", "Zone Name"},
{ OS_Pump_VariableSpeedFields::SkinLossRadiativeFraction, "SkinLossRadiativeFraction", "Skin Loss Radiative Fraction"},
{ OS_Pump_VariableSpeedFields::DesignPowerSizingMethod, "DesignPowerSizingMethod", "Design Power Sizing Method"},
{ OS_Pump_VariableSpeedFields::DesignElectricPowerperUnitFlowRate, "DesignElectricPowerperUnitFlowRate", "Design Electric Power per Unit Flow Rate"},
{ OS_Pump_VariableSpeedFields::DesignShaftPowerperUnitFlowRateperUnitHead, "DesignShaftPowerperUnitFlowRateperUnitHead", "Design Shaft Power per Unit Flow Rate per Unit Head"},
{ OS_Pump_VariableSpeedFields::DesignMinimumFlowRateFraction, "DesignMinimumFlowRateFraction", "Design Minimum Flow Rate Fraction"},
{ OS_Pump_VariableSpeedFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Pump_VariableSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Pump_VariableSpeedFields> OptionalOS_Pump_VariableSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PUMP_VARIABLESPEED_FIELDENUMS_HXX
