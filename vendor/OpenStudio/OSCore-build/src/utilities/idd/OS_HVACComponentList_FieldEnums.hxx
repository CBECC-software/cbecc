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

#ifndef UTILITIES_IDD_OS_HVACCOMPONENTLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_HVACCOMPONENTLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_HVACComponentListFields
 *  \brief Enumeration of OS:HVACComponentList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_HVACComponentListFields, )
#else
class OS_HVACComponentListFields: public ::EnumBase<OS_HVACComponentListFields> {
 public: 
  enum domain 
  {
Handle, Name,   };
  OS_HVACComponentListFields()
   : EnumBase<OS_HVACComponentListFields>(Handle) {} 
  OS_HVACComponentListFields(const std::string &t_name) 
   : EnumBase<OS_HVACComponentListFields>(t_name) {} 
  OS_HVACComponentListFields(int t_value) 
   : EnumBase<OS_HVACComponentListFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_HVACComponentListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_HVACComponentListFields>::value()); }
   private:
    friend class EnumBase<OS_HVACComponentListFields>;
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
{ OS_HVACComponentListFields::Handle, "Handle", "Handle"},
{ OS_HVACComponentListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_HVACComponentListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_HVACComponentListFields> OptionalOS_HVACComponentListFields ;
#endif

/** \class OS_HVACComponentListExtensibleFields
 *  \brief Enumeration of OS:HVACComponentList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_HVACComponentListExtensibleFields, )
#else
class OS_HVACComponentListExtensibleFields: public ::EnumBase<OS_HVACComponentListExtensibleFields> {
 public: 
  enum domain 
  {
HVACComponent,   };
  OS_HVACComponentListExtensibleFields()
   : EnumBase<OS_HVACComponentListExtensibleFields>(HVACComponent) {} 
  OS_HVACComponentListExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_HVACComponentListExtensibleFields>(t_name) {} 
  OS_HVACComponentListExtensibleFields(int t_value) 
   : EnumBase<OS_HVACComponentListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_HVACComponentListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_HVACComponentListExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_HVACComponentListExtensibleFields>;
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
{ OS_HVACComponentListExtensibleFields::HVACComponent, "HVACComponent", "HVACComponent"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_HVACComponentListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_HVACComponentListExtensibleFields> OptionalOS_HVACComponentListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_HVACCOMPONENTLIST_FIELDENUMS_HXX
