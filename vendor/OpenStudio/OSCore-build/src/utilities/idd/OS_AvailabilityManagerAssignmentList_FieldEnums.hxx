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

#ifndef UTILITIES_IDD_OS_AVAILABILITYMANAGERASSIGNMENTLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AVAILABILITYMANAGERASSIGNMENTLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AvailabilityManagerAssignmentListFields
 *  \brief Enumeration of OS:AvailabilityManagerAssignmentList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AvailabilityManagerAssignmentListFields, )
#else
class OS_AvailabilityManagerAssignmentListFields: public ::EnumBase<OS_AvailabilityManagerAssignmentListFields> {
 public: 
  enum domain 
  {
Handle, Name,   };
  OS_AvailabilityManagerAssignmentListFields()
   : EnumBase<OS_AvailabilityManagerAssignmentListFields>(Handle) {} 
  OS_AvailabilityManagerAssignmentListFields(const std::string &t_name) 
   : EnumBase<OS_AvailabilityManagerAssignmentListFields>(t_name) {} 
  OS_AvailabilityManagerAssignmentListFields(int t_value) 
   : EnumBase<OS_AvailabilityManagerAssignmentListFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AvailabilityManagerAssignmentListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AvailabilityManagerAssignmentListFields>::value()); }
   private:
    friend class EnumBase<OS_AvailabilityManagerAssignmentListFields>;
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
{ OS_AvailabilityManagerAssignmentListFields::Handle, "Handle", "Handle"},
{ OS_AvailabilityManagerAssignmentListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AvailabilityManagerAssignmentListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AvailabilityManagerAssignmentListFields> OptionalOS_AvailabilityManagerAssignmentListFields ;
#endif

/** \class OS_AvailabilityManagerAssignmentListExtensibleFields
 *  \brief Enumeration of OS:AvailabilityManagerAssignmentList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_AvailabilityManagerAssignmentListExtensibleFields, )
#else
class OS_AvailabilityManagerAssignmentListExtensibleFields: public ::EnumBase<OS_AvailabilityManagerAssignmentListExtensibleFields> {
 public: 
  enum domain 
  {
AvailabilityManagerName,   };
  OS_AvailabilityManagerAssignmentListExtensibleFields()
   : EnumBase<OS_AvailabilityManagerAssignmentListExtensibleFields>(AvailabilityManagerName) {} 
  OS_AvailabilityManagerAssignmentListExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_AvailabilityManagerAssignmentListExtensibleFields>(t_name) {} 
  OS_AvailabilityManagerAssignmentListExtensibleFields(int t_value) 
   : EnumBase<OS_AvailabilityManagerAssignmentListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AvailabilityManagerAssignmentListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AvailabilityManagerAssignmentListExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_AvailabilityManagerAssignmentListExtensibleFields>;
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
{ OS_AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerName, "AvailabilityManagerName", "Availability Manager Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AvailabilityManagerAssignmentListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AvailabilityManagerAssignmentListExtensibleFields> OptionalOS_AvailabilityManagerAssignmentListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AVAILABILITYMANAGERASSIGNMENTLIST_FIELDENUMS_HXX
