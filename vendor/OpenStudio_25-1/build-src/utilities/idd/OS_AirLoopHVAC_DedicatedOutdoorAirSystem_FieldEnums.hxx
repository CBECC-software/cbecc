/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRLOOPHVAC_DEDICATEDOUTDOORAIRSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRLOOPHVAC_DEDICATEDOUTDOORAIRSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields
 *  \brief Enumeration of OS:AirLoopHVAC:DedicatedOutdoorAirSystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields, )
#else
class OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields: public ::EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields> {
 public: 
  enum domain 
  {
Handle, Name, OutdoorAirSystem, AvailabilitySchedule, PreheatDesignTemperature, PreheatDesignHumidityRatio, PrecoolDesignTemperature, PrecoolDesignHumidityRatio,   };
  OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields()
   : EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields>(Handle) {} 
  OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields>(t_name) {} 
  OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields>;
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
{ OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields::Handle, "Handle", "Handle"},
{ OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields::Name, "Name", "Name"},
{ OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields::OutdoorAirSystem, "OutdoorAirSystem", "Outdoor Air System"},
{ OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignTemperature, "PreheatDesignTemperature", "Preheat Design Temperature"},
{ OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignHumidityRatio, "PreheatDesignHumidityRatio", "Preheat Design Humidity Ratio"},
{ OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignTemperature, "PrecoolDesignTemperature", "Precool Design Temperature"},
{ OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignHumidityRatio, "PrecoolDesignHumidityRatio", "Precool Design Humidity Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_DedicatedOutdoorAirSystemFields> OptionalOS_AirLoopHVAC_DedicatedOutdoorAirSystemFields ;
#endif

/** \class OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields
 *  \brief Enumeration of OS:AirLoopHVAC:DedicatedOutdoorAirSystem's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields, )
#else
class OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields: public ::EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields> {
 public: 
  enum domain 
  {
AirLoop,   };
  OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields()
   : EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields>(AirLoop) {} 
  OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields>(t_name) {} 
  OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields(int t_value) 
   : EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields>;
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
{ OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields::AirLoop, "AirLoop", "Air Loop"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields> OptionalOS_AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRLOOPHVAC_DEDICATEDOUTDOORAIRSYSTEM_FIELDENUMS_HXX
