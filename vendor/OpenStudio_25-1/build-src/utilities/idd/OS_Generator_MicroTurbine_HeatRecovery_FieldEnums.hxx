/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_GENERATOR_MICROTURBINE_HEATRECOVERY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GENERATOR_MICROTURBINE_HEATRECOVERY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Generator_MicroTurbine_HeatRecoveryFields
 *  \brief Enumeration of OS:Generator:MicroTurbine:HeatRecovery's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Generator_MicroTurbine_HeatRecoveryFields, )
#else
class OS_Generator_MicroTurbine_HeatRecoveryFields: public ::EnumBase<OS_Generator_MicroTurbine_HeatRecoveryFields> {
 public: 
  enum domain 
  {
Handle, Name, HeatRecoveryWaterInletNodeName, HeatRecoveryWaterOutletNodeName, ReferenceThermalEfficiencyUsingLowerHeatValue, ReferenceInletWaterTemperature, HeatRecoveryWaterFlowOperatingMode, ReferenceHeatRecoveryWaterFlowRate, HeatRecoveryWaterFlowRateFunctionofTemperatureandPowerCurveName, ThermalEfficiencyFunctionofTemperatureandElevationCurveName, HeatRecoveryRateFunctionofPartLoadRatioCurveName, HeatRecoveryRateFunctionofInletWaterTemperatureCurveName, HeatRecoveryRateFunctionofWaterFlowRateCurveName, MinimumHeatRecoveryWaterFlowRate, MaximumHeatRecoveryWaterFlowRate, MaximumHeatRecoveryWaterTemperature, RatedThermaltoElectricalPowerRatio,   };
  OS_Generator_MicroTurbine_HeatRecoveryFields()
   : EnumBase<OS_Generator_MicroTurbine_HeatRecoveryFields>(Handle) {} 
  OS_Generator_MicroTurbine_HeatRecoveryFields(const std::string &t_name) 
   : EnumBase<OS_Generator_MicroTurbine_HeatRecoveryFields>(t_name) {} 
  OS_Generator_MicroTurbine_HeatRecoveryFields(int t_value) 
   : EnumBase<OS_Generator_MicroTurbine_HeatRecoveryFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Generator_MicroTurbine_HeatRecoveryFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Generator_MicroTurbine_HeatRecoveryFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Generator_MicroTurbine_HeatRecoveryFields>;
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
{ OS_Generator_MicroTurbine_HeatRecoveryFields::Handle, "Handle", "Handle"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::Name, "Name", "Name"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::HeatRecoveryWaterInletNodeName, "HeatRecoveryWaterInletNodeName", "Heat Recovery Water Inlet Node Name"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::HeatRecoveryWaterOutletNodeName, "HeatRecoveryWaterOutletNodeName", "Heat Recovery Water Outlet Node Name"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::ReferenceThermalEfficiencyUsingLowerHeatValue, "ReferenceThermalEfficiencyUsingLowerHeatValue", "Reference Thermal Efficiency Using Lower Heat Value"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::ReferenceInletWaterTemperature, "ReferenceInletWaterTemperature", "Reference Inlet Water Temperature"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::HeatRecoveryWaterFlowOperatingMode, "HeatRecoveryWaterFlowOperatingMode", "Heat Recovery Water Flow Operating Mode"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::ReferenceHeatRecoveryWaterFlowRate, "ReferenceHeatRecoveryWaterFlowRate", "Reference Heat Recovery Water Flow Rate"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::HeatRecoveryWaterFlowRateFunctionofTemperatureandPowerCurveName, "HeatRecoveryWaterFlowRateFunctionofTemperatureandPowerCurveName", "Heat Recovery Water Flow Rate Function of Temperature and Power Curve Name"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::ThermalEfficiencyFunctionofTemperatureandElevationCurveName, "ThermalEfficiencyFunctionofTemperatureandElevationCurveName", "Thermal Efficiency Function of Temperature and Elevation Curve Name"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::HeatRecoveryRateFunctionofPartLoadRatioCurveName, "HeatRecoveryRateFunctionofPartLoadRatioCurveName", "Heat Recovery Rate Function of Part Load Ratio Curve Name"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::HeatRecoveryRateFunctionofInletWaterTemperatureCurveName, "HeatRecoveryRateFunctionofInletWaterTemperatureCurveName", "Heat Recovery Rate Function of Inlet Water Temperature Curve Name"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::HeatRecoveryRateFunctionofWaterFlowRateCurveName, "HeatRecoveryRateFunctionofWaterFlowRateCurveName", "Heat Recovery Rate Function of Water Flow Rate Curve Name"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::MinimumHeatRecoveryWaterFlowRate, "MinimumHeatRecoveryWaterFlowRate", "Minimum Heat Recovery Water Flow Rate"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::MaximumHeatRecoveryWaterFlowRate, "MaximumHeatRecoveryWaterFlowRate", "Maximum Heat Recovery Water Flow Rate"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::MaximumHeatRecoveryWaterTemperature, "MaximumHeatRecoveryWaterTemperature", "Maximum Heat Recovery Water Temperature"},
{ OS_Generator_MicroTurbine_HeatRecoveryFields::RatedThermaltoElectricalPowerRatio, "RatedThermaltoElectricalPowerRatio", "Rated Thermal to Electrical Power Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Generator_MicroTurbine_HeatRecoveryFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Generator_MicroTurbine_HeatRecoveryFields> OptionalOS_Generator_MicroTurbine_HeatRecoveryFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GENERATOR_MICROTURBINE_HEATRECOVERY_FIELDENUMS_HXX
