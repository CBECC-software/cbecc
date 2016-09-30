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

#ifndef UTILITIES_IDD_SCHEDULE_DAY_INTERVAL_FIELDENUMS_HXX
#define UTILITIES_IDD_SCHEDULE_DAY_INTERVAL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Schedule_Day_IntervalFields
 *  \brief Enumeration of Schedule:Day:Interval's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Schedule_Day_IntervalFields, )
#else
class Schedule_Day_IntervalFields: public ::EnumBase<Schedule_Day_IntervalFields> {
 public: 
  enum domain 
  {
Name, ScheduleTypeLimitsName, InterpolatetoTimestep,   };
  Schedule_Day_IntervalFields()
   : EnumBase<Schedule_Day_IntervalFields>(Name) {} 
  Schedule_Day_IntervalFields(const std::string &t_name) 
   : EnumBase<Schedule_Day_IntervalFields>(t_name) {} 
  Schedule_Day_IntervalFields(int t_value) 
   : EnumBase<Schedule_Day_IntervalFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_Day_IntervalFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_Day_IntervalFields>::value()); }
   private:
    friend class EnumBase<Schedule_Day_IntervalFields>;
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
{ Schedule_Day_IntervalFields::Name, "Name", "Name"},
{ Schedule_Day_IntervalFields::ScheduleTypeLimitsName, "ScheduleTypeLimitsName", "Schedule Type Limits Name"},
{ Schedule_Day_IntervalFields::InterpolatetoTimestep, "InterpolatetoTimestep", "Interpolate to Timestep"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_Day_IntervalFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_Day_IntervalFields> OptionalSchedule_Day_IntervalFields ;
#endif

/** \class Schedule_Day_IntervalExtensibleFields
 *  \brief Enumeration of Schedule:Day:Interval's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Schedule_Day_IntervalExtensibleFields, )
#else
class Schedule_Day_IntervalExtensibleFields: public ::EnumBase<Schedule_Day_IntervalExtensibleFields> {
 public: 
  enum domain 
  {
Time, ValueUntilTime,   };
  Schedule_Day_IntervalExtensibleFields()
   : EnumBase<Schedule_Day_IntervalExtensibleFields>(Time) {} 
  Schedule_Day_IntervalExtensibleFields(const std::string &t_name) 
   : EnumBase<Schedule_Day_IntervalExtensibleFields>(t_name) {} 
  Schedule_Day_IntervalExtensibleFields(int t_value) 
   : EnumBase<Schedule_Day_IntervalExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_Day_IntervalExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_Day_IntervalExtensibleFields>::value()); }
   private:
    friend class EnumBase<Schedule_Day_IntervalExtensibleFields>;
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
{ Schedule_Day_IntervalExtensibleFields::Time, "Time", "Time"},
{ Schedule_Day_IntervalExtensibleFields::ValueUntilTime, "ValueUntilTime", "Value Until Time"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_Day_IntervalExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_Day_IntervalExtensibleFields> OptionalSchedule_Day_IntervalExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SCHEDULE_DAY_INTERVAL_FIELDENUMS_HXX
