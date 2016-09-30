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

#ifndef UTILITIES_IDD_OS_SETPOINTMANAGER_WARMESTTEMPERATUREFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SETPOINTMANAGER_WARMESTTEMPERATUREFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SetpointManager_WarmestTemperatureFlowFields
 *  \brief Enumeration of OS:SetpointManager:WarmestTemperatureFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SetpointManager_WarmestTemperatureFlowFields, )
#else
class OS_SetpointManager_WarmestTemperatureFlowFields: public ::EnumBase<OS_SetpointManager_WarmestTemperatureFlowFields> {
 public: 
  enum domain 
  {
Handle, Name, ControlVariable, MinimumSetpointTemperature, MaximumSetpointTemperature, Strategy, SetpointNodeorNodeListName, MinimumTurndownRatio,   };
  OS_SetpointManager_WarmestTemperatureFlowFields()
   : EnumBase<OS_SetpointManager_WarmestTemperatureFlowFields>(Handle) {} 
  OS_SetpointManager_WarmestTemperatureFlowFields(const std::string &t_name) 
   : EnumBase<OS_SetpointManager_WarmestTemperatureFlowFields>(t_name) {} 
  OS_SetpointManager_WarmestTemperatureFlowFields(int t_value) 
   : EnumBase<OS_SetpointManager_WarmestTemperatureFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SetpointManager_WarmestTemperatureFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SetpointManager_WarmestTemperatureFlowFields>::value()); }
   private:
    friend class EnumBase<OS_SetpointManager_WarmestTemperatureFlowFields>;
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
{ OS_SetpointManager_WarmestTemperatureFlowFields::Handle, "Handle", "Handle"},
{ OS_SetpointManager_WarmestTemperatureFlowFields::Name, "Name", "Name"},
{ OS_SetpointManager_WarmestTemperatureFlowFields::ControlVariable, "ControlVariable", "Control Variable"},
{ OS_SetpointManager_WarmestTemperatureFlowFields::MinimumSetpointTemperature, "MinimumSetpointTemperature", "Minimum Setpoint Temperature"},
{ OS_SetpointManager_WarmestTemperatureFlowFields::MaximumSetpointTemperature, "MaximumSetpointTemperature", "Maximum Setpoint Temperature"},
{ OS_SetpointManager_WarmestTemperatureFlowFields::Strategy, "Strategy", "Strategy"},
{ OS_SetpointManager_WarmestTemperatureFlowFields::SetpointNodeorNodeListName, "SetpointNodeorNodeListName", "Setpoint Node or NodeList Name"},
{ OS_SetpointManager_WarmestTemperatureFlowFields::MinimumTurndownRatio, "MinimumTurndownRatio", "Minimum Turndown Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SetpointManager_WarmestTemperatureFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SetpointManager_WarmestTemperatureFlowFields> OptionalOS_SetpointManager_WarmestTemperatureFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SETPOINTMANAGER_WARMESTTEMPERATUREFLOW_FIELDENUMS_HXX
