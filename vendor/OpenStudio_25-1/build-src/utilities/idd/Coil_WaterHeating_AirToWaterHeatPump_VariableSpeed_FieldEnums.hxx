/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_COIL_WATERHEATING_AIRTOWATERHEATPUMP_VARIABLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_WATERHEATING_AIRTOWATERHEATPUMP_VARIABLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields
 *  \brief Enumeration of Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields, )
#else
class Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields: public ::EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields> {
 public: 
  enum domain 
  {
Name, NumberofSpeeds, NominalSpeedLevel, RatedWaterHeatingCapacity, RatedEvaporatorInletAirDryBulbTemperature, RatedEvaporatorInletAirWetBulbTemperature, RatedCondenserInletWaterTemperature, RatedEvaporatorAirFlowRate, RatedCondenserWaterFlowRate, EvaporatorFanPowerIncludedinRatedCOP, CondenserPumpPowerIncludedinRatedCOP, CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, FractionofCondenserPumpHeattoWater, EvaporatorAirInletNodeName, EvaporatorAirOutletNodeName, CondenserWaterInletNodeName, CondenserWaterOutletNodeName, CrankcaseHeaterCapacity, CrankcaseHeaterCapacityFunctionofTemperatureCurveName, MaximumAmbientTemperatureforCrankcaseHeaterOperation, EvaporatorAirTemperatureTypeforCurveObjects, PartLoadFractionCorrelationCurveName,   };
  Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields()
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>(Name) {} 
  Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields(const std::string &t_name) 
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>(t_name) {} 
  Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields(int t_value) 
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>::integer_value()); }
   private:
    friend class EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>;
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
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Name, "Name", "Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::NumberofSpeeds, "NumberofSpeeds", "Number of Speeds"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::NominalSpeedLevel, "NominalSpeedLevel", "Nominal Speed Level"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacity, "RatedWaterHeatingCapacity", "Rated Water Heating Capacity"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorInletAirDryBulbTemperature, "RatedEvaporatorInletAirDryBulbTemperature", "Rated Evaporator Inlet Air Dry-Bulb Temperature"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorInletAirWetBulbTemperature, "RatedEvaporatorInletAirWetBulbTemperature", "Rated Evaporator Inlet Air Wet-Bulb Temperature"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedCondenserInletWaterTemperature, "RatedCondenserInletWaterTemperature", "Rated Condenser Inlet Water Temperature"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedEvaporatorAirFlowRate, "RatedEvaporatorAirFlowRate", "Rated Evaporator Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedCondenserWaterFlowRate, "RatedCondenserWaterFlowRate", "Rated Condenser Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorFanPowerIncludedinRatedCOP, "EvaporatorFanPowerIncludedinRatedCOP", "Evaporator Fan Power Included in Rated COP"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserPumpPowerIncludedinRatedCOP, "CondenserPumpPowerIncludedinRatedCOP", "Condenser Pump Power Included in Rated COP"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, "CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP", "Condenser Pump Heat Included in Rated Heating Capacity and Rated COP"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::FractionofCondenserPumpHeattoWater, "FractionofCondenserPumpHeattoWater", "Fraction of Condenser Pump Heat to Water"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirInletNodeName, "EvaporatorAirInletNodeName", "Evaporator Air Inlet Node Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirOutletNodeName, "EvaporatorAirOutletNodeName", "Evaporator Air Outlet Node Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserWaterInletNodeName, "CondenserWaterInletNodeName", "Condenser Water Inlet Node Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CondenserWaterOutletNodeName, "CondenserWaterOutletNodeName", "Condenser Water Outlet Node Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::CrankcaseHeaterCapacityFunctionofTemperatureCurveName, "CrankcaseHeaterCapacityFunctionofTemperatureCurveName", "Crankcase Heater Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, "MaximumAmbientTemperatureforCrankcaseHeaterOperation", "Maximum Ambient Temperature for Crankcase Heater Operation"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirTemperatureTypeforCurveObjects, "EvaporatorAirTemperatureTypeforCurveObjects", "Evaporator Air Temperature Type for Curve Objects"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields> OptionalCoil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields ;
#endif

/** \class Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields
 *  \brief Enumeration of Coil:WaterHeating:AirToWaterHeatPump:VariableSpeed's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields, )
#else
class Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields: public ::EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields> {
 public: 
  enum domain 
  {
RatedWaterHeatingCapacityatSpeed, RatedWaterHeatingCOPatSpeed, RatedSensibleHeatRatioatSpeed, SpeedReferenceUnitRatedAirFlowRate, SpeedReferenceUnitRatedWaterFlowRate, SpeedReferenceUnitWaterPumpInputPowerAtRatedConditions, SpeedTotalWHCapacityFunctionofTemperatureCurveName, SpeedTotalWHCapacityFunctionofAirFlowFractionCurveName, SpeedTotalWHCapacityFunctionofWaterFlowFractionCurveName, SpeedCOPFunctionofTemperatureCurveName, SpeedCOPFunctionofAirFlowFractionCurveName, SpeedCOPFunctionofWaterFlowFractionCurveName,   };
  Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields()
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields>(RatedWaterHeatingCapacityatSpeed) {} 
  Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields(const std::string &t_name) 
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields>(t_name) {} 
  Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields(int t_value) 
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields>;
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
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::RatedWaterHeatingCapacityatSpeed, "RatedWaterHeatingCapacityatSpeed", "Rated Water Heating Capacity at Speed"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::RatedWaterHeatingCOPatSpeed, "RatedWaterHeatingCOPatSpeed", "Rated Water Heating COP at Speed"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::RatedSensibleHeatRatioatSpeed, "RatedSensibleHeatRatioatSpeed", "Rated Sensible Heat Ratio at Speed"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::SpeedReferenceUnitRatedAirFlowRate, "SpeedReferenceUnitRatedAirFlowRate", "Speed Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::SpeedReferenceUnitRatedWaterFlowRate, "SpeedReferenceUnitRatedWaterFlowRate", "Speed Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::SpeedReferenceUnitWaterPumpInputPowerAtRatedConditions, "SpeedReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::SpeedTotalWHCapacityFunctionofTemperatureCurveName, "SpeedTotalWHCapacityFunctionofTemperatureCurveName", "Speed Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::SpeedTotalWHCapacityFunctionofAirFlowFractionCurveName, "SpeedTotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::SpeedTotalWHCapacityFunctionofWaterFlowFractionCurveName, "SpeedTotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::SpeedCOPFunctionofTemperatureCurveName, "SpeedCOPFunctionofTemperatureCurveName", "Speed COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::SpeedCOPFunctionofAirFlowFractionCurveName, "SpeedCOPFunctionofAirFlowFractionCurveName", "Speed COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields::SpeedCOPFunctionofWaterFlowFractionCurveName, "SpeedCOPFunctionofWaterFlowFractionCurveName", "Speed COP Function of Water Flow Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields> OptionalCoil_WaterHeating_AirToWaterHeatPump_VariableSpeedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_WATERHEATING_AIRTOWATERHEATPUMP_VARIABLESPEED_FIELDENUMS_HXX
