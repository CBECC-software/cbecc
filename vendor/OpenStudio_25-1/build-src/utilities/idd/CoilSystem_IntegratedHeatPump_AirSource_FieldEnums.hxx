/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX
#define UTILITIES_IDD_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CoilSystem_IntegratedHeatPump_AirSourceFields
 *  \brief Enumeration of CoilSystem:IntegratedHeatPump:AirSource's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CoilSystem_IntegratedHeatPump_AirSourceFields, )
#else
class CoilSystem_IntegratedHeatPump_AirSourceFields: public ::EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields> {
 public: 
  enum domain 
  {
Name, SupplyHotWaterFlowSensorNodeName, SpaceCoolingCoilName, SpaceHeatingCoilName, DedicatedWaterHeatingCoilName, SCWHCoilName, SCDWHCoolingCoilName, SCDWHWaterHeatingCoilName, SHDWHHeatingCoilName, SHDWHWaterHeatingCoilName, IndoorTemperatureLimitforSCWHMode, AmbientTemperatureLimitforSCWHMode, IndoorTemperatureaboveWhichWHhasHigherPriority, AmbientTemperatureaboveWhichWHhasHigherPriority, FlagtoIndicateLoadControlinSCWHMode, MinimumSpeedLevelforSCWHMode, MaximumWaterFlowVolumebeforeSwitchingfromSCDWHtoSCWHMode, MinimumSpeedLevelforSCDWHMode, MaximumRunningTimebeforeAllowingElectricResistanceHeatUseduringSHDWHMode, MinimumSpeedLevelforSHDWHMode,   };
  CoilSystem_IntegratedHeatPump_AirSourceFields()
   : EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields>(Name) {} 
  CoilSystem_IntegratedHeatPump_AirSourceFields(const std::string &t_name) 
   : EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields>(t_name) {} 
  CoilSystem_IntegratedHeatPump_AirSourceFields(int t_value) 
   : EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields>(t_value) {} 
  static std::string enumName() 
  { return "CoilSystem_IntegratedHeatPump_AirSourceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields>::integer_value()); }
   private:
    friend class EnumBase<CoilSystem_IntegratedHeatPump_AirSourceFields>;
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
{ CoilSystem_IntegratedHeatPump_AirSourceFields::Name, "Name", "Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SupplyHotWaterFlowSensorNodeName, "SupplyHotWaterFlowSensorNodeName", "Supply Hot Water Flow Sensor Node Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceCoolingCoilName, "SpaceCoolingCoilName", "Space Cooling Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SpaceHeatingCoilName, "SpaceHeatingCoilName", "Space Heating Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::DedicatedWaterHeatingCoilName, "DedicatedWaterHeatingCoilName", "Dedicated Water Heating Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SCWHCoilName, "SCWHCoilName", "SCWH Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHCoolingCoilName, "SCDWHCoolingCoilName", "SCDWH Cooling Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SCDWHWaterHeatingCoilName, "SCDWHWaterHeatingCoilName", "SCDWH Water Heating Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHHeatingCoilName, "SHDWHHeatingCoilName", "SHDWH Heating Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::SHDWHWaterHeatingCoilName, "SHDWHWaterHeatingCoilName", "SHDWH Water Heating Coil Name"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureLimitforSCWHMode, "IndoorTemperatureLimitforSCWHMode", "Indoor Temperature Limit for SCWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureLimitforSCWHMode, "AmbientTemperatureLimitforSCWHMode", "Ambient Temperature Limit for SCWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::IndoorTemperatureaboveWhichWHhasHigherPriority, "IndoorTemperatureaboveWhichWHhasHigherPriority", "Indoor Temperature above Which WH has Higher Priority"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::AmbientTemperatureaboveWhichWHhasHigherPriority, "AmbientTemperatureaboveWhichWHhasHigherPriority", "Ambient Temperature above Which WH has Higher Priority"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::FlagtoIndicateLoadControlinSCWHMode, "FlagtoIndicateLoadControlinSCWHMode", "Flag to Indicate Load Control in SCWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSCWHMode, "MinimumSpeedLevelforSCWHMode", "Minimum Speed Level for SCWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumWaterFlowVolumebeforeSwitchingfromSCDWHtoSCWHMode, "MaximumWaterFlowVolumebeforeSwitchingfromSCDWHtoSCWHMode", "Maximum Water Flow Volume before Switching from SCDWH to SCWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSCDWHMode, "MinimumSpeedLevelforSCDWHMode", "Minimum Speed Level for SCDWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::MaximumRunningTimebeforeAllowingElectricResistanceHeatUseduringSHDWHMode, "MaximumRunningTimebeforeAllowingElectricResistanceHeatUseduringSHDWHMode", "Maximum Running Time before Allowing Electric Resistance Heat Use during SHDWH Mode"},
{ CoilSystem_IntegratedHeatPump_AirSourceFields::MinimumSpeedLevelforSHDWHMode, "MinimumSpeedLevelforSHDWHMode", "Minimum Speed Level for SHDWH Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const CoilSystem_IntegratedHeatPump_AirSourceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CoilSystem_IntegratedHeatPump_AirSourceFields> OptionalCoilSystem_IntegratedHeatPump_AirSourceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COILSYSTEM_INTEGRATEDHEATPUMP_AIRSOURCE_FIELDENUMS_HXX
