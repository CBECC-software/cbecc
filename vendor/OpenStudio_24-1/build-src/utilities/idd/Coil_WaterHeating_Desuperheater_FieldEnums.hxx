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

#ifndef UTILITIES_IDD_COIL_WATERHEATING_DESUPERHEATER_FIELDENUMS_HXX
#define UTILITIES_IDD_COIL_WATERHEATING_DESUPERHEATER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Coil_WaterHeating_DesuperheaterFields
 *  \brief Enumeration of Coil:WaterHeating:Desuperheater's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Coil_WaterHeating_DesuperheaterFields, )
#else
class Coil_WaterHeating_DesuperheaterFields: public ::EnumBase<Coil_WaterHeating_DesuperheaterFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, SetpointTemperatureScheduleName, DeadBandTemperatureDifference, RatedHeatReclaimRecoveryEfficiency, RatedInletWaterTemperature, RatedOutdoorAirTemperature, MaximumInletWaterTemperatureforHeatReclaim, HeatReclaimEfficiencyFunctionofTemperatureCurveName, WaterInletNodeName, WaterOutletNodeName, TankObjectType, TankName, HeatingSourceObjectType, HeatingSourceName, WaterFlowRate, WaterPumpPower, FractionofPumpHeattoWater, OnCycleParasiticElectricLoad, OffCycleParasiticElectricLoad,   };
  Coil_WaterHeating_DesuperheaterFields()
   : EnumBase<Coil_WaterHeating_DesuperheaterFields>(Name) {} 
  Coil_WaterHeating_DesuperheaterFields(const std::string &t_name) 
   : EnumBase<Coil_WaterHeating_DesuperheaterFields>(t_name) {} 
  Coil_WaterHeating_DesuperheaterFields(int t_value) 
   : EnumBase<Coil_WaterHeating_DesuperheaterFields>(t_value) {} 
  static std::string enumName() 
  { return "Coil_WaterHeating_DesuperheaterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Coil_WaterHeating_DesuperheaterFields>::value()); }
   private:
    friend class EnumBase<Coil_WaterHeating_DesuperheaterFields>;
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
{ Coil_WaterHeating_DesuperheaterFields::Name, "Name", "Name"},
{ Coil_WaterHeating_DesuperheaterFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ Coil_WaterHeating_DesuperheaterFields::SetpointTemperatureScheduleName, "SetpointTemperatureScheduleName", "Setpoint Temperature Schedule Name"},
{ Coil_WaterHeating_DesuperheaterFields::DeadBandTemperatureDifference, "DeadBandTemperatureDifference", "Dead Band Temperature Difference"},
{ Coil_WaterHeating_DesuperheaterFields::RatedHeatReclaimRecoveryEfficiency, "RatedHeatReclaimRecoveryEfficiency", "Rated Heat Reclaim Recovery Efficiency"},
{ Coil_WaterHeating_DesuperheaterFields::RatedInletWaterTemperature, "RatedInletWaterTemperature", "Rated Inlet Water Temperature"},
{ Coil_WaterHeating_DesuperheaterFields::RatedOutdoorAirTemperature, "RatedOutdoorAirTemperature", "Rated Outdoor Air Temperature"},
{ Coil_WaterHeating_DesuperheaterFields::MaximumInletWaterTemperatureforHeatReclaim, "MaximumInletWaterTemperatureforHeatReclaim", "Maximum Inlet Water Temperature for Heat Reclaim"},
{ Coil_WaterHeating_DesuperheaterFields::HeatReclaimEfficiencyFunctionofTemperatureCurveName, "HeatReclaimEfficiencyFunctionofTemperatureCurveName", "Heat Reclaim Efficiency Function of Temperature Curve Name"},
{ Coil_WaterHeating_DesuperheaterFields::WaterInletNodeName, "WaterInletNodeName", "Water Inlet Node Name"},
{ Coil_WaterHeating_DesuperheaterFields::WaterOutletNodeName, "WaterOutletNodeName", "Water Outlet Node Name"},
{ Coil_WaterHeating_DesuperheaterFields::TankObjectType, "TankObjectType", "Tank Object Type"},
{ Coil_WaterHeating_DesuperheaterFields::TankName, "TankName", "Tank Name"},
{ Coil_WaterHeating_DesuperheaterFields::HeatingSourceObjectType, "HeatingSourceObjectType", "Heating Source Object Type"},
{ Coil_WaterHeating_DesuperheaterFields::HeatingSourceName, "HeatingSourceName", "Heating Source Name"},
{ Coil_WaterHeating_DesuperheaterFields::WaterFlowRate, "WaterFlowRate", "Water Flow Rate"},
{ Coil_WaterHeating_DesuperheaterFields::WaterPumpPower, "WaterPumpPower", "Water Pump Power"},
{ Coil_WaterHeating_DesuperheaterFields::FractionofPumpHeattoWater, "FractionofPumpHeattoWater", "Fraction of Pump Heat to Water"},
{ Coil_WaterHeating_DesuperheaterFields::OnCycleParasiticElectricLoad, "OnCycleParasiticElectricLoad", "On-Cycle Parasitic Electric Load"},
{ Coil_WaterHeating_DesuperheaterFields::OffCycleParasiticElectricLoad, "OffCycleParasiticElectricLoad", "Off-Cycle Parasitic Electric Load"},
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
  inline std::ostream &operator<<(std::ostream &os, const Coil_WaterHeating_DesuperheaterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Coil_WaterHeating_DesuperheaterFields> OptionalCoil_WaterHeating_DesuperheaterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_COIL_WATERHEATING_DESUPERHEATER_FIELDENUMS_HXX
