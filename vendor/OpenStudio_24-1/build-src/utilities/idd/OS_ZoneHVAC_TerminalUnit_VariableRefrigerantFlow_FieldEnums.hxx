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

#ifndef UTILITIES_IDD_OS_ZONEHVAC_TERMINALUNIT_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEHVAC_TERMINALUNIT_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields
 *  \brief Enumeration of OS:ZoneHVAC:TerminalUnit:VariableRefrigerantFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields, )
#else
class OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields: public ::EnumBase<OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields> {
 public: 
  enum domain 
  {
Handle, Name, TerminalUnitAvailabilityschedule, TerminalUnitAirInletNode, TerminalUnitAirOutletNode, SupplyAirFlowRateDuringCoolingOperation, SupplyAirFlowRateWhenNoCoolingisNeeded, SupplyAirFlowRateDuringHeatingOperation, SupplyAirFlowRateWhenNoHeatingisNeeded, OutdoorAirFlowRateDuringCoolingOperation, OutdoorAirFlowRateDuringHeatingOperation, OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, SupplyAirFanOperatingModeSchedule, SupplyAirFanPlacement, SupplyAirFan, OutsideAirMixer, CoolingCoil, HeatingCoil, ZoneTerminalUnitOnParasiticElectricEnergyUse, ZoneTerminalUnitOffParasiticElectricEnergyUse, RatedTotalHeatingCapacitySizingRatio, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName, SupplementalHeatingCoilName, MaximumSupplyAirTemperaturefromSupplementalHeater, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, ControllingZoneorThermostatLocation,   };
  OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields()
   : EnumBase<OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields>(Handle) {} 
  OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields(const std::string &t_name) 
   : EnumBase<OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields>(t_name) {} 
  OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields(int t_value) 
   : EnumBase<OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields>::value()); }
   private:
    friend class EnumBase<OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields>;
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
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::Handle, "Handle", "Handle"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::Name, "Name", "Name"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAvailabilityschedule, "TerminalUnitAvailabilityschedule", "Terminal Unit Availability schedule"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirInletNode, "TerminalUnitAirInletNode", "Terminal Unit Air Inlet Node"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::TerminalUnitAirOutletNode, "TerminalUnitAirOutletNode", "Terminal Unit Air Outlet Node"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringCoolingOperation, "SupplyAirFlowRateDuringCoolingOperation", "Supply Air Flow Rate During Cooling Operation"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoCoolingisNeeded, "SupplyAirFlowRateWhenNoCoolingisNeeded", "Supply Air Flow Rate When No Cooling is Needed"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateDuringHeatingOperation, "SupplyAirFlowRateDuringHeatingOperation", "Supply Air Flow Rate During Heating Operation"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFlowRateWhenNoHeatingisNeeded, "SupplyAirFlowRateWhenNoHeatingisNeeded", "Supply Air Flow Rate When No Heating is Needed"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringCoolingOperation, "OutdoorAirFlowRateDuringCoolingOperation", "Outdoor Air Flow Rate During Cooling Operation"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateDuringHeatingOperation, "OutdoorAirFlowRateDuringHeatingOperation", "Outdoor Air Flow Rate During Heating Operation"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, "OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded", "Outdoor Air Flow Rate When No Cooling or Heating is Needed"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanOperatingModeSchedule, "SupplyAirFanOperatingModeSchedule", "Supply Air Fan Operating Mode Schedule"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanPlacement, "SupplyAirFanPlacement", "Supply Air Fan Placement"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFan, "SupplyAirFan", "Supply Air Fan"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixer, "OutsideAirMixer", "Outside Air Mixer"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoil, "CoolingCoil", "Cooling Coil"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoil, "HeatingCoil", "Heating Coil"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOnParasiticElectricEnergyUse, "ZoneTerminalUnitOnParasiticElectricEnergyUse", "Zone Terminal Unit On Parasitic Electric Energy Use"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOffParasiticElectricEnergyUse, "ZoneTerminalUnitOffParasiticElectricEnergyUse", "Zone Terminal Unit Off Parasitic Electric Energy Use"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::RatedTotalHeatingCapacitySizingRatio, "RatedTotalHeatingCapacitySizingRatio", "Rated Total Heating Capacity Sizing Ratio"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "MaximumSupplyAirTemperaturefromSupplementalHeater", "Maximum Supply Air Temperature from Supplemental Heater"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ControllingZoneorThermostatLocation, "ControllingZoneorThermostatLocation", "Controlling Zone or Thermostat Location"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields> OptionalOS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEHVAC_TERMINALUNIT_VARIABLEREFRIGERANTFLOW_FIELDENUMS_HXX
