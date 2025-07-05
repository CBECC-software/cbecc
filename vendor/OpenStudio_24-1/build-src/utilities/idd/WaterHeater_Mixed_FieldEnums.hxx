/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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
Name, TankVolume, SetpointTemperatureScheduleName, DeadbandTemperatureDifference, MaximumTemperatureLimit, HeaterControlType, HeaterMaximumCapacity, HeaterMinimumCapacity, HeaterIgnitionMinimumFlowRate, HeaterIgnitionDelay, HeaterFuelType, HeaterThermalEfficiency, PartLoadFactorCurveName, OffCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelType, OffCycleParasiticHeatFractiontoTank, OnCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelType, OnCycleParasiticHeatFractiontoTank, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, AmbientTemperatureZoneName, AmbientTemperatureOutdoorAirNodeName, OffCycleLossCoefficienttoAmbientTemperature, OffCycleLossFractiontoZone, OnCycleLossCoefficienttoAmbientTemperature, OnCycleLossFractiontoZone, PeakUseFlowRate, UseFlowRateFractionScheduleName, ColdWaterSupplyTemperatureScheduleName, UseSideInletNodeName, UseSideOutletNodeName, UseSideEffectiveness, SourceSideInletNodeName, SourceSideOutletNodeName, SourceSideEffectiveness, UseSideDesignFlowRate, SourceSideDesignFlowRate, IndirectWaterHeatingRecoveryTime, SourceSideFlowControlMode, IndirectAlternateSetpointTemperatureScheduleName, EndUseSubcategory,   };
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
{ WaterHeater_MixedFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
