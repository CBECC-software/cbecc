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

#ifndef UTILITIES_IDD_OS_THERMALZONE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_THERMALZONE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ThermalZoneFields
 *  \brief Enumeration of OS:ThermalZone's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ThermalZoneFields, )
#else
class OS_ThermalZoneFields: public ::EnumBase<OS_ThermalZoneFields> {
 public: 
  enum domain 
  {
Handle, Name, Multiplier, CeilingHeight, Volume, FloorArea, ZoneInsideConvectionAlgorithm, ZoneOutsideConvectionAlgorithm, ZoneConditioningEquipmentListName, ZoneAirInletPortList, ZoneAirExhaustPortList, ZoneAirNodeName, ZoneReturnAirPortList, PrimaryDaylightingControlName, FractionofZoneControlledbyPrimaryDaylightingControl, SecondaryDaylightingControlName, FractionofZoneControlledbySecondaryDaylightingControl, IlluminanceMapName, GroupRenderingName, ThermostatName, UseIdealAirLoads, HumidistatName, DaylightingControlsAvailabilityScheduleName,   };
  OS_ThermalZoneFields()
   : EnumBase<OS_ThermalZoneFields>(Handle) {} 
  OS_ThermalZoneFields(const std::string &t_name) 
   : EnumBase<OS_ThermalZoneFields>(t_name) {} 
  OS_ThermalZoneFields(int t_value) 
   : EnumBase<OS_ThermalZoneFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ThermalZoneFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ThermalZoneFields>::value()); }
   private:
    friend class EnumBase<OS_ThermalZoneFields>;
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
{ OS_ThermalZoneFields::Handle, "Handle", "Handle"},
{ OS_ThermalZoneFields::Name, "Name", "Name"},
{ OS_ThermalZoneFields::Multiplier, "Multiplier", "Multiplier"},
{ OS_ThermalZoneFields::CeilingHeight, "CeilingHeight", "Ceiling Height"},
{ OS_ThermalZoneFields::Volume, "Volume", "Volume"},
{ OS_ThermalZoneFields::FloorArea, "FloorArea", "Floor Area"},
{ OS_ThermalZoneFields::ZoneInsideConvectionAlgorithm, "ZoneInsideConvectionAlgorithm", "Zone Inside Convection Algorithm"},
{ OS_ThermalZoneFields::ZoneOutsideConvectionAlgorithm, "ZoneOutsideConvectionAlgorithm", "Zone Outside Convection Algorithm"},
{ OS_ThermalZoneFields::ZoneConditioningEquipmentListName, "ZoneConditioningEquipmentListName", "Zone Conditioning Equipment List Name"},
{ OS_ThermalZoneFields::ZoneAirInletPortList, "ZoneAirInletPortList", "Zone Air Inlet Port List"},
{ OS_ThermalZoneFields::ZoneAirExhaustPortList, "ZoneAirExhaustPortList", "Zone Air Exhaust Port List"},
{ OS_ThermalZoneFields::ZoneAirNodeName, "ZoneAirNodeName", "Zone Air Node Name"},
{ OS_ThermalZoneFields::ZoneReturnAirPortList, "ZoneReturnAirPortList", "Zone Return Air Port List"},
{ OS_ThermalZoneFields::PrimaryDaylightingControlName, "PrimaryDaylightingControlName", "Primary Daylighting Control Name"},
{ OS_ThermalZoneFields::FractionofZoneControlledbyPrimaryDaylightingControl, "FractionofZoneControlledbyPrimaryDaylightingControl", "Fraction of Zone Controlled by Primary Daylighting Control"},
{ OS_ThermalZoneFields::SecondaryDaylightingControlName, "SecondaryDaylightingControlName", "Secondary Daylighting Control Name"},
{ OS_ThermalZoneFields::FractionofZoneControlledbySecondaryDaylightingControl, "FractionofZoneControlledbySecondaryDaylightingControl", "Fraction of Zone Controlled by Secondary Daylighting Control"},
{ OS_ThermalZoneFields::IlluminanceMapName, "IlluminanceMapName", "Illuminance Map Name"},
{ OS_ThermalZoneFields::GroupRenderingName, "GroupRenderingName", "Group Rendering Name"},
{ OS_ThermalZoneFields::ThermostatName, "ThermostatName", "Thermostat Name"},
{ OS_ThermalZoneFields::UseIdealAirLoads, "UseIdealAirLoads", "Use Ideal Air Loads"},
{ OS_ThermalZoneFields::HumidistatName, "HumidistatName", "Humidistat Name"},
{ OS_ThermalZoneFields::DaylightingControlsAvailabilityScheduleName, "DaylightingControlsAvailabilityScheduleName", "Daylighting Controls Availability Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ThermalZoneFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ThermalZoneFields> OptionalOS_ThermalZoneFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_THERMALZONE_FIELDENUMS_HXX
