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

#ifndef UTILITIES_IDD_COIL_COOLING_DX_SINGLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_DX_SINGLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_DX_SingleSpeedFields
 *  \brief Enumeration of Coil:Cooling:DX:SingleSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_DX_SingleSpeedFields, )
#else
class Coil_Cooling_DX_SingleSpeedFields: public ::EnumBase<Coil_Cooling_DX_SingleSpeedFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, GrossRatedTotalCoolingCapacity, GrossRatedSensibleHeatRatio, GrossRatedCoolingCOP, RatedAirFlowRate, RatedEvaporatorFanPowerPerVolumeFlowRate, AirInletNodeName, AirOutletNodeName, TotalCoolingCapacityFunctionofTemperatureCurveName, TotalCoolingCapacityFunctionofFlowFractionCurveName, EnergyInputRatioFunctionofTemperatureCurveName, EnergyInputRatioFunctionofFlowFractionCurveName, PartLoadFractionCorrelationCurveName, NominalTimeforCondensateRemovaltoBegin, RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, MaximumCyclingRate, LatentCapacityTimeConstant, CondenserAirInletNodeName, CondenserType, EvaporativeCondenserEffectiveness, EvaporativeCondenserAirFlowRate, EvaporativeCondenserPumpRatedPowerConsumption, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, SupplyWaterStorageTankName, CondensateCollectionWaterStorageTankName, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, SensibleHeatRatioFunctionofTemperatureCurveName, SensibleHeatRatioFunctionofFlowFractionCurveName, ReportASHRAEStandard127PerformanceRatings, ZoneNameforCondenserPlacement,   };
  Coil_Cooling_DX_SingleSpeedFields()
   : EnumBase<Coil_Cooling_DX_SingleSpeedFields>(Name) {} 
  Coil_Cooling_DX_SingleSpeedFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_SingleSpeedFields>(t_name) {} 
  Coil_Cooling_DX_SingleSpeedFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_SingleSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_SingleSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_SingleSpeedFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_SingleSpeedFields>;
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
{ Coil_Cooling_DX_SingleSpeedFields::Name, "Name", "Name"},
{ Coil_Cooling_DX_SingleSpeedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Cooling_DX_SingleSpeedFields::GrossRatedTotalCoolingCapacity, "GrossRatedTotalCoolingCapacity", "Gross Rated Total Cooling Capacity"},
{ Coil_Cooling_DX_SingleSpeedFields::GrossRatedSensibleHeatRatio, "GrossRatedSensibleHeatRatio", "Gross Rated Sensible Heat Ratio"},
{ Coil_Cooling_DX_SingleSpeedFields::GrossRatedCoolingCOP, "GrossRatedCoolingCOP", "Gross Rated Cooling COP"},
{ Coil_Cooling_DX_SingleSpeedFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ Coil_Cooling_DX_SingleSpeedFields::RatedEvaporatorFanPowerPerVolumeFlowRate, "RatedEvaporatorFanPowerPerVolumeFlowRate", "Rated Evaporator Fan Power Per Volume Flow Rate"},
{ Coil_Cooling_DX_SingleSpeedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Cooling_DX_SingleSpeedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Cooling_DX_SingleSpeedFields::TotalCoolingCapacityFunctionofTemperatureCurveName, "TotalCoolingCapacityFunctionofTemperatureCurveName", "Total Cooling Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeedFields::TotalCoolingCapacityFunctionofFlowFractionCurveName, "TotalCoolingCapacityFunctionofFlowFractionCurveName", "Total Cooling Capacity Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, "EnergyInputRatioFunctionofTemperatureCurveName", "Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName, "EnergyInputRatioFunctionofFlowFractionCurveName", "Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ Coil_Cooling_DX_SingleSpeedFields::NominalTimeforCondensateRemovaltoBegin, "NominalTimeforCondensateRemovaltoBegin", "Nominal Time for Condensate Removal to Begin"},
{ Coil_Cooling_DX_SingleSpeedFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, "RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity", "Ratio of Initial Moisture Evaporation Rate and Steady State Latent Capacity"},
{ Coil_Cooling_DX_SingleSpeedFields::MaximumCyclingRate, "MaximumCyclingRate", "Maximum Cycling Rate"},
{ Coil_Cooling_DX_SingleSpeedFields::LatentCapacityTimeConstant, "LatentCapacityTimeConstant", "Latent Capacity Time Constant"},
{ Coil_Cooling_DX_SingleSpeedFields::CondenserAirInletNodeName, "CondenserAirInletNodeName", "Condenser Air Inlet Node Name"},
{ Coil_Cooling_DX_SingleSpeedFields::CondenserType, "CondenserType", "Condenser Type"},
{ Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserAirFlowRate, "EvaporativeCondenserAirFlowRate", "Evaporative Condenser Air Flow Rate"},
{ Coil_Cooling_DX_SingleSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption, "EvaporativeCondenserPumpRatedPowerConsumption", "Evaporative Condenser Pump Rated Power Consumption"},
{ Coil_Cooling_DX_SingleSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_Cooling_DX_SingleSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ Coil_Cooling_DX_SingleSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ Coil_Cooling_DX_SingleSpeedFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
{ Coil_Cooling_DX_SingleSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Coil_Cooling_DX_SingleSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Coil_Cooling_DX_SingleSpeedFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ Coil_Cooling_DX_SingleSpeedFields::SensibleHeatRatioFunctionofTemperatureCurveName, "SensibleHeatRatioFunctionofTemperatureCurveName", "Sensible Heat Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_SingleSpeedFields::SensibleHeatRatioFunctionofFlowFractionCurveName, "SensibleHeatRatioFunctionofFlowFractionCurveName", "Sensible Heat Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_SingleSpeedFields::ReportASHRAEStandard127PerformanceRatings, "ReportASHRAEStandard127PerformanceRatings", "Report ASHRAE Standard 127 Performance Ratings"},
{ Coil_Cooling_DX_SingleSpeedFields::ZoneNameforCondenserPlacement, "ZoneNameforCondenserPlacement", "Zone Name for Condenser Placement"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_SingleSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_SingleSpeedFields> OptionalCoil_Cooling_DX_SingleSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_DX_SINGLESPEED_FIELDENUMS_HXX
