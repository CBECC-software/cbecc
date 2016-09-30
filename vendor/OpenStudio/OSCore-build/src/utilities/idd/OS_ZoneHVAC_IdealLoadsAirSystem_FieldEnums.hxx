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

#ifndef UTILITIES_IDD_OS_ZONEHVAC_IDEALLOADSAIRSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEHVAC_IDEALLOADSAIRSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneHVAC_IdealLoadsAirSystemFields
 *  \brief Enumeration of OS:ZoneHVAC:IdealLoadsAirSystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneHVAC_IdealLoadsAirSystemFields, )
#else
class OS_ZoneHVAC_IdealLoadsAirSystemFields: public ::EnumBase<OS_ZoneHVAC_IdealLoadsAirSystemFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, ZoneSupplyAirNodeName, ZoneExhaustAirNodeName, MaximumHeatingSupplyAirTemperature, MinimumCoolingSupplyAirTemperature, MaximumHeatingSupplyAirHumidityRatio, MinimumCoolingSupplyAirHumidityRatio, HeatingLimit, MaximumHeatingAirFlowRate, MaximumSensibleHeatingCapacity, CoolingLimit, MaximumCoolingAirFlowRate, MaximumTotalCoolingCapacity, HeatingAvailabilityScheduleName, CoolingAvailabilityScheduleName, DehumidificationControlType, CoolingSensibleHeatRatio, HumidificationControlType, DesignSpecificationOutdoorAirObjectName, DemandControlledVentilationType, OutdoorAirEconomizerType, HeatRecoveryType, SensibleHeatRecoveryEffectiveness, LatentHeatRecoveryEffectiveness,   };
  OS_ZoneHVAC_IdealLoadsAirSystemFields()
   : EnumBase<OS_ZoneHVAC_IdealLoadsAirSystemFields>(Handle) {} 
  OS_ZoneHVAC_IdealLoadsAirSystemFields(const std::string &t_name) 
   : EnumBase<OS_ZoneHVAC_IdealLoadsAirSystemFields>(t_name) {} 
  OS_ZoneHVAC_IdealLoadsAirSystemFields(int t_value) 
   : EnumBase<OS_ZoneHVAC_IdealLoadsAirSystemFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneHVAC_IdealLoadsAirSystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneHVAC_IdealLoadsAirSystemFields>::value()); }
   private:
    friend class EnumBase<OS_ZoneHVAC_IdealLoadsAirSystemFields>;
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
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::Handle, "Handle", "Handle"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::Name, "Name", "Name"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::ZoneSupplyAirNodeName, "ZoneSupplyAirNodeName", "Zone Supply Air Node Name"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::ZoneExhaustAirNodeName, "ZoneExhaustAirNodeName", "Zone Exhaust Air Node Name"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirTemperature, "MaximumHeatingSupplyAirTemperature", "Maximum Heating Supply Air Temperature"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirTemperature, "MinimumCoolingSupplyAirTemperature", "Minimum Cooling Supply Air Temperature"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingSupplyAirHumidityRatio, "MaximumHeatingSupplyAirHumidityRatio", "Maximum Heating Supply Air Humidity Ratio"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::MinimumCoolingSupplyAirHumidityRatio, "MinimumCoolingSupplyAirHumidityRatio", "Minimum Cooling Supply Air Humidity Ratio"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::HeatingLimit, "HeatingLimit", "Heating Limit"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::MaximumHeatingAirFlowRate, "MaximumHeatingAirFlowRate", "Maximum Heating Air Flow Rate"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::MaximumSensibleHeatingCapacity, "MaximumSensibleHeatingCapacity", "Maximum Sensible Heating Capacity"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::CoolingLimit, "CoolingLimit", "Cooling Limit"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::MaximumCoolingAirFlowRate, "MaximumCoolingAirFlowRate", "Maximum Cooling Air Flow Rate"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::MaximumTotalCoolingCapacity, "MaximumTotalCoolingCapacity", "Maximum Total Cooling Capacity"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::HeatingAvailabilityScheduleName, "HeatingAvailabilityScheduleName", "Heating Availability Schedule Name"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::CoolingAvailabilityScheduleName, "CoolingAvailabilityScheduleName", "Cooling Availability Schedule Name"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::CoolingSensibleHeatRatio, "CoolingSensibleHeatRatio", "Cooling Sensible Heat Ratio"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::HumidificationControlType, "HumidificationControlType", "Humidification Control Type"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::DemandControlledVentilationType, "DemandControlledVentilationType", "Demand Controlled Ventilation Type"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::OutdoorAirEconomizerType, "OutdoorAirEconomizerType", "Outdoor Air Economizer Type"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::HeatRecoveryType, "HeatRecoveryType", "Heat Recovery Type"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::SensibleHeatRecoveryEffectiveness, "SensibleHeatRecoveryEffectiveness", "Sensible Heat Recovery Effectiveness"},
{ OS_ZoneHVAC_IdealLoadsAirSystemFields::LatentHeatRecoveryEffectiveness, "LatentHeatRecoveryEffectiveness", "Latent Heat Recovery Effectiveness"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneHVAC_IdealLoadsAirSystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneHVAC_IdealLoadsAirSystemFields> OptionalOS_ZoneHVAC_IdealLoadsAirSystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEHVAC_IDEALLOADSAIRSYSTEM_FIELDENUMS_HXX
