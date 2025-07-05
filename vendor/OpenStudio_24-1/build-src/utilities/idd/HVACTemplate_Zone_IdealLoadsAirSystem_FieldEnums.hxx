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

#ifndef UTILITIES_IDD_HVACTEMPLATE_ZONE_IDEALLOADSAIRSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_ZONE_IDEALLOADSAIRSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Zone_IdealLoadsAirSystemFields
 *  \brief Enumeration of HVACTemplate:Zone:IdealLoadsAirSystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Zone_IdealLoadsAirSystemFields, )
#else
class HVACTemplate_Zone_IdealLoadsAirSystemFields: public ::EnumBase<HVACTemplate_Zone_IdealLoadsAirSystemFields> {
 public: 
  enum domain 
  {
ZoneName, TemplateThermostatName, SystemAvailabilityScheduleName, MaximumHeatingSupplyAirTemperature, MinimumCoolingSupplyAirTemperature, MaximumHeatingSupplyAirHumidityRatio, MinimumCoolingSupplyAirHumidityRatio, HeatingLimit, MaximumHeatingAirFlowRate, MaximumSensibleHeatingCapacity, CoolingLimit, MaximumCoolingAirFlowRate, MaximumTotalCoolingCapacity, HeatingAvailabilityScheduleName, CoolingAvailabilityScheduleName, DehumidificationControlType, CoolingSensibleHeatRatio, DehumidificationSetpoint, HumidificationControlType, HumidificationSetpoint, OutdoorAirMethod, OutdoorAirFlowRateperPerson, OutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZone, DesignSpecificationOutdoorAirObjectName, DemandControlledVentilationType, OutdoorAirEconomizerType, HeatRecoveryType, SensibleHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness,   };
  HVACTemplate_Zone_IdealLoadsAirSystemFields()
   : EnumBase<HVACTemplate_Zone_IdealLoadsAirSystemFields>(ZoneName) {} 
  HVACTemplate_Zone_IdealLoadsAirSystemFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Zone_IdealLoadsAirSystemFields>(t_name) {} 
  HVACTemplate_Zone_IdealLoadsAirSystemFields(int t_value) 
   : EnumBase<HVACTemplate_Zone_IdealLoadsAirSystemFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Zone_IdealLoadsAirSystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Zone_IdealLoadsAirSystemFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Zone_IdealLoadsAirSystemFields>;
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
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::ZoneName, "ZoneName", "Zone Name"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::TemplateThermostatName, "TemplateThermostatName", "Template Thermostat Name"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::SystemAvailabilityScheduleName, "SystemAvailabilityScheduleName", "System Availability Schedule Name"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirTemperature, "MaximumHeatingSupplyAirTemperature", "Maximum Heating Supply Air Temperature"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirTemperature, "MinimumCoolingSupplyAirTemperature", "Minimum Cooling Supply Air Temperature"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirHumidityRatio, "MaximumHeatingSupplyAirHumidityRatio", "Maximum Heating Supply Air Humidity Ratio"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirHumidityRatio, "MinimumCoolingSupplyAirHumidityRatio", "Minimum Cooling Supply Air Humidity Ratio"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::HeatingLimit, "HeatingLimit", "Heating Limit"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::MaximumHeatingAirFlowRate, "MaximumHeatingAirFlowRate", "Maximum Heating Air Flow Rate"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::MaximumSensibleHeatingCapacity, "MaximumSensibleHeatingCapacity", "Maximum Sensible Heating Capacity"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::CoolingLimit, "CoolingLimit", "Cooling Limit"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::MaximumCoolingAirFlowRate, "MaximumCoolingAirFlowRate", "Maximum Cooling Air Flow Rate"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::MaximumTotalCoolingCapacity, "MaximumTotalCoolingCapacity", "Maximum Total Cooling Capacity"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::HeatingAvailabilityScheduleName, "HeatingAvailabilityScheduleName", "Heating Availability Schedule Name"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::CoolingAvailabilityScheduleName, "CoolingAvailabilityScheduleName", "Cooling Availability Schedule Name"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::CoolingSensibleHeatRatio, "CoolingSensibleHeatRatio", "Cooling Sensible Heat Ratio"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::DehumidificationSetpoint, "DehumidificationSetpoint", "Dehumidification Setpoint"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::HumidificationControlType, "HumidificationControlType", "Humidification Control Type"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::HumidificationSetpoint, "HumidificationSetpoint", "Humidification Setpoint"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::OutdoorAirMethod, "OutdoorAirMethod", "Outdoor Air Method"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::OutdoorAirFlowRateperPerson, "OutdoorAirFlowRateperPerson", "Outdoor Air Flow Rate per Person"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::OutdoorAirFlowRateperZoneFloorArea, "OutdoorAirFlowRateperZoneFloorArea", "Outdoor Air Flow Rate per Zone Floor Area"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::OutdoorAirFlowRateperZone, "OutdoorAirFlowRateperZone", "Outdoor Air Flow Rate per Zone"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::DemandControlledVentilationType, "DemandControlledVentilationType", "Demand Controlled Ventilation Type"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::OutdoorAirEconomizerType, "OutdoorAirEconomizerType", "Outdoor Air Economizer Type"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::HeatRecoveryType, "HeatRecoveryType", "Heat Recovery Type"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::SensibleHeatRecoveryEffectiveness, "SensibleHeatRecoveryEffectiveness", "Sensible Heat Recovery Effectiveness"},
{ HVACTemplate_Zone_IdealLoadsAirSystemFields::LatentHeatRecoveryEffectiveness, "LatentHeatRecoveryEffectiveness", "Latent Heat Recovery Effectiveness"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Zone_IdealLoadsAirSystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Zone_IdealLoadsAirSystemFields> OptionalHVACTemplate_Zone_IdealLoadsAirSystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_ZONE_IDEALLOADSAIRSYSTEM_FIELDENUMS_HXX
