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

#ifndef UTILITIES_IDD_SETPOINTMANAGER_RETURNAIRBYPASSFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_SETPOINTMANAGER_RETURNAIRBYPASSFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SetpointManager_ReturnAirBypassFlowFields
 *  \brief Enumeration of SetpointManager:ReturnAirBypassFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SetpointManager_ReturnAirBypassFlowFields, )
#else
class SetpointManager_ReturnAirBypassFlowFields: public ::EnumBase<SetpointManager_ReturnAirBypassFlowFields> {
 public: 
  enum domain 
  {
Name, ControlVariable, HVACAirLoopName, TemperatureSetpointScheduleName,   };
  SetpointManager_ReturnAirBypassFlowFields()
   : EnumBase<SetpointManager_ReturnAirBypassFlowFields>(Name) {} 
  SetpointManager_ReturnAirBypassFlowFields(const std::string &t_name) 
   : EnumBase<SetpointManager_ReturnAirBypassFlowFields>(t_name) {} 
  SetpointManager_ReturnAirBypassFlowFields(int t_value) 
   : EnumBase<SetpointManager_ReturnAirBypassFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "SetpointManager_ReturnAirBypassFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SetpointManager_ReturnAirBypassFlowFields>::value()); }
   private:
    friend class EnumBase<SetpointManager_ReturnAirBypassFlowFields>;
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
{ SetpointManager_ReturnAirBypassFlowFields::Name, "Name", "Name"},
{ SetpointManager_ReturnAirBypassFlowFields::ControlVariable, "ControlVariable", "Control Variable"},
{ SetpointManager_ReturnAirBypassFlowFields::HVACAirLoopName, "HVACAirLoopName", "HVAC Air Loop Name"},
{ SetpointManager_ReturnAirBypassFlowFields::TemperatureSetpointScheduleName, "TemperatureSetpointScheduleName", "Temperature Setpoint Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SetpointManager_ReturnAirBypassFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SetpointManager_ReturnAirBypassFlowFields> OptionalSetpointManager_ReturnAirBypassFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SETPOINTMANAGER_RETURNAIRBYPASSFLOW_FIELDENUMS_HXX
