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

#ifndef UTILITIES_IDD_OS_WATERHEATER_STRATIFIED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WATERHEATER_STRATIFIED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WaterHeater_StratifiedFields
 *  \brief Enumeration of OS:WaterHeater:Stratified's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WaterHeater_StratifiedFields, )
#else
class OS_WaterHeater_StratifiedFields: public ::EnumBase<OS_WaterHeater_StratifiedFields> {
 public: 
  enum domain 
  {
Handle, Name, EndUseSubcategory, TankVolume, TankHeight, TankShape, TankPerimeter, MaximumTemperatureLimit, HeaterPriorityControl, Heater1SetpointTemperatureScheduleName, Heater1DeadbandTemperatureDifference, Heater1Capacity, Heater1Height, Heater2SetpointTemperatureScheduleName, Heater2DeadbandTemperatureDifference, Heater2Capacity, Heater2Height, HeaterFuelType, HeaterThermalEfficiency, OffCycleParasiticFuelConsumptionRate, OffCycleParasiticFuelType, OffCycleParasiticHeatFractiontoTank, OffCycleParasiticHeight, OnCycleParasiticFuelConsumptionRate, OnCycleParasiticFuelType, OnCycleParasiticHeatFractiontoTank, OnCycleParasiticHeight, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, AmbientTemperatureThermalZoneName, AmbientTemperatureOutdoorAirNodeName, UniformSkinLossCoefficientperUnitAreatoAmbientTemperature, SkinLossFractiontoZone, OffCycleFlueLossCoefficienttoAmbientTemperature, OffCycleFlueLossFractiontoZone, PeakUseFlowRate, UseFlowRateFractionScheduleName, ColdWaterSupplyTemperatureScheduleName, UseSideInletNodeName, UseSideOutletNodeName, UseSideEffectiveness, UseSideInletHeight, UseSideOutletHeight, SourceSideInletNodeName, SourceSideOutletNodeName, SourceSideEffectiveness, SourceSideInletHeight, SourceSideOutletHeight, InletMode, UseSideDesignFlowRate, SourceSideDesignFlowRate, IndirectWaterHeatingRecoveryTime, NumberofNodes, AdditionalDestratificationConductivity, Node1AdditionalLossCoefficient, Node2AdditionalLossCoefficient, Node3AdditionalLossCoefficient, Node4AdditionalLossCoefficient, Node5AdditionalLossCoefficient, Node6AdditionalLossCoefficient, Node7AdditionalLossCoefficient, Node8AdditionalLossCoefficient, Node9AdditionalLossCoefficient, Node10AdditionalLossCoefficient, SourceSideFlowControlMode, IndirectAlternateSetpointTemperatureScheduleName,   };
  OS_WaterHeater_StratifiedFields()
   : EnumBase<OS_WaterHeater_StratifiedFields>(Handle) {} 
  OS_WaterHeater_StratifiedFields(const std::string &t_name) 
   : EnumBase<OS_WaterHeater_StratifiedFields>(t_name) {} 
  OS_WaterHeater_StratifiedFields(int t_value) 
   : EnumBase<OS_WaterHeater_StratifiedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WaterHeater_StratifiedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WaterHeater_StratifiedFields>::value()); }
   private:
    friend class EnumBase<OS_WaterHeater_StratifiedFields>;
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
{ OS_WaterHeater_StratifiedFields::Handle, "Handle", "Handle"},
{ OS_WaterHeater_StratifiedFields::Name, "Name", "Name"},
{ OS_WaterHeater_StratifiedFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ OS_WaterHeater_StratifiedFields::TankVolume, "TankVolume", "Tank Volume"},
{ OS_WaterHeater_StratifiedFields::TankHeight, "TankHeight", "Tank Height"},
{ OS_WaterHeater_StratifiedFields::TankShape, "TankShape", "Tank Shape"},
{ OS_WaterHeater_StratifiedFields::TankPerimeter, "TankPerimeter", "Tank Perimeter"},
{ OS_WaterHeater_StratifiedFields::MaximumTemperatureLimit, "MaximumTemperatureLimit", "Maximum Temperature Limit"},
{ OS_WaterHeater_StratifiedFields::HeaterPriorityControl, "HeaterPriorityControl", "Heater Priority Control"},
{ OS_WaterHeater_StratifiedFields::Heater1SetpointTemperatureScheduleName, "Heater1SetpointTemperatureScheduleName", "Heater 1 Setpoint Temperature Schedule Name"},
{ OS_WaterHeater_StratifiedFields::Heater1DeadbandTemperatureDifference, "Heater1DeadbandTemperatureDifference", "Heater 1 Deadband Temperature Difference"},
{ OS_WaterHeater_StratifiedFields::Heater1Capacity, "Heater1Capacity", "Heater 1 Capacity"},
{ OS_WaterHeater_StratifiedFields::Heater1Height, "Heater1Height", "Heater 1 Height"},
{ OS_WaterHeater_StratifiedFields::Heater2SetpointTemperatureScheduleName, "Heater2SetpointTemperatureScheduleName", "Heater 2 Setpoint Temperature Schedule Name"},
{ OS_WaterHeater_StratifiedFields::Heater2DeadbandTemperatureDifference, "Heater2DeadbandTemperatureDifference", "Heater 2 Deadband Temperature Difference"},
{ OS_WaterHeater_StratifiedFields::Heater2Capacity, "Heater2Capacity", "Heater 2 Capacity"},
{ OS_WaterHeater_StratifiedFields::Heater2Height, "Heater2Height", "Heater 2 Height"},
{ OS_WaterHeater_StratifiedFields::HeaterFuelType, "HeaterFuelType", "Heater Fuel Type"},
{ OS_WaterHeater_StratifiedFields::HeaterThermalEfficiency, "HeaterThermalEfficiency", "Heater Thermal Efficiency"},
{ OS_WaterHeater_StratifiedFields::OffCycleParasiticFuelConsumptionRate, "OffCycleParasiticFuelConsumptionRate", "Off Cycle Parasitic Fuel Consumption Rate"},
{ OS_WaterHeater_StratifiedFields::OffCycleParasiticFuelType, "OffCycleParasiticFuelType", "Off Cycle Parasitic Fuel Type"},
{ OS_WaterHeater_StratifiedFields::OffCycleParasiticHeatFractiontoTank, "OffCycleParasiticHeatFractiontoTank", "Off Cycle Parasitic Heat Fraction to Tank"},
{ OS_WaterHeater_StratifiedFields::OffCycleParasiticHeight, "OffCycleParasiticHeight", "Off Cycle Parasitic Height"},
{ OS_WaterHeater_StratifiedFields::OnCycleParasiticFuelConsumptionRate, "OnCycleParasiticFuelConsumptionRate", "On Cycle Parasitic Fuel Consumption Rate"},
{ OS_WaterHeater_StratifiedFields::OnCycleParasiticFuelType, "OnCycleParasiticFuelType", "On Cycle Parasitic Fuel Type"},
{ OS_WaterHeater_StratifiedFields::OnCycleParasiticHeatFractiontoTank, "OnCycleParasiticHeatFractiontoTank", "On Cycle Parasitic Heat Fraction to Tank"},
{ OS_WaterHeater_StratifiedFields::OnCycleParasiticHeight, "OnCycleParasiticHeight", "On Cycle Parasitic Height"},
{ OS_WaterHeater_StratifiedFields::AmbientTemperatureIndicator, "AmbientTemperatureIndicator", "Ambient Temperature Indicator"},
{ OS_WaterHeater_StratifiedFields::AmbientTemperatureScheduleName, "AmbientTemperatureScheduleName", "Ambient Temperature Schedule Name"},
{ OS_WaterHeater_StratifiedFields::AmbientTemperatureThermalZoneName, "AmbientTemperatureThermalZoneName", "Ambient Temperature Thermal Zone Name"},
{ OS_WaterHeater_StratifiedFields::AmbientTemperatureOutdoorAirNodeName, "AmbientTemperatureOutdoorAirNodeName", "Ambient Temperature Outdoor Air Node Name"},
{ OS_WaterHeater_StratifiedFields::UniformSkinLossCoefficientperUnitAreatoAmbientTemperature, "UniformSkinLossCoefficientperUnitAreatoAmbientTemperature", "Uniform Skin Loss Coefficient per Unit Area to Ambient Temperature"},
{ OS_WaterHeater_StratifiedFields::SkinLossFractiontoZone, "SkinLossFractiontoZone", "Skin Loss Fraction to Zone"},
{ OS_WaterHeater_StratifiedFields::OffCycleFlueLossCoefficienttoAmbientTemperature, "OffCycleFlueLossCoefficienttoAmbientTemperature", "Off Cycle Flue Loss Coefficient to Ambient Temperature"},
{ OS_WaterHeater_StratifiedFields::OffCycleFlueLossFractiontoZone, "OffCycleFlueLossFractiontoZone", "Off Cycle Flue Loss Fraction to Zone"},
{ OS_WaterHeater_StratifiedFields::PeakUseFlowRate, "PeakUseFlowRate", "Peak Use Flow Rate"},
{ OS_WaterHeater_StratifiedFields::UseFlowRateFractionScheduleName, "UseFlowRateFractionScheduleName", "Use Flow Rate Fraction Schedule Name"},
{ OS_WaterHeater_StratifiedFields::ColdWaterSupplyTemperatureScheduleName, "ColdWaterSupplyTemperatureScheduleName", "Cold Water Supply Temperature Schedule Name"},
{ OS_WaterHeater_StratifiedFields::UseSideInletNodeName, "UseSideInletNodeName", "Use Side Inlet Node Name"},
{ OS_WaterHeater_StratifiedFields::UseSideOutletNodeName, "UseSideOutletNodeName", "Use Side Outlet Node Name"},
{ OS_WaterHeater_StratifiedFields::UseSideEffectiveness, "UseSideEffectiveness", "Use Side Effectiveness"},
{ OS_WaterHeater_StratifiedFields::UseSideInletHeight, "UseSideInletHeight", "Use Side Inlet Height"},
{ OS_WaterHeater_StratifiedFields::UseSideOutletHeight, "UseSideOutletHeight", "Use Side Outlet Height"},
{ OS_WaterHeater_StratifiedFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ OS_WaterHeater_StratifiedFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ OS_WaterHeater_StratifiedFields::SourceSideEffectiveness, "SourceSideEffectiveness", "Source Side Effectiveness"},
{ OS_WaterHeater_StratifiedFields::SourceSideInletHeight, "SourceSideInletHeight", "Source Side Inlet Height"},
{ OS_WaterHeater_StratifiedFields::SourceSideOutletHeight, "SourceSideOutletHeight", "Source Side Outlet Height"},
{ OS_WaterHeater_StratifiedFields::InletMode, "InletMode", "Inlet Mode"},
{ OS_WaterHeater_StratifiedFields::UseSideDesignFlowRate, "UseSideDesignFlowRate", "Use Side Design Flow Rate"},
{ OS_WaterHeater_StratifiedFields::SourceSideDesignFlowRate, "SourceSideDesignFlowRate", "Source Side Design Flow Rate"},
{ OS_WaterHeater_StratifiedFields::IndirectWaterHeatingRecoveryTime, "IndirectWaterHeatingRecoveryTime", "Indirect Water Heating Recovery Time"},
{ OS_WaterHeater_StratifiedFields::NumberofNodes, "NumberofNodes", "Number of Nodes"},
{ OS_WaterHeater_StratifiedFields::AdditionalDestratificationConductivity, "AdditionalDestratificationConductivity", "Additional Destratification Conductivity"},
{ OS_WaterHeater_StratifiedFields::Node1AdditionalLossCoefficient, "Node1AdditionalLossCoefficient", "Node 1 Additional Loss Coefficient"},
{ OS_WaterHeater_StratifiedFields::Node2AdditionalLossCoefficient, "Node2AdditionalLossCoefficient", "Node 2 Additional Loss Coefficient"},
{ OS_WaterHeater_StratifiedFields::Node3AdditionalLossCoefficient, "Node3AdditionalLossCoefficient", "Node 3 Additional Loss Coefficient"},
{ OS_WaterHeater_StratifiedFields::Node4AdditionalLossCoefficient, "Node4AdditionalLossCoefficient", "Node 4 Additional Loss Coefficient"},
{ OS_WaterHeater_StratifiedFields::Node5AdditionalLossCoefficient, "Node5AdditionalLossCoefficient", "Node 5 Additional Loss Coefficient"},
{ OS_WaterHeater_StratifiedFields::Node6AdditionalLossCoefficient, "Node6AdditionalLossCoefficient", "Node 6 Additional Loss Coefficient"},
{ OS_WaterHeater_StratifiedFields::Node7AdditionalLossCoefficient, "Node7AdditionalLossCoefficient", "Node 7 Additional Loss Coefficient"},
{ OS_WaterHeater_StratifiedFields::Node8AdditionalLossCoefficient, "Node8AdditionalLossCoefficient", "Node 8 Additional Loss Coefficient"},
{ OS_WaterHeater_StratifiedFields::Node9AdditionalLossCoefficient, "Node9AdditionalLossCoefficient", "Node 9 Additional Loss Coefficient"},
{ OS_WaterHeater_StratifiedFields::Node10AdditionalLossCoefficient, "Node10AdditionalLossCoefficient", "Node 10 Additional Loss Coefficient"},
{ OS_WaterHeater_StratifiedFields::SourceSideFlowControlMode, "SourceSideFlowControlMode", "Source Side Flow Control Mode"},
{ OS_WaterHeater_StratifiedFields::IndirectAlternateSetpointTemperatureScheduleName, "IndirectAlternateSetpointTemperatureScheduleName", "Indirect Alternate Setpoint Temperature Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WaterHeater_StratifiedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WaterHeater_StratifiedFields> OptionalOS_WaterHeater_StratifiedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WATERHEATER_STRATIFIED_FIELDENUMS_HXX
