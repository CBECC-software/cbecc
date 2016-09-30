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

#ifndef UTILITIES_IDD_OS_COIL_COOLING_DX_TWOSPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_COOLING_DX_TWOSPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Cooling_DX_TwoSpeedFields
 *  \brief Enumeration of OS:Coil:Cooling:DX:TwoSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Cooling_DX_TwoSpeedFields, )
#else
class OS_Coil_Cooling_DX_TwoSpeedFields: public ::EnumBase<OS_Coil_Cooling_DX_TwoSpeedFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, RatedHighSpeedTotalCoolingCapacity, RatedHighSpeedSensibleHeatRatio, RatedHighSpeedCOP, RatedHighSpeedAirFlowRate, AirInletNodeName, AirOutletNodeName, TotalCoolingCapacityFunctionofTemperatureCurveName, TotalCoolingCapacityFunctionofFlowFractionCurveName, EnergyInputRatioFunctionofTemperatureCurveName, EnergyInputRatioFunctionofFlowFractionCurveName, PartLoadFractionCorrelationCurveName, RatedLowSpeedTotalCoolingCapacity, RatedLowSpeedSensibleHeatRatio, RatedLowSpeedCOP, RatedLowSpeedAirFlowRate, LowSpeedTotalCoolingCapacityFunctionofTemperatureCurveName, LowSpeedEnergyInputRatioFunctionofTemperatureCurveName, CondenserAirInletNodeName, CondenserType, HighSpeedEvaporativeCondenserEffectiveness, HighSpeedEvaporativeCondenserAirFlowRate, HighSpeedEvaporativeCondenserPumpRatedPowerConsumption, LowSpeedEvaporativeCondenserEffectiveness, LowSpeedEvaporativeCondenserAirFlowRate, LowSpeedEvaporativeCondenserPumpRatedPowerConsumption, SupplyWaterStorageTankName, CondensateCollectionWaterStorageTankName, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName,   };
  OS_Coil_Cooling_DX_TwoSpeedFields()
   : EnumBase<OS_Coil_Cooling_DX_TwoSpeedFields>(Handle) {} 
  OS_Coil_Cooling_DX_TwoSpeedFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Cooling_DX_TwoSpeedFields>(t_name) {} 
  OS_Coil_Cooling_DX_TwoSpeedFields(int t_value) 
   : EnumBase<OS_Coil_Cooling_DX_TwoSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Cooling_DX_TwoSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Cooling_DX_TwoSpeedFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_Cooling_DX_TwoSpeedFields>;
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
{ OS_Coil_Cooling_DX_TwoSpeedFields::Handle, "Handle", "Handle"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::Name, "Name", "Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::RatedHighSpeedTotalCoolingCapacity, "RatedHighSpeedTotalCoolingCapacity", "Rated High Speed Total Cooling Capacity"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::RatedHighSpeedSensibleHeatRatio, "RatedHighSpeedSensibleHeatRatio", "Rated High Speed Sensible Heat Ratio"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::RatedHighSpeedCOP, "RatedHighSpeedCOP", "Rated High Speed COP"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::RatedHighSpeedAirFlowRate, "RatedHighSpeedAirFlowRate", "Rated High Speed Air Flow Rate"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::TotalCoolingCapacityFunctionofTemperatureCurveName, "TotalCoolingCapacityFunctionofTemperatureCurveName", "Total Cooling Capacity Function of Temperature Curve Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::TotalCoolingCapacityFunctionofFlowFractionCurveName, "TotalCoolingCapacityFunctionofFlowFractionCurveName", "Total Cooling Capacity Function of Flow Fraction Curve Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::EnergyInputRatioFunctionofTemperatureCurveName, "EnergyInputRatioFunctionofTemperatureCurveName", "Energy Input Ratio Function of Temperature Curve Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::EnergyInputRatioFunctionofFlowFractionCurveName, "EnergyInputRatioFunctionofFlowFractionCurveName", "Energy Input Ratio Function of Flow Fraction Curve Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::RatedLowSpeedTotalCoolingCapacity, "RatedLowSpeedTotalCoolingCapacity", "Rated Low Speed Total Cooling Capacity"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::RatedLowSpeedSensibleHeatRatio, "RatedLowSpeedSensibleHeatRatio", "Rated Low Speed Sensible Heat Ratio"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::RatedLowSpeedCOP, "RatedLowSpeedCOP", "Rated Low Speed COP"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::RatedLowSpeedAirFlowRate, "RatedLowSpeedAirFlowRate", "Rated Low Speed Air Flow Rate"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::LowSpeedTotalCoolingCapacityFunctionofTemperatureCurveName, "LowSpeedTotalCoolingCapacityFunctionofTemperatureCurveName", "Low Speed Total Cooling Capacity Function of Temperature Curve Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::LowSpeedEnergyInputRatioFunctionofTemperatureCurveName, "LowSpeedEnergyInputRatioFunctionofTemperatureCurveName", "Low Speed Energy Input Ratio Function of Temperature Curve Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::CondenserAirInletNodeName, "CondenserAirInletNodeName", "Condenser Air Inlet Node Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::CondenserType, "CondenserType", "Condenser Type"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserEffectiveness, "HighSpeedEvaporativeCondenserEffectiveness", "High Speed Evaporative Condenser Effectiveness"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserAirFlowRate, "HighSpeedEvaporativeCondenserAirFlowRate", "High Speed Evaporative Condenser Air Flow Rate"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::HighSpeedEvaporativeCondenserPumpRatedPowerConsumption, "HighSpeedEvaporativeCondenserPumpRatedPowerConsumption", "High Speed Evaporative Condenser Pump Rated Power Consumption"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserEffectiveness, "LowSpeedEvaporativeCondenserEffectiveness", "Low Speed Evaporative Condenser Effectiveness"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserAirFlowRate, "LowSpeedEvaporativeCondenserAirFlowRate", "Low Speed Evaporative Condenser Air Flow Rate"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::LowSpeedEvaporativeCondenserPumpRatedPowerConsumption, "LowSpeedEvaporativeCondenserPumpRatedPowerConsumption", "Low Speed Evaporative Condenser Pump Rated Power Consumption"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ OS_Coil_Cooling_DX_TwoSpeedFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Cooling_DX_TwoSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Cooling_DX_TwoSpeedFields> OptionalOS_Coil_Cooling_DX_TwoSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_COOLING_DX_TWOSPEED_FIELDENUMS_HXX
