/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

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
Name, ZoneorSpaceName, ScheduleName, DesignFlowRateCalculationMethod, DesignFlowRate, FlowRateperFloor, FlowRateperPerson, AirChangesperHour, SourceZoneorSpaceName, DeltaTemperature, DeltaTemperatureScheduleName, MinimumReceivingTemperatureScheduleName, MaximumReceivingTemperatureScheduleName, MinimumSourceTemperatureScheduleName, MaximumSourceTemperatureScheduleName, MinimumOutdoorTemperatureScheduleName, MaximumOutdoorTemperatureScheduleName,   };
  ZoneCrossMixingFields()
   : EnumBase<ZoneCrossMixingFields>(Name) {} 
  ZoneCrossMixingFields(const std::string &t_name) 
   : EnumBase<ZoneCrossMixingFields>(t_name) {} 
  ZoneCrossMixingFields(int t_value) 
   : EnumBase<ZoneCrossMixingFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneCrossMixingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneCrossMixingFields>::integer_value()); }
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
{ ZoneCrossMixingFields::ZoneorSpaceName, "ZoneorSpaceName", "Zone or Space Name"},
{ ZoneCrossMixingFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ ZoneCrossMixingFields::DesignFlowRateCalculationMethod, "DesignFlowRateCalculationMethod", "Design Flow Rate Calculation Method"},
{ ZoneCrossMixingFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ ZoneCrossMixingFields::FlowRateperFloor, "FlowRateperFloor", "Flow Rate per Floor"},
{ ZoneCrossMixingFields::FlowRateperPerson, "FlowRateperPerson", "Flow Rate per Person"},
{ ZoneCrossMixingFields::AirChangesperHour, "AirChangesperHour", "Air Changes per Hour"},
{ ZoneCrossMixingFields::SourceZoneorSpaceName, "SourceZoneorSpaceName", "Source Zone or Space Name"},
{ ZoneCrossMixingFields::DeltaTemperature, "DeltaTemperature", "Delta Temperature"},
{ ZoneCrossMixingFields::DeltaTemperatureScheduleName, "DeltaTemperatureScheduleName", "Delta Temperature Schedule Name"},
{ ZoneCrossMixingFields::MinimumReceivingTemperatureScheduleName, "MinimumReceivingTemperatureScheduleName", "Minimum Receiving Temperature Schedule Name"},
{ ZoneCrossMixingFields::MaximumReceivingTemperatureScheduleName, "MaximumReceivingTemperatureScheduleName", "Maximum Receiving Temperature Schedule Name"},
{ ZoneCrossMixingFields::MinimumSourceTemperatureScheduleName, "MinimumSourceTemperatureScheduleName", "Minimum Source Temperature Schedule Name"},
{ ZoneCrossMixingFields::MaximumSourceTemperatureScheduleName, "MaximumSourceTemperatureScheduleName", "Maximum Source Temperature Schedule Name"},
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
