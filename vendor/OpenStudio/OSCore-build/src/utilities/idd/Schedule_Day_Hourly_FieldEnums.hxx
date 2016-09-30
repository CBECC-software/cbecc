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

#ifndef UTILITIES_IDD_SCHEDULE_DAY_HOURLY_FIELDENUMS_HXX
#define UTILITIES_IDD_SCHEDULE_DAY_HOURLY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Schedule_Day_HourlyFields
 *  \brief Enumeration of Schedule:Day:Hourly's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Schedule_Day_HourlyFields, )
#else
class Schedule_Day_HourlyFields: public ::EnumBase<Schedule_Day_HourlyFields> {
 public: 
  enum domain 
  {
Name, ScheduleTypeLimitsName, Hour1, Hour2, Hour3, Hour4, Hour5, Hour6, Hour7, Hour8, Hour9, Hour10, Hour11, Hour12, Hour13, Hour14, Hour15, Hour16, Hour17, Hour18, Hour19, Hour20, Hour21, Hour22, Hour23, Hour24,   };
  Schedule_Day_HourlyFields()
   : EnumBase<Schedule_Day_HourlyFields>(Name) {} 
  Schedule_Day_HourlyFields(const std::string &t_name) 
   : EnumBase<Schedule_Day_HourlyFields>(t_name) {} 
  Schedule_Day_HourlyFields(int t_value) 
   : EnumBase<Schedule_Day_HourlyFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_Day_HourlyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_Day_HourlyFields>::value()); }
   private:
    friend class EnumBase<Schedule_Day_HourlyFields>;
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
{ Schedule_Day_HourlyFields::Name, "Name", "Name"},
{ Schedule_Day_HourlyFields::ScheduleTypeLimitsName, "ScheduleTypeLimitsName", "Schedule Type Limits Name"},
{ Schedule_Day_HourlyFields::Hour1, "Hour1", "Hour 1"},
{ Schedule_Day_HourlyFields::Hour2, "Hour2", "Hour 2"},
{ Schedule_Day_HourlyFields::Hour3, "Hour3", "Hour 3"},
{ Schedule_Day_HourlyFields::Hour4, "Hour4", "Hour 4"},
{ Schedule_Day_HourlyFields::Hour5, "Hour5", "Hour 5"},
{ Schedule_Day_HourlyFields::Hour6, "Hour6", "Hour 6"},
{ Schedule_Day_HourlyFields::Hour7, "Hour7", "Hour 7"},
{ Schedule_Day_HourlyFields::Hour8, "Hour8", "Hour 8"},
{ Schedule_Day_HourlyFields::Hour9, "Hour9", "Hour 9"},
{ Schedule_Day_HourlyFields::Hour10, "Hour10", "Hour 10"},
{ Schedule_Day_HourlyFields::Hour11, "Hour11", "Hour 11"},
{ Schedule_Day_HourlyFields::Hour12, "Hour12", "Hour 12"},
{ Schedule_Day_HourlyFields::Hour13, "Hour13", "Hour 13"},
{ Schedule_Day_HourlyFields::Hour14, "Hour14", "Hour 14"},
{ Schedule_Day_HourlyFields::Hour15, "Hour15", "Hour 15"},
{ Schedule_Day_HourlyFields::Hour16, "Hour16", "Hour 16"},
{ Schedule_Day_HourlyFields::Hour17, "Hour17", "Hour 17"},
{ Schedule_Day_HourlyFields::Hour18, "Hour18", "Hour 18"},
{ Schedule_Day_HourlyFields::Hour19, "Hour19", "Hour 19"},
{ Schedule_Day_HourlyFields::Hour20, "Hour20", "Hour 20"},
{ Schedule_Day_HourlyFields::Hour21, "Hour21", "Hour 21"},
{ Schedule_Day_HourlyFields::Hour22, "Hour22", "Hour 22"},
{ Schedule_Day_HourlyFields::Hour23, "Hour23", "Hour 23"},
{ Schedule_Day_HourlyFields::Hour24, "Hour24", "Hour 24"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_Day_HourlyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_Day_HourlyFields> OptionalSchedule_Day_HourlyFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SCHEDULE_DAY_HOURLY_FIELDENUMS_HXX
