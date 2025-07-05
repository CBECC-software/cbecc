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

#ifndef UTILITIES_IDD_COOLINGTOWER_VARIABLESPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_COOLINGTOWER_VARIABLESPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class CoolingTower_VariableSpeedFields
 *  \brief Enumeration of CoolingTower:VariableSpeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(CoolingTower_VariableSpeedFields, )
#else
class CoolingTower_VariableSpeedFields: public ::EnumBase<CoolingTower_VariableSpeedFields> {
 public: 
  enum domain 
  {
Name, WaterInletNodeName, WaterOutletNodeName, ModelType, ModelCoefficientName, DesignInletAirWetBulbTemperature, DesignApproachTemperature, DesignRangeTemperature, DesignWaterFlowRate, DesignAirFlowRate, DesignFanPower, FanPowerRatioFunctionofAirFlowRateRatioCurveName, MinimumAirFlowRateRatio, FractionofTowerCapacityinFreeConvectionRegime, BasinHeaterCapacity, BasinHeaterSetpointTemperature, BasinHeaterOperatingScheduleName, EvaporationLossMode, EvaporationLossFactor, DriftLossPercent, BlowdownCalculationMode, BlowdownConcentrationRatio, BlowdownMakeupWaterUsageScheduleName, SupplyWaterStorageTankName, OutdoorAirInletNodeName, NumberofCells, CellControl, CellMinimumWaterFlowRateFraction, CellMaximumWaterFlowRateFraction, SizingFactor, EndUseSubcategory,   };
  CoolingTower_VariableSpeedFields()
   : EnumBase<CoolingTower_VariableSpeedFields>(Name) {} 
  CoolingTower_VariableSpeedFields(const std::string &t_name) 
   : EnumBase<CoolingTower_VariableSpeedFields>(t_name) {} 
  CoolingTower_VariableSpeedFields(int t_value) 
   : EnumBase<CoolingTower_VariableSpeedFields>(t_value) {} 
  static std::string enumName() 
  { return "CoolingTower_VariableSpeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<CoolingTower_VariableSpeedFields>::value()); }
   private:
    friend class EnumBase<CoolingTower_VariableSpeedFields>;
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
{ CoolingTower_VariableSpeedFields::Name, "Name", "Name"},
{ CoolingTower_VariableSpeedFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ CoolingTower_VariableSpeedFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ CoolingTower_VariableSpeedFields::ModelType, "ModelType", "Model Type"},
{ CoolingTower_VariableSpeedFields::ModelCoefficientName, "ModelCoefficientName", "Model Coefficient Name"},
{ CoolingTower_VariableSpeedFields::DesignInletAirWetBulbTemperature, "DesignInletAirWetBulbTemperature", "Design Inlet Air Wet-Bulb Temperature"},
{ CoolingTower_VariableSpeedFields::DesignApproachTemperature, "DesignApproachTemperature", "Design Approach Temperature"},
{ CoolingTower_VariableSpeedFields::DesignRangeTemperature, "DesignRangeTemperature", "Design Range Temperature"},
{ CoolingTower_VariableSpeedFields::DesignWaterFlowRate, "DesignWaterFlowRate", "Design Water Flow Rate"},
{ CoolingTower_VariableSpeedFields::DesignAirFlowRate, "DesignAirFlowRate", "Design Air Flow Rate"},
{ CoolingTower_VariableSpeedFields::DesignFanPower, "DesignFanPower", "Design Fan Power"},
{ CoolingTower_VariableSpeedFields::FanPowerRatioFunctionofAirFlowRateRatioCurveName, "FanPowerRatioFunctionofAirFlowRateRatioCurveName", "Fan Power Ratio Function of Air Flow Rate Ratio Curve Name"},
{ CoolingTower_VariableSpeedFields::MinimumAirFlowRateRatio, "MinimumAirFlowRateRatio", "Minimum Air Flow Rate Ratio"},
{ CoolingTower_VariableSpeedFields::FractionofTowerCapacityinFreeConvectionRegime, "FractionofTowerCapacityinFreeConvectionRegime", "Fraction of Tower Capacity in Free Convection Regime"},
{ CoolingTower_VariableSpeedFields::BasinHeaterCapacity, "BasinHeaterCapacity", "Basin Heater Capacity"},
{ CoolingTower_VariableSpeedFields::BasinHeaterSetpointTemperature, "BasinHeaterSetpointTemperature", "Basin Heater Setpoint Temperature"},
{ CoolingTower_VariableSpeedFields::BasinHeaterOperatingScheduleName, "BasinHeaterOperatingScheduleName", "Basin Heater Operating Schedule Name"},
{ CoolingTower_VariableSpeedFields::EvaporationLossMode, "EvaporationLossMode", "Evaporation Loss Mode"},
{ CoolingTower_VariableSpeedFields::EvaporationLossFactor, "EvaporationLossFactor", "Evaporation Loss Factor"},
{ CoolingTower_VariableSpeedFields::DriftLossPercent, "DriftLossPercent", "Drift Loss Percent"},
{ CoolingTower_VariableSpeedFields::BlowdownCalculationMode, "BlowdownCalculationMode", "Blowdown Calculation Mode"},
{ CoolingTower_VariableSpeedFields::BlowdownConcentrationRatio, "BlowdownConcentrationRatio", "Blowdown Concentration Ratio"},
{ CoolingTower_VariableSpeedFields::BlowdownMakeupWaterUsageScheduleName, "BlowdownMakeupWaterUsageScheduleName", "Blowdown Makeup Water Usage Schedule Name"},
{ CoolingTower_VariableSpeedFields::SupplyWaterStorageTankName, "SupplyWaterStorageTankName", "Supply Water Storage Tank Name"},
{ CoolingTower_VariableSpeedFields::OutdoorAirInletNodeName, "OutdoorAirInletNodeName", "Outdoor Air Inlet Node Name"},
{ CoolingTower_VariableSpeedFields::NumberofCells, "NumberofCells", "Number of Cells"},
{ CoolingTower_VariableSpeedFields::CellControl, "CellControl", "Cell Control"},
{ CoolingTower_VariableSpeedFields::CellMinimumWaterFlowRateFraction, "CellMinimumWaterFlowRateFraction", "Cell Minimum  Water Flow Rate Fraction"},
{ CoolingTower_VariableSpeedFields::CellMaximumWaterFlowRateFraction, "CellMaximumWaterFlowRateFraction", "Cell Maximum Water Flow Rate Fraction"},
{ CoolingTower_VariableSpeedFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ CoolingTower_VariableSpeedFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const CoolingTower_VariableSpeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<CoolingTower_VariableSpeedFields> OptionalCoolingTower_VariableSpeedFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COOLINGTOWER_VARIABLESPEED_FIELDENUMS_HXX
