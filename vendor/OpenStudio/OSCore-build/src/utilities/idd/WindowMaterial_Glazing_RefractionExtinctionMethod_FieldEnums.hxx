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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_GLAZING_REFRACTIONEXTINCTIONMETHOD_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_GLAZING_REFRACTIONEXTINCTIONMETHOD_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_Glazing_RefractionExtinctionMethodFields
 *  \brief Enumeration of WindowMaterial:Glazing:RefractionExtinctionMethod's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_Glazing_RefractionExtinctionMethodFields, )
#else
class WindowMaterial_Glazing_RefractionExtinctionMethodFields: public ::EnumBase<WindowMaterial_Glazing_RefractionExtinctionMethodFields> {
 public: 
  enum domain 
  {
Name, Thickness, SolarIndexofRefraction, SolarExtinctionCoefficient, VisibleIndexofRefraction, VisibleExtinctionCoefficient, InfraredTransmittanceatNormalIncidence, InfraredHemisphericalEmissivity, Conductivity, DirtCorrectionFactorforSolarandVisibleTransmittance, SolarDiffusing,   };
  WindowMaterial_Glazing_RefractionExtinctionMethodFields()
   : EnumBase<WindowMaterial_Glazing_RefractionExtinctionMethodFields>(Name) {} 
  WindowMaterial_Glazing_RefractionExtinctionMethodFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_Glazing_RefractionExtinctionMethodFields>(t_name) {} 
  WindowMaterial_Glazing_RefractionExtinctionMethodFields(int t_value) 
   : EnumBase<WindowMaterial_Glazing_RefractionExtinctionMethodFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_Glazing_RefractionExtinctionMethodFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_Glazing_RefractionExtinctionMethodFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_Glazing_RefractionExtinctionMethodFields>;
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
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::Name, "Name", "Name"},
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::Thickness, "Thickness", "Thickness"},
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarIndexofRefraction, "SolarIndexofRefraction", "Solar Index of Refraction"},
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarExtinctionCoefficient, "SolarExtinctionCoefficient", "Solar Extinction Coefficient"},
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::VisibleIndexofRefraction, "VisibleIndexofRefraction", "Visible Index of Refraction"},
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::VisibleExtinctionCoefficient, "VisibleExtinctionCoefficient", "Visible Extinction Coefficient"},
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::InfraredTransmittanceatNormalIncidence, "InfraredTransmittanceatNormalIncidence", "Infrared Transmittance at Normal Incidence"},
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::InfraredHemisphericalEmissivity, "InfraredHemisphericalEmissivity", "Infrared Hemispherical Emissivity"},
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::Conductivity, "Conductivity", "Conductivity"},
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::DirtCorrectionFactorforSolarandVisibleTransmittance, "DirtCorrectionFactorforSolarandVisibleTransmittance", "Dirt Correction Factor for Solar and Visible Transmittance"},
{ WindowMaterial_Glazing_RefractionExtinctionMethodFields::SolarDiffusing, "SolarDiffusing", "Solar Diffusing"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_Glazing_RefractionExtinctionMethodFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_Glazing_RefractionExtinctionMethodFields> OptionalWindowMaterial_Glazing_RefractionExtinctionMethodFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_GLAZING_REFRACTIONEXTINCTIONMETHOD_FIELDENUMS_HXX
