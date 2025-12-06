/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONEHVAC_WATERTOAIRHEATPUMP_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEHVAC_WATERTOAIRHEATPUMP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneHVAC_WaterToAirHeatPumpFields
 *  \brief Enumeration of OS:ZoneHVAC:WaterToAirHeatPump's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneHVAC_WaterToAirHeatPumpFields, )
#else
class OS_ZoneHVAC_WaterToAirHeatPumpFields: public ::EnumBase<OS_ZoneHVAC_WaterToAirHeatPumpFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, OutdoorAirMixerName, SupplyAirFlowRateDuringCoolingOperation, SupplyAirFlowRateDuringHeatingOperation, SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, NoLoadSupplyAirFlowRateControlSetToLowSpeed, OutdoorAirFlowRateDuringCoolingOperation, OutdoorAirFlowRateDuringHeatingOperation, OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, SupplyAirFanName, HeatingCoilName, CoolingCoilName, SupplementalHeatingCoilName, MaximumSupplyAirTemperaturefromSupplementalHeater, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, OutdoorDryBulbTemperatureSensorNodeName, FanPlacement, SupplyAirFanOperatingModeScheduleName, AvailabilityManagerListName, HeatPumpCoilWaterFlowMode, DesignSpecificationZoneHVACSizingObjectName,   };
  OS_ZoneHVAC_WaterToAirHeatPumpFields()
   : EnumBase<OS_ZoneHVAC_WaterToAirHeatPumpFields>(Handle) {} 
  OS_ZoneHVAC_WaterToAirHeatPumpFields(const std::string &t_name) 
   : EnumBase<OS_ZoneHVAC_WaterToAirHeatPumpFields>(t_name) {} 
  OS_ZoneHVAC_WaterToAirHeatPumpFields(int t_value) 
   : EnumBase<OS_ZoneHVAC_WaterToAirHeatPumpFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneHVAC_WaterToAirHeatPumpFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneHVAC_WaterToAirHeatPumpFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneHVAC_WaterToAirHeatPumpFields>;
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
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::Handle, "Handle", "Handle"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::Name, "Name", "Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerName, "OutdoorAirMixerName", "Outdoor Air Mixer Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFlowRateDuringCoolingOperation, "SupplyAirFlowRateDuringCoolingOperation", "Supply Air Flow Rate During Cooling Operation"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFlowRateDuringHeatingOperation, "SupplyAirFlowRateDuringHeatingOperation", "Supply Air Flow Rate During Heating Operation"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded, "SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded", "Supply Air Flow Rate When No Cooling or Heating is Needed"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed, "NoLoadSupplyAirFlowRateControlSetToLowSpeed", "No Load Supply Air Flow Rate Control Set To Low Speed"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirFlowRateDuringCoolingOperation, "OutdoorAirFlowRateDuringCoolingOperation", "Outdoor Air Flow Rate During Cooling Operation"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirFlowRateDuringHeatingOperation, "OutdoorAirFlowRateDuringHeatingOperation", "Outdoor Air Flow Rate During Heating Operation"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded, "OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded", "Outdoor Air Flow Rate When No Cooling or Heating is Needed"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "MaximumSupplyAirTemperaturefromSupplementalHeater", "Maximum Supply Air Temperature from Supplemental Heater"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::OutdoorDryBulbTemperatureSensorNodeName, "OutdoorDryBulbTemperatureSensorNodeName", "Outdoor Dry-Bulb Temperature Sensor Node Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, "HeatPumpCoilWaterFlowMode", "Heat Pump Coil Water Flow Mode"},
{ OS_ZoneHVAC_WaterToAirHeatPumpFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneHVAC_WaterToAirHeatPumpFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneHVAC_WaterToAirHeatPumpFields> OptionalOS_ZoneHVAC_WaterToAirHeatPumpFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEHVAC_WATERTOAIRHEATPUMP_FIELDENUMS_HXX
