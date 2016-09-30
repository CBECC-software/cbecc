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

#ifndef UTILITIES_IDD_SCHEDULE_COMPACT_FIELDENUMS_HXX
#define UTILITIES_IDD_SCHEDULE_COMPACT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Schedule_CompactFields
 *  \brief Enumeration of Schedule:Compact's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Schedule_CompactFields, )
#else
class Schedule_CompactFields: public ::EnumBase<Schedule_CompactFields> {
 public: 
  enum domain 
  {
Name, ScheduleTypeLimitsName,   };
  Schedule_CompactFields()
   : EnumBase<Schedule_CompactFields>(Name) {} 
  Schedule_CompactFields(const std::string &t_name) 
   : EnumBase<Schedule_CompactFields>(t_name) {} 
  Schedule_CompactFields(int t_value) 
   : EnumBase<Schedule_CompactFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_CompactFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_CompactFields>::value()); }
   private:
    friend class EnumBase<Schedule_CompactFields>;
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
{ Schedule_CompactFields::Name, "Name", "Name"},
{ Schedule_CompactFields::ScheduleTypeLimitsName, "ScheduleTypeLimitsName", "Schedule Type Limits Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_CompactFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_CompactFields> OptionalSchedule_CompactFields ;
#endif

/** \class Schedule_CompactExtensibleFields
 *  \brief Enumeration of Schedule:Compact's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Schedule_CompactExtensibleFields, )
#else
class Schedule_CompactExtensibleFields: public ::EnumBase<Schedule_CompactExtensibleFields> {
 public: 
  enum domain 
  {
Field,   };
  Schedule_CompactExtensibleFields()
   : EnumBase<Schedule_CompactExtensibleFields>(Field) {} 
  Schedule_CompactExtensibleFields(const std::string &t_name) 
   : EnumBase<Schedule_CompactExtensibleFields>(t_name) {} 
  Schedule_CompactExtensibleFields(int t_value) 
   : EnumBase<Schedule_CompactExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_CompactExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_CompactExtensibleFields>::value()); }
   private:
    friend class EnumBase<Schedule_CompactExtensibleFields>;
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
{ Schedule_CompactExtensibleFields::Field, "Field", "Field"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_CompactExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_CompactExtensibleFields> OptionalSchedule_CompactExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SCHEDULE_COMPACT_FIELDENUMS_HXX
