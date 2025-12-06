/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONEHVAC_WATERTOAIRHEATPUMP_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_WATERTOAIRHEATPUMP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_WaterToAirHeatPumpFields
 *  \brief Enumeration of ZoneHVAC:WaterToAirHeatPump's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_WaterToAirHeatPumpFields, )
#else
class ZoneHVAC_WaterToAirHeatPumpFields: public ::EnumBase<ZoneHVAC_WaterToAirHeatPumpFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, OutdoorAirMixerObjectType, OutdoorAirMixerName, CoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRateControlSetToLowSpeed, CoolingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate, SupplyAirFanObjectType, SupplyAirFanName, HeatingCoilObjectType, HeatingCoilName, CoolingCoilObjectType, CoolingCoilName, SupplementalHeatingCoilObjectType, SupplementalHeatingCoilName, MaximumSupplyAirTemperaturefromSupplementalHeater, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, OutdoorDryBulbTemperatureSensorNodeName, FanPlacement, SupplyAirFanOperatingModeScheduleName, AvailabilityManagerListName, HeatPumpCoilWaterFlowMode, DesignSpecificationZoneHVACSizingObjectName, DesignSpecificationMultispeedObjectType, DesignSpecificationMultispeedObjectName,   };
  ZoneHVAC_WaterToAirHeatPumpFields()
   : EnumBase<ZoneHVAC_WaterToAirHeatPumpFields>(Name) {} 
  ZoneHVAC_WaterToAirHeatPumpFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_WaterToAirHeatPumpFields>(t_name) {} 
  ZoneHVAC_WaterToAirHeatPumpFields(int t_value) 
   : EnumBase<ZoneHVAC_WaterToAirHeatPumpFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_WaterToAirHeatPumpFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_WaterToAirHeatPumpFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneHVAC_WaterToAirHeatPumpFields>;
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
{ ZoneHVAC_WaterToAirHeatPumpFields::Name, "Name", "Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerObjectType, "OutdoorAirMixerObjectType", "Outdoor Air Mixer Object Type"},
{ ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerName, "OutdoorAirMixerName", "Outdoor Air Mixer Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRateControlSetToLowSpeed, "NoLoadSupplyAirFlowRateControlSetToLowSpeed", "No Load Supply Air Flow Rate Control Set To Low Speed"},
{ ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate, "CoolingOutdoorAirFlowRate", "Cooling Outdoor Air Flow Rate"},
{ ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate, "HeatingOutdoorAirFlowRate", "Heating Outdoor Air Flow Rate"},
{ ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate, "NoLoadOutdoorAirFlowRate", "No Load Outdoor Air Flow Rate"},
{ ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilObjectType, "SupplementalHeatingCoilObjectType", "Supplemental Heating Coil Object Type"},
{ ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "MaximumSupplyAirTemperaturefromSupplementalHeater", "Maximum Supply Air Temperature from Supplemental Heater"},
{ ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ ZoneHVAC_WaterToAirHeatPumpFields::OutdoorDryBulbTemperatureSensorNodeName, "OutdoorDryBulbTemperatureSensorNodeName", "Outdoor Dry-Bulb Temperature Sensor Node Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpCoilWaterFlowMode, "HeatPumpCoilWaterFlowMode", "Heat Pump Coil Water Flow Mode"},
{ ZoneHVAC_WaterToAirHeatPumpFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
{ ZoneHVAC_WaterToAirHeatPumpFields::DesignSpecificationMultispeedObjectType, "DesignSpecificationMultispeedObjectType", "Design Specification Multispeed Object Type"},
{ ZoneHVAC_WaterToAirHeatPumpFields::DesignSpecificationMultispeedObjectName, "DesignSpecificationMultispeedObjectName", "Design Specification Multispeed Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_WaterToAirHeatPumpFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_WaterToAirHeatPumpFields> OptionalZoneHVAC_WaterToAirHeatPumpFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_WATERTOAIRHEATPUMP_FIELDENUMS_HXX
