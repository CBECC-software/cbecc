/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

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
Name, OpticalDataType, WindowGlassSpectralDataSetName, Thickness, SolarTransmittanceatNormalIncidence, FrontSideSolarReflectanceatNormalIncidence, BackSideSolarReflectanceatNormalIncidence, VisibleTransmittanceatNormalIncidence, FrontSideVisibleReflectanceatNormalIncidence, BackSideVisibleReflectanceatNormalIncidence, InfraredTransmittanceatNormalIncidence, FrontSideInfraredHemisphericalEmissivity, BackSideInfraredHemisphericalEmissivity, Conductivity, DirtCorrectionFactorforSolarandVisibleTransmittance, SolarDiffusing, Youngsmodulus, Poissonsratio, WindowGlassSpectralandIncidentAngleTransmittanceDataSetTableName, WindowGlassSpectralandIncidentAngleFrontReflectanceDataSetTableName, WindowGlassSpectralandIncidentAngleBackReflectanceDataSetTableName,   };
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
{ WindowMaterial_GlazingFields::WindowGlassSpectralandIncidentAngleTransmittanceDataSetTableName, "WindowGlassSpectralandIncidentAngleTransmittanceDataSetTableName", "Window Glass Spectral and Incident Angle Transmittance Data Set Table Name"},
{ WindowMaterial_GlazingFields::WindowGlassSpectralandIncidentAngleFrontReflectanceDataSetTableName, "WindowGlassSpectralandIncidentAngleFrontReflectanceDataSetTableName", "Window Glass Spectral and Incident Angle Front Reflectance Data Set Table Name"},
{ WindowMaterial_GlazingFields::WindowGlassSpectralandIncidentAngleBackReflectanceDataSetTableName, "WindowGlassSpectralandIncidentAngleBackReflectanceDataSetTableName", "Window Glass Spectral and Incident Angle Back Reflectance Data Set Table Name"},
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
