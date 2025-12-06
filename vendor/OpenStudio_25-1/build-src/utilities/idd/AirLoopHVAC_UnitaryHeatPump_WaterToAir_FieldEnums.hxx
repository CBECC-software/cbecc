/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATPUMP_WATERTOAIR_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATPUMP_WATERTOAIR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_UnitaryHeatPump_WaterToAirFields
 *  \brief Enumeration of AirLoopHVAC:UnitaryHeatPump:WaterToAir's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_UnitaryHeatPump_WaterToAirFields, )
#else
class AirLoopHVAC_UnitaryHeatPump_WaterToAirFields: public ::EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, SupplyAirFlowRate, ControllingZoneorThermostatLocation, SupplyAirFanObjectType, SupplyAirFanName, HeatingCoilObjectType, HeatingCoilName, HeatingConvergence, CoolingCoilObjectType, CoolingCoilName, CoolingConvergence, SupplementalHeatingCoilObjectType, SupplementalHeatingCoilName, MaximumSupplyAirTemperaturefromSupplementalHeater, MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, OutdoorDryBulbTemperatureSensorNodeName, FanPlacement, SupplyAirFanOperatingModeScheduleName, DehumidificationControlType, HeatPumpCoilWaterFlowMode,   };
  AirLoopHVAC_UnitaryHeatPump_WaterToAirFields()
   : EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields>(Name) {} 
  AirLoopHVAC_UnitaryHeatPump_WaterToAirFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields>(t_name) {} 
  AirLoopHVAC_UnitaryHeatPump_WaterToAirFields(int t_value) 
   : EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_UnitaryHeatPump_WaterToAirFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields>::integer_value()); }
   private:
    friend class EnumBase<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields>;
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
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::Name, "Name", "Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFlowRate, "SupplyAirFlowRate", "Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::ControllingZoneorThermostatLocation, "ControllingZoneorThermostatLocation", "Controlling Zone or Thermostat Location"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatingConvergence, "HeatingConvergence", "Heating Convergence"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::CoolingConvergence, "CoolingConvergence", "Cooling Convergence"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplementalHeatingCoilObjectType, "SupplementalHeatingCoilObjectType", "Supplemental Heating Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplementalHeatingCoilName, "SupplementalHeatingCoilName", "Supplemental Heating Coil Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumSupplyAirTemperaturefromSupplementalHeater, "MaximumSupplyAirTemperaturefromSupplementalHeater", "Maximum Supply Air Temperature from Supplemental Heater"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation, "MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Supplemental Heater Operation"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::OutdoorDryBulbTemperatureSensorNodeName, "OutdoorDryBulbTemperatureSensorNodeName", "Outdoor Dry-Bulb Temperature Sensor Node Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ AirLoopHVAC_UnitaryHeatPump_WaterToAirFields::HeatPumpCoilWaterFlowMode, "HeatPumpCoilWaterFlowMode", "Heat Pump Coil Water Flow Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_UnitaryHeatPump_WaterToAirFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_UnitaryHeatPump_WaterToAirFields> OptionalAirLoopHVAC_UnitaryHeatPump_WaterToAirFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATPUMP_WATERTOAIR_FIELDENUMS_HXX
