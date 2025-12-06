/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_ENVIRONMENTALIMPACTFACTORS_FIELDENUMS_HXX
#define UTILITIES_IDD_ENVIRONMENTALIMPACTFACTORS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class EnvironmentalImpactFactorsFields
 *  \brief Enumeration of EnvironmentalImpactFactors's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(EnvironmentalImpactFactorsFields, )
#else
class EnvironmentalImpactFactorsFields: public ::EnumBase<EnvironmentalImpactFactorsFields> {
 public: 
  enum domain 
  {
DistrictHeatingWaterEfficiency, DistrictCoolingCOP, DistrictHeatingSteamConversionEfficiency, TotalCarbonEquivalentEmissionFactorFromN2O, TotalCarbonEquivalentEmissionFactorFromCH4, TotalCarbonEquivalentEmissionFactorFromCO2,   };
  EnvironmentalImpactFactorsFields()
   : EnumBase<EnvironmentalImpactFactorsFields>(DistrictHeatingWaterEfficiency) {} 
  EnvironmentalImpactFactorsFields(const std::string &t_name) 
   : EnumBase<EnvironmentalImpactFactorsFields>(t_name) {} 
  EnvironmentalImpactFactorsFields(int t_value) 
   : EnumBase<EnvironmentalImpactFactorsFields>(t_value) {} 
  static std::string enumName() 
  { return "EnvironmentalImpactFactorsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<EnvironmentalImpactFactorsFields>::integer_value()); }
   private:
    friend class EnumBase<EnvironmentalImpactFactorsFields>;
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
{ EnvironmentalImpactFactorsFields::DistrictHeatingWaterEfficiency, "DistrictHeatingWaterEfficiency", "District Heating Water Efficiency"},
{ EnvironmentalImpactFactorsFields::DistrictCoolingCOP, "DistrictCoolingCOP", "District Cooling COP"},
{ EnvironmentalImpactFactorsFields::DistrictHeatingSteamConversionEfficiency, "DistrictHeatingSteamConversionEfficiency", "District Heating Steam Conversion Efficiency"},
{ EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromN2O, "TotalCarbonEquivalentEmissionFactorFromN2O", "Total Carbon Equivalent Emission Factor From N2O"},
{ EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromCH4, "TotalCarbonEquivalentEmissionFactorFromCH4", "Total Carbon Equivalent Emission Factor From CH4"},
{ EnvironmentalImpactFactorsFields::TotalCarbonEquivalentEmissionFactorFromCO2, "TotalCarbonEquivalentEmissionFactorFromCO2", "Total Carbon Equivalent Emission Factor From CO2"},
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
  inline std::ostream &operator<<(std::ostream &os, const EnvironmentalImpactFactorsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<EnvironmentalImpactFactorsFields> OptionalEnvironmentalImpactFactorsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_ENVIRONMENTALIMPACTFACTORS_FIELDENUMS_HXX
