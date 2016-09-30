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
ZoneName, TotalDaylightingReferencePoints, XCoordinateofFirstReferencePoint, YCoordinateofFirstReferencePoint, ZCoordinateofFirstReferencePoint, XCoordinateofSecondReferencePoint, YCoordinateofSecondReferencePoint, ZCoordinateofSecondReferencePoint, FractionofZoneControlledbyFirstReferencePoint, FractionofZoneControlledbySecondReferencePoint, IlluminanceSetpointatFirstReferencePoint, IlluminanceSetpointatSecondReferencePoint, LightingControlType, GlareCalculationAzimuthAngleofViewDirectionClockwisefromZoneyAxis, MaximumAllowableDiscomfortGlareIndex, MinimumInputPowerFractionforContinuousDimmingControl, MinimumLightOutputFractionforContinuousDimmingControl, NumberofSteppedControlSteps, ProbabilityLightingwillbeResetWhenNeededinManualSteppedControl, AvailabilityScheduleName,   };
  Daylighting_ControlsFields()
   : EnumBase<Daylighting_ControlsFields>(ZoneName) {} 
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
{ Daylighting_ControlsFields::ZoneName, "ZoneName", "Zone Name"},
{ Daylighting_ControlsFields::TotalDaylightingReferencePoints, "TotalDaylightingReferencePoints", "Total Daylighting Reference Points"},
{ Daylighting_ControlsFields::XCoordinateofFirstReferencePoint, "XCoordinateofFirstReferencePoint", "X-Coordinate of First Reference Point"},
{ Daylighting_ControlsFields::YCoordinateofFirstReferencePoint, "YCoordinateofFirstReferencePoint", "Y-Coordinate of First Reference Point"},
{ Daylighting_ControlsFields::ZCoordinateofFirstReferencePoint, "ZCoordinateofFirstReferencePoint", "Z-Coordinate of First Reference Point"},
{ Daylighting_ControlsFields::XCoordinateofSecondReferencePoint, "XCoordinateofSecondReferencePoint", "X-Coordinate of Second Reference Point"},
{ Daylighting_ControlsFields::YCoordinateofSecondReferencePoint, "YCoordinateofSecondReferencePoint", "Y-Coordinate of Second Reference Point"},
{ Daylighting_ControlsFields::ZCoordinateofSecondReferencePoint, "ZCoordinateofSecondReferencePoint", "Z-Coordinate of Second Reference Point"},
{ Daylighting_ControlsFields::FractionofZoneControlledbyFirstReferencePoint, "FractionofZoneControlledbyFirstReferencePoint", "Fraction of Zone Controlled by First Reference Point"},
{ Daylighting_ControlsFields::FractionofZoneControlledbySecondReferencePoint, "FractionofZoneControlledbySecondReferencePoint", "Fraction of Zone Controlled by Second Reference Point"},
{ Daylighting_ControlsFields::IlluminanceSetpointatFirstReferencePoint, "IlluminanceSetpointatFirstReferencePoint", "Illuminance Setpoint at First Reference Point"},
{ Daylighting_ControlsFields::IlluminanceSetpointatSecondReferencePoint, "IlluminanceSetpointatSecondReferencePoint", "Illuminance Setpoint at Second Reference Point"},
{ Daylighting_ControlsFields::LightingControlType, "LightingControlType", "Lighting Control Type"},
{ Daylighting_ControlsFields::GlareCalculationAzimuthAngleofViewDirectionClockwisefromZoneyAxis, "GlareCalculationAzimuthAngleofViewDirectionClockwisefromZoneyAxis", "Glare Calculation Azimuth Angle of View Direction Clockwise from Zone y-Axis"},
{ Daylighting_ControlsFields::MaximumAllowableDiscomfortGlareIndex, "MaximumAllowableDiscomfortGlareIndex", "Maximum Allowable Discomfort Glare Index"},
{ Daylighting_ControlsFields::MinimumInputPowerFractionforContinuousDimmingControl, "MinimumInputPowerFractionforContinuousDimmingControl", "Minimum Input Power Fraction for Continuous Dimming Control"},
{ Daylighting_ControlsFields::MinimumLightOutputFractionforContinuousDimmingControl, "MinimumLightOutputFractionforContinuousDimmingControl", "Minimum Light Output Fraction for Continuous Dimming Control"},
{ Daylighting_ControlsFields::NumberofSteppedControlSteps, "NumberofSteppedControlSteps", "Number of Stepped Control Steps"},
{ Daylighting_ControlsFields::ProbabilityLightingwillbeResetWhenNeededinManualSteppedControl, "ProbabilityLightingwillbeResetWhenNeededinManualSteppedControl", "Probability Lighting will be Reset When Needed in Manual Stepped Control"},
{ Daylighting_ControlsFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
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

} // openstudio

#endif // UTILITIES_IDD_DAYLIGHTING_CONTROLS_FIELDENUMS_HXX
