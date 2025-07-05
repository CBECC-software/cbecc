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

#ifndef UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_FANPOWERED_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_FANPOWERED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Zone_VAV_FanPoweredFields
 *  \brief Enumeration of HVACTemplate:Zone:VAV:FanPowered's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Zone_VAV_FanPoweredFields, )
#else
class HVACTemplate_Zone_VAV_FanPoweredFields: public ::EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields> {
 public: 
  enum domain 
  {
ZoneName, TemplateVAVSystemName, TemplateThermostatName, PrimarySupplyAirMaximumFlowRate, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, PrimarySupplyAirMinimumFlowFraction, SecondarySupplyAirMaximumFlowRate, FlowType, ParallelFanOnFlowFraction, OutdoorAirMethod, OutdoorAirFlowRateperPerson, OutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZone, ReheatCoilType, ReheatCoilAvailabilityScheduleName, FanTotalEfficiency, FanDeltaPressure, FanMotorEfficiency, SupplyPlenumName, ReturnPlenumName, BaseboardHeatingType, BaseboardHeatingAvailabilityScheduleName, BaseboardHeatingCapacity, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperatureDifference, ZonePIUFanScheduleName, DesignSpecificationOutdoorAirObjectName, DesignSpecificationZoneAirDistributionObjectName,   };
  HVACTemplate_Zone_VAV_FanPoweredFields()
   : EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields>(ZoneName) {} 
  HVACTemplate_Zone_VAV_FanPoweredFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields>(t_name) {} 
  HVACTemplate_Zone_VAV_FanPoweredFields(int t_value) 
   : EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Zone_VAV_FanPoweredFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields>;
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
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneName, "ZoneName", "Zone Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::TemplateVAVSystemName, "TemplateVAVSystemName", "Template VAV System Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::TemplateThermostatName, "TemplateThermostatName", "Template Thermostat Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMaximumFlowRate, "PrimarySupplyAirMaximumFlowRate", "Primary Supply Air Maximum Flow Rate"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingSizingFactor, "ZoneCoolingSizingFactor", "Zone Cooling Sizing Factor"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMinimumFlowFraction, "PrimarySupplyAirMinimumFlowFraction", "Primary Supply Air Minimum Flow Fraction"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::SecondarySupplyAirMaximumFlowRate, "SecondarySupplyAirMaximumFlowRate", "Secondary Supply Air Maximum Flow Rate"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::FlowType, "FlowType", "Flow Type"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ParallelFanOnFlowFraction, "ParallelFanOnFlowFraction", "Parallel Fan On Flow Fraction"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirMethod, "OutdoorAirMethod", "Outdoor Air Method"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperPerson, "OutdoorAirFlowRateperPerson", "Outdoor Air Flow Rate per Person"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZoneFloorArea, "OutdoorAirFlowRateperZoneFloorArea", "Outdoor Air Flow Rate per Zone Floor Area"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZone, "OutdoorAirFlowRateperZone", "Outdoor Air Flow Rate per Zone"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ReheatCoilType, "ReheatCoilType", "Reheat Coil Type"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ReheatCoilAvailabilityScheduleName, "ReheatCoilAvailabilityScheduleName", "Reheat Coil Availability Schedule Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::FanDeltaPressure, "FanDeltaPressure", "Fan Delta Pressure"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::FanMotorEfficiency, "FanMotorEfficiency", "Fan Motor Efficiency"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::SupplyPlenumName, "SupplyPlenumName", "Supply Plenum Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ReturnPlenumName, "ReturnPlenumName", "Return Plenum Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingType, "BaseboardHeatingType", "Baseboard Heating Type"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingAvailabilityScheduleName, "BaseboardHeatingAvailabilityScheduleName", "Baseboard Heating Availability Schedule Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingCapacity, "BaseboardHeatingCapacity", "Baseboard Heating Capacity"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, "ZoneCoolingDesignSupplyAirTemperatureInputMethod", "Zone Cooling Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperature, "ZoneCoolingDesignSupplyAirTemperature", "Zone Cooling Design Supply Air Temperature"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureDifference, "ZoneCoolingDesignSupplyAirTemperatureDifference", "Zone Cooling Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, "ZoneHeatingDesignSupplyAirTemperatureInputMethod", "Zone Heating Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperature, "ZoneHeatingDesignSupplyAirTemperature", "Zone Heating Design Supply Air Temperature"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureDifference, "ZoneHeatingDesignSupplyAirTemperatureDifference", "Zone Heating Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZonePIUFanScheduleName, "ZonePIUFanScheduleName", "Zone PIU Fan Schedule Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Zone_VAV_FanPoweredFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Zone_VAV_FanPoweredFields> OptionalHVACTemplate_Zone_VAV_FanPoweredFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_FANPOWERED_FIELDENUMS_HXX
