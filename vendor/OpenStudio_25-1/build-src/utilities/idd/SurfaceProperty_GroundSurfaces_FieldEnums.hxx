/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SURFACEPROPERTY_GROUNDSURFACES_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACEPROPERTY_GROUNDSURFACES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceProperty_GroundSurfacesFields
 *  \brief Enumeration of SurfaceProperty:GroundSurfaces's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceProperty_GroundSurfacesFields, )
#else
class SurfaceProperty_GroundSurfacesFields: public ::EnumBase<SurfaceProperty_GroundSurfacesFields> {
 public: 
  enum domain 
  {
Name,   };
  SurfaceProperty_GroundSurfacesFields()
   : EnumBase<SurfaceProperty_GroundSurfacesFields>(Name) {} 
  SurfaceProperty_GroundSurfacesFields(const std::string &t_name) 
   : EnumBase<SurfaceProperty_GroundSurfacesFields>(t_name) {} 
  SurfaceProperty_GroundSurfacesFields(int t_value) 
   : EnumBase<SurfaceProperty_GroundSurfacesFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperty_GroundSurfacesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperty_GroundSurfacesFields>::integer_value()); }
   private:
    friend class EnumBase<SurfaceProperty_GroundSurfacesFields>;
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
{ SurfaceProperty_GroundSurfacesFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperty_GroundSurfacesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperty_GroundSurfacesFields> OptionalSurfaceProperty_GroundSurfacesFields ;
#endif

/** \class SurfaceProperty_GroundSurfacesExtensibleFields
 *  \brief Enumeration of SurfaceProperty:GroundSurfaces's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(SurfaceProperty_GroundSurfacesExtensibleFields, )
#else
class SurfaceProperty_GroundSurfacesExtensibleFields: public ::EnumBase<SurfaceProperty_GroundSurfacesExtensibleFields> {
 public: 
  enum domain 
  {
GroundSurfaceName, GroundSurfaceViewFactor, GroundSurfaceTemperatureScheduleName, GroundSurfaceReflectanceScheduleName,   };
  SurfaceProperty_GroundSurfacesExtensibleFields()
   : EnumBase<SurfaceProperty_GroundSurfacesExtensibleFields>(GroundSurfaceName) {} 
  SurfaceProperty_GroundSurfacesExtensibleFields(const std::string &t_name) 
   : EnumBase<SurfaceProperty_GroundSurfacesExtensibleFields>(t_name) {} 
  SurfaceProperty_GroundSurfacesExtensibleFields(int t_value) 
   : EnumBase<SurfaceProperty_GroundSurfacesExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperty_GroundSurfacesExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperty_GroundSurfacesExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<SurfaceProperty_GroundSurfacesExtensibleFields>;
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
{ SurfaceProperty_GroundSurfacesExtensibleFields::GroundSurfaceName, "GroundSurfaceName", "Ground Surface Name"},
{ SurfaceProperty_GroundSurfacesExtensibleFields::GroundSurfaceViewFactor, "GroundSurfaceViewFactor", "Ground Surface View Factor"},
{ SurfaceProperty_GroundSurfacesExtensibleFields::GroundSurfaceTemperatureScheduleName, "GroundSurfaceTemperatureScheduleName", "Ground Surface Temperature Schedule Name"},
{ SurfaceProperty_GroundSurfacesExtensibleFields::GroundSurfaceReflectanceScheduleName, "GroundSurfaceReflectanceScheduleName", "Ground Surface Reflectance Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperty_GroundSurfacesExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperty_GroundSurfacesExtensibleFields> OptionalSurfaceProperty_GroundSurfacesExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACEPROPERTY_GROUNDSURFACES_FIELDENUMS_HXX
