/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_SITE_GROUNDTEMPERATURE_FCFACTORMETHOD_FIELDENUMS_HXX
#define UTILITIES_IDD_SITE_GROUNDTEMPERATURE_FCFACTORMETHOD_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Site_GroundTemperature_FCfactorMethodFields
 *  \brief Enumeration of Site:GroundTemperature:FCfactorMethod's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Site_GroundTemperature_FCfactorMethodFields, )
#else
class Site_GroundTemperature_FCfactorMethodFields: public ::EnumBase<Site_GroundTemperature_FCfactorMethodFields> {
 public: 
  enum domain 
  {
JanuaryGroundTemperature, FebruaryGroundTemperature, MarchGroundTemperature, AprilGroundTemperature, MayGroundTemperature, JuneGroundTemperature, JulyGroundTemperature, AugustGroundTemperature, SeptemberGroundTemperature, OctoberGroundTemperature, NovemberGroundTemperature, DecemberGroundTemperature,   };
  Site_GroundTemperature_FCfactorMethodFields()
   : EnumBase<Site_GroundTemperature_FCfactorMethodFields>(JanuaryGroundTemperature) {} 
  Site_GroundTemperature_FCfactorMethodFields(const std::string &t_name) 
   : EnumBase<Site_GroundTemperature_FCfactorMethodFields>(t_name) {} 
  Site_GroundTemperature_FCfactorMethodFields(int t_value) 
   : EnumBase<Site_GroundTemperature_FCfactorMethodFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_GroundTemperature_FCfactorMethodFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_GroundTemperature_FCfactorMethodFields>::value()); }
   private:
    friend class EnumBase<Site_GroundTemperature_FCfactorMethodFields>;
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
{ Site_GroundTemperature_FCfactorMethodFields::JanuaryGroundTemperature, "JanuaryGroundTemperature", "January Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::FebruaryGroundTemperature, "FebruaryGroundTemperature", "February Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::MarchGroundTemperature, "MarchGroundTemperature", "March Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::AprilGroundTemperature, "AprilGroundTemperature", "April Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::MayGroundTemperature, "MayGroundTemperature", "May Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::JuneGroundTemperature, "JuneGroundTemperature", "June Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::JulyGroundTemperature, "JulyGroundTemperature", "July Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::AugustGroundTemperature, "AugustGroundTemperature", "August Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::SeptemberGroundTemperature, "SeptemberGroundTemperature", "September Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::OctoberGroundTemperature, "OctoberGroundTemperature", "October Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::NovemberGroundTemperature, "NovemberGroundTemperature", "November Ground Temperature"},
{ Site_GroundTemperature_FCfactorMethodFields::DecemberGroundTemperature, "DecemberGroundTemperature", "December Ground Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_GroundTemperature_FCfactorMethodFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_GroundTemperature_FCfactorMethodFields> OptionalSite_GroundTemperature_FCfactorMethodFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SITE_GROUNDTEMPERATURE_FCFACTORMETHOD_FIELDENUMS_HXX
