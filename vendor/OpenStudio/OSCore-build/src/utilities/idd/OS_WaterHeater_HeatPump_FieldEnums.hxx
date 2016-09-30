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

#ifndef UTILITIES_IDD_OS_WATERHEATER_HEATPUMP_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WATERHEATER_HEATPUMP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WaterHeater_HeatPumpFields
 *  \brief Enumeration of OS:WaterHeater:HeatPump's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WaterHeater_HeatPumpFields, )
#else
class OS_WaterHeater_HeatPumpFields: public ::EnumBase<OS_WaterHeater_HeatPumpFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, CompressorSetpointTemperatureSchedule, DeadBandTemperatureDifference, CondenserWaterFlowRate, EvaporatorAirFlowRate, InletAirConfiguration, AirInletNode, AirOutletNode, OutdoorAirNode, InletAirTemperatureSchedule, InletAirHumiditySchedule, Tank, DXCoil, MinimumInletAirTemperatureforCompressorOperation, CompressorLocation, CompressorAmbientTemperatureSchedule, Fan, FanPlacement, OnCycleParasiticElectricLoad, OffCycleParasiticElectricLoad, ParasiticHeatRejectionLocation, InletAirMixerSchedule, ControlSensorLocationInStratifiedTank,   };
  OS_WaterHeater_HeatPumpFields()
   : EnumBase<OS_WaterHeater_HeatPumpFields>(Handle) {} 
  OS_WaterHeater_HeatPumpFields(const std::string &t_name) 
   : EnumBase<OS_WaterHeater_HeatPumpFields>(t_name) {} 
  OS_WaterHeater_HeatPumpFields(int t_value) 
   : EnumBase<OS_WaterHeater_HeatPumpFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WaterHeater_HeatPumpFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WaterHeater_HeatPumpFields>::value()); }
   private:
    friend class EnumBase<OS_WaterHeater_HeatPumpFields>;
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
{ OS_WaterHeater_HeatPumpFields::Handle, "Handle", "Handle"},
{ OS_WaterHeater_HeatPumpFields::Name, "Name", "Name"},
{ OS_WaterHeater_HeatPumpFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_WaterHeater_HeatPumpFields::CompressorSetpointTemperatureSchedule, "CompressorSetpointTemperatureSchedule", "Compressor Setpoint Temperature Schedule"},
{ OS_WaterHeater_HeatPumpFields::DeadBandTemperatureDifference, "DeadBandTemperatureDifference", "Dead Band Temperature Difference"},
{ OS_WaterHeater_HeatPumpFields::CondenserWaterFlowRate, "CondenserWaterFlowRate", "Condenser Water Flow Rate"},
{ OS_WaterHeater_HeatPumpFields::EvaporatorAirFlowRate, "EvaporatorAirFlowRate", "Evaporator Air Flow Rate"},
{ OS_WaterHeater_HeatPumpFields::InletAirConfiguration, "InletAirConfiguration", "Inlet Air Configuration"},
{ OS_WaterHeater_HeatPumpFields::AirInletNode, "AirInletNode", "Air Inlet Node"},
{ OS_WaterHeater_HeatPumpFields::AirOutletNode, "AirOutletNode", "Air Outlet Node"},
{ OS_WaterHeater_HeatPumpFields::OutdoorAirNode, "OutdoorAirNode", "Outdoor Air Node"},
{ OS_WaterHeater_HeatPumpFields::InletAirTemperatureSchedule, "InletAirTemperatureSchedule", "Inlet Air Temperature Schedule"},
{ OS_WaterHeater_HeatPumpFields::InletAirHumiditySchedule, "InletAirHumiditySchedule", "Inlet Air Humidity Schedule"},
{ OS_WaterHeater_HeatPumpFields::Tank, "Tank", "Tank"},
{ OS_WaterHeater_HeatPumpFields::DXCoil, "DXCoil", "DX Coil"},
{ OS_WaterHeater_HeatPumpFields::MinimumInletAirTemperatureforCompressorOperation, "MinimumInletAirTemperatureforCompressorOperation", "Minimum Inlet Air Temperature for Compressor Operation"},
{ OS_WaterHeater_HeatPumpFields::CompressorLocation, "CompressorLocation", "Compressor Location"},
{ OS_WaterHeater_HeatPumpFields::CompressorAmbientTemperatureSchedule, "CompressorAmbientTemperatureSchedule", "Compressor Ambient Temperature Schedule"},
{ OS_WaterHeater_HeatPumpFields::Fan, "Fan", "Fan"},
{ OS_WaterHeater_HeatPumpFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ OS_WaterHeater_HeatPumpFields::OnCycleParasiticElectricLoad, "OnCycleParasiticElectricLoad", "On Cycle Parasitic Electric Load"},
{ OS_WaterHeater_HeatPumpFields::OffCycleParasiticElectricLoad, "OffCycleParasiticElectricLoad", "Off Cycle Parasitic Electric Load"},
{ OS_WaterHeater_HeatPumpFields::ParasiticHeatRejectionLocation, "ParasiticHeatRejectionLocation", "Parasitic Heat Rejection Location"},
{ OS_WaterHeater_HeatPumpFields::InletAirMixerSchedule, "InletAirMixerSchedule", "Inlet Air Mixer Schedule"},
{ OS_WaterHeater_HeatPumpFields::ControlSensorLocationInStratifiedTank, "ControlSensorLocationInStratifiedTank", "Control Sensor Location In Stratified Tank"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WaterHeater_HeatPumpFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WaterHeater_HeatPumpFields> OptionalOS_WaterHeater_HeatPumpFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WATERHEATER_HEATPUMP_FIELDENUMS_HXX
