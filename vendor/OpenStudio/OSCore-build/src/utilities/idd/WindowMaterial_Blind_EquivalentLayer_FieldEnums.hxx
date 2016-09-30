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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_BLIND_EQUIVALENTLAYER_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_BLIND_EQUIVALENTLAYER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_Blind_EquivalentLayerFields
 *  \brief Enumeration of WindowMaterial:Blind:EquivalentLayer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_Blind_EquivalentLayerFields, )
#else
class WindowMaterial_Blind_EquivalentLayerFields: public ::EnumBase<WindowMaterial_Blind_EquivalentLayerFields> {
 public: 
  enum domain 
  {
Name, SlatOrientation, SlatWidth, SlatSeparation, SlatCrown, SlatAngle, FrontSideSlatBeamDiffuseSolarTransmittance, BackSideSlatBeamDiffuseSolarTransmittance, FrontSideSlatBeamDiffuseSolarReflectance, BackSideSlatBeamDiffuseSolarReflectance, FrontSideSlatBeamDiffuseVisibleTransmittance, BackSideSlatBeamDiffuseVisibleTransmittance, FrontSideSlatBeamDiffuseVisibleReflectance, BackSideSlatBeamDiffuseVisibleReflectance, SlatDiffuseDiffuseSolarTransmittance, FrontSideSlatDiffuseDiffuseSolarReflectance, BackSideSlatDiffuseDiffuseSolarReflectance, SlatDiffuseDiffuseVisibleTransmittance, FrontSideSlatDiffuseDiffuseVisibleReflectance, BackSideSlatDiffuseDiffuseVisibleReflectance, SlatInfraredTransmittance, FrontSideSlatInfraredEmissivity, BackSideSlatInfraredEmissivity, SlatAngleControl,   };
  WindowMaterial_Blind_EquivalentLayerFields()
   : EnumBase<WindowMaterial_Blind_EquivalentLayerFields>(Name) {} 
  WindowMaterial_Blind_EquivalentLayerFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_Blind_EquivalentLayerFields>(t_name) {} 
  WindowMaterial_Blind_EquivalentLayerFields(int t_value) 
   : EnumBase<WindowMaterial_Blind_EquivalentLayerFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_Blind_EquivalentLayerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_Blind_EquivalentLayerFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_Blind_EquivalentLayerFields>;
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
{ WindowMaterial_Blind_EquivalentLayerFields::Name, "Name", "Name"},
{ WindowMaterial_Blind_EquivalentLayerFields::SlatOrientation, "SlatOrientation", "Slat Orientation"},
{ WindowMaterial_Blind_EquivalentLayerFields::SlatWidth, "SlatWidth", "Slat Width"},
{ WindowMaterial_Blind_EquivalentLayerFields::SlatSeparation, "SlatSeparation", "Slat Separation"},
{ WindowMaterial_Blind_EquivalentLayerFields::SlatCrown, "SlatCrown", "Slat Crown"},
{ WindowMaterial_Blind_EquivalentLayerFields::SlatAngle, "SlatAngle", "Slat Angle"},
{ WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseSolarTransmittance, "FrontSideSlatBeamDiffuseSolarTransmittance", "Front Side Slat Beam-Diffuse Solar Transmittance"},
{ WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseSolarTransmittance, "BackSideSlatBeamDiffuseSolarTransmittance", "Back Side Slat Beam-Diffuse Solar Transmittance"},
{ WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseSolarReflectance, "FrontSideSlatBeamDiffuseSolarReflectance", "Front Side Slat Beam-Diffuse Solar Reflectance"},
{ WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseSolarReflectance, "BackSideSlatBeamDiffuseSolarReflectance", "Back Side Slat Beam-Diffuse Solar Reflectance"},
{ WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseVisibleTransmittance, "FrontSideSlatBeamDiffuseVisibleTransmittance", "Front Side Slat Beam-Diffuse Visible Transmittance"},
{ WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseVisibleTransmittance, "BackSideSlatBeamDiffuseVisibleTransmittance", "Back Side Slat Beam-Diffuse Visible Transmittance"},
{ WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatBeamDiffuseVisibleReflectance, "FrontSideSlatBeamDiffuseVisibleReflectance", "Front Side Slat Beam-Diffuse Visible Reflectance"},
{ WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatBeamDiffuseVisibleReflectance, "BackSideSlatBeamDiffuseVisibleReflectance", "Back Side Slat Beam-Diffuse Visible Reflectance"},
{ WindowMaterial_Blind_EquivalentLayerFields::SlatDiffuseDiffuseSolarTransmittance, "SlatDiffuseDiffuseSolarTransmittance", "Slat Diffuse-Diffuse Solar Transmittance"},
{ WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatDiffuseDiffuseSolarReflectance, "FrontSideSlatDiffuseDiffuseSolarReflectance", "Front Side Slat Diffuse-Diffuse Solar Reflectance"},
{ WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatDiffuseDiffuseSolarReflectance, "BackSideSlatDiffuseDiffuseSolarReflectance", "Back Side Slat Diffuse-Diffuse Solar Reflectance"},
{ WindowMaterial_Blind_EquivalentLayerFields::SlatDiffuseDiffuseVisibleTransmittance, "SlatDiffuseDiffuseVisibleTransmittance", "Slat Diffuse-Diffuse Visible Transmittance"},
{ WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatDiffuseDiffuseVisibleReflectance, "FrontSideSlatDiffuseDiffuseVisibleReflectance", "Front Side Slat Diffuse-Diffuse Visible Reflectance"},
{ WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatDiffuseDiffuseVisibleReflectance, "BackSideSlatDiffuseDiffuseVisibleReflectance", "Back Side Slat Diffuse-Diffuse Visible Reflectance"},
{ WindowMaterial_Blind_EquivalentLayerFields::SlatInfraredTransmittance, "SlatInfraredTransmittance", "Slat Infrared Transmittance"},
{ WindowMaterial_Blind_EquivalentLayerFields::FrontSideSlatInfraredEmissivity, "FrontSideSlatInfraredEmissivity", "Front Side Slat Infrared Emissivity"},
{ WindowMaterial_Blind_EquivalentLayerFields::BackSideSlatInfraredEmissivity, "BackSideSlatInfraredEmissivity", "Back Side Slat Infrared Emissivity"},
{ WindowMaterial_Blind_EquivalentLayerFields::SlatAngleControl, "SlatAngleControl", "Slat Angle Control"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_Blind_EquivalentLayerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_Blind_EquivalentLayerFields> OptionalWindowMaterial_Blind_EquivalentLayerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_BLIND_EQUIVALENTLAYER_FIELDENUMS_HXX
