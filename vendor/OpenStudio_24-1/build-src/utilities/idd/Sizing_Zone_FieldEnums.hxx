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
ZoneorZoneListName, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperatureDifference, ZoneCoolingDesignSupplyAirHumidityRatio, ZoneHeatingDesignSupplyAirHumidityRatio, DesignSpecificationOutdoorAirObjectName, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, CoolingDesignAirFlowMethod, CoolingDesignAirFlowRate, CoolingMinimumAirFlowperZoneFloorArea, CoolingMinimumAirFlow, CoolingMinimumAirFlowFraction, HeatingDesignAirFlowMethod, HeatingDesignAirFlowRate, HeatingMaximumAirFlowperZoneFloorArea, HeatingMaximumAirFlow, HeatingMaximumAirFlowFraction, DesignSpecificationZoneAirDistributionObjectName, AccountforDedicatedOutdoorAirSystem, DedicatedOutdoorAirSystemControlStrategy, DedicatedOutdoorAirLowSetpointTemperatureforDesign, DedicatedOutdoorAirHighSetpointTemperatureforDesign, ZoneLoadSizingMethod, ZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod, ZoneDehumidificationDesignSupplyAirHumidityRatio, ZoneCoolingDesignSupplyAirHumidityRatioDifference, ZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod, ZoneHumidificationDesignSupplyAirHumidityRatio, ZoneHumidificationDesignSupplyAirHumidityRatioDifference, ZoneHumidistatDehumidificationSetPointScheduleName, ZoneHumidistatHumidificationSetPointScheduleName,   };
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
{ Sizing_ZoneFields::ZoneLoadSizingMethod, "ZoneLoadSizingMethod", "Zone Load Sizing Method"},
{ Sizing_ZoneFields::ZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod, "ZoneLatentCoolingDesignSupplyAirHumidityRatioInputMethod", "Zone Latent Cooling Design Supply Air Humidity Ratio Input Method"},
{ Sizing_ZoneFields::ZoneDehumidificationDesignSupplyAirHumidityRatio, "ZoneDehumidificationDesignSupplyAirHumidityRatio", "Zone Dehumidification Design Supply Air Humidity Ratio"},
{ Sizing_ZoneFields::ZoneCoolingDesignSupplyAirHumidityRatioDifference, "ZoneCoolingDesignSupplyAirHumidityRatioDifference", "Zone Cooling Design Supply Air Humidity Ratio Difference"},
{ Sizing_ZoneFields::ZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod, "ZoneLatentHeatingDesignSupplyAirHumidityRatioInputMethod", "Zone Latent Heating Design Supply Air Humidity Ratio Input Method"},
{ Sizing_ZoneFields::ZoneHumidificationDesignSupplyAirHumidityRatio, "ZoneHumidificationDesignSupplyAirHumidityRatio", "Zone Humidification Design Supply Air Humidity Ratio"},
{ Sizing_ZoneFields::ZoneHumidificationDesignSupplyAirHumidityRatioDifference, "ZoneHumidificationDesignSupplyAirHumidityRatioDifference", "Zone Humidification Design Supply Air Humidity Ratio Difference"},
{ Sizing_ZoneFields::ZoneHumidistatDehumidificationSetPointScheduleName, "ZoneHumidistatDehumidificationSetPointScheduleName", "Zone Humidistat Dehumidification Set Point Schedule Name"},
{ Sizing_ZoneFields::ZoneHumidistatHumidificationSetPointScheduleName, "ZoneHumidistatHumidificationSetPointScheduleName", "Zone Humidistat Humidification Set Point Schedule Name"},
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
