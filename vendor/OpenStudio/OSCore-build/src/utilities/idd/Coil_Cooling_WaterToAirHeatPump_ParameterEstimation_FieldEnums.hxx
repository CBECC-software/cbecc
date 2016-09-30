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

#ifndef UTILITIES_IDD_COIL_COOLING_WATERTOAIRHEATPUMP_PARAMETERESTIMATION_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_COOLING_WATERTOAIRHEATPUMP_PARAMETERESTIMATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields
 *  \brief Enumeration of Coil:Cooling:WaterToAirHeatPump:ParameterEstimation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields, )
#else
class Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields: public ::EnumBase<Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields> {
 public: 
  enum domain 
  {
Name, CompressorType, RefrigerantType, DesignSourceSideFlowRate, NominalCoolingCoilCapacity, NominalTimeforCondensateRemovaltoBegin, RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, HighPressureCutoff, LowPressureCutoff, WaterInletNodeName, WaterOutletNodeName, AirInletNodeName, AirOutletNodeName, LoadSideTotalHeatTransferCoefficient, LoadSideOutsideSurfaceHeatTransferCoefficient, SuperheatTemperatureattheEvaporatorOutlet, CompressorPowerLosses, CompressorEfficiency, CompressorPistonDisplacement, CompressorSuction_DischargePressureDrop, CompressorClearanceFactor, RefrigerantVolumeFlowRate, VolumeRatio, LeakRateCoefficient, SourceSideHeatTransferCoefficient, SourceSideHeatTransferResistance1, SourceSideHeatTransferResistance2,   };
  Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields()
   : EnumBase<Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields>(Name) {} 
  Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields(const std::string &t_name) 
   : EnumBase<Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields>(t_name) {} 
  Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields(int t_value) 
   : EnumBase<Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields>::value()); }
   private:
    friend class EnumBase<Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields>;
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
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::Name, "Name", "Name"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorType, "CompressorType", "Compressor Type"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::RefrigerantType, "RefrigerantType", "Refrigerant Type"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::DesignSourceSideFlowRate, "DesignSourceSideFlowRate", "Design Source Side Flow Rate"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::NominalCoolingCoilCapacity, "NominalCoolingCoilCapacity", "Nominal Cooling Coil Capacity"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::NominalTimeforCondensateRemovaltoBegin, "NominalTimeforCondensateRemovaltoBegin", "Nominal Time for Condensate Removal to Begin"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity, "RatioofInitialMoistureEvaporationRateandSteadyStateLatentCapacity", "Ratio of Initial Moisture Evaporation Rate and Steady State Latent Capacity"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::HighPressureCutoff, "HighPressureCutoff", "High Pressure Cutoff"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LowPressureCutoff, "LowPressureCutoff", "Low Pressure Cutoff"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LoadSideTotalHeatTransferCoefficient, "LoadSideTotalHeatTransferCoefficient", "Load Side Total Heat Transfer Coefficient"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LoadSideOutsideSurfaceHeatTransferCoefficient, "LoadSideOutsideSurfaceHeatTransferCoefficient", "Load Side Outside Surface Heat Transfer Coefficient"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SuperheatTemperatureattheEvaporatorOutlet, "SuperheatTemperatureattheEvaporatorOutlet", "Superheat Temperature at the Evaporator Outlet"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorPowerLosses, "CompressorPowerLosses", "Compressor Power Losses"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorEfficiency, "CompressorEfficiency", "Compressor Efficiency"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorPistonDisplacement, "CompressorPistonDisplacement", "Compressor Piston Displacement"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorSuction_DischargePressureDrop, "CompressorSuction_DischargePressureDrop", "Compressor Suction/Discharge Pressure Drop"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::CompressorClearanceFactor, "CompressorClearanceFactor", "Compressor Clearance Factor"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::RefrigerantVolumeFlowRate, "RefrigerantVolumeFlowRate", "Refrigerant Volume Flow Rate"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::VolumeRatio, "VolumeRatio", "Volume Ratio"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::LeakRateCoefficient, "LeakRateCoefficient", "Leak Rate Coefficient"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferCoefficient, "SourceSideHeatTransferCoefficient", "Source Side Heat Transfer Coefficient"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance1, "SourceSideHeatTransferResistance1", "Source Side Heat Transfer Resistance1"},
{ Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance2, "SourceSideHeatTransferResistance2", "Source Side Heat Transfer Resistance2"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Cooling_WaterToAirHeatPump_ParameterEstimationFields> OptionalCoil_Cooling_WaterToAirHeatPump_ParameterEstimationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_COOLING_WATERTOAIRHEATPUMP_PARAMETERESTIMATION_FIELDENUMS_HXX
