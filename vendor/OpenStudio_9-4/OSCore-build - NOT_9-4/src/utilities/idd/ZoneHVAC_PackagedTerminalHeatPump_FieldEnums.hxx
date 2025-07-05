/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_ZONEHVAC_PACKAGEDTERMINALHEATPUMP_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_PACKAGEDTERMINALHEATPUMP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_PackagedTerminalHeatPumpFields
 *  \brief Enumeration of ZoneHVAC:PackagedTerminalHeatPump's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_PackagedTerminalHeatPumpFields, )
#else
class ZoneHVAC_PackagedTerminalHeatPumpFields: public ::EnumBase<ZoneHVAC_PackagedTerminalHeatPumpFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, OutdoorAirMixerObjectType, OutdoorAirMixerName, CoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoLoadSupplyAirFlowRate, CoolingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate, SupplyAirFanObjectType, SupplyAirFanName, HeatingCoilObjectType, HeatingCoilName, HeatingConvergenceTolerance, CoolingCoilObjectType, CoolingCoilName, CoolingConvergenceTolerance, SupplementalHeatingCoilObjectType, SupplementalHeatingCoilName, MaximumSupplyAirTemperaturefromSupplementalHeater, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, FanPlacement, SupplyAirFanOperatingModeScheduleName, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName, CapacityControlMethod, MinimumSupplyAirTemperatureinCoolingMode, MaximumSupplyAirTemperatureinHeatingMode,   };
  ZoneHVAC_PackagedTerminalHeatPumpFields()
   : EnumBase<ZoneHVAC_PackagedTerminalHeatPumpFields>(Name) {} 
  ZoneHVAC_PackagedTerminalHeatPumpFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_PackagedTerminalHeatPumpFields>(t_name) {} 
  ZoneHVAC_PackagedTerminalHeatPumpFields(int t_value) 
   : EnumBase<ZoneHVAC_PackagedTerminalHeatPumpFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_PackagedTerminalHeatPumpFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_PackagedTerminalHeatPumpFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_PackagedTerminalHeatPumpFields>;
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
{ ZoneHVAC_PackagedTerminalHeatPumpFields::Name, "Name", "Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerObjectType, "OutdoorAirMixerObjectType", "Outdoor Air Mixer Object Type"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerName, "OutdoorAirMixerName", "Outdoor Air Mixer Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingOutdoorAirFlowRate, "CoolingOutdoorAirFlowRate", "Cooling Outdoor Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingOutdoorAirFlowRate, "HeatingOutdoorAirFlowRate", "Heating Outdoor Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::NoLoadOutdoorAirFlowRate, "NoLoadOutdoorAirFlowRate", "No Load Outdoor Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingConvergenceTolerance, "HeatingConvergenceTolerance", "Heating Convergence Tolerance"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingConvergenceTolerance, "CoolingConvergenceTolerance", "Cooling Convergence Tolerance"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilObjectType, "SupplementalHeatingCoilObjectType", "Supplemental Heating Coil Object Type"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "MaximumSupplyAirTemperaturefromSupplementalHeater", "Maximum Supply Air Temperature from Supplemental Heater"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::CapacityControlMethod, "CapacityControlMethod", "Capacity Control Method"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::MinimumSupplyAirTemperatureinCoolingMode, "MinimumSupplyAirTemperatureinCoolingMode", "Minimum Supply Air Temperature in Cooling Mode"},
{ ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperatureinHeatingMode, "MaximumSupplyAirTemperatureinHeatingMode", "Maximum Supply Air Temperature in Heating Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_PackagedTerminalHeatPumpFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_PackagedTerminalHeatPumpFields> OptionalZoneHVAC_PackagedTerminalHeatPumpFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_PACKAGEDTERMINALHEATPUMP_FIELDENUMS_HXX
