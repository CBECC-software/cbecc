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

#ifndef UTILITIES_IDD_ZONECROSSMIXING_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONECROSSMIXING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneCrossMixingFields
 *  \brief Enumeration of ZoneCrossMixing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneCrossMixingFields, )
#else
class ZoneCrossMixingFields: public ::EnumBase<ZoneCrossMixingFields> {
 public: 
  enum domain 
  {
Name, ZoneName, ScheduleName, DesignFlowRateCalculationMethod, DesignFlowRate, FlowRateperZoneFloorArea, FlowRateperPerson, AirChangesperHour, SourceZoneName, DeltaTemperature, DeltaTemperatureScheduleName, MinimumZoneTemperatureScheduleName, MaximumZoneTemperatureScheduleName, MinimumSourceZoneTemperatureScheduleName, MaximumSourceZoneTemperatureScheduleName, MinimumOutdoorTemperatureScheduleName, MaximumOutdoorTemperatureScheduleName,   };
  ZoneCrossMixingFields()
   : EnumBase<ZoneCrossMixingFields>(Name) {} 
  ZoneCrossMixingFields(const std::string &t_name) 
   : EnumBase<ZoneCrossMixingFields>(t_name) {} 
  ZoneCrossMixingFields(int t_value) 
   : EnumBase<ZoneCrossMixingFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneCrossMixingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneCrossMixingFields>::value()); }
   private:
    friend class EnumBase<ZoneCrossMixingFields>;
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
{ ZoneCrossMixingFields::Name, "Name", "Name"},
{ ZoneCrossMixingFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneCrossMixingFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ ZoneCrossMixingFields::DesignFlowRateCalculationMethod, "DesignFlowRateCalculationMethod", "Design Flow Rate Calculation Method"},
{ ZoneCrossMixingFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ ZoneCrossMixingFields::FlowRateperZoneFloorArea, "FlowRateperZoneFloorArea", "Flow Rate per Zone Floor Area"},
{ ZoneCrossMixingFields::FlowRateperPerson, "FlowRateperPerson", "Flow Rate per Person"},
{ ZoneCrossMixingFields::AirChangesperHour, "AirChangesperHour", "Air Changes per Hour"},
{ ZoneCrossMixingFields::SourceZoneName, "SourceZoneName", "Source Zone Name"},
{ ZoneCrossMixingFields::DeltaTemperature, "DeltaTemperature", "Delta Temperature"},
{ ZoneCrossMixingFields::DeltaTemperatureScheduleName, "DeltaTemperatureScheduleName", "Delta Temperature Schedule Name"},
{ ZoneCrossMixingFields::MinimumZoneTemperatureScheduleName, "MinimumZoneTemperatureScheduleName", "Minimum Zone Temperature Schedule Name"},
{ ZoneCrossMixingFields::MaximumZoneTemperatureScheduleName, "MaximumZoneTemperatureScheduleName", "Maximum Zone Temperature Schedule Name"},
{ ZoneCrossMixingFields::MinimumSourceZoneTemperatureScheduleName, "MinimumSourceZoneTemperatureScheduleName", "Minimum Source Zone Temperature Schedule Name"},
{ ZoneCrossMixingFields::MaximumSourceZoneTemperatureScheduleName, "MaximumSourceZoneTemperatureScheduleName", "Maximum Source Zone Temperature Schedule Name"},
{ ZoneCrossMixingFields::MinimumOutdoorTemperatureScheduleName, "MinimumOutdoorTemperatureScheduleName", "Minimum Outdoor Temperature Schedule Name"},
{ ZoneCrossMixingFields::MaximumOutdoorTemperatureScheduleName, "MaximumOutdoorTemperatureScheduleName", "Maximum Outdoor Temperature Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneCrossMixingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneCrossMixingFields> OptionalZoneCrossMixingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONECROSSMIXING_FIELDENUMS_HXX
