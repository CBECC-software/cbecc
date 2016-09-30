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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_SCREEN_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_SCREEN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_ScreenFields
 *  \brief Enumeration of WindowMaterial:Screen's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_ScreenFields, )
#else
class WindowMaterial_ScreenFields: public ::EnumBase<WindowMaterial_ScreenFields> {
 public: 
  enum domain 
  {
Name, ReflectedBeamTransmittanceAccountingMethod, DiffuseSolarReflectance, DiffuseVisibleReflectance, ThermalHemisphericalEmissivity, Conductivity, ScreenMaterialSpacing, ScreenMaterialDiameter, ScreentoGlassDistance, TopOpeningMultiplier, BottomOpeningMultiplier, LeftSideOpeningMultiplier, RightSideOpeningMultiplier, AngleofResolutionforScreenTransmittanceOutputMap,   };
  WindowMaterial_ScreenFields()
   : EnumBase<WindowMaterial_ScreenFields>(Name) {} 
  WindowMaterial_ScreenFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_ScreenFields>(t_name) {} 
  WindowMaterial_ScreenFields(int t_value) 
   : EnumBase<WindowMaterial_ScreenFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_ScreenFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_ScreenFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_ScreenFields>;
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
{ WindowMaterial_ScreenFields::Name, "Name", "Name"},
{ WindowMaterial_ScreenFields::ReflectedBeamTransmittanceAccountingMethod, "ReflectedBeamTransmittanceAccountingMethod", "Reflected Beam Transmittance Accounting Method"},
{ WindowMaterial_ScreenFields::DiffuseSolarReflectance, "DiffuseSolarReflectance", "Diffuse Solar Reflectance"},
{ WindowMaterial_ScreenFields::DiffuseVisibleReflectance, "DiffuseVisibleReflectance", "Diffuse Visible Reflectance"},
{ WindowMaterial_ScreenFields::ThermalHemisphericalEmissivity, "ThermalHemisphericalEmissivity", "Thermal Hemispherical Emissivity"},
{ WindowMaterial_ScreenFields::Conductivity, "Conductivity", "Conductivity"},
{ WindowMaterial_ScreenFields::ScreenMaterialSpacing, "ScreenMaterialSpacing", "Screen Material Spacing"},
{ WindowMaterial_ScreenFields::ScreenMaterialDiameter, "ScreenMaterialDiameter", "Screen Material Diameter"},
{ WindowMaterial_ScreenFields::ScreentoGlassDistance, "ScreentoGlassDistance", "Screen to Glass Distance"},
{ WindowMaterial_ScreenFields::TopOpeningMultiplier, "TopOpeningMultiplier", "Top Opening Multiplier"},
{ WindowMaterial_ScreenFields::BottomOpeningMultiplier, "BottomOpeningMultiplier", "Bottom Opening Multiplier"},
{ WindowMaterial_ScreenFields::LeftSideOpeningMultiplier, "LeftSideOpeningMultiplier", "Left Side Opening Multiplier"},
{ WindowMaterial_ScreenFields::RightSideOpeningMultiplier, "RightSideOpeningMultiplier", "Right Side Opening Multiplier"},
{ WindowMaterial_ScreenFields::AngleofResolutionforScreenTransmittanceOutputMap, "AngleofResolutionforScreenTransmittanceOutputMap", "Angle of Resolution for Screen Transmittance Output Map"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_ScreenFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_ScreenFields> OptionalWindowMaterial_ScreenFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_SCREEN_FIELDENUMS_HXX
