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

#ifndef UTILITIES_IDD_COILPERFORMANCE_DX_COOLING_FIELDENUMS_HXX
#define UTILITIES_IDD_COILPERFORMANCE_DX_COOLING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CoilPerformance_DX_CoolingFields
 *  \brief Enumeration of CoilPerformance:DX:Cooling's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CoilPerformance_DX_CoolingFields, )
#else
class CoilPerformance_DX_CoolingFields: public ::EnumBase<CoilPerformance_DX_CoolingFields> {
 public: 
  enum domain 
  {
Name, GrossRatedTotalCoolingCapacity, GrossRatedSensibleHeatRatio, GrossRatedCoolingCOP, RatedAirFlowRate, FractionofAirFlowBypassedAroundCoil, TotalCoolingCapacityFunctionofTemperatureCurveName, TotalCoolingCapacityFunctionofFlowFractionCurveName, EnergyInputRatioFunctionofTemperatureCurveName, EnergyInputRatioFunctionofFlowFractionCurveName, PartLoadFractionCorrelationCurveName, NominalTimeforCondensateRemovaltoBegin, RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, MaximumCyclingRate, LatentCapacityTimeConstant, CondenserAirInletNodeName, CondenserType, EvaporativeCondenserEffectiveness, EvaporativeCondenserAirFlowRate, EvaporativeCondenserPumpRatedPowerConsumption, SensibleHeatRatioFunctionofTemperatureCurveName, SensibleHeatRatioFunctionofFlowFractionCurveName,   };
  CoilPerformance_DX_CoolingFields()
   : EnumBase<CoilPerformance_DX_CoolingFields>(Name) {} 
  CoilPerformance_DX_CoolingFields(const std::string &t_name) 
   : EnumBase<CoilPerformance_DX_CoolingFields>(t_name) {} 
  CoilPerformance_DX_CoolingFields(int t_value) 
   : EnumBase<CoilPerformance_DX_CoolingFields>(t_value) {} 
  static std::string enumName() 
  { return "CoilPerformance_DX_CoolingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CoilPerformance_DX_CoolingFields>::value()); }
   private:
    friend class EnumBase<CoilPerformance_DX_CoolingFields>;
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
{ CoilPerformance_DX_CoolingFields::Name, "Name", "Name"},
{ CoilPerformance_DX_CoolingFields::GrossRatedTotalCoolingCapacity, "GrossRatedTotalCoolingCapacity", "Gross Rated Total Cooling Capacity"},
{ CoilPerformance_DX_CoolingFields::GrossRatedSensibleHeatRatio, "GrossRatedSensibleHeatRatio", "Gross Rated Sensible Heat Ratio"},
{ CoilPerformance_DX_CoolingFields::GrossRatedCoolingCOP, "GrossRatedCoolingCOP", "Gross Rated Cooling COP"},
{ CoilPerformance_DX_CoolingFields::RatedAirFlowRate, "RatedAirFlowRate", "Rated Air Flow Rate"},
{ CoilPerformance_DX_CoolingFields::FractionofAirFlowBypassedAroundCoil, "FractionofAirFlowBypassedAroundCoil", "Fraction of Air Flow Bypassed Around Coil"},
{ CoilPerformance_DX_CoolingFields::TotalCoolingCapacityFunctionofTemperatureCurveName, "TotalCoolingCapacityFunctionofTemperatureCurveName", "Total Cooling Capacity Function of Temperature Curve Name"},
{ CoilPerformance_DX_CoolingFields::TotalCoolingCapacityFunctionofFlowFractionCurveName, "TotalCoolingCapacityFunctionofFlowFractionCurveName", "Total Cooling Capacity Function of Flow Fraction Curve Name"},
{ CoilPerformance_DX_CoolingFields::EnergyInputRatioFunctionofTemperatureCurveName, "EnergyInputRatioFunctionofTemperatureCurveName", "Energy Input Ratio Function of Temperature Curve Name"},
{ CoilPerformance_DX_CoolingFields::EnergyInputRatioFunctionofFlowFractionCurveName, "EnergyInputRatioFunctionofFlowFractionCurveName", "Energy Input Ratio Function of Flow Fraction Curve Name"},
{ CoilPerformance_DX_CoolingFields::PartLoadFractionCorrelationCurveName, "PartLoadFractionCorrelationCurveName", "Part Load Fraction Correlation Curve Name"},
{ CoilPerformance_DX_CoolingFields::NominalTimeforCondensateRemovaltoBegin, "NominalTimeforCondensateRemovaltoBegin", "Nominal Time for Condensate Removal to Begin"},
{ CoilPerformance_DX_CoolingFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, "RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity", "Ratio of Initial Moisture Evaporation Rate and Steady State Latent Capacity"},
{ CoilPerformance_DX_CoolingFields::MaximumCyclingRate, "MaximumCyclingRate", "Maximum Cycling Rate"},
{ CoilPerformance_DX_CoolingFields::LatentCapacityTimeConstant, "LatentCapacityTimeConstant", "Latent Capacity Time Constant"},
{ CoilPerformance_DX_CoolingFields::CondenserAirInletNodeName, "CondenserAirInletNodeName", "Condenser Air Inlet Node Name"},
{ CoilPerformance_DX_CoolingFields::CondenserType, "CondenserType", "Condenser Type"},
{ CoilPerformance_DX_CoolingFields::EvaporativeCondenserEffectiveness, "EvaporativeCondenserEffectiveness", "Evaporative Condenser Effectiveness"},
{ CoilPerformance_DX_CoolingFields::EvaporativeCondenserAirFlowRate, "EvaporativeCondenserAirFlowRate", "Evaporative Condenser Air Flow Rate"},
{ CoilPerformance_DX_CoolingFields::EvaporativeCondenserPumpRatedPowerConsumption, "EvaporativeCondenserPumpRatedPowerConsumption", "Evaporative Condenser Pump Rated Power Consumption"},
{ CoilPerformance_DX_CoolingFields::SensibleHeatRatioFunctionofTemperatureCurveName, "SensibleHeatRatioFunctionofTemperatureCurveName", "Sensible Heat Ratio Function of Temperature Curve Name"},
{ CoilPerformance_DX_CoolingFields::SensibleHeatRatioFunctionofFlowFractionCurveName, "SensibleHeatRatioFunctionofFlowFractionCurveName", "Sensible Heat Ratio Function of Flow Fraction Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const CoilPerformance_DX_CoolingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CoilPerformance_DX_CoolingFields> OptionalCoilPerformance_DX_CoolingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COILPERFORMANCE_DX_COOLING_FIELDENUMS_HXX
