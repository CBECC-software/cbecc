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

#ifndef UTILITIES_IDD_AVAILABILITYMANAGERASSIGNMENTLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_AVAILABILITYMANAGERASSIGNMENTLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AvailabilityManagerAssignmentListFields
 *  \brief Enumeration of AvailabilityManagerAssignmentList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AvailabilityManagerAssignmentListFields, )
#else
class AvailabilityManagerAssignmentListFields: public ::EnumBase<AvailabilityManagerAssignmentListFields> {
 public: 
  enum domain 
  {
Name,   };
  AvailabilityManagerAssignmentListFields()
   : EnumBase<AvailabilityManagerAssignmentListFields>(Name) {} 
  AvailabilityManagerAssignmentListFields(const std::string &t_name) 
   : EnumBase<AvailabilityManagerAssignmentListFields>(t_name) {} 
  AvailabilityManagerAssignmentListFields(int t_value) 
   : EnumBase<AvailabilityManagerAssignmentListFields>(t_value) {} 
  static std::string enumName() 
  { return "AvailabilityManagerAssignmentListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AvailabilityManagerAssignmentListFields>::value()); }
   private:
    friend class EnumBase<AvailabilityManagerAssignmentListFields>;
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
{ AvailabilityManagerAssignmentListFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AvailabilityManagerAssignmentListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AvailabilityManagerAssignmentListFields> OptionalAvailabilityManagerAssignmentListFields ;
#endif

/** \class AvailabilityManagerAssignmentListExtensibleFields
 *  \brief Enumeration of AvailabilityManagerAssignmentList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AvailabilityManagerAssignmentListExtensibleFields, )
#else
class AvailabilityManagerAssignmentListExtensibleFields: public ::EnumBase<AvailabilityManagerAssignmentListExtensibleFields> {
 public: 
  enum domain 
  {
AvailabilityManagerObjectType, AvailabilityManagerName,   };
  AvailabilityManagerAssignmentListExtensibleFields()
   : EnumBase<AvailabilityManagerAssignmentListExtensibleFields>(AvailabilityManagerObjectType) {} 
  AvailabilityManagerAssignmentListExtensibleFields(const std::string &t_name) 
   : EnumBase<AvailabilityManagerAssignmentListExtensibleFields>(t_name) {} 
  AvailabilityManagerAssignmentListExtensibleFields(int t_value) 
   : EnumBase<AvailabilityManagerAssignmentListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AvailabilityManagerAssignmentListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AvailabilityManagerAssignmentListExtensibleFields>::value()); }
   private:
    friend class EnumBase<AvailabilityManagerAssignmentListExtensibleFields>;
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
{ AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerObjectType, "AvailabilityManagerObjectType", "Availability Manager Object Type"},
{ AvailabilityManagerAssignmentListExtensibleFields::AvailabilityManagerName, "AvailabilityManagerName", "Availability Manager Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AvailabilityManagerAssignmentListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AvailabilityManagerAssignmentListExtensibleFields> OptionalAvailabilityManagerAssignmentListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AVAILABILITYMANAGERASSIGNMENTLIST_FIELDENUMS_HXX
