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

#ifndef UTILITIES_IDD_ZONEMIXING_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEMIXING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneMixingFields
 *  \brief Enumeration of ZoneMixing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneMixingFields, )
#else
class ZoneMixingFields: public ::EnumBase<ZoneMixingFields> {
 public: 
  enum domain 
  {
Name, ZoneName, ScheduleName, DesignFlowRateCalculationMethod, DesignFlowRate, FlowRateperZoneFloorArea, FlowRateperPerson, AirChangesperHour, SourceZoneName, DeltaTemperature, DeltaTemperatureScheduleName, MinimumZoneTemperatureScheduleName, MaximumZoneTemperatureScheduleName, MinimumSourceZoneTemperatureScheduleName, MaximumSourceZoneTemperatureScheduleName, MinimumOutdoorTemperatureScheduleName, MaximumOutdoorTemperatureScheduleName,   };
  ZoneMixingFields()
   : EnumBase<ZoneMixingFields>(Name) {} 
  ZoneMixingFields(const std::string &t_name) 
   : EnumBase<ZoneMixingFields>(t_name) {} 
  ZoneMixingFields(int t_value) 
   : EnumBase<ZoneMixingFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneMixingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneMixingFields>::value()); }
   private:
    friend class EnumBase<ZoneMixingFields>;
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
{ ZoneMixingFields::Name, "Name", "Name"},
{ ZoneMixingFields::ZoneName, "ZoneName", "Zone Name"},
{ ZoneMixingFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ ZoneMixingFields::DesignFlowRateCalculationMethod, "DesignFlowRateCalculationMethod", "Design Flow Rate Calculation Method"},
{ ZoneMixingFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ ZoneMixingFields::FlowRateperZoneFloorArea, "FlowRateperZoneFloorArea", "Flow Rate per Zone Floor Area"},
{ ZoneMixingFields::FlowRateperPerson, "FlowRateperPerson", "Flow Rate per Person"},
{ ZoneMixingFields::AirChangesperHour, "AirChangesperHour", "Air Changes per Hour"},
{ ZoneMixingFields::SourceZoneName, "SourceZoneName", "Source Zone Name"},
{ ZoneMixingFields::DeltaTemperature, "DeltaTemperature", "Delta Temperature"},
{ ZoneMixingFields::DeltaTemperatureScheduleName, "DeltaTemperatureScheduleName", "Delta Temperature Schedule Name"},
{ ZoneMixingFields::MinimumZoneTemperatureScheduleName, "MinimumZoneTemperatureScheduleName", "Minimum Zone Temperature Schedule Name"},
{ ZoneMixingFields::MaximumZoneTemperatureScheduleName, "MaximumZoneTemperatureScheduleName", "Maximum Zone Temperature Schedule Name"},
{ ZoneMixingFields::MinimumSourceZoneTemperatureScheduleName, "MinimumSourceZoneTemperatureScheduleName", "Minimum Source Zone Temperature Schedule Name"},
{ ZoneMixingFields::MaximumSourceZoneTemperatureScheduleName, "MaximumSourceZoneTemperatureScheduleName", "Maximum Source Zone Temperature Schedule Name"},
{ ZoneMixingFields::MinimumOutdoorTemperatureScheduleName, "MinimumOutdoorTemperatureScheduleName", "Minimum Outdoor Temperature Schedule Name"},
{ ZoneMixingFields::MaximumOutdoorTemperatureScheduleName, "MaximumOutdoorTemperatureScheduleName", "Maximum Outdoor Temperature Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneMixingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneMixingFields> OptionalZoneMixingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEMIXING_FIELDENUMS_HXX
