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
