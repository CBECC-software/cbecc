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

#ifndef UTILITIES_IDD_ZONEHVAC_HYBRIDUNITARYHVAC_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_HYBRIDUNITARYHVAC_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_HybridUnitaryHVACFields
 *  \brief Enumeration of ZoneHVAC:HybridUnitaryHVAC's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_HybridUnitaryHVACFields, )
#else
class ZoneHVAC_HybridUnitaryHVACFields: public ::EnumBase<ZoneHVAC_HybridUnitaryHVACFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AvailabilityManagerListName, MinimumSupplyAirTemperatureScheduleName, MaximumSupplyAirTemperatureScheduleName, MinimumSupplyAirHumidityRatioScheduleName, MaximumSupplyAirHumidityRatioScheduleName, MethodtoChooseControlledInputsandPartRuntimeFraction, ReturnAirNodeName, OutdoorAirNodeName, SupplyAirNodeName, ReliefNodeName, SystemMaximumSupplyAirFlowRate, ExternalStaticPressureatSystemMaximumSupplyAirFlowRate, FanHeatIncludedinLookupTables, FanHeatGainLocation, FanHeatInAirStreamFraction, ScalingFactor, MinimumTimeBetweenModeChange, FirstFuelType, SecondFuelType, ThirdFuelType, ObjectiveFunctiontoMinimize, DesignSpecificationOutdoorAirObjectName, Mode0Name, Mode0SupplyAirTemperatureLookupTableName, Mode0SupplyAirHumidityRatioLookupTableName, Mode0SystemElectricPowerLookupTableName, Mode0SupplyFanElectricPowerLookupTableName, Mode0ExternalStaticPressureLookupTableName, Mode0SystemSecondFuelConsumptionLookupTableName, Mode0SystemThirdFuelConsumptionLookupTableName, Mode0SystemWaterUseLookupTableName, Mode0OutdoorAirFraction, Mode0SupplyAirMassFlowRateRatio,   };
  ZoneHVAC_HybridUnitaryHVACFields()
   : EnumBase<ZoneHVAC_HybridUnitaryHVACFields>(Name) {} 
  ZoneHVAC_HybridUnitaryHVACFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_HybridUnitaryHVACFields>(t_name) {} 
  ZoneHVAC_HybridUnitaryHVACFields(int t_value) 
   : EnumBase<ZoneHVAC_HybridUnitaryHVACFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_HybridUnitaryHVACFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_HybridUnitaryHVACFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_HybridUnitaryHVACFields>;
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
{ ZoneHVAC_HybridUnitaryHVACFields::Name, "Name", "Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::MinimumSupplyAirTemperatureScheduleName, "MinimumSupplyAirTemperatureScheduleName", "Minimum Supply Air Temperature Schedule Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::MaximumSupplyAirTemperatureScheduleName, "MaximumSupplyAirTemperatureScheduleName", "Maximum Supply Air Temperature Schedule Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::MinimumSupplyAirHumidityRatioScheduleName, "MinimumSupplyAirHumidityRatioScheduleName", "Minimum Supply Air Humidity Ratio Schedule Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::MaximumSupplyAirHumidityRatioScheduleName, "MaximumSupplyAirHumidityRatioScheduleName", "Maximum Supply Air Humidity Ratio Schedule Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::MethodtoChooseControlledInputsandPartRuntimeFraction, "MethodtoChooseControlledInputsandPartRuntimeFraction", "Method to Choose Controlled Inputs and Part Runtime Fraction"},
{ ZoneHVAC_HybridUnitaryHVACFields::ReturnAirNodeName, "ReturnAirNodeName", "Return Air Node Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::OutdoorAirNodeName, "OutdoorAirNodeName", "Outdoor Air Node Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::SupplyAirNodeName, "SupplyAirNodeName", "Supply Air Node Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::ReliefNodeName, "ReliefNodeName", "Relief Node Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::SystemMaximumSupplyAirFlowRate, "SystemMaximumSupplyAirFlowRate", "System Maximum Supply Air Flow Rate"},
{ ZoneHVAC_HybridUnitaryHVACFields::ExternalStaticPressureatSystemMaximumSupplyAirFlowRate, "ExternalStaticPressureatSystemMaximumSupplyAirFlowRate", "External Static Pressure at System Maximum Supply Air Flow Rate"},
{ ZoneHVAC_HybridUnitaryHVACFields::FanHeatIncludedinLookupTables, "FanHeatIncludedinLookupTables", "Fan Heat Included in Lookup Tables"},
{ ZoneHVAC_HybridUnitaryHVACFields::FanHeatGainLocation, "FanHeatGainLocation", "Fan Heat Gain Location"},
{ ZoneHVAC_HybridUnitaryHVACFields::FanHeatInAirStreamFraction, "FanHeatInAirStreamFraction", "Fan Heat In Air Stream Fraction"},
{ ZoneHVAC_HybridUnitaryHVACFields::ScalingFactor, "ScalingFactor", "Scaling Factor"},
{ ZoneHVAC_HybridUnitaryHVACFields::MinimumTimeBetweenModeChange, "MinimumTimeBetweenModeChange", "Minimum Time Between Mode Change"},
{ ZoneHVAC_HybridUnitaryHVACFields::FirstFuelType, "FirstFuelType", "First Fuel Type"},
{ ZoneHVAC_HybridUnitaryHVACFields::SecondFuelType, "SecondFuelType", "Second Fuel Type"},
{ ZoneHVAC_HybridUnitaryHVACFields::ThirdFuelType, "ThirdFuelType", "Third Fuel Type"},
{ ZoneHVAC_HybridUnitaryHVACFields::ObjectiveFunctiontoMinimize, "ObjectiveFunctiontoMinimize", "Objective Function to Minimize"},
{ ZoneHVAC_HybridUnitaryHVACFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0Name, "Mode0Name", "Mode 0 Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0SupplyAirTemperatureLookupTableName, "Mode0SupplyAirTemperatureLookupTableName", "Mode 0 Supply Air Temperature Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0SupplyAirHumidityRatioLookupTableName, "Mode0SupplyAirHumidityRatioLookupTableName", "Mode 0 Supply Air Humidity Ratio Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0SystemElectricPowerLookupTableName, "Mode0SystemElectricPowerLookupTableName", "Mode 0 System Electric Power Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0SupplyFanElectricPowerLookupTableName, "Mode0SupplyFanElectricPowerLookupTableName", "Mode 0 Supply Fan Electric Power Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0ExternalStaticPressureLookupTableName, "Mode0ExternalStaticPressureLookupTableName", "Mode 0 External Static Pressure Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0SystemSecondFuelConsumptionLookupTableName, "Mode0SystemSecondFuelConsumptionLookupTableName", "Mode 0 System Second Fuel Consumption Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0SystemThirdFuelConsumptionLookupTableName, "Mode0SystemThirdFuelConsumptionLookupTableName", "Mode 0 System Third Fuel Consumption Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0SystemWaterUseLookupTableName, "Mode0SystemWaterUseLookupTableName", "Mode 0 System Water Use Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0OutdoorAirFraction, "Mode0OutdoorAirFraction", "Mode 0 Outdoor Air Fraction"},
{ ZoneHVAC_HybridUnitaryHVACFields::Mode0SupplyAirMassFlowRateRatio, "Mode0SupplyAirMassFlowRateRatio", "Mode 0 Supply Air Mass Flow Rate Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_HybridUnitaryHVACFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_HybridUnitaryHVACFields> OptionalZoneHVAC_HybridUnitaryHVACFields ;
#endif

/** \class ZoneHVAC_HybridUnitaryHVACExtensibleFields
 *  \brief Enumeration of ZoneHVAC:HybridUnitaryHVAC's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_HybridUnitaryHVACExtensibleFields, )
#else
class ZoneHVAC_HybridUnitaryHVACExtensibleFields: public ::EnumBase<ZoneHVAC_HybridUnitaryHVACExtensibleFields> {
 public: 
  enum domain 
  {
ModeName, ModeSupplyAirTemperatureLookupTableName, ModeSupplyAirHumidityRatioLookupTableName, ModeSystemElectricPowerLookupTableName, ModeSupplyFanElectricPowerLookupTableName, ModeExternalStaticPressureLookupTableName, ModeSystemSecondFuelConsumptionLookupTableName, ModeSystemThirdFuelConsumptionLookupTableName, ModeSystemWaterUseLookupTableName, ModeMinimumOutdoorAirTemperature, ModeMaximumOutdoorAirTemperature, ModeMinimumOutdoorAirHumidityRatio, ModeMaximumOutdoorAirHumidityRatio, ModeMinimumOutdoorAirRelativeHumidity, ModeMaximumOutdoorAirRelativeHumidity, ModeMinimumReturnAirTemperature, ModeMaximumReturnAirTemperature, ModeMinimumReturnAirHumidityRatio, ModeMaximumReturnAirHumidityRatio, ModeMinimumReturnAirRelativeHumidity, ModeMaximumReturnAirRelativeHumidity, ModeMinimumOutdoorAirFraction, ModeMaximumOutdoorAirFraction, ModeMinimumSupplyAirMassFlowRateRatio, ModeMaximumSupplyAirMassFlowRateRatio,   };
  ZoneHVAC_HybridUnitaryHVACExtensibleFields()
   : EnumBase<ZoneHVAC_HybridUnitaryHVACExtensibleFields>(ModeName) {} 
  ZoneHVAC_HybridUnitaryHVACExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_HybridUnitaryHVACExtensibleFields>(t_name) {} 
  ZoneHVAC_HybridUnitaryHVACExtensibleFields(int t_value) 
   : EnumBase<ZoneHVAC_HybridUnitaryHVACExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_HybridUnitaryHVACExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_HybridUnitaryHVACExtensibleFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_HybridUnitaryHVACExtensibleFields>;
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
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeName, "ModeName", "Mode Name"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeSupplyAirTemperatureLookupTableName, "ModeSupplyAirTemperatureLookupTableName", "Mode Supply Air Temperature Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeSupplyAirHumidityRatioLookupTableName, "ModeSupplyAirHumidityRatioLookupTableName", "Mode Supply Air Humidity Ratio Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeSystemElectricPowerLookupTableName, "ModeSystemElectricPowerLookupTableName", "Mode System Electric Power Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeSupplyFanElectricPowerLookupTableName, "ModeSupplyFanElectricPowerLookupTableName", "Mode Supply Fan Electric Power Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeExternalStaticPressureLookupTableName, "ModeExternalStaticPressureLookupTableName", "Mode External Static Pressure Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeSystemSecondFuelConsumptionLookupTableName, "ModeSystemSecondFuelConsumptionLookupTableName", "Mode System Second Fuel Consumption Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeSystemThirdFuelConsumptionLookupTableName, "ModeSystemThirdFuelConsumptionLookupTableName", "Mode System Third Fuel Consumption Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeSystemWaterUseLookupTableName, "ModeSystemWaterUseLookupTableName", "Mode System Water Use Lookup Table Name"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMinimumOutdoorAirTemperature, "ModeMinimumOutdoorAirTemperature", "Mode Minimum Outdoor Air Temperature"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMaximumOutdoorAirTemperature, "ModeMaximumOutdoorAirTemperature", "Mode Maximum Outdoor Air Temperature"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMinimumOutdoorAirHumidityRatio, "ModeMinimumOutdoorAirHumidityRatio", "Mode Minimum Outdoor Air Humidity Ratio"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMaximumOutdoorAirHumidityRatio, "ModeMaximumOutdoorAirHumidityRatio", "Mode Maximum Outdoor Air Humidity Ratio"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMinimumOutdoorAirRelativeHumidity, "ModeMinimumOutdoorAirRelativeHumidity", "Mode Minimum Outdoor Air Relative Humidity"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMaximumOutdoorAirRelativeHumidity, "ModeMaximumOutdoorAirRelativeHumidity", "Mode Maximum Outdoor Air Relative Humidity"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMinimumReturnAirTemperature, "ModeMinimumReturnAirTemperature", "Mode Minimum Return Air Temperature"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMaximumReturnAirTemperature, "ModeMaximumReturnAirTemperature", "Mode Maximum Return Air Temperature"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMinimumReturnAirHumidityRatio, "ModeMinimumReturnAirHumidityRatio", "Mode Minimum Return Air Humidity Ratio"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMaximumReturnAirHumidityRatio, "ModeMaximumReturnAirHumidityRatio", "Mode Maximum Return Air Humidity Ratio"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMinimumReturnAirRelativeHumidity, "ModeMinimumReturnAirRelativeHumidity", "Mode Minimum Return Air Relative Humidity"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMaximumReturnAirRelativeHumidity, "ModeMaximumReturnAirRelativeHumidity", "Mode Maximum Return Air Relative Humidity"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMinimumOutdoorAirFraction, "ModeMinimumOutdoorAirFraction", "Mode Minimum Outdoor Air Fraction"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMaximumOutdoorAirFraction, "ModeMaximumOutdoorAirFraction", "Mode Maximum Outdoor Air Fraction"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMinimumSupplyAirMassFlowRateRatio, "ModeMinimumSupplyAirMassFlowRateRatio", "Mode Minimum Supply Air Mass Flow Rate Ratio"},
{ ZoneHVAC_HybridUnitaryHVACExtensibleFields::ModeMaximumSupplyAirMassFlowRateRatio, "ModeMaximumSupplyAirMassFlowRateRatio", "Mode Maximum Supply Air Mass Flow Rate Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_HybridUnitaryHVACExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_HybridUnitaryHVACExtensibleFields> OptionalZoneHVAC_HybridUnitaryHVACExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_HYBRIDUNITARYHVAC_FIELDENUMS_HXX
