/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONEHVAC_LOWTEMPERATURERADIANT_CONSTANTFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEHVAC_LOWTEMPERATURERADIANT_CONSTANTFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields
 *  \brief Enumeration of OS:ZoneHVAC:LowTemperatureRadiant:ConstantFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields, )
#else
class OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields: public ::EnumBase<OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, RadiantSurfaceType, FluidtoRadiantSurfaceHeatTransferModel, HydronicTubingInsideDiameter, HydronicTubingOutsideDiameter, HydronicTubingLength, HydronicTubingConductivity, TemperatureControlType, RunningMeanOutdoorDryBulbTemperatureWeightingFactor, LowTempRadiantConstantFlowHeatingCoilName, LowTempRadiantConstantFlowCoolingCoilName, RatedFlowRate, PumpFlowRateScheduleName, RatedPumpHead, RatedPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, NumberofCircuits, CircuitLength, ChangeoverDelayTimePeriodSchedule,   };
  OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields()
   : EnumBase<OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields>(Handle) {} 
  OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields(const std::string &t_name) 
   : EnumBase<OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields>(t_name) {} 
  OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields(int t_value) 
   : EnumBase<OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields>;
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
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::Handle, "Handle", "Handle"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::Name, "Name", "Name"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RadiantSurfaceType, "RadiantSurfaceType", "Radiant Surface Type"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::FluidtoRadiantSurfaceHeatTransferModel, "FluidtoRadiantSurfaceHeatTransferModel", "Fluid to Radiant Surface Heat Transfer Model"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingInsideDiameter, "HydronicTubingInsideDiameter", "Hydronic Tubing Inside Diameter"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingOutsideDiameter, "HydronicTubingOutsideDiameter", "Hydronic Tubing Outside Diameter"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, "HydronicTubingLength", "Hydronic Tubing Length"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingConductivity, "HydronicTubingConductivity", "Hydronic Tubing Conductivity"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::TemperatureControlType, "TemperatureControlType", "Temperature Control Type"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RunningMeanOutdoorDryBulbTemperatureWeightingFactor, "RunningMeanOutdoorDryBulbTemperatureWeightingFactor", "Running Mean Outdoor Dry-Bulb Temperature Weighting Factor"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::LowTempRadiantConstantFlowHeatingCoilName, "LowTempRadiantConstantFlowHeatingCoilName", "Low Temp Radiant Constant Flow Heating Coil Name"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::LowTempRadiantConstantFlowCoolingCoilName, "LowTempRadiantConstantFlowCoolingCoilName", "Low Temp Radiant Constant Flow Cooling Coil Name"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, "RatedFlowRate", "Rated Flow Rate"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::PumpFlowRateScheduleName, "PumpFlowRateScheduleName", "Pump Flow Rate Schedule Name"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, "RatedPumpHead", "Rated Pump Head"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, "RatedPowerConsumption", "Rated Power Consumption"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, "NumberofCircuits", "Number of Circuits"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, "CircuitLength", "Circuit Length"},
{ OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::ChangeoverDelayTimePeriodSchedule, "ChangeoverDelayTimePeriodSchedule", "Changeover Delay Time Period Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields> OptionalOS_ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEHVAC_LOWTEMPERATURERADIANT_CONSTANTFLOW_FIELDENUMS_HXX
