/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_FOUNDATION_KIVA_SETTINGS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_FOUNDATION_KIVA_SETTINGS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Foundation_Kiva_SettingsFields
 *  \brief Enumeration of OS:Foundation:Kiva:Settings's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Foundation_Kiva_SettingsFields, )
#else
class OS_Foundation_Kiva_SettingsFields: public ::EnumBase<OS_Foundation_Kiva_SettingsFields> {
 public: 
  enum domain 
  {
Handle, SoilConductivity, SoilDensity, SoilSpecificHeat, GroundSolarAbsorptivity, GroundThermalAbsorptivity, GroundSurfaceRoughness, FarFieldWidth, DeepGroundBoundaryCondition, DeepGroundDepth, MinimumCellDimension, MaximumCellGrowthCoefficient, SimulationTimestep,   };
  OS_Foundation_Kiva_SettingsFields()
   : EnumBase<OS_Foundation_Kiva_SettingsFields>(Handle) {} 
  OS_Foundation_Kiva_SettingsFields(const std::string &t_name) 
   : EnumBase<OS_Foundation_Kiva_SettingsFields>(t_name) {} 
  OS_Foundation_Kiva_SettingsFields(int t_value) 
   : EnumBase<OS_Foundation_Kiva_SettingsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Foundation_Kiva_SettingsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Foundation_Kiva_SettingsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Foundation_Kiva_SettingsFields>;
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
{ OS_Foundation_Kiva_SettingsFields::Handle, "Handle", "Handle"},
{ OS_Foundation_Kiva_SettingsFields::SoilConductivity, "SoilConductivity", "Soil Conductivity"},
{ OS_Foundation_Kiva_SettingsFields::SoilDensity, "SoilDensity", "Soil Density"},
{ OS_Foundation_Kiva_SettingsFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ OS_Foundation_Kiva_SettingsFields::GroundSolarAbsorptivity, "GroundSolarAbsorptivity", "Ground Solar Absorptivity"},
{ OS_Foundation_Kiva_SettingsFields::GroundThermalAbsorptivity, "GroundThermalAbsorptivity", "Ground Thermal Absorptivity"},
{ OS_Foundation_Kiva_SettingsFields::GroundSurfaceRoughness, "GroundSurfaceRoughness", "Ground Surface Roughness"},
{ OS_Foundation_Kiva_SettingsFields::FarFieldWidth, "FarFieldWidth", "Far-Field Width"},
{ OS_Foundation_Kiva_SettingsFields::DeepGroundBoundaryCondition, "DeepGroundBoundaryCondition", "Deep-Ground Boundary Condition"},
{ OS_Foundation_Kiva_SettingsFields::DeepGroundDepth, "DeepGroundDepth", "Deep-Ground Depth"},
{ OS_Foundation_Kiva_SettingsFields::MinimumCellDimension, "MinimumCellDimension", "Minimum Cell Dimension"},
{ OS_Foundation_Kiva_SettingsFields::MaximumCellGrowthCoefficient, "MaximumCellGrowthCoefficient", "Maximum Cell Growth Coefficient"},
{ OS_Foundation_Kiva_SettingsFields::SimulationTimestep, "SimulationTimestep", "Simulation Timestep"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Foundation_Kiva_SettingsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Foundation_Kiva_SettingsFields> OptionalOS_Foundation_Kiva_SettingsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_FOUNDATION_KIVA_SETTINGS_FIELDENUMS_HXX
