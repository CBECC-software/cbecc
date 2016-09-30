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

#ifndef UTILITIES_IDD_MATERIAL_ROOFVEGETATION_FIELDENUMS_HXX
#define UTILITIES_IDD_MATERIAL_ROOFVEGETATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Material_RoofVegetationFields
 *  \brief Enumeration of Material:RoofVegetation's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Material_RoofVegetationFields, )
#else
class Material_RoofVegetationFields: public ::EnumBase<Material_RoofVegetationFields> {
 public: 
  enum domain 
  {
Name, HeightofPlants, LeafAreaIndex, LeafReflectivity, LeafEmissivity, MinimumStomatalResistance, SoilLayerName, Roughness, Thickness, ConductivityofDrySoil, DensityofDrySoil, SpecificHeatofDrySoil, ThermalAbsorptance, SolarAbsorptance, VisibleAbsorptance, SaturationVolumetricMoistureContentoftheSoilLayer, ResidualVolumetricMoistureContentoftheSoilLayer, InitialVolumetricMoistureContentoftheSoilLayer, MoistureDiffusionCalculationMethod,   };
  Material_RoofVegetationFields()
   : EnumBase<Material_RoofVegetationFields>(Name) {} 
  Material_RoofVegetationFields(const std::string &t_name) 
   : EnumBase<Material_RoofVegetationFields>(t_name) {} 
  Material_RoofVegetationFields(int t_value) 
   : EnumBase<Material_RoofVegetationFields>(t_value) {} 
  static std::string enumName() 
  { return "Material_RoofVegetationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Material_RoofVegetationFields>::value()); }
   private:
    friend class EnumBase<Material_RoofVegetationFields>;
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
{ Material_RoofVegetationFields::Name, "Name", "Name"},
{ Material_RoofVegetationFields::HeightofPlants, "HeightofPlants", "Height of Plants"},
{ Material_RoofVegetationFields::LeafAreaIndex, "LeafAreaIndex", "Leaf Area Index"},
{ Material_RoofVegetationFields::LeafReflectivity, "LeafReflectivity", "Leaf Reflectivity"},
{ Material_RoofVegetationFields::LeafEmissivity, "LeafEmissivity", "Leaf Emissivity"},
{ Material_RoofVegetationFields::MinimumStomatalResistance, "MinimumStomatalResistance", "Minimum Stomatal Resistance"},
{ Material_RoofVegetationFields::SoilLayerName, "SoilLayerName", "Soil Layer Name"},
{ Material_RoofVegetationFields::Roughness, "Roughness", "Roughness"},
{ Material_RoofVegetationFields::Thickness, "Thickness", "Thickness"},
{ Material_RoofVegetationFields::ConductivityofDrySoil, "ConductivityofDrySoil", "Conductivity of Dry Soil"},
{ Material_RoofVegetationFields::DensityofDrySoil, "DensityofDrySoil", "Density of Dry Soil"},
{ Material_RoofVegetationFields::SpecificHeatofDrySoil, "SpecificHeatofDrySoil", "Specific Heat of Dry Soil"},
{ Material_RoofVegetationFields::ThermalAbsorptance, "ThermalAbsorptance", "Thermal Absorptance"},
{ Material_RoofVegetationFields::SolarAbsorptance, "SolarAbsorptance", "Solar Absorptance"},
{ Material_RoofVegetationFields::VisibleAbsorptance, "VisibleAbsorptance", "Visible Absorptance"},
{ Material_RoofVegetationFields::SaturationVolumetricMoistureContentoftheSoilLayer, "SaturationVolumetricMoistureContentoftheSoilLayer", "Saturation Volumetric Moisture Content of the Soil Layer"},
{ Material_RoofVegetationFields::ResidualVolumetricMoistureContentoftheSoilLayer, "ResidualVolumetricMoistureContentoftheSoilLayer", "Residual Volumetric Moisture Content of the Soil Layer"},
{ Material_RoofVegetationFields::InitialVolumetricMoistureContentoftheSoilLayer, "InitialVolumetricMoistureContentoftheSoilLayer", "Initial Volumetric Moisture Content of the Soil Layer"},
{ Material_RoofVegetationFields::MoistureDiffusionCalculationMethod, "MoistureDiffusionCalculationMethod", "Moisture Diffusion Calculation Method"},
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
  inline std::ostream &operator<<(std::ostream &os, const Material_RoofVegetationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Material_RoofVegetationFields> OptionalMaterial_RoofVegetationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_MATERIAL_ROOFVEGETATION_FIELDENUMS_HXX
