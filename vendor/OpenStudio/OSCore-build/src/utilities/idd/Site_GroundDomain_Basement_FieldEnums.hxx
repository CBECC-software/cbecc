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

#ifndef UTILITIES_IDD_SITE_GROUNDDOMAIN_BASEMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_SITE_GROUNDDOMAIN_BASEMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Site_GroundDomain_BasementFields
 *  \brief Enumeration of Site:GroundDomain:Basement's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Site_GroundDomain_BasementFields, )
#else
class Site_GroundDomain_BasementFields: public ::EnumBase<Site_GroundDomain_BasementFields> {
 public: 
  enum domain 
  {
Name, GroundDomainDepth, AspectRatio, PerimeterOffset, SoilThermalConductivity, SoilDensity, SoilSpecificHeat, SoilMoistureContentVolumeFraction, SoilMoistureContentVolumeFractionatSaturation, UndisturbedGroundTemperatureModelType, UndisturbedGroundTemperatureModelName, EvapotranspirationGroundCoverParameter, BasementFloorBoundaryConditionModelName, HorizontalInsulation, HorizontalInsulationMaterialName, HorizontalInsulationExtents, PerimeterHorizontalInsulationWidth, BasementWallDepth, BasementWallBoundaryConditionModelName, VerticalInsulation, BasementWallVerticalInsulationMaterialName, VerticalInsulationDepth, SimulationTimestep, MeshDensityParameter,   };
  Site_GroundDomain_BasementFields()
   : EnumBase<Site_GroundDomain_BasementFields>(Name) {} 
  Site_GroundDomain_BasementFields(const std::string &t_name) 
   : EnumBase<Site_GroundDomain_BasementFields>(t_name) {} 
  Site_GroundDomain_BasementFields(int t_value) 
   : EnumBase<Site_GroundDomain_BasementFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_GroundDomain_BasementFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_GroundDomain_BasementFields>::value()); }
   private:
    friend class EnumBase<Site_GroundDomain_BasementFields>;
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
{ Site_GroundDomain_BasementFields::Name, "Name", "Name"},
{ Site_GroundDomain_BasementFields::GroundDomainDepth, "GroundDomainDepth", "Ground Domain Depth"},
{ Site_GroundDomain_BasementFields::AspectRatio, "AspectRatio", "Aspect Ratio"},
{ Site_GroundDomain_BasementFields::PerimeterOffset, "PerimeterOffset", "Perimeter Offset"},
{ Site_GroundDomain_BasementFields::SoilThermalConductivity, "SoilThermalConductivity", "Soil Thermal Conductivity"},
{ Site_GroundDomain_BasementFields::SoilDensity, "SoilDensity", "Soil Density"},
{ Site_GroundDomain_BasementFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ Site_GroundDomain_BasementFields::SoilMoistureContentVolumeFraction, "SoilMoistureContentVolumeFraction", "Soil Moisture Content Volume Fraction"},
{ Site_GroundDomain_BasementFields::SoilMoistureContentVolumeFractionatSaturation, "SoilMoistureContentVolumeFractionatSaturation", "Soil Moisture Content Volume Fraction at Saturation"},
{ Site_GroundDomain_BasementFields::UndisturbedGroundTemperatureModelType, "UndisturbedGroundTemperatureModelType", "Undisturbed Ground Temperature Model Type"},
{ Site_GroundDomain_BasementFields::UndisturbedGroundTemperatureModelName, "UndisturbedGroundTemperatureModelName", "Undisturbed Ground Temperature Model Name"},
{ Site_GroundDomain_BasementFields::EvapotranspirationGroundCoverParameter, "EvapotranspirationGroundCoverParameter", "Evapotranspiration Ground Cover Parameter"},
{ Site_GroundDomain_BasementFields::BasementFloorBoundaryConditionModelName, "BasementFloorBoundaryConditionModelName", "Basement Floor Boundary Condition Model Name"},
{ Site_GroundDomain_BasementFields::HorizontalInsulation, "HorizontalInsulation", "Horizontal Insulation"},
{ Site_GroundDomain_BasementFields::HorizontalInsulationMaterialName, "HorizontalInsulationMaterialName", "Horizontal Insulation Material Name"},
{ Site_GroundDomain_BasementFields::HorizontalInsulationExtents, "HorizontalInsulationExtents", "Horizontal Insulation Extents"},
{ Site_GroundDomain_BasementFields::PerimeterHorizontalInsulationWidth, "PerimeterHorizontalInsulationWidth", "Perimeter Horizontal Insulation Width"},
{ Site_GroundDomain_BasementFields::BasementWallDepth, "BasementWallDepth", "Basement Wall Depth"},
{ Site_GroundDomain_BasementFields::BasementWallBoundaryConditionModelName, "BasementWallBoundaryConditionModelName", "Basement Wall Boundary Condition Model Name"},
{ Site_GroundDomain_BasementFields::VerticalInsulation, "VerticalInsulation", "Vertical Insulation"},
{ Site_GroundDomain_BasementFields::BasementWallVerticalInsulationMaterialName, "BasementWallVerticalInsulationMaterialName", "Basement Wall Vertical Insulation Material Name"},
{ Site_GroundDomain_BasementFields::VerticalInsulationDepth, "VerticalInsulationDepth", "Vertical Insulation Depth"},
{ Site_GroundDomain_BasementFields::SimulationTimestep, "SimulationTimestep", "Simulation Timestep"},
{ Site_GroundDomain_BasementFields::MeshDensityParameter, "MeshDensityParameter", "Mesh Density Parameter"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_GroundDomain_BasementFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_GroundDomain_BasementFields> OptionalSite_GroundDomain_BasementFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SITE_GROUNDDOMAIN_BASEMENT_FIELDENUMS_HXX
