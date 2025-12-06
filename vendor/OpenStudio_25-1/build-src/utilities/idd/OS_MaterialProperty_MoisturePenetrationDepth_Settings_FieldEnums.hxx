/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_MATERIALPROPERTY_MOISTUREPENETRATIONDEPTH_SETTINGS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_MATERIALPROPERTY_MOISTUREPENETRATIONDEPTH_SETTINGS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields
 *  \brief Enumeration of OS:MaterialProperty:MoisturePenetrationDepth:Settings's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields, )
#else
class OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields: public ::EnumBase<OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields> {
 public: 
  enum domain 
  {
Handle, MaterialName, WaterVaporDiffusionResistanceFactor, MoistureEquationCoefficienta, MoistureEquationCoefficientb, MoistureEquationCoefficientc, MoistureEquationCoefficientd, SurfaceLayerPenetrationDepth, DeepLayerPenetrationDepth, CoatingLayerThickness, CoatingLayerWaterVaporDiffusionResistanceFactor,   };
  OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields()
   : EnumBase<OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields>(Handle) {} 
  OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields(const std::string &t_name) 
   : EnumBase<OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields>(t_name) {} 
  OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields(int t_value) 
   : EnumBase<OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields>;
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
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::Handle, "Handle", "Handle"},
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::MaterialName, "MaterialName", "Material Name"},
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::WaterVaporDiffusionResistanceFactor, "WaterVaporDiffusionResistanceFactor", "Water Vapor Diffusion Resistance Factor"},
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficienta, "MoistureEquationCoefficienta", "Moisture Equation Coefficient a"},
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientb, "MoistureEquationCoefficientb", "Moisture Equation Coefficient b"},
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientc, "MoistureEquationCoefficientc", "Moisture Equation Coefficient c"},
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::MoistureEquationCoefficientd, "MoistureEquationCoefficientd", "Moisture Equation Coefficient d"},
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::SurfaceLayerPenetrationDepth, "SurfaceLayerPenetrationDepth", "Surface Layer Penetration Depth"},
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::DeepLayerPenetrationDepth, "DeepLayerPenetrationDepth", "Deep Layer Penetration Depth"},
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::CoatingLayerThickness, "CoatingLayerThickness", "Coating Layer Thickness"},
{ OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields::CoatingLayerWaterVaporDiffusionResistanceFactor, "CoatingLayerWaterVaporDiffusionResistanceFactor", "Coating Layer Water Vapor Diffusion Resistance Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_MaterialProperty_MoisturePenetrationDepth_SettingsFields> OptionalOS_MaterialProperty_MoisturePenetrationDepth_SettingsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_MATERIALPROPERTY_MOISTUREPENETRATIONDEPTH_SETTINGS_FIELDENUMS_HXX
