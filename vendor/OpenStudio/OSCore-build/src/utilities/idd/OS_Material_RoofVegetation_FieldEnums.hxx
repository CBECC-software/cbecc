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

#ifndef UTILITIES_IDD_OS_MATERIAL_ROOFVEGETATION_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_MATERIAL_ROOFVEGETATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Material_RoofVegetationFields
 *  \brief Enumeration of OS:Material:RoofVegetation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Material_RoofVegetationFields, )
#else
class OS_Material_RoofVegetationFields: public ::EnumBase<OS_Material_RoofVegetationFields> {
 public: 
  enum domain 
  {
Handle, Name, HeightofPlants, LeafAreaIndex, LeafReflectivity, LeafEmissivity, MinimumStomatalResistance, SoilLayerName, Roughness, Thickness, ConductivityofDrySoil, DensityofDrySoil, SpecificHeatofDrySoil, ThermalAbsorptance, SolarAbsorptance, VisibleAbsorptance, SaturationVolumetricMoistureContentoftheSoilLayer, ResidualVolumetricMoistureContentoftheSoilLayer, InitialVolumetricMoistureContentoftheSoilLayer, MoistureDiffusionCalculationMethod,   };
  OS_Material_RoofVegetationFields()
   : EnumBase<OS_Material_RoofVegetationFields>(Handle) {} 
  OS_Material_RoofVegetationFields(const std::string &t_name) 
   : EnumBase<OS_Material_RoofVegetationFields>(t_name) {} 
  OS_Material_RoofVegetationFields(int t_value) 
   : EnumBase<OS_Material_RoofVegetationFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Material_RoofVegetationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Material_RoofVegetationFields>::value()); }
   private:
    friend class EnumBase<OS_Material_RoofVegetationFields>;
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
{ OS_Material_RoofVegetationFields::Handle, "Handle", "Handle"},
{ OS_Material_RoofVegetationFields::Name, "Name", "Name"},
{ OS_Material_RoofVegetationFields::HeightofPlants, "HeightofPlants", "Height of Plants"},
{ OS_Material_RoofVegetationFields::LeafAreaIndex, "LeafAreaIndex", "Leaf Area Index"},
{ OS_Material_RoofVegetationFields::LeafReflectivity, "LeafReflectivity", "Leaf Reflectivity"},
{ OS_Material_RoofVegetationFields::LeafEmissivity, "LeafEmissivity", "Leaf Emissivity"},
{ OS_Material_RoofVegetationFields::MinimumStomatalResistance, "MinimumStomatalResistance", "Minimum Stomatal Resistance"},
{ OS_Material_RoofVegetationFields::SoilLayerName, "SoilLayerName", "Soil Layer Name"},
{ OS_Material_RoofVegetationFields::Roughness, "Roughness", "Roughness"},
{ OS_Material_RoofVegetationFields::Thickness, "Thickness", "Thickness"},
{ OS_Material_RoofVegetationFields::ConductivityofDrySoil, "ConductivityofDrySoil", "Conductivity of Dry Soil"},
{ OS_Material_RoofVegetationFields::DensityofDrySoil, "DensityofDrySoil", "Density of Dry Soil"},
{ OS_Material_RoofVegetationFields::SpecificHeatofDrySoil, "SpecificHeatofDrySoil", "Specific Heat of Dry Soil"},
{ OS_Material_RoofVegetationFields::ThermalAbsorptance, "ThermalAbsorptance", "Thermal Absorptance"},
{ OS_Material_RoofVegetationFields::SolarAbsorptance, "SolarAbsorptance", "Solar Absorptance"},
{ OS_Material_RoofVegetationFields::VisibleAbsorptance, "VisibleAbsorptance", "Visible Absorptance"},
{ OS_Material_RoofVegetationFields::SaturationVolumetricMoistureContentoftheSoilLayer, "SaturationVolumetricMoistureContentoftheSoilLayer", "Saturation Volumetric Moisture Content of the Soil Layer"},
{ OS_Material_RoofVegetationFields::ResidualVolumetricMoistureContentoftheSoilLayer, "ResidualVolumetricMoistureContentoftheSoilLayer", "Residual Volumetric Moisture Content of the Soil Layer"},
{ OS_Material_RoofVegetationFields::InitialVolumetricMoistureContentoftheSoilLayer, "InitialVolumetricMoistureContentoftheSoilLayer", "Initial Volumetric Moisture Content of the Soil Layer"},
{ OS_Material_RoofVegetationFields::MoistureDiffusionCalculationMethod, "MoistureDiffusionCalculationMethod", "Moisture Diffusion Calculation Method"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Material_RoofVegetationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Material_RoofVegetationFields> OptionalOS_Material_RoofVegetationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_MATERIAL_ROOFVEGETATION_FIELDENUMS_HXX
