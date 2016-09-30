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

#ifndef UTILITIES_IDD_OS_ZONEHVAC_PACKAGEDTERMINALHEATPUMP_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEHVAC_PACKAGEDTERMINALHEATPUMP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneHVAC_PackagedTerminalHeatPumpFields
 *  \brief Enumeration of OS:ZoneHVAC:PackagedTerminalHeatPump's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneHVAC_PackagedTerminalHeatPumpFields, )
#else
class OS_ZoneHVAC_PackagedTerminalHeatPumpFields: public ::EnumBase<OS_ZoneHVAC_PackagedTerminalHeatPumpFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, OutdoorAirMixerObjectType, OutdoorAirMixerName, SupplyAirFlowRateDuringCoolingOperation, SupplyAirFlowRateDuringHeatingOperation, SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, OutdoorAirFlowRateDuringCoolingOperation, OutdoorAirFlowRateDuringHeatingOperation, OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, SupplyAirFanName, HeatingCoilName, HeatingConvergenceTolerance, MinimumOutdoorDryBulbTemperatureforCompressorOperation, CoolingCoilName, CoolingConvergenceTolerance, SupplementalHeatingCoilName, MaximumSupplyAirTemperaturefromSupplementalHeater, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, FanPlacement, SupplyAirFanOperatingModeScheduleName,   };
  OS_ZoneHVAC_PackagedTerminalHeatPumpFields()
   : EnumBase<OS_ZoneHVAC_PackagedTerminalHeatPumpFields>(Handle) {} 
  OS_ZoneHVAC_PackagedTerminalHeatPumpFields(const std::string &t_name) 
   : EnumBase<OS_ZoneHVAC_PackagedTerminalHeatPumpFields>(t_name) {} 
  OS_ZoneHVAC_PackagedTerminalHeatPumpFields(int t_value) 
   : EnumBase<OS_ZoneHVAC_PackagedTerminalHeatPumpFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneHVAC_PackagedTerminalHeatPumpFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneHVAC_PackagedTerminalHeatPumpFields>::value()); }
   private:
    friend class EnumBase<OS_ZoneHVAC_PackagedTerminalHeatPumpFields>;
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
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::Handle, "Handle", "Handle"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::Name, "Name", "Name"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerObjectType, "OutdoorAirMixerObjectType", "Outdoor Air Mixer Object Type"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirMixerName, "OutdoorAirMixerName", "Outdoor Air Mixer Name"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringCoolingOperation, "SupplyAirFlowRateDuringCoolingOperation", "Supply Air Flow Rate During Cooling Operation"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateDuringHeatingOperation, "SupplyAirFlowRateDuringHeatingOperation", "Supply Air Flow Rate During Heating Operation"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, "SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded", "Supply Air Flow Rate When No Cooling or Heating is Needed"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringCoolingOperation, "OutdoorAirFlowRateDuringCoolingOperation", "Outdoor Air Flow Rate During Cooling Operation"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateDuringHeatingOperation, "OutdoorAirFlowRateDuringHeatingOperation", "Outdoor Air Flow Rate During Heating Operation"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, "OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded", "Outdoor Air Flow Rate When No Cooling or Heating is Needed"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::HeatingConvergenceTolerance, "HeatingConvergenceTolerance", "Heating Convergence Tolerance"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::CoolingConvergenceTolerance, "CoolingConvergenceTolerance", "Cooling Convergence Tolerance"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "MaximumSupplyAirTemperaturefromSupplementalHeater", "Maximum Supply Air Temperature from Supplemental Heater"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ OS_ZoneHVAC_PackagedTerminalHeatPumpFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneHVAC_PackagedTerminalHeatPumpFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneHVAC_PackagedTerminalHeatPumpFields> OptionalOS_ZoneHVAC_PackagedTerminalHeatPumpFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEHVAC_PACKAGEDTERMINALHEATPUMP_FIELDENUMS_HXX
