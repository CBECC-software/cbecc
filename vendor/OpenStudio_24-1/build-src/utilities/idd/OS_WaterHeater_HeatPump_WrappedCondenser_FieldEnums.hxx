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

#ifndef UTILITIES_IDD_OS_WATERHEATER_HEATPUMP_WRAPPEDCONDENSER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WATERHEATER_HEATPUMP_WRAPPEDCONDENSER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WaterHeater_HeatPump_WrappedCondenserFields
 *  \brief Enumeration of OS:WaterHeater:HeatPump:WrappedCondenser's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WaterHeater_HeatPump_WrappedCondenserFields, )
#else
class OS_WaterHeater_HeatPump_WrappedCondenserFields: public ::EnumBase<OS_WaterHeater_HeatPump_WrappedCondenserFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, CompressorSetpointTemperatureScheduleName, DeadBandTemperatureDifference, CondenserBottomLocation, CondenserTopLocation, EvaporatorAirFlowRate, InletAirConfiguration, AirInletNodeName, AirOutletNodeName, OutdoorAirNodeName, InletAirTemperatureScheduleName, InletAirHumidityScheduleName, TankName, DXCoilName, MinimumInletAirTemperatureforCompressorOperation, MaximumInletAirTemperatureforCompressorOperation, CompressorLocation, CompressorAmbientTemperatureScheduleName, FanName, FanPlacement, OnCycleParasiticElectricLoad, OffCycleParasiticElectricLoad, ParasiticHeatRejectionLocation, InletAirMixerScheduleName, TankElementControlLogic, ControlSensor1HeightInStratifiedTank, ControlSensor1Weight, ControlSensor2HeightInStratifiedTank,   };
  OS_WaterHeater_HeatPump_WrappedCondenserFields()
   : EnumBase<OS_WaterHeater_HeatPump_WrappedCondenserFields>(Handle) {} 
  OS_WaterHeater_HeatPump_WrappedCondenserFields(const std::string &t_name) 
   : EnumBase<OS_WaterHeater_HeatPump_WrappedCondenserFields>(t_name) {} 
  OS_WaterHeater_HeatPump_WrappedCondenserFields(int t_value) 
   : EnumBase<OS_WaterHeater_HeatPump_WrappedCondenserFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WaterHeater_HeatPump_WrappedCondenserFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WaterHeater_HeatPump_WrappedCondenserFields>::value()); }
   private:
    friend class EnumBase<OS_WaterHeater_HeatPump_WrappedCondenserFields>;
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
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::Handle, "Handle", "Handle"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::Name, "Name", "Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::CompressorSetpointTemperatureScheduleName, "CompressorSetpointTemperatureScheduleName", "Compressor Setpoint Temperature Schedule Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::DeadBandTemperatureDifference, "DeadBandTemperatureDifference", "Dead Band Temperature Difference"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::CondenserBottomLocation, "CondenserBottomLocation", "Condenser Bottom Location"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::CondenserTopLocation, "CondenserTopLocation", "Condenser Top Location"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::EvaporatorAirFlowRate, "EvaporatorAirFlowRate", "Evaporator Air Flow Rate"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::InletAirConfiguration, "InletAirConfiguration", "Inlet Air Configuration"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::OutdoorAirNodeName, "OutdoorAirNodeName", "Outdoor Air Node Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::InletAirTemperatureScheduleName, "InletAirTemperatureScheduleName", "Inlet Air Temperature Schedule Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::InletAirHumidityScheduleName, "InletAirHumidityScheduleName", "Inlet Air Humidity Schedule Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::TankName, "TankName", "Tank Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::DXCoilName, "DXCoilName", "DX Coil Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::MinimumInletAirTemperatureforCompressorOperation, "MinimumInletAirTemperatureforCompressorOperation", "Minimum Inlet Air Temperature for Compressor Operation"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::MaximumInletAirTemperatureforCompressorOperation, "MaximumInletAirTemperatureforCompressorOperation", "Maximum Inlet Air Temperature for Compressor Operation"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::CompressorLocation, "CompressorLocation", "Compressor Location"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::CompressorAmbientTemperatureScheduleName, "CompressorAmbientTemperatureScheduleName", "Compressor Ambient Temperature Schedule Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::FanName, "FanName", "Fan Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::OnCycleParasiticElectricLoad, "OnCycleParasiticElectricLoad", "On Cycle Parasitic Electric Load"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::OffCycleParasiticElectricLoad, "OffCycleParasiticElectricLoad", "Off Cycle Parasitic Electric Load"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::ParasiticHeatRejectionLocation, "ParasiticHeatRejectionLocation", "Parasitic Heat Rejection Location"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::InletAirMixerScheduleName, "InletAirMixerScheduleName", "Inlet Air Mixer Schedule Name"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::TankElementControlLogic, "TankElementControlLogic", "Tank Element Control Logic"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1HeightInStratifiedTank, "ControlSensor1HeightInStratifiedTank", "Control Sensor 1 Height In Stratified Tank"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1Weight, "ControlSensor1Weight", "Control Sensor 1 Weight"},
{ OS_WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor2HeightInStratifiedTank, "ControlSensor2HeightInStratifiedTank", "Control Sensor 2 Height In Stratified Tank"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WaterHeater_HeatPump_WrappedCondenserFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WaterHeater_HeatPump_WrappedCondenserFields> OptionalOS_WaterHeater_HeatPump_WrappedCondenserFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WATERHEATER_HEATPUMP_WRAPPEDCONDENSER_FIELDENUMS_HXX
