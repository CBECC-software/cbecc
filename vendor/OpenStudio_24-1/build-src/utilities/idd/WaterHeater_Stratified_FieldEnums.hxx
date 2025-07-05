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

#ifndef UTILITIES_IDD_WATERHEATER_STRATIFIED_FIELDENUMS_HXX
#define UTILITIES_IDD_WATERHEATER_STRATIFIED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WaterHeater_StratifiedFields
 *  \brief Enumeration of WaterHeater:Stratified's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WaterHeater_StratifiedFields, )
#else
class WaterHeater_StratifiedFields: public ::EnumBase<WaterHeater_StratifiedFields> {
 public: 
  enum domain 
  {
Name, EndUseSubcategory, TankVolume, TankHeight, TankShape, TankPerimeter, MaximumTemperatureLimit, HeaterPriorityControl, Heater1SetpointTemperatureScheduleName, Heater1DeadbandTemperatureDifference, Heater1Capacity, Heater1Height, Heater2SetpointTemperatureScheduleName, Heater2DeadbandTemperatureDifference, Heater2Capacity, Heater2Height, HeaterFuelType, HeaterThermalEfficiency, OffCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelType, OffCycleParasiticHeatFractiontoTank, OffCycleParasiticHeight, OnCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelType, OnCycleParasiticHeatFractiontoTank, OnCycleParasiticHeight, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, AmbientTemperatureZoneName, AmbientTemperatureOutdoorAirNodeName, UniformSkinLossCoefficientperUnitAreatoAmbientTemperature, SkinLossFractiontoZone, OffCycleFlueLossCoefficienttoAmbientTemperature, OffCycleFlueLossFractiontoZone, PeakUseFlowRate, UseFlowRateFractionScheduleName, ColdWaterSupplyTemperatureScheduleName, UseSideInletNodeName, UseSideOutletNodeName, UseSideEffectiveness, UseSideInletHeight, UseSideOutletHeight, SourceSideInletNodeName, SourceSideOutletNodeName, SourceSideEffectiveness, SourceSideInletHeight, SourceSideOutletHeight, InletMode, UseSideDesignFlowRate, SourceSideDesignFlowRate, IndirectWaterHeatingRecoveryTime, NumberofNodes, AdditionalDestratificationConductivity, Node1AdditionalLossCoefficient, Node2AdditionalLossCoefficient, Node3AdditionalLossCoefficient, Node4AdditionalLossCoefficient, Node5AdditionalLossCoefficient, Node6AdditionalLossCoefficient, Node7AdditionalLossCoefficient, Node8AdditionalLossCoefficient, Node9AdditionalLossCoefficient, Node10AdditionalLossCoefficient, Node11AdditionalLossCoefficient, Node12AdditionalLossCoefficient, SourceSideFlowControlMode, IndirectAlternateSetpointTemperatureScheduleName,   };
  WaterHeater_StratifiedFields()
   : EnumBase<WaterHeater_StratifiedFields>(Name) {} 
  WaterHeater_StratifiedFields(const std::string &t_name) 
   : EnumBase<WaterHeater_StratifiedFields>(t_name) {} 
  WaterHeater_StratifiedFields(int t_value) 
   : EnumBase<WaterHeater_StratifiedFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterHeater_StratifiedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterHeater_StratifiedFields>::value()); }
   private:
    friend class EnumBase<WaterHeater_StratifiedFields>;
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
{ WaterHeater_StratifiedFields::Name, "Name", "Name"},
{ WaterHeater_StratifiedFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ WaterHeater_StratifiedFields::TankVolume, "TankVolume", "Tank Volume"},
{ WaterHeater_StratifiedFields::TankHeight, "TankHeight", "Tank Height"},
{ WaterHeater_StratifiedFields::TankShape, "TankShape", "Tank Shape"},
{ WaterHeater_StratifiedFields::TankPerimeter, "TankPerimeter", "Tank Perimeter"},
{ WaterHeater_StratifiedFields::MaximumTemperatureLimit, "MaximumTemperatureLimit", "Maximum Temperature Limit"},
{ WaterHeater_StratifiedFields::HeaterPriorityControl, "HeaterPriorityControl", "Heater Priority Control"},
{ WaterHeater_StratifiedFields::Heater1SetpointTemperatureScheduleName, "Heater1SetpointTemperatureScheduleName", "Heater 1 Setpoint Temperature Schedule Name"},
{ WaterHeater_StratifiedFields::Heater1DeadbandTemperatureDifference, "Heater1DeadbandTemperatureDifference", "Heater 1 Deadband Temperature Difference"},
{ WaterHeater_StratifiedFields::Heater1Capacity, "Heater1Capacity", "Heater 1 Capacity"},
{ WaterHeater_StratifiedFields::Heater1Height, "Heater1Height", "Heater 1 Height"},
{ WaterHeater_StratifiedFields::Heater2SetpointTemperatureScheduleName, "Heater2SetpointTemperatureScheduleName", "Heater 2 Setpoint Temperature Schedule Name"},
{ WaterHeater_StratifiedFields::Heater2DeadbandTemperatureDifference, "Heater2DeadbandTemperatureDifference", "Heater 2 Deadband Temperature Difference"},
{ WaterHeater_StratifiedFields::Heater2Capacity, "Heater2Capacity", "Heater 2 Capacity"},
{ WaterHeater_StratifiedFields::Heater2Height, "Heater2Height", "Heater 2 Height"},
{ WaterHeater_StratifiedFields::HeaterFuelType, "HeaterFuelType", "Heater Fuel Type"},
{ WaterHeater_StratifiedFields::HeaterThermalEfficiency, "HeaterThermalEfficiency", "Heater Thermal Efficiency"},
{ WaterHeater_StratifiedFields::OffCycleParasiticFuelConsumptionRate, "OffCycleParasiticFuelConsumptionRate", "Off Cycle Parasitic Fuel Consumption Rate"},
{ WaterHeater_StratifiedFields::OffCycleParasiticFuelType, "OffCycleParasiticFuelType", "Off Cycle Parasitic Fuel Type"},
{ WaterHeater_StratifiedFields::OffCycleParasiticHeatFractiontoTank, "OffCycleParasiticHeatFractiontoTank", "Off Cycle Parasitic Heat Fraction to Tank"},
{ WaterHeater_StratifiedFields::OffCycleParasiticHeight, "OffCycleParasiticHeight", "Off Cycle Parasitic Height"},
{ WaterHeater_StratifiedFields::OnCycleParasiticFuelConsumptionRate, "OnCycleParasiticFuelConsumptionRate", "On Cycle Parasitic Fuel Consumption Rate"},
{ WaterHeater_StratifiedFields::OnCycleParasiticFuelType, "OnCycleParasiticFuelType", "On Cycle Parasitic Fuel Type"},
{ WaterHeater_StratifiedFields::OnCycleParasiticHeatFractiontoTank, "OnCycleParasiticHeatFractiontoTank", "On Cycle Parasitic Heat Fraction to Tank"},
{ WaterHeater_StratifiedFields::OnCycleParasiticHeight, "OnCycleParasiticHeight", "On Cycle Parasitic Height"},
{ WaterHeater_StratifiedFields::AmbientTemperatureIndicator, "AmbientTemperatureIndicator", "Ambient Temperature Indicator"},
{ WaterHeater_StratifiedFields::AmbientTemperatureScheduleName, "AmbientTemperatureScheduleName", "Ambient Temperature Schedule Name"},
{ WaterHeater_StratifiedFields::AmbientTemperatureZoneName, "AmbientTemperatureZoneName", "Ambient Temperature Zone Name"},
{ WaterHeater_StratifiedFields::AmbientTemperatureOutdoorAirNodeName, "AmbientTemperatureOutdoorAirNodeName", "Ambient Temperature Outdoor Air Node Name"},
{ WaterHeater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature, "UniformSkinLossCoefficientperUnitAreatoAmbientTemperature", "Uniform Skin Loss Coefficient per Unit Area to Ambient Temperature"},
{ WaterHeater_StratifiedFields::SkinLossFractiontoZone, "SkinLossFractiontoZone", "Skin Loss Fraction to Zone"},
{ WaterHeater_StratifiedFields::OffCycleFlueLossCoefficienttoAmbientTemperature, "OffCycleFlueLossCoefficienttoAmbientTemperature", "Off Cycle Flue Loss Coefficient to Ambient Temperature"},
{ WaterHeater_StratifiedFields::OffCycleFlueLossFractiontoZone, "OffCycleFlueLossFractiontoZone", "Off Cycle Flue Loss Fraction to Zone"},
{ WaterHeater_StratifiedFields::PeakUseFlowRate, "PeakUseFlowRate", "Peak Use Flow Rate"},
{ WaterHeater_StratifiedFields::UseFlowRateFractionScheduleName, "UseFlowRateFractionScheduleName", "Use Flow Rate Fraction Schedule Name"},
{ WaterHeater_StratifiedFields::ColdWaterSupplyTemperatureScheduleName, "ColdWaterSupplyTemperatureScheduleName", "Cold Water Supply Temperature Schedule Name"},
{ WaterHeater_StratifiedFields::UseSideInletNodeName, "UseSideInletNodeName", "Use Side Inlet Node Name"},
{ WaterHeater_StratifiedFields::UseSideOutletNodeName, "UseSideOutletNodeName", "Use Side Outlet Node Name"},
{ WaterHeater_StratifiedFields::UseSideEffectiveness, "UseSideEffectiveness", "Use Side Effectiveness"},
{ WaterHeater_StratifiedFields::UseSideInletHeight, "UseSideInletHeight", "Use Side Inlet Height"},
{ WaterHeater_StratifiedFields::UseSideOutletHeight, "UseSideOutletHeight", "Use Side Outlet Height"},
{ WaterHeater_StratifiedFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ WaterHeater_StratifiedFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ WaterHeater_StratifiedFields::SourceSideEffectiveness, "SourceSideEffectiveness", "Source Side Effectiveness"},
{ WaterHeater_StratifiedFields::SourceSideInletHeight, "SourceSideInletHeight", "Source Side Inlet Height"},
{ WaterHeater_StratifiedFields::SourceSideOutletHeight, "SourceSideOutletHeight", "Source Side Outlet Height"},
{ WaterHeater_StratifiedFields::InletMode, "InletMode", "Inlet Mode"},
{ WaterHeater_StratifiedFields::UseSideDesignFlowRate, "UseSideDesignFlowRate", "Use Side Design Flow Rate"},
{ WaterHeater_StratifiedFields::SourceSideDesignFlowRate, "SourceSideDesignFlowRate", "Source Side Design Flow Rate"},
{ WaterHeater_StratifiedFields::IndirectWaterHeatingRecoveryTime, "IndirectWaterHeatingRecoveryTime", "Indirect Water Heating Recovery Time"},
{ WaterHeater_StratifiedFields::NumberofNodes, "NumberofNodes", "Number of Nodes"},
{ WaterHeater_StratifiedFields::AdditionalDestratificationConductivity, "AdditionalDestratificationConductivity", "Additional Destratification Conductivity"},
{ WaterHeater_StratifiedFields::Node1AdditionalLossCoefficient, "Node1AdditionalLossCoefficient", "Node 1 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node2AdditionalLossCoefficient, "Node2AdditionalLossCoefficient", "Node 2 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node3AdditionalLossCoefficient, "Node3AdditionalLossCoefficient", "Node 3 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node4AdditionalLossCoefficient, "Node4AdditionalLossCoefficient", "Node 4 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node5AdditionalLossCoefficient, "Node5AdditionalLossCoefficient", "Node 5 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node6AdditionalLossCoefficient, "Node6AdditionalLossCoefficient", "Node 6 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node7AdditionalLossCoefficient, "Node7AdditionalLossCoefficient", "Node 7 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node8AdditionalLossCoefficient, "Node8AdditionalLossCoefficient", "Node 8 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node9AdditionalLossCoefficient, "Node9AdditionalLossCoefficient", "Node 9 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node10AdditionalLossCoefficient, "Node10AdditionalLossCoefficient", "Node 10 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node11AdditionalLossCoefficient, "Node11AdditionalLossCoefficient", "Node 11 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::Node12AdditionalLossCoefficient, "Node12AdditionalLossCoefficient", "Node 12 Additional Loss Coefficient"},
{ WaterHeater_StratifiedFields::SourceSideFlowControlMode, "SourceSideFlowControlMode", "Source Side Flow Control Mode"},
{ WaterHeater_StratifiedFields::IndirectAlternateSetpointTemperatureScheduleName, "IndirectAlternateSetpointTemperatureScheduleName", "Indirect Alternate Setpoint Temperature Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterHeater_StratifiedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterHeater_StratifiedFields> OptionalWaterHeater_StratifiedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WATERHEATER_STRATIFIED_FIELDENUMS_HXX
