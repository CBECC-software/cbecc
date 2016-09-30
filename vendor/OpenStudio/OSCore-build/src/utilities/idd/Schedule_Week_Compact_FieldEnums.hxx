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

#ifndef UTILITIES_IDD_SCHEDULE_WEEK_COMPACT_FIELDENUMS_HXX
#define UTILITIES_IDD_SCHEDULE_WEEK_COMPACT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Schedule_Week_CompactFields
 *  \brief Enumeration of Schedule:Week:Compact's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Schedule_Week_CompactFields, )
#else
class Schedule_Week_CompactFields: public ::EnumBase<Schedule_Week_CompactFields> {
 public: 
  enum domain 
  {
Name,   };
  Schedule_Week_CompactFields()
   : EnumBase<Schedule_Week_CompactFields>(Name) {} 
  Schedule_Week_CompactFields(const std::string &t_name) 
   : EnumBase<Schedule_Week_CompactFields>(t_name) {} 
  Schedule_Week_CompactFields(int t_value) 
   : EnumBase<Schedule_Week_CompactFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_Week_CompactFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_Week_CompactFields>::value()); }
   private:
    friend class EnumBase<Schedule_Week_CompactFields>;
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
{ Schedule_Week_CompactFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_Week_CompactFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_Week_CompactFields> OptionalSchedule_Week_CompactFields ;
#endif

/** \class Schedule_Week_CompactExtensibleFields
 *  \brief Enumeration of Schedule:Week:Compact's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Schedule_Week_CompactExtensibleFields, )
#else
class Schedule_Week_CompactExtensibleFields: public ::EnumBase<Schedule_Week_CompactExtensibleFields> {
 public: 
  enum domain 
  {
DayTypeList, Schedule_DayName,   };
  Schedule_Week_CompactExtensibleFields()
   : EnumBase<Schedule_Week_CompactExtensibleFields>(DayTypeList) {} 
  Schedule_Week_CompactExtensibleFields(const std::string &t_name) 
   : EnumBase<Schedule_Week_CompactExtensibleFields>(t_name) {} 
  Schedule_Week_CompactExtensibleFields(int t_value) 
   : EnumBase<Schedule_Week_CompactExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_Week_CompactExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_Week_CompactExtensibleFields>::value()); }
   private:
    friend class EnumBase<Schedule_Week_CompactExtensibleFields>;
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
{ Schedule_Week_CompactExtensibleFields::DayTypeList, "DayTypeList", "DayType List"},
{ Schedule_Week_CompactExtensibleFields::Schedule_DayName, "Schedule_DayName", "Schedule:Day Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_Week_CompactExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_Week_CompactExtensibleFields> OptionalSchedule_Week_CompactExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SCHEDULE_WEEK_COMPACT_FIELDENUMS_HXX
