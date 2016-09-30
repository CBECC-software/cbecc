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

#ifndef UTILITIES_IDD_SETPOINTMANAGER_SINGLEZONE_REHEAT_FIELDENUMS_HXX
#define UTILITIES_IDD_SETPOINTMANAGER_SINGLEZONE_REHEAT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SetpointManager_SingleZone_ReheatFields
 *  \brief Enumeration of SetpointManager:SingleZone:Reheat's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SetpointManager_SingleZone_ReheatFields, )
#else
class SetpointManager_SingleZone_ReheatFields: public ::EnumBase<SetpointManager_SingleZone_ReheatFields> {
 public: 
  enum domain 
  {
Name, ControlVariable, MinimumSupplyAirTemperature, MaximumSupplyAirTemperature, ControlZoneName, ZoneNodeName, ZoneInletNodeName, SetpointNodeorNodeListName,   };
  SetpointManager_SingleZone_ReheatFields()
   : EnumBase<SetpointManager_SingleZone_ReheatFields>(Name) {} 
  SetpointManager_SingleZone_ReheatFields(const std::string &t_name) 
   : EnumBase<SetpointManager_SingleZone_ReheatFields>(t_name) {} 
  SetpointManager_SingleZone_ReheatFields(int t_value) 
   : EnumBase<SetpointManager_SingleZone_ReheatFields>(t_value) {} 
  static std::string enumName() 
  { return "SetpointManager_SingleZone_ReheatFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SetpointManager_SingleZone_ReheatFields>::value()); }
   private:
    friend class EnumBase<SetpointManager_SingleZone_ReheatFields>;
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
{ SetpointManager_SingleZone_ReheatFields::Name, "Name", "Name"},
{ SetpointManager_SingleZone_ReheatFields::ControlVariable, "ControlVariable", "Control Variable"},
{ SetpointManager_SingleZone_ReheatFields::MinimumSupplyAirTemperature, "MinimumSupplyAirTemperature", "Minimum Supply Air Temperature"},
{ SetpointManager_SingleZone_ReheatFields::MaximumSupplyAirTemperature, "MaximumSupplyAirTemperature", "Maximum Supply Air Temperature"},
{ SetpointManager_SingleZone_ReheatFields::ControlZoneName, "ControlZoneName", "Control Zone Name"},
{ SetpointManager_SingleZone_ReheatFields::ZoneNodeName, "ZoneNodeName", "Zone Node Name"},
{ SetpointManager_SingleZone_ReheatFields::ZoneInletNodeName, "ZoneInletNodeName", "Zone Inlet Node Name"},
{ SetpointManager_SingleZone_ReheatFields::SetpointNodeorNodeListName, "SetpointNodeorNodeListName", "Setpoint Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SetpointManager_SingleZone_ReheatFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SetpointManager_SingleZone_ReheatFields> OptionalSetpointManager_SingleZone_ReheatFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SETPOINTMANAGER_SINGLEZONE_REHEAT_FIELDENUMS_HXX
