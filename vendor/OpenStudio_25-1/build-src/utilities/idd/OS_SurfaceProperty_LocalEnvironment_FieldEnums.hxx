/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SURFACEPROPERTY_LOCALENVIRONMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SURFACEPROPERTY_LOCALENVIRONMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SurfaceProperty_LocalEnvironmentFields
 *  \brief Enumeration of OS:SurfaceProperty:LocalEnvironment's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SurfaceProperty_LocalEnvironmentFields, )
#else
class OS_SurfaceProperty_LocalEnvironmentFields: public ::EnumBase<OS_SurfaceProperty_LocalEnvironmentFields> {
 public: 
  enum domain 
  {
Handle, Name, ExteriorSurfaceName, ExternalShadingFractionScheduleName, SurroundingSurfacesObjectName, OutdoorAirNodeName, GroundSurfacesObjectName,   };
  OS_SurfaceProperty_LocalEnvironmentFields()
   : EnumBase<OS_SurfaceProperty_LocalEnvironmentFields>(Handle) {} 
  OS_SurfaceProperty_LocalEnvironmentFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceProperty_LocalEnvironmentFields>(t_name) {} 
  OS_SurfaceProperty_LocalEnvironmentFields(int t_value) 
   : EnumBase<OS_SurfaceProperty_LocalEnvironmentFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceProperty_LocalEnvironmentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceProperty_LocalEnvironmentFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SurfaceProperty_LocalEnvironmentFields>;
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
{ OS_SurfaceProperty_LocalEnvironmentFields::Handle, "Handle", "Handle"},
{ OS_SurfaceProperty_LocalEnvironmentFields::Name, "Name", "Name"},
{ OS_SurfaceProperty_LocalEnvironmentFields::ExteriorSurfaceName, "ExteriorSurfaceName", "Exterior Surface Name"},
{ OS_SurfaceProperty_LocalEnvironmentFields::ExternalShadingFractionScheduleName, "ExternalShadingFractionScheduleName", "External Shading Fraction Schedule Name"},
{ OS_SurfaceProperty_LocalEnvironmentFields::SurroundingSurfacesObjectName, "SurroundingSurfacesObjectName", "Surrounding Surfaces Object Name"},
{ OS_SurfaceProperty_LocalEnvironmentFields::OutdoorAirNodeName, "OutdoorAirNodeName", "Outdoor Air Node Name"},
{ OS_SurfaceProperty_LocalEnvironmentFields::GroundSurfacesObjectName, "GroundSurfacesObjectName", "Ground Surfaces Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceProperty_LocalEnvironmentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceProperty_LocalEnvironmentFields> OptionalOS_SurfaceProperty_LocalEnvironmentFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SURFACEPROPERTY_LOCALENVIRONMENT_FIELDENUMS_HXX
