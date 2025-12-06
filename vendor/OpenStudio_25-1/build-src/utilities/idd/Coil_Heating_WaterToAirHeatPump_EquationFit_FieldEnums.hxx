/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_WaterToAirHeatPump_EquationFitFields
 *  \brief Enumeration of Coil:Heating:WaterToAirHeatPump:EquationFit's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_WaterToAirHeatPump_EquationFitFields, )
#else
class Coil_Heating_WaterToAirHeatPump_EquationFitFields: public ::EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields> {
 public: 
  enum domain 
  {
Name, WaterInletNodeName, WaterOutletNodeName, AirInletNodeName, AirOutletNodeName, RatedAirFlowRate, RatedWaterFlowRate, GrossRatedHeatingCapacity, GrossRatedHeatingCOP, RatedEnteringWaterTemperature, RatedEnteringAirDryBulbTemperature, RatioofRatedHeatingCapacitytoRatedCoolingCapacity, HeatingCapacityCurveName, HeatingPowerConsumptionCurveName, PartLoadFractionCorrelationCurveName,   };
  Coil_Heating_WaterToAirHeatPump_EquationFitFields()
   : EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields>(Name) {} 
  Coil_Heating_WaterToAirHeatPump_EquationFitFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields>(t_name) {} 
  Coil_Heating_WaterToAirHeatPump_EquationFitFields(int t_value) 
   : EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_WaterToAirHeatPump_EquationFitFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields>::integer_value()); }
   private:
    friend class EnumBase<Coil_Heating_WaterToAirHeatPump_EquationFitFields>;
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
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::Name, "Name", "Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedWaterFlowRate, "RatedWaterFlowRate", "Rated Water Flow Rate"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCapacity, "GrossRatedHeatingCapacity", "Gross Rated Heating Capacity"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::GrossRatedHeatingCOP, "GrossRatedHeatingCOP", "Gross Rated Heating COP"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedEnteringWaterTemperature, "RatedEnteringWaterTemperature", "Rated Entering Water Temperature"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatedEnteringAirDryBulbTemperature, "RatedEnteringAirDryBulbTemperature", "Rated Entering Air Dry-Bulb Temperature"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::RatioofRatedHeatingCapacitytoRatedCoolingCapacity, "RatioofRatedHeatingCapacitytoRatedCoolingCapacity", "Ratio of Rated Heating Capacity to Rated Cooling Capacity"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingCapacityCurveName, "HeatingCapacityCurveName", "Heating Capacity Curve Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::HeatingPowerConsumptionCurveName, "HeatingPowerConsumptionCurveName", "Heating Power Consumption Curve Name"},
{ Coil_Heating_WaterToAirHeatPump_EquationFitFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_WaterToAirHeatPump_EquationFitFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_WaterToAirHeatPump_EquationFitFields> OptionalCoil_Heating_WaterToAirHeatPump_EquationFitFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_EQUATIONFIT_FIELDENUMS_HXX
