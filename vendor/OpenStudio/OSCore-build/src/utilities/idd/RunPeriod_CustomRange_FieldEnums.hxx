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

#ifndef UTILITIES_IDD_RUNPERIOD_CUSTOMRANGE_FIELDENUMS_HXX
#define UTILITIES_IDD_RUNPERIOD_CUSTOMRANGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RunPeriod_CustomRangeFields
 *  \brief Enumeration of RunPeriod:CustomRange's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RunPeriod_CustomRangeFields, )
#else
class RunPeriod_CustomRangeFields: public ::EnumBase<RunPeriod_CustomRangeFields> {
 public: 
  enum domain 
  {
Name, BeginMonth, BeginDayofMonth, BeginYear, EndMonth, EndDayofMonth, EndYear, DayofWeekforStartDay, UseWeatherFileHolidaysandSpecialDays, UseWeatherFileDaylightSavingPeriod, ApplyWeekendHolidayRule, UseWeatherFileRainIndicators, UseWeatherFileSnowIndicators,   };
  RunPeriod_CustomRangeFields()
   : EnumBase<RunPeriod_CustomRangeFields>(Name) {} 
  RunPeriod_CustomRangeFields(const std::string &t_name) 
   : EnumBase<RunPeriod_CustomRangeFields>(t_name) {} 
  RunPeriod_CustomRangeFields(int t_value) 
   : EnumBase<RunPeriod_CustomRangeFields>(t_value) {} 
  static std::string enumName() 
  { return "RunPeriod_CustomRangeFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RunPeriod_CustomRangeFields>::value()); }
   private:
    friend class EnumBase<RunPeriod_CustomRangeFields>;
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
{ RunPeriod_CustomRangeFields::Name, "Name", "Name"},
{ RunPeriod_CustomRangeFields::BeginMonth, "BeginMonth", "Begin Month"},
{ RunPeriod_CustomRangeFields::BeginDayofMonth, "BeginDayofMonth", "Begin Day of Month"},
{ RunPeriod_CustomRangeFields::BeginYear, "BeginYear", "Begin Year"},
{ RunPeriod_CustomRangeFields::EndMonth, "EndMonth", "End Month"},
{ RunPeriod_CustomRangeFields::EndDayofMonth, "EndDayofMonth", "End Day of Month"},
{ RunPeriod_CustomRangeFields::EndYear, "EndYear", "End Year"},
{ RunPeriod_CustomRangeFields::DayofWeekforStartDay, "DayofWeekforStartDay", "Day of Week for Start Day"},
{ RunPeriod_CustomRangeFields::UseWeatherFileHolidaysandSpecialDays, "UseWeatherFileHolidaysandSpecialDays", "Use Weather File Holidays and Special Days"},
{ RunPeriod_CustomRangeFields::UseWeatherFileDaylightSavingPeriod, "UseWeatherFileDaylightSavingPeriod", "Use Weather File Daylight Saving Period"},
{ RunPeriod_CustomRangeFields::ApplyWeekendHolidayRule, "ApplyWeekendHolidayRule", "Apply Weekend Holiday Rule"},
{ RunPeriod_CustomRangeFields::UseWeatherFileRainIndicators, "UseWeatherFileRainIndicators", "Use Weather File Rain Indicators"},
{ RunPeriod_CustomRangeFields::UseWeatherFileSnowIndicators, "UseWeatherFileSnowIndicators", "Use Weather File Snow Indicators"},
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
  inline std::ostream &operator<<(std::ostream &os, const RunPeriod_CustomRangeFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RunPeriod_CustomRangeFields> OptionalRunPeriod_CustomRangeFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_RUNPERIOD_CUSTOMRANGE_FIELDENUMS_HXX
