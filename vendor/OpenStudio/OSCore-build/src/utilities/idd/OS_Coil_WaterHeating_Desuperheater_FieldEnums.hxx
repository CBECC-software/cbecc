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

#ifndef UTILITIES_IDD_OS_COIL_WATERHEATING_DESUPERHEATER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_WATERHEATING_DESUPERHEATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_WaterHeating_DesuperheaterFields
 *  \brief Enumeration of OS:Coil:WaterHeating:Desuperheater's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_WaterHeating_DesuperheaterFields, )
#else
class OS_Coil_WaterHeating_DesuperheaterFields: public ::EnumBase<OS_Coil_WaterHeating_DesuperheaterFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilityScheduleName, SetpointTemperatureScheduleName, DeadBandTemperatureDifference, RatedHeatReclaimRecoveryEfficiency, RatedInletWaterTemperature, RatedOutdoorAirTemperature, MaximumInletWaterTemperatureforHeatReclaim, HeatReclaimEfficiencyFunctionofTemperatureCurveName, WaterInletNodeName, WaterOutletNodeName, HeatingSourceName, WaterFlowRate, WaterPumpPower, FractionofPumpHeattoWater, OnCycleParasiticElectricLoad, OffCycleParasiticElectricLoad,   };
  OS_Coil_WaterHeating_DesuperheaterFields()
   : EnumBase<OS_Coil_WaterHeating_DesuperheaterFields>(Handle) {} 
  OS_Coil_WaterHeating_DesuperheaterFields(const std::string &t_name) 
   : EnumBase<OS_Coil_WaterHeating_DesuperheaterFields>(t_name) {} 
  OS_Coil_WaterHeating_DesuperheaterFields(int t_value) 
   : EnumBase<OS_Coil_WaterHeating_DesuperheaterFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_WaterHeating_DesuperheaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_WaterHeating_DesuperheaterFields>::value()); }
   private:
    friend class EnumBase<OS_Coil_WaterHeating_DesuperheaterFields>;
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
{ OS_Coil_WaterHeating_DesuperheaterFields::Handle, "Handle", "Handle"},
{ OS_Coil_WaterHeating_DesuperheaterFields::Name, "Name", "Name"},
{ OS_Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ OS_Coil_WaterHeating_DesuperheaterFields::SetpointTemperatureScheduleName, "SetpointTemperatureScheduleName", "Setpoint Temperature Schedule Name"},
{ OS_Coil_WaterHeating_DesuperheaterFields::DeadBandTemperatureDifference, "DeadBandTemperatureDifference", "Dead Band Temperature Difference"},
{ OS_Coil_WaterHeating_DesuperheaterFields::RatedHeatReclaimRecoveryEfficiency, "RatedHeatReclaimRecoveryEfficiency", "Rated Heat Reclaim Recovery Efficiency"},
{ OS_Coil_WaterHeating_DesuperheaterFields::RatedInletWaterTemperature, "RatedInletWaterTemperature", "Rated Inlet Water Temperature"},
{ OS_Coil_WaterHeating_DesuperheaterFields::RatedOutdoorAirTemperature, "RatedOutdoorAirTemperature", "Rated Outdoor Air Temperature"},
{ OS_Coil_WaterHeating_DesuperheaterFields::MaximumInletWaterTemperatureforHeatReclaim, "MaximumInletWaterTemperatureforHeatReclaim", "Maximum Inlet Water Temperature for Heat Reclaim"},
{ OS_Coil_WaterHeating_DesuperheaterFields::HeatReclaimEfficiencyFunctionofTemperatureCurveName, "HeatReclaimEfficiencyFunctionofTemperatureCurveName", "Heat Reclaim Efficiency Function of Temperature Curve Name"},
{ OS_Coil_WaterHeating_DesuperheaterFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ OS_Coil_WaterHeating_DesuperheaterFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ OS_Coil_WaterHeating_DesuperheaterFields::HeatingSourceName, "HeatingSourceName", "Heating Source Name"},
{ OS_Coil_WaterHeating_DesuperheaterFields::WaterFlowRate, "WaterFlowRate", "Water Flow Rate"},
{ OS_Coil_WaterHeating_DesuperheaterFields::WaterPumpPower, "WaterPumpPower", "Water Pump Power"},
{ OS_Coil_WaterHeating_DesuperheaterFields::FractionofPumpHeattoWater, "FractionofPumpHeattoWater", "Fraction of Pump Heat to Water"},
{ OS_Coil_WaterHeating_DesuperheaterFields::OnCycleParasiticElectricLoad, "OnCycleParasiticElectricLoad", "On-Cycle Parasitic Electric Load"},
{ OS_Coil_WaterHeating_DesuperheaterFields::OffCycleParasiticElectricLoad, "OffCycleParasiticElectricLoad", "Off-Cycle Parasitic Electric Load"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_WaterHeating_DesuperheaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_WaterHeating_DesuperheaterFields> OptionalOS_Coil_WaterHeating_DesuperheaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_WATERHEATING_DESUPERHEATER_FIELDENUMS_HXX
