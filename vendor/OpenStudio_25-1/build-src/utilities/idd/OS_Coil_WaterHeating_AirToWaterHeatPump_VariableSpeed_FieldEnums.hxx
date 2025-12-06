/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_WATERHEATING_AIRTOWATERHEATPUMP_VARIABLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_WATERHEATING_AIRTOWATERHEATPUMP_VARIABLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields
 *  \brief Enumeration of OS:Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields, )
#else
class OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields: public ::EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, NominalSpeedLevel, RatedWaterHeatingCapacity, RatedEvaporatorInletAirDryBulbTemperature, RatedEvaporatorInletAirWetBulbTemperature, RatedCondenserInletWaterTemperature, RatedEvaporatorAirFlowRate, RatedCondenserWaterFlowRate, EvaporatorFanPowerIncludedinRatedCOP, CondenserPumpPowerIncludedinRatedCOP, CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, FractionofCondenserPumpHeattoWater, EvaporatorAirInletNodeName, EvaporatorAirOutletNodeName, CondenserWaterInletNodeName, CondenserWaterOutletNodeName, CrankcaseHeaterCapacity, CrankcaseHeaterCapacityFunctionofTemperatureCurveName, MaximumAmbientTemperatureforCrankcaseHeaterOperation, EvaporatorAirTemperatureTypeforCurveObjects, PartLoadFractionCorrelationCurveName, SpeedDataList,   };
  OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields()
   : EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>(Handle) {} 
  OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields(const std::string &t_name) 
   : EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>(t_name) {} 
  OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields(int t_value) 
   : EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>;
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
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Handle, "Handle", "Handle"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Name, "Name", "Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::NominalSpeedLevel, "NominalSpeedLevel", "Nominal Speed Level"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacity, "RatedWaterHeatingCapacity", "Rated Water Heating Capacity"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorInletAirDryBulbTemperature, "RatedEvaporatorInletAirDryBulbTemperature", "Rated Evaporator Inlet Air Dry-Bulb Temperature"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorInletAirWetBulbTemperature, "RatedEvaporatorInletAirWetBulbTemperature", "Rated Evaporator Inlet Air Wet-Bulb Temperature"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedCondenserInletWaterTemperature, "RatedCondenserInletWaterTemperature", "Rated Condenser Inlet Water Temperature"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorAirFlowRate, "RatedEvaporatorAirFlowRate", "Rated Evaporator Air Flow Rate"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedCondenserWaterFlowRate, "RatedCondenserWaterFlowRate", "Rated Condenser Water Flow Rate"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorFanPowerIncludedinRatedCOP, "EvaporatorFanPowerIncludedinRatedCOP", "Evaporator Fan Power Included in Rated COP"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserPumpPowerIncludedinRatedCOP, "CondenserPumpPowerIncludedinRatedCOP", "Condenser Pump Power Included in Rated COP"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, "CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP", "Condenser Pump Heat Included in Rated Heating Capacity and Rated COP"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::FractionofCondenserPumpHeattoWater, "FractionofCondenserPumpHeattoWater", "Fraction of Condenser Pump Heat to Water"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirInletNodeName, "EvaporatorAirInletNodeName", "Evaporator Air Inlet Node Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirOutletNodeName, "EvaporatorAirOutletNodeName", "Evaporator Air Outlet Node Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserWaterInletNodeName, "CondenserWaterInletNodeName", "Condenser Water Inlet Node Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserWaterOutletNodeName, "CondenserWaterOutletNodeName", "Condenser Water Outlet Node Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, "CrankcaseHeaterCapacityFunctionofTemperatureCurveName", "Crankcase Heater Capacity Function of Temperature Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, "MaximumAmbientTemperatureforCrankcaseHeaterOperation", "Maximum Ambient Temperature for Crankcase Heater Operation"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirTemperatureTypeforCurveObjects, "EvaporatorAirTemperatureTypeforCurveObjects", "Evaporator Air Temperature Type for Curve Objects"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::SpeedDataList, "SpeedDataList", "Speed Data List"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields> OptionalOS_Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_WATERHEATING_AIRTOWATERHEATPUMP_VARIABLESPEED_FIELDENUMS_HXX
