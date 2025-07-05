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
