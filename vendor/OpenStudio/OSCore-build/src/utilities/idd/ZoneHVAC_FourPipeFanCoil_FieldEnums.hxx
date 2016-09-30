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

#ifndef UTILITIES_IDD_ZONEHVAC_FOURPIPEFANCOIL_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_FOURPIPEFANCOIL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_FourPipeFanCoilFields
 *  \brief Enumeration of ZoneHVAC:FourPipeFanCoil's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_FourPipeFanCoilFields, )
#else
class ZoneHVAC_FourPipeFanCoilFields: public ::EnumBase<ZoneHVAC_FourPipeFanCoilFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CapacityControlMethod, MaximumSupplyAirFlowRate, LowSpeedSupplyAirFlowRatio, MediumSpeedSupplyAirFlowRatio, MaximumOutdoorAirFlowRate, OutdoorAirScheduleName, AirInletNodeName, AirOutletNodeName, OutdoorAirMixerObjectType, OutdoorAirMixerName, SupplyAirFanObjectType, SupplyAirFanName, CoolingCoilObjectType, CoolingCoilName, MaximumColdWaterFlowRate, MinimumColdWaterFlowRate, CoolingConvergenceTolerance, HeatingCoilObjectType, HeatingCoilName, MaximumHotWaterFlowRate, MinimumHotWaterFlowRate, HeatingConvergenceTolerance, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName, SupplyAirFanOperatingModeScheduleName, MinimumSupplyAirTemperatureinCoolingMode, MaximumSupplyAirTemperatureinHeatingMode,   };
  ZoneHVAC_FourPipeFanCoilFields()
   : EnumBase<ZoneHVAC_FourPipeFanCoilFields>(Name) {} 
  ZoneHVAC_FourPipeFanCoilFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_FourPipeFanCoilFields>(t_name) {} 
  ZoneHVAC_FourPipeFanCoilFields(int t_value) 
   : EnumBase<ZoneHVAC_FourPipeFanCoilFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_FourPipeFanCoilFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_FourPipeFanCoilFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_FourPipeFanCoilFields>;
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
{ ZoneHVAC_FourPipeFanCoilFields::Name, "Name", "Name"},
{ ZoneHVAC_FourPipeFanCoilFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_FourPipeFanCoilFields::CapacityControlMethod, "CapacityControlMethod", "Capacity Control Method"},
{ ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirFlowRate, "MaximumSupplyAirFlowRate", "Maximum Supply Air Flow Rate"},
{ ZoneHVAC_FourPipeFanCoilFields::LowSpeedSupplyAirFlowRatio, "LowSpeedSupplyAirFlowRatio", "Low Speed Supply Air Flow Ratio"},
{ ZoneHVAC_FourPipeFanCoilFields::MediumSpeedSupplyAirFlowRatio, "MediumSpeedSupplyAirFlowRatio", "Medium Speed Supply Air Flow Ratio"},
{ ZoneHVAC_FourPipeFanCoilFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ ZoneHVAC_FourPipeFanCoilFields::OutdoorAirScheduleName, "OutdoorAirScheduleName", "Outdoor Air Schedule Name"},
{ ZoneHVAC_FourPipeFanCoilFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ ZoneHVAC_FourPipeFanCoilFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ ZoneHVAC_FourPipeFanCoilFields::OutdoorAirMixerObjectType, "OutdoorAirMixerObjectType", "Outdoor Air Mixer Object Type"},
{ ZoneHVAC_FourPipeFanCoilFields::OutdoorAirMixerName, "OutdoorAirMixerName", "Outdoor Air Mixer Name"},
{ ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_FourPipeFanCoilFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ ZoneHVAC_FourPipeFanCoilFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ ZoneHVAC_FourPipeFanCoilFields::MaximumColdWaterFlowRate, "MaximumColdWaterFlowRate", "Maximum Cold Water Flow Rate"},
{ ZoneHVAC_FourPipeFanCoilFields::MinimumColdWaterFlowRate, "MinimumColdWaterFlowRate", "Minimum Cold Water Flow Rate"},
{ ZoneHVAC_FourPipeFanCoilFields::CoolingConvergenceTolerance, "CoolingConvergenceTolerance", "Cooling Convergence Tolerance"},
{ ZoneHVAC_FourPipeFanCoilFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ ZoneHVAC_FourPipeFanCoilFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ ZoneHVAC_FourPipeFanCoilFields::MaximumHotWaterFlowRate, "MaximumHotWaterFlowRate", "Maximum Hot Water Flow Rate"},
{ ZoneHVAC_FourPipeFanCoilFields::MinimumHotWaterFlowRate, "MinimumHotWaterFlowRate", "Minimum Hot Water Flow Rate"},
{ ZoneHVAC_FourPipeFanCoilFields::HeatingConvergenceTolerance, "HeatingConvergenceTolerance", "Heating Convergence Tolerance"},
{ ZoneHVAC_FourPipeFanCoilFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_FourPipeFanCoilFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
{ ZoneHVAC_FourPipeFanCoilFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ ZoneHVAC_FourPipeFanCoilFields::MinimumSupplyAirTemperatureinCoolingMode, "MinimumSupplyAirTemperatureinCoolingMode", "Minimum Supply Air Temperature in Cooling Mode"},
{ ZoneHVAC_FourPipeFanCoilFields::MaximumSupplyAirTemperatureinHeatingMode, "MaximumSupplyAirTemperatureinHeatingMode", "Maximum Supply Air Temperature in Heating Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_FourPipeFanCoilFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_FourPipeFanCoilFields> OptionalZoneHVAC_FourPipeFanCoilFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_FOURPIPEFANCOIL_FIELDENUMS_HXX
