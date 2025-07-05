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

#ifndef UTILITIES_IDD_OS_SIZING_SYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SIZING_SYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Sizing_SystemFields
 *  \brief Enumeration of OS:Sizing:System's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Sizing_SystemFields, )
#else
class OS_Sizing_SystemFields: public ::EnumBase<OS_Sizing_SystemFields> {
 public: 
  enum domain 
  {
Handle, AirLoopName, TypeofLoadtoSizeOn, DesignOutdoorAirFlowRate, CentralHeatingMaximumSystemAirFlowRatio, PreheatDesignTemperature, PreheatDesignHumidityRatio, PrecoolDesignTemperature, PrecoolDesignHumidityRatio, CentralCoolingDesignSupplyAirTemperature, CentralHeatingDesignSupplyAirTemperature, SizingOption, AllOutdoorAirinCooling, AllOutdoorAirinHeating, CentralCoolingDesignSupplyAirHumidityRatio, CentralHeatingDesignSupplyAirHumidityRatio, CoolingDesignAirFlowMethod, CoolingDesignAirFlowRate, HeatingDesignAirFlowMethod, HeatingDesignAirFlowRate, SystemOutdoorAirMethod, ZoneMaximumOutdoorAirFraction, CoolingSupplyAirFlowRatePerFloorArea, CoolingFractionofAutosizedCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRatePerUnitCoolingCapacity, HeatingSupplyAirFlowRatePerFloorArea, HeatingFractionofAutosizedHeatingSupplyAirFlowRate, HeatingFractionofAutosizedCoolingSupplyAirFlowRate, HeatingSupplyAirFlowRatePerUnitHeatingCapacity, CoolingDesignCapacityMethod, CoolingDesignCapacity, CoolingDesignCapacityPerFloorArea, FractionofAutosizedCoolingDesignCapacity, HeatingDesignCapacityMethod, HeatingDesignCapacity, HeatingDesignCapacityPerFloorArea, FractionofAutosizedHeatingDesignCapacity, CentralCoolingCapacityControlMethod, OccupantDiversity,   };
  OS_Sizing_SystemFields()
   : EnumBase<OS_Sizing_SystemFields>(Handle) {} 
  OS_Sizing_SystemFields(const std::string &t_name) 
   : EnumBase<OS_Sizing_SystemFields>(t_name) {} 
  OS_Sizing_SystemFields(int t_value) 
   : EnumBase<OS_Sizing_SystemFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Sizing_SystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Sizing_SystemFields>::value()); }
   private:
    friend class EnumBase<OS_Sizing_SystemFields>;
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
{ OS_Sizing_SystemFields::Handle, "Handle", "Handle"},
{ OS_Sizing_SystemFields::AirLoopName, "AirLoopName", "AirLoop Name"},
{ OS_Sizing_SystemFields::TypeofLoadtoSizeOn, "TypeofLoadtoSizeOn", "Type of Load to Size On"},
{ OS_Sizing_SystemFields::DesignOutdoorAirFlowRate, "DesignOutdoorAirFlowRate", "Design Outdoor Air Flow Rate"},
{ OS_Sizing_SystemFields::CentralHeatingMaximumSystemAirFlowRatio, "CentralHeatingMaximumSystemAirFlowRatio", "Central Heating Maximum System Air Flow Ratio"},
{ OS_Sizing_SystemFields::PreheatDesignTemperature, "PreheatDesignTemperature", "Preheat Design Temperature"},
{ OS_Sizing_SystemFields::PreheatDesignHumidityRatio, "PreheatDesignHumidityRatio", "Preheat Design Humidity Ratio"},
{ OS_Sizing_SystemFields::PrecoolDesignTemperature, "PrecoolDesignTemperature", "Precool Design Temperature"},
{ OS_Sizing_SystemFields::PrecoolDesignHumidityRatio, "PrecoolDesignHumidityRatio", "Precool Design Humidity Ratio"},
{ OS_Sizing_SystemFields::CentralCoolingDesignSupplyAirTemperature, "CentralCoolingDesignSupplyAirTemperature", "Central Cooling Design Supply Air Temperature"},
{ OS_Sizing_SystemFields::CentralHeatingDesignSupplyAirTemperature, "CentralHeatingDesignSupplyAirTemperature", "Central Heating Design Supply Air Temperature"},
{ OS_Sizing_SystemFields::SizingOption, "SizingOption", "Sizing Option"},
{ OS_Sizing_SystemFields::AllOutdoorAirinCooling, "AllOutdoorAirinCooling", "100% Outdoor Air in Cooling"},
{ OS_Sizing_SystemFields::AllOutdoorAirinHeating, "AllOutdoorAirinHeating", "100% Outdoor Air in Heating"},
{ OS_Sizing_SystemFields::CentralCoolingDesignSupplyAirHumidityRatio, "CentralCoolingDesignSupplyAirHumidityRatio", "Central Cooling Design Supply Air Humidity Ratio"},
{ OS_Sizing_SystemFields::CentralHeatingDesignSupplyAirHumidityRatio, "CentralHeatingDesignSupplyAirHumidityRatio", "Central Heating Design Supply Air Humidity Ratio"},
{ OS_Sizing_SystemFields::CoolingDesignAirFlowMethod, "CoolingDesignAirFlowMethod", "Cooling Design Air Flow Method"},
{ OS_Sizing_SystemFields::CoolingDesignAirFlowRate, "CoolingDesignAirFlowRate", "Cooling Design Air Flow Rate"},
{ OS_Sizing_SystemFields::HeatingDesignAirFlowMethod, "HeatingDesignAirFlowMethod", "Heating Design Air Flow Method"},
{ OS_Sizing_SystemFields::HeatingDesignAirFlowRate, "HeatingDesignAirFlowRate", "Heating Design Air Flow Rate"},
{ OS_Sizing_SystemFields::SystemOutdoorAirMethod, "SystemOutdoorAirMethod", "System Outdoor Air Method"},
{ OS_Sizing_SystemFields::ZoneMaximumOutdoorAirFraction, "ZoneMaximumOutdoorAirFraction", "Zone Maximum Outdoor Air Fraction"},
{ OS_Sizing_SystemFields::CoolingSupplyAirFlowRatePerFloorArea, "CoolingSupplyAirFlowRatePerFloorArea", "Cooling Supply Air Flow Rate Per Floor Area"},
{ OS_Sizing_SystemFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, "CoolingFractionofAutosizedCoolingSupplyAirFlowRate", "Cooling Fraction of Autosized Cooling Supply Air Flow Rate"},
{ OS_Sizing_SystemFields::CoolingSupplyAirFlowRatePerUnitCoolingCapacity, "CoolingSupplyAirFlowRatePerUnitCoolingCapacity", "Cooling Supply Air Flow Rate Per Unit Cooling Capacity"},
{ OS_Sizing_SystemFields::HeatingSupplyAirFlowRatePerFloorArea, "HeatingSupplyAirFlowRatePerFloorArea", "Heating Supply Air Flow Rate Per Floor Area"},
{ OS_Sizing_SystemFields::HeatingFractionofAutosizedHeatingSupplyAirFlowRate, "HeatingFractionofAutosizedHeatingSupplyAirFlowRate", "Heating Fraction of Autosized Heating Supply Air Flow Rate"},
{ OS_Sizing_SystemFields::HeatingFractionofAutosizedCoolingSupplyAirFlowRate, "HeatingFractionofAutosizedCoolingSupplyAirFlowRate", "Heating Fraction of Autosized Cooling Supply Air Flow Rate"},
{ OS_Sizing_SystemFields::HeatingSupplyAirFlowRatePerUnitHeatingCapacity, "HeatingSupplyAirFlowRatePerUnitHeatingCapacity", "Heating Supply Air Flow Rate Per Unit Heating Capacity"},
{ OS_Sizing_SystemFields::CoolingDesignCapacityMethod, "CoolingDesignCapacityMethod", "Cooling Design Capacity Method"},
{ OS_Sizing_SystemFields::CoolingDesignCapacity, "CoolingDesignCapacity", "Cooling Design Capacity"},
{ OS_Sizing_SystemFields::CoolingDesignCapacityPerFloorArea, "CoolingDesignCapacityPerFloorArea", "Cooling Design Capacity Per Floor Area"},
{ OS_Sizing_SystemFields::FractionofAutosizedCoolingDesignCapacity, "FractionofAutosizedCoolingDesignCapacity", "Fraction of Autosized Cooling Design Capacity"},
{ OS_Sizing_SystemFields::HeatingDesignCapacityMethod, "HeatingDesignCapacityMethod", "Heating Design Capacity Method"},
{ OS_Sizing_SystemFields::HeatingDesignCapacity, "HeatingDesignCapacity", "Heating Design Capacity"},
{ OS_Sizing_SystemFields::HeatingDesignCapacityPerFloorArea, "HeatingDesignCapacityPerFloorArea", "Heating Design Capacity Per Floor Area"},
{ OS_Sizing_SystemFields::FractionofAutosizedHeatingDesignCapacity, "FractionofAutosizedHeatingDesignCapacity", "Fraction of Autosized Heating Design Capacity"},
{ OS_Sizing_SystemFields::CentralCoolingCapacityControlMethod, "CentralCoolingCapacityControlMethod", "Central Cooling Capacity Control Method"},
{ OS_Sizing_SystemFields::OccupantDiversity, "OccupantDiversity", "Occupant Diversity"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Sizing_SystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Sizing_SystemFields> OptionalOS_Sizing_SystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SIZING_SYSTEM_FIELDENUMS_HXX
