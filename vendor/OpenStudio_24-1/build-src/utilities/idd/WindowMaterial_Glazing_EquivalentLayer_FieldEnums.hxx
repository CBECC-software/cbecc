/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_GLAZING_EQUIVALENTLAYER_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_GLAZING_EQUIVALENTLAYER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_Glazing_EquivalentLayerFields
 *  \brief Enumeration of WindowMaterial:Glazing:EquivalentLayer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_Glazing_EquivalentLayerFields, )
#else
class WindowMaterial_Glazing_EquivalentLayerFields: public ::EnumBase<WindowMaterial_Glazing_EquivalentLayerFields> {
 public: 
  enum domain 
  {
Name, OpticalDataType, WindowGlassSpectralDataSetName, FrontSideBeamBeamSolarTransmittance, BackSideBeamBeamSolarTransmittance, FrontSideBeamBeamSolarReflectance, BackSideBeamBeamSolarReflectance, FrontSideBeamBeamVisibleSolarTransmittance, BackSideBeamBeamVisibleSolarTransmittance, FrontSideBeamBeamVisibleSolarReflectance, BackSideBeamBeamVisibleSolarReflectance, FrontSideBeamDiffuseSolarTransmittance, BackSideBeamDiffuseSolarTransmittance, FrontSideBeamDiffuseSolarReflectance, BackSideBeamDiffuseSolarReflectance, FrontSideBeamDiffuseVisibleSolarTransmittance, BackSideBeamDiffuseVisibleSolarTransmittance, FrontSideBeamDiffuseVisibleSolarReflectance, BackSideBeamDiffuseVisibleSolarReflectance, DiffuseDiffuseSolarTransmittance, FrontSideDiffuseDiffuseSolarReflectance, BackSideDiffuseDiffuseSolarReflectance, DiffuseDiffuseVisibleSolarTransmittance, FrontSideDiffuseDiffuseVisibleSolarReflectance, BackSideDiffuseDiffuseVisibleSolarReflectance, InfraredTransmittance_appliestofrontandback_, FrontSideInfraredEmissivity, BackSideInfraredEmissivity, ThermalResistance,   };
  WindowMaterial_Glazing_EquivalentLayerFields()
   : EnumBase<WindowMaterial_Glazing_EquivalentLayerFields>(Name) {} 
  WindowMaterial_Glazing_EquivalentLayerFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_Glazing_EquivalentLayerFields>(t_name) {} 
  WindowMaterial_Glazing_EquivalentLayerFields(int t_value) 
   : EnumBase<WindowMaterial_Glazing_EquivalentLayerFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_Glazing_EquivalentLayerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_Glazing_EquivalentLayerFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_Glazing_EquivalentLayerFields>;
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
{ WindowMaterial_Glazing_EquivalentLayerFields::Name, "Name", "Name"},
{ WindowMaterial_Glazing_EquivalentLayerFields::OpticalDataType, "OpticalDataType", "Optical Data Type"},
{ WindowMaterial_Glazing_EquivalentLayerFields::WindowGlassSpectralDataSetName, "WindowGlassSpectralDataSetName", "Window Glass Spectral Data Set Name"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamSolarTransmittance, "FrontSideBeamBeamSolarTransmittance", "Front Side Beam-Beam Solar Transmittance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamSolarTransmittance, "BackSideBeamBeamSolarTransmittance", "Back Side Beam-Beam Solar Transmittance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamSolarReflectance, "FrontSideBeamBeamSolarReflectance", "Front Side Beam-Beam Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamSolarReflectance, "BackSideBeamBeamSolarReflectance", "Back Side Beam-Beam Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamVisibleSolarTransmittance, "FrontSideBeamBeamVisibleSolarTransmittance", "Front Side Beam-Beam Visible Solar Transmittance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamVisibleSolarTransmittance, "BackSideBeamBeamVisibleSolarTransmittance", "Back Side Beam-Beam Visible Solar Transmittance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamBeamVisibleSolarReflectance, "FrontSideBeamBeamVisibleSolarReflectance", "Front Side Beam-Beam Visible Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamBeamVisibleSolarReflectance, "BackSideBeamBeamVisibleSolarReflectance", "Back Side Beam-Beam Visible Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseSolarTransmittance, "FrontSideBeamDiffuseSolarTransmittance", "Front Side Beam-Diffuse Solar Transmittance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseSolarTransmittance, "BackSideBeamDiffuseSolarTransmittance", "Back Side Beam-Diffuse Solar Transmittance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseSolarReflectance, "FrontSideBeamDiffuseSolarReflectance", "Front Side Beam-Diffuse Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseSolarReflectance, "BackSideBeamDiffuseSolarReflectance", "Back Side Beam-Diffuse Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseVisibleSolarTransmittance, "FrontSideBeamDiffuseVisibleSolarTransmittance", "Front Side Beam-Diffuse Visible Solar Transmittance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseVisibleSolarTransmittance, "BackSideBeamDiffuseVisibleSolarTransmittance", "Back Side Beam-Diffuse Visible Solar Transmittance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideBeamDiffuseVisibleSolarReflectance, "FrontSideBeamDiffuseVisibleSolarReflectance", "Front Side Beam-Diffuse Visible Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideBeamDiffuseVisibleSolarReflectance, "BackSideBeamDiffuseVisibleSolarReflectance", "Back Side Beam-Diffuse Visible Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseSolarTransmittance, "DiffuseDiffuseSolarTransmittance", "Diffuse-Diffuse Solar Transmittance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseSolarReflectance, "FrontSideDiffuseDiffuseSolarReflectance", "Front Side Diffuse-Diffuse Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseSolarReflectance, "BackSideDiffuseDiffuseSolarReflectance", "Back Side Diffuse-Diffuse Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::DiffuseDiffuseVisibleSolarTransmittance, "DiffuseDiffuseVisibleSolarTransmittance", "Diffuse-Diffuse Visible Solar Transmittance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideDiffuseDiffuseVisibleSolarReflectance, "FrontSideDiffuseDiffuseVisibleSolarReflectance", "Front Side Diffuse-Diffuse Visible Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideDiffuseDiffuseVisibleSolarReflectance, "BackSideDiffuseDiffuseVisibleSolarReflectance", "Back Side Diffuse-Diffuse Visible Solar Reflectance"},
{ WindowMaterial_Glazing_EquivalentLayerFields::InfraredTransmittance_appliestofrontandback_, "InfraredTransmittance_appliestofrontandback_", "Infrared Transmittance (applies to front and back)"},
{ WindowMaterial_Glazing_EquivalentLayerFields::FrontSideInfraredEmissivity, "FrontSideInfraredEmissivity", "Front Side Infrared Emissivity"},
{ WindowMaterial_Glazing_EquivalentLayerFields::BackSideInfraredEmissivity, "BackSideInfraredEmissivity", "Back Side Infrared Emissivity"},
{ WindowMaterial_Glazing_EquivalentLayerFields::ThermalResistance, "ThermalResistance", "Thermal Resistance"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_Glazing_EquivalentLayerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_Glazing_EquivalentLayerFields> OptionalWindowMaterial_Glazing_EquivalentLayerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_GLAZING_EQUIVALENTLAYER_FIELDENUMS_HXX
