/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_ZONEHVAC_PACKAGEDTERMINALAIRCONDITIONER_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_PACKAGEDTERMINALAIRCONDITIONER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_PackagedTerminalAirConditionerFields
 *  \brief Enumeration of ZoneHVAC:PackagedTerminalAirConditioner's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_PackagedTerminalAirConditionerFields, )
#else
class ZoneHVAC_PackagedTerminalAirConditionerFields: public ::EnumBase<ZoneHVAC_PackagedTerminalAirConditionerFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, OutdoorAirMixerObjectType, OutdoorAirMixerName, CoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoLoadSupplyAirFlowRate, CoolingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate, SupplyAirFanObjectType, SupplyAirFanName, HeatingCoilObjectType, HeatingCoilName, CoolingCoilObjectType, CoolingCoilName, FanPlacement, SupplyAirFanOperatingModeScheduleName, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName, CapacityControlMethod, MinimumSupplyAirTemperatureinCoolingMode, MaximumSupplyAirTemperatureinHeatingMode,   };
  ZoneHVAC_PackagedTerminalAirConditionerFields()
   : EnumBase<ZoneHVAC_PackagedTerminalAirConditionerFields>(Name) {} 
  ZoneHVAC_PackagedTerminalAirConditionerFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_PackagedTerminalAirConditionerFields>(t_name) {} 
  ZoneHVAC_PackagedTerminalAirConditionerFields(int t_value) 
   : EnumBase<ZoneHVAC_PackagedTerminalAirConditionerFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_PackagedTerminalAirConditionerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_PackagedTerminalAirConditionerFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_PackagedTerminalAirConditionerFields>;
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
{ ZoneHVAC_PackagedTerminalAirConditionerFields::Name, "Name", "Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::OutdoorAirMixerObjectType, "OutdoorAirMixerObjectType", "Outdoor Air Mixer Object Type"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::OutdoorAirMixerName, "OutdoorAirMixerName", "Outdoor Air Mixer Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingOutdoorAirFlowRate, "CoolingOutdoorAirFlowRate", "Cooling Outdoor Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingOutdoorAirFlowRate, "HeatingOutdoorAirFlowRate", "Heating Outdoor Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::NoLoadOutdoorAirFlowRate, "NoLoadOutdoorAirFlowRate", "No Load Outdoor Air Flow Rate"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::CapacityControlMethod, "CapacityControlMethod", "Capacity Control Method"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::MinimumSupplyAirTemperatureinCoolingMode, "MinimumSupplyAirTemperatureinCoolingMode", "Minimum Supply Air Temperature in Cooling Mode"},
{ ZoneHVAC_PackagedTerminalAirConditionerFields::MaximumSupplyAirTemperatureinHeatingMode, "MaximumSupplyAirTemperatureinHeatingMode", "Maximum Supply Air Temperature in Heating Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_PackagedTerminalAirConditionerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_PackagedTerminalAirConditionerFields> OptionalZoneHVAC_PackagedTerminalAirConditionerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_PACKAGEDTERMINALAIRCONDITIONER_FIELDENUMS_HXX
