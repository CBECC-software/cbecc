/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRLOOPHVAC_DEDICATEDOUTDOORAIRSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_DEDICATEDOUTDOORAIRSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_DedicatedOutdoorAirSystemFields
 *  \brief Enumeration of AirLoopHVAC:DedicatedOutdoorAirSystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_DedicatedOutdoorAirSystemFields, )
#else
class AirLoopHVAC_DedicatedOutdoorAirSystemFields: public ::EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemFields> {
 public: 
  enum domain 
  {
Name, AirLoopHVAC_OutdoorAirSystemName, AvailabilityScheduleName, AirLoopHVAC_MixerName, AirLoopHVAC_SplitterName, PreheatDesignTemperature, PreheatDesignHumidityRatio, PrecoolDesignTemperature, PrecoolDesignHumidityRatio, NumberofAirLoopHVAC,   };
  AirLoopHVAC_DedicatedOutdoorAirSystemFields()
   : EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemFields>(Name) {} 
  AirLoopHVAC_DedicatedOutdoorAirSystemFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemFields>(t_name) {} 
  AirLoopHVAC_DedicatedOutdoorAirSystemFields(int t_value) 
   : EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_DedicatedOutdoorAirSystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemFields>::integer_value()); }
   private:
    friend class EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemFields>;
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
{ AirLoopHVAC_DedicatedOutdoorAirSystemFields::Name, "Name", "Name"},
{ AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_OutdoorAirSystemName, "AirLoopHVAC_OutdoorAirSystemName", "AirLoopHVAC:OutdoorAirSystem Name"},
{ AirLoopHVAC_DedicatedOutdoorAirSystemFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
{ AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_MixerName, "AirLoopHVAC_MixerName", "AirLoopHVAC:Mixer Name"},
{ AirLoopHVAC_DedicatedOutdoorAirSystemFields::AirLoopHVAC_SplitterName, "AirLoopHVAC_SplitterName", "AirLoopHVAC:Splitter Name"},
{ AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignTemperature, "PreheatDesignTemperature", "Preheat Design Temperature"},
{ AirLoopHVAC_DedicatedOutdoorAirSystemFields::PreheatDesignHumidityRatio, "PreheatDesignHumidityRatio", "Preheat Design Humidity Ratio"},
{ AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignTemperature, "PrecoolDesignTemperature", "Precool Design Temperature"},
{ AirLoopHVAC_DedicatedOutdoorAirSystemFields::PrecoolDesignHumidityRatio, "PrecoolDesignHumidityRatio", "Precool Design Humidity Ratio"},
{ AirLoopHVAC_DedicatedOutdoorAirSystemFields::NumberofAirLoopHVAC, "NumberofAirLoopHVAC", "Number of AirLoopHVAC"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_DedicatedOutdoorAirSystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_DedicatedOutdoorAirSystemFields> OptionalAirLoopHVAC_DedicatedOutdoorAirSystemFields ;
#endif

/** \class AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields
 *  \brief Enumeration of AirLoopHVAC:DedicatedOutdoorAirSystem's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields, )
#else
class AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields: public ::EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields> {
 public: 
  enum domain 
  {
AirLoopHVACName,   };
  AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields()
   : EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields>(AirLoopHVACName) {} 
  AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields>(t_name) {} 
  AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields(int t_value) 
   : EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields>;
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
{ AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields::AirLoopHVACName, "AirLoopHVACName", "AirLoopHVAC Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields> OptionalAirLoopHVAC_DedicatedOutdoorAirSystemExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_DEDICATEDOUTDOORAIRSYSTEM_FIELDENUMS_HXX
