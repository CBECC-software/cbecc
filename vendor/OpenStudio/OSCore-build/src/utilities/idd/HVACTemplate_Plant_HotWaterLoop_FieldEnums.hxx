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

#ifndef UTILITIES_IDD_HVACTEMPLATE_PLANT_HOTWATERLOOP_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_PLANT_HOTWATERLOOP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Plant_HotWaterLoopFields
 *  \brief Enumeration of HVACTemplate:Plant:HotWaterLoop's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Plant_HotWaterLoopFields, )
#else
class HVACTemplate_Plant_HotWaterLoopFields: public ::EnumBase<HVACTemplate_Plant_HotWaterLoopFields> {
 public: 
  enum domain 
  {
Name, PumpScheduleName, PumpControlType, HotWaterPlantOperationSchemeType, HotWaterPlantEquipmentOperationSchemesName, HotWaterSetpointScheduleName, HotWaterDesignSetpoint, HotWaterPumpConfiguration, HotWaterPumpRatedHead, HotWaterSetpointResetType, HotWaterSetpointatOutdoorDryBulbLow, HotWaterResetOutdoorDryBulbLow, HotWaterSetpointatOutdoorDryBulbHigh, HotWaterResetOutdoorDryBulbHigh, HotWaterPumpType, SupplySideBypassPipe, DemandSideBypassPipe, FluidType, LoopDesignDeltaTemperature, MaximumOutdoorDryBulbTemperature, LoadDistributionScheme,   };
  HVACTemplate_Plant_HotWaterLoopFields()
   : EnumBase<HVACTemplate_Plant_HotWaterLoopFields>(Name) {} 
  HVACTemplate_Plant_HotWaterLoopFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Plant_HotWaterLoopFields>(t_name) {} 
  HVACTemplate_Plant_HotWaterLoopFields(int t_value) 
   : EnumBase<HVACTemplate_Plant_HotWaterLoopFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Plant_HotWaterLoopFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Plant_HotWaterLoopFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Plant_HotWaterLoopFields>;
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
{ HVACTemplate_Plant_HotWaterLoopFields::Name, "Name", "Name"},
{ HVACTemplate_Plant_HotWaterLoopFields::PumpScheduleName, "PumpScheduleName", "Pump Schedule Name"},
{ HVACTemplate_Plant_HotWaterLoopFields::PumpControlType, "PumpControlType", "Pump Control Type"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterPlantOperationSchemeType, "HotWaterPlantOperationSchemeType", "Hot Water Plant Operation Scheme Type"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterPlantEquipmentOperationSchemesName, "HotWaterPlantEquipmentOperationSchemesName", "Hot Water Plant Equipment Operation Schemes Name"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointScheduleName, "HotWaterSetpointScheduleName", "Hot Water Setpoint Schedule Name"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterDesignSetpoint, "HotWaterDesignSetpoint", "Hot Water Design Setpoint"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpConfiguration, "HotWaterPumpConfiguration", "Hot Water Pump Configuration"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpRatedHead, "HotWaterPumpRatedHead", "Hot Water Pump Rated Head"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointResetType, "HotWaterSetpointResetType", "Hot Water Setpoint Reset Type"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointatOutdoorDryBulbLow, "HotWaterSetpointatOutdoorDryBulbLow", "Hot Water Setpoint at Outdoor Dry-Bulb Low"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterResetOutdoorDryBulbLow, "HotWaterResetOutdoorDryBulbLow", "Hot Water Reset Outdoor Dry-Bulb Low"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterSetpointatOutdoorDryBulbHigh, "HotWaterSetpointatOutdoorDryBulbHigh", "Hot Water Setpoint at Outdoor Dry-Bulb High"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterResetOutdoorDryBulbHigh, "HotWaterResetOutdoorDryBulbHigh", "Hot Water Reset Outdoor Dry-Bulb High"},
{ HVACTemplate_Plant_HotWaterLoopFields::HotWaterPumpType, "HotWaterPumpType", "Hot Water Pump Type"},
{ HVACTemplate_Plant_HotWaterLoopFields::SupplySideBypassPipe, "SupplySideBypassPipe", "Supply Side Bypass Pipe"},
{ HVACTemplate_Plant_HotWaterLoopFields::DemandSideBypassPipe, "DemandSideBypassPipe", "Demand Side Bypass Pipe"},
{ HVACTemplate_Plant_HotWaterLoopFields::FluidType, "FluidType", "Fluid Type"},
{ HVACTemplate_Plant_HotWaterLoopFields::LoopDesignDeltaTemperature, "LoopDesignDeltaTemperature", "Loop Design Delta Temperature"},
{ HVACTemplate_Plant_HotWaterLoopFields::MaximumOutdoorDryBulbTemperature, "MaximumOutdoorDryBulbTemperature", "Maximum Outdoor Dry Bulb Temperature"},
{ HVACTemplate_Plant_HotWaterLoopFields::LoadDistributionScheme, "LoadDistributionScheme", "Load Distribution Scheme"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Plant_HotWaterLoopFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Plant_HotWaterLoopFields> OptionalHVACTemplate_Plant_HotWaterLoopFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_PLANT_HOTWATERLOOP_FIELDENUMS_HXX
