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
ZoneTerminalUnitName, TerminalUnitAvailabilitySchedule, TerminalUnitAirInletNodeName, TerminalUnitAirOutletNodeName, CoolingSupplyAirFlowRate, NoCoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoHeatingSupplyAirFlowRate, CoolingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate, SupplyAirFanOperatingModeScheduleName, SupplyAirFanPlacement, SupplyAirFanObjectType, SupplyAirFanObjectName, OutsideAirMixerObjectType, OutsideAirMixerObjectName, CoolingCoilObjectType, CoolingCoilObjectName, HeatingCoilObjectType, HeatingCoilObjectName, ZoneTerminalUnitOnParasiticElectricEnergyUse, ZoneTerminalUnitOffParasiticElectricEnergyUse, RatedTotalHeatingCapacitySizingRatio, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName,   };
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
{ ZoneHVAC_TerminalUnit_VariableRefrigerantFlowFields::RatedTotalHeatingCapacitySizingRatio, "RatedTotalHeatingCapacitySizingRatio", "Rated Total Heating Capacity Sizing Ratio"},
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
