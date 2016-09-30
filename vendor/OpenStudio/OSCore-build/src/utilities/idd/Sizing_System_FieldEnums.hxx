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

#ifndef UTILITIES_IDD_SIZING_SYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_SIZING_SYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Sizing_SystemFields
 *  \brief Enumeration of Sizing:System's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Sizing_SystemFields, )
#else
class Sizing_SystemFields: public ::EnumBase<Sizing_SystemFields> {
 public: 
  enum domain 
  {
AirLoopName, TypeofLoadtoSizeOn, DesignOutdoorAirFlowRate, CentralHeatingMaximumSystemAirFlowRatio, PreheatDesignTemperature, PreheatDesignHumidityRatio, PrecoolDesignTemperature, PrecoolDesignHumidityRatio, CentralCoolingDesignSupplyAirTemperature, CentralHeatingDesignSupplyAirTemperature, TypeofZoneSumtoUse, AllOutdoorAirinCooling, AllOutdoorAirinHeating, CentralCoolingDesignSupplyAirHumidityRatio, CentralHeatingDesignSupplyAirHumidityRatio, CoolingSupplyAirFlowRateMethod, CoolingSupplyAirFlowRate, CoolingSupplyAirFlowRatePerFloorArea, CoolingFractionofAutosizedCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRatePerUnitCoolingCapacity, HeatingSupplyAirFlowRateMethod, HeatingSupplyAirFlowRate, HeatingSupplyAirFlowRatePerFloorArea, HeatingFractionofAutosizedHeatingSupplyAirFlowRate, HeatingFractionofAutosizedCoolingSupplyAirFlowRate, HeatingSupplyAirFlowRatePerUnitHeatingCapacity, SystemOutdoorAirMethod, ZoneMaximumOutdoorAirFraction, CoolingDesignCapacityMethod, CoolingDesignCapacity, CoolingDesignCapacityPerFloorArea, FractionofAutosizedCoolingDesignCapacity, HeatingDesignCapacityMethod, HeatingDesignCapacity, HeatingDesignCapacityPerFloorArea, FractionofAutosizedHeatingDesignCapacity, CentralCoolingCapacityControlMethod,   };
  Sizing_SystemFields()
   : EnumBase<Sizing_SystemFields>(AirLoopName) {} 
  Sizing_SystemFields(const std::string &t_name) 
   : EnumBase<Sizing_SystemFields>(t_name) {} 
  Sizing_SystemFields(int t_value) 
   : EnumBase<Sizing_SystemFields>(t_value) {} 
  static std::string enumName() 
  { return "Sizing_SystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Sizing_SystemFields>::value()); }
   private:
    friend class EnumBase<Sizing_SystemFields>;
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
{ Sizing_SystemFields::AirLoopName, "AirLoopName", "AirLoop Name"},
{ Sizing_SystemFields::TypeofLoadtoSizeOn, "TypeofLoadtoSizeOn", "Type of Load to Size On"},
{ Sizing_SystemFields::DesignOutdoorAirFlowRate, "DesignOutdoorAirFlowRate", "Design Outdoor Air Flow Rate"},
{ Sizing_SystemFields::CentralHeatingMaximumSystemAirFlowRatio, "CentralHeatingMaximumSystemAirFlowRatio", "Central Heating Maximum System Air Flow Ratio"},
{ Sizing_SystemFields::PreheatDesignTemperature, "PreheatDesignTemperature", "Preheat Design Temperature"},
{ Sizing_SystemFields::PreheatDesignHumidityRatio, "PreheatDesignHumidityRatio", "Preheat Design Humidity Ratio"},
{ Sizing_SystemFields::PrecoolDesignTemperature, "PrecoolDesignTemperature", "Precool Design Temperature"},
{ Sizing_SystemFields::PrecoolDesignHumidityRatio, "PrecoolDesignHumidityRatio", "Precool Design Humidity Ratio"},
{ Sizing_SystemFields::CentralCoolingDesignSupplyAirTemperature, "CentralCoolingDesignSupplyAirTemperature", "Central Cooling Design Supply Air Temperature"},
{ Sizing_SystemFields::CentralHeatingDesignSupplyAirTemperature, "CentralHeatingDesignSupplyAirTemperature", "Central Heating Design Supply Air Temperature"},
{ Sizing_SystemFields::TypeofZoneSumtoUse, "TypeofZoneSumtoUse", "Type of Zone Sum to Use"},
{ Sizing_SystemFields::AllOutdoorAirinCooling, "AllOutdoorAirinCooling", "100% Outdoor Air in Cooling"},
{ Sizing_SystemFields::AllOutdoorAirinHeating, "AllOutdoorAirinHeating", "100% Outdoor Air in Heating"},
{ Sizing_SystemFields::CentralCoolingDesignSupplyAirHumidityRatio, "CentralCoolingDesignSupplyAirHumidityRatio", "Central Cooling Design Supply Air Humidity Ratio"},
{ Sizing_SystemFields::CentralHeatingDesignSupplyAirHumidityRatio, "CentralHeatingDesignSupplyAirHumidityRatio", "Central Heating Design Supply Air Humidity Ratio"},
{ Sizing_SystemFields::CoolingSupplyAirFlowRateMethod, "CoolingSupplyAirFlowRateMethod", "Cooling Supply Air Flow Rate Method"},
{ Sizing_SystemFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ Sizing_SystemFields::CoolingSupplyAirFlowRatePerFloorArea, "CoolingSupplyAirFlowRatePerFloorArea", "Cooling Supply Air Flow Rate Per Floor Area"},
{ Sizing_SystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, "CoolingFractionofAutosizedCoolingSupplyAirFlowRate", "Cooling Fraction of Autosized Cooling Supply Air Flow Rate"},
{ Sizing_SystemFields::CoolingSupplyAirFlowRatePerUnitCoolingCapacity, "CoolingSupplyAirFlowRatePerUnitCoolingCapacity", "Cooling Supply Air Flow Rate Per Unit Cooling Capacity"},
{ Sizing_SystemFields::HeatingSupplyAirFlowRateMethod, "HeatingSupplyAirFlowRateMethod", "Heating Supply Air Flow Rate Method"},
{ Sizing_SystemFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ Sizing_SystemFields::HeatingSupplyAirFlowRatePerFloorArea, "HeatingSupplyAirFlowRatePerFloorArea", "Heating Supply Air Flow Rate Per Floor Area"},
{ Sizing_SystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate, "HeatingFractionofAutosizedHeatingSupplyAirFlowRate", "Heating Fraction of Autosized Heating Supply Air Flow Rate"},
{ Sizing_SystemFields::HeatingFractionofAutosizedCoolingSupplyAirFlowRate, "HeatingFractionofAutosizedCoolingSupplyAirFlowRate", "Heating Fraction of Autosized Cooling Supply Air Flow Rate"},
{ Sizing_SystemFields::HeatingSupplyAirFlowRatePerUnitHeatingCapacity, "HeatingSupplyAirFlowRatePerUnitHeatingCapacity", "Heating Supply Air Flow Rate Per Unit Heating Capacity"},
{ Sizing_SystemFields::SystemOutdoorAirMethod, "SystemOutdoorAirMethod", "System Outdoor Air Method"},
{ Sizing_SystemFields::ZoneMaximumOutdoorAirFraction, "ZoneMaximumOutdoorAirFraction", "Zone Maximum Outdoor Air Fraction"},
{ Sizing_SystemFields::CoolingDesignCapacityMethod, "CoolingDesignCapacityMethod", "Cooling Design Capacity Method"},
{ Sizing_SystemFields::CoolingDesignCapacity, "CoolingDesignCapacity", "Cooling Design Capacity"},
{ Sizing_SystemFields::CoolingDesignCapacityPerFloorArea, "CoolingDesignCapacityPerFloorArea", "Cooling Design Capacity Per Floor Area"},
{ Sizing_SystemFields::FractionofAutosizedCoolingDesignCapacity, "FractionofAutosizedCoolingDesignCapacity", "Fraction of Autosized Cooling Design Capacity"},
{ Sizing_SystemFields::HeatingDesignCapacityMethod, "HeatingDesignCapacityMethod", "Heating Design Capacity Method"},
{ Sizing_SystemFields::HeatingDesignCapacity, "HeatingDesignCapacity", "Heating Design Capacity"},
{ Sizing_SystemFields::HeatingDesignCapacityPerFloorArea, "HeatingDesignCapacityPerFloorArea", "Heating Design Capacity Per Floor Area"},
{ Sizing_SystemFields::FractionofAutosizedHeatingDesignCapacity, "FractionofAutosizedHeatingDesignCapacity", "Fraction of Autosized Heating Design Capacity"},
{ Sizing_SystemFields::CentralCoolingCapacityControlMethod, "CentralCoolingCapacityControlMethod", "Central Cooling Capacity Control Method"},
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
  inline std::ostream &operator<<(std::ostream &os, const Sizing_SystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Sizing_SystemFields> OptionalSizing_SystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SIZING_SYSTEM_FIELDENUMS_HXX
