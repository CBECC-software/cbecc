/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SPACEHVAC_ZONEEQUIPMENTSPLITTER_FIELDENUMS_HXX
#define UTILITIES_IDD_SPACEHVAC_ZONEEQUIPMENTSPLITTER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SpaceHVAC_ZoneEquipmentSplitterFields
 *  \brief Enumeration of SpaceHVAC:ZoneEquipmentSplitter's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SpaceHVAC_ZoneEquipmentSplitterFields, )
#else
class SpaceHVAC_ZoneEquipmentSplitterFields: public ::EnumBase<SpaceHVAC_ZoneEquipmentSplitterFields> {
 public: 
  enum domain 
  {
Name, ZoneName, ZoneEquipmentObjectType, ZoneEquipmentName, ZoneEquipmentOutletNodeName, ThermostatControlMethod, ControlSpaceName, SpaceFractionMethod,   };
  SpaceHVAC_ZoneEquipmentSplitterFields()
   : EnumBase<SpaceHVAC_ZoneEquipmentSplitterFields>(Name) {} 
  SpaceHVAC_ZoneEquipmentSplitterFields(const std::string &t_name) 
   : EnumBase<SpaceHVAC_ZoneEquipmentSplitterFields>(t_name) {} 
  SpaceHVAC_ZoneEquipmentSplitterFields(int t_value) 
   : EnumBase<SpaceHVAC_ZoneEquipmentSplitterFields>(t_value) {} 
  static std::string enumName() 
  { return "SpaceHVAC_ZoneEquipmentSplitterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SpaceHVAC_ZoneEquipmentSplitterFields>::integer_value()); }
   private:
    friend class EnumBase<SpaceHVAC_ZoneEquipmentSplitterFields>;
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
{ SpaceHVAC_ZoneEquipmentSplitterFields::Name, "Name", "Name"},
{ SpaceHVAC_ZoneEquipmentSplitterFields::ZoneName, "ZoneName", "Zone Name"},
{ SpaceHVAC_ZoneEquipmentSplitterFields::ZoneEquipmentObjectType, "ZoneEquipmentObjectType", "Zone Equipment Object Type"},
{ SpaceHVAC_ZoneEquipmentSplitterFields::ZoneEquipmentName, "ZoneEquipmentName", "Zone Equipment Name"},
{ SpaceHVAC_ZoneEquipmentSplitterFields::ZoneEquipmentOutletNodeName, "ZoneEquipmentOutletNodeName", "Zone Equipment Outlet Node Name"},
{ SpaceHVAC_ZoneEquipmentSplitterFields::ThermostatControlMethod, "ThermostatControlMethod", "Thermostat Control Method"},
{ SpaceHVAC_ZoneEquipmentSplitterFields::ControlSpaceName, "ControlSpaceName", "Control Space Name"},
{ SpaceHVAC_ZoneEquipmentSplitterFields::SpaceFractionMethod, "SpaceFractionMethod", "Space Fraction Method"},
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
  inline std::ostream &operator<<(std::ostream &os, const SpaceHVAC_ZoneEquipmentSplitterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SpaceHVAC_ZoneEquipmentSplitterFields> OptionalSpaceHVAC_ZoneEquipmentSplitterFields ;
#endif

/** \class SpaceHVAC_ZoneEquipmentSplitterExtensibleFields
 *  \brief Enumeration of SpaceHVAC:ZoneEquipmentSplitter's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(SpaceHVAC_ZoneEquipmentSplitterExtensibleFields, )
#else
class SpaceHVAC_ZoneEquipmentSplitterExtensibleFields: public ::EnumBase<SpaceHVAC_ZoneEquipmentSplitterExtensibleFields> {
 public: 
  enum domain 
  {
SpaceName, SpaceFraction, SpaceSupplyNodeName,   };
  SpaceHVAC_ZoneEquipmentSplitterExtensibleFields()
   : EnumBase<SpaceHVAC_ZoneEquipmentSplitterExtensibleFields>(SpaceName) {} 
  SpaceHVAC_ZoneEquipmentSplitterExtensibleFields(const std::string &t_name) 
   : EnumBase<SpaceHVAC_ZoneEquipmentSplitterExtensibleFields>(t_name) {} 
  SpaceHVAC_ZoneEquipmentSplitterExtensibleFields(int t_value) 
   : EnumBase<SpaceHVAC_ZoneEquipmentSplitterExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "SpaceHVAC_ZoneEquipmentSplitterExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SpaceHVAC_ZoneEquipmentSplitterExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<SpaceHVAC_ZoneEquipmentSplitterExtensibleFields>;
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
{ SpaceHVAC_ZoneEquipmentSplitterExtensibleFields::SpaceName, "SpaceName", "Space Name"},
{ SpaceHVAC_ZoneEquipmentSplitterExtensibleFields::SpaceFraction, "SpaceFraction", "Space Fraction"},
{ SpaceHVAC_ZoneEquipmentSplitterExtensibleFields::SpaceSupplyNodeName, "SpaceSupplyNodeName", "Space Supply Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SpaceHVAC_ZoneEquipmentSplitterExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SpaceHVAC_ZoneEquipmentSplitterExtensibleFields> OptionalSpaceHVAC_ZoneEquipmentSplitterExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SPACEHVAC_ZONEEQUIPMENTSPLITTER_FIELDENUMS_HXX
