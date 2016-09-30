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

#ifndef UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYHEATPUMP_AIRTOAIR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYHEATPUMP_AIRTOAIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields
 *  \brief Enumeration of OS:AirLoopHVAC:UnitaryHeatPump:AirToAir's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields, )
#else
class OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields: public ::EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, SupplyAirFlowRateDuringCoolingOperation, SupplyAirFlowRateDuringHeatingOperation, SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, ControllingZoneorThermostatLocation, SupplyAirFanName, HeatingCoilName, CoolingCoilName, SupplementalHeatingCoilName, MaximumSupplyAirTemperaturefromSupplementalHeater, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, FanPlacement, SupplyAirFanOperatingModeScheduleName, DehumidificationControlType,   };
  OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields()
   : EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields>(Handle) {} 
  OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields>(t_name) {} 
  OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields>::value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields>;
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
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::Handle, "Handle", "Handle"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::Name, "Name", "Name"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFlowRateDuringCoolingOperation, "SupplyAirFlowRateDuringCoolingOperation", "Supply Air Flow Rate During Cooling Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFlowRateDuringHeatingOperation, "SupplyAirFlowRateDuringHeatingOperation", "Supply Air Flow Rate During Heating Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, "SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded", "Supply Air Flow Rate When No Cooling or Heating is Needed"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::ControllingZoneorThermostatLocation, "ControllingZoneorThermostatLocation", "Controlling Zone or Thermostat Location"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "MaximumSupplyAirTemperaturefromSupplementalHeater", "Maximum Supply Air Temperature from Supplemental Heater"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields> OptionalOS_AirLoopHVAC_UnitaryHeatPump_AirToAirFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRLOOPHVAC_UNITARYHEATPUMP_AIRTOAIR_FIELDENUMS_HXX
