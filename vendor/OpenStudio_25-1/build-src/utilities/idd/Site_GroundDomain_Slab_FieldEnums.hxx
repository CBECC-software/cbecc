/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SITE_GROUNDDOMAIN_SLAB_FIELDENUMS_HXX
#define UTILITIES_IDD_SITE_GROUNDDOMAIN_SLAB_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Site_GroundDomain_SlabFields
 *  \brief Enumeration of Site:GroundDomain:Slab's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Site_GroundDomain_SlabFields, )
#else
class Site_GroundDomain_SlabFields: public ::EnumBase<Site_GroundDomain_SlabFields> {
 public: 
  enum domain 
  {
Name, GroundDomainDepth, AspectRatio, PerimeterOffset, SoilThermalConductivity, SoilDensity, SoilSpecificHeat, SoilMoistureContentVolumeFraction, SoilMoistureContentVolumeFractionatSaturation, UndisturbedGroundTemperatureModelType, UndisturbedGroundTemperatureModelName, EvapotranspirationGroundCoverParameter, SlabBoundaryConditionModelName, SlabLocation, SlabMaterialName, HorizontalInsulation, HorizontalInsulationMaterialName, HorizontalInsulationExtents, PerimeterInsulationWidth, VerticalInsulation, VerticalInsulationMaterialName, VerticalInsulationDepth, SimulationTimestep, GeometricMeshCoefficient, MeshDensityParameter,   };
  Site_GroundDomain_SlabFields()
   : EnumBase<Site_GroundDomain_SlabFields>(Name) {} 
  Site_GroundDomain_SlabFields(const std::string &t_name) 
   : EnumBase<Site_GroundDomain_SlabFields>(t_name) {} 
  Site_GroundDomain_SlabFields(int t_value) 
   : EnumBase<Site_GroundDomain_SlabFields>(t_value) {} 
  static std::string enumName() 
  { return "Site_GroundDomain_SlabFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Site_GroundDomain_SlabFields>::integer_value()); }
   private:
    friend class EnumBase<Site_GroundDomain_SlabFields>;
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
{ Site_GroundDomain_SlabFields::Name, "Name", "Name"},
{ Site_GroundDomain_SlabFields::GroundDomainDepth, "GroundDomainDepth", "Ground Domain Depth"},
{ Site_GroundDomain_SlabFields::AspectRatio, "AspectRatio", "Aspect Ratio"},
{ Site_GroundDomain_SlabFields::PerimeterOffset, "PerimeterOffset", "Perimeter Offset"},
{ Site_GroundDomain_SlabFields::SoilThermalConductivity, "SoilThermalConductivity", "Soil Thermal Conductivity"},
{ Site_GroundDomain_SlabFields::SoilDensity, "SoilDensity", "Soil Density"},
{ Site_GroundDomain_SlabFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ Site_GroundDomain_SlabFields::SoilMoistureContentVolumeFraction, "SoilMoistureContentVolumeFraction", "Soil Moisture Content Volume Fraction"},
{ Site_GroundDomain_SlabFields::SoilMoistureContentVolumeFractionatSaturation, "SoilMoistureContentVolumeFractionatSaturation", "Soil Moisture Content Volume Fraction at Saturation"},
{ Site_GroundDomain_SlabFields::UndisturbedGroundTemperatureModelType, "UndisturbedGroundTemperatureModelType", "Undisturbed Ground Temperature Model Type"},
{ Site_GroundDomain_SlabFields::UndisturbedGroundTemperatureModelName, "UndisturbedGroundTemperatureModelName", "Undisturbed Ground Temperature Model Name"},
{ Site_GroundDomain_SlabFields::EvapotranspirationGroundCoverParameter, "EvapotranspirationGroundCoverParameter", "Evapotranspiration Ground Cover Parameter"},
{ Site_GroundDomain_SlabFields::SlabBoundaryConditionModelName, "SlabBoundaryConditionModelName", "Slab Boundary Condition Model Name"},
{ Site_GroundDomain_SlabFields::SlabLocation, "SlabLocation", "Slab Location"},
{ Site_GroundDomain_SlabFields::SlabMaterialName, "SlabMaterialName", "Slab Material Name"},
{ Site_GroundDomain_SlabFields::HorizontalInsulation, "HorizontalInsulation", "Horizontal Insulation"},
{ Site_GroundDomain_SlabFields::HorizontalInsulationMaterialName, "HorizontalInsulationMaterialName", "Horizontal Insulation Material Name"},
{ Site_GroundDomain_SlabFields::HorizontalInsulationExtents, "HorizontalInsulationExtents", "Horizontal Insulation Extents"},
{ Site_GroundDomain_SlabFields::PerimeterInsulationWidth, "PerimeterInsulationWidth", "Perimeter Insulation Width"},
{ Site_GroundDomain_SlabFields::VerticalInsulation, "VerticalInsulation", "Vertical Insulation"},
{ Site_GroundDomain_SlabFields::VerticalInsulationMaterialName, "VerticalInsulationMaterialName", "Vertical Insulation Material Name"},
{ Site_GroundDomain_SlabFields::VerticalInsulationDepth, "VerticalInsulationDepth", "Vertical Insulation Depth"},
{ Site_GroundDomain_SlabFields::SimulationTimestep, "SimulationTimestep", "Simulation Timestep"},
{ Site_GroundDomain_SlabFields::GeometricMeshCoefficient, "GeometricMeshCoefficient", "Geometric Mesh Coefficient"},
{ Site_GroundDomain_SlabFields::MeshDensityParameter, "MeshDensityParameter", "Mesh Density Parameter"},
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
  inline std::ostream &operator<<(std::ostream &os, const Site_GroundDomain_SlabFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Site_GroundDomain_SlabFields> OptionalSite_GroundDomain_SlabFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SITE_GROUNDDOMAIN_SLAB_FIELDENUMS_HXX
