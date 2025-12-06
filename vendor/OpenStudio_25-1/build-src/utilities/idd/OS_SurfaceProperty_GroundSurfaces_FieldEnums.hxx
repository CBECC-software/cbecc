/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SURFACEPROPERTY_GROUNDSURFACES_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SURFACEPROPERTY_GROUNDSURFACES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SurfaceProperty_GroundSurfacesFields
 *  \brief Enumeration of OS:SurfaceProperty:GroundSurfaces's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SurfaceProperty_GroundSurfacesFields, )
#else
class OS_SurfaceProperty_GroundSurfacesFields: public ::EnumBase<OS_SurfaceProperty_GroundSurfacesFields> {
 public: 
  enum domain 
  {
Handle, Name,   };
  OS_SurfaceProperty_GroundSurfacesFields()
   : EnumBase<OS_SurfaceProperty_GroundSurfacesFields>(Handle) {} 
  OS_SurfaceProperty_GroundSurfacesFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceProperty_GroundSurfacesFields>(t_name) {} 
  OS_SurfaceProperty_GroundSurfacesFields(int t_value) 
   : EnumBase<OS_SurfaceProperty_GroundSurfacesFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceProperty_GroundSurfacesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceProperty_GroundSurfacesFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SurfaceProperty_GroundSurfacesFields>;
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
{ OS_SurfaceProperty_GroundSurfacesFields::Handle, "Handle", "Handle"},
{ OS_SurfaceProperty_GroundSurfacesFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceProperty_GroundSurfacesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceProperty_GroundSurfacesFields> OptionalOS_SurfaceProperty_GroundSurfacesFields ;
#endif

/** \class OS_SurfaceProperty_GroundSurfacesExtensibleFields
 *  \brief Enumeration of OS:SurfaceProperty:GroundSurfaces's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_SurfaceProperty_GroundSurfacesExtensibleFields, )
#else
class OS_SurfaceProperty_GroundSurfacesExtensibleFields: public ::EnumBase<OS_SurfaceProperty_GroundSurfacesExtensibleFields> {
 public: 
  enum domain 
  {
GroundSurfaceName, GroundSurfaceViewFactor, GroundSurfaceTemperatureScheduleName, GroundSurfaceReflectanceScheduleName,   };
  OS_SurfaceProperty_GroundSurfacesExtensibleFields()
   : EnumBase<OS_SurfaceProperty_GroundSurfacesExtensibleFields>(GroundSurfaceName) {} 
  OS_SurfaceProperty_GroundSurfacesExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceProperty_GroundSurfacesExtensibleFields>(t_name) {} 
  OS_SurfaceProperty_GroundSurfacesExtensibleFields(int t_value) 
   : EnumBase<OS_SurfaceProperty_GroundSurfacesExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceProperty_GroundSurfacesExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceProperty_GroundSurfacesExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SurfaceProperty_GroundSurfacesExtensibleFields>;
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
{ OS_SurfaceProperty_GroundSurfacesExtensibleFields::GroundSurfaceName, "GroundSurfaceName", "Ground Surface Name"},
{ OS_SurfaceProperty_GroundSurfacesExtensibleFields::GroundSurfaceViewFactor, "GroundSurfaceViewFactor", "Ground Surface View Factor"},
{ OS_SurfaceProperty_GroundSurfacesExtensibleFields::GroundSurfaceTemperatureScheduleName, "GroundSurfaceTemperatureScheduleName", "Ground Surface Temperature Schedule Name"},
{ OS_SurfaceProperty_GroundSurfacesExtensibleFields::GroundSurfaceReflectanceScheduleName, "GroundSurfaceReflectanceScheduleName", "Ground Surface Reflectance Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceProperty_GroundSurfacesExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceProperty_GroundSurfacesExtensibleFields> OptionalOS_SurfaceProperty_GroundSurfacesExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SURFACEPROPERTY_GROUNDSURFACES_FIELDENUMS_HXX
