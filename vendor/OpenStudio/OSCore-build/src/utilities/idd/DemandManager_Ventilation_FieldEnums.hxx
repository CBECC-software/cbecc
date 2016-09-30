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

#ifndef UTILITIES_IDD_DEMANDMANAGER_VENTILATION_FIELDENUMS_HXX
#define UTILITIES_IDD_DEMANDMANAGER_VENTILATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DemandManager_VentilationFields
 *  \brief Enumeration of DemandManager:Ventilation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DemandManager_VentilationFields, )
#else
class DemandManager_VentilationFields: public ::EnumBase<DemandManager_VentilationFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, LimitControl, MinimumLimitDuration, FixedRate, ReductionRatio, LimitStepChange, SelectionControl, RotationDuration,   };
  DemandManager_VentilationFields()
   : EnumBase<DemandManager_VentilationFields>(Name) {} 
  DemandManager_VentilationFields(const std::string &t_name) 
   : EnumBase<DemandManager_VentilationFields>(t_name) {} 
  DemandManager_VentilationFields(int t_value) 
   : EnumBase<DemandManager_VentilationFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_VentilationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_VentilationFields>::value()); }
   private:
    friend class EnumBase<DemandManager_VentilationFields>;
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
{ DemandManager_VentilationFields::Name, "Name", "Name"},
{ DemandManager_VentilationFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ DemandManager_VentilationFields::LimitControl, "LimitControl", "Limit Control"},
{ DemandManager_VentilationFields::MinimumLimitDuration, "MinimumLimitDuration", "Minimum Limit Duration"},
{ DemandManager_VentilationFields::FixedRate, "FixedRate", "Fixed Rate"},
{ DemandManager_VentilationFields::ReductionRatio, "ReductionRatio", "Reduction Ratio"},
{ DemandManager_VentilationFields::LimitStepChange, "LimitStepChange", "Limit Step Change"},
{ DemandManager_VentilationFields::SelectionControl, "SelectionControl", "Selection Control"},
{ DemandManager_VentilationFields::RotationDuration, "RotationDuration", "Rotation Duration"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_VentilationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_VentilationFields> OptionalDemandManager_VentilationFields ;
#endif

/** \class DemandManager_VentilationExtensibleFields
 *  \brief Enumeration of DemandManager:Ventilation's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(DemandManager_VentilationExtensibleFields, )
#else
class DemandManager_VentilationExtensibleFields: public ::EnumBase<DemandManager_VentilationExtensibleFields> {
 public: 
  enum domain 
  {
ControllerOutdoorAirName,   };
  DemandManager_VentilationExtensibleFields()
   : EnumBase<DemandManager_VentilationExtensibleFields>(ControllerOutdoorAirName) {} 
  DemandManager_VentilationExtensibleFields(const std::string &t_name) 
   : EnumBase<DemandManager_VentilationExtensibleFields>(t_name) {} 
  DemandManager_VentilationExtensibleFields(int t_value) 
   : EnumBase<DemandManager_VentilationExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "DemandManager_VentilationExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DemandManager_VentilationExtensibleFields>::value()); }
   private:
    friend class EnumBase<DemandManager_VentilationExtensibleFields>;
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
{ DemandManager_VentilationExtensibleFields::ControllerOutdoorAirName, "ControllerOutdoorAirName", "Controller Outdoor Air Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const DemandManager_VentilationExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DemandManager_VentilationExtensibleFields> OptionalDemandManager_VentilationExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DEMANDMANAGER_VENTILATION_FIELDENUMS_HXX
