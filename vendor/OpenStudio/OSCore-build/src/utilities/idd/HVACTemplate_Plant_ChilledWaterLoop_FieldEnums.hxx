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

#ifndef UTILITIES_IDD_HVACTEMPLATE_PLANT_CHILLEDWATERLOOP_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_PLANT_CHILLEDWATERLOOP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Plant_ChilledWaterLoopFields
 *  \brief Enumeration of HVACTemplate:Plant:ChilledWaterLoop's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Plant_ChilledWaterLoopFields, )
#else
class HVACTemplate_Plant_ChilledWaterLoopFields: public ::EnumBase<HVACTemplate_Plant_ChilledWaterLoopFields> {
 public: 
  enum domain 
  {
Name, PumpScheduleName, PumpControlType, ChillerPlantOperationSchemeType, ChillerPlantEquipmentOperationSchemesName, ChilledWaterSetpointScheduleName, ChilledWaterDesignSetpoint, ChilledWaterPumpConfiguration, PrimaryChilledWaterPumpRatedHead, SecondaryChilledWaterPumpRatedHead, CondenserPlantOperationSchemeType, CondenserEquipmentOperationSchemesName, CondenserWaterTemperatureControlType, CondenserWaterSetpointScheduleName, CondenserWaterDesignSetpoint, CondenserWaterPumpRatedHead, ChilledWaterSetpointResetType, ChilledWaterSetpointatOutdoorDryBulbLow, ChilledWaterResetOutdoorDryBulbLow, ChilledWaterSetpointatOutdoorDryBulbHigh, ChilledWaterResetOutdoorDryBulbHigh, ChilledWaterPrimaryPumpType, ChilledWaterSecondaryPumpType, CondenserWaterPumpType, ChilledWaterSupplySideBypassPipe, ChilledWaterDemandSideBypassPipe, CondenserWaterSupplySideBypassPipe, CondenserWaterDemandSideBypassPipe, FluidType, LoopDesignDeltaTemperature, MinimumOutdoorDryBulbTemperature, ChilledWaterLoadDistributionScheme, CondenserWaterLoadDistributionScheme,   };
  HVACTemplate_Plant_ChilledWaterLoopFields()
   : EnumBase<HVACTemplate_Plant_ChilledWaterLoopFields>(Name) {} 
  HVACTemplate_Plant_ChilledWaterLoopFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Plant_ChilledWaterLoopFields>(t_name) {} 
  HVACTemplate_Plant_ChilledWaterLoopFields(int t_value) 
   : EnumBase<HVACTemplate_Plant_ChilledWaterLoopFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Plant_ChilledWaterLoopFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Plant_ChilledWaterLoopFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Plant_ChilledWaterLoopFields>;
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
{ HVACTemplate_Plant_ChilledWaterLoopFields::Name, "Name", "Name"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::PumpScheduleName, "PumpScheduleName", "Pump Schedule Name"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChillerPlantOperationSchemeType, "ChillerPlantOperationSchemeType", "Chiller Plant Operation Scheme Type"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChillerPlantEquipmentOperationSchemesName, "ChillerPlantEquipmentOperationSchemesName", "Chiller Plant Equipment Operation Schemes Name"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointScheduleName, "ChilledWaterSetpointScheduleName", "Chilled Water Setpoint Schedule Name"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterDesignSetpoint, "ChilledWaterDesignSetpoint", "Chilled Water Design Setpoint"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPumpConfiguration, "ChilledWaterPumpConfiguration", "Chilled Water Pump Configuration"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::PrimaryChilledWaterPumpRatedHead, "PrimaryChilledWaterPumpRatedHead", "Primary Chilled Water Pump Rated Head"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::SecondaryChilledWaterPumpRatedHead, "SecondaryChilledWaterPumpRatedHead", "Secondary Chilled Water Pump Rated Head"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::CondenserPlantOperationSchemeType, "CondenserPlantOperationSchemeType", "Condenser Plant Operation Scheme Type"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::CondenserEquipmentOperationSchemesName, "CondenserEquipmentOperationSchemesName", "Condenser Equipment Operation Schemes Name"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterTemperatureControlType, "CondenserWaterTemperatureControlType", "Condenser Water Temperature Control Type"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterSetpointScheduleName, "CondenserWaterSetpointScheduleName", "Condenser Water Setpoint Schedule Name"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterDesignSetpoint, "CondenserWaterDesignSetpoint", "Condenser Water Design Setpoint"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpRatedHead, "CondenserWaterPumpRatedHead", "Condenser Water Pump Rated Head"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointResetType, "ChilledWaterSetpointResetType", "Chilled Water Setpoint Reset Type"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointatOutdoorDryBulbLow, "ChilledWaterSetpointatOutdoorDryBulbLow", "Chilled Water Setpoint at Outdoor Dry-Bulb Low"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterResetOutdoorDryBulbLow, "ChilledWaterResetOutdoorDryBulbLow", "Chilled Water Reset Outdoor Dry-Bulb Low"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSetpointatOutdoorDryBulbHigh, "ChilledWaterSetpointatOutdoorDryBulbHigh", "Chilled Water Setpoint at Outdoor Dry-Bulb High"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterResetOutdoorDryBulbHigh, "ChilledWaterResetOutdoorDryBulbHigh", "Chilled Water Reset Outdoor Dry-Bulb High"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterPrimaryPumpType, "ChilledWaterPrimaryPumpType", "Chilled Water Primary Pump Type"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSecondaryPumpType, "ChilledWaterSecondaryPumpType", "Chilled Water Secondary Pump Type"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterPumpType, "CondenserWaterPumpType", "Condenser Water Pump Type"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterSupplySideBypassPipe, "ChilledWaterSupplySideBypassPipe", "Chilled Water Supply Side Bypass Pipe"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterDemandSideBypassPipe, "ChilledWaterDemandSideBypassPipe", "Chilled Water Demand Side Bypass Pipe"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterSupplySideBypassPipe, "CondenserWaterSupplySideBypassPipe", "Condenser Water Supply Side Bypass Pipe"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterDemandSideBypassPipe, "CondenserWaterDemandSideBypassPipe", "Condenser Water Demand Side Bypass Pipe"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::FluidType, "FluidType", "Fluid Type"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::LoopDesignDeltaTemperature, "LoopDesignDeltaTemperature", "Loop Design Delta Temperature"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::MinimumOutdoorDryBulbTemperature, "MinimumOutdoorDryBulbTemperature", "Minimum Outdoor Dry Bulb Temperature"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::ChilledWaterLoadDistributionScheme, "ChilledWaterLoadDistributionScheme", "Chilled Water Load Distribution Scheme"},
{ HVACTemplate_Plant_ChilledWaterLoopFields::CondenserWaterLoadDistributionScheme, "CondenserWaterLoadDistributionScheme", "Condenser Water Load Distribution Scheme"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Plant_ChilledWaterLoopFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Plant_ChilledWaterLoopFields> OptionalHVACTemplate_Plant_ChilledWaterLoopFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_PLANT_CHILLEDWATERLOOP_FIELDENUMS_HXX
