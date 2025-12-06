/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SURFACEPROPERTY_EXPOSEDFOUNDATIONPERIMETER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SURFACEPROPERTY_EXPOSEDFOUNDATIONPERIMETER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SurfaceProperty_ExposedFoundationPerimeterFields
 *  \brief Enumeration of OS:SurfaceProperty:ExposedFoundationPerimeter's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SurfaceProperty_ExposedFoundationPerimeterFields, )
#else
class OS_SurfaceProperty_ExposedFoundationPerimeterFields: public ::EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterFields> {
 public: 
  enum domain 
  {
Handle, SurfaceName, ExposedPerimeterCalculationMethod, TotalExposedPerimeter, ExposedPerimeterFraction,   };
  OS_SurfaceProperty_ExposedFoundationPerimeterFields()
   : EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterFields>(Handle) {} 
  OS_SurfaceProperty_ExposedFoundationPerimeterFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterFields>(t_name) {} 
  OS_SurfaceProperty_ExposedFoundationPerimeterFields(int t_value) 
   : EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceProperty_ExposedFoundationPerimeterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterFields>;
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
{ OS_SurfaceProperty_ExposedFoundationPerimeterFields::Handle, "Handle", "Handle"},
{ OS_SurfaceProperty_ExposedFoundationPerimeterFields::SurfaceName, "SurfaceName", "Surface Name"},
{ OS_SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterCalculationMethod, "ExposedPerimeterCalculationMethod", "Exposed Perimeter Calculation Method"},
{ OS_SurfaceProperty_ExposedFoundationPerimeterFields::TotalExposedPerimeter, "TotalExposedPerimeter", "Total Exposed Perimeter"},
{ OS_SurfaceProperty_ExposedFoundationPerimeterFields::ExposedPerimeterFraction, "ExposedPerimeterFraction", "Exposed Perimeter Fraction"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceProperty_ExposedFoundationPerimeterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceProperty_ExposedFoundationPerimeterFields> OptionalOS_SurfaceProperty_ExposedFoundationPerimeterFields ;
#endif

/** \class OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields
 *  \brief Enumeration of OS:SurfaceProperty:ExposedFoundationPerimeter's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields, )
#else
class OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields: public ::EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceSegmentExposed,   };
  OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields()
   : EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields>(SurfaceSegmentExposed) {} 
  OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields>(t_name) {} 
  OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields(int t_value) 
   : EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields>;
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
{ OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields::SurfaceSegmentExposed, "SurfaceSegmentExposed", "Surface Segment Exposed"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields> OptionalOS_SurfaceProperty_ExposedFoundationPerimeterExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SURFACEPROPERTY_EXPOSEDFOUNDATIONPERIMETER_FIELDENUMS_HXX
