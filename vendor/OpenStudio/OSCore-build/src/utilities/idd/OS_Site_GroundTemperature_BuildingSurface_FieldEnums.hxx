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

#ifndef UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_BUILDINGSURFACE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_BUILDINGSURFACE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Site_GroundTemperature_BuildingSurfaceFields
 *  \brief Enumeration of OS:Site:GroundTemperature:BuildingSurface's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Site_GroundTemperature_BuildingSurfaceFields, )
#else
class OS_Site_GroundTemperature_BuildingSurfaceFields: public ::EnumBase<OS_Site_GroundTemperature_BuildingSurfaceFields> {
 public: 
  enum domain 
  {
Handle, JanuaryGroundTemperature, FebruaryGroundTemperature, MarchGroundTemperature, AprilGroundTemperature, MayGroundTemperature, JuneGroundTemperature, JulyGroundTemperature, AugustGroundTemperature, SeptemberGroundTemperature, OctoberGroundTemperature, NovemberGroundTemperature, DecemberGroundTemperature,   };
  OS_Site_GroundTemperature_BuildingSurfaceFields()
   : EnumBase<OS_Site_GroundTemperature_BuildingSurfaceFields>(Handle) {} 
  OS_Site_GroundTemperature_BuildingSurfaceFields(const std::string &t_name) 
   : EnumBase<OS_Site_GroundTemperature_BuildingSurfaceFields>(t_name) {} 
  OS_Site_GroundTemperature_BuildingSurfaceFields(int t_value) 
   : EnumBase<OS_Site_GroundTemperature_BuildingSurfaceFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Site_GroundTemperature_BuildingSurfaceFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Site_GroundTemperature_BuildingSurfaceFields>::value()); }
   private:
    friend class EnumBase<OS_Site_GroundTemperature_BuildingSurfaceFields>;
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
{ OS_Site_GroundTemperature_BuildingSurfaceFields::Handle, "Handle", "Handle"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::JanuaryGroundTemperature, "JanuaryGroundTemperature", "January Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::FebruaryGroundTemperature, "FebruaryGroundTemperature", "February Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::MarchGroundTemperature, "MarchGroundTemperature", "March Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::AprilGroundTemperature, "AprilGroundTemperature", "April Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::MayGroundTemperature, "MayGroundTemperature", "May Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::JuneGroundTemperature, "JuneGroundTemperature", "June Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::JulyGroundTemperature, "JulyGroundTemperature", "July Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::AugustGroundTemperature, "AugustGroundTemperature", "August Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::SeptemberGroundTemperature, "SeptemberGroundTemperature", "September Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::OctoberGroundTemperature, "OctoberGroundTemperature", "October Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::NovemberGroundTemperature, "NovemberGroundTemperature", "November Ground Temperature"},
{ OS_Site_GroundTemperature_BuildingSurfaceFields::DecemberGroundTemperature, "DecemberGroundTemperature", "December Ground Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Site_GroundTemperature_BuildingSurfaceFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Site_GroundTemperature_BuildingSurfaceFields> OptionalOS_Site_GroundTemperature_BuildingSurfaceFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_BUILDINGSURFACE_FIELDENUMS_HXX
