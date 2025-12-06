/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_DAYLIGHTINGDEVICE_TUBULAR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_DAYLIGHTINGDEVICE_TUBULAR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_DaylightingDevice_TubularFields
 *  \brief Enumeration of OS:DaylightingDevice:Tubular's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_DaylightingDevice_TubularFields, )
#else
class OS_DaylightingDevice_TubularFields: public ::EnumBase<OS_DaylightingDevice_TubularFields> {
 public: 
  enum domain 
  {
Handle, Name, DomeName, DiffuserName, ConstructionName, Diameter, TotalLength, EffectiveThermalResistance,   };
  OS_DaylightingDevice_TubularFields()
   : EnumBase<OS_DaylightingDevice_TubularFields>(Handle) {} 
  OS_DaylightingDevice_TubularFields(const std::string &t_name) 
   : EnumBase<OS_DaylightingDevice_TubularFields>(t_name) {} 
  OS_DaylightingDevice_TubularFields(int t_value) 
   : EnumBase<OS_DaylightingDevice_TubularFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_DaylightingDevice_TubularFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_DaylightingDevice_TubularFields>::integer_value()); }
   private:
    friend class EnumBase<OS_DaylightingDevice_TubularFields>;
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
{ OS_DaylightingDevice_TubularFields::Handle, "Handle", "Handle"},
{ OS_DaylightingDevice_TubularFields::Name, "Name", "Name"},
{ OS_DaylightingDevice_TubularFields::DomeName, "DomeName", "Dome Name"},
{ OS_DaylightingDevice_TubularFields::DiffuserName, "DiffuserName", "Diffuser Name"},
{ OS_DaylightingDevice_TubularFields::ConstructionName, "ConstructionName", "Construction Name"},
{ OS_DaylightingDevice_TubularFields::Diameter, "Diameter", "Diameter"},
{ OS_DaylightingDevice_TubularFields::TotalLength, "TotalLength", "Total Length"},
{ OS_DaylightingDevice_TubularFields::EffectiveThermalResistance, "EffectiveThermalResistance", "Effective Thermal Resistance"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_DaylightingDevice_TubularFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_DaylightingDevice_TubularFields> OptionalOS_DaylightingDevice_TubularFields ;
#endif

/** \class OS_DaylightingDevice_TubularExtensibleFields
 *  \brief Enumeration of OS:DaylightingDevice:Tubular's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_DaylightingDevice_TubularExtensibleFields, )
#else
class OS_DaylightingDevice_TubularExtensibleFields: public ::EnumBase<OS_DaylightingDevice_TubularExtensibleFields> {
 public: 
  enum domain 
  {
TransitionZoneName, TransitionZoneLength,   };
  OS_DaylightingDevice_TubularExtensibleFields()
   : EnumBase<OS_DaylightingDevice_TubularExtensibleFields>(TransitionZoneName) {} 
  OS_DaylightingDevice_TubularExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_DaylightingDevice_TubularExtensibleFields>(t_name) {} 
  OS_DaylightingDevice_TubularExtensibleFields(int t_value) 
   : EnumBase<OS_DaylightingDevice_TubularExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_DaylightingDevice_TubularExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_DaylightingDevice_TubularExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_DaylightingDevice_TubularExtensibleFields>;
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
{ OS_DaylightingDevice_TubularExtensibleFields::TransitionZoneName, "TransitionZoneName", "Transition Zone Name"},
{ OS_DaylightingDevice_TubularExtensibleFields::TransitionZoneLength, "TransitionZoneLength", "Transition Zone Length"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_DaylightingDevice_TubularExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_DaylightingDevice_TubularExtensibleFields> OptionalOS_DaylightingDevice_TubularExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_DAYLIGHTINGDEVICE_TUBULAR_FIELDENUMS_HXX
