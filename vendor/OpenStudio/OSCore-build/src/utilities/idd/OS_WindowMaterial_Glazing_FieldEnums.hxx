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

#ifndef UTILITIES_IDD_OS_WINDOWMATERIAL_GLAZING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_WINDOWMATERIAL_GLAZING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_WindowMaterial_GlazingFields
 *  \brief Enumeration of OS:WindowMaterial:Glazing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_WindowMaterial_GlazingFields, )
#else
class OS_WindowMaterial_GlazingFields: public ::EnumBase<OS_WindowMaterial_GlazingFields> {
 public: 
  enum domain 
  {
Handle, Name, OpticalDataType, WindowGlassSpectralDataSetName, Thickness, SolarTransmittanceatNormalIncidence, FrontSideSolarReflectanceatNormalIncidence, BackSideSolarReflectanceatNormalIncidence, VisibleTransmittanceatNormalIncidence, FrontSideVisibleReflectanceatNormalIncidence, BackSideVisibleReflectanceatNormalIncidence, InfraredTransmittanceatNormalIncidence, FrontSideInfraredHemisphericalEmissivity, BackSideInfraredHemisphericalEmissivity, Conductivity, DirtCorrectionFactorforSolarandVisibleTransmittance, SolarDiffusing,   };
  OS_WindowMaterial_GlazingFields()
   : EnumBase<OS_WindowMaterial_GlazingFields>(Handle) {} 
  OS_WindowMaterial_GlazingFields(const std::string &t_name) 
   : EnumBase<OS_WindowMaterial_GlazingFields>(t_name) {} 
  OS_WindowMaterial_GlazingFields(int t_value) 
   : EnumBase<OS_WindowMaterial_GlazingFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_WindowMaterial_GlazingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_WindowMaterial_GlazingFields>::value()); }
   private:
    friend class EnumBase<OS_WindowMaterial_GlazingFields>;
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
{ OS_WindowMaterial_GlazingFields::Handle, "Handle", "Handle"},
{ OS_WindowMaterial_GlazingFields::Name, "Name", "Name"},
{ OS_WindowMaterial_GlazingFields::OpticalDataType, "OpticalDataType", "Optical Data Type"},
{ OS_WindowMaterial_GlazingFields::WindowGlassSpectralDataSetName, "WindowGlassSpectralDataSetName", "Window Glass Spectral Data Set Name"},
{ OS_WindowMaterial_GlazingFields::Thickness, "Thickness", "Thickness"},
{ OS_WindowMaterial_GlazingFields::SolarTransmittanceatNormalIncidence, "SolarTransmittanceatNormalIncidence", "Solar Transmittance at Normal Incidence"},
{ OS_WindowMaterial_GlazingFields::FrontSideSolarReflectanceatNormalIncidence, "FrontSideSolarReflectanceatNormalIncidence", "Front Side Solar Reflectance at Normal Incidence"},
{ OS_WindowMaterial_GlazingFields::BackSideSolarReflectanceatNormalIncidence, "BackSideSolarReflectanceatNormalIncidence", "Back Side Solar Reflectance at Normal Incidence"},
{ OS_WindowMaterial_GlazingFields::VisibleTransmittanceatNormalIncidence, "VisibleTransmittanceatNormalIncidence", "Visible Transmittance at Normal Incidence"},
{ OS_WindowMaterial_GlazingFields::FrontSideVisibleReflectanceatNormalIncidence, "FrontSideVisibleReflectanceatNormalIncidence", "Front Side Visible Reflectance at Normal Incidence"},
{ OS_WindowMaterial_GlazingFields::BackSideVisibleReflectanceatNormalIncidence, "BackSideVisibleReflectanceatNormalIncidence", "Back Side Visible Reflectance at Normal Incidence"},
{ OS_WindowMaterial_GlazingFields::InfraredTransmittanceatNormalIncidence, "InfraredTransmittanceatNormalIncidence", "Infrared Transmittance at Normal Incidence"},
{ OS_WindowMaterial_GlazingFields::FrontSideInfraredHemisphericalEmissivity, "FrontSideInfraredHemisphericalEmissivity", "Front Side Infrared Hemispherical Emissivity"},
{ OS_WindowMaterial_GlazingFields::BackSideInfraredHemisphericalEmissivity, "BackSideInfraredHemisphericalEmissivity", "Back Side Infrared Hemispherical Emissivity"},
{ OS_WindowMaterial_GlazingFields::Conductivity, "Conductivity", "Conductivity"},
{ OS_WindowMaterial_GlazingFields::DirtCorrectionFactorforSolarandVisibleTransmittance, "DirtCorrectionFactorforSolarandVisibleTransmittance", "Dirt Correction Factor for Solar and Visible Transmittance"},
{ OS_WindowMaterial_GlazingFields::SolarDiffusing, "SolarDiffusing", "Solar Diffusing"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_WindowMaterial_GlazingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_WindowMaterial_GlazingFields> OptionalOS_WindowMaterial_GlazingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_WINDOWMATERIAL_GLAZING_FIELDENUMS_HXX
