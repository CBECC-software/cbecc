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
Name, OpticalDataType, WindowGlassSpectralDataSetName, FrontSideBeamBeamSolarTransmittance, BackSideBeamBeamSolarTransmittance, FrontSideBeamBeamSolarReflectance, BackSideBeamBeamSolarReflectance, FrontSideBeamBeamVisibleSolarTransmittance, BackSideBeamBeamVisibleSolarTransmittance, FrontSideBeamBeamVisibleSolarReflectance, BackSideBeamBeamVisibleSolarReflectance, FrontSideBeamDiffuseSolarTransmittance, BackSideBeamDiffuseSolarTransmittance, FrontSideBeamDiffuseSolarReflectance, BackSideBeamDiffuseSolarReflectance, FrontSideBeamDiffuseVisibleSolarTransmittance, BackSideBeamDiffuseVisibleSolarTransmittance, FrontSideBeamDiffuseVisibleSolarReflectance, BackSideBeamDiffuseVisibleSolarReflectance, DiffuseDiffuseSolarTransmittance, FrontSideDiffuseDiffuseSolarReflectance, BackSideDiffuseDiffuseSolarReflectance, DiffuseDiffuseVisibleSolarTransmittance, FrontSideDiffuseDiffuseVisibleSolarReflectance, BackSideDiffuseDiffuseVisibleSolarReflectance, InfraredTransmittance_appliestofrontandback_, FrontSideInfraredEmissivity, BackSideInfraredEmissivity,   };
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
