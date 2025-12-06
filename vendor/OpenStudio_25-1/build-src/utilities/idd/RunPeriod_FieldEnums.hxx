/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_RUNPERIOD_FIELDENUMS_HXX
#define UTILITIES_IDD_RUNPERIOD_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class RunPeriodFields
 *  \brief Enumeration of RunPeriod's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(RunPeriodFields, )
#else
class RunPeriodFields: public ::EnumBase<RunPeriodFields> {
 public: 
  enum domain 
  {
Name, BeginMonth, BeginDayofMonth, BeginYear, EndMonth, EndDayofMonth, EndYear, DayofWeekforStartDay, UseWeatherFileHolidaysandSpecialDays, UseWeatherFileDaylightSavingPeriod, ApplyWeekendHolidayRule, UseWeatherFileRainIndicators, UseWeatherFileSnowIndicators, TreatWeatherasActual, FirstHourInterpolationStartingValues,   };
  RunPeriodFields()
   : EnumBase<RunPeriodFields>(Name) {} 
  RunPeriodFields(const std::string &t_name) 
   : EnumBase<RunPeriodFields>(t_name) {} 
  RunPeriodFields(int t_value) 
   : EnumBase<RunPeriodFields>(t_value) {} 
  static std::string enumName() 
  { return "RunPeriodFields"; }
  domain value() const { return static_cast<domain>(EnumBase<RunPeriodFields>::integer_value()); }
   private:
    friend class EnumBase<RunPeriodFields>;
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
{ RunPeriodFields::Name, "Name", "Name"},
{ RunPeriodFields::BeginMonth, "BeginMonth", "Begin Month"},
{ RunPeriodFields::BeginDayofMonth, "BeginDayofMonth", "Begin Day of Month"},
{ RunPeriodFields::BeginYear, "BeginYear", "Begin Year"},
{ RunPeriodFields::EndMonth, "EndMonth", "End Month"},
{ RunPeriodFields::EndDayofMonth, "EndDayofMonth", "End Day of Month"},
{ RunPeriodFields::EndYear, "EndYear", "End Year"},
{ RunPeriodFields::DayofWeekforStartDay, "DayofWeekforStartDay", "Day of Week for Start Day"},
{ RunPeriodFields::UseWeatherFileHolidaysandSpecialDays, "UseWeatherFileHolidaysandSpecialDays", "Use Weather File Holidays and Special Days"},
{ RunPeriodFields::UseWeatherFileDaylightSavingPeriod, "UseWeatherFileDaylightSavingPeriod", "Use Weather File Daylight Saving Period"},
{ RunPeriodFields::ApplyWeekendHolidayRule, "ApplyWeekendHolidayRule", "Apply Weekend Holiday Rule"},
{ RunPeriodFields::UseWeatherFileRainIndicators, "UseWeatherFileRainIndicators", "Use Weather File Rain Indicators"},
{ RunPeriodFields::UseWeatherFileSnowIndicators, "UseWeatherFileSnowIndicators", "Use Weather File Snow Indicators"},
{ RunPeriodFields::TreatWeatherasActual, "TreatWeatherasActual", "Treat Weather as Actual"},
{ RunPeriodFields::FirstHourInterpolationStartingValues, "FirstHourInterpolationStartingValues", "First Hour Interpolation Starting Values"},
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
  inline std::ostream &operator<<(std::ostream &os, const RunPeriodFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<RunPeriodFields> OptionalRunPeriodFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_RUNPERIOD_FIELDENUMS_HXX
