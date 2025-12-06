/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SURFACEPROPERTY_SURROUNDINGSURFACES_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SURFACEPROPERTY_SURROUNDINGSURFACES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SurfaceProperty_SurroundingSurfacesFields
 *  \brief Enumeration of OS:SurfaceProperty:SurroundingSurfaces's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SurfaceProperty_SurroundingSurfacesFields, )
#else
class OS_SurfaceProperty_SurroundingSurfacesFields: public ::EnumBase<OS_SurfaceProperty_SurroundingSurfacesFields> {
 public: 
  enum domain 
  {
Handle, Name, SkyViewFactor, SkyTemperatureScheduleName, GroundViewFactor, GroundTemperatureScheduleName,   };
  OS_SurfaceProperty_SurroundingSurfacesFields()
   : EnumBase<OS_SurfaceProperty_SurroundingSurfacesFields>(Handle) {} 
  OS_SurfaceProperty_SurroundingSurfacesFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceProperty_SurroundingSurfacesFields>(t_name) {} 
  OS_SurfaceProperty_SurroundingSurfacesFields(int t_value) 
   : EnumBase<OS_SurfaceProperty_SurroundingSurfacesFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceProperty_SurroundingSurfacesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceProperty_SurroundingSurfacesFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SurfaceProperty_SurroundingSurfacesFields>;
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
{ OS_SurfaceProperty_SurroundingSurfacesFields::Handle, "Handle", "Handle"},
{ OS_SurfaceProperty_SurroundingSurfacesFields::Name, "Name", "Name"},
{ OS_SurfaceProperty_SurroundingSurfacesFields::SkyViewFactor, "SkyViewFactor", "Sky View Factor"},
{ OS_SurfaceProperty_SurroundingSurfacesFields::SkyTemperatureScheduleName, "SkyTemperatureScheduleName", "Sky Temperature Schedule Name"},
{ OS_SurfaceProperty_SurroundingSurfacesFields::GroundViewFactor, "GroundViewFactor", "Ground View Factor"},
{ OS_SurfaceProperty_SurroundingSurfacesFields::GroundTemperatureScheduleName, "GroundTemperatureScheduleName", "Ground Temperature Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceProperty_SurroundingSurfacesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceProperty_SurroundingSurfacesFields> OptionalOS_SurfaceProperty_SurroundingSurfacesFields ;
#endif

/** \class OS_SurfaceProperty_SurroundingSurfacesExtensibleFields
 *  \brief Enumeration of OS:SurfaceProperty:SurroundingSurfaces's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_SurfaceProperty_SurroundingSurfacesExtensibleFields, )
#else
class OS_SurfaceProperty_SurroundingSurfacesExtensibleFields: public ::EnumBase<OS_SurfaceProperty_SurroundingSurfacesExtensibleFields> {
 public: 
  enum domain 
  {
SurroundingSurfaceName, SurroundingSurfaceViewFactor, SurroundingSurfaceTemperatureScheduleName,   };
  OS_SurfaceProperty_SurroundingSurfacesExtensibleFields()
   : EnumBase<OS_SurfaceProperty_SurroundingSurfacesExtensibleFields>(SurroundingSurfaceName) {} 
  OS_SurfaceProperty_SurroundingSurfacesExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceProperty_SurroundingSurfacesExtensibleFields>(t_name) {} 
  OS_SurfaceProperty_SurroundingSurfacesExtensibleFields(int t_value) 
   : EnumBase<OS_SurfaceProperty_SurroundingSurfacesExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceProperty_SurroundingSurfacesExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceProperty_SurroundingSurfacesExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SurfaceProperty_SurroundingSurfacesExtensibleFields>;
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
{ OS_SurfaceProperty_SurroundingSurfacesExtensibleFields::SurroundingSurfaceName, "SurroundingSurfaceName", "Surrounding Surface Name"},
{ OS_SurfaceProperty_SurroundingSurfacesExtensibleFields::SurroundingSurfaceViewFactor, "SurroundingSurfaceViewFactor", "Surrounding Surface View Factor"},
{ OS_SurfaceProperty_SurroundingSurfacesExtensibleFields::SurroundingSurfaceTemperatureScheduleName, "SurroundingSurfaceTemperatureScheduleName", "Surrounding Surface Temperature Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceProperty_SurroundingSurfacesExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceProperty_SurroundingSurfacesExtensibleFields> OptionalOS_SurfaceProperty_SurroundingSurfacesExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SURFACEPROPERTY_SURROUNDINGSURFACES_FIELDENUMS_HXX
