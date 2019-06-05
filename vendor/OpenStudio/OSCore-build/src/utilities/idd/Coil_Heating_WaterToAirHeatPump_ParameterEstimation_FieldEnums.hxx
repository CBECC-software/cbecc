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

#ifndef UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_PARAMETERESTIMATION_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_PARAMETERESTIMATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields
 *  \brief Enumeration of Coil:Heating:WaterToAirHeatPump:ParameterEstimation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields, )
#else
class Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields: public ::EnumBase<Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields> {
 public: 
  enum domain 
  {
Name, CompressorType, RefrigerantType, DesignSourceSideFlowRate, GrossRatedHeatingCapacity, HighPressureCutoff, LowPressureCutoff, WaterInletNodeName, WaterOutletNodeName, AirInletNodeName, AirOutletNodeName, LoadSideTotalHeatTransferCoefficient, SuperheatTemperatureattheEvaporatorOutlet, CompressorPowerLosses, CompressorEfficiency, CompressorPistonDisplacement, CompressorSuction_DischargePressureDrop, CompressorClearanceFactor, RefrigerantVolumeFlowRate, VolumeRatio, LeakRateCoefficient, SourceSideHeatTransferCoefficient, SourceSideHeatTransferResistance1, SourceSideHeatTransferResistance2,   };
  Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields()
   : EnumBase<Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields>(Name) {} 
  Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields(const std::string &t_name) 
   : EnumBase<Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields>(t_name) {} 
  Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields(int t_value) 
   : EnumBase<Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields>::value()); }
   private:
    friend class EnumBase<Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields>;
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
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::Name, "Name", "Name"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorType, "CompressorType", "Compressor Type"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::RefrigerantType, "RefrigerantType", "Refrigerant Type"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::DesignSourceSideFlowRate, "DesignSourceSideFlowRate", "Design Source Side Flow Rate"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::GrossRatedHeatingCapacity, "GrossRatedHeatingCapacity", "Gross Rated Heating Capacity"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::HighPressureCutoff, "HighPressureCutoff", "High Pressure Cutoff"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::LowPressureCutoff, "LowPressureCutoff", "Low Pressure Cutoff"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::LoadSideTotalHeatTransferCoefficient, "LoadSideTotalHeatTransferCoefficient", "Load Side Total Heat Transfer Coefficient"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SuperheatTemperatureattheEvaporatorOutlet, "SuperheatTemperatureattheEvaporatorOutlet", "Superheat Temperature at the Evaporator Outlet"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorPowerLosses, "CompressorPowerLosses", "Compressor Power Losses"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorEfficiency, "CompressorEfficiency", "Compressor Efficiency"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorPistonDisplacement, "CompressorPistonDisplacement", "Compressor Piston Displacement"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorSuction_DischargePressureDrop, "CompressorSuction_DischargePressureDrop", "Compressor Suction/Discharge Pressure Drop"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::CompressorClearanceFactor, "CompressorClearanceFactor", "Compressor Clearance Factor"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::RefrigerantVolumeFlowRate, "RefrigerantVolumeFlowRate", "Refrigerant Volume Flow Rate"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::VolumeRatio, "VolumeRatio", "Volume Ratio"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::LeakRateCoefficient, "LeakRateCoefficient", "Leak Rate Coefficient"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferCoefficient, "SourceSideHeatTransferCoefficient", "Source Side Heat Transfer Coefficient"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance1, "SourceSideHeatTransferResistance1", "Source Side Heat Transfer Resistance1"},
{ Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields::SourceSideHeatTransferResistance2, "SourceSideHeatTransferResistance2", "Source Side Heat Transfer Resistance2"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_Heating_WaterToAirHeatPump_ParameterEstimationFields> OptionalCoil_Heating_WaterToAirHeatPump_ParameterEstimationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_HEATING_WATERTOAIRHEATPUMP_PARAMETERESTIMATION_FIELDENUMS_HXX
