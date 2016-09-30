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

#ifndef UTILITIES_IDD_ZONECONTROL_THERMOSTAT_THERMALCOMFORT_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONECONTROL_THERMOSTAT_THERMALCOMFORT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneControl_Thermostat_ThermalComfortFields
 *  \brief Enumeration of ZoneControl:Thermostat:ThermalComfort's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneControl_Thermostat_ThermalComfortFields, )
#else
class ZoneControl_Thermostat_ThermalComfortFields: public ::EnumBase<ZoneControl_Thermostat_ThermalComfortFields> {
 public: 
  enum domain 
  {
Name, ZoneorZoneListName, AveragingMethod, SpecificPeopleName, MinimumDryBulbTemperatureSetpoint, MaximumDryBulbTemperatureSetpoint, ThermalComfortControlTypeScheduleName,   };
  ZoneControl_Thermostat_ThermalComfortFields()
   : EnumBase<ZoneControl_Thermostat_ThermalComfortFields>(Name) {} 
  ZoneControl_Thermostat_ThermalComfortFields(const std::string &t_name) 
   : EnumBase<ZoneControl_Thermostat_ThermalComfortFields>(t_name) {} 
  ZoneControl_Thermostat_ThermalComfortFields(int t_value) 
   : EnumBase<ZoneControl_Thermostat_ThermalComfortFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneControl_Thermostat_ThermalComfortFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneControl_Thermostat_ThermalComfortFields>::value()); }
   private:
    friend class EnumBase<ZoneControl_Thermostat_ThermalComfortFields>;
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
{ ZoneControl_Thermostat_ThermalComfortFields::Name, "Name", "Name"},
{ ZoneControl_Thermostat_ThermalComfortFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ ZoneControl_Thermostat_ThermalComfortFields::AveragingMethod, "AveragingMethod", "Averaging Method"},
{ ZoneControl_Thermostat_ThermalComfortFields::SpecificPeopleName, "SpecificPeopleName", "Specific People Name"},
{ ZoneControl_Thermostat_ThermalComfortFields::MinimumDryBulbTemperatureSetpoint, "MinimumDryBulbTemperatureSetpoint", "Minimum Dry-Bulb Temperature Setpoint"},
{ ZoneControl_Thermostat_ThermalComfortFields::MaximumDryBulbTemperatureSetpoint, "MaximumDryBulbTemperatureSetpoint", "Maximum Dry-Bulb Temperature Setpoint"},
{ ZoneControl_Thermostat_ThermalComfortFields::ThermalComfortControlTypeScheduleName, "ThermalComfortControlTypeScheduleName", "Thermal Comfort Control Type Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneControl_Thermostat_ThermalComfortFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneControl_Thermostat_ThermalComfortFields> OptionalZoneControl_Thermostat_ThermalComfortFields ;
#endif

/** \class ZoneControl_Thermostat_ThermalComfortExtensibleFields
 *  \brief Enumeration of ZoneControl:Thermostat:ThermalComfort's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneControl_Thermostat_ThermalComfortExtensibleFields, )
#else
class ZoneControl_Thermostat_ThermalComfortExtensibleFields: public ::EnumBase<ZoneControl_Thermostat_ThermalComfortExtensibleFields> {
 public: 
  enum domain 
  {
ThermalComfortControlObjectType, ThermalComfortControlName,   };
  ZoneControl_Thermostat_ThermalComfortExtensibleFields()
   : EnumBase<ZoneControl_Thermostat_ThermalComfortExtensibleFields>(ThermalComfortControlObjectType) {} 
  ZoneControl_Thermostat_ThermalComfortExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneControl_Thermostat_ThermalComfortExtensibleFields>(t_name) {} 
  ZoneControl_Thermostat_ThermalComfortExtensibleFields(int t_value) 
   : EnumBase<ZoneControl_Thermostat_ThermalComfortExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneControl_Thermostat_ThermalComfortExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneControl_Thermostat_ThermalComfortExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneControl_Thermostat_ThermalComfortExtensibleFields>;
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
{ ZoneControl_Thermostat_ThermalComfortExtensibleFields::ThermalComfortControlObjectType, "ThermalComfortControlObjectType", "Thermal Comfort Control Object Type"},
{ ZoneControl_Thermostat_ThermalComfortExtensibleFields::ThermalComfortControlName, "ThermalComfortControlName", "Thermal Comfort Control Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneControl_Thermostat_ThermalComfortExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneControl_Thermostat_ThermalComfortExtensibleFields> OptionalZoneControl_Thermostat_ThermalComfortExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONECONTROL_THERMOSTAT_THERMALCOMFORT_FIELDENUMS_HXX
