/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONEMIXING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEMIXING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneMixingFields
 *  \brief Enumeration of OS:ZoneMixing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneMixingFields, )
#else
class OS_ZoneMixingFields: public ::EnumBase<OS_ZoneMixingFields> {
 public: 
  enum domain 
  {
Handle, Name, ZoneorSpaceName, ScheduleName, DesignFlowRateCalculationMethod, DesignFlowRate, FlowRateperFloorArea, FlowRateperPerson, AirChangesperHour, SourceZoneorSpaceName, DeltaTemperature, DeltaTemperatureScheduleName, MinimumReceivingTemperatureScheduleName, MaximumReceivingTemperatureScheduleName, MinimumSourceTemperatureScheduleName, MaximumSourceTemperatureScheduleName, MinimumOutdoorTemperatureScheduleName, MaximumOutdoorTemperatureScheduleName,   };
  OS_ZoneMixingFields()
   : EnumBase<OS_ZoneMixingFields>(Handle) {} 
  OS_ZoneMixingFields(const std::string &t_name) 
   : EnumBase<OS_ZoneMixingFields>(t_name) {} 
  OS_ZoneMixingFields(int t_value) 
   : EnumBase<OS_ZoneMixingFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneMixingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneMixingFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneMixingFields>;
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
{ OS_ZoneMixingFields::Handle, "Handle", "Handle"},
{ OS_ZoneMixingFields::Name, "Name", "Name"},
{ OS_ZoneMixingFields::ZoneorSpaceName, "ZoneorSpaceName", "Zone or Space Name"},
{ OS_ZoneMixingFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_ZoneMixingFields::DesignFlowRateCalculationMethod, "DesignFlowRateCalculationMethod", "Design Flow Rate Calculation Method"},
{ OS_ZoneMixingFields::DesignFlowRate, "DesignFlowRate", "Design Flow Rate"},
{ OS_ZoneMixingFields::FlowRateperFloorArea, "FlowRateperFloorArea", "Flow Rate per Floor Area"},
{ OS_ZoneMixingFields::FlowRateperPerson, "FlowRateperPerson", "Flow Rate per Person"},
{ OS_ZoneMixingFields::AirChangesperHour, "AirChangesperHour", "Air Changes per Hour"},
{ OS_ZoneMixingFields::SourceZoneorSpaceName, "SourceZoneorSpaceName", "Source Zone or Space Name"},
{ OS_ZoneMixingFields::DeltaTemperature, "DeltaTemperature", "Delta Temperature"},
{ OS_ZoneMixingFields::DeltaTemperatureScheduleName, "DeltaTemperatureScheduleName", "Delta Temperature Schedule Name"},
{ OS_ZoneMixingFields::MinimumReceivingTemperatureScheduleName, "MinimumReceivingTemperatureScheduleName", "Minimum Receiving Temperature Schedule Name"},
{ OS_ZoneMixingFields::MaximumReceivingTemperatureScheduleName, "MaximumReceivingTemperatureScheduleName", "Maximum Receiving Temperature Schedule Name"},
{ OS_ZoneMixingFields::MinimumSourceTemperatureScheduleName, "MinimumSourceTemperatureScheduleName", "Minimum Source Temperature Schedule Name"},
{ OS_ZoneMixingFields::MaximumSourceTemperatureScheduleName, "MaximumSourceTemperatureScheduleName", "Maximum Source Temperature Schedule Name"},
{ OS_ZoneMixingFields::MinimumOutdoorTemperatureScheduleName, "MinimumOutdoorTemperatureScheduleName", "Minimum Outdoor Temperature Schedule Name"},
{ OS_ZoneMixingFields::MaximumOutdoorTemperatureScheduleName, "MaximumOutdoorTemperatureScheduleName", "Maximum Outdoor Temperature Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneMixingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneMixingFields> OptionalOS_ZoneMixingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEMIXING_FIELDENUMS_HXX
