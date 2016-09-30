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

#ifndef UTILITIES_IDD_SETPOINTMANAGER_MULTIZONE_HUMIDITY_MINIMUM_FIELDENUMS_HXX
#define UTILITIES_IDD_SETPOINTMANAGER_MULTIZONE_HUMIDITY_MINIMUM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SetpointManager_MultiZone_Humidity_MinimumFields
 *  \brief Enumeration of SetpointManager:MultiZone:Humidity:Minimum's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SetpointManager_MultiZone_Humidity_MinimumFields, )
#else
class SetpointManager_MultiZone_Humidity_MinimumFields: public ::EnumBase<SetpointManager_MultiZone_Humidity_MinimumFields> {
 public: 
  enum domain 
  {
Name, HVACAirLoopName, MinimumSetpointHumidityRatio, MaximumSetpointHumidityRatio, SetpointNodeorNodeListName,   };
  SetpointManager_MultiZone_Humidity_MinimumFields()
   : EnumBase<SetpointManager_MultiZone_Humidity_MinimumFields>(Name) {} 
  SetpointManager_MultiZone_Humidity_MinimumFields(const std::string &t_name) 
   : EnumBase<SetpointManager_MultiZone_Humidity_MinimumFields>(t_name) {} 
  SetpointManager_MultiZone_Humidity_MinimumFields(int t_value) 
   : EnumBase<SetpointManager_MultiZone_Humidity_MinimumFields>(t_value) {} 
  static std::string enumName() 
  { return "SetpointManager_MultiZone_Humidity_MinimumFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SetpointManager_MultiZone_Humidity_MinimumFields>::value()); }
   private:
    friend class EnumBase<SetpointManager_MultiZone_Humidity_MinimumFields>;
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
{ SetpointManager_MultiZone_Humidity_MinimumFields::Name, "Name", "Name"},
{ SetpointManager_MultiZone_Humidity_MinimumFields::HVACAirLoopName, "HVACAirLoopName", "HVAC Air Loop Name"},
{ SetpointManager_MultiZone_Humidity_MinimumFields::MinimumSetpointHumidityRatio, "MinimumSetpointHumidityRatio", "Minimum Setpoint Humidity Ratio"},
{ SetpointManager_MultiZone_Humidity_MinimumFields::MaximumSetpointHumidityRatio, "MaximumSetpointHumidityRatio", "Maximum Setpoint Humidity Ratio"},
{ SetpointManager_MultiZone_Humidity_MinimumFields::SetpointNodeorNodeListName, "SetpointNodeorNodeListName", "Setpoint Node or NodeList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SetpointManager_MultiZone_Humidity_MinimumFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SetpointManager_MultiZone_Humidity_MinimumFields> OptionalSetpointManager_MultiZone_Humidity_MinimumFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SETPOINTMANAGER_MULTIZONE_HUMIDITY_MINIMUM_FIELDENUMS_HXX
