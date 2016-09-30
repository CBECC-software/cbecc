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

#ifndef UTILITIES_IDD_COIL_COOLING_DX_TWOSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_DX_TWOSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_DX_TwoSpeedFields
 *  \brief Enumeration of Coil:Cooling:DX:TwoSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_DX_TwoSpeedFields, )
#else
class Coil_Cooling_DX_TwoSpeedFields: public ::EnumBase<Coil_Cooling_DX_TwoSpeedFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, HighSpeedGrossRatedTotalCoolingCapacity, HighSpeedRatedSensibleHeatRatio, HighSpeedGrossRatedCoolingCOP, HighSpeedRatedAirFlowRate, UnitInternalStaticAirPressure, AirInletNodeName, AirOutletNodeName, TotalCoolingCapacityFunctionofTemperatureCurveName, TotalCoolingCapacityFunctionofFlowFractionCurveName, EnergyInputRatioFunctionofTemperatureCurveName, EnergyInputRatioFunctionofFlowFractionCurveName, PartLoadFractionCorrelationCurveName, LowSpeedGrossRatedTotalCoolingCapacity, LowSpeedGrossRatedSensibleHeatRatio, LowSpeedGrossRatedCoolingCOP, LowSpeedRatedAirFlowRate, LowSpeedTotalCoolingCapacityFunctionofTemperatureCurveName, LowSpeedEnergyInputRatioFunctionofTemperatureCurveName, CondenserAirInletNodeName, CondenserType, HighSpeedEvaporativeCondenserEffectiveness, HighSpeedEvaporativeCondenserAirFlowRate, HighSpeedEvaporativeCondenserPumpRatedPowerConsumption, LowSpeedEvaporativeCondenserEffectiveness, LowSpeedEvaporativeCondenserAirFlowRate, LowSpeedEvaporativeCondenserPumpRatedPowerConsumption, SupplyWaterStorageTankName, CondensateCollectionWaterStorageTankName, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, SensibleHeatRatioFunctionofTemperatureCurveName, SensibleHeatRatioFunctionofFlowFractionCurveName, LowSpeedSensibleHeatRatioFunctionofTemperatureCurveName, LowSpeedSensibleHeatRatioFunctionofFlowFractionCurveName, ZoneNameforCondenserPlacement,   };
  Coil_Cooling_DX_TwoSpeedFields()
   : EnumBase<Coil_Cooling_DX_TwoSpeedFields>(Name) {} 
  Coil_Cooling_DX_TwoSpeedFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_TwoSpeedFields>(t_name) {} 
  Coil_Cooling_DX_TwoSpeedFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_TwoSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_TwoSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_TwoSpeedFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_TwoSpeedFields>;
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
{ Coil_Cooling_DX_TwoSpeedFields::Name, "Name", "Name"},
{ Coil_Cooling_DX_TwoSpeedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedTotalCoolingCapacity, "HighSpeedGrossRatedTotalCoolingCapacity", "High Speed Gross Rated Total Cooling Capacity"},
{ Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedSensibleHeatRatio, "HighSpeedRatedSensibleHeatRatio", "High Speed Rated Sensible Heat Ratio"},
{ Coil_Cooling_DX_TwoSpeedFields::HighSpeedGrossRatedCoolingCOP, "HighSpeedGrossRatedCoolingCOP", "High Speed Gross Rated Cooling COP"},
{ Coil_Cooling_DX_TwoSpeedFields::HighSpeedRatedAirFlowRate, "HighSpeedRatedAirFlowRate", "High Speed Rated Air Flow Rate"},
{ Coil_Cooling_DX_TwoSpeedFields::UnitInternalStaticAirPressure, "UnitInternalStaticAirPressure", "Unit Internal Static Air Pressure"},
{ Coil_Cooling_DX_TwoSpeedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Cooling_DX_TwoSpeedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Cooling_DX_TwoSpeedFields::TotalCoolingCapacityFunctionofTemperatureCurveName, "TotalCoolingCapacityFunctionofTemperatureCurveName", "Total Cooling Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::TotalCoolingCapacityFunctionofFlowFractionCurveName, "TotalCoolingCapacityFunctionofFlowFractionCurveName", "Total Cooling Capacity Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, "EnergyInputRatioFunctionofTemperatureCurveName", "Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName, "EnergyInputRatioFunctionofFlowFractionCurveName", "Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedTotalCoolingCapacity, "LowSpeedGrossRatedTotalCoolingCapacity", "Low Speed Gross Rated Total Cooling Capacity"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedSensibleHeatRatio, "LowSpeedGrossRatedSensibleHeatRatio", "Low Speed Gross Rated Sensible Heat Ratio"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedGrossRatedCoolingCOP, "LowSpeedGrossRatedCoolingCOP", "Low Speed Gross Rated Cooling COP"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedRatedAirFlowRate, "LowSpeedRatedAirFlowRate", "Low Speed Rated Air Flow Rate"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedTotalCoolingCapacityFunctionofTemperatureCurveName, "LowSpeedTotalCoolingCapacityFunctionofTemperatureCurveName", "Low Speed Total Cooling Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedEnergyInputRatioFunctionofTemperatureCurveName, "LowSpeedEnergyInputRatioFunctionofTemperatureCurveName", "Low Speed Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::CondenserAirInletNodeName, "CondenserAirInletNodeName", "Condenser Air Inlet Node Name"},
{ Coil_Cooling_DX_TwoSpeedFields::CondenserType, "CondenserType", "Condenser Type"},
{ Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserEffectiveness, "HighSpeedEvaporativeCondenserEffectiveness", "High Speed Evaporative Condenser Effectiveness"},
{ Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserAirFlowRate, "HighSpeedEvaporativeCondenserAirFlowRate", "High Speed Evaporative Condenser Air Flow Rate"},
{ Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserPumpRatedPowerConsumption, "HighSpeedEvaporativeCondenserPumpRatedPowerConsumption", "High Speed Evaporative Condenser Pump Rated Power Consumption"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserEffectiveness, "LowSpeedEvaporativeCondenserEffectiveness", "Low Speed Evaporative Condenser Effectiveness"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserAirFlowRate, "LowSpeedEvaporativeCondenserAirFlowRate", "Low Speed Evaporative Condenser Air Flow Rate"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserPumpRatedPowerConsumption, "LowSpeedEvaporativeCondenserPumpRatedPowerConsumption", "Low Speed Evaporative Condenser Pump Rated Power Consumption"},
{ Coil_Cooling_DX_TwoSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ Coil_Cooling_DX_TwoSpeedFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
{ Coil_Cooling_DX_TwoSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Coil_Cooling_DX_TwoSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Coil_Cooling_DX_TwoSpeedFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ Coil_Cooling_DX_TwoSpeedFields::SensibleHeatRatioFunctionofTemperatureCurveName, "SensibleHeatRatioFunctionofTemperatureCurveName", "Sensible Heat Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::SensibleHeatRatioFunctionofFlowFractionCurveName, "SensibleHeatRatioFunctionofFlowFractionCurveName", "Sensible Heat Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedSensibleHeatRatioFunctionofTemperatureCurveName, "LowSpeedSensibleHeatRatioFunctionofTemperatureCurveName", "Low Speed Sensible Heat Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::LowSpeedSensibleHeatRatioFunctionofFlowFractionCurveName, "LowSpeedSensibleHeatRatioFunctionofFlowFractionCurveName", "Low Speed Sensible Heat Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_TwoSpeedFields::ZoneNameforCondenserPlacement, "ZoneNameforCondenserPlacement", "Zone Name for Condenser Placement"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_TwoSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_TwoSpeedFields> OptionalCoil_Cooling_DX_TwoSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_DX_TWOSPEED_FIELDENUMS_HXX
