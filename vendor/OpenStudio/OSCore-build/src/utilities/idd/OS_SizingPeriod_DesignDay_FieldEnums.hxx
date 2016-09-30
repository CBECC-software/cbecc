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

#ifndef UTILITIES_IDD_OS_SIZINGPERIOD_DESIGNDAY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SIZINGPERIOD_DESIGNDAY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SizingPeriod_DesignDayFields
 *  \brief Enumeration of OS:SizingPeriod:DesignDay's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SizingPeriod_DesignDayFields, )
#else
class OS_SizingPeriod_DesignDayFields: public ::EnumBase<OS_SizingPeriod_DesignDayFields> {
 public: 
  enum domain 
  {
Handle, Name, MaximumDryBulbTemperature, DailyDryBulbTemperatureRange, HumidityIndicatingConditionsatMaximumDryBulb, BarometricPressure, WindSpeed, WindDirection, SkyClearness, RainIndicator, SnowIndicator, DayofMonth, Month, DayType, DaylightSavingTimeIndicator, HumidityIndicatingType, HumidityIndicatingDayScheduleName, DryBulbTemperatureRangeModifierType, DryBulbTemperatureRangeModifierScheduleName, SolarModelIndicator, BeamSolarDayScheduleName, DiffuseSolarDayScheduleName, ASHRAETaub, ASHRAETaud, DailyWetBulbTemperatureRange,   };
  OS_SizingPeriod_DesignDayFields()
   : EnumBase<OS_SizingPeriod_DesignDayFields>(Handle) {} 
  OS_SizingPeriod_DesignDayFields(const std::string &t_name) 
   : EnumBase<OS_SizingPeriod_DesignDayFields>(t_name) {} 
  OS_SizingPeriod_DesignDayFields(int t_value) 
   : EnumBase<OS_SizingPeriod_DesignDayFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SizingPeriod_DesignDayFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SizingPeriod_DesignDayFields>::value()); }
   private:
    friend class EnumBase<OS_SizingPeriod_DesignDayFields>;
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
{ OS_SizingPeriod_DesignDayFields::Handle, "Handle", "Handle"},
{ OS_SizingPeriod_DesignDayFields::Name, "Name", "Name"},
{ OS_SizingPeriod_DesignDayFields::MaximumDryBulbTemperature, "MaximumDryBulbTemperature", "Maximum Dry-Bulb Temperature"},
{ OS_SizingPeriod_DesignDayFields::DailyDryBulbTemperatureRange, "DailyDryBulbTemperatureRange", "Daily Dry-Bulb Temperature Range"},
{ OS_SizingPeriod_DesignDayFields::HumidityIndicatingConditionsatMaximumDryBulb, "HumidityIndicatingConditionsatMaximumDryBulb", "Humidity Indicating Conditions at Maximum Dry-Bulb"},
{ OS_SizingPeriod_DesignDayFields::BarometricPressure, "BarometricPressure", "Barometric Pressure"},
{ OS_SizingPeriod_DesignDayFields::WindSpeed, "WindSpeed", "Wind Speed"},
{ OS_SizingPeriod_DesignDayFields::WindDirection, "WindDirection", "Wind Direction"},
{ OS_SizingPeriod_DesignDayFields::SkyClearness, "SkyClearness", "Sky Clearness"},
{ OS_SizingPeriod_DesignDayFields::RainIndicator, "RainIndicator", "Rain Indicator"},
{ OS_SizingPeriod_DesignDayFields::SnowIndicator, "SnowIndicator", "Snow Indicator"},
{ OS_SizingPeriod_DesignDayFields::DayofMonth, "DayofMonth", "Day of Month"},
{ OS_SizingPeriod_DesignDayFields::Month, "Month", "Month"},
{ OS_SizingPeriod_DesignDayFields::DayType, "DayType", "Day Type"},
{ OS_SizingPeriod_DesignDayFields::DaylightSavingTimeIndicator, "DaylightSavingTimeIndicator", "Daylight Saving Time Indicator"},
{ OS_SizingPeriod_DesignDayFields::HumidityIndicatingType, "HumidityIndicatingType", "Humidity Indicating Type"},
{ OS_SizingPeriod_DesignDayFields::HumidityIndicatingDayScheduleName, "HumidityIndicatingDayScheduleName", "Humidity Indicating Day Schedule Name"},
{ OS_SizingPeriod_DesignDayFields::DryBulbTemperatureRangeModifierType, "DryBulbTemperatureRangeModifierType", "Dry-Bulb Temperature Range Modifier Type"},
{ OS_SizingPeriod_DesignDayFields::DryBulbTemperatureRangeModifierScheduleName, "DryBulbTemperatureRangeModifierScheduleName", "Dry-Bulb Temperature Range Modifier Schedule Name"},
{ OS_SizingPeriod_DesignDayFields::SolarModelIndicator, "SolarModelIndicator", "Solar Model Indicator"},
{ OS_SizingPeriod_DesignDayFields::BeamSolarDayScheduleName, "BeamSolarDayScheduleName", "Beam Solar Day Schedule Name"},
{ OS_SizingPeriod_DesignDayFields::DiffuseSolarDayScheduleName, "DiffuseSolarDayScheduleName", "Diffuse Solar Day Schedule Name"},
{ OS_SizingPeriod_DesignDayFields::ASHRAETaub, "ASHRAETaub", "ASHRAE Taub"},
{ OS_SizingPeriod_DesignDayFields::ASHRAETaud, "ASHRAETaud", "ASHRAE Taud"},
{ OS_SizingPeriod_DesignDayFields::DailyWetBulbTemperatureRange, "DailyWetBulbTemperatureRange", "Daily Wet-Bulb Temperature Range"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SizingPeriod_DesignDayFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SizingPeriod_DesignDayFields> OptionalOS_SizingPeriod_DesignDayFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SIZINGPERIOD_DESIGNDAY_FIELDENUMS_HXX
