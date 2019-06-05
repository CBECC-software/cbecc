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

#ifndef UTILITIES_IDD_ZONEHVAC_TERMINALUNIT_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_TERMINALUNIT_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields
 *  \brief Enumeration of ZoneHVAC:TerminalUnit:VariableRefrigerantFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields, )
#else
class ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields: public ::EnumBase<ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields> {
 public: 
  enum domain 
  {
ZoneTerminalUnitName, TerminalUnitAvailabilitySchedule, TerminalUnitAirInletNodeName, TerminalUnitAirOutletNodeName, CoolingSupplyAirFlowRate, NoCoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoHeatingSupplyAirFlowRate, CoolingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate, SupplyAirFanOperatingModeScheduleName, SupplyAirFanPlacement, SupplyAirFanObjectType, SupplyAirFanObjectName, OutsideAirMixerObjectType, OutsideAirMixerObjectName, CoolingCoilObjectType, CoolingCoilObjectName, HeatingCoilObjectType, HeatingCoilObjectName, ZoneTerminalUnitOnParasiticElectricEnergyUse, ZoneTerminalUnitOffParasiticElectricEnergyUse, RatedHeatingCapacitySizingRatio, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName,   };
  ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields()
   : EnumBase<ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields>(ZoneTerminalUnitName) {} 
  ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields>(t_name) {} 
  ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields(int t_value) 
   : EnumBase<ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields>;
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
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitName, "ZoneTerminalUnitName", "Zone Terminal Unit Name"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAvailabilitySchedule, "TerminalUnitAvailabilitySchedule", "Terminal Unit Availability Schedule"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirInletNodeName, "TerminalUnitAirInletNodeName", "Terminal Unit Air Inlet Node Name"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirOutletNodeName, "TerminalUnitAirOutletNodeName", "Terminal Unit Air Outlet Node Name"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoCoolingSupplyAirFlowRate, "NoCoolingSupplyAirFlowRate", "No Cooling Supply Air Flow Rate"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoHeatingSupplyAirFlowRate, "NoHeatingSupplyAirFlowRate", "No Heating Supply Air Flow Rate"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingOutdoorAirFlowRate, "CoolingOutdoorAirFlowRate", "Cooling Outdoor Air Flow Rate"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingOutdoorAirFlowRate, "HeatingOutdoorAirFlowRate", "Heating Outdoor Air Flow Rate"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::NoLoadOutdoorAirFlowRate, "NoLoadOutdoorAirFlowRate", "No Load Outdoor Air Flow Rate"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement, "SupplyAirFanPlacement", "Supply Air Fan Placement"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanObjectName, "SupplyAirFanObjectName", "Supply Air Fan Object Name"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectType, "OutsideAirMixerObjectType", "Outside Air Mixer Object Type"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixerObjectName, "OutsideAirMixerObjectName", "Outside Air Mixer Object Name"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoilObjectName, "CoolingCoilObjectName", "Cooling Coil Object Name"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoilObjectName, "HeatingCoilObjectName", "Heating Coil Object Name"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOnParasiticElectricEnergyUse, "ZoneTerminalUnitOnParasiticElectricEnergyUse", "Zone Terminal Unit On Parasitic Electric Energy Use"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOffParasiticElectricEnergyUse, "ZoneTerminalUnitOffParasiticElectricEnergyUse", "Zone Terminal Unit Off Parasitic Electric Energy Use"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::RatedHeatingCapacitySizingRatio, "RatedHeatingCapacitySizingRatio", "Rated Heating Capacity Sizing Ratio"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields> OptionalZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_TERMINALUNIT_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
