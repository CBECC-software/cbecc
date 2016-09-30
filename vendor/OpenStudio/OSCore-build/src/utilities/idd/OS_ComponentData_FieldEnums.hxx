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

#ifndef UTILITIES_IDD_OS_COMPONENTDATA_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COMPONENTDATA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ComponentDataFields
 *  \brief Enumeration of OS:ComponentData's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ComponentDataFields, )
#else
class OS_ComponentDataFields: public ::EnumBase<OS_ComponentDataFields> {
 public: 
  enum domain 
  {
Handle, Name, UUID, VersionUUID, CreationTimestamp, VersionTimestamp,   };
  OS_ComponentDataFields()
   : EnumBase<OS_ComponentDataFields>(Handle) {} 
  OS_ComponentDataFields(const std::string &t_name) 
   : EnumBase<OS_ComponentDataFields>(t_name) {} 
  OS_ComponentDataFields(int t_value) 
   : EnumBase<OS_ComponentDataFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ComponentDataFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ComponentDataFields>::value()); }
   private:
    friend class EnumBase<OS_ComponentDataFields>;
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
{ OS_ComponentDataFields::Handle, "Handle", "Handle"},
{ OS_ComponentDataFields::Name, "Name", "Name"},
{ OS_ComponentDataFields::UUID, "UUID", "UUID"},
{ OS_ComponentDataFields::VersionUUID, "VersionUUID", "Version UUID"},
{ OS_ComponentDataFields::CreationTimestamp, "CreationTimestamp", "Creation Timestamp"},
{ OS_ComponentDataFields::VersionTimestamp, "VersionTimestamp", "Version Timestamp"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ComponentDataFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ComponentDataFields> OptionalOS_ComponentDataFields ;
#endif

/** \class OS_ComponentDataExtensibleFields
 *  \brief Enumeration of OS:ComponentData's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_ComponentDataExtensibleFields, )
#else
class OS_ComponentDataExtensibleFields: public ::EnumBase<OS_ComponentDataExtensibleFields> {
 public: 
  enum domain 
  {
NameofObject,   };
  OS_ComponentDataExtensibleFields()
   : EnumBase<OS_ComponentDataExtensibleFields>(NameofObject) {} 
  OS_ComponentDataExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ComponentDataExtensibleFields>(t_name) {} 
  OS_ComponentDataExtensibleFields(int t_value) 
   : EnumBase<OS_ComponentDataExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ComponentDataExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ComponentDataExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_ComponentDataExtensibleFields>;
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
{ OS_ComponentDataExtensibleFields::NameofObject, "NameofObject", "Name of Object"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ComponentDataExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ComponentDataExtensibleFields> OptionalOS_ComponentDataExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COMPONENTDATA_FIELDENUMS_HXX
