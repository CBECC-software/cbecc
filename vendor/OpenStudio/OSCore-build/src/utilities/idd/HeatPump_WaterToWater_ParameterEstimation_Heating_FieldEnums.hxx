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

#ifndef UTILITIES_IDD_HEATPUMP_WATERTOWATER_PARAMETERESTIMATION_HEATING_FIELDENUMS_HXX
#define UTILITIES_IDD_HEATPUMP_WATERTOWATER_PARAMETERESTIMATION_HEATING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HeatPump_WaterToWater_ParameterEstimation_HeatingFields
 *  \brief Enumeration of HeatPump:WaterToWater:ParameterEstimation:Heating's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HeatPump_WaterToWater_ParameterEstimation_HeatingFields, )
#else
class HeatPump_WaterToWater_ParameterEstimation_HeatingFields: public ::EnumBase<HeatPump_WaterToWater_ParameterEstimation_HeatingFields> {
 public: 
  enum domain 
  {
Name, SourceSideInletNodeName, SourceSideOutletNodeName, LoadSideInletNodeName, LoadSideOutletNodeName, NominalCOP, NominalCapacity, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, LoadSideFlowRate, SourceSideFlowRate, LoadSideHeatTransferCoefficient, SourceSideHeatTransferCoefficient, PistonDisplacement, CompressorClearanceFactor, CompressorSuctionandDischargePressureDrop, Superheating, ConstantPartofElectromechanicalPowerLosses, LossFactor, HighPressureCutOff, LowPressureCutOff,   };
  HeatPump_WaterToWater_ParameterEstimation_HeatingFields()
   : EnumBase<HeatPump_WaterToWater_ParameterEstimation_HeatingFields>(Name) {} 
  HeatPump_WaterToWater_ParameterEstimation_HeatingFields(const std::string &t_name) 
   : EnumBase<HeatPump_WaterToWater_ParameterEstimation_HeatingFields>(t_name) {} 
  HeatPump_WaterToWater_ParameterEstimation_HeatingFields(int t_value) 
   : EnumBase<HeatPump_WaterToWater_ParameterEstimation_HeatingFields>(t_value) {} 
  static std::string enumName() 
  { return "HeatPump_WaterToWater_ParameterEstimation_HeatingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HeatPump_WaterToWater_ParameterEstimation_HeatingFields>::value()); }
   private:
    friend class EnumBase<HeatPump_WaterToWater_ParameterEstimation_HeatingFields>;
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
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::Name, "Name", "Name"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideInletNodeName, "SourceSideInletNodeName", "Source Side Inlet Node Name"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideOutletNodeName, "SourceSideOutletNodeName", "Source Side Outlet Node Name"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideInletNodeName, "LoadSideInletNodeName", "Load Side Inlet Node Name"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideOutletNodeName, "LoadSideOutletNodeName", "Load Side Outlet Node Name"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::NominalCOP, "NominalCOP", "Nominal COP"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::NominalCapacity, "NominalCapacity", "Nominal Capacity"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideFlowRate, "LoadSideFlowRate", "Load Side Flow Rate"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideFlowRate, "SourceSideFlowRate", "Source Side Flow Rate"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LoadSideHeatTransferCoefficient, "LoadSideHeatTransferCoefficient", "Load Side Heat Transfer Coefficient"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::SourceSideHeatTransferCoefficient, "SourceSideHeatTransferCoefficient", "Source Side Heat Transfer Coefficient"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::PistonDisplacement, "PistonDisplacement", "Piston Displacement"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::CompressorClearanceFactor, "CompressorClearanceFactor", "Compressor Clearance Factor"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::CompressorSuctionandDischargePressureDrop, "CompressorSuctionandDischargePressureDrop", "Compressor Suction and Discharge Pressure Drop"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::Superheating, "Superheating", "Superheating"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::ConstantPartofElectromechanicalPowerLosses, "ConstantPartofElectromechanicalPowerLosses", "Constant Part of Electromechanical Power Losses"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LossFactor, "LossFactor", "Loss Factor"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::HighPressureCutOff, "HighPressureCutOff", "High Pressure Cut Off"},
{ HeatPump_WaterToWater_ParameterEstimation_HeatingFields::LowPressureCutOff, "LowPressureCutOff", "Low Pressure Cut Off"},
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
  inline std::ostream &operator<<(std::ostream &os, const HeatPump_WaterToWater_ParameterEstimation_HeatingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HeatPump_WaterToWater_ParameterEstimation_HeatingFields> OptionalHeatPump_WaterToWater_ParameterEstimation_HeatingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HEATPUMP_WATERTOWATER_PARAMETERESTIMATION_HEATING_FIELDENUMS_HXX
