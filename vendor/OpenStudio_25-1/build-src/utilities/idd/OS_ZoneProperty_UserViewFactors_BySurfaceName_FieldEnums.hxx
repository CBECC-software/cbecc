/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ZONEPROPERTY_USERVIEWFACTORS_BYSURFACENAME_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ZONEPROPERTY_USERVIEWFACTORS_BYSURFACENAME_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_ZoneProperty_UserViewFactors_BySurfaceNameFields
 *  \brief Enumeration of OS:ZoneProperty:UserViewFactors:BySurfaceName's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_ZoneProperty_UserViewFactors_BySurfaceNameFields, )
#else
class OS_ZoneProperty_UserViewFactors_BySurfaceNameFields: public ::EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameFields> {
 public: 
  enum domain 
  {
Handle, ThermalZoneName,   };
  OS_ZoneProperty_UserViewFactors_BySurfaceNameFields()
   : EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameFields>(Handle) {} 
  OS_ZoneProperty_UserViewFactors_BySurfaceNameFields(const std::string &t_name) 
   : EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameFields>(t_name) {} 
  OS_ZoneProperty_UserViewFactors_BySurfaceNameFields(int t_value) 
   : EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneProperty_UserViewFactors_BySurfaceNameFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameFields>;
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
{ OS_ZoneProperty_UserViewFactors_BySurfaceNameFields::Handle, "Handle", "Handle"},
{ OS_ZoneProperty_UserViewFactors_BySurfaceNameFields::ThermalZoneName, "ThermalZoneName", "Thermal Zone Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneProperty_UserViewFactors_BySurfaceNameFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneProperty_UserViewFactors_BySurfaceNameFields> OptionalOS_ZoneProperty_UserViewFactors_BySurfaceNameFields ;
#endif

/** \class OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields
 *  \brief Enumeration of OS:ZoneProperty:UserViewFactors:BySurfaceName's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields, )
#else
class OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields: public ::EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields> {
 public: 
  enum domain 
  {
FromSurfaceName, ToSurfaceName, ViewFactor,   };
  OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields()
   : EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields>(FromSurfaceName) {} 
  OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields>(t_name) {} 
  OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields(int t_value) 
   : EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields>;
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
{ OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields::FromSurfaceName, "FromSurfaceName", "From Surface Name"},
{ OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields::ToSurfaceName, "ToSurfaceName", "To Surface Name"},
{ OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields::ViewFactor, "ViewFactor", "View Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields> OptionalOS_ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ZONEPROPERTY_USERVIEWFACTORS_BYSURFACENAME_FIELDENUMS_HXX
