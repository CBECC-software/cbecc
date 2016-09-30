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

#ifndef UTILITIES_IDD_OS_CONTROLLER_MECHANICALVENTILATION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CONTROLLER_MECHANICALVENTILATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Controller_MechanicalVentilationFields
 *  \brief Enumeration of OS:Controller:MechanicalVentilation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Controller_MechanicalVentilationFields, )
#else
class OS_Controller_MechanicalVentilationFields: public ::EnumBase<OS_Controller_MechanicalVentilationFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, DemandControlledVentilation, SystemOutdoorAirMethod,   };
  OS_Controller_MechanicalVentilationFields()
   : EnumBase<OS_Controller_MechanicalVentilationFields>(Handle) {} 
  OS_Controller_MechanicalVentilationFields(const std::string &t_name) 
   : EnumBase<OS_Controller_MechanicalVentilationFields>(t_name) {} 
  OS_Controller_MechanicalVentilationFields(int t_value) 
   : EnumBase<OS_Controller_MechanicalVentilationFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Controller_MechanicalVentilationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Controller_MechanicalVentilationFields>::value()); }
   private:
    friend class EnumBase<OS_Controller_MechanicalVentilationFields>;
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
{ OS_Controller_MechanicalVentilationFields::Handle, "Handle", "Handle"},
{ OS_Controller_MechanicalVentilationFields::Name, "Name", "Name"},
{ OS_Controller_MechanicalVentilationFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_Controller_MechanicalVentilationFields::DemandControlledVentilation, "DemandControlledVentilation", "Demand Controlled Ventilation"},
{ OS_Controller_MechanicalVentilationFields::SystemOutdoorAirMethod, "SystemOutdoorAirMethod", "System Outdoor Air Method"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Controller_MechanicalVentilationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Controller_MechanicalVentilationFields> OptionalOS_Controller_MechanicalVentilationFields ;
#endif

/** \class OS_Controller_MechanicalVentilationExtensibleFields
 *  \brief Enumeration of OS:Controller:MechanicalVentilation's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Controller_MechanicalVentilationExtensibleFields, )
#else
class OS_Controller_MechanicalVentilationExtensibleFields: public ::EnumBase<OS_Controller_MechanicalVentilationExtensibleFields> {
 public: 
  enum domain 
  {
ThermalZone, DesignSpecificationOutdoorAirObject, DesignSpecificationZoneAirDistributionObject,   };
  OS_Controller_MechanicalVentilationExtensibleFields()
   : EnumBase<OS_Controller_MechanicalVentilationExtensibleFields>(ThermalZone) {} 
  OS_Controller_MechanicalVentilationExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Controller_MechanicalVentilationExtensibleFields>(t_name) {} 
  OS_Controller_MechanicalVentilationExtensibleFields(int t_value) 
   : EnumBase<OS_Controller_MechanicalVentilationExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Controller_MechanicalVentilationExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Controller_MechanicalVentilationExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Controller_MechanicalVentilationExtensibleFields>;
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
{ OS_Controller_MechanicalVentilationExtensibleFields::ThermalZone, "ThermalZone", "Thermal Zone"},
{ OS_Controller_MechanicalVentilationExtensibleFields::DesignSpecificationOutdoorAirObject, "DesignSpecificationOutdoorAirObject", "Design Specification Outdoor Air Object"},
{ OS_Controller_MechanicalVentilationExtensibleFields::DesignSpecificationZoneAirDistributionObject, "DesignSpecificationZoneAirDistributionObject", "Design Specification Zone Air Distribution Object"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Controller_MechanicalVentilationExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Controller_MechanicalVentilationExtensibleFields> OptionalOS_Controller_MechanicalVentilationExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CONTROLLER_MECHANICALVENTILATION_FIELDENUMS_HXX
