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

#ifndef UTILITIES_IDD_OS_DAYLIGHTING_CONTROL_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_DAYLIGHTING_CONTROL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Daylighting_ControlFields
 *  \brief Enumeration of OS:Daylighting:Control's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Daylighting_ControlFields, )
#else
class OS_Daylighting_ControlFields: public ::EnumBase<OS_Daylighting_ControlFields> {
 public: 
  enum domain 
  {
Handle, Name, SpaceName, PositionXCoordinate, PositionYCoordinate, PositionZCoordinate, PsiRotationAroundXAxis, ThetaRotationAroundYAxis, PhiRotationAroundZAxis, IlluminanceSetpoint, LightingControlType, MinimumInputPowerFractionforContinuousDimmingControl, MinimumLightOutputFractionforContinuousDimmingControl, NumberofSteppedControlSteps, ProbabilityLightingwillbeResetWhenNeededinManualSteppedControl, NumberofDaylightingViews, MaximumAllowableDiscomfortGlareIndex,   };
  OS_Daylighting_ControlFields()
   : EnumBase<OS_Daylighting_ControlFields>(Handle) {} 
  OS_Daylighting_ControlFields(const std::string &t_name) 
   : EnumBase<OS_Daylighting_ControlFields>(t_name) {} 
  OS_Daylighting_ControlFields(int t_value) 
   : EnumBase<OS_Daylighting_ControlFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Daylighting_ControlFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Daylighting_ControlFields>::value()); }
   private:
    friend class EnumBase<OS_Daylighting_ControlFields>;
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
{ OS_Daylighting_ControlFields::Handle, "Handle", "Handle"},
{ OS_Daylighting_ControlFields::Name, "Name", "Name"},
{ OS_Daylighting_ControlFields::SpaceName, "SpaceName", "Space Name"},
{ OS_Daylighting_ControlFields::PositionXCoordinate, "PositionXCoordinate", "Position X-Coordinate"},
{ OS_Daylighting_ControlFields::PositionYCoordinate, "PositionYCoordinate", "Position Y-Coordinate"},
{ OS_Daylighting_ControlFields::PositionZCoordinate, "PositionZCoordinate", "Position Z-Coordinate"},
{ OS_Daylighting_ControlFields::PsiRotationAroundXAxis, "PsiRotationAroundXAxis", "Psi Rotation Around X-Axis"},
{ OS_Daylighting_ControlFields::ThetaRotationAroundYAxis, "ThetaRotationAroundYAxis", "Theta Rotation Around Y-Axis"},
{ OS_Daylighting_ControlFields::PhiRotationAroundZAxis, "PhiRotationAroundZAxis", "Phi Rotation Around Z-Axis"},
{ OS_Daylighting_ControlFields::IlluminanceSetpoint, "IlluminanceSetpoint", "Illuminance Setpoint"},
{ OS_Daylighting_ControlFields::LightingControlType, "LightingControlType", "Lighting Control Type"},
{ OS_Daylighting_ControlFields::MinimumInputPowerFractionforContinuousDimmingControl, "MinimumInputPowerFractionforContinuousDimmingControl", "Minimum Input Power Fraction for Continuous Dimming Control"},
{ OS_Daylighting_ControlFields::MinimumLightOutputFractionforContinuousDimmingControl, "MinimumLightOutputFractionforContinuousDimmingControl", "Minimum Light Output Fraction for Continuous Dimming Control"},
{ OS_Daylighting_ControlFields::NumberofSteppedControlSteps, "NumberofSteppedControlSteps", "Number of Stepped Control Steps"},
{ OS_Daylighting_ControlFields::ProbabilityLightingwillbeResetWhenNeededinManualSteppedControl, "ProbabilityLightingwillbeResetWhenNeededinManualSteppedControl", "Probability Lighting will be Reset When Needed in Manual Stepped Control"},
{ OS_Daylighting_ControlFields::NumberofDaylightingViews, "NumberofDaylightingViews", "Number of Daylighting Views"},
{ OS_Daylighting_ControlFields::MaximumAllowableDiscomfortGlareIndex, "MaximumAllowableDiscomfortGlareIndex", "Maximum Allowable Discomfort Glare Index"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Daylighting_ControlFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Daylighting_ControlFields> OptionalOS_Daylighting_ControlFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_DAYLIGHTING_CONTROL_FIELDENUMS_HXX
