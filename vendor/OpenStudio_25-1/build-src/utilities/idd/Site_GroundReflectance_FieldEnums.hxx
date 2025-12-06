/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SITE_GROUNDREFLECTANCE_FIELDENUMS_HXX
#define UTILITIES_IDD_SITE_GROUNDREFLECTANCE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Site_GroundReflectanceFields
 *  \brief Enumeration of Site:GroundReflectance's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Site_GroundReflectanceFields, )
#else
class Site_GroundReflectanceFields: public ::EnumBase<Site_GroundReflectanceFields> {
 public: 
  enum domain 
  {
JanuaryGroundReflectance, FebruaryGroundReflectance, MarchGroundReflectance, AprilGroundReflectance, MayGroundReflectance, JuneGroundReflectance, JulyGroundReflectance, AugustGroundReflectance, SeptemberGroundReflectance, OctoberGroundReflectance, NovemberGroundReflectance, DecemberGroundReflectance,   };
  Site_GroundReflectanceFields()
   : EnumBase<Site_GroundReflectanceFields>(JanuaryGroundReflectance) {} 
  Site_GroundReflectanceFields(const std::string &t_name) 
   : EnumBase<Site_GroundReflectanceFields>(t_name) {} 
  Site_GroundReflectanceFields(int t_value) 
   : EnumBase<Site_GroundReflectanceFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_GroundReflectanceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_GroundReflectanceFields>::integer_value()); }
   private:
    friend class EnumBase<Site_GroundReflectanceFields>;
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
{ Site_GroundReflectanceFields::JanuaryGroundReflectance, "JanuaryGroundReflectance", "January Ground Reflectance"},
{ Site_GroundReflectanceFields::FebruaryGroundReflectance, "FebruaryGroundReflectance", "February Ground Reflectance"},
{ Site_GroundReflectanceFields::MarchGroundReflectance, "MarchGroundReflectance", "March Ground Reflectance"},
{ Site_GroundReflectanceFields::AprilGroundReflectance, "AprilGroundReflectance", "April Ground Reflectance"},
{ Site_GroundReflectanceFields::MayGroundReflectance, "MayGroundReflectance", "May Ground Reflectance"},
{ Site_GroundReflectanceFields::JuneGroundReflectance, "JuneGroundReflectance", "June Ground Reflectance"},
{ Site_GroundReflectanceFields::JulyGroundReflectance, "JulyGroundReflectance", "July Ground Reflectance"},
{ Site_GroundReflectanceFields::AugustGroundReflectance, "AugustGroundReflectance", "August Ground Reflectance"},
{ Site_GroundReflectanceFields::SeptemberGroundReflectance, "SeptemberGroundReflectance", "September Ground Reflectance"},
{ Site_GroundReflectanceFields::OctoberGroundReflectance, "OctoberGroundReflectance", "October Ground Reflectance"},
{ Site_GroundReflectanceFields::NovemberGroundReflectance, "NovemberGroundReflectance", "November Ground Reflectance"},
{ Site_GroundReflectanceFields::DecemberGroundReflectance, "DecemberGroundReflectance", "December Ground Reflectance"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_GroundReflectanceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_GroundReflectanceFields> OptionalSite_GroundReflectanceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SITE_GROUNDREFLECTANCE_FIELDENUMS_HXX
