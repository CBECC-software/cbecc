/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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
