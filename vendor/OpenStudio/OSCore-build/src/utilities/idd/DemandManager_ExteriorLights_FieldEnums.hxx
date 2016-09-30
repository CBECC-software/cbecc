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

#ifndef UTILITIES_IDD_DEMANDMANAGER_EXTERIORLIGHTS_FIELDENUMS_HXX
#define UTILITIES_IDD_DEMANDMANAGER_EXTERIORLIGHTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DemandManager_ExteriorLightsFields
 *  \brief Enumeration of DemandManager:ExteriorLights's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DemandManager_ExteriorLightsFields, )
#else
class DemandManager_ExteriorLightsFields: public ::EnumBase<DemandManager_ExteriorLightsFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, LimitControl, MinimumLimitDuration, MaximumLimitFraction, LimitStepChange, SelectionControl, RotationDuration,   };
  DemandManager_ExteriorLightsFields()
   : EnumBase<DemandManager_ExteriorLightsFields>(Name) {} 
  DemandManager_ExteriorLightsFields(const std::string &t_name) 
   : EnumBase<DemandManager_ExteriorLightsFields>(t_name) {} 
  DemandManager_ExteriorLightsFields(int t_value) 
   : EnumBase<DemandManager_ExteriorLightsFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_ExteriorLightsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_ExteriorLightsFields>::value()); }
   private:
    friend class EnumBase<DemandManager_ExteriorLightsFields>;
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
{ DemandManager_ExteriorLightsFields::Name, "Name", "Name"},
{ DemandManager_ExteriorLightsFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ DemandManager_ExteriorLightsFields::LimitControl, "LimitControl", "Limit Control"},
{ DemandManager_ExteriorLightsFields::MinimumLimitDuration, "MinimumLimitDuration", "Minimum Limit Duration"},
{ DemandManager_ExteriorLightsFields::MaximumLimitFraction, "MaximumLimitFraction", "Maximum Limit Fraction"},
{ DemandManager_ExteriorLightsFields::LimitStepChange, "LimitStepChange", "Limit Step Change"},
{ DemandManager_ExteriorLightsFields::SelectionControl, "SelectionControl", "Selection Control"},
{ DemandManager_ExteriorLightsFields::RotationDuration, "RotationDuration", "Rotation Duration"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_ExteriorLightsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_ExteriorLightsFields> OptionalDemandManager_ExteriorLightsFields ;
#endif

/** \class DemandManager_ExteriorLightsExtensibleFields
 *  \brief Enumeration of DemandManager:ExteriorLights's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(DemandManager_ExteriorLightsExtensibleFields, )
#else
class DemandManager_ExteriorLightsExtensibleFields: public ::EnumBase<DemandManager_ExteriorLightsExtensibleFields> {
 public: 
  enum domain 
  {
ExteriorLightsName,   };
  DemandManager_ExteriorLightsExtensibleFields()
   : EnumBase<DemandManager_ExteriorLightsExtensibleFields>(ExteriorLightsName) {} 
  DemandManager_ExteriorLightsExtensibleFields(const std::string &t_name) 
   : EnumBase<DemandManager_ExteriorLightsExtensibleFields>(t_name) {} 
  DemandManager_ExteriorLightsExtensibleFields(int t_value) 
   : EnumBase<DemandManager_ExteriorLightsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_ExteriorLightsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_ExteriorLightsExtensibleFields>::value()); }
   private:
    friend class EnumBase<DemandManager_ExteriorLightsExtensibleFields>;
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
{ DemandManager_ExteriorLightsExtensibleFields::ExteriorLightsName, "ExteriorLightsName", "Exterior Lights Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_ExteriorLightsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_ExteriorLightsExtensibleFields> OptionalDemandManager_ExteriorLightsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DEMANDMANAGER_EXTERIORLIGHTS_FIELDENUMS_HXX
