/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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
Name, AvailabilityScheduleName, HighSpeedGrossRatedTotalCoolingCapacity, HighSpeedRatedSensibleHeatRatio, HighSpeedGrossRatedCoolingCOP, HighSpeedRatedAirFlowRate, UnitInternalStaticAirPressure, AirInletNodeName, AirOutletNodeName, TotalCoolingCapacityFunctionofTemperatureCurveName, TotalCoolingCapacityFunctionofFlowFractionCurveName, EnergyInputRatioFunctionofTemperatureCurveName, EnergyInputRatioFunctionofFlowFractionCurveName, PartLoadFractionCorrelationCurveName, LowSpeedGrossRatedTotalCoolingCapacity, LowSpeedGrossRatedSensibleHeatRatio, LowSpeedGrossRatedCoolingCOP, LowSpeedRatedAirFlowRate, LowSpeedTotalCoolingCapacityFunctionofTemperatureCurveName, LowSpeedEnergyInputRatioFunctionofTemperatureCurveName, CondenserAirInletNodeName, CondenserType, MinimumOutdoorDryBulbTemperatureforCompressorOperation, HighSpeedEvaporativeCondenserEffectiveness, HighSpeedEvaporativeCondenserAirFlowRate, HighSpeedEvaporativeCondenserPumpRatedPowerConsumption, LowSpeedEvaporativeCondenserEffectiveness, LowSpeedEvaporativeCondenserAirFlowRate, LowSpeedEvaporativeCondenserPumpRatedPowerConsumption, SupplyWaterStorageTankName, CondensateCollectionWaterStorageTankName, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, SensibleHeatRatioFunctionofTemperatureCurveName, SensibleHeatRatioFunctionofFlowFractionCurveName, LowSpeedSensibleHeatRatioFunctionofTemperatureCurveName, LowSpeedSensibleHeatRatioFunctionofFlowFractionCurveName, ZoneNameforCondenserPlacement,   };
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
{ Coil_Cooling_DX_TwoSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
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
