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
Handle, Name, AvailabilityScheduleName, RatedHighSpeedTotalCoolingCapacity, RatedHighSpeedSensibleHeatRatio, RatedHighSpeedCOP, RatedHighSpeedAirFlowRate, UnitInternalStaticAirPressure, AirInletNodeName, AirOutletNodeName, TotalCoolingCapacityFunctionofTemperatureCurveName, TotalCoolingCapacityFunctionofFlowFractionCurveName, EnergyInputRatioFunctionofTemperatureCurveName, EnergyInputRatioFunctionofFlowFractionCurveName, PartLoadFractionCorrelationCurveName, RatedLowSpeedTotalCoolingCapacity, RatedLowSpeedSensibleHeatRatio, RatedLowSpeedCOP, RatedLowSpeedAirFlowRate, LowSpeedTotalCoolingCapacityFunctionofTemperatureCurveName, LowSpeedEnergyInputRatioFunctionofTemperatureCurveName, CondenserAirInletNodeName, CondenserType, MinimumOutdoorDryBulbTemperatureforCompressorOperation, HighSpeedEvaporativeCondenserEffectiveness, HighSpeedEvaporativeCondenserAirFlowRate, HighSpeedEvaporativeCondenserPumpRatedPowerConsumption, LowSpeedEvaporativeCondenserEffectiveness, LowSpeedEvaporativeCondenserAirFlowRate, LowSpeedEvaporativeCondenserPumpRatedPowerConsumption, SupplyWaterStorageTankName, CondensateCollectionWaterStorageTankName, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName,   };
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
{ OS_Coil_Cooling_DX_TwoSpeedFields::UnitInternalStaticAirPressure, "UnitInternalStaticAirPressure", "Unit Internal Static Air Pressure"},
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
{ OS_Coil_Cooling_DX_TwoSpeedFields::MinimumOutdoorDryBulbTemperatureforCompressorOperation, "MinimumOutdoorDryBulbTemperatureforCompressorOperation", "Minimum Outdoor Dry-Bulb Temperature for Compressor Operation"},
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
