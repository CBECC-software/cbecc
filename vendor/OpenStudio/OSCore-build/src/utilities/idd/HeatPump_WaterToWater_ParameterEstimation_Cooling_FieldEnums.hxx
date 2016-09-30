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
