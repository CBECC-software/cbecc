/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SPACEHVAC_ZONEEQUIPMENTMIXER_FIELDENUMS_HXX
#define UTILITIES_IDD_SPACEHVAC_ZONEEQUIPMENTMIXER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SpaceHVAC_ZoneEquipmentMixerFields
 *  \brief Enumeration of SpaceHVAC:ZoneEquipmentMixer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SpaceHVAC_ZoneEquipmentMixerFields, )
#else
class SpaceHVAC_ZoneEquipmentMixerFields: public ::EnumBase<SpaceHVAC_ZoneEquipmentMixerFields> {
 public: 
  enum domain 
  {
Name, ZoneName, ZoneEquipmentInletNodeName, SpaceFractionMethod,   };
  SpaceHVAC_ZoneEquipmentMixerFields()
   : EnumBase<SpaceHVAC_ZoneEquipmentMixerFields>(Name) {} 
  SpaceHVAC_ZoneEquipmentMixerFields(const std::string &t_name) 
   : EnumBase<SpaceHVAC_ZoneEquipmentMixerFields>(t_name) {} 
  SpaceHVAC_ZoneEquipmentMixerFields(int t_value) 
   : EnumBase<SpaceHVAC_ZoneEquipmentMixerFields>(t_value) {} 
  static std::string enumName() 
  { return "SpaceHVAC_ZoneEquipmentMixerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SpaceHVAC_ZoneEquipmentMixerFields>::integer_value()); }
   private:
    friend class EnumBase<SpaceHVAC_ZoneEquipmentMixerFields>;
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
{ SpaceHVAC_ZoneEquipmentMixerFields::Name, "Name", "Name"},
{ SpaceHVAC_ZoneEquipmentMixerFields::ZoneName, "ZoneName", "Zone Name"},
{ SpaceHVAC_ZoneEquipmentMixerFields::ZoneEquipmentInletNodeName, "ZoneEquipmentInletNodeName", "Zone Equipment Inlet Node Name"},
{ SpaceHVAC_ZoneEquipmentMixerFields::SpaceFractionMethod, "SpaceFractionMethod", "Space Fraction Method"},
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
  inline std::ostream &operator<<(std::ostream &os, const SpaceHVAC_ZoneEquipmentMixerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SpaceHVAC_ZoneEquipmentMixerFields> OptionalSpaceHVAC_ZoneEquipmentMixerFields ;
#endif

/** \class SpaceHVAC_ZoneEquipmentMixerExtensibleFields
 *  \brief Enumeration of SpaceHVAC:ZoneEquipmentMixer's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(SpaceHVAC_ZoneEquipmentMixerExtensibleFields, )
#else
class SpaceHVAC_ZoneEquipmentMixerExtensibleFields: public ::EnumBase<SpaceHVAC_ZoneEquipmentMixerExtensibleFields> {
 public: 
  enum domain 
  {
SpaceName, SpaceFraction, SpaceNodeName,   };
  SpaceHVAC_ZoneEquipmentMixerExtensibleFields()
   : EnumBase<SpaceHVAC_ZoneEquipmentMixerExtensibleFields>(SpaceName) {} 
  SpaceHVAC_ZoneEquipmentMixerExtensibleFields(const std::string &t_name) 
   : EnumBase<SpaceHVAC_ZoneEquipmentMixerExtensibleFields>(t_name) {} 
  SpaceHVAC_ZoneEquipmentMixerExtensibleFields(int t_value) 
   : EnumBase<SpaceHVAC_ZoneEquipmentMixerExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "SpaceHVAC_ZoneEquipmentMixerExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SpaceHVAC_ZoneEquipmentMixerExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<SpaceHVAC_ZoneEquipmentMixerExtensibleFields>;
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
{ SpaceHVAC_ZoneEquipmentMixerExtensibleFields::SpaceName, "SpaceName", "Space Name"},
{ SpaceHVAC_ZoneEquipmentMixerExtensibleFields::SpaceFraction, "SpaceFraction", "Space Fraction"},
{ SpaceHVAC_ZoneEquipmentMixerExtensibleFields::SpaceNodeName, "SpaceNodeName", "Space Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SpaceHVAC_ZoneEquipmentMixerExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SpaceHVAC_ZoneEquipmentMixerExtensibleFields> OptionalSpaceHVAC_ZoneEquipmentMixerExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SPACEHVAC_ZONEEQUIPMENTMIXER_FIELDENUMS_HXX
