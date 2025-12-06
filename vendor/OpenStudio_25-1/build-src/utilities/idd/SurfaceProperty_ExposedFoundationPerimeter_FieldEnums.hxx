/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SURFACEPROPERTY_EXPOSEDFOUNDATIONPERIMETER_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACEPROPERTY_EXPOSEDFOUNDATIONPERIMETER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceProperty_ExposedFoundationPerimeterFields
 *  \brief Enumeration of SurfaceProperty:ExposedFoundationPerimeter's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceProperty_ExposedFoundationPerimeterFields, )
#else
class SurfaceProperty_ExposedFoundationPerimeterFields: public ::EnumBase<SurfaceProperty_ExposedFoundationPerimeterFields> {
 public: 
  enum domain 
  {
SurfaceName, ExposedPerimeterCalculationMethod, TotalExposedPerimeter, ExposedPerimeterFraction,   };
  SurfaceProperty_ExposedFoundationPerimeterFields()
   : EnumBase<SurfaceProperty_ExposedFoundationPerimeterFields>(SurfaceName) {} 
  SurfaceProperty_ExposedFoundationPerimeterFields(const std::string &t_name) 
   : EnumBase<SurfaceProperty_ExposedFoundationPerimeterFields>(t_name) {} 
  SurfaceProperty_ExposedFoundationPerimeterFields(int t_value) 
   : EnumBase<SurfaceProperty_ExposedFoundationPerimeterFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperty_ExposedFoundationPerimeterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperty_ExposedFoundationPerimeterFields>::integer_value()); }
   private:
    friend class EnumBase<SurfaceProperty_ExposedFoundationPerimeterFields>;
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
{ SurfaceProperty_ExposedFoundationPerimeterFields::SurfaceName, "SurfaceName", "Surface Name"},
{ SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterCalculationMethod, "ExposedPerimeterCalculationMethod", "Exposed Perimeter Calculation Method"},
{ SurfaceProperty_ExposedFoundationPerimeterFields::TotalExposedPerimeter, "TotalExposedPerimeter", "Total Exposed Perimeter"},
{ SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterFraction, "ExposedPerimeterFraction", "Exposed Perimeter Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperty_ExposedFoundationPerimeterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperty_ExposedFoundationPerimeterFields> OptionalSurfaceProperty_ExposedFoundationPerimeterFields ;
#endif

/** \class SurfaceProperty_ExposedFoundationPerimeterExtensibleFields
 *  \brief Enumeration of SurfaceProperty:ExposedFoundationPerimeter's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(SurfaceProperty_ExposedFoundationPerimeterExtensibleFields, )
#else
class SurfaceProperty_ExposedFoundationPerimeterExtensibleFields: public ::EnumBase<SurfaceProperty_ExposedFoundationPerimeterExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceSegmentExposed,   };
  SurfaceProperty_ExposedFoundationPerimeterExtensibleFields()
   : EnumBase<SurfaceProperty_ExposedFoundationPerimeterExtensibleFields>(SurfaceSegmentExposed) {} 
  SurfaceProperty_ExposedFoundationPerimeterExtensibleFields(const std::string &t_name) 
   : EnumBase<SurfaceProperty_ExposedFoundationPerimeterExtensibleFields>(t_name) {} 
  SurfaceProperty_ExposedFoundationPerimeterExtensibleFields(int t_value) 
   : EnumBase<SurfaceProperty_ExposedFoundationPerimeterExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperty_ExposedFoundationPerimeterExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperty_ExposedFoundationPerimeterExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<SurfaceProperty_ExposedFoundationPerimeterExtensibleFields>;
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
{ SurfaceProperty_ExposedFoundationPerimeterExtensibleFields::SurfaceSegmentExposed, "SurfaceSegmentExposed", "Surface Segment Exposed"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperty_ExposedFoundationPerimeterExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperty_ExposedFoundationPerimeterExtensibleFields> OptionalSurfaceProperty_ExposedFoundationPerimeterExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACEPROPERTY_EXPOSEDFOUNDATIONPERIMETER_FIELDENUMS_HXX
