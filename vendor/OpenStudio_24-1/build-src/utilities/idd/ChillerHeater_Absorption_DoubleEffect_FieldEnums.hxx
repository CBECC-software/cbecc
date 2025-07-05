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

#ifndef UTILITIES_IDD_CHILLERHEATER_ABSORPTION_DOUBLEEFFECT_FIELDENUMS_HXX
#define UTILITIES_IDD_CHILLERHEATER_ABSORPTION_DOUBLEEFFECT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ChillerHeater_Absorption_DoubleEffectFields
 *  \brief Enumeration of ChillerHeater:Absorption:DoubleEffect's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ChillerHeater_Absorption_DoubleEffectFields, )
#else
class ChillerHeater_Absorption_DoubleEffectFields: public ::EnumBase<ChillerHeater_Absorption_DoubleEffectFields> {
 public: 
  enum domain 
  {
Name, NominalCoolingCapacity, HeatingtoCoolingCapacityRatio, ThermalEnergyInputtoCoolingOutputRatio, ThermalEnergyInputtoHeatingOutputRatio, ElectricInputtoCoolingOutputRatio, ElectricInputtoHeatingOutputRatio, ChilledWaterInletNodeName, ChilledWaterOutletNodeName, CondenserInletNodeName, CondenserOutletNodeName, HotWaterInletNodeName, HotWaterOutletNodeName, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, DesignEnteringCondenserWaterTemperature, DesignLeavingChilledWaterTemperature, DesignChilledWaterFlowRate, DesignCondenserWaterFlowRate, DesignHotWaterFlowRate, CoolingCapacityFunctionofTemperatureCurveName, FuelInputtoCoolingOutputRatioFunctionofTemperatureCurveName, FuelInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, HeatingCapacityFunctionofCoolingCapacityCurveName, FuelInputtoHeatOutputRatioDuringHeatingOnlyOperationCurveName, TemperatureCurveInputVariable, CondenserType, ChilledWaterTemperatureLowerLimit, ExhaustSourceObjectType, ExhaustSourceObjectName, SizingFactor,   };
  ChillerHeater_Absorption_DoubleEffectFields()
   : EnumBase<ChillerHeater_Absorption_DoubleEffectFields>(Name) {} 
  ChillerHeater_Absorption_DoubleEffectFields(const std::string &t_name) 
   : EnumBase<ChillerHeater_Absorption_DoubleEffectFields>(t_name) {} 
  ChillerHeater_Absorption_DoubleEffectFields(int t_value) 
   : EnumBase<ChillerHeater_Absorption_DoubleEffectFields>(t_value) {} 
  static std::string enumName() 
  { return "ChillerHeater_Absorption_DoubleEffectFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ChillerHeater_Absorption_DoubleEffectFields>::value()); }
   private:
    friend class EnumBase<ChillerHeater_Absorption_DoubleEffectFields>;
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
{ ChillerHeater_Absorption_DoubleEffectFields::Name, "Name", "Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::NominalCoolingCapacity, "NominalCoolingCapacity", "Nominal Cooling Capacity"},
{ ChillerHeater_Absorption_DoubleEffectFields::HeatingtoCoolingCapacityRatio, "HeatingtoCoolingCapacityRatio", "Heating to Cooling Capacity Ratio"},
{ ChillerHeater_Absorption_DoubleEffectFields::ThermalEnergyInputtoCoolingOutputRatio, "ThermalEnergyInputtoCoolingOutputRatio", "Thermal Energy Input to Cooling Output Ratio"},
{ ChillerHeater_Absorption_DoubleEffectFields::ThermalEnergyInputtoHeatingOutputRatio, "ThermalEnergyInputtoHeatingOutputRatio", "Thermal Energy Input to Heating Output Ratio"},
{ ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoCoolingOutputRatio, "ElectricInputtoCoolingOutputRatio", "Electric Input to Cooling Output Ratio"},
{ ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoHeatingOutputRatio, "ElectricInputtoHeatingOutputRatio", "Electric Input to Heating Output Ratio"},
{ ChillerHeater_Absorption_DoubleEffectFields::ChilledWaterInletNodeName, "ChilledWaterInletNodeName", "Chilled Water Inlet Node Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::ChilledWaterOutletNodeName, "ChilledWaterOutletNodeName", "Chilled Water Outlet Node Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::CondenserInletNodeName, "CondenserInletNodeName", "Condenser Inlet Node Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::CondenserOutletNodeName, "CondenserOutletNodeName", "Condenser Outlet Node Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::HotWaterInletNodeName, "HotWaterInletNodeName", "Hot Water Inlet Node Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::HotWaterOutletNodeName, "HotWaterOutletNodeName", "Hot Water Outlet Node Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ ChillerHeater_Absorption_DoubleEffectFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ ChillerHeater_Absorption_DoubleEffectFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ ChillerHeater_Absorption_DoubleEffectFields::DesignEnteringCondenserWaterTemperature, "DesignEnteringCondenserWaterTemperature", "Design Entering Condenser Water Temperature"},
{ ChillerHeater_Absorption_DoubleEffectFields::DesignLeavingChilledWaterTemperature, "DesignLeavingChilledWaterTemperature", "Design Leaving Chilled Water Temperature"},
{ ChillerHeater_Absorption_DoubleEffectFields::DesignChilledWaterFlowRate, "DesignChilledWaterFlowRate", "Design Chilled Water Flow Rate"},
{ ChillerHeater_Absorption_DoubleEffectFields::DesignCondenserWaterFlowRate, "DesignCondenserWaterFlowRate", "Design Condenser Water Flow Rate"},
{ ChillerHeater_Absorption_DoubleEffectFields::DesignHotWaterFlowRate, "DesignHotWaterFlowRate", "Design Hot Water Flow Rate"},
{ ChillerHeater_Absorption_DoubleEffectFields::CoolingCapacityFunctionofTemperatureCurveName, "CoolingCapacityFunctionofTemperatureCurveName", "Cooling Capacity Function of Temperature Curve Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::FuelInputtoCoolingOutputRatioFunctionofTemperatureCurveName, "FuelInputtoCoolingOutputRatioFunctionofTemperatureCurveName", "Fuel Input to Cooling Output Ratio Function of Temperature Curve Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::FuelInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, "FuelInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName", "Fuel Input to Cooling Output Ratio Function of Part Load Ratio Curve Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName, "ElectricInputtoCoolingOutputRatioFunctionofTemperatureCurveName", "Electric Input to Cooling Output Ratio Function of Temperature Curve Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName, "ElectricInputtoCoolingOutputRatioFunctionofPartLoadRatioCurveName", "Electric Input to Cooling Output Ratio Function of Part Load Ratio Curve Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::HeatingCapacityFunctionofCoolingCapacityCurveName, "HeatingCapacityFunctionofCoolingCapacityCurveName", "Heating Capacity Function of Cooling Capacity Curve Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::FuelInputtoHeatOutputRatioDuringHeatingOnlyOperationCurveName, "FuelInputtoHeatOutputRatioDuringHeatingOnlyOperationCurveName", "Fuel Input to Heat Output Ratio During Heating Only Operation Curve Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::TemperatureCurveInputVariable, "TemperatureCurveInputVariable", "Temperature Curve Input Variable"},
{ ChillerHeater_Absorption_DoubleEffectFields::CondenserType, "CondenserType", "Condenser Type"},
{ ChillerHeater_Absorption_DoubleEffectFields::ChilledWaterTemperatureLowerLimit, "ChilledWaterTemperatureLowerLimit", "Chilled Water Temperature Lower Limit"},
{ ChillerHeater_Absorption_DoubleEffectFields::ExhaustSourceObjectType, "ExhaustSourceObjectType", "Exhaust Source Object Type"},
{ ChillerHeater_Absorption_DoubleEffectFields::ExhaustSourceObjectName, "ExhaustSourceObjectName", "Exhaust Source Object Name"},
{ ChillerHeater_Absorption_DoubleEffectFields::SizingFactor, "SizingFactor", "Sizing Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const ChillerHeater_Absorption_DoubleEffectFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ChillerHeater_Absorption_DoubleEffectFields> OptionalChillerHeater_Absorption_DoubleEffectFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CHILLERHEATER_ABSORPTION_DOUBLEEFFECT_FIELDENUMS_HXX
