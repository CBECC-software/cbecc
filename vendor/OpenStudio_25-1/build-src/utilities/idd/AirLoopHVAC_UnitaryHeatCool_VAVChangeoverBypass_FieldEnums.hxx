/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATCOOL_VAVCHANGEOVERBYPASS_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATCOOL_VAVCHANGEOVERBYPASS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields
 *  \brief Enumeration of AirLoopHVAC:UnitaryHeatCool:VAVChangeoverBypass's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields, )
#else
class AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields: public ::EnumBase<AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoLoadSupplyAirFlowRate, CoolingOutdoorAirFlowRate, HeatingOutdoorAirFlowRate, NoLoadOutdoorAirFlowRate, OutdoorAirFlowRateMultiplierScheduleName, AirInletNodeName, BypassDuctMixerNodeName, BypassDuctSplitterNodeName, AirOutletNodeName, OutdoorAirMixerObjectType, OutdoorAirMixerName, SupplyAirFanObjectType, SupplyAirFanName, SupplyAirFanPlacement, SupplyAirFanOperatingModeScheduleName, CoolingCoilObjectType, CoolingCoilName, HeatingCoilObjectType, HeatingCoilName, PriorityControlMode, MinimumOutletAirTemperatureDuringCoolingOperation, MaximumOutletAirTemperatureDuringHeatingOperation, DehumidificationControlType, PlenumorMixerInletNodeName, MinimumRuntimeBeforeOperatingModeChange,   };
  AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields()
   : EnumBase<AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields>(Name) {} 
  AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields>(t_name) {} 
  AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields(int t_value) 
   : EnumBase<AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields>::integer_value()); }
   private:
    friend class EnumBase<AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields>;
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
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::Name, "Name", "Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingOutdoorAirFlowRate, "CoolingOutdoorAirFlowRate", "Cooling Outdoor Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingOutdoorAirFlowRate, "HeatingOutdoorAirFlowRate", "Heating Outdoor Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::NoLoadOutdoorAirFlowRate, "NoLoadOutdoorAirFlowRate", "No Load Outdoor Air Flow Rate"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirFlowRateMultiplierScheduleName, "OutdoorAirFlowRateMultiplierScheduleName", "Outdoor Air Flow Rate Multiplier Schedule Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctMixerNodeName, "BypassDuctMixerNodeName", "Bypass Duct Mixer Node Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::BypassDuctSplitterNodeName, "BypassDuctSplitterNodeName", "Bypass Duct Splitter Node Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerObjectType, "OutdoorAirMixerObjectType", "Outdoor Air Mixer Object Type"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::OutdoorAirMixerName, "OutdoorAirMixerName", "Outdoor Air Mixer Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanPlacement, "SupplyAirFanPlacement", "Supply Air Fan Placement"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::PriorityControlMode, "PriorityControlMode", "Priority Control Mode"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MinimumOutletAirTemperatureDuringCoolingOperation, "MinimumOutletAirTemperatureDuringCoolingOperation", "Minimum Outlet Air Temperature During Cooling Operation"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MaximumOutletAirTemperatureDuringHeatingOperation, "MaximumOutletAirTemperatureDuringHeatingOperation", "Maximum Outlet Air Temperature During Heating Operation"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::PlenumorMixerInletNodeName, "PlenumorMixerInletNodeName", "Plenum or Mixer Inlet Node Name"},
{ AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields::MinimumRuntimeBeforeOperatingModeChange, "MinimumRuntimeBeforeOperatingModeChange", "Minimum Runtime Before Operating Mode Change"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields> OptionalAirLoopHVAC_UnitaryHeatCool_VAVChangeoverBypassFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_UNITARYHEATCOOL_VAVCHANGEOVERBYPASS_FIELDENUMS_HXX
