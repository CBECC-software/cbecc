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

#ifndef UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_HEATANDCOOL_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_HEATANDCOOL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Zone_VAV_HeatAndCoolFields
 *  \brief Enumeration of HVACTemplate:Zone:VAV:HeatAndCool's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Zone_VAV_HeatAndCoolFields, )
#else
class HVACTemplate_Zone_VAV_HeatAndCoolFields: public ::EnumBase<HVACTemplate_Zone_VAV_HeatAndCoolFields> {
 public: 
  enum domain 
  {
ZoneName, TemplateVAVSystemName, TemplateThermostatName, SupplyAirMaximumFlowRate, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, ConstantMinimumAirFlowFraction, OutdoorAirMethod, OutdoorAirFlowRateperPerson, OutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZone, DesignSpecificationOutdoorAirObjectNameforSizing, DesignSpecificationZoneAirDistributionObjectName, ReheatCoilType, ReheatCoilAvailabilityScheduleName, MaximumReheatAirTemperature, SupplyPlenumName, ReturnPlenumName, BaseboardHeatingType, BaseboardHeatingAvailabilityScheduleName, BaseboardHeatingCapacity, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperatureDifference,   };
  HVACTemplate_Zone_VAV_HeatAndCoolFields()
   : EnumBase<HVACTemplate_Zone_VAV_HeatAndCoolFields>(ZoneName) {} 
  HVACTemplate_Zone_VAV_HeatAndCoolFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Zone_VAV_HeatAndCoolFields>(t_name) {} 
  HVACTemplate_Zone_VAV_HeatAndCoolFields(int t_value) 
   : EnumBase<HVACTemplate_Zone_VAV_HeatAndCoolFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Zone_VAV_HeatAndCoolFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Zone_VAV_HeatAndCoolFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Zone_VAV_HeatAndCoolFields>;
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
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneName, "ZoneName", "Zone Name"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::TemplateVAVSystemName, "TemplateVAVSystemName", "Template VAV System Name"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::TemplateThermostatName, "TemplateThermostatName", "Template Thermostat Name"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::SupplyAirMaximumFlowRate, "SupplyAirMaximumFlowRate", "Supply Air Maximum Flow Rate"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingSizingFactor, "ZoneCoolingSizingFactor", "Zone Cooling Sizing Factor"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ConstantMinimumAirFlowFraction, "ConstantMinimumAirFlowFraction", "Constant Minimum Air Flow Fraction"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirMethod, "OutdoorAirMethod", "Outdoor Air Method"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperPerson, "OutdoorAirFlowRateperPerson", "Outdoor Air Flow Rate per Person"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperZoneFloorArea, "OutdoorAirFlowRateperZoneFloorArea", "Outdoor Air Flow Rate per Zone Floor Area"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::OutdoorAirFlowRateperZone, "OutdoorAirFlowRateperZone", "Outdoor Air Flow Rate per Zone"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::DesignSpecificationOutdoorAirObjectNameforSizing, "DesignSpecificationOutdoorAirObjectNameforSizing", "Design Specification Outdoor Air Object Name for Sizing"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ReheatCoilType, "ReheatCoilType", "Reheat Coil Type"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ReheatCoilAvailabilityScheduleName, "ReheatCoilAvailabilityScheduleName", "Reheat Coil Availability Schedule Name"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::MaximumReheatAirTemperature, "MaximumReheatAirTemperature", "Maximum Reheat Air Temperature"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::SupplyPlenumName, "SupplyPlenumName", "Supply Plenum Name"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ReturnPlenumName, "ReturnPlenumName", "Return Plenum Name"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingType, "BaseboardHeatingType", "Baseboard Heating Type"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingAvailabilityScheduleName, "BaseboardHeatingAvailabilityScheduleName", "Baseboard Heating Availability Schedule Name"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::BaseboardHeatingCapacity, "BaseboardHeatingCapacity", "Baseboard Heating Capacity"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, "ZoneCoolingDesignSupplyAirTemperatureInputMethod", "Zone Cooling Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperature, "ZoneCoolingDesignSupplyAirTemperature", "Zone Cooling Design Supply Air Temperature"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneCoolingDesignSupplyAirTemperatureDifference, "ZoneCoolingDesignSupplyAirTemperatureDifference", "Zone Cooling Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, "ZoneHeatingDesignSupplyAirTemperatureInputMethod", "Zone Heating Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperature, "ZoneHeatingDesignSupplyAirTemperature", "Zone Heating Design Supply Air Temperature"},
{ HVACTemplate_Zone_VAV_HeatAndCoolFields::ZoneHeatingDesignSupplyAirTemperatureDifference, "ZoneHeatingDesignSupplyAirTemperatureDifference", "Zone Heating Design Supply Air Temperature Difference"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Zone_VAV_HeatAndCoolFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Zone_VAV_HeatAndCoolFields> OptionalHVACTemplate_Zone_VAV_HeatAndCoolFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_HEATANDCOOL_FIELDENUMS_HXX
