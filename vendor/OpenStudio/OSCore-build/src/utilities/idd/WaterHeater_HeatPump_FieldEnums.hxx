/**********************************************************************
*  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
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

#ifndef UTILITIES_IDD_WATERHEATER_HEATPUMP_FIELDENUMS_HXX
#define UTILITIES_IDD_WATERHEATER_HEATPUMP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WaterHeater_HeatPumpFields
 *  \brief Enumeration of WaterHeater:HeatPump's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WaterHeater_HeatPumpFields, )
#else
class WaterHeater_HeatPumpFields: public ::EnumBase<WaterHeater_HeatPumpFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CompressorSetpointTemperatureScheduleName, DeadBandTemperatureDifference, CondenserWaterInletNodeName, CondenserWaterOutletNodeName, CondenserWaterFlowRate, EvaporatorAirFlowRate, InletAirConfiguration, AirInletNodeName, AirOutletNodeName, OutdoorAirNodeName, ExhaustAirNodeName, InletAirTemperatureScheduleName, InletAirHumidityScheduleName, InletAirZoneName, TankObjectType, TankName, TankUseSideInletNodeName, TankUseSideOutletNodeName, DXCoilObjectType, DXCoilName, MinimumInletAirTemperatureforCompressorOperation, CompressorLocation, CompressorAmbientTemperatureScheduleName, FanObjectType, FanName, FanPlacement, OnCycleParasiticElectricLoad, OffCycleParasiticElectricLoad, ParasiticHeatRejectionLocation, InletAirMixerNodeName, OutletAirSplitterNodeName, InletAirMixerScheduleName, ControlSensorLocationInStratifiedTank,   };
  WaterHeater_HeatPumpFields()
   : EnumBase<WaterHeater_HeatPumpFields>(Name) {} 
  WaterHeater_HeatPumpFields(const std::string &t_name) 
   : EnumBase<WaterHeater_HeatPumpFields>(t_name) {} 
  WaterHeater_HeatPumpFields(int t_value) 
   : EnumBase<WaterHeater_HeatPumpFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterHeater_HeatPumpFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterHeater_HeatPumpFields>::value()); }
   private:
    friend class EnumBase<WaterHeater_HeatPumpFields>;
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
{ WaterHeater_HeatPumpFields::Name, "Name", "Name"},
{ WaterHeater_HeatPumpFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ WaterHeater_HeatPumpFields::CompressorSetpointTemperatureScheduleName, "CompressorSetpointTemperatureScheduleName", "Compressor Setpoint Temperature Schedule Name"},
{ WaterHeater_HeatPumpFields::DeadBandTemperatureDifference, "DeadBandTemperatureDifference", "Dead Band Temperature Difference"},
{ WaterHeater_HeatPumpFields::CondenserWaterInletNodeName, "CondenserWaterInletNodeName", "Condenser Water Inlet Node Name"},
{ WaterHeater_HeatPumpFields::CondenserWaterOutletNodeName, "CondenserWaterOutletNodeName", "Condenser Water Outlet Node Name"},
{ WaterHeater_HeatPumpFields::CondenserWaterFlowRate, "CondenserWaterFlowRate", "Condenser Water Flow Rate"},
{ WaterHeater_HeatPumpFields::EvaporatorAirFlowRate, "EvaporatorAirFlowRate", "Evaporator Air Flow Rate"},
{ WaterHeater_HeatPumpFields::InletAirConfiguration, "InletAirConfiguration", "Inlet Air Configuration"},
{ WaterHeater_HeatPumpFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ WaterHeater_HeatPumpFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ WaterHeater_HeatPumpFields::OutdoorAirNodeName, "OutdoorAirNodeName", "Outdoor Air Node Name"},
{ WaterHeater_HeatPumpFields::ExhaustAirNodeName, "ExhaustAirNodeName", "Exhaust Air Node Name"},
{ WaterHeater_HeatPumpFields::InletAirTemperatureScheduleName, "InletAirTemperatureScheduleName", "Inlet Air Temperature Schedule Name"},
{ WaterHeater_HeatPumpFields::InletAirHumidityScheduleName, "InletAirHumidityScheduleName", "Inlet Air Humidity Schedule Name"},
{ WaterHeater_HeatPumpFields::InletAirZoneName, "InletAirZoneName", "Inlet Air Zone Name"},
{ WaterHeater_HeatPumpFields::TankObjectType, "TankObjectType", "Tank Object Type"},
{ WaterHeater_HeatPumpFields::TankName, "TankName", "Tank Name"},
{ WaterHeater_HeatPumpFields::TankUseSideInletNodeName, "TankUseSideInletNodeName", "Tank Use Side Inlet Node Name"},
{ WaterHeater_HeatPumpFields::TankUseSideOutletNodeName, "TankUseSideOutletNodeName", "Tank Use Side Outlet Node Name"},
{ WaterHeater_HeatPumpFields::DXCoilObjectType, "DXCoilObjectType", "DX Coil Object Type"},
{ WaterHeater_HeatPumpFields::DXCoilName, "DXCoilName", "DX Coil Name"},
{ WaterHeater_HeatPumpFields::MinimumInletAirTemperatureforCompressorOperation, "MinimumInletAirTemperatureforCompressorOperation", "Minimum Inlet Air Temperature for Compressor Operation"},
{ WaterHeater_HeatPumpFields::CompressorLocation, "CompressorLocation", "Compressor Location"},
{ WaterHeater_HeatPumpFields::CompressorAmbientTemperatureScheduleName, "CompressorAmbientTemperatureScheduleName", "Compressor Ambient Temperature Schedule Name"},
{ WaterHeater_HeatPumpFields::FanObjectType, "FanObjectType", "Fan Object Type"},
{ WaterHeater_HeatPumpFields::FanName, "FanName", "Fan Name"},
{ WaterHeater_HeatPumpFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ WaterHeater_HeatPumpFields::OnCycleParasiticElectricLoad, "OnCycleParasiticElectricLoad", "On Cycle Parasitic Electric Load"},
{ WaterHeater_HeatPumpFields::OffCycleParasiticElectricLoad, "OffCycleParasiticElectricLoad", "Off Cycle Parasitic Electric Load"},
{ WaterHeater_HeatPumpFields::ParasiticHeatRejectionLocation, "ParasiticHeatRejectionLocation", "Parasitic Heat Rejection Location"},
{ WaterHeater_HeatPumpFields::InletAirMixerNodeName, "InletAirMixerNodeName", "Inlet Air Mixer Node Name"},
{ WaterHeater_HeatPumpFields::OutletAirSplitterNodeName, "OutletAirSplitterNodeName", "Outlet Air Splitter Node Name"},
{ WaterHeater_HeatPumpFields::InletAirMixerScheduleName, "InletAirMixerScheduleName", "Inlet Air Mixer Schedule Name"},
{ WaterHeater_HeatPumpFields::ControlSensorLocationInStratifiedTank, "ControlSensorLocationInStratifiedTank", "Control Sensor Location In Stratified Tank"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterHeater_HeatPumpFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterHeater_HeatPumpFields> OptionalWaterHeater_HeatPumpFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WATERHEATER_HEATPUMP_FIELDENUMS_HXX
