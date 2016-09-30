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

#ifndef UTILITIES_IDD_SCHEDULE_WEEK_DAILY_FIELDENUMS_HXX
#define UTILITIES_IDD_SCHEDULE_WEEK_DAILY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Schedule_Week_DailyFields
 *  \brief Enumeration of Schedule:Week:Daily's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Schedule_Week_DailyFields, )
#else
class Schedule_Week_DailyFields: public ::EnumBase<Schedule_Week_DailyFields> {
 public: 
  enum domain 
  {
Name, SundaySchedule_DayName, MondaySchedule_DayName, TuesdaySchedule_DayName, WednesdaySchedule_DayName, ThursdaySchedule_DayName, FridaySchedule_DayName, SaturdaySchedule_DayName, HolidaySchedule_DayName, SummerDesignDaySchedule_DayName, WinterDesignDaySchedule_DayName, CustomDay1Schedule_DayName, CustomDay2Schedule_DayName,   };
  Schedule_Week_DailyFields()
   : EnumBase<Schedule_Week_DailyFields>(Name) {} 
  Schedule_Week_DailyFields(const std::string &t_name) 
   : EnumBase<Schedule_Week_DailyFields>(t_name) {} 
  Schedule_Week_DailyFields(int t_value) 
   : EnumBase<Schedule_Week_DailyFields>(t_value) {} 
  static std::string enumName() 
  { return "Schedule_Week_DailyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Schedule_Week_DailyFields>::value()); }
   private:
    friend class EnumBase<Schedule_Week_DailyFields>;
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
{ Schedule_Week_DailyFields::Name, "Name", "Name"},
{ Schedule_Week_DailyFields::SundaySchedule_DayName, "SundaySchedule_DayName", "Sunday Schedule:Day Name"},
{ Schedule_Week_DailyFields::MondaySchedule_DayName, "MondaySchedule_DayName", "Monday Schedule:Day Name"},
{ Schedule_Week_DailyFields::TuesdaySchedule_DayName, "TuesdaySchedule_DayName", "Tuesday Schedule:Day Name"},
{ Schedule_Week_DailyFields::WednesdaySchedule_DayName, "WednesdaySchedule_DayName", "Wednesday Schedule:Day Name"},
{ Schedule_Week_DailyFields::ThursdaySchedule_DayName, "ThursdaySchedule_DayName", "Thursday Schedule:Day Name"},
{ Schedule_Week_DailyFields::FridaySchedule_DayName, "FridaySchedule_DayName", "Friday Schedule:Day Name"},
{ Schedule_Week_DailyFields::SaturdaySchedule_DayName, "SaturdaySchedule_DayName", "Saturday Schedule:Day Name"},
{ Schedule_Week_DailyFields::HolidaySchedule_DayName, "HolidaySchedule_DayName", "Holiday Schedule:Day Name"},
{ Schedule_Week_DailyFields::SummerDesignDaySchedule_DayName, "SummerDesignDaySchedule_DayName", "SummerDesignDay Schedule:Day Name"},
{ Schedule_Week_DailyFields::WinterDesignDaySchedule_DayName, "WinterDesignDaySchedule_DayName", "WinterDesignDay Schedule:Day Name"},
{ Schedule_Week_DailyFields::CustomDay1Schedule_DayName, "CustomDay1Schedule_DayName", "CustomDay1 Schedule:Day Name"},
{ Schedule_Week_DailyFields::CustomDay2Schedule_DayName, "CustomDay2Schedule_DayName", "CustomDay2 Schedule:Day Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Schedule_Week_DailyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Schedule_Week_DailyFields> OptionalSchedule_Week_DailyFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SCHEDULE_WEEK_DAILY_FIELDENUMS_HXX
