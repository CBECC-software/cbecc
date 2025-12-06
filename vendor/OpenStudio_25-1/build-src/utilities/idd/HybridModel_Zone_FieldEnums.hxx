/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_HYBRIDMODEL_ZONE_FIELDENUMS_HXX
#define UTILITIES_IDD_HYBRIDMODEL_ZONE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HybridModel_ZoneFields
 *  \brief Enumeration of HybridModel:Zone's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HybridModel_ZoneFields, )
#else
class HybridModel_ZoneFields: public ::EnumBase<HybridModel_ZoneFields> {
 public: 
  enum domain 
  {
Name, ZoneName, CalculateZoneInternalThermalMass, CalculateZoneAirInfiltrationRate, CalculateZonePeopleCount, ZoneMeasuredAirTemperatureScheduleName, ZoneMeasuredAirHumidityRatioScheduleName, ZoneMeasuredAirCO2ConcentrationScheduleName, ZoneInputPeopleActivityScheduleName, ZoneInputPeopleSensibleHeatFractionScheduleName, ZoneInputPeopleRadiantHeatFractionScheduleName, ZoneInputPeopleCO2GenerationRateScheduleName, ZoneInputSupplyAirTemperatureScheduleName, ZoneInputSupplyAirMassFlowRateScheduleName, ZoneInputSupplyAirHumidityRatioScheduleName, ZoneInputSupplyAirCO2ConcentrationScheduleName, BeginMonth, BeginDayofMonth, EndMonth, EndDayofMonth,   };
  HybridModel_ZoneFields()
   : EnumBase<HybridModel_ZoneFields>(Name) {} 
  HybridModel_ZoneFields(const std::string &t_name) 
   : EnumBase<HybridModel_ZoneFields>(t_name) {} 
  HybridModel_ZoneFields(int t_value) 
   : EnumBase<HybridModel_ZoneFields>(t_value) {} 
  static std::string enumName() 
  { return "HybridModel_ZoneFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HybridModel_ZoneFields>::integer_value()); }
   private:
    friend class EnumBase<HybridModel_ZoneFields>;
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
{ HybridModel_ZoneFields::Name, "Name", "Name"},
{ HybridModel_ZoneFields::ZoneName, "ZoneName", "Zone Name"},
{ HybridModel_ZoneFields::CalculateZoneInternalThermalMass, "CalculateZoneInternalThermalMass", "Calculate Zone Internal Thermal Mass"},
{ HybridModel_ZoneFields::CalculateZoneAirInfiltrationRate, "CalculateZoneAirInfiltrationRate", "Calculate Zone Air Infiltration Rate"},
{ HybridModel_ZoneFields::CalculateZonePeopleCount, "CalculateZonePeopleCount", "Calculate Zone People Count"},
{ HybridModel_ZoneFields::ZoneMeasuredAirTemperatureScheduleName, "ZoneMeasuredAirTemperatureScheduleName", "Zone Measured Air Temperature Schedule Name"},
{ HybridModel_ZoneFields::ZoneMeasuredAirHumidityRatioScheduleName, "ZoneMeasuredAirHumidityRatioScheduleName", "Zone Measured Air Humidity Ratio Schedule Name"},
{ HybridModel_ZoneFields::ZoneMeasuredAirCO2ConcentrationScheduleName, "ZoneMeasuredAirCO2ConcentrationScheduleName", "Zone Measured Air CO2 Concentration Schedule Name"},
{ HybridModel_ZoneFields::ZoneInputPeopleActivityScheduleName, "ZoneInputPeopleActivityScheduleName", "Zone Input People Activity Schedule Name"},
{ HybridModel_ZoneFields::ZoneInputPeopleSensibleHeatFractionScheduleName, "ZoneInputPeopleSensibleHeatFractionScheduleName", "Zone Input People Sensible Heat Fraction Schedule Name"},
{ HybridModel_ZoneFields::ZoneInputPeopleRadiantHeatFractionScheduleName, "ZoneInputPeopleRadiantHeatFractionScheduleName", "Zone Input People Radiant Heat Fraction Schedule Name"},
{ HybridModel_ZoneFields::ZoneInputPeopleCO2GenerationRateScheduleName, "ZoneInputPeopleCO2GenerationRateScheduleName", "Zone Input People CO2 Generation Rate Schedule Name"},
{ HybridModel_ZoneFields::ZoneInputSupplyAirTemperatureScheduleName, "ZoneInputSupplyAirTemperatureScheduleName", "Zone Input Supply Air Temperature Schedule Name"},
{ HybridModel_ZoneFields::ZoneInputSupplyAirMassFlowRateScheduleName, "ZoneInputSupplyAirMassFlowRateScheduleName", "Zone Input Supply Air Mass Flow Rate Schedule Name"},
{ HybridModel_ZoneFields::ZoneInputSupplyAirHumidityRatioScheduleName, "ZoneInputSupplyAirHumidityRatioScheduleName", "Zone Input Supply Air Humidity Ratio Schedule Name"},
{ HybridModel_ZoneFields::ZoneInputSupplyAirCO2ConcentrationScheduleName, "ZoneInputSupplyAirCO2ConcentrationScheduleName", "Zone Input Supply Air CO2 Concentration Schedule Name"},
{ HybridModel_ZoneFields::BeginMonth, "BeginMonth", "Begin Month"},
{ HybridModel_ZoneFields::BeginDayofMonth, "BeginDayofMonth", "Begin Day of Month"},
{ HybridModel_ZoneFields::EndMonth, "EndMonth", "End Month"},
{ HybridModel_ZoneFields::EndDayofMonth, "EndDayofMonth", "End Day of Month"},
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
  inline std::ostream &operator<<(std::ostream &os, const HybridModel_ZoneFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HybridModel_ZoneFields> OptionalHybridModel_ZoneFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HYBRIDMODEL_ZONE_FIELDENUMS_HXX
