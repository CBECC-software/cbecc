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

#ifndef UTILITIES_IDD_ZONECONTROL_THERMOSTAT_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONECONTROL_THERMOSTAT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneControl_ThermostatFields
 *  \brief Enumeration of ZoneControl:Thermostat's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneControl_ThermostatFields, )
#else
class ZoneControl_ThermostatFields: public ::EnumBase<ZoneControl_ThermostatFields> {
 public: 
  enum domain 
  {
Name, ZoneorZoneListName, ControlTypeScheduleName,   };
  ZoneControl_ThermostatFields()
   : EnumBase<ZoneControl_ThermostatFields>(Name) {} 
  ZoneControl_ThermostatFields(const std::string &t_name) 
   : EnumBase<ZoneControl_ThermostatFields>(t_name) {} 
  ZoneControl_ThermostatFields(int t_value) 
   : EnumBase<ZoneControl_ThermostatFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneControl_ThermostatFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneControl_ThermostatFields>::value()); }
   private:
    friend class EnumBase<ZoneControl_ThermostatFields>;
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
{ ZoneControl_ThermostatFields::Name, "Name", "Name"},
{ ZoneControl_ThermostatFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ ZoneControl_ThermostatFields::ControlTypeScheduleName, "ControlTypeScheduleName", "Control Type Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneControl_ThermostatFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneControl_ThermostatFields> OptionalZoneControl_ThermostatFields ;
#endif

/** \class ZoneControl_ThermostatExtensibleFields
 *  \brief Enumeration of ZoneControl:Thermostat's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneControl_ThermostatExtensibleFields, )
#else
class ZoneControl_ThermostatExtensibleFields: public ::EnumBase<ZoneControl_ThermostatExtensibleFields> {
 public: 
  enum domain 
  {
ControlObjectType, ControlName,   };
  ZoneControl_ThermostatExtensibleFields()
   : EnumBase<ZoneControl_ThermostatExtensibleFields>(ControlObjectType) {} 
  ZoneControl_ThermostatExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneControl_ThermostatExtensibleFields>(t_name) {} 
  ZoneControl_ThermostatExtensibleFields(int t_value) 
   : EnumBase<ZoneControl_ThermostatExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneControl_ThermostatExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneControl_ThermostatExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneControl_ThermostatExtensibleFields>;
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
{ ZoneControl_ThermostatExtensibleFields::ControlObjectType, "ControlObjectType", "Control Object Type"},
{ ZoneControl_ThermostatExtensibleFields::ControlName, "ControlName", "Control Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneControl_ThermostatExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneControl_ThermostatExtensibleFields> OptionalZoneControl_ThermostatExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONECONTROL_THERMOSTAT_FIELDENUMS_HXX
