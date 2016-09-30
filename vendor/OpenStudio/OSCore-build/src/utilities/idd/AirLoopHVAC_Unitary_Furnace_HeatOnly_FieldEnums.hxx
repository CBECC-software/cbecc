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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_UNITARY_FURNACE_HEATONLY_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_UNITARY_FURNACE_HEATONLY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_Unitary_Furnace_HeatOnlyFields
 *  \brief Enumeration of AirLoopHVAC:Unitary:Furnace:HeatOnly's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_Unitary_Furnace_HeatOnlyFields, )
#else
class AirLoopHVAC_Unitary_Furnace_HeatOnlyFields: public ::EnumBase<AirLoopHVAC_Unitary_Furnace_HeatOnlyFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, FurnaceAirInletNodeName, FurnaceAirOutletNodeName, SupplyAirFanOperatingModeScheduleName, MaximumSupplyAirTemperature, HeatingSupplyAirFlowRate, ControllingZoneorThermostatLocation, SupplyFanObjectType, SupplyFanName, FanPlacement, HeatingCoilObjectType, HeatingCoilName,   };
  AirLoopHVAC_Unitary_Furnace_HeatOnlyFields()
   : EnumBase<AirLoopHVAC_Unitary_Furnace_HeatOnlyFields>(Name) {} 
  AirLoopHVAC_Unitary_Furnace_HeatOnlyFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_Unitary_Furnace_HeatOnlyFields>(t_name) {} 
  AirLoopHVAC_Unitary_Furnace_HeatOnlyFields(int t_value) 
   : EnumBase<AirLoopHVAC_Unitary_Furnace_HeatOnlyFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_Unitary_Furnace_HeatOnlyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_Unitary_Furnace_HeatOnlyFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_Unitary_Furnace_HeatOnlyFields>;
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
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::Name, "Name", "Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::FurnaceAirInletNodeName, "FurnaceAirInletNodeName", "Furnace Air Inlet Node Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::FurnaceAirOutletNodeName, "FurnaceAirOutletNodeName", "Furnace Air Outlet Node Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::MaximumSupplyAirTemperature, "MaximumSupplyAirTemperature", "Maximum Supply Air Temperature"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::ControllingZoneorThermostatLocation, "ControllingZoneorThermostatLocation", "Controlling Zone or Thermostat Location"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::SupplyFanObjectType, "SupplyFanObjectType", "Supply Fan Object Type"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::SupplyFanName, "SupplyFanName", "Supply Fan Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ AirLoopHVAC_Unitary_Furnace_HeatOnlyFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_Unitary_Furnace_HeatOnlyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_Unitary_Furnace_HeatOnlyFields> OptionalAirLoopHVAC_Unitary_Furnace_HeatOnlyFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_UNITARY_FURNACE_HEATONLY_FIELDENUMS_HXX
