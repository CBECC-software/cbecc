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

#ifndef UTILITIES_IDD_OS_ZONEVENTILATION_DESIGNFLOWRATE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEVENTILATION_DESIGNFLOWRATE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneVentilation_DesignFlowRateFields
 *  \brief Enumeration of OS:ZoneVentilation:DesignFlowRate's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneVentilation_DesignFlowRateFields, )
#else
class OS_ZoneVentilation_DesignFlowRateFields: public ::EnumBase<OS_ZoneVentilation_DesignFlowRateFields> {
 public: 
  enum domain 
  {
Handle, Name, ScheduleName, DesignFlowRateCalculationMethod, DesignFlowRate, FlowRateperZoneFloorArea, FlowRateperPerson, AirChangesperHour, VentilationType, FanPressureRise, FanTotalEfficiency, ConstantTermCoefficient, TemperatureTermCoefficient, VelocityTermCoefficient, VelocitySquaredTermCoefficient, MinimumIndoorTemperature, MinimumIndoorTemperatureScheduleName, MaximumIndoorTemperature, MaximumIndoorTemperatureScheduleName, DeltaTemperature, DeltaTemperatureScheduleName, MinimumOutdoorTemperature, MinimumOutdoorTemperatureScheduleName, MaximumOutdoorTemperature, MaximumOutdoorTemperatureScheduleName, MaximumWindSpeed,   };
  OS_ZoneVentilation_DesignFlowRateFields()
   : EnumBase<OS_ZoneVentilation_DesignFlowRateFields>(Handle) {} 
  OS_ZoneVentilation_DesignFlowRateFields(const std::string &t_name) 
   : EnumBase<OS_ZoneVentilation_DesignFlowRateFields>(t_name) {} 
  OS_ZoneVentilation_DesignFlowRateFields(int t_value) 
   : EnumBase<OS_ZoneVentilation_DesignFlowRateFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneVentilation_DesignFlowRateFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneVentilation_DesignFlowRateFields>::value()); }
   private:
    friend class EnumBase<OS_ZoneVentilation_DesignFlowRateFields>;
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
{ OS_ZoneVentilation_DesignFlowRateFields::Handle, "Handle", "Handle"},
{ OS_ZoneVentilation_DesignFlowRateFields::Name, "Name", "Name"},
{ OS_ZoneVentilation_DesignFlowRateFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRateCalculationMethod, "DesignFlowRateCalculationMethod", "Design Flow Rate Calculation Method"},
{ OS_ZoneVentilation_DesignFlowRateFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ OS_ZoneVentilation_DesignFlowRateFields::FlowRateperZoneFloorArea, "FlowRateperZoneFloorArea", "Flow Rate per Zone Floor Area"},
{ OS_ZoneVentilation_DesignFlowRateFields::FlowRateperPerson, "FlowRateperPerson", "Flow Rate per Person"},
{ OS_ZoneVentilation_DesignFlowRateFields::AirChangesperHour, "AirChangesperHour", "Air Changes per Hour"},
{ OS_ZoneVentilation_DesignFlowRateFields::VentilationType, "VentilationType", "Ventilation Type"},
{ OS_ZoneVentilation_DesignFlowRateFields::FanPressureRise, "FanPressureRise", "Fan Pressure Rise"},
{ OS_ZoneVentilation_DesignFlowRateFields::FanTotalEfficiency, "FanTotalEfficiency", "Fan Total Efficiency"},
{ OS_ZoneVentilation_DesignFlowRateFields::ConstantTermCoefficient, "ConstantTermCoefficient", "Constant Term Coefficient"},
{ OS_ZoneVentilation_DesignFlowRateFields::TemperatureTermCoefficient, "TemperatureTermCoefficient", "Temperature Term Coefficient"},
{ OS_ZoneVentilation_DesignFlowRateFields::VelocityTermCoefficient, "VelocityTermCoefficient", "Velocity Term Coefficient"},
{ OS_ZoneVentilation_DesignFlowRateFields::VelocitySquaredTermCoefficient, "VelocitySquaredTermCoefficient", "Velocity Squared Term Coefficient"},
{ OS_ZoneVentilation_DesignFlowRateFields::MinimumIndoorTemperature, "MinimumIndoorTemperature", "Minimum Indoor Temperature"},
{ OS_ZoneVentilation_DesignFlowRateFields::MinimumIndoorTemperatureScheduleName, "MinimumIndoorTemperatureScheduleName", "Minimum Indoor Temperature Schedule Name"},
{ OS_ZoneVentilation_DesignFlowRateFields::MaximumIndoorTemperature, "MaximumIndoorTemperature", "Maximum Indoor Temperature"},
{ OS_ZoneVentilation_DesignFlowRateFields::MaximumIndoorTemperatureScheduleName, "MaximumIndoorTemperatureScheduleName", "Maximum Indoor Temperature Schedule Name"},
{ OS_ZoneVentilation_DesignFlowRateFields::DeltaTemperature, "DeltaTemperature", "Delta Temperature"},
{ OS_ZoneVentilation_DesignFlowRateFields::DeltaTemperatureScheduleName, "DeltaTemperatureScheduleName", "Delta Temperature Schedule Name"},
{ OS_ZoneVentilation_DesignFlowRateFields::MinimumOutdoorTemperature, "MinimumOutdoorTemperature", "Minimum Outdoor Temperature"},
{ OS_ZoneVentilation_DesignFlowRateFields::MinimumOutdoorTemperatureScheduleName, "MinimumOutdoorTemperatureScheduleName", "Minimum Outdoor Temperature Schedule Name"},
{ OS_ZoneVentilation_DesignFlowRateFields::MaximumOutdoorTemperature, "MaximumOutdoorTemperature", "Maximum Outdoor Temperature"},
{ OS_ZoneVentilation_DesignFlowRateFields::MaximumOutdoorTemperatureScheduleName, "MaximumOutdoorTemperatureScheduleName", "Maximum Outdoor Temperature Schedule Name"},
{ OS_ZoneVentilation_DesignFlowRateFields::MaximumWindSpeed, "MaximumWindSpeed", "Maximum Wind Speed"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneVentilation_DesignFlowRateFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneVentilation_DesignFlowRateFields> OptionalOS_ZoneVentilation_DesignFlowRateFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEVENTILATION_DESIGNFLOWRATE_FIELDENUMS_HXX
