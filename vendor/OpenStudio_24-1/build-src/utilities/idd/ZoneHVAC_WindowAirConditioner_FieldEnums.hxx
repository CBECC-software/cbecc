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

#ifndef UTILITIES_IDD_ZONEHVAC_WINDOWAIRCONDITIONER_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_WINDOWAIRCONDITIONER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_WindowAirConditionerFields
 *  \brief Enumeration of ZoneHVAC:WindowAirConditioner's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_WindowAirConditionerFields, )
#else
class ZoneHVAC_WindowAirConditionerFields: public ::EnumBase<ZoneHVAC_WindowAirConditionerFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, MaximumSupplyAirFlowRate, MaximumOutdoorAirFlowRate, AirInletNodeName, AirOutletNodeName, OutdoorAirMixerObjectType, OutdoorAirMixerName, SupplyAirFanObjectType, SupplyAirFanName, CoolingCoilObjectType, DXCoolingCoilName, SupplyAirFanOperatingModeScheduleName, FanPlacement, CoolingConvergenceTolerance, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName,   };
  ZoneHVAC_WindowAirConditionerFields()
   : EnumBase<ZoneHVAC_WindowAirConditionerFields>(Name) {} 
  ZoneHVAC_WindowAirConditionerFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_WindowAirConditionerFields>(t_name) {} 
  ZoneHVAC_WindowAirConditionerFields(int t_value) 
   : EnumBase<ZoneHVAC_WindowAirConditionerFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_WindowAirConditionerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_WindowAirConditionerFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_WindowAirConditionerFields>;
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
{ ZoneHVAC_WindowAirConditionerFields::Name, "Name", "Name"},
{ ZoneHVAC_WindowAirConditionerFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_WindowAirConditionerFields::MaximumSupplyAirFlowRate, "MaximumSupplyAirFlowRate", "Maximum Supply Air Flow Rate"},
{ ZoneHVAC_WindowAirConditionerFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ ZoneHVAC_WindowAirConditionerFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ ZoneHVAC_WindowAirConditionerFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ ZoneHVAC_WindowAirConditionerFields::OutdoorAirMixerObjectType, "OutdoorAirMixerObjectType", "Outdoor Air Mixer Object Type"},
{ ZoneHVAC_WindowAirConditionerFields::OutdoorAirMixerName, "OutdoorAirMixerName", "Outdoor Air Mixer Name"},
{ ZoneHVAC_WindowAirConditionerFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_WindowAirConditionerFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_WindowAirConditionerFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ ZoneHVAC_WindowAirConditionerFields::DXCoolingCoilName, "DXCoolingCoilName", "DX Cooling Coil Name"},
{ ZoneHVAC_WindowAirConditionerFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ ZoneHVAC_WindowAirConditionerFields::FanPlacement, "FanPlacement", "Fan Placement"},
{ ZoneHVAC_WindowAirConditionerFields::CoolingConvergenceTolerance, "CoolingConvergenceTolerance", "Cooling Convergence Tolerance"},
{ ZoneHVAC_WindowAirConditionerFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_WindowAirConditionerFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_WindowAirConditionerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_WindowAirConditionerFields> OptionalZoneHVAC_WindowAirConditionerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_WINDOWAIRCONDITIONER_FIELDENUMS_HXX
