/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_HEATPUMP_AIRTOWATER_FUELFIRED_COOLING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_AIRTOWATER_FUELFIRED_COOLING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_AirToWater_FuelFired_CoolingFields
 *  \brief Enumeration of HeatPump:AirToWater:FuelFired:Cooling's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_AirToWater_FuelFired_CoolingFields, )
#else
class HeatPump_AirToWater_FuelFired_CoolingFields: public ::EnumBase<HeatPump_AirToWater_FuelFired_CoolingFields> {
 public: 
  enum domain 
  {
Name, WaterInletNodeName, WaterOutletNodeName, AirSourceNodeName, CompanionHeatingHeatPumpName, FuelType, EndUseSubcategory, NominalCoolingCapacity, NominalCOP, DesignFlowRate, DesignSupplyTemperature, DesignTemperatureLift, SizingFactor, FlowMode, OutdoorAirTemperatureCurveInputVariable, WaterTemperatureCurveInputVariable, NormalizedCapacityFunctionofTemperatureCurveName, FuelEnergyInputRatioFunctionofTemperatureCurveName, FuelEnergyInputRatioFunctionofPLRCurveName, MinimumPartLoadRatio, MaximumPartLoadRatio, CyclingRatioFactorCurveName, NominalAuxiliaryElectricPower, AuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurveName, AuxiliaryElectricEnergyInputRatioFunctionofPLRCurveName, StandbyElectricPower,   };
  HeatPump_AirToWater_FuelFired_CoolingFields()
   : EnumBase<HeatPump_AirToWater_FuelFired_CoolingFields>(Name) {} 
  HeatPump_AirToWater_FuelFired_CoolingFields(const std::string &t_name) 
   : EnumBase<HeatPump_AirToWater_FuelFired_CoolingFields>(t_name) {} 
  HeatPump_AirToWater_FuelFired_CoolingFields(int t_value) 
   : EnumBase<HeatPump_AirToWater_FuelFired_CoolingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_AirToWater_FuelFired_CoolingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_AirToWater_FuelFired_CoolingFields>::integer_value()); }
   private:
    friend class EnumBase<HeatPump_AirToWater_FuelFired_CoolingFields>;
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
{ HeatPump_AirToWater_FuelFired_CoolingFields::Name, "Name", "Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::AirSourceNodeName, "AirSourceNodeName", "Air Source Node Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::CompanionHeatingHeatPumpName, "CompanionHeatingHeatPumpName", "Companion Heating Heat Pump Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::FuelType, "FuelType", "Fuel Type"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::NominalCoolingCapacity, "NominalCoolingCapacity", "Nominal Cooling Capacity"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::NominalCOP, "NominalCOP", "Nominal COP"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::DesignSupplyTemperature, "DesignSupplyTemperature", "Design Supply Temperature"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::DesignTemperatureLift, "DesignTemperatureLift", "Design Temperature Lift"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::FlowMode, "FlowMode", "Flow Mode"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::OutdoorAirTemperatureCurveInputVariable, "OutdoorAirTemperatureCurveInputVariable", "Outdoor Air Temperature Curve Input Variable"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::WaterTemperatureCurveInputVariable, "WaterTemperatureCurveInputVariable", "Water Temperature Curve Input Variable"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::NormalizedCapacityFunctionofTemperatureCurveName, "NormalizedCapacityFunctionofTemperatureCurveName", "Normalized Capacity Function of Temperature Curve Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::FuelEnergyInputRatioFunctionofTemperatureCurveName, "FuelEnergyInputRatioFunctionofTemperatureCurveName", "Fuel Energy Input Ratio Function of Temperature Curve Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::FuelEnergyInputRatioFunctionofPLRCurveName, "FuelEnergyInputRatioFunctionofPLRCurveName", "Fuel Energy Input Ratio Function of PLR Curve Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::CyclingRatioFactorCurveName, "CyclingRatioFactorCurveName", "Cycling Ratio Factor Curve Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::NominalAuxiliaryElectricPower, "NominalAuxiliaryElectricPower", "Nominal Auxiliary Electric Power"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::AuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurveName, "AuxiliaryElectricEnergyInputRatioFunctionofTemperatureCurveName", "Auxiliary Electric Energy Input Ratio Function of Temperature Curve Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::AuxiliaryElectricEnergyInputRatioFunctionofPLRCurveName, "AuxiliaryElectricEnergyInputRatioFunctionofPLRCurveName", "Auxiliary Electric Energy Input Ratio Function of PLR Curve Name"},
{ HeatPump_AirToWater_FuelFired_CoolingFields::StandbyElectricPower, "StandbyElectricPower", "Standby Electric Power"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_AirToWater_FuelFired_CoolingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_AirToWater_FuelFired_CoolingFields> OptionalHeatPump_AirToWater_FuelFired_CoolingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_AIRTOWATER_FUELFIRED_COOLING_FIELDENUMS_HXX
