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

#ifndef UTILITIES_IDD_DAYLIGHTINGDEVICE_TUBULAR_FIELDENUMS_HXX
#define UTILITIES_IDD_DAYLIGHTINGDEVICE_TUBULAR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DaylightingDevice_TubularFields
 *  \brief Enumeration of DaylightingDevice:Tubular's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DaylightingDevice_TubularFields, )
#else
class DaylightingDevice_TubularFields: public ::EnumBase<DaylightingDevice_TubularFields> {
 public: 
  enum domain 
  {
Name, DomeName, DiffuserName, ConstructionName, Diameter, TotalLength, EffectiveThermalResistance,   };
  DaylightingDevice_TubularFields()
   : EnumBase<DaylightingDevice_TubularFields>(Name) {} 
  DaylightingDevice_TubularFields(const std::string &t_name) 
   : EnumBase<DaylightingDevice_TubularFields>(t_name) {} 
  DaylightingDevice_TubularFields(int t_value) 
   : EnumBase<DaylightingDevice_TubularFields>(t_value) {} 
  static std::string enumName() 
  { return "DaylightingDevice_TubularFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DaylightingDevice_TubularFields>::value()); }
   private:
    friend class EnumBase<DaylightingDevice_TubularFields>;
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
{ DaylightingDevice_TubularFields::Name, "Name", "Name"},
{ DaylightingDevice_TubularFields::DomeName, "DomeName", "Dome Name"},
{ DaylightingDevice_TubularFields::DiffuserName, "DiffuserName", "Diffuser Name"},
{ DaylightingDevice_TubularFields::ConstructionName, "ConstructionName", "Construction Name"},
{ DaylightingDevice_TubularFields::Diameter, "Diameter", "Diameter"},
{ DaylightingDevice_TubularFields::TotalLength, "TotalLength", "Total Length"},
{ DaylightingDevice_TubularFields::EffectiveThermalResistance, "EffectiveThermalResistance", "Effective Thermal Resistance"},
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
  inline std::ostream &operator<<(std::ostream &os, const DaylightingDevice_TubularFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DaylightingDevice_TubularFields> OptionalDaylightingDevice_TubularFields ;
#endif

/** \class DaylightingDevice_TubularExtensibleFields
 *  \brief Enumeration of DaylightingDevice:Tubular's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(DaylightingDevice_TubularExtensibleFields, )
#else
class DaylightingDevice_TubularExtensibleFields: public ::EnumBase<DaylightingDevice_TubularExtensibleFields> {
 public: 
  enum domain 
  {
TransitionZoneName, TransitionZoneLength,   };
  DaylightingDevice_TubularExtensibleFields()
   : EnumBase<DaylightingDevice_TubularExtensibleFields>(TransitionZoneName) {} 
  DaylightingDevice_TubularExtensibleFields(const std::string &t_name) 
   : EnumBase<DaylightingDevice_TubularExtensibleFields>(t_name) {} 
  DaylightingDevice_TubularExtensibleFields(int t_value) 
   : EnumBase<DaylightingDevice_TubularExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "DaylightingDevice_TubularExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DaylightingDevice_TubularExtensibleFields>::value()); }
   private:
    friend class EnumBase<DaylightingDevice_TubularExtensibleFields>;
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
{ DaylightingDevice_TubularExtensibleFields::TransitionZoneName, "TransitionZoneName", "Transition Zone Name"},
{ DaylightingDevice_TubularExtensibleFields::TransitionZoneLength, "TransitionZoneLength", "Transition Zone Length"},
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
  inline std::ostream &operator<<(std::ostream &os, const DaylightingDevice_TubularExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DaylightingDevice_TubularExtensibleFields> OptionalDaylightingDevice_TubularExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DAYLIGHTINGDEVICE_TUBULAR_FIELDENUMS_HXX
