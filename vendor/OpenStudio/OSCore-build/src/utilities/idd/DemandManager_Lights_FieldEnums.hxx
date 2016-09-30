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

#ifndef UTILITIES_IDD_DEMANDMANAGER_LIGHTS_FIELDENUMS_HXX
#define UTILITIES_IDD_DEMANDMANAGER_LIGHTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DemandManager_LightsFields
 *  \brief Enumeration of DemandManager:Lights's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DemandManager_LightsFields, )
#else
class DemandManager_LightsFields: public ::EnumBase<DemandManager_LightsFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, LimitControl, MinimumLimitDuration, MaximumLimitFraction, LimitStepChange, SelectionControl, RotationDuration,   };
  DemandManager_LightsFields()
   : EnumBase<DemandManager_LightsFields>(Name) {} 
  DemandManager_LightsFields(const std::string &t_name) 
   : EnumBase<DemandManager_LightsFields>(t_name) {} 
  DemandManager_LightsFields(int t_value) 
   : EnumBase<DemandManager_LightsFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_LightsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_LightsFields>::value()); }
   private:
    friend class EnumBase<DemandManager_LightsFields>;
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
{ DemandManager_LightsFields::Name, "Name", "Name"},
{ DemandManager_LightsFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ DemandManager_LightsFields::LimitControl, "LimitControl", "Limit Control"},
{ DemandManager_LightsFields::MinimumLimitDuration, "MinimumLimitDuration", "Minimum Limit Duration"},
{ DemandManager_LightsFields::MaximumLimitFraction, "MaximumLimitFraction", "Maximum Limit Fraction"},
{ DemandManager_LightsFields::LimitStepChange, "LimitStepChange", "Limit Step Change"},
{ DemandManager_LightsFields::SelectionControl, "SelectionControl", "Selection Control"},
{ DemandManager_LightsFields::RotationDuration, "RotationDuration", "Rotation Duration"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_LightsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_LightsFields> OptionalDemandManager_LightsFields ;
#endif

/** \class DemandManager_LightsExtensibleFields
 *  \brief Enumeration of DemandManager:Lights's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(DemandManager_LightsExtensibleFields, )
#else
class DemandManager_LightsExtensibleFields: public ::EnumBase<DemandManager_LightsExtensibleFields> {
 public: 
  enum domain 
  {
LightsName,   };
  DemandManager_LightsExtensibleFields()
   : EnumBase<DemandManager_LightsExtensibleFields>(LightsName) {} 
  DemandManager_LightsExtensibleFields(const std::string &t_name) 
   : EnumBase<DemandManager_LightsExtensibleFields>(t_name) {} 
  DemandManager_LightsExtensibleFields(int t_value) 
   : EnumBase<DemandManager_LightsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_LightsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_LightsExtensibleFields>::value()); }
   private:
    friend class EnumBase<DemandManager_LightsExtensibleFields>;
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
{ DemandManager_LightsExtensibleFields::LightsName, "LightsName", "Lights Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_LightsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_LightsExtensibleFields> OptionalDemandManager_LightsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DEMANDMANAGER_LIGHTS_FIELDENUMS_HXX
