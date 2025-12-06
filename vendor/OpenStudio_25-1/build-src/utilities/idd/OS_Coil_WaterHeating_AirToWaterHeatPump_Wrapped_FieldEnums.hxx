/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_WATERHEATING_AIRTOWATERHEATPUMP_WRAPPED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_WATERHEATING_AIRTOWATERHEATPUMP_WRAPPED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields
 *  \brief Enumeration of OS:Coil:WaterHeating:AirToWaterHeatPump:Wrapped's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields, )
#else
class OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields: public ::EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields> {
 public: 
  enum domain 
  {
Handle, Name, RatedHeatingCapacity, RatedCOP, RatedSensibleHeatRatio, RatedEvaporatorInletAirDryBulbTemperature, RatedEvaporatorInletAirWetBulbTemperature, RatedCondenserWaterTemperature, RatedEvaporatorAirFlowRate, EvaporatorFanPowerIncludedinRatedCOP, EvaporatorAirInletNodeName, EvaporatorAirOutletNodeName, CrankcaseHeaterCapacity, CrankcaseHeaterCapacityFunctionofTemperatureCurveName, MaximumAmbientTemperatureforCrankcaseHeaterOperation, EvaporatorAirTemperatureTypeforCurveObjects, HeatingCapacityFunctionofTemperatureCurveName, HeatingCapacityFunctionofAirFlowFractionCurveName, HeatingCOPFunctionofTemperatureCurveName, HeatingCOPFunctionofAirFlowFractionCurveName, PartLoadFractionCorrelationCurveName,   };
  OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields()
   : EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields>(Handle) {} 
  OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields(const std::string &t_name) 
   : EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields>(t_name) {} 
  OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields(int t_value) 
   : EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields>;
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
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::Handle, "Handle", "Handle"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::Name, "Name", "Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedHeatingCapacity, "RatedHeatingCapacity", "Rated Heating Capacity"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCOP, "RatedCOP", "Rated COP"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedSensibleHeatRatio, "RatedSensibleHeatRatio", "Rated Sensible Heat Ratio"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirDryBulbTemperature, "RatedEvaporatorInletAirDryBulbTemperature", "Rated Evaporator Inlet Air Dry-Bulb Temperature"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorInletAirWetBulbTemperature, "RatedEvaporatorInletAirWetBulbTemperature", "Rated Evaporator Inlet Air Wet-Bulb Temperature"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedCondenserWaterTemperature, "RatedCondenserWaterTemperature", "Rated Condenser Water Temperature"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::RatedEvaporatorAirFlowRate, "RatedEvaporatorAirFlowRate", "Rated Evaporator Air Flow Rate"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorFanPowerIncludedinRatedCOP, "EvaporatorFanPowerIncludedinRatedCOP", "Evaporator Fan Power Included in Rated COP"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirInletNodeName, "EvaporatorAirInletNodeName", "Evaporator Air Inlet Node Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirOutletNodeName, "EvaporatorAirOutletNodeName", "Evaporator Air Outlet Node Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, "CrankcaseHeaterCapacityFunctionofTemperatureCurveName", "Crankcase Heater Capacity Function of Temperature Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, "MaximumAmbientTemperatureforCrankcaseHeaterOperation", "Maximum Ambient Temperature for Crankcase Heater Operation"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::EvaporatorAirTemperatureTypeforCurveObjects, "EvaporatorAirTemperatureTypeforCurveObjects", "Evaporator Air Temperature Type for Curve Objects"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofTemperatureCurveName, "HeatingCapacityFunctionofTemperatureCurveName", "Heating Capacity Function of Temperature Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCapacityFunctionofAirFlowFractionCurveName, "HeatingCapacityFunctionofAirFlowFractionCurveName", "Heating Capacity Function of Air Flow Fraction Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofTemperatureCurveName, "HeatingCOPFunctionofTemperatureCurveName", "Heating COP Function of Temperature Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::HeatingCOPFunctionofAirFlowFractionCurveName, "HeatingCOPFunctionofAirFlowFractionCurveName", "Heating COP Function of Air Flow Fraction Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields> OptionalOS_Coil_WaterHeating_AirToWaterHeatPump_WrappedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_WATERHEATING_AIRTOWATERHEATPUMP_WRAPPED_FIELDENUMS_HXX
