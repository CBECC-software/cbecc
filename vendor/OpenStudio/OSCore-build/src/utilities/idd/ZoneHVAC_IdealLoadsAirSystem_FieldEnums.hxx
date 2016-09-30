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
Name, AvailabilityScheduleName, ZoneSupplyAirNodeName, ZoneExhaustAirNodeName, MaximumHeatingSupplyAirTemperature, MinimumCoolingSupplyAirTemperature, MaximumHeatingSupplyAirHumidityRatio, MinimumCoolingSupplyAirHumidityRatio, HeatingLimit, MaximumHeatingAirFlowRate, MaximumSensibleHeatingCapacity, CoolingLimit, MaximumCoolingAirFlowRate, MaximumTotalCoolingCapacity, HeatingAvailabilityScheduleName, CoolingAvailabilityScheduleName, DehumidificationControlType, CoolingSensibleHeatRatio, HumidificationControlType, DesignSpecificationOutdoorAirObjectName, OutdoorAirInletNodeName, DemandControlledVentilationType, OutdoorAirEconomizerType, HeatRecoveryType, SensibleHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness, DesignSpecificationZoneHVACSizingObjectName,   };
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
