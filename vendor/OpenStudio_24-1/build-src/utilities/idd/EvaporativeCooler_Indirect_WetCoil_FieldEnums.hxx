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

#ifndef UTILITIES_IDD_EVAPORATIVECOOLER_INDIRECT_WETCOIL_FIELDENUMS_HXX
#define UTILITIES_IDD_EVAPORATIVECOOLER_INDIRECT_WETCOIL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class EvaporativeCooler_Indirect_WetCoilFields
 *  \brief Enumeration of EvaporativeCooler:Indirect:WetCoil's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(EvaporativeCooler_Indirect_WetCoilFields, )
#else
class EvaporativeCooler_Indirect_WetCoilFields: public ::EnumBase<EvaporativeCooler_Indirect_WetCoilFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, CoilMaximumEfficiency, CoilFlowRatio, RecirculatingWaterPumpPowerConsumption, SecondaryAirFanFlowRate, SecondaryAirFanTotalEfficiency, SecondaryAirFanDeltaPressure, PrimaryAirInletNodeName, PrimaryAirOutletNodeName, ControlType, WaterSupplyStorageTankName, SecondaryAirInletNodeName,   };
  EvaporativeCooler_Indirect_WetCoilFields()
   : EnumBase<EvaporativeCooler_Indirect_WetCoilFields>(Name) {} 
  EvaporativeCooler_Indirect_WetCoilFields(const std::string &t_name) 
   : EnumBase<EvaporativeCooler_Indirect_WetCoilFields>(t_name) {} 
  EvaporativeCooler_Indirect_WetCoilFields(int t_value) 
   : EnumBase<EvaporativeCooler_Indirect_WetCoilFields>(t_value) {} 
  static std::string enumName() 
  { return "EvaporativeCooler_Indirect_WetCoilFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EvaporativeCooler_Indirect_WetCoilFields>::value()); }
   private:
    friend class EnumBase<EvaporativeCooler_Indirect_WetCoilFields>;
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
{ EvaporativeCooler_Indirect_WetCoilFields::Name, "Name", "Name"},
{ EvaporativeCooler_Indirect_WetCoilFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ EvaporativeCooler_Indirect_WetCoilFields::CoilMaximumEfficiency, "CoilMaximumEfficiency", "Coil Maximum Efficiency"},
{ EvaporativeCooler_Indirect_WetCoilFields::CoilFlowRatio, "CoilFlowRatio", "Coil Flow Ratio"},
{ EvaporativeCooler_Indirect_WetCoilFields::RecirculatingWaterPumpPowerConsumption, "RecirculatingWaterPumpPowerConsumption", "Recirculating Water Pump Power Consumption"},
{ EvaporativeCooler_Indirect_WetCoilFields::SecondaryAirFanFlowRate, "SecondaryAirFanFlowRate", "Secondary Air Fan Flow Rate"},
{ EvaporativeCooler_Indirect_WetCoilFields::SecondaryAirFanTotalEfficiency, "SecondaryAirFanTotalEfficiency", "Secondary Air Fan Total Efficiency"},
{ EvaporativeCooler_Indirect_WetCoilFields::SecondaryAirFanDeltaPressure, "SecondaryAirFanDeltaPressure", "Secondary Air Fan Delta Pressure"},
{ EvaporativeCooler_Indirect_WetCoilFields::PrimaryAirInletNodeName, "PrimaryAirInletNodeName", "Primary Air Inlet Node Name"},
{ EvaporativeCooler_Indirect_WetCoilFields::PrimaryAirOutletNodeName, "PrimaryAirOutletNodeName", "Primary Air Outlet Node Name"},
{ EvaporativeCooler_Indirect_WetCoilFields::ControlType, "ControlType", "Control Type"},
{ EvaporativeCooler_Indirect_WetCoilFields::WaterSupplyStorageTankName, "WaterSupplyStorageTankName", "Water Supply Storage Tank Name"},
{ EvaporativeCooler_Indirect_WetCoilFields::SecondaryAirInletNodeName, "SecondaryAirInletNodeName", "Secondary Air Inlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const EvaporativeCooler_Indirect_WetCoilFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EvaporativeCooler_Indirect_WetCoilFields> OptionalEvaporativeCooler_Indirect_WetCoilFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_EVAPORATIVECOOLER_INDIRECT_WETCOIL_FIELDENUMS_HXX
