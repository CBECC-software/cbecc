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

#ifndef UTILITIES_IDD_CHILLER_COMBUSTIONTURBINE_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLER_COMBUSTIONTURBINE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Chiller_CombustionTurbineFields
 *  \brief Enumeration of Chiller:CombustionTurbine's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Chiller_CombustionTurbineFields, )
#else
class Chiller_CombustionTurbineFields: public ::EnumBase<Chiller_CombustionTurbineFields> {
 public: 
  enum domain 
  {
Name, CondenserType, NominalCapacity, NominalCOP, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, DesignCondenserInletTemperature, TemperatureRiseCoefficient, DesignChilledWaterOutletTemperature, DesignChilledWaterFlowRate, DesignCondenserWaterFlowRate, Coefficient1ofCapacityRatioCurve, Coefficient2ofCapacityRatioCurve, Coefficient3ofCapacityRatioCurve, Coefficient1ofPowerRatioCurve, Coefficient2ofPowerRatioCurve, Coefficient3ofPowerRatioCurve, Coefficient1ofFullLoadRatioCurve, Coefficient2ofFullLoadRatioCurve, Coefficient3ofFullLoadRatioCurve, ChilledWaterOutletTemperatureLowerLimit, Coefficient1ofFuelInputCurve, Coefficient2ofFuelInputCurve, Coefficient3ofFuelInputCurve, Coefficient1ofTemperatureBasedFuelInputCurve, Coefficient2ofTemperatureBasedFuelInputCurve, Coefficient3ofTemperatureBasedFuelInputCurve, Coefficient1ofExhaustFlowCurve, Coefficient2ofExhaustFlowCurve, Coefficient3ofExhaustFlowCurve, Coefficient1ofExhaustGasTemperatureCurve, Coefficient2ofExhaustGasTemperatureCurve, Coefficient3ofExhaustGasTemperatureCurve, Coefficient1ofTemperatureBasedExhaustGasTemperatureCurve, Coefficient2ofTemperatureBasedExhaustGasTemperatureCurve, Coefficient3ofTemperatureBasedExhaustGasTemperatureCurve, Coefficient1ofRecoveryLubeHeatCurve, Coefficient2ofRecoveryLubeHeatCurve, Coefficient3ofRecoveryLubeHeatCurve, Coefficient1ofUFactorTimesAreaCurve, Coefficient2ofUFactorTimesAreaCurve, GasTurbineEngineCapacity, MaximumExhaustFlowperUnitofPowerOutput, DesignSteamSaturationTemperature, FuelHigherHeatingValue, DesignHeatRecoveryWaterFlowRate, HeatRecoveryInletNodeName, HeatRecoveryOutletNodeName, ChillerFlowMode, FuelType, HeatRecoveryMaximumTemperature, SizingFactor, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, CondenserHeatRecoveryRelativeCapacityFraction, TurbineEngineEfficiency,   };
  Chiller_CombustionTurbineFields()
   : EnumBase<Chiller_CombustionTurbineFields>(Name) {} 
  Chiller_CombustionTurbineFields(const std::string &t_name) 
   : EnumBase<Chiller_CombustionTurbineFields>(t_name) {} 
  Chiller_CombustionTurbineFields(int t_value) 
   : EnumBase<Chiller_CombustionTurbineFields>(t_value) {} 
  static std::string enumName() 
  { return "Chiller_CombustionTurbineFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Chiller_CombustionTurbineFields>::value()); }
   private:
    friend class EnumBase<Chiller_CombustionTurbineFields>;
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
{ Chiller_CombustionTurbineFields::Name, "Name", "Name"},
{ Chiller_CombustionTurbineFields::CondenserType, "CondenserType", "Condenser Type"},
{ Chiller_CombustionTurbineFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ Chiller_CombustionTurbineFields::NominalCOP, "NominalCOP", "Nominal COP"},
{ Chiller_CombustionTurbineFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ Chiller_CombustionTurbineFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ Chiller_CombustionTurbineFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ Chiller_CombustionTurbineFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ Chiller_CombustionTurbineFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ Chiller_CombustionTurbineFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ Chiller_CombustionTurbineFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ Chiller_CombustionTurbineFields::DesignCondenserInletTemperature, "DesignCondenserInletTemperature", "Design Condenser Inlet Temperature"},
{ Chiller_CombustionTurbineFields::TemperatureRiseCoefficient, "TemperatureRiseCoefficient", "Temperature Rise Coefficient"},
{ Chiller_CombustionTurbineFields::DesignChilledWaterOutletTemperature, "DesignChilledWaterOutletTemperature", "Design Chilled Water Outlet Temperature"},
{ Chiller_CombustionTurbineFields::DesignChilledWaterFlowRate, "DesignChilledWaterFlowRate", "Design Chilled Water Flow Rate"},
{ Chiller_CombustionTurbineFields::DesignCondenserWaterFlowRate, "DesignCondenserWaterFlowRate", "Design Condenser Water Flow Rate"},
{ Chiller_CombustionTurbineFields::Coefficient1ofCapacityRatioCurve, "Coefficient1ofCapacityRatioCurve", "Coefficient 1 of Capacity Ratio Curve"},
{ Chiller_CombustionTurbineFields::Coefficient2ofCapacityRatioCurve, "Coefficient2ofCapacityRatioCurve", "Coefficient 2 of Capacity Ratio Curve"},
{ Chiller_CombustionTurbineFields::Coefficient3ofCapacityRatioCurve, "Coefficient3ofCapacityRatioCurve", "Coefficient 3 of Capacity Ratio Curve"},
{ Chiller_CombustionTurbineFields::Coefficient1ofPowerRatioCurve, "Coefficient1ofPowerRatioCurve", "Coefficient 1 of Power Ratio Curve"},
{ Chiller_CombustionTurbineFields::Coefficient2ofPowerRatioCurve, "Coefficient2ofPowerRatioCurve", "Coefficient 2 of Power Ratio Curve"},
{ Chiller_CombustionTurbineFields::Coefficient3ofPowerRatioCurve, "Coefficient3ofPowerRatioCurve", "Coefficient 3 of Power Ratio Curve"},
{ Chiller_CombustionTurbineFields::Coefficient1ofFullLoadRatioCurve, "Coefficient1ofFullLoadRatioCurve", "Coefficient 1 of Full Load Ratio Curve"},
{ Chiller_CombustionTurbineFields::Coefficient2ofFullLoadRatioCurve, "Coefficient2ofFullLoadRatioCurve", "Coefficient 2 of Full Load Ratio Curve"},
{ Chiller_CombustionTurbineFields::Coefficient3ofFullLoadRatioCurve, "Coefficient3ofFullLoadRatioCurve", "Coefficient 3 of Full Load Ratio Curve"},
{ Chiller_CombustionTurbineFields::ChilledWaterOutletTemperatureLowerLimit, "ChilledWaterOutletTemperatureLowerLimit", "Chilled Water Outlet Temperature Lower Limit"},
{ Chiller_CombustionTurbineFields::Coefficient1ofFuelInputCurve, "Coefficient1ofFuelInputCurve", "Coefficient 1 of Fuel Input Curve"},
{ Chiller_CombustionTurbineFields::Coefficient2ofFuelInputCurve, "Coefficient2ofFuelInputCurve", "Coefficient 2 of Fuel Input Curve"},
{ Chiller_CombustionTurbineFields::Coefficient3ofFuelInputCurve, "Coefficient3ofFuelInputCurve", "Coefficient 3 of Fuel Input Curve"},
{ Chiller_CombustionTurbineFields::Coefficient1ofTemperatureBasedFuelInputCurve, "Coefficient1ofTemperatureBasedFuelInputCurve", "Coefficient 1 of Temperature Based Fuel Input Curve"},
{ Chiller_CombustionTurbineFields::Coefficient2ofTemperatureBasedFuelInputCurve, "Coefficient2ofTemperatureBasedFuelInputCurve", "Coefficient 2 of Temperature Based Fuel Input Curve"},
{ Chiller_CombustionTurbineFields::Coefficient3ofTemperatureBasedFuelInputCurve, "Coefficient3ofTemperatureBasedFuelInputCurve", "Coefficient 3 of Temperature Based Fuel Input Curve"},
{ Chiller_CombustionTurbineFields::Coefficient1ofExhaustFlowCurve, "Coefficient1ofExhaustFlowCurve", "Coefficient 1 of Exhaust Flow Curve"},
{ Chiller_CombustionTurbineFields::Coefficient2ofExhaustFlowCurve, "Coefficient2ofExhaustFlowCurve", "Coefficient 2 of Exhaust Flow Curve"},
{ Chiller_CombustionTurbineFields::Coefficient3ofExhaustFlowCurve, "Coefficient3ofExhaustFlowCurve", "Coefficient 3 of Exhaust Flow Curve"},
{ Chiller_CombustionTurbineFields::Coefficient1ofExhaustGasTemperatureCurve, "Coefficient1ofExhaustGasTemperatureCurve", "Coefficient 1 of Exhaust Gas Temperature Curve"},
{ Chiller_CombustionTurbineFields::Coefficient2ofExhaustGasTemperatureCurve, "Coefficient2ofExhaustGasTemperatureCurve", "Coefficient 2 of Exhaust Gas Temperature Curve"},
{ Chiller_CombustionTurbineFields::Coefficient3ofExhaustGasTemperatureCurve, "Coefficient3ofExhaustGasTemperatureCurve", "Coefficient 3 of Exhaust Gas Temperature Curve"},
{ Chiller_CombustionTurbineFields::Coefficient1ofTemperatureBasedExhaustGasTemperatureCurve, "Coefficient1ofTemperatureBasedExhaustGasTemperatureCurve", "Coefficient 1 of Temperature Based Exhaust Gas Temperature Curve"},
{ Chiller_CombustionTurbineFields::Coefficient2ofTemperatureBasedExhaustGasTemperatureCurve, "Coefficient2ofTemperatureBasedExhaustGasTemperatureCurve", "Coefficient 2 of Temperature Based Exhaust Gas Temperature Curve"},
{ Chiller_CombustionTurbineFields::Coefficient3ofTemperatureBasedExhaustGasTemperatureCurve, "Coefficient3ofTemperatureBasedExhaustGasTemperatureCurve", "Coefficient 3 of Temperature Based Exhaust Gas Temperature Curve"},
{ Chiller_CombustionTurbineFields::Coefficient1ofRecoveryLubeHeatCurve, "Coefficient1ofRecoveryLubeHeatCurve", "Coefficient 1 of Recovery Lube Heat Curve"},
{ Chiller_CombustionTurbineFields::Coefficient2ofRecoveryLubeHeatCurve, "Coefficient2ofRecoveryLubeHeatCurve", "Coefficient 2 of Recovery Lube Heat Curve"},
{ Chiller_CombustionTurbineFields::Coefficient3ofRecoveryLubeHeatCurve, "Coefficient3ofRecoveryLubeHeatCurve", "Coefficient 3 of Recovery Lube Heat Curve"},
{ Chiller_CombustionTurbineFields::Coefficient1ofUFactorTimesAreaCurve, "Coefficient1ofUFactorTimesAreaCurve", "Coefficient 1 of U-Factor Times Area Curve"},
{ Chiller_CombustionTurbineFields::Coefficient2ofUFactorTimesAreaCurve, "Coefficient2ofUFactorTimesAreaCurve", "Coefficient 2 of U-Factor Times Area Curve"},
{ Chiller_CombustionTurbineFields::GasTurbineEngineCapacity, "GasTurbineEngineCapacity", "Gas Turbine Engine Capacity"},
{ Chiller_CombustionTurbineFields::MaximumExhaustFlowperUnitofPowerOutput, "MaximumExhaustFlowperUnitofPowerOutput", "Maximum Exhaust Flow per Unit of Power Output"},
{ Chiller_CombustionTurbineFields::DesignSteamSaturationTemperature, "DesignSteamSaturationTemperature", "Design Steam Saturation Temperature"},
{ Chiller_CombustionTurbineFields::FuelHigherHeatingValue, "FuelHigherHeatingValue", "Fuel Higher Heating Value"},
{ Chiller_CombustionTurbineFields::DesignHeatRecoveryWaterFlowRate, "DesignHeatRecoveryWaterFlowRate", "Design Heat Recovery Water Flow Rate"},
{ Chiller_CombustionTurbineFields::HeatRecoveryInletNodeName, "HeatRecoveryInletNodeName", "Heat Recovery Inlet Node Name"},
{ Chiller_CombustionTurbineFields::HeatRecoveryOutletNodeName, "HeatRecoveryOutletNodeName", "Heat Recovery Outlet Node Name"},
{ Chiller_CombustionTurbineFields::ChillerFlowMode, "ChillerFlowMode", "Chiller Flow Mode"},
{ Chiller_CombustionTurbineFields::FuelType, "FuelType", "Fuel Type"},
{ Chiller_CombustionTurbineFields::HeatRecoveryMaximumTemperature, "HeatRecoveryMaximumTemperature", "Heat Recovery Maximum Temperature"},
{ Chiller_CombustionTurbineFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ Chiller_CombustionTurbineFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ Chiller_CombustionTurbineFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ Chiller_CombustionTurbineFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ Chiller_CombustionTurbineFields::CondenserHeatRecoveryRelativeCapacityFraction, "CondenserHeatRecoveryRelativeCapacityFraction", "Condenser Heat Recovery Relative Capacity Fraction"},
{ Chiller_CombustionTurbineFields::TurbineEngineEfficiency, "TurbineEngineEfficiency", "Turbine Engine Efficiency"},
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
  inline std::ostream &operator<<(std::ostream &os, const Chiller_CombustionTurbineFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Chiller_CombustionTurbineFields> OptionalChiller_CombustionTurbineFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLER_COMBUSTIONTURBINE_FIELDENUMS_HXX
