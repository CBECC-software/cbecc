/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ENVIRONMENTALIMPACTFACTORS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ENVIRONMENTALIMPACTFACTORS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_EnvironmentalImpactFactorsFields
 *  \brief Enumeration of OS:EnvironmentalImpactFactors's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_EnvironmentalImpactFactorsFields, )
#else
class OS_EnvironmentalImpactFactorsFields: public ::EnumBase<OS_EnvironmentalImpactFactorsFields> {
 public: 
  enum domain 
  {
Handle, DistrictHeatingWaterEfficiency, DistrictCoolingCOP, DistrictHeatingSteamConversionEfficiency, TotalCarbonEquivalentEmissionFactorFromN2O, TotalCarbonEquivalentEmissionFactorFromCH4, TotalCarbonEquivalentEmissionFactorFromCO2,   };
  OS_EnvironmentalImpactFactorsFields()
   : EnumBase<OS_EnvironmentalImpactFactorsFields>(Handle) {} 
  OS_EnvironmentalImpactFactorsFields(const std::string &t_name) 
   : EnumBase<OS_EnvironmentalImpactFactorsFields>(t_name) {} 
  OS_EnvironmentalImpactFactorsFields(int t_value) 
   : EnumBase<OS_EnvironmentalImpactFactorsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_EnvironmentalImpactFactorsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_EnvironmentalImpactFactorsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_EnvironmentalImpactFactorsFields>;
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
{ OS_EnvironmentalImpactFactorsFields::Handle, "Handle", "Handle"},
{ OS_EnvironmentalImpactFactorsFields::DistrictHeatingWaterEfficiency, "DistrictHeatingWaterEfficiency", "District Heating Water Efficiency"},
{ OS_EnvironmentalImpactFactorsFields::DistrictCoolingCOP, "DistrictCoolingCOP", "District Cooling COP"},
{ OS_EnvironmentalImpactFactorsFields::DistrictHeatingSteamConversionEfficiency, "DistrictHeatingSteamConversionEfficiency", "District Heating Steam Conversion Efficiency"},
{ OS_EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromN2O, "TotalCarbonEquivalentEmissionFactorFromN2O", "Total Carbon Equivalent Emission Factor From N2O"},
{ OS_EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromCH4, "TotalCarbonEquivalentEmissionFactorFromCH4", "Total Carbon Equivalent Emission Factor From CH4"},
{ OS_EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromCO2, "TotalCarbonEquivalentEmissionFactorFromCO2", "Total Carbon Equivalent Emission Factor From CO2"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_EnvironmentalImpactFactorsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_EnvironmentalImpactFactorsFields> OptionalOS_EnvironmentalImpactFactorsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ENVIRONMENTALIMPACTFACTORS_FIELDENUMS_HXX
