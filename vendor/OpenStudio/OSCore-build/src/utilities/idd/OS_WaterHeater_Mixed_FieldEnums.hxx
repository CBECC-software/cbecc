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

#ifndef UTILITIES_IDD_OS_WATERHEATER_MIXED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WATERHEATER_MIXED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WaterHeater_MixedFields
 *  \brief Enumeration of OS:WaterHeater:Mixed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WaterHeater_MixedFields, )
#else
class OS_WaterHeater_MixedFields: public ::EnumBase<OS_WaterHeater_MixedFields> {
 public: 
  enum domain 
  {
Handle, Name, TankVolume, SetpointTemperatureScheduleName, DeadbandTemperatureDifference, MaximumTemperatureLimit, HeaterControlType, HeaterMaximumCapacity, HeaterMinimumCapacity, HeaterIgnitionMinimumFlowRate, HeaterIgnitionDelay, HeaterFuelType, HeaterThermalEfficiency, PartLoadFactorCurveName, OffCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelType, OffCycleParasiticHeatFractiontoTank, OnCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelType, OnCycleParasiticHeatFractiontoTank, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, AmbientTemperatureThermalZoneName, AmbientTemperatureOutdoorAirNodeName, OffCycleLossCoefficienttoAmbientTemperature, OffCycleLossFractiontoThermalZone, OnCycleLossCoefficienttoAmbientTemperature, OnCycleLossFractiontoThermalZone, PeakUseFlowRate, UseFlowRateFractionScheduleName, ColdWaterSupplyTemperatureScheduleName, UseSideInletNodeName, UseSideOutletNodeName, UseSideEffectiveness, SourceSideInletNodeName, SourceSideOutletNodeName, SourceSideEffectiveness, UseSideDesignFlowRate, SourceSideDesignFlowRate, IndirectWaterHeatingRecoveryTime,   };
  OS_WaterHeater_MixedFields()
   : EnumBase<OS_WaterHeater_MixedFields>(Handle) {} 
  OS_WaterHeater_MixedFields(const std::string &t_name) 
   : EnumBase<OS_WaterHeater_MixedFields>(t_name) {} 
  OS_WaterHeater_MixedFields(int t_value) 
   : EnumBase<OS_WaterHeater_MixedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WaterHeater_MixedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WaterHeater_MixedFields>::value()); }
   private:
    friend class EnumBase<OS_WaterHeater_MixedFields>;
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
{ OS_WaterHeater_MixedFields::Handle, "Handle", "Handle"},
{ OS_WaterHeater_MixedFields::Name, "Name", "Name"},
{ OS_WaterHeater_MixedFields::TankVolume, "TankVolume", "Tank Volume"},
{ OS_WaterHeater_MixedFields::SetpointTemperatureScheduleName, "SetpointTemperatureScheduleName", "Setpoint Temperature Schedule Name"},
{ OS_WaterHeater_MixedFields::DeadbandTemperatureDifference, "DeadbandTemperatureDifference", "Deadband Temperature Difference"},
{ OS_WaterHeater_MixedFields::MaximumTemperatureLimit, "MaximumTemperatureLimit", "Maximum Temperature Limit"},
{ OS_WaterHeater_MixedFields::HeaterControlType, "HeaterControlType", "Heater Control Type"},
{ OS_WaterHeater_MixedFields::HeaterMaximumCapacity, "HeaterMaximumCapacity", "Heater Maximum Capacity"},
{ OS_WaterHeater_MixedFields::HeaterMinimumCapacity, "HeaterMinimumCapacity", "Heater Minimum Capacity"},
{ OS_WaterHeater_MixedFields::HeaterIgnitionMinimumFlowRate, "HeaterIgnitionMinimumFlowRate", "Heater Ignition Minimum Flow Rate"},
{ OS_WaterHeater_MixedFields::HeaterIgnitionDelay, "HeaterIgnitionDelay", "Heater Ignition Delay"},
{ OS_WaterHeater_MixedFields::HeaterFuelType, "HeaterFuelType", "Heater Fuel Type"},
{ OS_WaterHeater_MixedFields::HeaterThermalEfficiency, "HeaterThermalEfficiency", "Heater Thermal Efficiency"},
{ OS_WaterHeater_MixedFields::PartLoadFactorCurveName, "PartLoadFactorCurveName", "Part Load Factor Curve Name"},
{ OS_WaterHeater_MixedFields::OffCycleParasiticFuelConsumptionRate, "OffCycleParasiticFuelConsumptionRate", "Off Cycle Parasitic Fuel Consumption Rate"},
{ OS_WaterHeater_MixedFields::OffCycleParasiticFuelType, "OffCycleParasiticFuelType", "Off Cycle Parasitic Fuel Type"},
{ OS_WaterHeater_MixedFields::OffCycleParasiticHeatFractiontoTank, "OffCycleParasiticHeatFractiontoTank", "Off Cycle Parasitic Heat Fraction to Tank"},
{ OS_WaterHeater_MixedFields::OnCycleParasiticFuelConsumptionRate, "OnCycleParasiticFuelConsumptionRate", "On Cycle Parasitic Fuel Consumption Rate"},
{ OS_WaterHeater_MixedFields::OnCycleParasiticFuelType, "OnCycleParasiticFuelType", "On Cycle Parasitic Fuel Type"},
{ OS_WaterHeater_MixedFields::OnCycleParasiticHeatFractiontoTank, "OnCycleParasiticHeatFractiontoTank", "On Cycle Parasitic Heat Fraction to Tank"},
{ OS_WaterHeater_MixedFields::AmbientTemperatureIndicator, "AmbientTemperatureIndicator", "Ambient Temperature Indicator"},
{ OS_WaterHeater_MixedFields::AmbientTemperatureScheduleName, "AmbientTemperatureScheduleName", "Ambient Temperature Schedule Name"},
{ OS_WaterHeater_MixedFields::AmbientTemperatureThermalZoneName, "AmbientTemperatureThermalZoneName", "Ambient Temperature Thermal Zone Name"},
{ OS_WaterHeater_MixedFields::AmbientTemperatureOutdoorAirNodeName, "AmbientTemperatureOutdoorAirNodeName", "Ambient Temperature Outdoor Air Node Name"},
{ OS_WaterHeater_MixedFields::OffCycleLossCoefficienttoAmbientTemperature, "OffCycleLossCoefficienttoAmbientTemperature", "Off Cycle Loss Coefficient to Ambient Temperature"},
{ OS_WaterHeater_MixedFields::OffCycleLossFractiontoThermalZone, "OffCycleLossFractiontoThermalZone", "Off Cycle Loss Fraction to Thermal Zone"},
{ OS_WaterHeater_MixedFields::OnCycleLossCoefficienttoAmbientTemperature, "OnCycleLossCoefficienttoAmbientTemperature", "On Cycle Loss Coefficient to Ambient Temperature"},
{ OS_WaterHeater_MixedFields::OnCycleLossFractiontoThermalZone, "OnCycleLossFractiontoThermalZone", "On Cycle Loss Fraction to Thermal Zone"},
{ OS_WaterHeater_MixedFields::PeakUseFlowRate, "PeakUseFlowRate", "Peak Use Flow Rate"},
{ OS_WaterHeater_MixedFields::UseFlowRateFractionScheduleName, "UseFlowRateFractionScheduleName", "Use Flow Rate Fraction Schedule Name"},
{ OS_WaterHeater_MixedFields::ColdWaterSupplyTemperatureScheduleName, "ColdWaterSupplyTemperatureScheduleName", "Cold Water Supply Temperature Schedule Name"},
{ OS_WaterHeater_MixedFields::UseSideInletNodeName, "UseSideInletNodeName", "Use Side Inlet Node Name"},
{ OS_WaterHeater_MixedFields::UseSideOutletNodeName, "UseSideOutletNodeName", "Use Side Outlet Node Name"},
{ OS_WaterHeater_MixedFields::UseSideEffectiveness, "UseSideEffectiveness", "Use Side Effectiveness"},
{ OS_WaterHeater_MixedFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ OS_WaterHeater_MixedFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ OS_WaterHeater_MixedFields::SourceSideEffectiveness, "SourceSideEffectiveness", "Source Side Effectiveness"},
{ OS_WaterHeater_MixedFields::UseSideDesignFlowRate, "UseSideDesignFlowRate", "Use Side Design Flow Rate"},
{ OS_WaterHeater_MixedFields::SourceSideDesignFlowRate, "SourceSideDesignFlowRate", "Source Side Design Flow Rate"},
{ OS_WaterHeater_MixedFields::IndirectWaterHeatingRecoveryTime, "IndirectWaterHeatingRecoveryTime", "Indirect Water Heating Recovery Time"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WaterHeater_MixedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WaterHeater_MixedFields> OptionalOS_WaterHeater_MixedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WATERHEATER_MIXED_FIELDENUMS_HXX
