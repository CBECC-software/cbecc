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

#ifndef UTILITIES_IDD_HVACTEMPLATE_PLANT_MIXEDWATERLOOP_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_PLANT_MIXEDWATERLOOP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Plant_MixedWaterLoopFields
 *  \brief Enumeration of HVACTemplate:Plant:MixedWaterLoop's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Plant_MixedWaterLoopFields, )
#else
class HVACTemplate_Plant_MixedWaterLoopFields: public ::EnumBase<HVACTemplate_Plant_MixedWaterLoopFields> {
 public: 
  enum domain 
  {
Name, PumpScheduleName, PumpControlType, OperationSchemeType, EquipmentOperationSchemesName, HighTemperatureSetpointScheduleName, HighTemperatureDesignSetpoint, LowTemperatureSetpointScheduleName, LowTemperatureDesignSetpoint, WaterPumpConfiguration, WaterPumpRatedHead, WaterPumpType, SupplySideBypassPipe, DemandSideBypassPipe, FluidType, LoopDesignDeltaTemperature, LoadDistributionScheme,   };
  HVACTemplate_Plant_MixedWaterLoopFields()
   : EnumBase<HVACTemplate_Plant_MixedWaterLoopFields>(Name) {} 
  HVACTemplate_Plant_MixedWaterLoopFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Plant_MixedWaterLoopFields>(t_name) {} 
  HVACTemplate_Plant_MixedWaterLoopFields(int t_value) 
   : EnumBase<HVACTemplate_Plant_MixedWaterLoopFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Plant_MixedWaterLoopFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Plant_MixedWaterLoopFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Plant_MixedWaterLoopFields>;
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
{ HVACTemplate_Plant_MixedWaterLoopFields::Name, "Name", "Name"},
{ HVACTemplate_Plant_MixedWaterLoopFields::PumpScheduleName, "PumpScheduleName", "Pump Schedule Name"},
{ HVACTemplate_Plant_MixedWaterLoopFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ HVACTemplate_Plant_MixedWaterLoopFields::OperationSchemeType, "OperationSchemeType", "Operation Scheme Type"},
{ HVACTemplate_Plant_MixedWaterLoopFields::EquipmentOperationSchemesName, "EquipmentOperationSchemesName", "Equipment Operation Schemes Name"},
{ HVACTemplate_Plant_MixedWaterLoopFields::HighTemperatureSetpointScheduleName, "HighTemperatureSetpointScheduleName", "High Temperature Setpoint Schedule Name"},
{ HVACTemplate_Plant_MixedWaterLoopFields::HighTemperatureDesignSetpoint, "HighTemperatureDesignSetpoint", "High Temperature Design Setpoint"},
{ HVACTemplate_Plant_MixedWaterLoopFields::LowTemperatureSetpointScheduleName, "LowTemperatureSetpointScheduleName", "Low Temperature Setpoint Schedule Name"},
{ HVACTemplate_Plant_MixedWaterLoopFields::LowTemperatureDesignSetpoint, "LowTemperatureDesignSetpoint", "Low Temperature Design Setpoint"},
{ HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpConfiguration, "WaterPumpConfiguration", "Water Pump Configuration"},
{ HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpRatedHead, "WaterPumpRatedHead", "Water Pump Rated Head"},
{ HVACTemplate_Plant_MixedWaterLoopFields::WaterPumpType, "WaterPumpType", "Water Pump Type"},
{ HVACTemplate_Plant_MixedWaterLoopFields::SupplySideBypassPipe, "SupplySideBypassPipe", "Supply Side Bypass Pipe"},
{ HVACTemplate_Plant_MixedWaterLoopFields::DemandSideBypassPipe, "DemandSideBypassPipe", "Demand Side Bypass Pipe"},
{ HVACTemplate_Plant_MixedWaterLoopFields::FluidType, "FluidType", "Fluid Type"},
{ HVACTemplate_Plant_MixedWaterLoopFields::LoopDesignDeltaTemperature, "LoopDesignDeltaTemperature", "Loop Design Delta Temperature"},
{ HVACTemplate_Plant_MixedWaterLoopFields::LoadDistributionScheme, "LoadDistributionScheme", "Load Distribution Scheme"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Plant_MixedWaterLoopFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Plant_MixedWaterLoopFields> OptionalHVACTemplate_Plant_MixedWaterLoopFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_PLANT_MIXEDWATERLOOP_FIELDENUMS_HXX
