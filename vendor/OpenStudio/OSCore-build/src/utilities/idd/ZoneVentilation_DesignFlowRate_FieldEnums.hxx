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

#ifndef UTILITIES_IDD_ZONEVENTILATION_DESIGNFLOWRATE_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEVENTILATION_DESIGNFLOWRATE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneVentilation_DesignFlowRateFields
 *  \brief Enumeration of ZoneVentilation:DesignFlowRate's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneVentilation_DesignFlowRateFields, )
#else
class ZoneVentilation_DesignFlowRateFields: public ::EnumBase<ZoneVentilation_DesignFlowRateFields> {
 public: 
  enum domain 
  {
Name, ZoneorZoneListName, ScheduleName, DesignFlowRateCalculationMethod, DesignFlowRate, FlowRateperZoneFloorArea, FlowRateperPerson, AirChangesperHour, VentilationType, FanPressureRise, FanTotalEfficiency, ConstantTermCoefficient, TemperatureTermCoefficient, VelocityTermCoefficient, VelocitySquaredTermCoefficient, MinimumIndoorTemperature, MinimumIndoorTemperatureScheduleName, MaximumIndoorTemperature, MaximumIndoorTemperatureScheduleName, DeltaTemperature, DeltaTemperatureScheduleName, MinimumOutdoorTemperature, MinimumOutdoorTemperatureScheduleName, MaximumOutdoorTemperature, MaximumOutdoorTemperatureScheduleName, MaximumWindSpeed,   };
  ZoneVentilation_DesignFlowRateFields()
   : EnumBase<ZoneVentilation_DesignFlowRateFields>(Name) {} 
  ZoneVentilation_DesignFlowRateFields(const std::string &t_name) 
   : EnumBase<ZoneVentilation_DesignFlowRateFields>(t_name) {} 
  ZoneVentilation_DesignFlowRateFields(int t_value) 
   : EnumBase<ZoneVentilation_DesignFlowRateFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneVentilation_DesignFlowRateFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneVentilation_DesignFlowRateFields>::value()); }
   private:
    friend class EnumBase<ZoneVentilation_DesignFlowRateFields>;
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
{ ZoneVentilation_DesignFlowRateFields::Name, "Name", "Name"},
{ ZoneVentilation_DesignFlowRateFields::ZoneorZoneListName, "ZoneorZoneListName", "Zone or ZoneList Name"},
{ ZoneVentilation_DesignFlowRateFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ ZoneVentilation_DesignFlowRateFields::DesignFlowRateCalculationMethod, "DesignFlowRateCalculationMethod", "Design Flow Rate Calculation Method"},
{ ZoneVentilation_DesignFlowRateFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ ZoneVentilation_DesignFlowRateFields::FlowRateperZoneFloorArea, "FlowRateperZoneFloorArea", "Flow Rate per Zone Floor Area"},
{ ZoneVentilation_DesignFlowRateFields::FlowRateperPerson, "FlowRateperPerson", "Flow Rate per Person"},
{ ZoneVentilation_DesignFlowRateFields::AirChangesperHour, "AirChangesperHour", "Air Changes per Hour"},
{ ZoneVentilation_DesignFlowRateFields::VentilationType, "VentilationType", "Ventilation Type"},
{ ZoneVentilation_DesignFlowRateFields::FanPressureRise, "FanPressureRise", "Fan Pressure Rise"},
{ ZoneVentilation_DesignFlowRateFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ ZoneVentilation_DesignFlowRateFields::ConstantTermCoefficient, "ConstantTermCoefficient", "Constant Term Coefficient"},
{ ZoneVentilation_DesignFlowRateFields::TemperatureTermCoefficient, "TemperatureTermCoefficient", "Temperature Term Coefficient"},
{ ZoneVentilation_DesignFlowRateFields::VelocityTermCoefficient, "VelocityTermCoefficient", "Velocity Term Coefficient"},
{ ZoneVentilation_DesignFlowRateFields::VelocitySquaredTermCoefficient, "VelocitySquaredTermCoefficient", "Velocity Squared Term Coefficient"},
{ ZoneVentilation_DesignFlowRateFields::MinimumIndoorTemperature, "MinimumIndoorTemperature", "Minimum Indoor Temperature"},
{ ZoneVentilation_DesignFlowRateFields::MinimumIndoorTemperatureScheduleName, "MinimumIndoorTemperatureScheduleName", "Minimum Indoor Temperature Schedule Name"},
{ ZoneVentilation_DesignFlowRateFields::MaximumIndoorTemperature, "MaximumIndoorTemperature", "Maximum Indoor Temperature"},
{ ZoneVentilation_DesignFlowRateFields::MaximumIndoorTemperatureScheduleName, "MaximumIndoorTemperatureScheduleName", "Maximum Indoor Temperature Schedule Name"},
{ ZoneVentilation_DesignFlowRateFields::DeltaTemperature, "DeltaTemperature", "Delta Temperature"},
{ ZoneVentilation_DesignFlowRateFields::DeltaTemperatureScheduleName, "DeltaTemperatureScheduleName", "Delta Temperature Schedule Name"},
{ ZoneVentilation_DesignFlowRateFields::MinimumOutdoorTemperature, "MinimumOutdoorTemperature", "Minimum Outdoor Temperature"},
{ ZoneVentilation_DesignFlowRateFields::MinimumOutdoorTemperatureScheduleName, "MinimumOutdoorTemperatureScheduleName", "Minimum Outdoor Temperature Schedule Name"},
{ ZoneVentilation_DesignFlowRateFields::MaximumOutdoorTemperature, "MaximumOutdoorTemperature", "Maximum Outdoor Temperature"},
{ ZoneVentilation_DesignFlowRateFields::MaximumOutdoorTemperatureScheduleName, "MaximumOutdoorTemperatureScheduleName", "Maximum Outdoor Temperature Schedule Name"},
{ ZoneVentilation_DesignFlowRateFields::MaximumWindSpeed, "MaximumWindSpeed", "Maximum Wind Speed"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneVentilation_DesignFlowRateFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneVentilation_DesignFlowRateFields> OptionalZoneVentilation_DesignFlowRateFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEVENTILATION_DESIGNFLOWRATE_FIELDENUMS_HXX
