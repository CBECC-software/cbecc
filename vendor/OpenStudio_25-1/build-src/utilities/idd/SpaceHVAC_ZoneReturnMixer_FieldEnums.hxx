/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SPACEHVAC_ZONERETURNMIXER_FIELDENUMS_HXX
#define UTILITIES_IDD_SPACEHVAC_ZONERETURNMIXER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SpaceHVAC_ZoneReturnMixerFields
 *  \brief Enumeration of SpaceHVAC:ZoneReturnMixer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SpaceHVAC_ZoneReturnMixerFields, )
#else
class SpaceHVAC_ZoneReturnMixerFields: public ::EnumBase<SpaceHVAC_ZoneReturnMixerFields> {
 public: 
  enum domain 
  {
Name, ZoneName, ZoneReturnAirNodeName,   };
  SpaceHVAC_ZoneReturnMixerFields()
   : EnumBase<SpaceHVAC_ZoneReturnMixerFields>(Name) {} 
  SpaceHVAC_ZoneReturnMixerFields(const std::string &t_name) 
   : EnumBase<SpaceHVAC_ZoneReturnMixerFields>(t_name) {} 
  SpaceHVAC_ZoneReturnMixerFields(int t_value) 
   : EnumBase<SpaceHVAC_ZoneReturnMixerFields>(t_value) {} 
  static std::string enumName() 
  { return "SpaceHVAC_ZoneReturnMixerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SpaceHVAC_ZoneReturnMixerFields>::integer_value()); }
   private:
    friend class EnumBase<SpaceHVAC_ZoneReturnMixerFields>;
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
{ SpaceHVAC_ZoneReturnMixerFields::Name, "Name", "Name"},
{ SpaceHVAC_ZoneReturnMixerFields::ZoneName, "ZoneName", "Zone Name"},
{ SpaceHVAC_ZoneReturnMixerFields::ZoneReturnAirNodeName, "ZoneReturnAirNodeName", "Zone Return Air Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SpaceHVAC_ZoneReturnMixerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SpaceHVAC_ZoneReturnMixerFields> OptionalSpaceHVAC_ZoneReturnMixerFields ;
#endif

/** \class SpaceHVAC_ZoneReturnMixerExtensibleFields
 *  \brief Enumeration of SpaceHVAC:ZoneReturnMixer's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(SpaceHVAC_ZoneReturnMixerExtensibleFields, )
#else
class SpaceHVAC_ZoneReturnMixerExtensibleFields: public ::EnumBase<SpaceHVAC_ZoneReturnMixerExtensibleFields> {
 public: 
  enum domain 
  {
SpaceName, SpaceReturnAirNodeName,   };
  SpaceHVAC_ZoneReturnMixerExtensibleFields()
   : EnumBase<SpaceHVAC_ZoneReturnMixerExtensibleFields>(SpaceName) {} 
  SpaceHVAC_ZoneReturnMixerExtensibleFields(const std::string &t_name) 
   : EnumBase<SpaceHVAC_ZoneReturnMixerExtensibleFields>(t_name) {} 
  SpaceHVAC_ZoneReturnMixerExtensibleFields(int t_value) 
   : EnumBase<SpaceHVAC_ZoneReturnMixerExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "SpaceHVAC_ZoneReturnMixerExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SpaceHVAC_ZoneReturnMixerExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<SpaceHVAC_ZoneReturnMixerExtensibleFields>;
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
{ SpaceHVAC_ZoneReturnMixerExtensibleFields::SpaceName, "SpaceName", "Space Name"},
{ SpaceHVAC_ZoneReturnMixerExtensibleFields::SpaceReturnAirNodeName, "SpaceReturnAirNodeName", "Space Return Air Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SpaceHVAC_ZoneReturnMixerExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SpaceHVAC_ZoneReturnMixerExtensibleFields> OptionalSpaceHVAC_ZoneReturnMixerExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SPACEHVAC_ZONERETURNMIXER_FIELDENUMS_HXX
