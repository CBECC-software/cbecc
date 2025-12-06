/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SURFACEPROPERTY_INCIDENTSOLARMULTIPLIER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SURFACEPROPERTY_INCIDENTSOLARMULTIPLIER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_SurfaceProperty_IncidentSolarMultiplierFields
 *  \brief Enumeration of OS:SurfaceProperty:IncidentSolarMultiplier's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_SurfaceProperty_IncidentSolarMultiplierFields, )
#else
class OS_SurfaceProperty_IncidentSolarMultiplierFields: public ::EnumBase<OS_SurfaceProperty_IncidentSolarMultiplierFields> {
 public: 
  enum domain 
  {
Handle, SurfaceName, IncidentSolarMultiplier, IncidentSolarMultiplierScheduleName,   };
  OS_SurfaceProperty_IncidentSolarMultiplierFields()
   : EnumBase<OS_SurfaceProperty_IncidentSolarMultiplierFields>(Handle) {} 
  OS_SurfaceProperty_IncidentSolarMultiplierFields(const std::string &t_name) 
   : EnumBase<OS_SurfaceProperty_IncidentSolarMultiplierFields>(t_name) {} 
  OS_SurfaceProperty_IncidentSolarMultiplierFields(int t_value) 
   : EnumBase<OS_SurfaceProperty_IncidentSolarMultiplierFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_SurfaceProperty_IncidentSolarMultiplierFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_SurfaceProperty_IncidentSolarMultiplierFields>::integer_value()); }
   private:
    friend class EnumBase<OS_SurfaceProperty_IncidentSolarMultiplierFields>;
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
{ OS_SurfaceProperty_IncidentSolarMultiplierFields::Handle, "Handle", "Handle"},
{ OS_SurfaceProperty_IncidentSolarMultiplierFields::SurfaceName, "SurfaceName", "Surface Name"},
{ OS_SurfaceProperty_IncidentSolarMultiplierFields::IncidentSolarMultiplier, "IncidentSolarMultiplier", "Incident Solar Multiplier"},
{ OS_SurfaceProperty_IncidentSolarMultiplierFields::IncidentSolarMultiplierScheduleName, "IncidentSolarMultiplierScheduleName", "Incident Solar Multiplier Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_SurfaceProperty_IncidentSolarMultiplierFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_SurfaceProperty_IncidentSolarMultiplierFields> OptionalOS_SurfaceProperty_IncidentSolarMultiplierFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SURFACEPROPERTY_INCIDENTSOLARMULTIPLIER_FIELDENUMS_HXX
