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

#ifndef UTILITIES_IDD_WATERHEATER_HEATPUMP_WRAPPEDCONDENSER_FIELDENUMS_HXX
#define UTILITIES_IDD_WATERHEATER_HEATPUMP_WRAPPEDCONDENSER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WaterHeater_HeatPump_WrappedCondenserFields
 *  \brief Enumeration of WaterHeater:HeatPump:WrappedCondenser's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WaterHeater_HeatPump_WrappedCondenserFields, )
#else
class WaterHeater_HeatPump_WrappedCondenserFields: public ::EnumBase<WaterHeater_HeatPump_WrappedCondenserFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CompressorSetpointTemperatureScheduleName, DeadBandTemperatureDifference, CondenserBottomLocation, CondenserTopLocation, EvaporatorAirFlowRate, InletAirConfiguration, AirInletNodeName, AirOutletNodeName, OutdoorAirNodeName, ExhaustAirNodeName, InletAirTemperatureScheduleName, InletAirHumidityScheduleName, InletAirZoneName, TankObjectType, TankName, TankUseSideInletNodeName, TankUseSideOutletNodeName, DXCoilObjectType, DXCoilName, MinimumInletAirTemperatureforCompressorOperation, MaximumInletAirTemperatureforCompressorOperation, CompressorLocation, CompressorAmbientTemperatureScheduleName, FanObjectType, FanName, FanPlacement, OnCycleParasiticElectricLoad, OffCycleParasiticElectricLoad, ParasiticHeatRejectionLocation, InletAirMixerNodeName, OutletAirSplitterNodeName, InletAirMixerScheduleName, TankElementControlLogic, ControlSensor1HeightInStratifiedTank, ControlSensor1Weight, ControlSensor2HeightInStratifiedTank,   };
  WaterHeater_HeatPump_WrappedCondenserFields()
   : EnumBase<WaterHeater_HeatPump_WrappedCondenserFields>(Name) {} 
  WaterHeater_HeatPump_WrappedCondenserFields(const std::string &t_name) 
   : EnumBase<WaterHeater_HeatPump_WrappedCondenserFields>(t_name) {} 
  WaterHeater_HeatPump_WrappedCondenserFields(int t_value) 
   : EnumBase<WaterHeater_HeatPump_WrappedCondenserFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterHeater_HeatPump_WrappedCondenserFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterHeater_HeatPump_WrappedCondenserFields>::value()); }
   private:
    friend class EnumBase<WaterHeater_HeatPump_WrappedCondenserFields>;
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
{ WaterHeater_HeatPump_WrappedCondenserFields::Name, "Name", "Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::CompressorSetpointTemperatureScheduleName, "CompressorSetpointTemperatureScheduleName", "Compressor Setpoint Temperature Schedule Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::DeadBandTemperatureDifference, "DeadBandTemperatureDifference", "Dead Band Temperature Difference"},
{ WaterHeater_HeatPump_WrappedCondenserFields::CondenserBottomLocation, "CondenserBottomLocation", "Condenser Bottom Location"},
{ WaterHeater_HeatPump_WrappedCondenserFields::CondenserTopLocation, "CondenserTopLocation", "Condenser Top Location"},
{ WaterHeater_HeatPump_WrappedCondenserFields::EvaporatorAirFlowRate, "EvaporatorAirFlowRate", "Evaporator Air Flow Rate"},
{ WaterHeater_HeatPump_WrappedCondenserFields::InletAirConfiguration, "InletAirConfiguration", "Inlet Air Configuration"},
{ WaterHeater_HeatPump_WrappedCondenserFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::OutdoorAirNodeName, "OutdoorAirNodeName", "Outdoor Air Node Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::ExhaustAirNodeName, "ExhaustAirNodeName", "Exhaust Air Node Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::InletAirTemperatureScheduleName, "InletAirTemperatureScheduleName", "Inlet Air Temperature Schedule Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::InletAirHumidityScheduleName, "InletAirHumidityScheduleName", "Inlet Air Humidity Schedule Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::InletAirZoneName, "InletAirZoneName", "Inlet Air Zone Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::TankObjectType, "TankObjectType", "Tank Object Type"},
{ WaterHeater_HeatPump_WrappedCondenserFields::TankName, "TankName", "Tank Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::TankUseSideInletNodeName, "TankUseSideInletNodeName", "Tank Use Side Inlet Node Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::TankUseSideOutletNodeName, "TankUseSideOutletNodeName", "Tank Use Side Outlet Node Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::DXCoilObjectType, "DXCoilObjectType", "DX Coil Object Type"},
{ WaterHeater_HeatPump_WrappedCondenserFields::DXCoilName, "DXCoilName", "DX Coil Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::MinimumInletAirTemperatureforCompressorOperation, "MinimumInletAirTemperatureforCompressorOperation", "Minimum Inlet Air Temperature for Compressor Operation"},
{ WaterHeater_HeatPump_WrappedCondenserFields::MaximumInletAirTemperatureforCompressorOperation, "MaximumInletAirTemperatureforCompressorOperation", "Maximum Inlet Air Temperature for Compressor Operation"},
{ WaterHeater_HeatPump_WrappedCondenserFields::CompressorLocation, "CompressorLocation", "Compressor Location"},
{ WaterHeater_HeatPump_WrappedCondenserFields::CompressorAmbientTemperatureScheduleName, "CompressorAmbientTemperatureScheduleName", "Compressor Ambient Temperature Schedule Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::FanObjectType, "FanObjectType", "Fan Object Type"},
{ WaterHeater_HeatPump_WrappedCondenserFields::FanName, "FanName", "Fan Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ WaterHeater_HeatPump_WrappedCondenserFields::OnCycleParasiticElectricLoad, "OnCycleParasiticElectricLoad", "On Cycle Parasitic Electric Load"},
{ WaterHeater_HeatPump_WrappedCondenserFields::OffCycleParasiticElectricLoad, "OffCycleParasiticElectricLoad", "Off Cycle Parasitic Electric Load"},
{ WaterHeater_HeatPump_WrappedCondenserFields::ParasiticHeatRejectionLocation, "ParasiticHeatRejectionLocation", "Parasitic Heat Rejection Location"},
{ WaterHeater_HeatPump_WrappedCondenserFields::InletAirMixerNodeName, "InletAirMixerNodeName", "Inlet Air Mixer Node Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::OutletAirSplitterNodeName, "OutletAirSplitterNodeName", "Outlet Air Splitter Node Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::InletAirMixerScheduleName, "InletAirMixerScheduleName", "Inlet Air Mixer Schedule Name"},
{ WaterHeater_HeatPump_WrappedCondenserFields::TankElementControlLogic, "TankElementControlLogic", "Tank Element Control Logic"},
{ WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1HeightInStratifiedTank, "ControlSensor1HeightInStratifiedTank", "Control Sensor 1 Height In Stratified Tank"},
{ WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor1Weight, "ControlSensor1Weight", "Control Sensor 1 Weight"},
{ WaterHeater_HeatPump_WrappedCondenserFields::ControlSensor2HeightInStratifiedTank, "ControlSensor2HeightInStratifiedTank", "Control Sensor 2 Height In Stratified Tank"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterHeater_HeatPump_WrappedCondenserFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterHeater_HeatPump_WrappedCondenserFields> OptionalWaterHeater_HeatPump_WrappedCondenserFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WATERHEATER_HEATPUMP_WRAPPEDCONDENSER_FIELDENUMS_HXX
