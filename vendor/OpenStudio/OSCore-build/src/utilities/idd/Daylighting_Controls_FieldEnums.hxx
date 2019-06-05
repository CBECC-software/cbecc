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

#ifndef UTILITIES_IDD_DAYLIGHTING_CONTROLS_FIELDENUMS_HXX
#define UTILITIES_IDD_DAYLIGHTING_CONTROLS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Daylighting_ControlsFields
 *  \brief Enumeration of Daylighting:Controls's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Daylighting_ControlsFields, )
#else
class Daylighting_ControlsFields: public ::EnumBase<Daylighting_ControlsFields> {
 public: 
  enum domain 
  {
Name, ZoneName, DaylightingMethod, AvailabilityScheduleName, LightingControlType, MinimumInputPowerFractionforContinuousorContinuousOffDimmingControl, MinimumLightOutputFractionforContinuousorContinuousOffDimmingControl, NumberofSteppedControlSteps, ProbabilityLightingwillbeResetWhenNeededinManualSteppedControl, GlareCalculationDaylightingReferencePointName, GlareCalculationAzimuthAngleofViewDirectionClockwisefromZoneyAxis, MaximumAllowableDiscomfortGlareIndex, DElightGriddingResolution,   };
  Daylighting_ControlsFields()
   : EnumBase<Daylighting_ControlsFields>(Name) {} 
  Daylighting_ControlsFields(const std::string &t_name) 
   : EnumBase<Daylighting_ControlsFields>(t_name) {} 
  Daylighting_ControlsFields(int t_value) 
   : EnumBase<Daylighting_ControlsFields>(t_value) {} 
  static std::string enumName() 
  { return "Daylighting_ControlsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Daylighting_ControlsFields>::value()); }
   private:
    friend class EnumBase<Daylighting_ControlsFields>;
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
{ Daylighting_ControlsFields::Name, "Name", "Name"},
{ Daylighting_ControlsFields::ZoneName, "ZoneName", "Zone Name"},
{ Daylighting_ControlsFields::DaylightingMethod, "DaylightingMethod", "Daylighting Method"},
{ Daylighting_ControlsFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Daylighting_ControlsFields::LightingControlType, "LightingControlType", "Lighting Control Type"},
{ Daylighting_ControlsFields::MinimumInputPowerFractionforContinuousorContinuousOffDimmingControl, "MinimumInputPowerFractionforContinuousorContinuousOffDimmingControl", "Minimum Input Power Fraction for Continuous or ContinuousOff Dimming Control"},
{ Daylighting_ControlsFields::MinimumLightOutputFractionforContinuousorContinuousOffDimmingControl, "MinimumLightOutputFractionforContinuousorContinuousOffDimmingControl", "Minimum Light Output Fraction for Continuous or ContinuousOff Dimming Control"},
{ Daylighting_ControlsFields::NumberofSteppedControlSteps, "NumberofSteppedControlSteps", "Number of Stepped Control Steps"},
{ Daylighting_ControlsFields::ProbabilityLightingwillbeResetWhenNeededinManualSteppedControl, "ProbabilityLightingwillbeResetWhenNeededinManualSteppedControl", "Probability Lighting will be Reset When Needed in Manual Stepped Control"},
{ Daylighting_ControlsFields::GlareCalculationDaylightingReferencePointName, "GlareCalculationDaylightingReferencePointName", "Glare Calculation Daylighting Reference Point Name"},
{ Daylighting_ControlsFields::GlareCalculationAzimuthAngleofViewDirectionClockwisefromZoneyAxis, "GlareCalculationAzimuthAngleofViewDirectionClockwisefromZoneyAxis", "Glare Calculation Azimuth Angle of View Direction Clockwise from Zone y-Axis"},
{ Daylighting_ControlsFields::MaximumAllowableDiscomfortGlareIndex, "MaximumAllowableDiscomfortGlareIndex", "Maximum Allowable Discomfort Glare Index"},
{ Daylighting_ControlsFields::DElightGriddingResolution, "DElightGriddingResolution", "DElight Gridding Resolution"},
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
  inline std::ostream &operator<<(std::ostream &os, const Daylighting_ControlsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Daylighting_ControlsFields> OptionalDaylighting_ControlsFields ;
#endif

/** \class Daylighting_ControlsExtensibleFields
 *  \brief Enumeration of Daylighting:Controls's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Daylighting_ControlsExtensibleFields, )
#else
class Daylighting_ControlsExtensibleFields: public ::EnumBase<Daylighting_ControlsExtensibleFields> {
 public: 
  enum domain 
  {
DaylightingReferencePointName, FractionofZoneControlledbyReferencePoint, IlluminanceSetpointatReferencePoint,   };
  Daylighting_ControlsExtensibleFields()
   : EnumBase<Daylighting_ControlsExtensibleFields>(DaylightingReferencePointName) {} 
  Daylighting_ControlsExtensibleFields(const std::string &t_name) 
   : EnumBase<Daylighting_ControlsExtensibleFields>(t_name) {} 
  Daylighting_ControlsExtensibleFields(int t_value) 
   : EnumBase<Daylighting_ControlsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Daylighting_ControlsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Daylighting_ControlsExtensibleFields>::value()); }
   private:
    friend class EnumBase<Daylighting_ControlsExtensibleFields>;
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
{ Daylighting_ControlsExtensibleFields::DaylightingReferencePointName, "DaylightingReferencePointName", "Daylighting Reference Point Name"},
{ Daylighting_ControlsExtensibleFields::FractionofZoneControlledbyReferencePoint, "FractionofZoneControlledbyReferencePoint", "Fraction of Zone Controlled by Reference Point"},
{ Daylighting_ControlsExtensibleFields::IlluminanceSetpointatReferencePoint, "IlluminanceSetpointatReferencePoint", "Illuminance Setpoint at Reference Point"},
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
  inline std::ostream &operator<<(std::ostream &os, const Daylighting_ControlsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Daylighting_ControlsExtensibleFields> OptionalDaylighting_ControlsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DAYLIGHTING_CONTROLS_FIELDENUMS_HXX
