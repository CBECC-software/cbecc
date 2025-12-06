/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_CoilSystem_IntegratedHeatPump_AirSourceFields
 *  \brief Enumeration of OS:CoilSystem:IntegratedHeatPump:AirSource's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_CoilSystem_IntegratedHeatPump_AirSourceFields, )
#else
class OS_CoilSystem_IntegratedHeatPump_AirSourceFields: public ::EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields> {
 public: 
  enum domain 
  {
Handle, Name, AirInletNodeName, AirOutletNodeName, SupplyHotWaterFlowSensorNodeName, SpaceCoolingCoil, SpaceHeatingCoil, DedicatedWaterHeatingCoil, SCWHCoil, SCDWHCoolingCoil, SCDWHWaterHeatingCoil, SHDWHHeatingCoil, SHDWHWaterHeatingCoil, IndoorTemperatureLimitForSCWHMode, AmbientTemperatureLimitForSCWHMode, IndoorTemperatureAboveWhichWHHasHigherPriority, AmbientTemperatureAboveWhichWHHasHigherPriority, FlagtoIndicateLoadControlInSCWHMode, MinimumSpeedLevelForSCWHMode, MaximumWaterFlowVolumeBeforeSwitchingFromSCDWHToSCWHMode, MinimumSpeedLevelForSCDWHMode, MaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode, MinimumSpeedLevelForSHDWHMode,   };
  OS_CoilSystem_IntegratedHeatPump_AirSourceFields()
   : EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields>(Handle) {} 
  OS_CoilSystem_IntegratedHeatPump_AirSourceFields(const std::string &t_name) 
   : EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields>(t_name) {} 
  OS_CoilSystem_IntegratedHeatPump_AirSourceFields(int t_value) 
   : EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_CoilSystem_IntegratedHeatPump_AirSourceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields>::integer_value()); }
   private:
    friend class EnumBase<OS_CoilSystem_IntegratedHeatPump_AirSourceFields>;
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
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::Handle, "Handle", "Handle"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::Name, "Name", "Name"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SupplyHotWaterFlowSensorNodeName, "SupplyHotWaterFlowSensorNodeName", "Supply Hot Water Flow Sensor Node Name"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceCoolingCoil, "SpaceCoolingCoil", "Space Cooling Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceHeatingCoil, "SpaceHeatingCoil", "Space Heating Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::DedicatedWaterHeatingCoil, "DedicatedWaterHeatingCoil", "Dedicated Water Heating Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SCWHCoil, "SCWHCoil", "SCWH Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHCoolingCoil, "SCDWHCoolingCoil", "SCDWH Cooling Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHWaterHeatingCoil, "SCDWHWaterHeatingCoil", "SCDWH Water Heating Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHHeatingCoil, "SHDWHHeatingCoil", "SHDWH Heating Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHWaterHeatingCoil, "SHDWHWaterHeatingCoil", "SHDWH Water Heating Coil"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureLimitForSCWHMode, "IndoorTemperatureLimitForSCWHMode", "Indoor Temperature Limit For SCWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureLimitForSCWHMode, "AmbientTemperatureLimitForSCWHMode", "Ambient Temperature Limit For SCWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureAboveWhichWHHasHigherPriority, "IndoorTemperatureAboveWhichWHHasHigherPriority", "Indoor Temperature Above Which WH Has Higher Priority"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureAboveWhichWHHasHigherPriority, "AmbientTemperatureAboveWhichWHHasHigherPriority", "Ambient Temperature Above Which WH Has Higher Priority"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::FlagtoIndicateLoadControlInSCWHMode, "FlagtoIndicateLoadControlInSCWHMode", "Flag to Indicate Load Control In SCWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelForSCWHMode, "MinimumSpeedLevelForSCWHMode", "Minimum Speed Level For SCWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumWaterFlowVolumeBeforeSwitchingFromSCDWHToSCWHMode, "MaximumWaterFlowVolumeBeforeSwitchingFromSCDWHToSCWHMode", "Maximum Water Flow Volume Before Switching From SCDWH To SCWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelForSCDWHMode, "MinimumSpeedLevelForSCDWHMode", "Minimum Speed Level For SCDWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode, "MaximumRunningTimeBeforeAllowingElectricResistanceHeatUseDuringSHDWHMode", "Maximum Running Time Before Allowing Electric Resistance Heat Use During SHDWH Mode"},
{ OS_CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelForSHDWHMode, "MinimumSpeedLevelForSHDWHMode", "Minimum Speed Level For SHDWH Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_CoilSystem_IntegratedHeatPump_AirSourceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_CoilSystem_IntegratedHeatPump_AirSourceFields> OptionalOS_CoilSystem_IntegratedHeatPump_AirSourceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX
