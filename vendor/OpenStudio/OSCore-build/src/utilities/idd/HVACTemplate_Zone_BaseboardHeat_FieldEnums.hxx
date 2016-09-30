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

#ifndef UTILITIES_IDD_HVACTEMPLATE_ZONE_BASEBOARDHEAT_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_ZONE_BASEBOARDHEAT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Zone_BaseboardHeatFields
 *  \brief Enumeration of HVACTemplate:Zone:BaseboardHeat's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Zone_BaseboardHeatFields, )
#else
class HVACTemplate_Zone_BaseboardHeatFields: public ::EnumBase<HVACTemplate_Zone_BaseboardHeatFields> {
 public: 
  enum domain 
  {
ZoneName, TemplateThermostatName, ZoneHeatingSizingFactor, BaseboardHeatingType, BaseboardHeatingAvailabilityScheduleName, BaseboardHeatingCapacity, DedicatedOutdoorAirSystemName, OutdoorAirMethod, OutdoorAirFlowRateperPerson, OutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZone, DesignSpecificationOutdoorAirObjectname, DesignSpecificationZoneAirDistributionObjectName,   };
  HVACTemplate_Zone_BaseboardHeatFields()
   : EnumBase<HVACTemplate_Zone_BaseboardHeatFields>(ZoneName) {} 
  HVACTemplate_Zone_BaseboardHeatFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Zone_BaseboardHeatFields>(t_name) {} 
  HVACTemplate_Zone_BaseboardHeatFields(int t_value) 
   : EnumBase<HVACTemplate_Zone_BaseboardHeatFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Zone_BaseboardHeatFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Zone_BaseboardHeatFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Zone_BaseboardHeatFields>;
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
{ HVACTemplate_Zone_BaseboardHeatFields::ZoneName, "ZoneName", "Zone Name"},
{ HVACTemplate_Zone_BaseboardHeatFields::TemplateThermostatName, "TemplateThermostatName", "Template Thermostat Name"},
{ HVACTemplate_Zone_BaseboardHeatFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingType, "BaseboardHeatingType", "Baseboard Heating Type"},
{ HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingAvailabilityScheduleName, "BaseboardHeatingAvailabilityScheduleName", "Baseboard Heating Availability Schedule Name"},
{ HVACTemplate_Zone_BaseboardHeatFields::BaseboardHeatingCapacity, "BaseboardHeatingCapacity", "Baseboard Heating Capacity"},
{ HVACTemplate_Zone_BaseboardHeatFields::DedicatedOutdoorAirSystemName, "DedicatedOutdoorAirSystemName", "Dedicated Outdoor Air System Name"},
{ HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirMethod, "OutdoorAirMethod", "Outdoor Air Method"},
{ HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperPerson, "OutdoorAirFlowRateperPerson", "Outdoor Air Flow Rate per Person"},
{ HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperZoneFloorArea, "OutdoorAirFlowRateperZoneFloorArea", "Outdoor Air Flow Rate per Zone Floor Area"},
{ HVACTemplate_Zone_BaseboardHeatFields::OutdoorAirFlowRateperZone, "OutdoorAirFlowRateperZone", "Outdoor Air Flow Rate per Zone"},
{ HVACTemplate_Zone_BaseboardHeatFields::DesignSpecificationOutdoorAirObjectname, "DesignSpecificationOutdoorAirObjectname", "Design Specification Outdoor Air Object name"},
{ HVACTemplate_Zone_BaseboardHeatFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Zone_BaseboardHeatFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Zone_BaseboardHeatFields> OptionalHVACTemplate_Zone_BaseboardHeatFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_ZONE_BASEBOARDHEAT_FIELDENUMS_HXX
