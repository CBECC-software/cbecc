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

#ifndef UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_SHALLOW_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_SHALLOW_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Site_GroundTemperature_ShallowFields
 *  \brief Enumeration of OS:Site:GroundTemperature:Shallow's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Site_GroundTemperature_ShallowFields, )
#else
class OS_Site_GroundTemperature_ShallowFields: public ::EnumBase<OS_Site_GroundTemperature_ShallowFields> {
 public: 
  enum domain 
  {
Handle, JanuarySurfaceGroundTemperature, FebruarySurfaceGroundTemperature, MarchSurfaceGroundTemperature, AprilSurfaceGroundTemperature, MaySurfaceGroundTemperature, JuneSurfaceGroundTemperature, JulySurfaceGroundTemperature, AugustSurfaceGroundTemperature, SeptemberSurfaceGroundTemperature, OctoberSurfaceGroundTemperature, NovemberSurfaceGroundTemperature, DecemberSurfaceGroundTemperature,   };
  OS_Site_GroundTemperature_ShallowFields()
   : EnumBase<OS_Site_GroundTemperature_ShallowFields>(Handle) {} 
  OS_Site_GroundTemperature_ShallowFields(const std::string &t_name) 
   : EnumBase<OS_Site_GroundTemperature_ShallowFields>(t_name) {} 
  OS_Site_GroundTemperature_ShallowFields(int t_value) 
   : EnumBase<OS_Site_GroundTemperature_ShallowFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Site_GroundTemperature_ShallowFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Site_GroundTemperature_ShallowFields>::value()); }
   private:
    friend class EnumBase<OS_Site_GroundTemperature_ShallowFields>;
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
{ OS_Site_GroundTemperature_ShallowFields::Handle, "Handle", "Handle"},
{ OS_Site_GroundTemperature_ShallowFields::JanuarySurfaceGroundTemperature, "JanuarySurfaceGroundTemperature", "January Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::FebruarySurfaceGroundTemperature, "FebruarySurfaceGroundTemperature", "February Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::MarchSurfaceGroundTemperature, "MarchSurfaceGroundTemperature", "March Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::AprilSurfaceGroundTemperature, "AprilSurfaceGroundTemperature", "April Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::MaySurfaceGroundTemperature, "MaySurfaceGroundTemperature", "May Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::JuneSurfaceGroundTemperature, "JuneSurfaceGroundTemperature", "June Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::JulySurfaceGroundTemperature, "JulySurfaceGroundTemperature", "July Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::AugustSurfaceGroundTemperature, "AugustSurfaceGroundTemperature", "August Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::SeptemberSurfaceGroundTemperature, "SeptemberSurfaceGroundTemperature", "September Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::OctoberSurfaceGroundTemperature, "OctoberSurfaceGroundTemperature", "October Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::NovemberSurfaceGroundTemperature, "NovemberSurfaceGroundTemperature", "November Surface Ground Temperature"},
{ OS_Site_GroundTemperature_ShallowFields::DecemberSurfaceGroundTemperature, "DecemberSurfaceGroundTemperature", "December Surface Ground Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Site_GroundTemperature_ShallowFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Site_GroundTemperature_ShallowFields> OptionalOS_Site_GroundTemperature_ShallowFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_SHALLOW_FIELDENUMS_HXX
