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

#ifndef UTILITIES_IDD_COIL_COOLING_DX_MULTISPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_DX_MULTISPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_DX_MultiSpeedFields
 *  \brief Enumeration of Coil:Cooling:DX:MultiSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_DX_MultiSpeedFields, )
#else
class Coil_Cooling_DX_MultiSpeedFields: public ::EnumBase<Coil_Cooling_DX_MultiSpeedFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, AirInletNodeName, AirOutletNodeName, CondenserAirInletNodeName, CondenserType, SupplyWaterStorageTankName, CondensateCollectionWaterStorageTankName, ApplyPartLoadFractiontoSpeedsGreaterthan1, ApplyLatentDegradationtoSpeedsGreaterthan1, CrankcaseHeaterCapacity, MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, FuelType, NumberofSpeeds,   };
  Coil_Cooling_DX_MultiSpeedFields()
   : EnumBase<Coil_Cooling_DX_MultiSpeedFields>(Name) {} 
  Coil_Cooling_DX_MultiSpeedFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_MultiSpeedFields>(t_name) {} 
  Coil_Cooling_DX_MultiSpeedFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_MultiSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_MultiSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_MultiSpeedFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_MultiSpeedFields>;
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
{ Coil_Cooling_DX_MultiSpeedFields::Name, "Name", "Name"},
{ Coil_Cooling_DX_MultiSpeedFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_Cooling_DX_MultiSpeedFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Cooling_DX_MultiSpeedFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Cooling_DX_MultiSpeedFields::CondenserAirInletNodeName, "CondenserAirInletNodeName", "Condenser Air Inlet Node Name"},
{ Coil_Cooling_DX_MultiSpeedFields::CondenserType, "CondenserType", "Condenser Type"},
{ Coil_Cooling_DX_MultiSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ Coil_Cooling_DX_MultiSpeedFields::CondensateCollectionWaterStorageTankName, "CondensateCollectionWaterStorageTankName", "Condensate Collection Water Storage Tank Name"},
{ Coil_Cooling_DX_MultiSpeedFields::ApplyPartLoadFractiontoSpeedsGreaterthan1, "ApplyPartLoadFractiontoSpeedsGreaterthan1", "Apply Part Load Fraction to Speeds Greater than 1"},
{ Coil_Cooling_DX_MultiSpeedFields::ApplyLatentDegradationtoSpeedsGreaterthan1, "ApplyLatentDegradationtoSpeedsGreaterthan1", "Apply Latent Degradation to Speeds Greater than 1"},
{ Coil_Cooling_DX_MultiSpeedFields::CrankcaseHeaterCapacity, "CrankcaseHeaterCapacity", "Crankcase Heater Capacity"},
{ Coil_Cooling_DX_MultiSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation, "MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation", "Maximum Outdoor Dry-Bulb Temperature for Crankcase Heater Operation"},
{ Coil_Cooling_DX_MultiSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Coil_Cooling_DX_MultiSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Coil_Cooling_DX_MultiSpeedFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ Coil_Cooling_DX_MultiSpeedFields::FuelType, "FuelType", "Fuel Type"},
{ Coil_Cooling_DX_MultiSpeedFields::NumberofSpeeds, "NumberofSpeeds", "Number of Speeds"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_MultiSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_MultiSpeedFields> OptionalCoil_Cooling_DX_MultiSpeedFields ;
#endif

/** \class Coil_Cooling_DX_MultiSpeedExtensibleFields
 *  \brief Enumeration of Coil:Cooling:DX:MultiSpeed's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Coil_Cooling_DX_MultiSpeedExtensibleFields, )
#else
class Coil_Cooling_DX_MultiSpeedExtensibleFields: public ::EnumBase<Coil_Cooling_DX_MultiSpeedExtensibleFields> {
 public: 
  enum domain 
  {
SpeedGrossRatedTotalCoolingCapacity, SpeedGrossRatedSensibleHeatRatio, SpeedGrossRatedCoolingCOP, SpeedRatedAirFlowRate, RatedEvaporatorFanPowerPerVolumeFlowRate, SpeedTotalCoolingCapacityFunctionofTemperatureCurveName, SpeedTotalCoolingCapacityFunctionofFlowFractionCurveName, SpeedEnergyInputRatioFunctionofTemperatureCurveName, SpeedEnergyInputRatioFunctionofFlowFractionCurveName, SpeedPartLoadFractionCorrelationCurveName, SpeedNominalTimeforCondensateRemovaltoBegin, SpeedRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, SpeedMaximumCyclingRate, SpeedLatentCapacityTimeConstant, SpeedRatedWasteHeatFractionofPowerInput, SpeedWasteHeatFunctionofTemperatureCurveName, SpeedEvaporativeCondenserEffectiveness, SpeedEvaporativeCondenserAirFlowRate, SpeedRatedEvaporativeCondenserPumpPowerConsumption,   };
  Coil_Cooling_DX_MultiSpeedExtensibleFields()
   : EnumBase<Coil_Cooling_DX_MultiSpeedExtensibleFields>(SpeedGrossRatedTotalCoolingCapacity) {} 
  Coil_Cooling_DX_MultiSpeedExtensibleFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_DX_MultiSpeedExtensibleFields>(t_name) {} 
  Coil_Cooling_DX_MultiSpeedExtensibleFields(int t_value) 
   : EnumBase<Coil_Cooling_DX_MultiSpeedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_DX_MultiSpeedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_DX_MultiSpeedExtensibleFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_DX_MultiSpeedExtensibleFields>;
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
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedGrossRatedTotalCoolingCapacity, "SpeedGrossRatedTotalCoolingCapacity", "Speed Gross Rated Total Cooling Capacity"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedGrossRatedSensibleHeatRatio, "SpeedGrossRatedSensibleHeatRatio", "Speed Gross Rated Sensible Heat Ratio"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedGrossRatedCoolingCOP, "SpeedGrossRatedCoolingCOP", "Speed Gross Rated Cooling COP"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedRatedAirFlowRate, "SpeedRatedAirFlowRate", "Speed Rated Air Flow Rate"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::RatedEvaporatorFanPowerPerVolumeFlowRate, "RatedEvaporatorFanPowerPerVolumeFlowRate", "Rated Evaporator Fan Power Per Volume Flow Rate"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedTotalCoolingCapacityFunctionofTemperatureCurveName, "SpeedTotalCoolingCapacityFunctionofTemperatureCurveName", "Speed Total Cooling Capacity Function of Temperature Curve Name"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedTotalCoolingCapacityFunctionofFlowFractionCurveName, "SpeedTotalCoolingCapacityFunctionofFlowFractionCurveName", "Speed Total Cooling Capacity Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName, "SpeedEnergyInputRatioFunctionofTemperatureCurveName", "Speed Energy Input Ratio Function of Temperature Curve Name"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedEnergyInputRatioFunctionofFlowFractionCurveName, "SpeedEnergyInputRatioFunctionofFlowFractionCurveName", "Speed Energy Input Ratio Function of Flow Fraction Curve Name"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedPartLoadFractionCorrelationCurveName, "SpeedPartLoadFractionCorrelationCurveName", "Speed Part Load Fraction Correlation Curve Name"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedNominalTimeforCondensateRemovaltoBegin, "SpeedNominalTimeforCondensateRemovaltoBegin", "Speed Nominal Time for Condensate Removal to Begin"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, "SpeedRatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity", "Speed Ratio of Initial Moisture Evaporation Rate and Steady State Latent Capacity"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedMaximumCyclingRate, "SpeedMaximumCyclingRate", "Speed Maximum Cycling Rate"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedLatentCapacityTimeConstant, "SpeedLatentCapacityTimeConstant", "Speed Latent Capacity Time Constant"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedRatedWasteHeatFractionofPowerInput, "SpeedRatedWasteHeatFractionofPowerInput", "Speed Rated Waste Heat Fraction of Power Input"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedWasteHeatFunctionofTemperatureCurveName, "SpeedWasteHeatFunctionofTemperatureCurveName", "Speed Waste Heat Function of Temperature Curve Name"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedEvaporativeCondenserEffectiveness, "SpeedEvaporativeCondenserEffectiveness", "Speed Evaporative Condenser Effectiveness"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedEvaporativeCondenserAirFlowRate, "SpeedEvaporativeCondenserAirFlowRate", "Speed Evaporative Condenser Air Flow Rate"},
{ Coil_Cooling_DX_MultiSpeedExtensibleFields::SpeedRatedEvaporativeCondenserPumpPowerConsumption, "SpeedRatedEvaporativeCondenserPumpPowerConsumption", "Speed Rated Evaporative Condenser Pump Power Consumption"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_DX_MultiSpeedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_DX_MultiSpeedExtensibleFields> OptionalCoil_Cooling_DX_MultiSpeedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_DX_MULTISPEED_FIELDENUMS_HXX
