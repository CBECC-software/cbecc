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

#ifndef UTILITIES_IDD_OS_CLIMATEZONES_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CLIMATEZONES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ClimateZonesFields
 *  \brief Enumeration of OS:ClimateZones's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ClimateZonesFields, )
#else
class OS_ClimateZonesFields: public ::EnumBase<OS_ClimateZonesFields> {
 public: 
  enum domain 
  {
Handle, ActiveInstitution, ActiveYear,   };
  OS_ClimateZonesFields()
   : EnumBase<OS_ClimateZonesFields>(Handle) {} 
  OS_ClimateZonesFields(const std::string &t_name) 
   : EnumBase<OS_ClimateZonesFields>(t_name) {} 
  OS_ClimateZonesFields(int t_value) 
   : EnumBase<OS_ClimateZonesFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ClimateZonesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ClimateZonesFields>::value()); }
   private:
    friend class EnumBase<OS_ClimateZonesFields>;
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
{ OS_ClimateZonesFields::Handle, "Handle", "Handle"},
{ OS_ClimateZonesFields::ActiveInstitution, "ActiveInstitution", "Active Institution"},
{ OS_ClimateZonesFields::ActiveYear, "ActiveYear", "Active Year"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ClimateZonesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ClimateZonesFields> OptionalOS_ClimateZonesFields ;
#endif

/** \class OS_ClimateZonesExtensibleFields
 *  \brief Enumeration of OS:ClimateZones's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_ClimateZonesExtensibleFields, )
#else
class OS_ClimateZonesExtensibleFields: public ::EnumBase<OS_ClimateZonesExtensibleFields> {
 public: 
  enum domain 
  {
ClimateZoneInstitutionName, ClimateZoneDocumentName, ClimateZoneDocumentYear, ClimateZoneValue,   };
  OS_ClimateZonesExtensibleFields()
   : EnumBase<OS_ClimateZonesExtensibleFields>(ClimateZoneInstitutionName) {} 
  OS_ClimateZonesExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ClimateZonesExtensibleFields>(t_name) {} 
  OS_ClimateZonesExtensibleFields(int t_value) 
   : EnumBase<OS_ClimateZonesExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ClimateZonesExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ClimateZonesExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_ClimateZonesExtensibleFields>;
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
{ OS_ClimateZonesExtensibleFields::ClimateZoneInstitutionName, "ClimateZoneInstitutionName", "Climate Zone Institution Name"},
{ OS_ClimateZonesExtensibleFields::ClimateZoneDocumentName, "ClimateZoneDocumentName", "Climate Zone Document Name"},
{ OS_ClimateZonesExtensibleFields::ClimateZoneDocumentYear, "ClimateZoneDocumentYear", "Climate Zone Document Year"},
{ OS_ClimateZonesExtensibleFields::ClimateZoneValue, "ClimateZoneValue", "Climate Zone Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ClimateZonesExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ClimateZonesExtensibleFields> OptionalOS_ClimateZonesExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CLIMATEZONES_FIELDENUMS_HXX
