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

#ifndef UTILITIES_IDD_COIL_WATERHEATING_AIRTOWATERHEATPUMP_PUMPED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_WATERHEATING_AIRTOWATERHEATPUMP_PUMPED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_WaterHeating_AirToWaterHeatPump_PumpedFields
 *  \brief Enumeration of Coil:WaterHeating:AirToWaterHeatPump:Pumped's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_WaterHeating_AirToWaterHeatPump_PumpedFields, )
#else
class Coil_WaterHeating_AirToWaterHeatPump_PumpedFields: public ::EnumBase<Coil_WaterHeating_AirToWaterHeatPump_PumpedFields> {
 public: 
  enum domain 
  {
Name, RatedHeatingCapacity, RatedCOP, RatedSensibleHeatRatio, RatedEvaporatorInletAirDryBulbTemperature, RatedEvaporatorInletAirWetBulbTemperature, RatedCondenserInletWaterTemperature, RatedEvaporatorAirFlowRate, RatedCondenserWaterFlowRate, EvaporatorFanPowerIncludedinRatedCOP, CondenserPumpPowerIncludedinRatedCOP, CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, CondenserWaterPumpPower, FractionofCondenserPumpHeattoWater, EvaporatorAirInletNodeName, EvaporatorAirOutletNodeName, CondenserWaterInletNodeName, CondenserWaterOutletNodeName, CrankcaseHeaterCapacity, MaximumAmbientTemperatureforCrankcaseHeaterOperation, EvaporatorAirTemperatureTypeforCurveObjects, HeatingCapacityFunctionofTemperatureCurveName, HeatingCapacityFunctionofAirFlowFractionCurveName, HeatingCapacityFunctionofWaterFlowFractionCurveName, HeatingCOPFunctionofTemperatureCurveName, HeatingCOPFunctionofAirFlowFractionCurveName, HeatingCOPFunctionofWaterFlowFractionCurveName, PartLoadFractionCorrelationCurveName,   };
  Coil_WaterHeating_AirToWaterHeatPump_PumpedFields()
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_PumpedFields>(Name) {} 
  Coil_WaterHeating_AirToWaterHeatPump_PumpedFields(const std::string &t_name) 
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_PumpedFields>(t_name) {} 
  Coil_WaterHeating_AirToWaterHeatPump_PumpedFields(int t_value) 
   : EnumBase<Coil_WaterHeating_AirToWaterHeatPump_PumpedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_WaterHeating_AirToWaterHeatPump_PumpedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_WaterHeating_AirToWaterHeatPump_PumpedFields>::value()); }
   private:
    friend class EnumBase<Coil_WaterHeating_AirToWaterHeatPump_PumpedFields>;
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
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::Name, "Name", "Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedHeatingCapacity, "RatedHeatingCapacity", "Rated Heating Capacity"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCOP, "RatedCOP", "Rated COP"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedSensibleHeatRatio, "RatedSensibleHeatRatio", "Rated Sensible Heat Ratio"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorInletAirDryBulbTemperature, "RatedEvaporatorInletAirDryBulbTemperature", "Rated Evaporator Inlet Air Dry-Bulb Temperature"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorInletAirWetBulbTemperature, "RatedEvaporatorInletAirWetBulbTemperature", "Rated Evaporator Inlet Air Wet-Bulb Temperature"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserInletWaterTemperature, "RatedCondenserInletWaterTemperature", "Rated Condenser Inlet Water Temperature"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedEvaporatorAirFlowRate, "RatedEvaporatorAirFlowRate", "Rated Evaporator Air Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::RatedCondenserWaterFlowRate, "RatedCondenserWaterFlowRate", "Rated Condenser Water Flow Rate"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorFanPowerIncludedinRatedCOP, "EvaporatorFanPowerIncludedinRatedCOP", "Evaporator Fan Power Included in Rated COP"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserPumpPowerIncludedinRatedCOP, "CondenserPumpPowerIncludedinRatedCOP", "Condenser Pump Power Included in Rated COP"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP, "CondenserPumpHeatIncludedinRatedHeatingCapacityandRatedCOP", "Condenser Pump Heat Included in Rated Heating Capacity and Rated COP"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterPumpPower, "CondenserWaterPumpPower", "Condenser Water Pump Power"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::FractionofCondenserPumpHeattoWater, "FractionofCondenserPumpHeattoWater", "Fraction of Condenser Pump Heat to Water"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirInletNodeName, "EvaporatorAirInletNodeName", "Evaporator Air Inlet Node Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirOutletNodeName, "EvaporatorAirOutletNodeName", "Evaporator Air Outlet Node Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterInletNodeName, "CondenserWaterInletNodeName", "Condenser Water Inlet Node Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CondenserWaterOutletNodeName, "CondenserWaterOutletNodeName", "Condenser Water Outlet Node Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::MaximumAmbientTemperatureforCrankcaseHeaterOperation, "MaximumAmbientTemperatureforCrankcaseHeaterOperation", "Maximum Ambient Temperature for Crankcase Heater Operation"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::EvaporatorAirTemperatureTypeforCurveObjects, "EvaporatorAirTemperatureTypeforCurveObjects", "Evaporator Air Temperature Type for Curve Objects"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCapacityFunctionofTemperatureCurveName, "HeatingCapacityFunctionofTemperatureCurveName", "Heating Capacity Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCapacityFunctionofAirFlowFractionCurveName, "HeatingCapacityFunctionofAirFlowFractionCurveName", "Heating Capacity Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCapacityFunctionofWaterFlowFractionCurveName, "HeatingCapacityFunctionofWaterFlowFractionCurveName", "Heating Capacity Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCOPFunctionofTemperatureCurveName, "HeatingCOPFunctionofTemperatureCurveName", "Heating COP Function of Temperature Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCOPFunctionofAirFlowFractionCurveName, "HeatingCOPFunctionofAirFlowFractionCurveName", "Heating COP Function of Air Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::HeatingCOPFunctionofWaterFlowFractionCurveName, "HeatingCOPFunctionofWaterFlowFractionCurveName", "Heating COP Function of Water Flow Fraction Curve Name"},
{ Coil_WaterHeating_AirToWaterHeatPump_PumpedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_WaterHeating_AirToWaterHeatPump_PumpedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_WaterHeating_AirToWaterHeatPump_PumpedFields> OptionalCoil_WaterHeating_AirToWaterHeatPump_PumpedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_WATERHEATING_AIRTOWATERHEATPUMP_PUMPED_FIELDENUMS_HXX
