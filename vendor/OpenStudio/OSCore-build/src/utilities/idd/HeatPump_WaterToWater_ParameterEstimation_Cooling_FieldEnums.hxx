/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_HEATPUMP_WATERTOWATER_PARAMETERESTIMATION_COOLING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_WATERTOWATER_PARAMETERESTIMATION_COOLING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_WaterToWater_ParameterEstimation_CoolingFields
 *  \brief Enumeration of HeatPump:WaterToWater:ParameterEstimation:Cooling's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_WaterToWater_ParameterEstimation_CoolingFields, )
#else
class HeatPump_WaterToWater_ParameterEstimation_CoolingFields: public ::EnumBase<HeatPump_WaterToWater_ParameterEstimation_CoolingFields> {
 public: 
  enum domain 
  {
Name, SourceSideInletNodeName, SourceSideOutletNodeName, LoadSideInletNodeName, LoadSideOutletNodeName, NominalCOP, NominalCapacity, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, LoadSideFlowRate, SourceSideFlowRate, LoadSideHeatTransferCoefficient, SourceSideHeatTransferCoefficient, PistonDisplacement, CompressorClearanceFactor, CompressorSuctionandDischargePressureDrop, Superheating, ConstantPartofElectromechanicalPowerLosses, LossFactor, HighPressureCutOff, LowPressureCutOff,   };
  HeatPump_WaterToWater_ParameterEstimation_CoolingFields()
   : EnumBase<HeatPump_WaterToWater_ParameterEstimation_CoolingFields>(Name) {} 
  HeatPump_WaterToWater_ParameterEstimation_CoolingFields(const std::string &t_name) 
   : EnumBase<HeatPump_WaterToWater_ParameterEstimation_CoolingFields>(t_name) {} 
  HeatPump_WaterToWater_ParameterEstimation_CoolingFields(int t_value) 
   : EnumBase<HeatPump_WaterToWater_ParameterEstimation_CoolingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_WaterToWater_ParameterEstimation_CoolingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_WaterToWater_ParameterEstimation_CoolingFields>::value()); }
   private:
    friend class EnumBase<HeatPump_WaterToWater_ParameterEstimation_CoolingFields>;
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
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::Name, "Name", "Name"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::NominalCOP, "NominalCOP", "Nominal COP"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LoadSideFlowRate, "LoadSideFlowRate", "Load Side Flow Rate"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::SourceSideFlowRate, "SourceSideFlowRate", "Source Side Flow Rate"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LoadSideHeatTransferCoefficient, "LoadSideHeatTransferCoefficient", "Load Side Heat Transfer Coefficient"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::SourceSideHeatTransferCoefficient, "SourceSideHeatTransferCoefficient", "Source Side Heat Transfer Coefficient"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::PistonDisplacement, "PistonDisplacement", "Piston Displacement"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::CompressorClearanceFactor, "CompressorClearanceFactor", "Compressor Clearance Factor"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::CompressorSuctionandDischargePressureDrop, "CompressorSuctionandDischargePressureDrop", "Compressor Suction and Discharge Pressure Drop"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::Superheating, "Superheating", "Superheating"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::ConstantPartofElectromechanicalPowerLosses, "ConstantPartofElectromechanicalPowerLosses", "Constant Part of Electromechanical Power Losses"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LossFactor, "LossFactor", "Loss Factor"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::HighPressureCutOff, "HighPressureCutOff", "High Pressure Cut Off"},
{ HeatPump_WaterToWater_ParameterEstimation_CoolingFields::LowPressureCutOff, "LowPressureCutOff", "Low Pressure Cut Off"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_WaterToWater_ParameterEstimation_CoolingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_WaterToWater_ParameterEstimation_CoolingFields> OptionalHeatPump_WaterToWater_ParameterEstimation_CoolingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_WATERTOWATER_PARAMETERESTIMATION_COOLING_FIELDENUMS_HXX
