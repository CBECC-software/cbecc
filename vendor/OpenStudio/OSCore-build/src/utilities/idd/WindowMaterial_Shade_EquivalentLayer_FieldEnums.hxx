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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_SHADE_EQUIVALENTLAYER_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_SHADE_EQUIVALENTLAYER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_Shade_EquivalentLayerFields
 *  \brief Enumeration of WindowMaterial:Shade:EquivalentLayer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_Shade_EquivalentLayerFields, )
#else
class WindowMaterial_Shade_EquivalentLayerFields: public ::EnumBase<WindowMaterial_Shade_EquivalentLayerFields> {
 public: 
  enum domain 
  {
Name, ShadeBeamBeamSolarTransmittance, FrontSideShadeBeamDiffuseSolarTransmittance, BackSideShadeBeamDiffuseSolarTransmittance, FrontSideShadeBeamDiffuseSolarReflectance, BackSideShadeBeamDiffuseSolarReflectance, ShadeBeamBeamVisibleTransmittanceatNormalIncidence, ShadeBeamDiffuseVisibleTransmittanceatNormalIncidence, ShadeBeamDiffuseVisibleReflectanceatNormalIncidence, ShadeMaterialInfraredTransmittance, FrontSideShadeMaterialInfraredEmissivity, BackSideShadeMaterialInfraredEmissivity,   };
  WindowMaterial_Shade_EquivalentLayerFields()
   : EnumBase<WindowMaterial_Shade_EquivalentLayerFields>(Name) {} 
  WindowMaterial_Shade_EquivalentLayerFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_Shade_EquivalentLayerFields>(t_name) {} 
  WindowMaterial_Shade_EquivalentLayerFields(int t_value) 
   : EnumBase<WindowMaterial_Shade_EquivalentLayerFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_Shade_EquivalentLayerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_Shade_EquivalentLayerFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_Shade_EquivalentLayerFields>;
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
{ WindowMaterial_Shade_EquivalentLayerFields::Name, "Name", "Name"},
{ WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamBeamSolarTransmittance, "ShadeBeamBeamSolarTransmittance", "Shade Beam-Beam Solar Transmittance"},
{ WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeBeamDiffuseSolarTransmittance, "FrontSideShadeBeamDiffuseSolarTransmittance", "Front Side Shade Beam-Diffuse Solar Transmittance"},
{ WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeBeamDiffuseSolarTransmittance, "BackSideShadeBeamDiffuseSolarTransmittance", "Back Side Shade Beam-Diffuse Solar Transmittance"},
{ WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeBeamDiffuseSolarReflectance, "FrontSideShadeBeamDiffuseSolarReflectance", "Front Side Shade Beam-Diffuse Solar Reflectance"},
{ WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeBeamDiffuseSolarReflectance, "BackSideShadeBeamDiffuseSolarReflectance", "Back Side Shade Beam-Diffuse Solar Reflectance"},
{ WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamBeamVisibleTransmittanceatNormalIncidence, "ShadeBeamBeamVisibleTransmittanceatNormalIncidence", "Shade Beam-Beam Visible Transmittance at Normal Incidence"},
{ WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamDiffuseVisibleTransmittanceatNormalIncidence, "ShadeBeamDiffuseVisibleTransmittanceatNormalIncidence", "Shade Beam-Diffuse Visible Transmittance at Normal Incidence"},
{ WindowMaterial_Shade_EquivalentLayerFields::ShadeBeamDiffuseVisibleReflectanceatNormalIncidence, "ShadeBeamDiffuseVisibleReflectanceatNormalIncidence", "Shade Beam-Diffuse Visible Reflectance at Normal Incidence"},
{ WindowMaterial_Shade_EquivalentLayerFields::ShadeMaterialInfraredTransmittance, "ShadeMaterialInfraredTransmittance", "Shade Material Infrared Transmittance"},
{ WindowMaterial_Shade_EquivalentLayerFields::FrontSideShadeMaterialInfraredEmissivity, "FrontSideShadeMaterialInfraredEmissivity", "Front Side Shade Material Infrared Emissivity"},
{ WindowMaterial_Shade_EquivalentLayerFields::BackSideShadeMaterialInfraredEmissivity, "BackSideShadeMaterialInfraredEmissivity", "Back Side Shade Material Infrared Emissivity"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_Shade_EquivalentLayerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_Shade_EquivalentLayerFields> OptionalWindowMaterial_Shade_EquivalentLayerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_SHADE_EQUIVALENTLAYER_FIELDENUMS_HXX
