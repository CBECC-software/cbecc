/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SITE_SOLARANDVISIBLESPECTRUM_FIELDENUMS_HXX
#define UTILITIES_IDD_SITE_SOLARANDVISIBLESPECTRUM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Site_SolarAndVisibleSpectrumFields
 *  \brief Enumeration of Site:SolarAndVisibleSpectrum's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Site_SolarAndVisibleSpectrumFields, )
#else
class Site_SolarAndVisibleSpectrumFields: public ::EnumBase<Site_SolarAndVisibleSpectrumFields> {
 public: 
  enum domain 
  {
Name, SpectrumDataMethod, SolarSpectrumDataObjectName, VisibleSpectrumDataObjectName,   };
  Site_SolarAndVisibleSpectrumFields()
   : EnumBase<Site_SolarAndVisibleSpectrumFields>(Name) {} 
  Site_SolarAndVisibleSpectrumFields(const std::string &t_name) 
   : EnumBase<Site_SolarAndVisibleSpectrumFields>(t_name) {} 
  Site_SolarAndVisibleSpectrumFields(int t_value) 
   : EnumBase<Site_SolarAndVisibleSpectrumFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_SolarAndVisibleSpectrumFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_SolarAndVisibleSpectrumFields>::integer_value()); }
   private:
    friend class EnumBase<Site_SolarAndVisibleSpectrumFields>;
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
{ Site_SolarAndVisibleSpectrumFields::Name, "Name", "Name"},
{ Site_SolarAndVisibleSpectrumFields::SpectrumDataMethod, "SpectrumDataMethod", "Spectrum Data Method"},
{ Site_SolarAndVisibleSpectrumFields::SolarSpectrumDataObjectName, "SolarSpectrumDataObjectName", "Solar Spectrum Data Object Name"},
{ Site_SolarAndVisibleSpectrumFields::VisibleSpectrumDataObjectName, "VisibleSpectrumDataObjectName", "Visible Spectrum Data Object Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_SolarAndVisibleSpectrumFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_SolarAndVisibleSpectrumFields> OptionalSite_SolarAndVisibleSpectrumFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SITE_SOLARANDVISIBLESPECTRUM_FIELDENUMS_HXX
