/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_UNDISTURBED_KUSUDAACHENBACH_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_UNDISTURBED_KUSUDAACHENBACH_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields
 *  \brief Enumeration of OS:Site:GroundTemperature:Undisturbed:KusudaAchenbach's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields, )
#else
class OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields: public ::EnumBase<OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields> {
 public: 
  enum domain 
  {
Handle, Name, SoilThermalConductivity, SoilDensity, SoilSpecificHeat, AverageSoilSurfaceTemperature, AverageAmplitudeofSurfaceTemperature, PhaseShiftofMinimumSurfaceTemperature,   };
  OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields()
   : EnumBase<OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields>(Handle) {} 
  OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields(const std::string &t_name) 
   : EnumBase<OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields>(t_name) {} 
  OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields(int t_value) 
   : EnumBase<OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields>;
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
{ OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::Handle, "Handle", "Handle"},
{ OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::Name, "Name", "Name"},
{ OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilThermalConductivity, "SoilThermalConductivity", "Soil Thermal Conductivity"},
{ OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilDensity, "SoilDensity", "Soil Density"},
{ OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::AverageSoilSurfaceTemperature, "AverageSoilSurfaceTemperature", "Average Soil Surface Temperature"},
{ OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::AverageAmplitudeofSurfaceTemperature, "AverageAmplitudeofSurfaceTemperature", "Average Amplitude of Surface Temperature"},
{ OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields::PhaseShiftofMinimumSurfaceTemperature, "PhaseShiftofMinimumSurfaceTemperature", "Phase Shift of Minimum Surface Temperature"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields> OptionalOS_Site_GroundTemperature_Undisturbed_KusudaAchenbachFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_UNDISTURBED_KUSUDAACHENBACH_FIELDENUMS_HXX
