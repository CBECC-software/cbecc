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

#ifndef UTILITIES_IDD_SIZINGPERIOD_DESIGNDAY_FIELDENUMS_HXX
#define UTILITIES_IDD_SIZINGPERIOD_DESIGNDAY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SizingPeriod_DesignDayFields
 *  \brief Enumeration of SizingPeriod:DesignDay's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SizingPeriod_DesignDayFields, )
#else
class SizingPeriod_DesignDayFields: public ::EnumBase<SizingPeriod_DesignDayFields> {
 public: 
  enum domain 
  {
Name, Month, DayofMonth, DayType, MaximumDryBulbTemperature, DailyDryBulbTemperatureRange, DryBulbTemperatureRangeModifierType, DryBulbTemperatureRangeModifierDayScheduleName, HumidityConditionType, WetbulborDewPointatMaximumDryBulb, HumidityConditionDayScheduleName, HumidityRatioatMaximumDryBulb, EnthalpyatMaximumDryBulb, DailyWetBulbTemperatureRange, BarometricPressure, WindSpeed, WindDirection, RainIndicator, SnowIndicator, DaylightSavingTimeIndicator, SolarModelIndicator, BeamSolarDayScheduleName, DiffuseSolarDayScheduleName, ASHRAEClearSkyOpticalDepthforBeamIrradiance_taub_, ASHRAEClearSkyOpticalDepthforDiffuseIrradiance_taud_, SkyClearness, MaximumNumberWarmupDays, BeginEnvironmentResetMode,   };
  SizingPeriod_DesignDayFields()
   : EnumBase<SizingPeriod_DesignDayFields>(Name) {} 
  SizingPeriod_DesignDayFields(const std::string &t_name) 
   : EnumBase<SizingPeriod_DesignDayFields>(t_name) {} 
  SizingPeriod_DesignDayFields(int t_value) 
   : EnumBase<SizingPeriod_DesignDayFields>(t_value) {} 
  static std::string enumName() 
  { return "SizingPeriod_DesignDayFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SizingPeriod_DesignDayFields>::value()); }
   private:
    friend class EnumBase<SizingPeriod_DesignDayFields>;
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
{ SizingPeriod_DesignDayFields::Name, "Name", "Name"},
{ SizingPeriod_DesignDayFields::Month, "Month", "Month"},
{ SizingPeriod_DesignDayFields::DayofMonth, "DayofMonth", "Day of Month"},
{ SizingPeriod_DesignDayFields::DayType, "DayType", "Day Type"},
{ SizingPeriod_DesignDayFields::MaximumDryBulbTemperature, "MaximumDryBulbTemperature", "Maximum Dry-Bulb Temperature"},
{ SizingPeriod_DesignDayFields::DailyDryBulbTemperatureRange, "DailyDryBulbTemperatureRange", "Daily Dry-Bulb Temperature Range"},
{ SizingPeriod_DesignDayFields::DryBulbTemperatureRangeModifierType, "DryBulbTemperatureRangeModifierType", "Dry-Bulb Temperature Range Modifier Type"},
{ SizingPeriod_DesignDayFields::DryBulbTemperatureRangeModifierDayScheduleName, "DryBulbTemperatureRangeModifierDayScheduleName", "Dry-Bulb Temperature Range Modifier Day Schedule Name"},
{ SizingPeriod_DesignDayFields::HumidityConditionType, "HumidityConditionType", "Humidity Condition Type"},
{ SizingPeriod_DesignDayFields::WetbulborDewPointatMaximumDryBulb, "WetbulborDewPointatMaximumDryBulb", "Wetbulb or DewPoint at Maximum Dry-Bulb"},
{ SizingPeriod_DesignDayFields::HumidityConditionDayScheduleName, "HumidityConditionDayScheduleName", "Humidity Condition Day Schedule Name"},
{ SizingPeriod_DesignDayFields::HumidityRatioatMaximumDryBulb, "HumidityRatioatMaximumDryBulb", "Humidity Ratio at Maximum Dry-Bulb"},
{ SizingPeriod_DesignDayFields::EnthalpyatMaximumDryBulb, "EnthalpyatMaximumDryBulb", "Enthalpy at Maximum Dry-Bulb"},
{ SizingPeriod_DesignDayFields::DailyWetBulbTemperatureRange, "DailyWetBulbTemperatureRange", "Daily Wet-Bulb Temperature Range"},
{ SizingPeriod_DesignDayFields::BarometricPressure, "BarometricPressure", "Barometric Pressure"},
{ SizingPeriod_DesignDayFields::WindSpeed, "WindSpeed", "Wind Speed"},
{ SizingPeriod_DesignDayFields::WindDirection, "WindDirection", "Wind Direction"},
{ SizingPeriod_DesignDayFields::RainIndicator, "RainIndicator", "Rain Indicator"},
{ SizingPeriod_DesignDayFields::SnowIndicator, "SnowIndicator", "Snow Indicator"},
{ SizingPeriod_DesignDayFields::DaylightSavingTimeIndicator, "DaylightSavingTimeIndicator", "Daylight Saving Time Indicator"},
{ SizingPeriod_DesignDayFields::SolarModelIndicator, "SolarModelIndicator", "Solar Model Indicator"},
{ SizingPeriod_DesignDayFields::BeamSolarDayScheduleName, "BeamSolarDayScheduleName", "Beam Solar Day Schedule Name"},
{ SizingPeriod_DesignDayFields::DiffuseSolarDayScheduleName, "DiffuseSolarDayScheduleName", "Diffuse Solar Day Schedule Name"},
{ SizingPeriod_DesignDayFields::ASHRAEClearSkyOpticalDepthforBeamIrradiance_taub_, "ASHRAEClearSkyOpticalDepthforBeamIrradiance_taub_", "ASHRAE Clear Sky Optical Depth for Beam Irradiance (taub)"},
{ SizingPeriod_DesignDayFields::ASHRAEClearSkyOpticalDepthforDiffuseIrradiance_taud_, "ASHRAEClearSkyOpticalDepthforDiffuseIrradiance_taud_", "ASHRAE Clear Sky Optical Depth for Diffuse Irradiance (taud)"},
{ SizingPeriod_DesignDayFields::SkyClearness, "SkyClearness", "Sky Clearness"},
{ SizingPeriod_DesignDayFields::MaximumNumberWarmupDays, "MaximumNumberWarmupDays", "Maximum Number Warmup Days"},
{ SizingPeriod_DesignDayFields::BeginEnvironmentResetMode, "BeginEnvironmentResetMode", "Begin Environment Reset Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const SizingPeriod_DesignDayFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SizingPeriod_DesignDayFields> OptionalSizingPeriod_DesignDayFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SIZINGPERIOD_DESIGNDAY_FIELDENUMS_HXX
