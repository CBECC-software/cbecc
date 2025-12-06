/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_COOLING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields
 *  \brief Enumeration of OS:Coil:Cooling:WaterToAirHeatPump:EquationFit's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields, )
#else
class OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields: public ::EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields> {
 public: 
  enum domain 
  {
Handle, Name, WaterInletNodeName, WaterOutletNodeName, AirInletNodeName, AirOutletNodeName, RatedAirFlowRate, RatedWaterFlowRate, RatedTotalCoolingCapacity, RatedSensibleCoolingCapacity, RatedCoolingCoefficientofPerformance, RatedEnteringWaterTemperature, RatedEnteringAirDryBulbTemperature, RatedEnteringAirWetBulbTemperature, TotalCoolingCapacityCurveName, SensibleCoolingCapacityCurveName, CoolingPowerConsumptionCurveName, PartLoadFractionCorrelationCurveName, NominalTimeforCondensateRemovaltoBegin, RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, MaximumCyclingRate, LatentCapacityTimeConstant, FanDelayTime,   };
  OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields()
   : EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields>(Handle) {} 
  OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields>(t_name) {} 
  OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields>;
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
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, "RatedWaterFlowRate", "Rated Water Flow Rate"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedTotalCoolingCapacity, "RatedTotalCoolingCapacity", "Rated Total Cooling Capacity"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedSensibleCoolingCapacity, "RatedSensibleCoolingCapacity", "Rated Sensible Cooling Capacity"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedCoolingCoefficientofPerformance, "RatedCoolingCoefficientofPerformance", "Rated Cooling Coefficient of Performance"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringWaterTemperature, "RatedEnteringWaterTemperature", "Rated Entering Water Temperature"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringAirDryBulbTemperature, "RatedEnteringAirDryBulbTemperature", "Rated Entering Air Dry-Bulb Temperature"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatedEnteringAirWetBulbTemperature, "RatedEnteringAirWetBulbTemperature", "Rated Entering Air Wet-Bulb Temperature"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::TotalCoolingCapacityCurveName, "TotalCoolingCapacityCurveName", "Total Cooling Capacity Curve Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::SensibleCoolingCapacityCurveName, "SensibleCoolingCapacityCurveName", "Sensible Cooling Capacity Curve Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::CoolingPowerConsumptionCurveName, "CoolingPowerConsumptionCurveName", "Cooling Power Consumption Curve Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::NominalTimeforCondensateRemovaltoBegin, "NominalTimeforCondensateRemovaltoBegin", "Nominal Time for Condensate Removal to Begin"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, "RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity", "Ratio of Initial Moisture Evaporation Rate and Steady State Latent Capacity"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::MaximumCyclingRate, "MaximumCyclingRate", "Maximum Cycling Rate"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::LatentCapacityTimeConstant, "LatentCapacityTimeConstant", "Latent Capacity Time Constant"},
{ OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields::FanDelayTime, "FanDelayTime", "Fan Delay Time"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields> OptionalOS_Coil_Cooling_WaterToAirHeatPump_EquationFitFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX
