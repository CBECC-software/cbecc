/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_CONSTANTFLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_CONSTANTFLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields
 *  \brief Enumeration of ZoneHVAC:LowTemperatureRadiant:ConstantFlow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields, )
#else
class ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields: public ::EnumBase<ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, ZoneName, SurfaceNameorRadiantSurfaceGroupName, FluidtoRadiantSurfaceHeatTransferModel, HydronicTubingInsideDiameter, HydronicTubingOutsideDiameter, HydronicTubingLength, HydronicTubingConductivity, TemperatureControlType, RunningMeanOutdoorDryBulbTemperatureWeightingFactor, RatedFlowRate, PumpFlowRateScheduleName, RatedPumpHead, RatedPowerConsumption, MotorEfficiency, FractionofMotorInefficienciestoFluidStream, HeatingWaterInletNodeName, HeatingWaterOutletNodeName, HeatingHighWaterTemperatureScheduleName, HeatingLowWaterTemperatureScheduleName, HeatingHighControlTemperatureScheduleName, HeatingLowControlTemperatureScheduleName, CoolingWaterInletNodeName, CoolingWaterOutletNodeName, CoolingHighWaterTemperatureScheduleName, CoolingLowWaterTemperatureScheduleName, CoolingHighControlTemperatureScheduleName, CoolingLowControlTemperatureScheduleName, CondensationControlType, CondensationControlDewpointOffset, NumberofCircuits, CircuitLength, ChangeoverDelayTimePeriodSchedule,   };
  ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields()
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields>(Name) {} 
  ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields>(t_name) {} 
  ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields(int t_value) 
   : EnumBase<ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields>;
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
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::Name, "Name", "Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::SurfaceNameorRadiantSurfaceGroupName, "SurfaceNameorRadiantSurfaceGroupName", "Surface Name or Radiant Surface Group Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::FluidtoRadiantSurfaceHeatTransferModel, "FluidtoRadiantSurfaceHeatTransferModel", "Fluid to Radiant Surface Heat Transfer Model"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingInsideDiameter, "HydronicTubingInsideDiameter", "Hydronic Tubing Inside Diameter"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingOutsideDiameter, "HydronicTubingOutsideDiameter", "Hydronic Tubing Outside Diameter"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingLength, "HydronicTubingLength", "Hydronic Tubing Length"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HydronicTubingConductivity, "HydronicTubingConductivity", "Hydronic Tubing Conductivity"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::TemperatureControlType, "TemperatureControlType", "Temperature Control Type"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RunningMeanOutdoorDryBulbTemperatureWeightingFactor, "RunningMeanOutdoorDryBulbTemperatureWeightingFactor", "Running Mean Outdoor Dry-Bulb Temperature Weighting Factor"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedFlowRate, "RatedFlowRate", "Rated Flow Rate"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::PumpFlowRateScheduleName, "PumpFlowRateScheduleName", "Pump Flow Rate Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPumpHead, "RatedPumpHead", "Rated Pump Head"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::RatedPowerConsumption, "RatedPowerConsumption", "Rated Power Consumption"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::MotorEfficiency, "MotorEfficiency", "Motor Efficiency"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::FractionofMotorInefficienciestoFluidStream, "FractionofMotorInefficienciestoFluidStream", "Fraction of Motor Inefficiencies to Fluid Stream"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterInletNodeName, "HeatingWaterInletNodeName", "Heating Water Inlet Node Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingWaterOutletNodeName, "HeatingWaterOutletNodeName", "Heating Water Outlet Node Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighWaterTemperatureScheduleName, "HeatingHighWaterTemperatureScheduleName", "Heating High Water Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowWaterTemperatureScheduleName, "HeatingLowWaterTemperatureScheduleName", "Heating Low Water Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingHighControlTemperatureScheduleName, "HeatingHighControlTemperatureScheduleName", "Heating High Control Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::HeatingLowControlTemperatureScheduleName, "HeatingLowControlTemperatureScheduleName", "Heating Low Control Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterInletNodeName, "CoolingWaterInletNodeName", "Cooling Water Inlet Node Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingWaterOutletNodeName, "CoolingWaterOutletNodeName", "Cooling Water Outlet Node Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighWaterTemperatureScheduleName, "CoolingHighWaterTemperatureScheduleName", "Cooling High Water Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowWaterTemperatureScheduleName, "CoolingLowWaterTemperatureScheduleName", "Cooling Low Water Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingHighControlTemperatureScheduleName, "CoolingHighControlTemperatureScheduleName", "Cooling High Control Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CoolingLowControlTemperatureScheduleName, "CoolingLowControlTemperatureScheduleName", "Cooling Low Control Temperature Schedule Name"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CondensationControlType, "CondensationControlType", "Condensation Control Type"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CondensationControlDewpointOffset, "CondensationControlDewpointOffset", "Condensation Control Dewpoint Offset"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::NumberofCircuits, "NumberofCircuits", "Number of Circuits"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::CircuitLength, "CircuitLength", "Circuit Length"},
{ ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields::ChangeoverDelayTimePeriodSchedule, "ChangeoverDelayTimePeriodSchedule", "Changeover Delay Time Period Schedule"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_LowTemperatureRadiant_ConstantFlowFields> OptionalZoneHVAC_LowTemperatureRadiant_ConstantFlowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_LOWTEMPERATURERADIANT_CONSTANTFLOW_FIELDENUMS_HXX
