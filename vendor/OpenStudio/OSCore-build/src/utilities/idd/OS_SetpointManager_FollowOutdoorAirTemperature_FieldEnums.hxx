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

#ifndef UTILITIES_IDD_OS_SETPOINTMANAGER_FOLLOWOUTDOORAIRTEMPERATURE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SETPOINTMANAGER_FOLLOWOUTDOORAIRTEMPERATURE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SetpointManager_FollowOutdoorAirTemperatureFields
 *  \brief Enumeration of OS:SetpointManager:FollowOutdoorAirTemperature's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SetpointManager_FollowOutdoorAirTemperatureFields, )
#else
class OS_SetpointManager_FollowOutdoorAirTemperatureFields: public ::EnumBase<OS_SetpointManager_FollowOutdoorAirTemperatureFields> {
 public: 
  enum domain 
  {
Handle, Name, ControlVariable, ReferenceTemperatureType, OffsetTemperatureDifference, MaximumSetpointTemperature, MinimumSetpointTemperature, SetpointNodeorNodeListName,   };
  OS_SetpointManager_FollowOutdoorAirTemperatureFields()
   : EnumBase<OS_SetpointManager_FollowOutdoorAirTemperatureFields>(Handle) {} 
  OS_SetpointManager_FollowOutdoorAirTemperatureFields(const std::string &t_name) 
   : EnumBase<OS_SetpointManager_FollowOutdoorAirTemperatureFields>(t_name) {} 
  OS_SetpointManager_FollowOutdoorAirTemperatureFields(int t_value) 
   : EnumBase<OS_SetpointManager_FollowOutdoorAirTemperatureFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SetpointManager_FollowOutdoorAirTemperatureFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SetpointManager_FollowOutdoorAirTemperatureFields>::value()); }
   private:
    friend class EnumBase<OS_SetpointManager_FollowOutdoorAirTemperatureFields>;
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
{ OS_SetpointManager_FollowOutdoorAirTemperatureFields::Handle, "Handle", "Handle"},
{ OS_SetpointManager_FollowOutdoorAirTemperatureFields::Name, "Name", "Name"},
{ OS_SetpointManager_FollowOutdoorAirTemperatureFields::ControlVariable, "ControlVariable", "Control Variable"},
{ OS_SetpointManager_FollowOutdoorAirTemperatureFields::ReferenceTemperatureType, "ReferenceTemperatureType", "Reference Temperature Type"},
{ OS_SetpointManager_FollowOutdoorAirTemperatureFields::OffsetTemperatureDifference, "OffsetTemperatureDifference", "Offset Temperature Difference"},
{ OS_SetpointManager_FollowOutdoorAirTemperatureFields::MaximumSetpointTemperature, "MaximumSetpointTemperature", "Maximum Setpoint Temperature"},
{ OS_SetpointManager_FollowOutdoorAirTemperatureFields::MinimumSetpointTemperature, "MinimumSetpointTemperature", "Minimum Setpoint Temperature"},
{ OS_SetpointManager_FollowOutdoorAirTemperatureFields::SetpointNodeorNodeListName, "SetpointNodeorNodeListName", "Setpoint Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SetpointManager_FollowOutdoorAirTemperatureFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SetpointManager_FollowOutdoorAirTemperatureFields> OptionalOS_SetpointManager_FollowOutdoorAirTemperatureFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SETPOINTMANAGER_FOLLOWOUTDOORAIRTEMPERATURE_FIELDENUMS_HXX
