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

#ifndef UTILITIES_IDD_GENERATOR_MICROTURBINE_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_MICROTURBINE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_MicroTurbineFields
 *  \brief Enumeration of Generator:MicroTurbine's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_MicroTurbineFields, )
#else
class Generator_MicroTurbineFields: public ::EnumBase<Generator_MicroTurbineFields> {
 public: 
  enum domain 
  {
Name, ReferenceElectricalPowerOutput, MinimumFullLoadElectricalPowerOutput, MaximumFullLoadElectricalPowerOutput, ReferenceElectricalEfficiencyUsingLowerHeatingValue, ReferenceCombustionAirInletTemperature, ReferenceCombustionAirInletHumidityRatio, ReferenceElevation, ElectricalPowerFunctionofTemperatureandElevationCurveName, ElectricalEfficiencyFunctionofTemperatureCurveName, ElectricalEfficiencyFunctionofPartLoadRatioCurveName, FuelType, FuelHigherHeatingValue, FuelLowerHeatingValue, StandbyPower, AncillaryPower, AncillaryPowerFunctionofFuelInputCurveName, HeatRecoveryWaterInletNodeName, HeatRecoveryWaterOutletNodeName, ReferenceThermalEfficiencyUsingLowerHeatValue, ReferenceInletWaterTemperature, HeatRecoveryWaterFlowOperatingMode, ReferenceHeatRecoveryWaterFlowRate, HeatRecoveryWaterFlowRateFunctionofTemperatureandPowerCurveName, ThermalEfficiencyFunctionofTemperatureandElevationCurveName, HeatRecoveryRateFunctionofPartLoadRatioCurveName, HeatRecoveryRateFunctionofInletWaterTemperatureCurveName, HeatRecoveryRateFunctionofWaterFlowRateCurveName, MinimumHeatRecoveryWaterFlowRate, MaximumHeatRecoveryWaterFlowRate, MaximumHeatRecoveryWaterTemperature, CombustionAirInletNodeName, CombustionAirOutletNodeName, ReferenceExhaustAirMassFlowRate, ExhaustAirFlowRateFunctionofTemperatureCurveName, ExhaustAirFlowRateFunctionofPartLoadRatioCurveName, NominalExhaustAirOutletTemperature, ExhaustAirTemperatureFunctionofTemperatureCurveName, ExhaustAirTemperatureFunctionofPartLoadRatioCurveName,   };
  Generator_MicroTurbineFields()
   : EnumBase<Generator_MicroTurbineFields>(Name) {} 
  Generator_MicroTurbineFields(const std::string &t_name) 
   : EnumBase<Generator_MicroTurbineFields>(t_name) {} 
  Generator_MicroTurbineFields(int t_value) 
   : EnumBase<Generator_MicroTurbineFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_MicroTurbineFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_MicroTurbineFields>::value()); }
   private:
    friend class EnumBase<Generator_MicroTurbineFields>;
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
{ Generator_MicroTurbineFields::Name, "Name", "Name"},
{ Generator_MicroTurbineFields::ReferenceElectricalPowerOutput, "ReferenceElectricalPowerOutput", "Reference Electrical Power Output"},
{ Generator_MicroTurbineFields::MinimumFullLoadElectricalPowerOutput, "MinimumFullLoadElectricalPowerOutput", "Minimum Full Load Electrical Power Output"},
{ Generator_MicroTurbineFields::MaximumFullLoadElectricalPowerOutput, "MaximumFullLoadElectricalPowerOutput", "Maximum Full Load Electrical Power Output"},
{ Generator_MicroTurbineFields::ReferenceElectricalEfficiencyUsingLowerHeatingValue, "ReferenceElectricalEfficiencyUsingLowerHeatingValue", "Reference Electrical Efficiency Using Lower Heating Value"},
{ Generator_MicroTurbineFields::ReferenceCombustionAirInletTemperature, "ReferenceCombustionAirInletTemperature", "Reference Combustion Air Inlet Temperature"},
{ Generator_MicroTurbineFields::ReferenceCombustionAirInletHumidityRatio, "ReferenceCombustionAirInletHumidityRatio", "Reference Combustion Air Inlet Humidity Ratio"},
{ Generator_MicroTurbineFields::ReferenceElevation, "ReferenceElevation", "Reference Elevation"},
{ Generator_MicroTurbineFields::ElectricalPowerFunctionofTemperatureandElevationCurveName, "ElectricalPowerFunctionofTemperatureandElevationCurveName", "Electrical Power Function of Temperature and Elevation Curve Name"},
{ Generator_MicroTurbineFields::ElectricalEfficiencyFunctionofTemperatureCurveName, "ElectricalEfficiencyFunctionofTemperatureCurveName", "Electrical Efficiency Function of Temperature Curve Name"},
{ Generator_MicroTurbineFields::ElectricalEfficiencyFunctionofPartLoadRatioCurveName, "ElectricalEfficiencyFunctionofPartLoadRatioCurveName", "Electrical Efficiency Function of Part Load Ratio Curve Name"},
{ Generator_MicroTurbineFields::FuelType, "FuelType", "Fuel Type"},
{ Generator_MicroTurbineFields::FuelHigherHeatingValue, "FuelHigherHeatingValue", "Fuel Higher Heating Value"},
{ Generator_MicroTurbineFields::FuelLowerHeatingValue, "FuelLowerHeatingValue", "Fuel Lower Heating Value"},
{ Generator_MicroTurbineFields::StandbyPower, "StandbyPower", "Standby Power"},
{ Generator_MicroTurbineFields::AncillaryPower, "AncillaryPower", "Ancillary Power"},
{ Generator_MicroTurbineFields::AncillaryPowerFunctionofFuelInputCurveName, "AncillaryPowerFunctionofFuelInputCurveName", "Ancillary Power Function of Fuel Input Curve Name"},
{ Generator_MicroTurbineFields::HeatRecoveryWaterInletNodeName, "HeatRecoveryWaterInletNodeName", "Heat Recovery Water Inlet Node Name"},
{ Generator_MicroTurbineFields::HeatRecoveryWaterOutletNodeName, "HeatRecoveryWaterOutletNodeName", "Heat Recovery Water Outlet Node Name"},
{ Generator_MicroTurbineFields::ReferenceThermalEfficiencyUsingLowerHeatValue, "ReferenceThermalEfficiencyUsingLowerHeatValue", "Reference Thermal Efficiency Using Lower Heat Value"},
{ Generator_MicroTurbineFields::ReferenceInletWaterTemperature, "ReferenceInletWaterTemperature", "Reference Inlet Water Temperature"},
{ Generator_MicroTurbineFields::HeatRecoveryWaterFlowOperatingMode, "HeatRecoveryWaterFlowOperatingMode", "Heat Recovery Water Flow Operating Mode"},
{ Generator_MicroTurbineFields::ReferenceHeatRecoveryWaterFlowRate, "ReferenceHeatRecoveryWaterFlowRate", "Reference Heat Recovery Water Flow Rate"},
{ Generator_MicroTurbineFields::HeatRecoveryWaterFlowRateFunctionofTemperatureandPowerCurveName, "HeatRecoveryWaterFlowRateFunctionofTemperatureandPowerCurveName", "Heat Recovery Water Flow Rate Function of Temperature and Power Curve Name"},
{ Generator_MicroTurbineFields::ThermalEfficiencyFunctionofTemperatureandElevationCurveName, "ThermalEfficiencyFunctionofTemperatureandElevationCurveName", "Thermal Efficiency Function of Temperature and Elevation Curve Name"},
{ Generator_MicroTurbineFields::HeatRecoveryRateFunctionofPartLoadRatioCurveName, "HeatRecoveryRateFunctionofPartLoadRatioCurveName", "Heat Recovery Rate Function of Part Load Ratio Curve Name"},
{ Generator_MicroTurbineFields::HeatRecoveryRateFunctionofInletWaterTemperatureCurveName, "HeatRecoveryRateFunctionofInletWaterTemperatureCurveName", "Heat Recovery Rate Function of Inlet Water Temperature Curve Name"},
{ Generator_MicroTurbineFields::HeatRecoveryRateFunctionofWaterFlowRateCurveName, "HeatRecoveryRateFunctionofWaterFlowRateCurveName", "Heat Recovery Rate Function of Water Flow Rate Curve Name"},
{ Generator_MicroTurbineFields::MinimumHeatRecoveryWaterFlowRate, "MinimumHeatRecoveryWaterFlowRate", "Minimum Heat Recovery Water Flow Rate"},
{ Generator_MicroTurbineFields::MaximumHeatRecoveryWaterFlowRate, "MaximumHeatRecoveryWaterFlowRate", "Maximum Heat Recovery Water Flow Rate"},
{ Generator_MicroTurbineFields::MaximumHeatRecoveryWaterTemperature, "MaximumHeatRecoveryWaterTemperature", "Maximum Heat Recovery Water Temperature"},
{ Generator_MicroTurbineFields::CombustionAirInletNodeName, "CombustionAirInletNodeName", "Combustion Air Inlet Node Name"},
{ Generator_MicroTurbineFields::CombustionAirOutletNodeName, "CombustionAirOutletNodeName", "Combustion Air Outlet Node Name"},
{ Generator_MicroTurbineFields::ReferenceExhaustAirMassFlowRate, "ReferenceExhaustAirMassFlowRate", "Reference Exhaust Air Mass Flow Rate"},
{ Generator_MicroTurbineFields::ExhaustAirFlowRateFunctionofTemperatureCurveName, "ExhaustAirFlowRateFunctionofTemperatureCurveName", "Exhaust Air Flow Rate Function of Temperature Curve Name"},
{ Generator_MicroTurbineFields::ExhaustAirFlowRateFunctionofPartLoadRatioCurveName, "ExhaustAirFlowRateFunctionofPartLoadRatioCurveName", "Exhaust Air Flow Rate Function of Part Load Ratio Curve Name"},
{ Generator_MicroTurbineFields::NominalExhaustAirOutletTemperature, "NominalExhaustAirOutletTemperature", "Nominal Exhaust Air Outlet Temperature"},
{ Generator_MicroTurbineFields::ExhaustAirTemperatureFunctionofTemperatureCurveName, "ExhaustAirTemperatureFunctionofTemperatureCurveName", "Exhaust Air Temperature Function of Temperature Curve Name"},
{ Generator_MicroTurbineFields::ExhaustAirTemperatureFunctionofPartLoadRatioCurveName, "ExhaustAirTemperatureFunctionofPartLoadRatioCurveName", "Exhaust Air Temperature Function of Part Load Ratio Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_MicroTurbineFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_MicroTurbineFields> OptionalGenerator_MicroTurbineFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_MICROTURBINE_FIELDENUMS_HXX
