/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SIZING_ZONE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SIZING_ZONE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Sizing_ZoneFields
 *  \brief Enumeration of OS:Sizing:Zone's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Sizing_ZoneFields, )
#else
class OS_Sizing_ZoneFields: public ::EnumBase<OS_Sizing_ZoneFields> {
 public: 
  enum domain 
  {
Handle, ZoneorZoneListName, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperatureDifference, ZoneCoolingDesignSupplyAirHumidityRatio, ZoneHeatingDesignSupplyAirHumidityRatio, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, CoolingDesignAirFlowMethod, CoolingDesignAirFlowRate, CoolingMinimumAirFlowperZoneFloorArea, CoolingMinimumAirFlow, CoolingMinimumAirFlowFraction, HeatingDesignAirFlowMethod, HeatingDesignAirFlowRate, HeatingMaximumAirFlowperZoneFloorArea, HeatingMaximumAirFlow, HeatingMaximumAirFlowFraction, AccountforDedicatedOutdoorAirSystem, DedicatedOutdoorAirSystemControlStrategy, DedicatedOutdoorAirLowSetpointTemperatureforDesign, DedicatedOutdoorAirHighSetpointTemperatureforDesign, ZoneLoadSizingMethod, ZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod, ZoneDehumidificationDesignSupplyAirHumidityRatio, ZoneCoolingDesignSupplyAirHumidityRatioDifference, ZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod, ZoneHumidificationDesignSupplyAirHumidityRatio, ZoneHumidificationDesignSupplyAirHumidityRatioDifference, ZoneHumidistatDehumidificationSetPointScheduleName, ZoneHumidistatHumidificationSetPointScheduleName, DesignZoneAirDistributionEffectivenessinCoolingMode, DesignZoneAirDistributionEffectivenessinHeatingMode, DesignZoneSecondaryRecirculationFraction, DesignMinimumZoneVentilationEfficiency, SizingOption,   };
  OS_Sizing_ZoneFields()
   : EnumBase<OS_Sizing_ZoneFields>(Handle) {} 
  OS_Sizing_ZoneFields(const std::string &t_name) 
   : EnumBase<OS_Sizing_ZoneFields>(t_name) {} 
  OS_Sizing_ZoneFields(int t_value) 
   : EnumBase<OS_Sizing_ZoneFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Sizing_ZoneFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Sizing_ZoneFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Sizing_ZoneFields>;
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
{ OS_Sizing_ZoneFields::Handle, "Handle", "Handle"},
{ OS_Sizing_ZoneFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ OS_Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, "ZoneCoolingDesignSupplyAirTemperatureInputMethod", "Zone Cooling Design Supply Air Temperature Input Method"},
{ OS_Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperature, "ZoneCoolingDesignSupplyAirTemperature", "Zone Cooling Design Supply Air Temperature"},
{ OS_Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperatureDifference, "ZoneCoolingDesignSupplyAirTemperatureDifference", "Zone Cooling Design Supply Air Temperature Difference"},
{ OS_Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, "ZoneHeatingDesignSupplyAirTemperatureInputMethod", "Zone Heating Design Supply Air Temperature Input Method"},
{ OS_Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperature, "ZoneHeatingDesignSupplyAirTemperature", "Zone Heating Design Supply Air Temperature"},
{ OS_Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperatureDifference, "ZoneHeatingDesignSupplyAirTemperatureDifference", "Zone Heating Design Supply Air Temperature Difference"},
{ OS_Sizing_ZoneFields::ZoneCoolingDesignSupplyAirHumidityRatio, "ZoneCoolingDesignSupplyAirHumidityRatio", "Zone Cooling Design Supply Air Humidity Ratio"},
{ OS_Sizing_ZoneFields::ZoneHeatingDesignSupplyAirHumidityRatio, "ZoneHeatingDesignSupplyAirHumidityRatio", "Zone Heating Design Supply Air Humidity Ratio"},
{ OS_Sizing_ZoneFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ OS_Sizing_ZoneFields::ZoneCoolingSizingFactor, "ZoneCoolingSizingFactor", "Zone Cooling Sizing Factor"},
{ OS_Sizing_ZoneFields::CoolingDesignAirFlowMethod, "CoolingDesignAirFlowMethod", "Cooling Design Air Flow Method"},
{ OS_Sizing_ZoneFields::CoolingDesignAirFlowRate, "CoolingDesignAirFlowRate", "Cooling Design Air Flow Rate"},
{ OS_Sizing_ZoneFields::CoolingMinimumAirFlowperZoneFloorArea, "CoolingMinimumAirFlowperZoneFloorArea", "Cooling Minimum Air Flow per Zone Floor Area"},
{ OS_Sizing_ZoneFields::CoolingMinimumAirFlow, "CoolingMinimumAirFlow", "Cooling Minimum Air Flow"},
{ OS_Sizing_ZoneFields::CoolingMinimumAirFlowFraction, "CoolingMinimumAirFlowFraction", "Cooling Minimum Air Flow Fraction"},
{ OS_Sizing_ZoneFields::HeatingDesignAirFlowMethod, "HeatingDesignAirFlowMethod", "Heating Design Air Flow Method"},
{ OS_Sizing_ZoneFields::HeatingDesignAirFlowRate, "HeatingDesignAirFlowRate", "Heating Design Air Flow Rate"},
{ OS_Sizing_ZoneFields::HeatingMaximumAirFlowperZoneFloorArea, "HeatingMaximumAirFlowperZoneFloorArea", "Heating Maximum Air Flow per Zone Floor Area"},
{ OS_Sizing_ZoneFields::HeatingMaximumAirFlow, "HeatingMaximumAirFlow", "Heating Maximum Air Flow"},
{ OS_Sizing_ZoneFields::HeatingMaximumAirFlowFraction, "HeatingMaximumAirFlowFraction", "Heating Maximum Air Flow Fraction"},
{ OS_Sizing_ZoneFields::AccountforDedicatedOutdoorAirSystem, "AccountforDedicatedOutdoorAirSystem", "Account for Dedicated Outdoor Air System"},
{ OS_Sizing_ZoneFields::DedicatedOutdoorAirSystemControlStrategy, "DedicatedOutdoorAirSystemControlStrategy", "Dedicated Outdoor Air System Control Strategy"},
{ OS_Sizing_ZoneFields::DedicatedOutdoorAirLowSetpointTemperatureforDesign, "DedicatedOutdoorAirLowSetpointTemperatureforDesign", "Dedicated Outdoor Air Low Setpoint Temperature for Design"},
{ OS_Sizing_ZoneFields::DedicatedOutdoorAirHighSetpointTemperatureforDesign, "DedicatedOutdoorAirHighSetpointTemperatureforDesign", "Dedicated Outdoor Air High Setpoint Temperature for Design"},
{ OS_Sizing_ZoneFields::ZoneLoadSizingMethod, "ZoneLoadSizingMethod", "Zone Load Sizing Method"},
{ OS_Sizing_ZoneFields::ZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod, "ZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod", "Zone Latent Cooling Design Supply Air Humidity Ratio Input Method"},
{ OS_Sizing_ZoneFields::ZoneDehumidificationDesignSupplyAirHumidityRatio, "ZoneDehumidificationDesignSupplyAirHumidityRatio", "Zone Dehumidification Design Supply Air Humidity Ratio"},
{ OS_Sizing_ZoneFields::ZoneCoolingDesignSupplyAirHumidityRatioDifference, "ZoneCoolingDesignSupplyAirHumidityRatioDifference", "Zone Cooling Design Supply Air Humidity Ratio Difference"},
{ OS_Sizing_ZoneFields::ZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod, "ZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod", "Zone Latent Heating Design Supply Air Humidity Ratio Input Method"},
{ OS_Sizing_ZoneFields::ZoneHumidificationDesignSupplyAirHumidityRatio, "ZoneHumidificationDesignSupplyAirHumidityRatio", "Zone Humidification Design Supply Air Humidity Ratio"},
{ OS_Sizing_ZoneFields::ZoneHumidificationDesignSupplyAirHumidityRatioDifference, "ZoneHumidificationDesignSupplyAirHumidityRatioDifference", "Zone Humidification Design Supply Air Humidity Ratio Difference"},
{ OS_Sizing_ZoneFields::ZoneHumidistatDehumidificationSetPointScheduleName, "ZoneHumidistatDehumidificationSetPointScheduleName", "Zone Humidistat Dehumidification Set Point Schedule Name"},
{ OS_Sizing_ZoneFields::ZoneHumidistatHumidificationSetPointScheduleName, "ZoneHumidistatHumidificationSetPointScheduleName", "Zone Humidistat Humidification Set Point Schedule Name"},
{ OS_Sizing_ZoneFields::DesignZoneAirDistributionEffectivenessinCoolingMode, "DesignZoneAirDistributionEffectivenessinCoolingMode", "Design Zone Air Distribution Effectiveness in Cooling Mode"},
{ OS_Sizing_ZoneFields::DesignZoneAirDistributionEffectivenessinHeatingMode, "DesignZoneAirDistributionEffectivenessinHeatingMode", "Design Zone Air Distribution Effectiveness in Heating Mode"},
{ OS_Sizing_ZoneFields::DesignZoneSecondaryRecirculationFraction, "DesignZoneSecondaryRecirculationFraction", "Design Zone Secondary Recirculation Fraction"},
{ OS_Sizing_ZoneFields::DesignMinimumZoneVentilationEfficiency, "DesignMinimumZoneVentilationEfficiency", "Design Minimum Zone Ventilation Efficiency"},
{ OS_Sizing_ZoneFields::SizingOption, "SizingOption", "Sizing Option"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Sizing_ZoneFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Sizing_ZoneFields> OptionalOS_Sizing_ZoneFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SIZING_ZONE_FIELDENUMS_HXX
