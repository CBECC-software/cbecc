/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
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
  domain value() const { return static_cast<domain>(EnumBase<OS_WaterHeater_HeatPump_WrappedCondenserFields>::integer_value()); }
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
