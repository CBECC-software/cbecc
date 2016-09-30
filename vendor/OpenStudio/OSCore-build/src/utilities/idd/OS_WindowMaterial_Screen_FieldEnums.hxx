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

#ifndef UTILITIES_IDD_OS_WINDOWMATERIAL_SCREEN_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WINDOWMATERIAL_SCREEN_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WindowMaterial_ScreenFields
 *  \brief Enumeration of OS:WindowMaterial:Screen's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WindowMaterial_ScreenFields, )
#else
class OS_WindowMaterial_ScreenFields: public ::EnumBase<OS_WindowMaterial_ScreenFields> {
 public: 
  enum domain 
  {
Handle, Name, ReflectedBeamTransmittanceAccountingMethod, DiffuseSolarReflectance, DiffuseVisibleReflectance, ThermalHemisphericalEmissivity, Conductivity, ScreenMaterialSpacing, ScreenMaterialDiameter, ScreentoGlassDistance, TopOpeningMultiplier, BottomOpeningMultiplier, LeftSideOpeningMultiplier, RightSideOpeningMultiplier, AngleofResolutionforScreenTransmittanceOutputMap,   };
  OS_WindowMaterial_ScreenFields()
   : EnumBase<OS_WindowMaterial_ScreenFields>(Handle) {} 
  OS_WindowMaterial_ScreenFields(const std::string &t_name) 
   : EnumBase<OS_WindowMaterial_ScreenFields>(t_name) {} 
  OS_WindowMaterial_ScreenFields(int t_value) 
   : EnumBase<OS_WindowMaterial_ScreenFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WindowMaterial_ScreenFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WindowMaterial_ScreenFields>::value()); }
   private:
    friend class EnumBase<OS_WindowMaterial_ScreenFields>;
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
{ OS_WindowMaterial_ScreenFields::Handle, "Handle", "Handle"},
{ OS_WindowMaterial_ScreenFields::Name, "Name", "Name"},
{ OS_WindowMaterial_ScreenFields::ReflectedBeamTransmittanceAccountingMethod, "ReflectedBeamTransmittanceAccountingMethod", "Reflected Beam Transmittance Accounting Method"},
{ OS_WindowMaterial_ScreenFields::DiffuseSolarReflectance, "DiffuseSolarReflectance", "Diffuse Solar Reflectance"},
{ OS_WindowMaterial_ScreenFields::DiffuseVisibleReflectance, "DiffuseVisibleReflectance", "Diffuse Visible Reflectance"},
{ OS_WindowMaterial_ScreenFields::ThermalHemisphericalEmissivity, "ThermalHemisphericalEmissivity", "Thermal Hemispherical Emissivity"},
{ OS_WindowMaterial_ScreenFields::Conductivity, "Conductivity", "Conductivity"},
{ OS_WindowMaterial_ScreenFields::ScreenMaterialSpacing, "ScreenMaterialSpacing", "Screen Material Spacing"},
{ OS_WindowMaterial_ScreenFields::ScreenMaterialDiameter, "ScreenMaterialDiameter", "Screen Material Diameter"},
{ OS_WindowMaterial_ScreenFields::ScreentoGlassDistance, "ScreentoGlassDistance", "Screen to Glass Distance"},
{ OS_WindowMaterial_ScreenFields::TopOpeningMultiplier, "TopOpeningMultiplier", "Top Opening Multiplier"},
{ OS_WindowMaterial_ScreenFields::BottomOpeningMultiplier, "BottomOpeningMultiplier", "Bottom Opening Multiplier"},
{ OS_WindowMaterial_ScreenFields::LeftSideOpeningMultiplier, "LeftSideOpeningMultiplier", "Left Side Opening Multiplier"},
{ OS_WindowMaterial_ScreenFields::RightSideOpeningMultiplier, "RightSideOpeningMultiplier", "Right Side Opening Multiplier"},
{ OS_WindowMaterial_ScreenFields::AngleofResolutionforScreenTransmittanceOutputMap, "AngleofResolutionforScreenTransmittanceOutputMap", "Angle of Resolution for Screen Transmittance Output Map"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WindowMaterial_ScreenFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WindowMaterial_ScreenFields> OptionalOS_WindowMaterial_ScreenFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WINDOWMATERIAL_SCREEN_FIELDENUMS_HXX
