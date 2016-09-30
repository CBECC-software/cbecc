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

#ifndef UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Zone_VAVFields
 *  \brief Enumeration of HVACTemplate:Zone:VAV's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Zone_VAVFields, )
#else
class HVACTemplate_Zone_VAVFields: public ::EnumBase<HVACTemplate_Zone_VAVFields> {
 public: 
  enum domain 
  {
ZoneName, TemplateVAVSystemName, TemplateThermostatName, SupplyAirMaximumFlowRate, ZoneHeatingSizingFactor, ZoneCoolingSizingFactor, ZoneMinimumAirFlowInputMethod, ConstantMinimumAirFlowFraction, FixedMinimumAirFlowRate, MinimumAirFlowFractionScheduleName, OutdoorAirMethod, OutdoorAirFlowRateperPerson, OutdoorAirFlowRateperZoneFloorArea, OutdoorAirFlowRateperZone, ReheatCoilType, ReheatCoilAvailabilityScheduleName, DamperHeatingAction, MaximumFlowperZoneFloorAreaDuringReheat, MaximumFlowFractionDuringReheat, MaximumReheatAirTemperature, DesignSpecificationOutdoorAirObjectNameforControl, SupplyPlenumName, ReturnPlenumName, BaseboardHeatingType, BaseboardHeatingAvailabilityScheduleName, BaseboardHeatingCapacity, ZoneCoolingDesignSupplyAirTemperatureInputMethod, ZoneCoolingDesignSupplyAirTemperature, ZoneCoolingDesignSupplyAirTemperatureDifference, ZoneHeatingDesignSupplyAirTemperatureInputMethod, ZoneHeatingDesignSupplyAirTemperature, ZoneHeatingDesignSupplyAirTemperatureDifference, DesignSpecificationOutdoorAirObjectNameforSizing, DesignSpecificationZoneAirDistributionObjectName,   };
  HVACTemplate_Zone_VAVFields()
   : EnumBase<HVACTemplate_Zone_VAVFields>(ZoneName) {} 
  HVACTemplate_Zone_VAVFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Zone_VAVFields>(t_name) {} 
  HVACTemplate_Zone_VAVFields(int t_value) 
   : EnumBase<HVACTemplate_Zone_VAVFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Zone_VAVFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Zone_VAVFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Zone_VAVFields>;
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
{ HVACTemplate_Zone_VAVFields::ZoneName, "ZoneName", "Zone Name"},
{ HVACTemplate_Zone_VAVFields::TemplateVAVSystemName, "TemplateVAVSystemName", "Template VAV System Name"},
{ HVACTemplate_Zone_VAVFields::TemplateThermostatName, "TemplateThermostatName", "Template Thermostat Name"},
{ HVACTemplate_Zone_VAVFields::SupplyAirMaximumFlowRate, "SupplyAirMaximumFlowRate", "Supply Air Maximum Flow Rate"},
{ HVACTemplate_Zone_VAVFields::ZoneHeatingSizingFactor, "ZoneHeatingSizingFactor", "Zone Heating Sizing Factor"},
{ HVACTemplate_Zone_VAVFields::ZoneCoolingSizingFactor, "ZoneCoolingSizingFactor", "Zone Cooling Sizing Factor"},
{ HVACTemplate_Zone_VAVFields::ZoneMinimumAirFlowInputMethod, "ZoneMinimumAirFlowInputMethod", "Zone Minimum Air Flow Input Method"},
{ HVACTemplate_Zone_VAVFields::ConstantMinimumAirFlowFraction, "ConstantMinimumAirFlowFraction", "Constant Minimum Air Flow Fraction"},
{ HVACTemplate_Zone_VAVFields::FixedMinimumAirFlowRate, "FixedMinimumAirFlowRate", "Fixed Minimum Air Flow Rate"},
{ HVACTemplate_Zone_VAVFields::MinimumAirFlowFractionScheduleName, "MinimumAirFlowFractionScheduleName", "Minimum Air Flow Fraction Schedule Name"},
{ HVACTemplate_Zone_VAVFields::OutdoorAirMethod, "OutdoorAirMethod", "Outdoor Air Method"},
{ HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperPerson, "OutdoorAirFlowRateperPerson", "Outdoor Air Flow Rate per Person"},
{ HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperZoneFloorArea, "OutdoorAirFlowRateperZoneFloorArea", "Outdoor Air Flow Rate per Zone Floor Area"},
{ HVACTemplate_Zone_VAVFields::OutdoorAirFlowRateperZone, "OutdoorAirFlowRateperZone", "Outdoor Air Flow Rate per Zone"},
{ HVACTemplate_Zone_VAVFields::ReheatCoilType, "ReheatCoilType", "Reheat Coil Type"},
{ HVACTemplate_Zone_VAVFields::ReheatCoilAvailabilityScheduleName, "ReheatCoilAvailabilityScheduleName", "Reheat Coil Availability Schedule Name"},
{ HVACTemplate_Zone_VAVFields::DamperHeatingAction, "DamperHeatingAction", "Damper Heating Action"},
{ HVACTemplate_Zone_VAVFields::MaximumFlowperZoneFloorAreaDuringReheat, "MaximumFlowperZoneFloorAreaDuringReheat", "Maximum Flow per Zone Floor Area During Reheat"},
{ HVACTemplate_Zone_VAVFields::MaximumFlowFractionDuringReheat, "MaximumFlowFractionDuringReheat", "Maximum Flow Fraction During Reheat"},
{ HVACTemplate_Zone_VAVFields::MaximumReheatAirTemperature, "MaximumReheatAirTemperature", "Maximum Reheat Air Temperature"},
{ HVACTemplate_Zone_VAVFields::DesignSpecificationOutdoorAirObjectNameforControl, "DesignSpecificationOutdoorAirObjectNameforControl", "Design Specification Outdoor Air Object Name for Control"},
{ HVACTemplate_Zone_VAVFields::SupplyPlenumName, "SupplyPlenumName", "Supply Plenum Name"},
{ HVACTemplate_Zone_VAVFields::ReturnPlenumName, "ReturnPlenumName", "Return Plenum Name"},
{ HVACTemplate_Zone_VAVFields::BaseboardHeatingType, "BaseboardHeatingType", "Baseboard Heating Type"},
{ HVACTemplate_Zone_VAVFields::BaseboardHeatingAvailabilityScheduleName, "BaseboardHeatingAvailabilityScheduleName", "Baseboard Heating Availability Schedule Name"},
{ HVACTemplate_Zone_VAVFields::BaseboardHeatingCapacity, "BaseboardHeatingCapacity", "Baseboard Heating Capacity"},
{ HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureInputMethod, "ZoneCoolingDesignSupplyAirTemperatureInputMethod", "Zone Cooling Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperature, "ZoneCoolingDesignSupplyAirTemperature", "Zone Cooling Design Supply Air Temperature"},
{ HVACTemplate_Zone_VAVFields::ZoneCoolingDesignSupplyAirTemperatureDifference, "ZoneCoolingDesignSupplyAirTemperatureDifference", "Zone Cooling Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureInputMethod, "ZoneHeatingDesignSupplyAirTemperatureInputMethod", "Zone Heating Design Supply Air Temperature Input Method"},
{ HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperature, "ZoneHeatingDesignSupplyAirTemperature", "Zone Heating Design Supply Air Temperature"},
{ HVACTemplate_Zone_VAVFields::ZoneHeatingDesignSupplyAirTemperatureDifference, "ZoneHeatingDesignSupplyAirTemperatureDifference", "Zone Heating Design Supply Air Temperature Difference"},
{ HVACTemplate_Zone_VAVFields::DesignSpecificationOutdoorAirObjectNameforSizing, "DesignSpecificationOutdoorAirObjectNameforSizing", "Design Specification Outdoor Air Object Name for Sizing"},
{ HVACTemplate_Zone_VAVFields::DesignSpecificationZoneAirDistributionObjectName, "DesignSpecificationZoneAirDistributionObjectName", "Design Specification Zone Air Distribution Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Zone_VAVFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Zone_VAVFields> OptionalHVACTemplate_Zone_VAVFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_ZONE_VAV_FIELDENUMS_HXX
