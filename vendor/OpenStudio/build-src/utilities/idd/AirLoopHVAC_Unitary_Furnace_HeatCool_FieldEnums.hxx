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

#ifndef UTILITIES_IDD_AIRLOOPHVAC_UNITARY_FURNACE_HEATCOOL_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_UNITARY_FURNACE_HEATCOOL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_Unitary_Furnace_HeatCoolFields
 *  \brief Enumeration of AirLoopHVAC:Unitary:Furnace:HeatCool's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_Unitary_Furnace_HeatCoolFields, )
#else
class AirLoopHVAC_Unitary_Furnace_HeatCoolFields: public ::EnumBase<AirLoopHVAC_Unitary_Furnace_HeatCoolFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, FurnaceAirInletNodeName, FurnaceAirOutletNodeName, SupplyAirFanOperatingModeScheduleName, MaximumSupplyAirTemperature, CoolingSupplyAirFlowRate, HeatingSupplyAirFlowRate, NoLoadSupplyAirFlowRate, ControllingZoneorThermostatLocation, SupplyFanObjectType, SupplyFanName, FanPlacement, HeatingCoilObjectType, HeatingCoilName, CoolingCoilObjectType, CoolingCoilName, DehumidificationControlType, ReheatCoilObjectType, ReheatCoilName,   };
  AirLoopHVAC_Unitary_Furnace_HeatCoolFields()
   : EnumBase<AirLoopHVAC_Unitary_Furnace_HeatCoolFields>(Name) {} 
  AirLoopHVAC_Unitary_Furnace_HeatCoolFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_Unitary_Furnace_HeatCoolFields>(t_name) {} 
  AirLoopHVAC_Unitary_Furnace_HeatCoolFields(int t_value) 
   : EnumBase<AirLoopHVAC_Unitary_Furnace_HeatCoolFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_Unitary_Furnace_HeatCoolFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_Unitary_Furnace_HeatCoolFields>::value()); }
   private:
    friend class EnumBase<AirLoopHVAC_Unitary_Furnace_HeatCoolFields>;
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
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::Name, "Name", "Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::FurnaceAirInletNodeName, "FurnaceAirInletNodeName", "Furnace Air Inlet Node Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::FurnaceAirOutletNodeName, "FurnaceAirOutletNodeName", "Furnace Air Outlet Node Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::MaximumSupplyAirTemperature, "MaximumSupplyAirTemperature", "Maximum Supply Air Temperature"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::ControllingZoneorThermostatLocation, "ControllingZoneorThermostatLocation", "Controlling Zone or Thermostat Location"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::SupplyFanObjectType, "SupplyFanObjectType", "Supply Fan Object Type"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::SupplyFanName, "SupplyFanName", "Supply Fan Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::DehumidificationControlType, "DehumidificationControlType", "Dehumidification Control Type"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::ReheatCoilObjectType, "ReheatCoilObjectType", "Reheat Coil Object Type"},
{ AirLoopHVAC_Unitary_Furnace_HeatCoolFields::ReheatCoilName, "ReheatCoilName", "Reheat Coil Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_Unitary_Furnace_HeatCoolFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_Unitary_Furnace_HeatCoolFields> OptionalAirLoopHVAC_Unitary_Furnace_HeatCoolFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_UNITARY_FURNACE_HEATCOOL_FIELDENUMS_HXX
