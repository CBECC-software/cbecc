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
Handle, Name, TankVolume, SetpointTemperatureScheduleName, DeadbandTemperatureDifference, MaximumTemperatureLimit, HeaterControlType, HeaterMaximumCapacity, HeaterMinimumCapacity, HeaterIgnitionMinimumFlowRate, HeaterIgnitionDelay, HeaterFuelType, HeaterThermalEfficiency, PartLoadFactorCurveName, OffCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelType, OffCycleParasiticHeatFractiontoTank, OnCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelType, OnCycleParasiticHeatFractiontoTank, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, AmbientTemperatureThermalZoneName, AmbientTemperatureOutdoorAirNodeName, OffCycleLossCoefficienttoAmbientTemperature, OffCycleLossFractiontoThermalZone, OnCycleLossCoefficienttoAmbientTemperature, OnCycleLossFractiontoThermalZone, PeakUseFlowRate, UseFlowRateFractionScheduleName, ColdWaterSupplyTemperatureScheduleName, UseSideInletNodeName, UseSideOutletNodeName, UseSideEffectiveness, SourceSideInletNodeName, SourceSideOutletNodeName, SourceSideEffectiveness, UseSideDesignFlowRate, SourceSideDesignFlowRate, IndirectWaterHeatingRecoveryTime, SourceSideFlowControlMode, IndirectAlternateSetpointTemperatureScheduleName, EndUseSubcategory,   };
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
{ OS_WaterHeater_MixedFields::SourceSideFlowControlMode, "SourceSideFlowControlMode", "Source Side Flow Control Mode"},
{ OS_WaterHeater_MixedFields::IndirectAlternateSetpointTemperatureScheduleName, "IndirectAlternateSetpointTemperatureScheduleName", "Indirect Alternate Setpoint Temperature Schedule Name"},
{ OS_WaterHeater_MixedFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
