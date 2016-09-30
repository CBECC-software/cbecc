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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_GLAZING_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_GLAZING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_GlazingFields
 *  \brief Enumeration of WindowMaterial:Glazing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_GlazingFields, )
#else
class WindowMaterial_GlazingFields: public ::EnumBase<WindowMaterial_GlazingFields> {
 public: 
  enum domain 
  {
Name, OpticalDataType, WindowGlassSpectralDataSetName, Thickness, SolarTransmittanceatNormalIncidence, FrontSideSolarReflectanceatNormalIncidence, BackSideSolarReflectanceatNormalIncidence, VisibleTransmittanceatNormalIncidence, FrontSideVisibleReflectanceatNormalIncidence, BackSideVisibleReflectanceatNormalIncidence, InfraredTransmittanceatNormalIncidence, FrontSideInfraredHemisphericalEmissivity, BackSideInfraredHemisphericalEmissivity, Conductivity, DirtCorrectionFactorforSolarandVisibleTransmittance, SolarDiffusing, Youngsmodulus, Poissonsratio,   };
  WindowMaterial_GlazingFields()
   : EnumBase<WindowMaterial_GlazingFields>(Name) {} 
  WindowMaterial_GlazingFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_GlazingFields>(t_name) {} 
  WindowMaterial_GlazingFields(int t_value) 
   : EnumBase<WindowMaterial_GlazingFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_GlazingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_GlazingFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_GlazingFields>;
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
{ WindowMaterial_GlazingFields::Name, "Name", "Name"},
{ WindowMaterial_GlazingFields::OpticalDataType, "OpticalDataType", "Optical Data Type"},
{ WindowMaterial_GlazingFields::WindowGlassSpectralDataSetName, "WindowGlassSpectralDataSetName", "Window Glass Spectral Data Set Name"},
{ WindowMaterial_GlazingFields::Thickness, "Thickness", "Thickness"},
{ WindowMaterial_GlazingFields::SolarTransmittanceatNormalIncidence, "SolarTransmittanceatNormalIncidence", "Solar Transmittance at Normal Incidence"},
{ WindowMaterial_GlazingFields::FrontSideSolarReflectanceatNormalIncidence, "FrontSideSolarReflectanceatNormalIncidence", "Front Side Solar Reflectance at Normal Incidence"},
{ WindowMaterial_GlazingFields::BackSideSolarReflectanceatNormalIncidence, "BackSideSolarReflectanceatNormalIncidence", "Back Side Solar Reflectance at Normal Incidence"},
{ WindowMaterial_GlazingFields::VisibleTransmittanceatNormalIncidence, "VisibleTransmittanceatNormalIncidence", "Visible Transmittance at Normal Incidence"},
{ WindowMaterial_GlazingFields::FrontSideVisibleReflectanceatNormalIncidence, "FrontSideVisibleReflectanceatNormalIncidence", "Front Side Visible Reflectance at Normal Incidence"},
{ WindowMaterial_GlazingFields::BackSideVisibleReflectanceatNormalIncidence, "BackSideVisibleReflectanceatNormalIncidence", "Back Side Visible Reflectance at Normal Incidence"},
{ WindowMaterial_GlazingFields::InfraredTransmittanceatNormalIncidence, "InfraredTransmittanceatNormalIncidence", "Infrared Transmittance at Normal Incidence"},
{ WindowMaterial_GlazingFields::FrontSideInfraredHemisphericalEmissivity, "FrontSideInfraredHemisphericalEmissivity", "Front Side Infrared Hemispherical Emissivity"},
{ WindowMaterial_GlazingFields::BackSideInfraredHemisphericalEmissivity, "BackSideInfraredHemisphericalEmissivity", "Back Side Infrared Hemispherical Emissivity"},
{ WindowMaterial_GlazingFields::Conductivity, "Conductivity", "Conductivity"},
{ WindowMaterial_GlazingFields::DirtCorrectionFactorforSolarandVisibleTransmittance, "DirtCorrectionFactorforSolarandVisibleTransmittance", "Dirt Correction Factor for Solar and Visible Transmittance"},
{ WindowMaterial_GlazingFields::SolarDiffusing, "SolarDiffusing", "Solar Diffusing"},
{ WindowMaterial_GlazingFields::Youngsmodulus, "Youngsmodulus", "Youngs modulus"},
{ WindowMaterial_GlazingFields::Poissonsratio, "Poissonsratio", "Poissons ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_GlazingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_GlazingFields> OptionalWindowMaterial_GlazingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_GLAZING_FIELDENUMS_HXX
