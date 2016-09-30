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

#ifndef UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_FANPOWERED_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_FANPOWERED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Zone_VAV_FanPoweredFields
 *  \brief Enumeration of HVACTemplate:Zone:VAV:FanPowered's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Zone_VAV_FanPoweredFields, )
#else
class HVACTemplate_Zone_VAV_FanPoweredFields: public ::EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields> {
 public: 
  enum domain 
  {
ZoneName, TemplateVAVSystemName, TemplateThermostatName, PrimarySupplyAirMaximumFlowRate, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, PrimarySupplyAirMinimumFlowFraction, SecondarySupplyAirMaximumFlowRate, FlowType, ParallelFanOnFlowFraction, OutdoorAirMethod, OutdoorAirFlowRateperPerson, OutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZone, ReheatCoilType, ReheatCoilAvailabilityScheduleName, FanTotalEfficiency, FanDeltaPressure, FanMotorEfficiency, SupplyPlenumName, ReturnPlenumName, BaseboardHeatingType, BaseboardHeatingAvailabilityScheduleName, BaseboardHeatingCapacity, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperatureDifference, ZonePIUFanScheduleName, DesignSpecificationOutdoorAirObjectName, DesignSpecificationZoneAirDistributionObjectName,   };
  HVACTemplate_Zone_VAV_FanPoweredFields()
   : EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields>(ZoneName) {} 
  HVACTemplate_Zone_VAV_FanPoweredFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields>(t_name) {} 
  HVACTemplate_Zone_VAV_FanPoweredFields(int t_value) 
   : EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Zone_VAV_FanPoweredFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Zone_VAV_FanPoweredFields>;
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
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneName, "ZoneName", "Zone Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::TemplateVAVSystemName, "TemplateVAVSystemName", "Template VAV System Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::TemplateThermostatName, "TemplateThermostatName", "Template Thermostat Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMaximumFlowRate, "PrimarySupplyAirMaximumFlowRate", "Primary Supply Air Maximum Flow Rate"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingSizingFactor, "ZoneCoolingSizingFactor", "Zone Cooling Sizing Factor"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::PrimarySupplyAirMinimumFlowFraction, "PrimarySupplyAirMinimumFlowFraction", "Primary Supply Air Minimum Flow Fraction"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::SecondarySupplyAirMaximumFlowRate, "SecondarySupplyAirMaximumFlowRate", "Secondary Supply Air Maximum Flow Rate"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::FlowType, "FlowType", "Flow Type"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ParallelFanOnFlowFraction, "ParallelFanOnFlowFraction", "Parallel Fan On Flow Fraction"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirMethod, "OutdoorAirMethod", "Outdoor Air Method"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperPerson, "OutdoorAirFlowRateperPerson", "Outdoor Air Flow Rate per Person"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZoneFloorArea, "OutdoorAirFlowRateperZoneFloorArea", "Outdoor Air Flow Rate per Zone Floor Area"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::OutdoorAirFlowRateperZone, "OutdoorAirFlowRateperZone", "Outdoor Air Flow Rate per Zone"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ReheatCoilType, "ReheatCoilType", "Reheat Coil Type"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ReheatCoilAvailabilityScheduleName, "ReheatCoilAvailabilityScheduleName", "Reheat Coil Availability Schedule Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::FanDeltaPressure, "FanDeltaPressure", "Fan Delta Pressure"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::FanMotorEfficiency, "FanMotorEfficiency", "Fan Motor Efficiency"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::SupplyPlenumName, "SupplyPlenumName", "Supply Plenum Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ReturnPlenumName, "ReturnPlenumName", "Return Plenum Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingType, "BaseboardHeatingType", "Baseboard Heating Type"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingAvailabilityScheduleName, "BaseboardHeatingAvailabilityScheduleName", "Baseboard Heating Availability Schedule Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::BaseboardHeatingCapacity, "BaseboardHeatingCapacity", "Baseboard Heating Capacity"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, "ZoneCoolingDesignSupplyAirTemperatureInputMethod", "Zone Cooling Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperature, "ZoneCoolingDesignSupplyAirTemperature", "Zone Cooling Design Supply Air Temperature"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneCoolingDesignSupplyAirTemperatureDifference, "ZoneCoolingDesignSupplyAirTemperatureDifference", "Zone Cooling Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, "ZoneHeatingDesignSupplyAirTemperatureInputMethod", "Zone Heating Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperature, "ZoneHeatingDesignSupplyAirTemperature", "Zone Heating Design Supply Air Temperature"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZoneHeatingDesignSupplyAirTemperatureDifference, "ZoneHeatingDesignSupplyAirTemperatureDifference", "Zone Heating Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::ZonePIUFanScheduleName, "ZonePIUFanScheduleName", "Zone PIU Fan Schedule Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::DesignSpecificationOutdoorAirObjectName, "DesignSpecificationOutdoorAirObjectName", "Design Specification Outdoor Air Object Name"},
{ HVACTemplate_Zone_VAV_FanPoweredFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Zone_VAV_FanPoweredFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Zone_VAV_FanPoweredFields> OptionalHVACTemplate_Zone_VAV_FanPoweredFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_FANPOWERED_FIELDENUMS_HXX
