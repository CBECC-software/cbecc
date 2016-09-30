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

#ifndef UTILITIES_IDD_OS_FAN_ONOFF_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_FAN_ONOFF_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Fan_OnOffFields
 *  \brief Enumeration of OS:Fan:OnOff's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Fan_OnOffFields, )
#else
class OS_Fan_OnOffFields: public ::EnumBase<OS_Fan_OnOffFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, FanEfficiency, PressureRise, MaximumFlowRate, MotorEfficiency, MotorInAirstreamFraction, AirInletNodeName, AirOutletNodeName, FanPowerRatioFunctionofSpeedRatioCurveName, FanEfficiencyRatioFunctionofSpeedRatioCurveName, EndUseSubcategory,   };
  OS_Fan_OnOffFields()
   : EnumBase<OS_Fan_OnOffFields>(Handle) {} 
  OS_Fan_OnOffFields(const std::string &t_name) 
   : EnumBase<OS_Fan_OnOffFields>(t_name) {} 
  OS_Fan_OnOffFields(int t_value) 
   : EnumBase<OS_Fan_OnOffFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Fan_OnOffFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Fan_OnOffFields>::value()); }
   private:
    friend class EnumBase<OS_Fan_OnOffFields>;
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
{ OS_Fan_OnOffFields::Handle, "Handle", "Handle"},
{ OS_Fan_OnOffFields::Name, "Name", "Name"},
{ OS_Fan_OnOffFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Fan_OnOffFields::FanEfficiency, "FanEfficiency", "Fan Efficiency"},
{ OS_Fan_OnOffFields::PressureRise, "PressureRise", "Pressure Rise"},
{ OS_Fan_OnOffFields::MaximumFlowRate, "MaximumFlowRate", "Maximum Flow Rate"},
{ OS_Fan_OnOffFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ OS_Fan_OnOffFields::MotorInAirstreamFraction, "MotorInAirstreamFraction", "Motor In Airstream Fraction"},
{ OS_Fan_OnOffFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Fan_OnOffFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Fan_OnOffFields::FanPowerRatioFunctionofSpeedRatioCurveName, "FanPowerRatioFunctionofSpeedRatioCurveName", "Fan Power Ratio Function of Speed Ratio Curve Name"},
{ OS_Fan_OnOffFields::FanEfficiencyRatioFunctionofSpeedRatioCurveName, "FanEfficiencyRatioFunctionofSpeedRatioCurveName", "Fan Efficiency Ratio Function of Speed Ratio Curve Name"},
{ OS_Fan_OnOffFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Fan_OnOffFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Fan_OnOffFields> OptionalOS_Fan_OnOffFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_FAN_ONOFF_FIELDENUMS_HXX
