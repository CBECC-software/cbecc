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

#ifndef UTILITIES_IDD_OS_LIGHTINGDESIGNDAY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_LIGHTINGDESIGNDAY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_LightingDesignDayFields
 *  \brief Enumeration of OS:LightingDesignDay's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_LightingDesignDayFields, )
#else
class OS_LightingDesignDayFields: public ::EnumBase<OS_LightingDesignDayFields> {
 public: 
  enum domain 
  {
Handle, Name, CIESkyModel, SnowIndicator, Month, DayofMonth,   };
  OS_LightingDesignDayFields()
   : EnumBase<OS_LightingDesignDayFields>(Handle) {} 
  OS_LightingDesignDayFields(const std::string &t_name) 
   : EnumBase<OS_LightingDesignDayFields>(t_name) {} 
  OS_LightingDesignDayFields(int t_value) 
   : EnumBase<OS_LightingDesignDayFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_LightingDesignDayFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_LightingDesignDayFields>::value()); }
   private:
    friend class EnumBase<OS_LightingDesignDayFields>;
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
{ OS_LightingDesignDayFields::Handle, "Handle", "Handle"},
{ OS_LightingDesignDayFields::Name, "Name", "Name"},
{ OS_LightingDesignDayFields::CIESkyModel, "CIESkyModel", "CIE Sky Model"},
{ OS_LightingDesignDayFields::SnowIndicator, "SnowIndicator", "Snow Indicator"},
{ OS_LightingDesignDayFields::Month, "Month", "Month"},
{ OS_LightingDesignDayFields::DayofMonth, "DayofMonth", "Day of Month"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_LightingDesignDayFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_LightingDesignDayFields> OptionalOS_LightingDesignDayFields ;
#endif

/** \class OS_LightingDesignDayExtensibleFields
 *  \brief Enumeration of OS:LightingDesignDay's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_LightingDesignDayExtensibleFields, )
#else
class OS_LightingDesignDayExtensibleFields: public ::EnumBase<OS_LightingDesignDayExtensibleFields> {
 public: 
  enum domain 
  {
HourtoSimulate, MinutetoSimulate,   };
  OS_LightingDesignDayExtensibleFields()
   : EnumBase<OS_LightingDesignDayExtensibleFields>(HourtoSimulate) {} 
  OS_LightingDesignDayExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_LightingDesignDayExtensibleFields>(t_name) {} 
  OS_LightingDesignDayExtensibleFields(int t_value) 
   : EnumBase<OS_LightingDesignDayExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_LightingDesignDayExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_LightingDesignDayExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_LightingDesignDayExtensibleFields>;
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
{ OS_LightingDesignDayExtensibleFields::HourtoSimulate, "HourtoSimulate", "Hour to Simulate"},
{ OS_LightingDesignDayExtensibleFields::MinutetoSimulate, "MinutetoSimulate", "Minute to Simulate"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_LightingDesignDayExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_LightingDesignDayExtensibleFields> OptionalOS_LightingDesignDayExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_LIGHTINGDESIGNDAY_FIELDENUMS_HXX
