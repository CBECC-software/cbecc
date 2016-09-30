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

#ifndef UTILITIES_IDD_WATERHEATER_MIXED_FIELDENUMS_HXX
#define UTILITIES_IDD_WATERHEATER_MIXED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WaterHeater_MixedFields
 *  \brief Enumeration of WaterHeater:Mixed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WaterHeater_MixedFields, )
#else
class WaterHeater_MixedFields: public ::EnumBase<WaterHeater_MixedFields> {
 public: 
  enum domain 
  {
Name, TankVolume, SetpointTemperatureScheduleName, DeadbandTemperatureDifference, MaximumTemperatureLimit, HeaterControlType, HeaterMaximumCapacity, HeaterMinimumCapacity, HeaterIgnitionMinimumFlowRate, HeaterIgnitionDelay, HeaterFuelType, HeaterThermalEfficiency, PartLoadFactorCurveName, OffCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelType, OffCycleParasiticHeatFractiontoTank, OnCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelType, OnCycleParasiticHeatFractiontoTank, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, AmbientTemperatureZoneName, AmbientTemperatureOutdoorAirNodeName, OffCycleLossCoefficienttoAmbientTemperature, OffCycleLossFractiontoZone, OnCycleLossCoefficienttoAmbientTemperature, OnCycleLossFractiontoZone, PeakUseFlowRate, UseFlowRateFractionScheduleName, ColdWaterSupplyTemperatureScheduleName, UseSideInletNodeName, UseSideOutletNodeName, UseSideEffectiveness, SourceSideInletNodeName, SourceSideOutletNodeName, SourceSideEffectiveness, UseSideDesignFlowRate, SourceSideDesignFlowRate, IndirectWaterHeatingRecoveryTime, SourceSideFlowControlMode, IndirectAlternateSetpointTemperatureScheduleName,   };
  WaterHeater_MixedFields()
   : EnumBase<WaterHeater_MixedFields>(Name) {} 
  WaterHeater_MixedFields(const std::string &t_name) 
   : EnumBase<WaterHeater_MixedFields>(t_name) {} 
  WaterHeater_MixedFields(int t_value) 
   : EnumBase<WaterHeater_MixedFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterHeater_MixedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterHeater_MixedFields>::value()); }
   private:
    friend class EnumBase<WaterHeater_MixedFields>;
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
{ WaterHeater_MixedFields::Name, "Name", "Name"},
{ WaterHeater_MixedFields::TankVolume, "TankVolume", "Tank Volume"},
{ WaterHeater_MixedFields::SetpointTemperatureScheduleName, "SetpointTemperatureScheduleName", "Setpoint Temperature Schedule Name"},
{ WaterHeater_MixedFields::DeadbandTemperatureDifference, "DeadbandTemperatureDifference", "Deadband Temperature Difference"},
{ WaterHeater_MixedFields::MaximumTemperatureLimit, "MaximumTemperatureLimit", "Maximum Temperature Limit"},
{ WaterHeater_MixedFields::HeaterControlType, "HeaterControlType", "Heater Control Type"},
{ WaterHeater_MixedFields::HeaterMaximumCapacity, "HeaterMaximumCapacity", "Heater Maximum Capacity"},
{ WaterHeater_MixedFields::HeaterMinimumCapacity, "HeaterMinimumCapacity", "Heater Minimum Capacity"},
{ WaterHeater_MixedFields::HeaterIgnitionMinimumFlowRate, "HeaterIgnitionMinimumFlowRate", "Heater Ignition Minimum Flow Rate"},
{ WaterHeater_MixedFields::HeaterIgnitionDelay, "HeaterIgnitionDelay", "Heater Ignition Delay"},
{ WaterHeater_MixedFields::HeaterFuelType, "HeaterFuelType", "Heater Fuel Type"},
{ WaterHeater_MixedFields::HeaterThermalEfficiency, "HeaterThermalEfficiency", "Heater Thermal Efficiency"},
{ WaterHeater_MixedFields::PartLoadFactorCurveName, "PartLoadFactorCurveName", "Part Load Factor Curve Name"},
{ WaterHeater_MixedFields::OffCycleParasiticFuelConsumptionRate, "OffCycleParasiticFuelConsumptionRate", "Off Cycle Parasitic Fuel Consumption Rate"},
{ WaterHeater_MixedFields::OffCycleParasiticFuelType, "OffCycleParasiticFuelType", "Off Cycle Parasitic Fuel Type"},
{ WaterHeater_MixedFields::OffCycleParasiticHeatFractiontoTank, "OffCycleParasiticHeatFractiontoTank", "Off Cycle Parasitic Heat Fraction to Tank"},
{ WaterHeater_MixedFields::OnCycleParasiticFuelConsumptionRate, "OnCycleParasiticFuelConsumptionRate", "On Cycle Parasitic Fuel Consumption Rate"},
{ WaterHeater_MixedFields::OnCycleParasiticFuelType, "OnCycleParasiticFuelType", "On Cycle Parasitic Fuel Type"},
{ WaterHeater_MixedFields::OnCycleParasiticHeatFractiontoTank, "OnCycleParasiticHeatFractiontoTank", "On Cycle Parasitic Heat Fraction to Tank"},
{ WaterHeater_MixedFields::AmbientTemperatureIndicator, "AmbientTemperatureIndicator", "Ambient Temperature Indicator"},
{ WaterHeater_MixedFields::AmbientTemperatureScheduleName, "AmbientTemperatureScheduleName", "Ambient Temperature Schedule Name"},
{ WaterHeater_MixedFields::AmbientTemperatureZoneName, "AmbientTemperatureZoneName", "Ambient Temperature Zone Name"},
{ WaterHeater_MixedFields::AmbientTemperatureOutdoorAirNodeName, "AmbientTemperatureOutdoorAirNodeName", "Ambient Temperature Outdoor Air Node Name"},
{ WaterHeater_MixedFields::OffCycleLossCoefficienttoAmbientTemperature, "OffCycleLossCoefficienttoAmbientTemperature", "Off Cycle Loss Coefficient to Ambient Temperature"},
{ WaterHeater_MixedFields::OffCycleLossFractiontoZone, "OffCycleLossFractiontoZone", "Off Cycle Loss Fraction to Zone"},
{ WaterHeater_MixedFields::OnCycleLossCoefficienttoAmbientTemperature, "OnCycleLossCoefficienttoAmbientTemperature", "On Cycle Loss Coefficient to Ambient Temperature"},
{ WaterHeater_MixedFields::OnCycleLossFractiontoZone, "OnCycleLossFractiontoZone", "On Cycle Loss Fraction to Zone"},
{ WaterHeater_MixedFields::PeakUseFlowRate, "PeakUseFlowRate", "Peak Use Flow Rate"},
{ WaterHeater_MixedFields::UseFlowRateFractionScheduleName, "UseFlowRateFractionScheduleName", "Use Flow Rate Fraction Schedule Name"},
{ WaterHeater_MixedFields::ColdWaterSupplyTemperatureScheduleName, "ColdWaterSupplyTemperatureScheduleName", "Cold Water Supply Temperature Schedule Name"},
{ WaterHeater_MixedFields::UseSideInletNodeName, "UseSideInletNodeName", "Use Side Inlet Node Name"},
{ WaterHeater_MixedFields::UseSideOutletNodeName, "UseSideOutletNodeName", "Use Side Outlet Node Name"},
{ WaterHeater_MixedFields::UseSideEffectiveness, "UseSideEffectiveness", "Use Side Effectiveness"},
{ WaterHeater_MixedFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ WaterHeater_MixedFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ WaterHeater_MixedFields::SourceSideEffectiveness, "SourceSideEffectiveness", "Source Side Effectiveness"},
{ WaterHeater_MixedFields::UseSideDesignFlowRate, "UseSideDesignFlowRate", "Use Side Design Flow Rate"},
{ WaterHeater_MixedFields::SourceSideDesignFlowRate, "SourceSideDesignFlowRate", "Source Side Design Flow Rate"},
{ WaterHeater_MixedFields::IndirectWaterHeatingRecoveryTime, "IndirectWaterHeatingRecoveryTime", "Indirect Water Heating Recovery Time"},
{ WaterHeater_MixedFields::SourceSideFlowControlMode, "SourceSideFlowControlMode", "Source Side Flow Control Mode"},
{ WaterHeater_MixedFields::IndirectAlternateSetpointTemperatureScheduleName, "IndirectAlternateSetpointTemperatureScheduleName", "Indirect Alternate Setpoint Temperature Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterHeater_MixedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterHeater_MixedFields> OptionalWaterHeater_MixedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WATERHEATER_MIXED_FIELDENUMS_HXX
