/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONEHVAC_EQUIPMENTLIST_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEHVAC_EQUIPMENTLIST_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneHVAC_EquipmentListFields
 *  \brief Enumeration of OS:ZoneHVAC:EquipmentList's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneHVAC_EquipmentListFields, )
#else
class OS_ZoneHVAC_EquipmentListFields: public ::EnumBase<OS_ZoneHVAC_EquipmentListFields> {
 public: 
  enum domain 
  {
Handle, Name, ThermalZone, LoadDistributionScheme,   };
  OS_ZoneHVAC_EquipmentListFields()
   : EnumBase<OS_ZoneHVAC_EquipmentListFields>(Handle) {} 
  OS_ZoneHVAC_EquipmentListFields(const std::string &t_name) 
   : EnumBase<OS_ZoneHVAC_EquipmentListFields>(t_name) {} 
  OS_ZoneHVAC_EquipmentListFields(int t_value) 
   : EnumBase<OS_ZoneHVAC_EquipmentListFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneHVAC_EquipmentListFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneHVAC_EquipmentListFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneHVAC_EquipmentListFields>;
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
{ OS_ZoneHVAC_EquipmentListFields::Handle, "Handle", "Handle"},
{ OS_ZoneHVAC_EquipmentListFields::Name, "Name", "Name"},
{ OS_ZoneHVAC_EquipmentListFields::ThermalZone, "ThermalZone", "Thermal Zone"},
{ OS_ZoneHVAC_EquipmentListFields::LoadDistributionScheme, "LoadDistributionScheme", "Load Distribution Scheme"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneHVAC_EquipmentListFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneHVAC_EquipmentListFields> OptionalOS_ZoneHVAC_EquipmentListFields ;
#endif

/** \class OS_ZoneHVAC_EquipmentListExtensibleFields
 *  \brief Enumeration of OS:ZoneHVAC:EquipmentList's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_ZoneHVAC_EquipmentListExtensibleFields, )
#else
class OS_ZoneHVAC_EquipmentListExtensibleFields: public ::EnumBase<OS_ZoneHVAC_EquipmentListExtensibleFields> {
 public: 
  enum domain 
  {
ZoneEquipment, ZoneEquipmentCoolingSequence, ZoneEquipmentHeatingorNoLoadSequence, ZoneEquipmentSequentialCoolingFractionScheduleName, ZoneEquipmentSequentialHeatingFractionScheduleName,   };
  OS_ZoneHVAC_EquipmentListExtensibleFields()
   : EnumBase<OS_ZoneHVAC_EquipmentListExtensibleFields>(ZoneEquipment) {} 
  OS_ZoneHVAC_EquipmentListExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ZoneHVAC_EquipmentListExtensibleFields>(t_name) {} 
  OS_ZoneHVAC_EquipmentListExtensibleFields(int t_value) 
   : EnumBase<OS_ZoneHVAC_EquipmentListExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneHVAC_EquipmentListExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneHVAC_EquipmentListExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneHVAC_EquipmentListExtensibleFields>;
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
{ OS_ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipment, "ZoneEquipment", "Zone Equipment"},
{ OS_ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentCoolingSequence, "ZoneEquipmentCoolingSequence", "Zone Equipment Cooling Sequence"},
{ OS_ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentHeatingorNoLoadSequence, "ZoneEquipmentHeatingorNoLoadSequence", "Zone Equipment Heating or No-Load Sequence"},
{ OS_ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentSequentialCoolingFractionScheduleName, "ZoneEquipmentSequentialCoolingFractionScheduleName", "Zone Equipment Sequential Cooling Fraction Schedule Name"},
{ OS_ZoneHVAC_EquipmentListExtensibleFields::ZoneEquipmentSequentialHeatingFractionScheduleName, "ZoneEquipmentSequentialHeatingFractionScheduleName", "Zone Equipment Sequential Heating Fraction Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneHVAC_EquipmentListExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneHVAC_EquipmentListExtensibleFields> OptionalOS_ZoneHVAC_EquipmentListExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEHVAC_EQUIPMENTLIST_FIELDENUMS_HXX
