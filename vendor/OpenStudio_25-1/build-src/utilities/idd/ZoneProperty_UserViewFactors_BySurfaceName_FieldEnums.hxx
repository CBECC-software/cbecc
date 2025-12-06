/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ZONEPROPERTY_USERVIEWFACTORS_BYSURFACENAME_FIELDENUMS_HXX
#define UTILITIES_IDD_ZONEPROPERTY_USERVIEWFACTORS_BYSURFACENAME_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class ZoneProperty_UserViewFactors_BySurfaceNameFields
 *  \brief Enumeration of ZoneProperty:UserViewFactors:BySurfaceName's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(ZoneProperty_UserViewFactors_BySurfaceNameFields, )
#else
class ZoneProperty_UserViewFactors_BySurfaceNameFields: public ::EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameFields> {
 public: 
  enum domain 
  {
ZoneorZoneListorSpaceorSpaceListName,   };
  ZoneProperty_UserViewFactors_BySurfaceNameFields()
   : EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameFields>(ZoneorZoneListorSpaceorSpaceListName) {} 
  ZoneProperty_UserViewFactors_BySurfaceNameFields(const std::string &t_name) 
   : EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameFields>(t_name) {} 
  ZoneProperty_UserViewFactors_BySurfaceNameFields(int t_value) 
   : EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneProperty_UserViewFactors_BySurfaceNameFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameFields>;
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
{ ZoneProperty_UserViewFactors_BySurfaceNameFields::ZoneorZoneListorSpaceorSpaceListName, "ZoneorZoneListorSpaceorSpaceListName", "Zone or ZoneList or Space or SpaceList Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneProperty_UserViewFactors_BySurfaceNameFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneProperty_UserViewFactors_BySurfaceNameFields> OptionalZoneProperty_UserViewFactors_BySurfaceNameFields ;
#endif

/** \class ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields
 *  \brief Enumeration of ZoneProperty:UserViewFactors:BySurfaceName's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields, )
#else
class ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields: public ::EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields> {
 public: 
  enum domain 
  {
FromSurface, ToSurface, ViewFactor,   };
  ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields()
   : EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields>(FromSurface) {} 
  ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields(const std::string &t_name) 
   : EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields>(t_name) {} 
  ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields(int t_value) 
   : EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields>;
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
{ ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields::FromSurface, "FromSurface", "From Surface"},
{ ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields::ToSurface, "ToSurface", "To Surface"},
{ ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields::ViewFactor, "ViewFactor", "View Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<ZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields> OptionalZoneProperty_UserViewFactors_BySurfaceNameExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ZONEPROPERTY_USERVIEWFACTORS_BYSURFACENAME_FIELDENUMS_HXX
