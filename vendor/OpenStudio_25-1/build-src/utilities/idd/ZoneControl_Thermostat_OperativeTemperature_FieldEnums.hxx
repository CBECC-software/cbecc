/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONECONTROL_THERMOSTAT_OPERATIVETEMPERATURE_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONECONTROL_THERMOSTAT_OPERATIVETEMPERATURE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneControl_Thermostat_OperativeTemperatureFields
 *  \brief Enumeration of ZoneControl:Thermostat:OperativeTemperature's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneControl_Thermostat_OperativeTemperatureFields, )
#else
class ZoneControl_Thermostat_OperativeTemperatureFields: public ::EnumBase<ZoneControl_Thermostat_OperativeTemperatureFields> {
 public: 
  enum domain 
  {
ThermostatName, RadiativeFractionInputMode, FixedRadiativeFraction, RadiativeFractionScheduleName, AdaptiveComfortModelType,   };
  ZoneControl_Thermostat_OperativeTemperatureFields()
   : EnumBase<ZoneControl_Thermostat_OperativeTemperatureFields>(ThermostatName) {} 
  ZoneControl_Thermostat_OperativeTemperatureFields(const std::string &t_name) 
   : EnumBase<ZoneControl_Thermostat_OperativeTemperatureFields>(t_name) {} 
  ZoneControl_Thermostat_OperativeTemperatureFields(int t_value) 
   : EnumBase<ZoneControl_Thermostat_OperativeTemperatureFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneControl_Thermostat_OperativeTemperatureFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneControl_Thermostat_OperativeTemperatureFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneControl_Thermostat_OperativeTemperatureFields>;
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
{ ZoneControl_Thermostat_OperativeTemperatureFields::ThermostatName, "ThermostatName", "Thermostat Name"},
{ ZoneControl_Thermostat_OperativeTemperatureFields::RadiativeFractionInputMode, "RadiativeFractionInputMode", "Radiative Fraction Input Mode"},
{ ZoneControl_Thermostat_OperativeTemperatureFields::FixedRadiativeFraction, "FixedRadiativeFraction", "Fixed Radiative Fraction"},
{ ZoneControl_Thermostat_OperativeTemperatureFields::RadiativeFractionScheduleName, "RadiativeFractionScheduleName", "Radiative Fraction Schedule Name"},
{ ZoneControl_Thermostat_OperativeTemperatureFields::AdaptiveComfortModelType, "AdaptiveComfortModelType", "Adaptive Comfort Model Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneControl_Thermostat_OperativeTemperatureFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneControl_Thermostat_OperativeTemperatureFields> OptionalZoneControl_Thermostat_OperativeTemperatureFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONECONTROL_THERMOSTAT_OPERATIVETEMPERATURE_FIELDENUMS_HXX
