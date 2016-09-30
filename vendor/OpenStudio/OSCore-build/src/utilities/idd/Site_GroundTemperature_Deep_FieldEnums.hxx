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

#ifndef UTILITIES_IDD_SITE_GROUNDTEMPERATURE_DEEP_FIELDENUMS_HXX
#define UTILITIES_IDD_SITE_GROUNDTEMPERATURE_DEEP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Site_GroundTemperature_DeepFields
 *  \brief Enumeration of Site:GroundTemperature:Deep's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Site_GroundTemperature_DeepFields, )
#else
class Site_GroundTemperature_DeepFields: public ::EnumBase<Site_GroundTemperature_DeepFields> {
 public: 
  enum domain 
  {
JanuaryDeepGroundTemperature, FebruaryDeepGroundTemperature, MarchDeepGroundTemperature, AprilDeepGroundTemperature, MayDeepGroundTemperature, JuneDeepGroundTemperature, JulyDeepGroundTemperature, AugustDeepGroundTemperature, SeptemberDeepGroundTemperature, OctoberDeepGroundTemperature, NovemberDeepGroundTemperature, DecemberDeepGroundTemperature,   };
  Site_GroundTemperature_DeepFields()
   : EnumBase<Site_GroundTemperature_DeepFields>(JanuaryDeepGroundTemperature) {} 
  Site_GroundTemperature_DeepFields(const std::string &t_name) 
   : EnumBase<Site_GroundTemperature_DeepFields>(t_name) {} 
  Site_GroundTemperature_DeepFields(int t_value) 
   : EnumBase<Site_GroundTemperature_DeepFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_GroundTemperature_DeepFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_GroundTemperature_DeepFields>::value()); }
   private:
    friend class EnumBase<Site_GroundTemperature_DeepFields>;
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
{ Site_GroundTemperature_DeepFields::JanuaryDeepGroundTemperature, "JanuaryDeepGroundTemperature", "January Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::FebruaryDeepGroundTemperature, "FebruaryDeepGroundTemperature", "February Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::MarchDeepGroundTemperature, "MarchDeepGroundTemperature", "March Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::AprilDeepGroundTemperature, "AprilDeepGroundTemperature", "April Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::MayDeepGroundTemperature, "MayDeepGroundTemperature", "May Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::JuneDeepGroundTemperature, "JuneDeepGroundTemperature", "June Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::JulyDeepGroundTemperature, "JulyDeepGroundTemperature", "July Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::AugustDeepGroundTemperature, "AugustDeepGroundTemperature", "August Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::SeptemberDeepGroundTemperature, "SeptemberDeepGroundTemperature", "September Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::OctoberDeepGroundTemperature, "OctoberDeepGroundTemperature", "October Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::NovemberDeepGroundTemperature, "NovemberDeepGroundTemperature", "November Deep Ground Temperature"},
{ Site_GroundTemperature_DeepFields::DecemberDeepGroundTemperature, "DecemberDeepGroundTemperature", "December Deep Ground Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_GroundTemperature_DeepFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_GroundTemperature_DeepFields> OptionalSite_GroundTemperature_DeepFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SITE_GROUNDTEMPERATURE_DEEP_FIELDENUMS_HXX
