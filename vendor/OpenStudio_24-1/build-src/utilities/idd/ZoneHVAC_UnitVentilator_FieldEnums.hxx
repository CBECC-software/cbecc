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

#ifndef UTILITIES_IDD_ZONEHVAC_UNITVENTILATOR_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEHVAC_UNITVENTILATOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneHVAC_UnitVentilatorFields
 *  \brief Enumeration of ZoneHVAC:UnitVentilator's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneHVAC_UnitVentilatorFields, )
#else
class ZoneHVAC_UnitVentilatorFields: public ::EnumBase<ZoneHVAC_UnitVentilatorFields> {
 public: 
  enum domain 
  {
Name, AvailabilityScheduleName, MaximumSupplyAirFlowRate, OutdoorAirControlType, MinimumOutdoorAirFlowRate, MinimumOutdoorAirScheduleName, MaximumOutdoorAirFlowRate, MaximumOutdoorAirFractionorTemperatureScheduleName, AirInletNodeName, AirOutletNodeName, OutdoorAirNodeName, ExhaustAirNodeName, MixedAirNodeName, SupplyAirFanObjectType, SupplyAirFanName, CoilOption, SupplyAirFanOperatingModeScheduleName, HeatingCoilObjectType, HeatingCoilName, HeatingConvergenceTolerance, CoolingCoilObjectType, CoolingCoilName, CoolingConvergenceTolerance, AvailabilityManagerListName, DesignSpecificationZoneHVACSizingObjectName,   };
  ZoneHVAC_UnitVentilatorFields()
   : EnumBase<ZoneHVAC_UnitVentilatorFields>(Name) {} 
  ZoneHVAC_UnitVentilatorFields(const std::string &t_name) 
   : EnumBase<ZoneHVAC_UnitVentilatorFields>(t_name) {} 
  ZoneHVAC_UnitVentilatorFields(int t_value) 
   : EnumBase<ZoneHVAC_UnitVentilatorFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneHVAC_UnitVentilatorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneHVAC_UnitVentilatorFields>::value()); }
   private:
    friend class EnumBase<ZoneHVAC_UnitVentilatorFields>;
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
{ ZoneHVAC_UnitVentilatorFields::Name, "Name", "Name"},
{ ZoneHVAC_UnitVentilatorFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ ZoneHVAC_UnitVentilatorFields::MaximumSupplyAirFlowRate, "MaximumSupplyAirFlowRate", "Maximum Supply Air Flow Rate"},
{ ZoneHVAC_UnitVentilatorFields::OutdoorAirControlType, "OutdoorAirControlType", "Outdoor Air Control Type"},
{ ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirFlowRate, "MinimumOutdoorAirFlowRate", "Minimum Outdoor Air Flow Rate"},
{ ZoneHVAC_UnitVentilatorFields::MinimumOutdoorAirScheduleName, "MinimumOutdoorAirScheduleName", "Minimum Outdoor Air Schedule Name"},
{ ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFlowRate, "MaximumOutdoorAirFlowRate", "Maximum Outdoor Air Flow Rate"},
{ ZoneHVAC_UnitVentilatorFields::MaximumOutdoorAirFractionorTemperatureScheduleName, "MaximumOutdoorAirFractionorTemperatureScheduleName", "Maximum Outdoor Air Fraction or Temperature Schedule Name"},
{ ZoneHVAC_UnitVentilatorFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ ZoneHVAC_UnitVentilatorFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ ZoneHVAC_UnitVentilatorFields::OutdoorAirNodeName, "OutdoorAirNodeName", "Outdoor Air Node Name"},
{ ZoneHVAC_UnitVentilatorFields::ExhaustAirNodeName, "ExhaustAirNodeName", "Exhaust Air Node Name"},
{ ZoneHVAC_UnitVentilatorFields::MixedAirNodeName, "MixedAirNodeName", "Mixed Air Node Name"},
{ ZoneHVAC_UnitVentilatorFields::SupplyAirFanObjectType, "SupplyAirFanObjectType", "Supply Air Fan Object Type"},
{ ZoneHVAC_UnitVentilatorFields::SupplyAirFanName, "SupplyAirFanName", "Supply Air Fan Name"},
{ ZoneHVAC_UnitVentilatorFields::CoilOption, "CoilOption", "Coil Option"},
{ ZoneHVAC_UnitVentilatorFields::SupplyAirFanOperatingModeScheduleName, "SupplyAirFanOperatingModeScheduleName", "Supply Air Fan Operating Mode Schedule Name"},
{ ZoneHVAC_UnitVentilatorFields::HeatingCoilObjectType, "HeatingCoilObjectType", "Heating Coil Object Type"},
{ ZoneHVAC_UnitVentilatorFields::HeatingCoilName, "HeatingCoilName", "Heating Coil Name"},
{ ZoneHVAC_UnitVentilatorFields::HeatingConvergenceTolerance, "HeatingConvergenceTolerance", "Heating Convergence Tolerance"},
{ ZoneHVAC_UnitVentilatorFields::CoolingCoilObjectType, "CoolingCoilObjectType", "Cooling Coil Object Type"},
{ ZoneHVAC_UnitVentilatorFields::CoolingCoilName, "CoolingCoilName", "Cooling Coil Name"},
{ ZoneHVAC_UnitVentilatorFields::CoolingConvergenceTolerance, "CoolingConvergenceTolerance", "Cooling Convergence Tolerance"},
{ ZoneHVAC_UnitVentilatorFields::AvailabilityManagerListName, "AvailabilityManagerListName", "Availability Manager List Name"},
{ ZoneHVAC_UnitVentilatorFields::DesignSpecificationZoneHVACSizingObjectName, "DesignSpecificationZoneHVACSizingObjectName", "Design Specification ZoneHVAC Sizing Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneHVAC_UnitVentilatorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneHVAC_UnitVentilatorFields> OptionalZoneHVAC_UnitVentilatorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEHVAC_UNITVENTILATOR_FIELDENUMS_HXX
