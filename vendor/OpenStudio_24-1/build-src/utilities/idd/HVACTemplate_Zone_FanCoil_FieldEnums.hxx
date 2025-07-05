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

#ifndef UTILITIES_IDD_HVACTEMPLATE_ZONE_FANCOIL_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_ZONE_FANCOIL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Zone_FanCoilFields
 *  \brief Enumeration of HVACTemplate:Zone:FanCoil's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Zone_FanCoilFields, )
#else
class HVACTemplate_Zone_FanCoilFields: public ::EnumBase<HVACTemplate_Zone_FanCoilFields> {
 public: 
  enum domain 
  {
ZoneName, TemplateThermostatName, SupplyAirMaximumFlowRate, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, OutdoorAirMethod, OutdoorAirFlowRateperPerson, OutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZone, SystemAvailabilityScheduleName, SupplyFanTotalEfficiency, SupplyFanDeltaPressure, SupplyFanMotorEfficiency, SupplyFanMotorinAirStreamFraction, CoolingCoilType, CoolingCoilAvailabilityScheduleName, CoolingCoilDesignSetpoint, HeatingCoilType, HeatingCoilAvailabilityScheduleName, HeatingCoilDesignSetpoint, DedicatedOutdoorAirSystemName, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperatureDifference, DesignSpecificationOutdoorAirObjectName, DesignSpecificationZoneAirDistributionObjectName, CapacityControlMethod, LowSpeedSupplyAirFlowRatio, MediumSpeedSupplyAirFlowRatio, OutdoorAirScheduleName, BaseboardHeatingType, BaseboardHeatingAvailabilityScheduleName, BaseboardHeatingCapacity,   };
  HVACTemplate_Zone_FanCoilFields()
   : EnumBase<HVACTemplate_Zone_FanCoilFields>(ZoneName) {} 
  HVACTemplate_Zone_FanCoilFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Zone_FanCoilFields>(t_name) {} 
  HVACTemplate_Zone_FanCoilFields(int t_value) 
   : EnumBase<HVACTemplate_Zone_FanCoilFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Zone_FanCoilFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Zone_FanCoilFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Zone_FanCoilFields>;
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
{ HVACTemplate_Zone_FanCoilFields::ZoneName, "ZoneName", "Zone Name"},
{ HVACTemplate_Zone_FanCoilFields::TemplateThermostatName, "TemplateThermostatName", "Template Thermostat Name"},
{ HVACTemplate_Zone_FanCoilFields::SupplyAirMaximumFlowRate, "SupplyAirMaximumFlowRate", "Supply Air Maximum Flow Rate"},
{ HVACTemplate_Zone_FanCoilFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ HVACTemplate_Zone_FanCoilFields::ZoneCoolingSizingFactor, "ZoneCoolingSizingFactor", "Zone Cooling Sizing Factor"},
{ HVACTemplate_Zone_FanCoilFields::OutdoorAirMethod, "OutdoorAirMethod", "Outdoor Air Method"},
{ HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperPerson, "OutdoorAirFlowRateperPerson", "Outdoor Air Flow Rate per Person"},
{ HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperZoneFloorArea, "OutdoorAirFlowRateperZoneFloorArea", "Outdoor Air Flow Rate per Zone Floor Area"},
{ HVACTemplate_Zone_FanCoilFields::OutdoorAirFlowRateperZone, "OutdoorAirFlowRateperZone", "Outdoor Air Flow Rate per Zone"},
{ HVACTemplate_Zone_FanCoilFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_Zone_FanCoilFields::SupplyFanTotalEfficiency, "SupplyFanTotalEfficiency", "Supply Fan Total Efficiency"},
{ HVACTemplate_Zone_FanCoilFields::SupplyFanDeltaPressure, "SupplyFanDeltaPressure", "Supply Fan Delta Pressure"},
{ HVACTemplate_Zone_FanCoilFields::SupplyFanMotorEfficiency, "SupplyFanMotorEfficiency", "Supply Fan Motor Efficiency"},
{ HVACTemplate_Zone_FanCoilFields::SupplyFanMotorinAirStreamFraction, "SupplyFanMotorinAirStreamFraction", "Supply Fan Motor in Air Stream Fraction"},
{ HVACTemplate_Zone_FanCoilFields::CoolingCoilType, "CoolingCoilType", "Cooling Coil Type"},
{ HVACTemplate_Zone_FanCoilFields::CoolingCoilAvailabilityScheduleName, "CoolingCoilAvailabilityScheduleName", "Cooling Coil Availability Schedule Name"},
{ HVACTemplate_Zone_FanCoilFields::CoolingCoilDesignSetpoint, "CoolingCoilDesignSetpoint", "Cooling Coil Design Setpoint"},
{ HVACTemplate_Zone_FanCoilFields::HeatingCoilType, "HeatingCoilType", "Heating Coil Type"},
{ HVACTemplate_Zone_FanCoilFields::HeatingCoilAvailabilityScheduleName, "HeatingCoilAvailabilityScheduleName", "Heating Coil Availability Schedule Name"},
{ HVACTemplate_Zone_FanCoilFields::HeatingCoilDesignSetpoint, "HeatingCoilDesignSetpoint", "Heating Coil Design Setpoint"},
{ HVACTemplate_Zone_FanCoilFields::DedicatedOutdoorAirSystemName, "DedicatedOutdoorAirSystemName", "Dedicated Outdoor Air System Name"},
{ HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, "ZoneCoolingDesignSupplyAirTemperatureInputMethod", "Zone Cooling Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_FanCoilFields::ZoneCoolingDesignSupplyAirTemperatureDifference, "ZoneCoolingDesignSupplyAirTemperatureDifference", "Zone Cooling Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, "ZoneHeatingDesignSupplyAirTemperatureInputMethod", "Zone Heating Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_FanCoilFields::ZoneHeatingDesignSupplyAirTemperatureDifference, "ZoneHeatingDesignSupplyAirTemperatureDifference", "Zone Heating Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_FanCoilFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ HVACTemplate_Zone_FanCoilFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
{ HVACTemplate_Zone_FanCoilFields::CapacityControlMethod, "CapacityControlMethod", "Capacity Control Method"},
{ HVACTemplate_Zone_FanCoilFields::LowSpeedSupplyAirFlowRatio, "LowSpeedSupplyAirFlowRatio", "Low Speed Supply Air Flow Ratio"},
{ HVACTemplate_Zone_FanCoilFields::MediumSpeedSupplyAirFlowRatio, "MediumSpeedSupplyAirFlowRatio", "Medium Speed Supply Air Flow Ratio"},
{ HVACTemplate_Zone_FanCoilFields::OutdoorAirScheduleName, "OutdoorAirScheduleName", "Outdoor Air Schedule Name"},
{ HVACTemplate_Zone_FanCoilFields::BaseboardHeatingType, "BaseboardHeatingType", "Baseboard Heating Type"},
{ HVACTemplate_Zone_FanCoilFields::BaseboardHeatingAvailabilityScheduleName, "BaseboardHeatingAvailabilityScheduleName", "Baseboard Heating Availability Schedule Name"},
{ HVACTemplate_Zone_FanCoilFields::BaseboardHeatingCapacity, "BaseboardHeatingCapacity", "Baseboard Heating Capacity"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Zone_FanCoilFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Zone_FanCoilFields> OptionalHVACTemplate_Zone_FanCoilFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_ZONE_FANCOIL_FIELDENUMS_HXX
