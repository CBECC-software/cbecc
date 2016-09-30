/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

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
Name, NumberofSpeeds, NominalSpeedLevel, RatedWaterHeatingCapacity, RatedEvaporatorInletAirDryBulbTemperature, RatedEvaporatorInletAirWetBulbTemperature, RatedCondenserInletWaterTemperature, RatedEvaporatorAirFlowRate, RatedCondenserWaterFlowRate, EvaporatorFanPowerIncludedinRatedCOP, CondenserPumpPowerIncludedinRatedCOP, CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, FractionofCondenserPumpHeattoWater, EvaporatorAirInletNodeName, EvaporatorAirOutletNodeName, CondenserWaterInletNodeName, CondenserWaterOutletNodeName, CrankcaseHeaterCapacity, MaximumAmbientTemperatureforCrankcaseHeaterOperation, EvaporatorAirTemperatureTypeforCurveObjects, PartLoadFractionCorrelationCurveName, RatedWaterHeatingCapacityatSpeed1, RatedWaterHeatingCOPatSpeed1, RatedSensibleHeatRatioatSpeed1, Speed1ReferenceUnitRatedAirFlowRate, Speed1ReferenceUnitRatedWaterFlowRate, Speed1ReferenceUnitWaterPumpInputPowerAtRatedConditions, Speed1TotalWHCapacityFunctionofTemperatureCurveName, Speed1TotalWHCapacityFunctionofAirFlowFractionCurveName, Speed1TotalWHCapacityFunctionofWaterFlowFractionCurveName, Speed1COPFunctionofTemperatureCurveName, Speed1COPFunctionofAirFlowFractionCurveName, Speed1COPFunctionofWaterFlowFractionCurveName, RatedWaterHeatingCapacityatSpeed2, RatedWaterHeatingCOPatSpeed2, RatedSensibleHeatRatioatSpeed2, Speed2ReferenceUnitRatedAirFlowRate, Speed2ReferenceUnitRatedWaterFlowRate, Speed2ReferenceUnitWaterPumpInputPowerAtRatedConditions, Speed2TotalWHCapacityFunctionofTemperatureCurveName, Speed2TotalWHCapacityFunctionofAirFlowFractionCurveName, Speed2TotalWHCapacityFunctionofWaterFlowFractionCurveName, Speed2COPFunctionofTemperatureCurveName, Speed2COPFunctionofAirFlowFractionCurveName, Speed2COPFunctionofWaterFlowFractionCurveName, RatedWaterHeatingCapacityatspeed3, RatedWaterHeatingCOPatSpeed3, RatedSensibleHeatRatioatSpeed3, Speed3ReferenceUnitRatedAirFlowRate, Speed3ReferenceUnitRatedWaterFlowRate, Speed3ReferenceUnitWaterPumpInputPowerAtRatedConditions, Speed3TotalWHCapacityFunctionofTemperatureCurveName, Speed3TotalWHCapacityFunctionofAirFlowFractionCurveName, Speed3TotalWHCapacityFunctionofWaterFlowFractionCurveName, Speed3COPFunctionofTemperatureCurveName, Speed3COPFunctionofAirFlowFractionCurveName, Speed3COPFunctionofWaterFlowFractionCurveName, RatedWaterHeatingCapacityatSpeed4, RatedWaterHeatingCOPatSpeed4, RatedSensibleHeatRatioatSpeed4, Speed4ReferenceUnitRatedAirFlowRate, Speed4ReferenceUnitRatedWaterFlowRate, Speed4ReferenceUnitWaterPumpInputPowerAtRatedConditions, Speed4TotalWHCapacityFunctionofTemperatureCurveName, Speed4TotalWHCapacityFunctionofAirFlowFractionCurveName, Speed4TotalWHCapacityFunctionofWaterFlowFractionCurveName, Speed4COPFunctionofTemperatureCurveName, Speed4COPFunctionofAirFlowFractionCurveName, Speed4COPFunctionofWaterFlowFractionCurveName, RatedWaterHeatingCapacityatSpeed5, RatedWaterHeatingCOPatSpeed5, RatedSensibleHeatRatioatSpeed5, Speed5ReferenceUnitRatedAirFlowRate, Speed5ReferenceUnitRatedWaterFlowRate, Speed5ReferenceUnitWaterPumpInputPowerAtRatedConditions, Speed5TotalWHCapacityFunctionofTemperatureCurveName, Speed5TotalWHCapacityFunctionofAirFlowFractionCurveName, Speed5TotalWHCapacityFunctionofWaterFlowFractionCurveName, Speed5COPFunctionofTemperatureCurveName, Speed5COPFunctionofAirFlowFractionCurveName, Speed5COPFunctionofWaterFlowFractionCurveName, RatedWaterHeatingCapacityatSpeed6, RatedWaterHeatingCOPatSpeed6, RatedSensibleHeatRatioatSpeed6, Speed6ReferenceUnitRatedAirFlowRate, Speed6ReferenceUnitRatedWaterFlowRate, Speed6ReferenceUnitWaterPumpInputPowerAtRatedConditions, Speed6TotalWHCapacityFunctionofTemperatureCurveName, Speed6TotalWHCapacityFunctionofAirFlowFractionCurveName, Speed6TotalWHCapacityFunctionofWaterFlowFractionCurveName, Speed6COPFunctionofTemperatureCurveName, Speed6COPFunctionofAirFlowFractionCurveName, Speed6COPFunctionofWaterFlowFractionCurveName, RatedWaterHeatingCapacityatSpeed7, RatedWaterHeatingCOPatSpeed7, RatedSensibleHeatRatioatSpeed7, Speed7ReferenceUnitRatedAirFlowRate, Speed7ReferenceUnitRatedWaterFlowRate, Speed7ReferenceUnitWaterPumpInputPowerAtRatedConditions, Speed7TotalWHCapacityFunctionofTemperatureCurveName, Speed7TotalWHCapacityFunctionofAirFlowFractionCurveName, Speed7TotalWHCapacityFunctionofWaterFlowFractionCurveName, Speed7COPFunctionofTemperatureCurveName, Speed7COPFunctionofAirFlowFractionCurveName, Speed7COPFunctionofWaterFlowFractionCurveName, RatedWaterHeatingCapacityatSpeed8, RatedWaterHeatingCOPatSpeed8, RatedSensibleHeatRatioatSpeed8, Speed8ReferenceUnitRatedAirFlowRate, Speed8ReferenceUnitRatedWaterFlowRate, Speed8ReferenceUnitWaterPumpInputPowerAtRatedConditions, Speed8TotalWHCapacityFunctionofTemperatureCurveName, Speed8TotalWHCapacityFunctionofAirFlowFractionCurveName, Speed8TotalWHCapacityFunctionofWaterFlowFractionCurveName, Speed8COPFunctionofTemperatureCurveName, Speed8COPFunctionofAirFlowFractionCurveName, Speed8COPFunctionofWaterFlowFractionCurveName, RatedWaterHeatingCapacityatSpeed9, RatedWaterHeatingCOPatSpeed9, RatedSensibleHeatRatioatSpeed9, Speed9ReferenceUnitRatedAirFlowRate, Speed9ReferenceUnitRatedWaterFlowRate, Speed9ReferenceUnitWaterPumpInputPowerAtRatedConditions, Speed9TotalWHCapacityFunctionofTemperatureCurveName, Speed9TotalWHCapacityFunctionofAirFlowFractionCurveName, Speed9TotalWHCapacityFunctionofWaterFlowFractionCurveName, Speed9COPFunctionofTemperatureCurveName, Speed9COPFunctionofAirFlowFractionCurveName, Speed9COPFunctionofWaterFlowFractionCurveName, RatedWaterHeatingCapacityatSpeed10, RatedWaterHeatingCOPatSpeed10, RatedSensibleHeatRatioatSpeed10, Speed10ReferenceUnitRatedAirFlowRate, Speed10ReferenceUnitRatedWaterFlowRate, Speed10ReferenceUnitWaterPumpInputPowerAtRatedConditions, Speed10TotalWHCapacityFunctionofTemperatureCurveName, Speed10TotalWHCapacityFunctionofAirFlowFractionCurveName, Speed10TotalWHCapacityFunctionofWaterFlowFractionCurveName, Speed10COPFunctionofTemperatureCurveName, Speed10COPFunctionofAirFlowFractionCurveName, Speed10COPFunctionofWaterFlowFractionCurveName,   };
  Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields()
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>(Name) {} 
  Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields(const std::string &t_name) 
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>(t_name) {} 
  Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields(int t_value) 
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields>::value()); }
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
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, "MaximumAmbientTemperatureforCrankcaseHeaterOperation", "Maximum Ambient Temperature for Crankcase Heater Operation"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::EvaporatorAirTemperatureTypeforCurveObjects, "EvaporatorAirTemperatureTypeforCurveObjects", "Evaporator Air Temperature Type for Curve Objects"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacityatSpeed1, "RatedWaterHeatingCapacityatSpeed1", "Rated Water Heating Capacity at Speed 1"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCOPatSpeed1, "RatedWaterHeatingCOPatSpeed1", "Rated Water Heating COP at Speed 1"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedSensibleHeatRatioatSpeed1, "RatedSensibleHeatRatioatSpeed1", "Rated Sensible Heat Ratio at Speed 1"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed1ReferenceUnitRatedAirFlowRate, "Speed1ReferenceUnitRatedAirFlowRate", "Speed 1 Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed1ReferenceUnitRatedWaterFlowRate, "Speed1ReferenceUnitRatedWaterFlowRate", "Speed 1 Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed1ReferenceUnitWaterPumpInputPowerAtRatedConditions, "Speed1ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed 1 Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed1TotalWHCapacityFunctionofTemperatureCurveName, "Speed1TotalWHCapacityFunctionofTemperatureCurveName", "Speed 1 Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed1TotalWHCapacityFunctionofAirFlowFractionCurveName, "Speed1TotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed 1 Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed1TotalWHCapacityFunctionofWaterFlowFractionCurveName, "Speed1TotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed 1 Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed1COPFunctionofTemperatureCurveName, "Speed1COPFunctionofTemperatureCurveName", "Speed 1 COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed1COPFunctionofAirFlowFractionCurveName, "Speed1COPFunctionofAirFlowFractionCurveName", "Speed 1 COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed1COPFunctionofWaterFlowFractionCurveName, "Speed1COPFunctionofWaterFlowFractionCurveName", "Speed 1 COP Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacityatSpeed2, "RatedWaterHeatingCapacityatSpeed2", "Rated Water Heating Capacity at Speed 2"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCOPatSpeed2, "RatedWaterHeatingCOPatSpeed2", "Rated Water Heating COP at Speed 2"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedSensibleHeatRatioatSpeed2, "RatedSensibleHeatRatioatSpeed2", "Rated Sensible Heat Ratio at Speed 2"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed2ReferenceUnitRatedAirFlowRate, "Speed2ReferenceUnitRatedAirFlowRate", "Speed 2 Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed2ReferenceUnitRatedWaterFlowRate, "Speed2ReferenceUnitRatedWaterFlowRate", "Speed 2 Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed2ReferenceUnitWaterPumpInputPowerAtRatedConditions, "Speed2ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed 2 Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed2TotalWHCapacityFunctionofTemperatureCurveName, "Speed2TotalWHCapacityFunctionofTemperatureCurveName", "Speed 2 Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed2TotalWHCapacityFunctionofAirFlowFractionCurveName, "Speed2TotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed 2 Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed2TotalWHCapacityFunctionofWaterFlowFractionCurveName, "Speed2TotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed 2 Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed2COPFunctionofTemperatureCurveName, "Speed2COPFunctionofTemperatureCurveName", "Speed 2 COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed2COPFunctionofAirFlowFractionCurveName, "Speed2COPFunctionofAirFlowFractionCurveName", "Speed 2 COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed2COPFunctionofWaterFlowFractionCurveName, "Speed2COPFunctionofWaterFlowFractionCurveName", "Speed 2 COP Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacityatspeed3, "RatedWaterHeatingCapacityatspeed3", "Rated Water Heating Capacity at speed 3"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCOPatSpeed3, "RatedWaterHeatingCOPatSpeed3", "Rated Water Heating COP at Speed 3"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedSensibleHeatRatioatSpeed3, "RatedSensibleHeatRatioatSpeed3", "Rated Sensible Heat Ratio at Speed 3"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed3ReferenceUnitRatedAirFlowRate, "Speed3ReferenceUnitRatedAirFlowRate", "Speed 3 Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed3ReferenceUnitRatedWaterFlowRate, "Speed3ReferenceUnitRatedWaterFlowRate", "Speed 3 Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed3ReferenceUnitWaterPumpInputPowerAtRatedConditions, "Speed3ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed 3 Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed3TotalWHCapacityFunctionofTemperatureCurveName, "Speed3TotalWHCapacityFunctionofTemperatureCurveName", "Speed 3 Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed3TotalWHCapacityFunctionofAirFlowFractionCurveName, "Speed3TotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed 3 Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed3TotalWHCapacityFunctionofWaterFlowFractionCurveName, "Speed3TotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed 3 Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed3COPFunctionofTemperatureCurveName, "Speed3COPFunctionofTemperatureCurveName", "Speed 3 COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed3COPFunctionofAirFlowFractionCurveName, "Speed3COPFunctionofAirFlowFractionCurveName", "Speed 3 COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed3COPFunctionofWaterFlowFractionCurveName, "Speed3COPFunctionofWaterFlowFractionCurveName", "Speed 3 COP Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacityatSpeed4, "RatedWaterHeatingCapacityatSpeed4", "Rated Water Heating Capacity at Speed 4"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCOPatSpeed4, "RatedWaterHeatingCOPatSpeed4", "Rated Water Heating COP at Speed 4"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedSensibleHeatRatioatSpeed4, "RatedSensibleHeatRatioatSpeed4", "Rated Sensible Heat Ratio at Speed 4"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed4ReferenceUnitRatedAirFlowRate, "Speed4ReferenceUnitRatedAirFlowRate", "Speed 4 Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed4ReferenceUnitRatedWaterFlowRate, "Speed4ReferenceUnitRatedWaterFlowRate", "Speed 4 Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed4ReferenceUnitWaterPumpInputPowerAtRatedConditions, "Speed4ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed 4 Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed4TotalWHCapacityFunctionofTemperatureCurveName, "Speed4TotalWHCapacityFunctionofTemperatureCurveName", "Speed 4 Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed4TotalWHCapacityFunctionofAirFlowFractionCurveName, "Speed4TotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed 4 Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed4TotalWHCapacityFunctionofWaterFlowFractionCurveName, "Speed4TotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed 4 Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed4COPFunctionofTemperatureCurveName, "Speed4COPFunctionofTemperatureCurveName", "Speed 4 COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed4COPFunctionofAirFlowFractionCurveName, "Speed4COPFunctionofAirFlowFractionCurveName", "Speed 4 COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed4COPFunctionofWaterFlowFractionCurveName, "Speed4COPFunctionofWaterFlowFractionCurveName", "Speed 4 COP Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacityatSpeed5, "RatedWaterHeatingCapacityatSpeed5", "Rated Water Heating Capacity at Speed 5"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCOPatSpeed5, "RatedWaterHeatingCOPatSpeed5", "Rated Water Heating COP at Speed 5"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedSensibleHeatRatioatSpeed5, "RatedSensibleHeatRatioatSpeed5", "Rated Sensible Heat Ratio at Speed 5"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed5ReferenceUnitRatedAirFlowRate, "Speed5ReferenceUnitRatedAirFlowRate", "Speed 5 Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed5ReferenceUnitRatedWaterFlowRate, "Speed5ReferenceUnitRatedWaterFlowRate", "Speed 5 Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed5ReferenceUnitWaterPumpInputPowerAtRatedConditions, "Speed5ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed 5 Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed5TotalWHCapacityFunctionofTemperatureCurveName, "Speed5TotalWHCapacityFunctionofTemperatureCurveName", "Speed 5 Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed5TotalWHCapacityFunctionofAirFlowFractionCurveName, "Speed5TotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed 5 Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed5TotalWHCapacityFunctionofWaterFlowFractionCurveName, "Speed5TotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed 5 Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed5COPFunctionofTemperatureCurveName, "Speed5COPFunctionofTemperatureCurveName", "Speed 5 COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed5COPFunctionofAirFlowFractionCurveName, "Speed5COPFunctionofAirFlowFractionCurveName", "Speed 5 COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed5COPFunctionofWaterFlowFractionCurveName, "Speed5COPFunctionofWaterFlowFractionCurveName", "Speed 5 COP Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacityatSpeed6, "RatedWaterHeatingCapacityatSpeed6", "Rated Water Heating Capacity at Speed 6"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCOPatSpeed6, "RatedWaterHeatingCOPatSpeed6", "Rated Water Heating COP at Speed 6"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedSensibleHeatRatioatSpeed6, "RatedSensibleHeatRatioatSpeed6", "Rated Sensible Heat Ratio at Speed 6"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed6ReferenceUnitRatedAirFlowRate, "Speed6ReferenceUnitRatedAirFlowRate", "Speed 6 Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed6ReferenceUnitRatedWaterFlowRate, "Speed6ReferenceUnitRatedWaterFlowRate", "Speed 6 Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed6ReferenceUnitWaterPumpInputPowerAtRatedConditions, "Speed6ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed 6 Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed6TotalWHCapacityFunctionofTemperatureCurveName, "Speed6TotalWHCapacityFunctionofTemperatureCurveName", "Speed 6 Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed6TotalWHCapacityFunctionofAirFlowFractionCurveName, "Speed6TotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed 6 Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed6TotalWHCapacityFunctionofWaterFlowFractionCurveName, "Speed6TotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed 6 Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed6COPFunctionofTemperatureCurveName, "Speed6COPFunctionofTemperatureCurveName", "Speed 6 COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed6COPFunctionofAirFlowFractionCurveName, "Speed6COPFunctionofAirFlowFractionCurveName", "Speed 6 COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed6COPFunctionofWaterFlowFractionCurveName, "Speed6COPFunctionofWaterFlowFractionCurveName", "Speed 6 COP Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacityatSpeed7, "RatedWaterHeatingCapacityatSpeed7", "Rated Water Heating Capacity at Speed 7"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCOPatSpeed7, "RatedWaterHeatingCOPatSpeed7", "Rated Water Heating COP at Speed 7"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedSensibleHeatRatioatSpeed7, "RatedSensibleHeatRatioatSpeed7", "Rated Sensible Heat Ratio at Speed 7"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed7ReferenceUnitRatedAirFlowRate, "Speed7ReferenceUnitRatedAirFlowRate", "Speed 7 Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed7ReferenceUnitRatedWaterFlowRate, "Speed7ReferenceUnitRatedWaterFlowRate", "Speed 7 Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed7ReferenceUnitWaterPumpInputPowerAtRatedConditions, "Speed7ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed 7 Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed7TotalWHCapacityFunctionofTemperatureCurveName, "Speed7TotalWHCapacityFunctionofTemperatureCurveName", "Speed 7 Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed7TotalWHCapacityFunctionofAirFlowFractionCurveName, "Speed7TotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed 7 Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed7TotalWHCapacityFunctionofWaterFlowFractionCurveName, "Speed7TotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed 7 Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed7COPFunctionofTemperatureCurveName, "Speed7COPFunctionofTemperatureCurveName", "Speed 7 COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed7COPFunctionofAirFlowFractionCurveName, "Speed7COPFunctionofAirFlowFractionCurveName", "Speed 7 COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed7COPFunctionofWaterFlowFractionCurveName, "Speed7COPFunctionofWaterFlowFractionCurveName", "Speed 7 COP Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacityatSpeed8, "RatedWaterHeatingCapacityatSpeed8", "Rated Water Heating Capacity at Speed 8"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCOPatSpeed8, "RatedWaterHeatingCOPatSpeed8", "Rated Water Heating COP at Speed 8"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedSensibleHeatRatioatSpeed8, "RatedSensibleHeatRatioatSpeed8", "Rated Sensible Heat Ratio at Speed 8"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed8ReferenceUnitRatedAirFlowRate, "Speed8ReferenceUnitRatedAirFlowRate", "Speed 8 Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed8ReferenceUnitRatedWaterFlowRate, "Speed8ReferenceUnitRatedWaterFlowRate", "Speed 8 Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed8ReferenceUnitWaterPumpInputPowerAtRatedConditions, "Speed8ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed 8 Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed8TotalWHCapacityFunctionofTemperatureCurveName, "Speed8TotalWHCapacityFunctionofTemperatureCurveName", "Speed 8 Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed8TotalWHCapacityFunctionofAirFlowFractionCurveName, "Speed8TotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed 8 Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed8TotalWHCapacityFunctionofWaterFlowFractionCurveName, "Speed8TotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed 8 Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed8COPFunctionofTemperatureCurveName, "Speed8COPFunctionofTemperatureCurveName", "Speed 8 COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed8COPFunctionofAirFlowFractionCurveName, "Speed8COPFunctionofAirFlowFractionCurveName", "Speed 8 COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed8COPFunctionofWaterFlowFractionCurveName, "Speed8COPFunctionofWaterFlowFractionCurveName", "Speed 8 COP Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacityatSpeed9, "RatedWaterHeatingCapacityatSpeed9", "Rated Water Heating Capacity at Speed 9"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCOPatSpeed9, "RatedWaterHeatingCOPatSpeed9", "Rated Water Heating COP at Speed 9"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedSensibleHeatRatioatSpeed9, "RatedSensibleHeatRatioatSpeed9", "Rated Sensible Heat Ratio at Speed 9"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed9ReferenceUnitRatedAirFlowRate, "Speed9ReferenceUnitRatedAirFlowRate", "Speed 9 Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed9ReferenceUnitRatedWaterFlowRate, "Speed9ReferenceUnitRatedWaterFlowRate", "Speed 9 Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed9ReferenceUnitWaterPumpInputPowerAtRatedConditions, "Speed9ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed 9 Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed9TotalWHCapacityFunctionofTemperatureCurveName, "Speed9TotalWHCapacityFunctionofTemperatureCurveName", "Speed 9 Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed9TotalWHCapacityFunctionofAirFlowFractionCurveName, "Speed9TotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed 9 Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed9TotalWHCapacityFunctionofWaterFlowFractionCurveName, "Speed9TotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed 9 Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed9COPFunctionofTemperatureCurveName, "Speed9COPFunctionofTemperatureCurveName", "Speed 9 COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed9COPFunctionofAirFlowFractionCurveName, "Speed9COPFunctionofAirFlowFractionCurveName", "Speed 9 COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed9COPFunctionofWaterFlowFractionCurveName, "Speed9COPFunctionofWaterFlowFractionCurveName", "Speed 9 COP Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCapacityatSpeed10, "RatedWaterHeatingCapacityatSpeed10", "Rated Water Heating Capacity at Speed 10"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedWaterHeatingCOPatSpeed10, "RatedWaterHeatingCOPatSpeed10", "Rated Water Heating COP at Speed 10"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::RatedSensibleHeatRatioatSpeed10, "RatedSensibleHeatRatioatSpeed10", "Rated Sensible Heat Ratio at Speed 10"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed10ReferenceUnitRatedAirFlowRate, "Speed10ReferenceUnitRatedAirFlowRate", "Speed 10 Reference Unit Rated Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed10ReferenceUnitRatedWaterFlowRate, "Speed10ReferenceUnitRatedWaterFlowRate", "Speed 10 Reference Unit Rated Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed10ReferenceUnitWaterPumpInputPowerAtRatedConditions, "Speed10ReferenceUnitWaterPumpInputPowerAtRatedConditions", "Speed 10 Reference Unit Water Pump Input Power At Rated Conditions"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed10TotalWHCapacityFunctionofTemperatureCurveName, "Speed10TotalWHCapacityFunctionofTemperatureCurveName", "Speed 10 Total WH Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed10TotalWHCapacityFunctionofAirFlowFractionCurveName, "Speed10TotalWHCapacityFunctionofAirFlowFractionCurveName", "Speed 10 Total WH Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed10TotalWHCapacityFunctionofWaterFlowFractionCurveName, "Speed10TotalWHCapacityFunctionofWaterFlowFractionCurveName", "Speed 10 Total WH Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed10COPFunctionofTemperatureCurveName, "Speed10COPFunctionofTemperatureCurveName", "Speed 10 COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed10COPFunctionofAirFlowFractionCurveName, "Speed10COPFunctionofAirFlowFractionCurveName", "Speed 10 COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_VariableSpeedFields::Speed10COPFunctionofWaterFlowFractionCurveName, "Speed10COPFunctionofWaterFlowFractionCurveName", "Speed 10 COP Function of Water Flow Fraction Curve Name"},
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

} // openstudio

#endif // UTILITIES_IDD_COIL_WATERHEATING_AIRTOWATERHEATPUMP_VARIABLESPEED_FIELDENUMS_HXX
