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

#ifndef UTILITIES_IDD_SIZING_ZONE_FIELDENUMS_HXX
#define UTILITIES_IDD_SIZING_ZONE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Sizing_ZoneFields
 *  \brief Enumeration of Sizing:Zone's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Sizing_ZoneFields, )
#else
class Sizing_ZoneFields: public ::EnumBase<Sizing_ZoneFields> {
 public: 
  enum domain 
  {
ZoneorZoneListName, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperatureDifference, ZoneCoolingDesignSupplyAirHumidityRatio, ZoneHeatingDesignSupplyAirHumidityRatio, DesignSpecificationOutdoorAirObjectName, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, CoolingDesignAirFlowMethod, CoolingDesignAirFlowRate, CoolingMinimumAirFlowperZoneFloorArea, CoolingMinimumAirFlow, CoolingMinimumAirFlowFraction, HeatingDesignAirFlowMethod, HeatingDesignAirFlowRate, HeatingMaximumAirFlowperZoneFloorArea, HeatingMaximumAirFlow, HeatingMaximumAirFlowFraction, DesignSpecificationZoneAirDistributionObjectName, AccountforDedicatedOutdoorAirSystem, DedicatedOutdoorAirSystemControlStrategy, DedicatedOutdoorAirLowSetpointTemperatureforDesign, DedicatedOutdoorAirHighSetpointTemperatureforDesign,   };
  Sizing_ZoneFields()
   : EnumBase<Sizing_ZoneFields>(ZoneorZoneListName) {} 
  Sizing_ZoneFields(const std::string &t_name) 
   : EnumBase<Sizing_ZoneFields>(t_name) {} 
  Sizing_ZoneFields(int t_value) 
   : EnumBase<Sizing_ZoneFields>(t_value) {} 
  static std::string enumName() 
  { return "Sizing_ZoneFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Sizing_ZoneFields>::value()); }
   private:
    friend class EnumBase<Sizing_ZoneFields>;
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
{ Sizing_ZoneFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, "ZoneCoolingDesignSupplyAirTemperatureInputMethod", "Zone Cooling Design Supply Air Temperature Input Method"},
{ Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperature, "ZoneCoolingDesignSupplyAirTemperature", "Zone Cooling Design Supply Air Temperature"},
{ Sizing_ZoneFields::ZoneCoolingDesignSupplyAirTemperatureDifference, "ZoneCoolingDesignSupplyAirTemperatureDifference", "Zone Cooling Design Supply Air Temperature Difference"},
{ Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, "ZoneHeatingDesignSupplyAirTemperatureInputMethod", "Zone Heating Design Supply Air Temperature Input Method"},
{ Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperature, "ZoneHeatingDesignSupplyAirTemperature", "Zone Heating Design Supply Air Temperature"},
{ Sizing_ZoneFields::ZoneHeatingDesignSupplyAirTemperatureDifference, "ZoneHeatingDesignSupplyAirTemperatureDifference", "Zone Heating Design Supply Air Temperature Difference"},
{ Sizing_ZoneFields::ZoneCoolingDesignSupplyAirHumidityRatio, "ZoneCoolingDesignSupplyAirHumidityRatio", "Zone Cooling Design Supply Air Humidity Ratio"},
{ Sizing_ZoneFields::ZoneHeatingDesignSupplyAirHumidityRatio, "ZoneHeatingDesignSupplyAirHumidityRatio", "Zone Heating Design Supply Air Humidity Ratio"},
{ Sizing_ZoneFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ Sizing_ZoneFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ Sizing_ZoneFields::ZoneCoolingSizingFactor, "ZoneCoolingSizingFactor", "Zone Cooling Sizing Factor"},
{ Sizing_ZoneFields::CoolingDesignAirFlowMethod, "CoolingDesignAirFlowMethod", "Cooling Design Air Flow Method"},
{ Sizing_ZoneFields::CoolingDesignAirFlowRate, "CoolingDesignAirFlowRate", "Cooling Design Air Flow Rate"},
{ Sizing_ZoneFields::CoolingMinimumAirFlowperZoneFloorArea, "CoolingMinimumAirFlowperZoneFloorArea", "Cooling Minimum Air Flow per Zone Floor Area"},
{ Sizing_ZoneFields::CoolingMinimumAirFlow, "CoolingMinimumAirFlow", "Cooling Minimum Air Flow"},
{ Sizing_ZoneFields::CoolingMinimumAirFlowFraction, "CoolingMinimumAirFlowFraction", "Cooling Minimum Air Flow Fraction"},
{ Sizing_ZoneFields::HeatingDesignAirFlowMethod, "HeatingDesignAirFlowMethod", "Heating Design Air Flow Method"},
{ Sizing_ZoneFields::HeatingDesignAirFlowRate, "HeatingDesignAirFlowRate", "Heating Design Air Flow Rate"},
{ Sizing_ZoneFields::HeatingMaximumAirFlowperZoneFloorArea, "HeatingMaximumAirFlowperZoneFloorArea", "Heating Maximum Air Flow per Zone Floor Area"},
{ Sizing_ZoneFields::HeatingMaximumAirFlow, "HeatingMaximumAirFlow", "Heating Maximum Air Flow"},
{ Sizing_ZoneFields::HeatingMaximumAirFlowFraction, "HeatingMaximumAirFlowFraction", "Heating Maximum Air Flow Fraction"},
{ Sizing_ZoneFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
{ Sizing_ZoneFields::AccountforDedicatedOutdoorAirSystem, "AccountforDedicatedOutdoorAirSystem", "Account for Dedicated Outdoor Air System"},
{ Sizing_ZoneFields::DedicatedOutdoorAirSystemControlStrategy, "DedicatedOutdoorAirSystemControlStrategy", "Dedicated Outdoor Air System Control Strategy"},
{ Sizing_ZoneFields::DedicatedOutdoorAirLowSetpointTemperatureforDesign, "DedicatedOutdoorAirLowSetpointTemperatureforDesign", "Dedicated Outdoor Air Low Setpoint Temperature for Design"},
{ Sizing_ZoneFields::DedicatedOutdoorAirHighSetpointTemperatureforDesign, "DedicatedOutdoorAirHighSetpointTemperatureforDesign", "Dedicated Outdoor Air High Setpoint Temperature for Design"},
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
  inline std::ostream &operator<<(std::ostream &os, const Sizing_ZoneFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Sizing_ZoneFields> OptionalSizing_ZoneFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SIZING_ZONE_FIELDENUMS_HXX
