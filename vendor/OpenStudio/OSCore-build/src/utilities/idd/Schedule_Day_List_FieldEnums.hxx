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

#ifndef UTILITIES_IDD_SCHEDULE_DAY_LIST_FIELDENUMS_HXX
#define UTILITIES_IDD_SCHEDULE_DAY_LIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Schedule_Day_ListFields
 *  \brief Enumeration of Schedule:Day:List's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Schedule_Day_ListFields, )
#else
class Schedule_Day_ListFields: public ::EnumBase<Schedule_Day_ListFields> {
 public: 
  enum domain 
  {
Name, ScheduleTypeLimitsName, InterpolatetoTimestep, MinutesperItem,   };
  Schedule_Day_ListFields()
   : EnumBase<Schedule_Day_ListFields>(Name) {} 
  Schedule_Day_ListFields(const std::string &t_name) 
   : EnumBase<Schedule_Day_ListFields>(t_name) {} 
  Schedule_Day_ListFields(int t_value) 
   : EnumBase<Schedule_Day_ListFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_Day_ListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_Day_ListFields>::value()); }
   private:
    friend class EnumBase<Schedule_Day_ListFields>;
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
{ Schedule_Day_ListFields::Name, "Name", "Name"},
{ Schedule_Day_ListFields::ScheduleTypeLimitsName, "ScheduleTypeLimitsName", "Schedule Type Limits Name"},
{ Schedule_Day_ListFields::InterpolatetoTimestep, "InterpolatetoTimestep", "Interpolate to Timestep"},
{ Schedule_Day_ListFields::MinutesperItem, "MinutesperItem", "Minutes per Item"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_Day_ListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_Day_ListFields> OptionalSchedule_Day_ListFields ;
#endif

/** \class Schedule_Day_ListExtensibleFields
 *  \brief Enumeration of Schedule:Day:List's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Schedule_Day_ListExtensibleFields, )
#else
class Schedule_Day_ListExtensibleFields: public ::EnumBase<Schedule_Day_ListExtensibleFields> {
 public: 
  enum domain 
  {
Value,   };
  Schedule_Day_ListExtensibleFields()
   : EnumBase<Schedule_Day_ListExtensibleFields>(Value) {} 
  Schedule_Day_ListExtensibleFields(const std::string &t_name) 
   : EnumBase<Schedule_Day_ListExtensibleFields>(t_name) {} 
  Schedule_Day_ListExtensibleFields(int t_value) 
   : EnumBase<Schedule_Day_ListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_Day_ListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_Day_ListExtensibleFields>::value()); }
   private:
    friend class EnumBase<Schedule_Day_ListExtensibleFields>;
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
{ Schedule_Day_ListExtensibleFields::Value, "Value", "Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_Day_ListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_Day_ListExtensibleFields> OptionalSchedule_Day_ListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SCHEDULE_DAY_LIST_FIELDENUMS_HXX
