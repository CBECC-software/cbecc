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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_BLIND_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_BLIND_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_BlindFields
 *  \brief Enumeration of WindowMaterial:Blind's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_BlindFields, )
#else
class WindowMaterial_BlindFields: public ::EnumBase<WindowMaterial_BlindFields> {
 public: 
  enum domain 
  {
Name, SlatOrientation, SlatWidth, SlatSeparation, SlatThickness, SlatAngle, SlatConductivity, SlatBeamSolarTransmittance, FrontSideSlatBeamSolarReflectance, BackSideSlatBeamSolarReflectance, SlatDiffuseSolarTransmittance, FrontSideSlatDiffuseSolarReflectance, BackSideSlatDiffuseSolarReflectance, SlatBeamVisibleTransmittance, FrontSideSlatBeamVisibleReflectance, BackSideSlatBeamVisibleReflectance, SlatDiffuseVisibleTransmittance, FrontSideSlatDiffuseVisibleReflectance, BackSideSlatDiffuseVisibleReflectance, SlatInfraredHemisphericalTransmittance, FrontSideSlatInfraredHemisphericalEmissivity, BackSideSlatInfraredHemisphericalEmissivity, BlindtoGlassDistance, BlindTopOpeningMultiplier, BlindBottomOpeningMultiplier, BlindLeftSideOpeningMultiplier, BlindRightSideOpeningMultiplier, MinimumSlatAngle, MaximumSlatAngle,   };
  WindowMaterial_BlindFields()
   : EnumBase<WindowMaterial_BlindFields>(Name) {} 
  WindowMaterial_BlindFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_BlindFields>(t_name) {} 
  WindowMaterial_BlindFields(int t_value) 
   : EnumBase<WindowMaterial_BlindFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_BlindFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_BlindFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_BlindFields>;
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
{ WindowMaterial_BlindFields::Name, "Name", "Name"},
{ WindowMaterial_BlindFields::SlatOrientation, "SlatOrientation", "Slat Orientation"},
{ WindowMaterial_BlindFields::SlatWidth, "SlatWidth", "Slat Width"},
{ WindowMaterial_BlindFields::SlatSeparation, "SlatSeparation", "Slat Separation"},
{ WindowMaterial_BlindFields::SlatThickness, "SlatThickness", "Slat Thickness"},
{ WindowMaterial_BlindFields::SlatAngle, "SlatAngle", "Slat Angle"},
{ WindowMaterial_BlindFields::SlatConductivity, "SlatConductivity", "Slat Conductivity"},
{ WindowMaterial_BlindFields::SlatBeamSolarTransmittance, "SlatBeamSolarTransmittance", "Slat Beam Solar Transmittance"},
{ WindowMaterial_BlindFields::FrontSideSlatBeamSolarReflectance, "FrontSideSlatBeamSolarReflectance", "Front Side Slat Beam Solar Reflectance"},
{ WindowMaterial_BlindFields::BackSideSlatBeamSolarReflectance, "BackSideSlatBeamSolarReflectance", "Back Side Slat Beam Solar Reflectance"},
{ WindowMaterial_BlindFields::SlatDiffuseSolarTransmittance, "SlatDiffuseSolarTransmittance", "Slat Diffuse Solar Transmittance"},
{ WindowMaterial_BlindFields::FrontSideSlatDiffuseSolarReflectance, "FrontSideSlatDiffuseSolarReflectance", "Front Side Slat Diffuse Solar Reflectance"},
{ WindowMaterial_BlindFields::BackSideSlatDiffuseSolarReflectance, "BackSideSlatDiffuseSolarReflectance", "Back Side Slat Diffuse Solar Reflectance"},
{ WindowMaterial_BlindFields::SlatBeamVisibleTransmittance, "SlatBeamVisibleTransmittance", "Slat Beam Visible Transmittance"},
{ WindowMaterial_BlindFields::FrontSideSlatBeamVisibleReflectance, "FrontSideSlatBeamVisibleReflectance", "Front Side Slat Beam Visible Reflectance"},
{ WindowMaterial_BlindFields::BackSideSlatBeamVisibleReflectance, "BackSideSlatBeamVisibleReflectance", "Back Side Slat Beam Visible Reflectance"},
{ WindowMaterial_BlindFields::SlatDiffuseVisibleTransmittance, "SlatDiffuseVisibleTransmittance", "Slat Diffuse Visible Transmittance"},
{ WindowMaterial_BlindFields::FrontSideSlatDiffuseVisibleReflectance, "FrontSideSlatDiffuseVisibleReflectance", "Front Side Slat Diffuse Visible Reflectance"},
{ WindowMaterial_BlindFields::BackSideSlatDiffuseVisibleReflectance, "BackSideSlatDiffuseVisibleReflectance", "Back Side Slat Diffuse Visible Reflectance"},
{ WindowMaterial_BlindFields::SlatInfraredHemisphericalTransmittance, "SlatInfraredHemisphericalTransmittance", "Slat Infrared Hemispherical Transmittance"},
{ WindowMaterial_BlindFields::FrontSideSlatInfraredHemisphericalEmissivity, "FrontSideSlatInfraredHemisphericalEmissivity", "Front Side Slat Infrared Hemispherical Emissivity"},
{ WindowMaterial_BlindFields::BackSideSlatInfraredHemisphericalEmissivity, "BackSideSlatInfraredHemisphericalEmissivity", "Back Side Slat Infrared Hemispherical Emissivity"},
{ WindowMaterial_BlindFields::BlindtoGlassDistance, "BlindtoGlassDistance", "Blind to Glass Distance"},
{ WindowMaterial_BlindFields::BlindTopOpeningMultiplier, "BlindTopOpeningMultiplier", "Blind Top Opening Multiplier"},
{ WindowMaterial_BlindFields::BlindBottomOpeningMultiplier, "BlindBottomOpeningMultiplier", "Blind Bottom Opening Multiplier"},
{ WindowMaterial_BlindFields::BlindLeftSideOpeningMultiplier, "BlindLeftSideOpeningMultiplier", "Blind Left Side Opening Multiplier"},
{ WindowMaterial_BlindFields::BlindRightSideOpeningMultiplier, "BlindRightSideOpeningMultiplier", "Blind Right Side Opening Multiplier"},
{ WindowMaterial_BlindFields::MinimumSlatAngle, "MinimumSlatAngle", "Minimum Slat Angle"},
{ WindowMaterial_BlindFields::MaximumSlatAngle, "MaximumSlatAngle", "Maximum Slat Angle"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_BlindFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_BlindFields> OptionalWindowMaterial_BlindFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_BLIND_FIELDENUMS_HXX
