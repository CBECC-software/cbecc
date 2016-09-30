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

#ifndef UTILITIES_IDD_OS_SCHEDULE_WEEK_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SCHEDULE_WEEK_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Schedule_WeekFields
 *  \brief Enumeration of OS:Schedule:Week's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Schedule_WeekFields, )
#else
class OS_Schedule_WeekFields: public ::EnumBase<OS_Schedule_WeekFields> {
 public: 
  enum domain 
  {
Handle, Name, ScheduleRenderingName, SundaySchedule_DayName, MondaySchedule_DayName, TuesdaySchedule_DayName, WednesdaySchedule_DayName, ThursdaySchedule_DayName, FridaySchedule_DayName, SaturdaySchedule_DayName, HolidaySchedule_DayName, SummerDesignDaySchedule_DayName, WinterDesignDaySchedule_DayName, CustomDay1Schedule_DayName, CustomDay2Schedule_DayName,   };
  OS_Schedule_WeekFields()
   : EnumBase<OS_Schedule_WeekFields>(Handle) {} 
  OS_Schedule_WeekFields(const std::string &t_name) 
   : EnumBase<OS_Schedule_WeekFields>(t_name) {} 
  OS_Schedule_WeekFields(int t_value) 
   : EnumBase<OS_Schedule_WeekFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Schedule_WeekFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Schedule_WeekFields>::value()); }
   private:
    friend class EnumBase<OS_Schedule_WeekFields>;
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
{ OS_Schedule_WeekFields::Handle, "Handle", "Handle"},
{ OS_Schedule_WeekFields::Name, "Name", "Name"},
{ OS_Schedule_WeekFields::ScheduleRenderingName, "ScheduleRenderingName", "Schedule Rendering Name"},
{ OS_Schedule_WeekFields::SundaySchedule_DayName, "SundaySchedule_DayName", "Sunday Schedule:Day Name"},
{ OS_Schedule_WeekFields::MondaySchedule_DayName, "MondaySchedule_DayName", "Monday Schedule:Day Name"},
{ OS_Schedule_WeekFields::TuesdaySchedule_DayName, "TuesdaySchedule_DayName", "Tuesday Schedule:Day Name"},
{ OS_Schedule_WeekFields::WednesdaySchedule_DayName, "WednesdaySchedule_DayName", "Wednesday Schedule:Day Name"},
{ OS_Schedule_WeekFields::ThursdaySchedule_DayName, "ThursdaySchedule_DayName", "Thursday Schedule:Day Name"},
{ OS_Schedule_WeekFields::FridaySchedule_DayName, "FridaySchedule_DayName", "Friday Schedule:Day Name"},
{ OS_Schedule_WeekFields::SaturdaySchedule_DayName, "SaturdaySchedule_DayName", "Saturday Schedule:Day Name"},
{ OS_Schedule_WeekFields::HolidaySchedule_DayName, "HolidaySchedule_DayName", "Holiday Schedule:Day Name"},
{ OS_Schedule_WeekFields::SummerDesignDaySchedule_DayName, "SummerDesignDaySchedule_DayName", "SummerDesignDay Schedule:Day Name"},
{ OS_Schedule_WeekFields::WinterDesignDaySchedule_DayName, "WinterDesignDaySchedule_DayName", "WinterDesignDay Schedule:Day Name"},
{ OS_Schedule_WeekFields::CustomDay1Schedule_DayName, "CustomDay1Schedule_DayName", "CustomDay1 Schedule:Day Name"},
{ OS_Schedule_WeekFields::CustomDay2Schedule_DayName, "CustomDay2Schedule_DayName", "CustomDay2 Schedule:Day Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Schedule_WeekFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Schedule_WeekFields> OptionalOS_Schedule_WeekFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SCHEDULE_WEEK_FIELDENUMS_HXX
