/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_WEATHERPROPERTY_SKYTEMPERATURE_FIELDENUMS_HXX
#define UTILITIES_IDD_WEATHERPROPERTY_SKYTEMPERATURE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WeatherProperty_SkyTemperatureFields
 *  \brief Enumeration of WeatherProperty:SkyTemperature's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WeatherProperty_SkyTemperatureFields, )
#else
class WeatherProperty_SkyTemperatureFields: public ::EnumBase<WeatherProperty_SkyTemperatureFields> {
 public: 
  enum domain 
  {
Name, CalculationType, ScheduleName, UseWeatherFileHorizontalIR,   };
  WeatherProperty_SkyTemperatureFields()
   : EnumBase<WeatherProperty_SkyTemperatureFields>(Name) {} 
  WeatherProperty_SkyTemperatureFields(const std::string &t_name) 
   : EnumBase<WeatherProperty_SkyTemperatureFields>(t_name) {} 
  WeatherProperty_SkyTemperatureFields(int t_value) 
   : EnumBase<WeatherProperty_SkyTemperatureFields>(t_value) {} 
  static std::string enumName() 
  { return "WeatherProperty_SkyTemperatureFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WeatherProperty_SkyTemperatureFields>::integer_value()); }
   private:
    friend class EnumBase<WeatherProperty_SkyTemperatureFields>;
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
{ WeatherProperty_SkyTemperatureFields::Name, "Name", "Name"},
{ WeatherProperty_SkyTemperatureFields::CalculationType, "CalculationType", "Calculation Type"},
{ WeatherProperty_SkyTemperatureFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ WeatherProperty_SkyTemperatureFields::UseWeatherFileHorizontalIR, "UseWeatherFileHorizontalIR", "Use Weather File Horizontal IR"},
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
  inline std::ostream &operator<<(std::ostream &os, const WeatherProperty_SkyTemperatureFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WeatherProperty_SkyTemperatureFields> OptionalWeatherProperty_SkyTemperatureFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WEATHERPROPERTY_SKYTEMPERATURE_FIELDENUMS_HXX
