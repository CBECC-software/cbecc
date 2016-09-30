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
Handle, Name, TerminalUnitAvailabilityschedule, TerminalUnitAirInletNode, TerminalUnitAirOutletNode, SupplyAirFlowRateDuringCoolingOperation, SupplyAirFlowRateWhenNoCoolingisNeeded, SupplyAirFlowRateDuringHeatingOperation, SupplyAirFlowRateWhenNoHeatingisNeeded, OutdoorAirFlowRateDuringCoolingOperation, OutdoorAirFlowRateDuringHeatingOperation, OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, SupplyAirFanOperatingModeSchedule, SupplyAirFanplacement, SupplyAirFan, OutsideAirMixer, CoolingCoil, HeatingCoil, ZoneTerminalUnitOnParasiticElectricEnergyUse, ZoneTerminalUnitOffParasiticElectricEnergyUse, RatedTotalHeatingCapacitySizingRatio,   };
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
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFanplacement, "SupplyAirFanplacement", "Supply Air Fan placement"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::SupplyAirFan, "SupplyAirFan", "Supply Air Fan"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::OutsideAirMixer, "OutsideAirMixer", "Outside Air Mixer"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::CoolingCoil, "CoolingCoil", "Cooling Coil"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::HeatingCoil, "HeatingCoil", "Heating Coil"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOnParasiticElectricEnergyUse, "ZoneTerminalUnitOnParasiticElectricEnergyUse", "Zone Terminal Unit On Parasitic Electric Energy Use"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::ZoneTerminalUnitOffParasiticElectricEnergyUse, "ZoneTerminalUnitOffParasiticElectricEnergyUse", "Zone Terminal Unit Off Parasitic Electric Energy Use"},
{ OS_ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::RatedTotalHeatingCapacitySizingRatio, "RatedTotalHeatingCapacitySizingRatio", "Rated Total Heating Capacity Sizing Ratio"},
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
