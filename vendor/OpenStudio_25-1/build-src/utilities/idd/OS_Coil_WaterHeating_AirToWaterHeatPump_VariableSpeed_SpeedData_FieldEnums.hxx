/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_WATERHEATING_AIRTOWATERHEATPUMP_VARIABLESPEED_SPEEDDATA_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_WATERHEATING_AIRTOWATERHEATPUMP_VARIABLESPEED_SPEEDDATA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields
 *  \brief Enumeration of OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed:SpeedData's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields, )
#else
class OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields: public ::EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields> {
 public: 
  enum domain 
  {
Handle, Name, RatedWaterHeatingCapacity, RatedWaterHeatingCOP, RatedSensibleHeatRatio, ReferenceUnitRatedAirFlowRate, ReferenceUnitRatedWaterFlowRate, ReferenceUnitWaterPumpInputPowerAtRatedConditions, TotalWaterHeatingCapacityFunctionofTemperatureCurveName, TotalWaterHeatingCapacityFunctionofAirFlowFractionCurveName, TotalWaterHeatingCapacityFunctionofWaterFlowFractionCurveName, COPFunctionofTemperatureCurveName, COPFunctionofAirFlowFractionCurveName, COPFunctionofWaterFlowFractionCurveName,   };
  OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields()
   : EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields>(Handle) {} 
  OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields(const std::string &t_name) 
   : EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields>(t_name) {} 
  OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields(int t_value) 
   : EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields>;
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
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::Handle, "Handle", "Handle"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::Name, "Name", "Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::RatedWaterHeatingCapacity, "RatedWaterHeatingCapacity", "Rated Water Heating Capacity"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::RatedWaterHeatingCOP, "RatedWaterHeatingCOP", "Rated Water Heating COP"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::RatedSensibleHeatRatio, "RatedSensibleHeatRatio", "Rated Sensible Heat Ratio"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::ReferenceUnitRatedAirFlowRate, "ReferenceUnitRatedAirFlowRate", "Reference Unit Rated Air Flow Rate"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::ReferenceUnitRatedWaterFlowRate, "ReferenceUnitRatedWaterFlowRate", "Reference Unit Rated Water Flow Rate"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::ReferenceUnitWaterPumpInputPowerAtRatedConditions, "ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Reference Unit Water Pump Input Power At Rated Conditions"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::TotalWaterHeatingCapacityFunctionofTemperatureCurveName, "TotalWaterHeatingCapacityFunctionofTemperatureCurveName", "Total Water Heating Capacity Function of Temperature Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::TotalWaterHeatingCapacityFunctionofAirFlowFractionCurveName, "TotalWaterHeatingCapacityFunctionofAirFlowFractionCurveName", "Total Water Heating Capacity Function of Air Flow Fraction Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::TotalWaterHeatingCapacityFunctionofWaterFlowFractionCurveName, "TotalWaterHeatingCapacityFunctionofWaterFlowFractionCurveName", "Total Water Heating Capacity Function of Water Flow Fraction Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::COPFunctionofTemperatureCurveName, "COPFunctionofTemperatureCurveName", "COP Function of Temperature Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::COPFunctionofAirFlowFractionCurveName, "COPFunctionofAirFlowFractionCurveName", "COP Function of Air Flow Fraction Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields::COPFunctionofWaterFlowFractionCurveName, "COPFunctionofWaterFlowFractionCurveName", "COP Function of Water Flow Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields> OptionalOS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeed_SpeedDataFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_WATERHEATING_AIRTOWATERHEATPUMP_VARIABLESPEED_SPEEDDATA_FIELDENUMS_HXX
