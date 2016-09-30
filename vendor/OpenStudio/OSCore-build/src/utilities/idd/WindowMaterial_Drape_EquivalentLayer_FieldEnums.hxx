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

#ifndef UTILITIES_IDD_WINDOWMATERIAL_DRAPE_EQUIVALENTLAYER_FIELDENUMS_HXX
#define UTILITIES_IDD_WINDOWMATERIAL_DRAPE_EQUIVALENTLAYER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WindowMaterial_Drape_EquivalentLayerFields
 *  \brief Enumeration of WindowMaterial:Drape:EquivalentLayer's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WindowMaterial_Drape_EquivalentLayerFields, )
#else
class WindowMaterial_Drape_EquivalentLayerFields: public ::EnumBase<WindowMaterial_Drape_EquivalentLayerFields> {
 public: 
  enum domain 
  {
Name, DrapeBeamBeamSolarTransmittanceatNormalIncidence, FrontSideDrapeBeamDiffuseSolarTransmittance, BackSideDrapeBeamDiffuseSolarTransmittance, FrontSideDrapeBeamDiffuseSolarReflectance, BackSideDrapeBeamDiffuseSolarReflectance, DrapeBeamBeamVisibleTransmittance, DrapeBeamDiffuseVisibleTransmittance, DrapeBeamDiffuseVisibleReflectance, DrapeMaterialInfraredTransmittance, FrontSideDrapeMaterialInfraredEmissivity, BackSideDrapeMaterialInfraredEmissivity, WidthofPleatedFabric, LengthofPleatedFabric,   };
  WindowMaterial_Drape_EquivalentLayerFields()
   : EnumBase<WindowMaterial_Drape_EquivalentLayerFields>(Name) {} 
  WindowMaterial_Drape_EquivalentLayerFields(const std::string &t_name) 
   : EnumBase<WindowMaterial_Drape_EquivalentLayerFields>(t_name) {} 
  WindowMaterial_Drape_EquivalentLayerFields(int t_value) 
   : EnumBase<WindowMaterial_Drape_EquivalentLayerFields>(t_value) {} 
  static std::string enumName() 
  { return "WindowMaterial_Drape_EquivalentLayerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WindowMaterial_Drape_EquivalentLayerFields>::value()); }
   private:
    friend class EnumBase<WindowMaterial_Drape_EquivalentLayerFields>;
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
{ WindowMaterial_Drape_EquivalentLayerFields::Name, "Name", "Name"},
{ WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamBeamSolarTransmittanceatNormalIncidence, "DrapeBeamBeamSolarTransmittanceatNormalIncidence", "Drape Beam-Beam Solar Transmittance at Normal Incidence"},
{ WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeBeamDiffuseSolarTransmittance, "FrontSideDrapeBeamDiffuseSolarTransmittance", "Front Side Drape Beam-Diffuse Solar Transmittance"},
{ WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeBeamDiffuseSolarTransmittance, "BackSideDrapeBeamDiffuseSolarTransmittance", "Back Side Drape Beam-Diffuse Solar Transmittance"},
{ WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeBeamDiffuseSolarReflectance, "FrontSideDrapeBeamDiffuseSolarReflectance", "Front Side Drape Beam-Diffuse Solar Reflectance"},
{ WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeBeamDiffuseSolarReflectance, "BackSideDrapeBeamDiffuseSolarReflectance", "Back Side Drape Beam-Diffuse Solar Reflectance"},
{ WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamBeamVisibleTransmittance, "DrapeBeamBeamVisibleTransmittance", "Drape Beam-Beam Visible Transmittance"},
{ WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamDiffuseVisibleTransmittance, "DrapeBeamDiffuseVisibleTransmittance", "Drape Beam-Diffuse Visible Transmittance"},
{ WindowMaterial_Drape_EquivalentLayerFields::DrapeBeamDiffuseVisibleReflectance, "DrapeBeamDiffuseVisibleReflectance", "Drape Beam-Diffuse Visible Reflectance"},
{ WindowMaterial_Drape_EquivalentLayerFields::DrapeMaterialInfraredTransmittance, "DrapeMaterialInfraredTransmittance", "Drape Material Infrared Transmittance"},
{ WindowMaterial_Drape_EquivalentLayerFields::FrontSideDrapeMaterialInfraredEmissivity, "FrontSideDrapeMaterialInfraredEmissivity", "Front Side Drape Material Infrared Emissivity"},
{ WindowMaterial_Drape_EquivalentLayerFields::BackSideDrapeMaterialInfraredEmissivity, "BackSideDrapeMaterialInfraredEmissivity", "Back Side Drape Material Infrared Emissivity"},
{ WindowMaterial_Drape_EquivalentLayerFields::WidthofPleatedFabric, "WidthofPleatedFabric", "Width of Pleated Fabric"},
{ WindowMaterial_Drape_EquivalentLayerFields::LengthofPleatedFabric, "LengthofPleatedFabric", "Length of Pleated Fabric"},
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
  inline std::ostream &operator<<(std::ostream &os, const WindowMaterial_Drape_EquivalentLayerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WindowMaterial_Drape_EquivalentLayerFields> OptionalWindowMaterial_Drape_EquivalentLayerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WINDOWMATERIAL_DRAPE_EQUIVALENTLAYER_FIELDENUMS_HXX
