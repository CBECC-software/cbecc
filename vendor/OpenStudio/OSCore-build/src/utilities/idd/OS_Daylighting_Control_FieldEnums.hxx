/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

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
