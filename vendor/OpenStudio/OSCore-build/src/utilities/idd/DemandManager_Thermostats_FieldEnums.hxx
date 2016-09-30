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

#ifndef UTILITIES_IDD_DEMANDMANAGER_THERMOSTATS_FIELDENUMS_HXX
#define UTILITIES_IDD_DEMANDMANAGER_THERMOSTATS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DemandManager_ThermostatsFields
 *  \brief Enumeration of DemandManager:Thermostats's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DemandManager_ThermostatsFields, )
#else
class DemandManager_ThermostatsFields: public ::EnumBase<DemandManager_ThermostatsFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ResetControl, MinimumResetDuration, MaximumHeatingSetpointReset, MaximumCoolingSetpointReset, ResetStepChange, SelectionControl, RotationDuration,   };
  DemandManager_ThermostatsFields()
   : EnumBase<DemandManager_ThermostatsFields>(Name) {} 
  DemandManager_ThermostatsFields(const std::string &t_name) 
   : EnumBase<DemandManager_ThermostatsFields>(t_name) {} 
  DemandManager_ThermostatsFields(int t_value) 
   : EnumBase<DemandManager_ThermostatsFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_ThermostatsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_ThermostatsFields>::value()); }
   private:
    friend class EnumBase<DemandManager_ThermostatsFields>;
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
{ DemandManager_ThermostatsFields::Name, "Name", "Name"},
{ DemandManager_ThermostatsFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ DemandManager_ThermostatsFields::ResetControl, "ResetControl", "Reset Control"},
{ DemandManager_ThermostatsFields::MinimumResetDuration, "MinimumResetDuration", "Minimum Reset Duration"},
{ DemandManager_ThermostatsFields::MaximumHeatingSetpointReset, "MaximumHeatingSetpointReset", "Maximum Heating Setpoint Reset"},
{ DemandManager_ThermostatsFields::MaximumCoolingSetpointReset, "MaximumCoolingSetpointReset", "Maximum Cooling Setpoint Reset"},
{ DemandManager_ThermostatsFields::ResetStepChange, "ResetStepChange", "Reset Step Change"},
{ DemandManager_ThermostatsFields::SelectionControl, "SelectionControl", "Selection Control"},
{ DemandManager_ThermostatsFields::RotationDuration, "RotationDuration", "Rotation Duration"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_ThermostatsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_ThermostatsFields> OptionalDemandManager_ThermostatsFields ;
#endif

/** \class DemandManager_ThermostatsExtensibleFields
 *  \brief Enumeration of DemandManager:Thermostats's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(DemandManager_ThermostatsExtensibleFields, )
#else
class DemandManager_ThermostatsExtensibleFields: public ::EnumBase<DemandManager_ThermostatsExtensibleFields> {
 public: 
  enum domain 
  {
ThermostatName,   };
  DemandManager_ThermostatsExtensibleFields()
   : EnumBase<DemandManager_ThermostatsExtensibleFields>(ThermostatName) {} 
  DemandManager_ThermostatsExtensibleFields(const std::string &t_name) 
   : EnumBase<DemandManager_ThermostatsExtensibleFields>(t_name) {} 
  DemandManager_ThermostatsExtensibleFields(int t_value) 
   : EnumBase<DemandManager_ThermostatsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_ThermostatsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_ThermostatsExtensibleFields>::value()); }
   private:
    friend class EnumBase<DemandManager_ThermostatsExtensibleFields>;
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
{ DemandManager_ThermostatsExtensibleFields::ThermostatName, "ThermostatName", "Thermostat Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_ThermostatsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_ThermostatsExtensibleFields> OptionalDemandManager_ThermostatsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DEMANDMANAGER_THERMOSTATS_FIELDENUMS_HXX
