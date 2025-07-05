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

#ifndef UTILITIES_IDD_ZONEHVAC_IDEALLOADSAIRSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_IDEALLOADSAIRSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_IdealLoadsAirSystemFields
 *  \brief Enumeration of ZoneHVAC:IdealLoadsAirSystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_IdealLoadsAirSystemFields, )
#else
class ZoneHVAC_IdealLoadsAirSystemFields: public ::EnumBase<ZoneHVAC_IdealLoadsAirSystemFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneSupplyAirNodeName, ZoneExhaustAirNodeName, SystemInletAirNodeName, MaximumHeatingSupplyAirTemperature, MinimumCoolingSupplyAirTemperature, MaximumHeatingSupplyAirHumidityRatio, MinimumCoolingSupplyAirHumidityRatio, HeatingLimit, MaximumHeatingAirFlowRate, MaximumSensibleHeatingCapacity, CoolingLimit, MaximumCoolingAirFlowRate, MaximumTotalCoolingCapacity, HeatingAvailabilityScheduleName, CoolingAvailabilityScheduleName, DehumidificationControlType, CoolingSensibleHeatRatio, HumidificationControlType, DesignSpecificationOutdoorAirObjectName, OutdoorAirInletNodeName, DemandControlledVentilationType, OutdoorAirEconomizerType, HeatRecoveryType, SensibleHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness, DesignSpecificationZoneHVACSizingObjectName,   };
  ZoneHVAC_IdealLoadsAirSystemFields()
   : EnumBase<ZoneHVAC_IdealLoadsAirSystemFields>(Name) {} 
  ZoneHVAC_IdealLoadsAirSystemFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_IdealLoadsAirSystemFields>(t_name) {} 
  ZoneHVAC_IdealLoadsAirSystemFields(int t_value) 
   : EnumBase<ZoneHVAC_IdealLoadsAirSystemFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_IdealLoadsAirSystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_IdealLoadsAirSystemFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_IdealLoadsAirSystemFields>;
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
{ ZoneHVAC_IdealLoadsAirSystemFields::Name, "Name", "Name"},
{ ZoneHVAC_IdealLoadsAirSystemFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_IdealLoadsAirSystemFields::ZoneSupplyAirNodeName, "ZoneSupplyAirNodeName", "Zone Supply Air Node Name"},
{ ZoneHVAC_IdealLoadsAirSystemFields::ZoneExhaustAirNodeName, "ZoneExhaustAirNodeName", "Zone Exhaust Air Node Name"},
{ ZoneHVAC_IdealLoadsAirSystemFields::SystemInletAirNodeName, "SystemInletAirNodeName", "System Inlet Air Node Name"},
{ ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirTemperature, "MaximumHeatingSupplyAirTemperature", "Maximum Heating Supply Air Temperature"},
{ ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirTemperature, "MinimumCoolingSupplyAirTemperature", "Minimum Cooling Supply Air Temperature"},
{ ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirHumidityRatio, "MaximumHeatingSupplyAirHumidityRatio", "Maximum Heating Supply Air Humidity Ratio"},
{ ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirHumidityRatio, "MinimumCoolingSupplyAirHumidityRatio", "Minimum Cooling Supply Air Humidity Ratio"},
{ ZoneHVAC_IdealLoadsAirSystemFields::HeatingLimit, "HeatingLimit", "Heating Limit"},
{ ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingAirFlowRate, "MaximumHeatingAirFlowRate", "Maximum Heating Air Flow Rate"},
{ ZoneHVAC_IdealLoadsAirSystemFields::MaximumSensibleHeatingCapacity, "MaximumSensibleHeatingCapacity", "Maximum Sensible Heating Capacity"},
{ ZoneHVAC_IdealLoadsAirSystemFields::CoolingLimit, "CoolingLimit", "Cooling Limit"},
{ ZoneHVAC_IdealLoadsAirSystemFields::MaximumCoolingAirFlowRate, "MaximumCoolingAirFlowRate", "Maximum Cooling Air Flow Rate"},
{ ZoneHVAC_IdealLoadsAirSystemFields::MaximumTotalCoolingCapacity, "MaximumTotalCoolingCapacity", "Maximum Total Cooling Capacity"},
{ ZoneHVAC_IdealLoadsAirSystemFields::HeatingAvailabilityScheduleName, "HeatingAvailabilityScheduleName", "Heating Availability Schedule Name"},
{ ZoneHVAC_IdealLoadsAirSystemFields::CoolingAvailabilityScheduleName, "CoolingAvailabilityScheduleName", "Cooling Availability Schedule Name"},
{ ZoneHVAC_IdealLoadsAirSystemFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ ZoneHVAC_IdealLoadsAirSystemFields::CoolingSensibleHeatRatio, "CoolingSensibleHeatRatio", "Cooling Sensible Heat Ratio"},
{ ZoneHVAC_IdealLoadsAirSystemFields::HumidificationControlType, "HumidificationControlType", "Humidification Control Type"},
{ ZoneHVAC_IdealLoadsAirSystemFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ ZoneHVAC_IdealLoadsAirSystemFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ ZoneHVAC_IdealLoadsAirSystemFields::DemandControlledVentilationType, "DemandControlledVentilationType", "Demand Controlled Ventilation Type"},
{ ZoneHVAC_IdealLoadsAirSystemFields::OutdoorAirEconomizerType, "OutdoorAirEconomizerType", "Outdoor Air Economizer Type"},
{ ZoneHVAC_IdealLoadsAirSystemFields::HeatRecoveryType, "HeatRecoveryType", "Heat Recovery Type"},
{ ZoneHVAC_IdealLoadsAirSystemFields::SensibleHeatRecoveryEffectiveness, "SensibleHeatRecoveryEffectiveness", "Sensible Heat Recovery Effectiveness"},
{ ZoneHVAC_IdealLoadsAirSystemFields::LatentHeatRecoveryEffectiveness, "LatentHeatRecoveryEffectiveness", "Latent Heat Recovery Effectiveness"},
{ ZoneHVAC_IdealLoadsAirSystemFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_IdealLoadsAirSystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_IdealLoadsAirSystemFields> OptionalZoneHVAC_IdealLoadsAirSystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_IDEALLOADSAIRSYSTEM_FIELDENUMS_HXX
