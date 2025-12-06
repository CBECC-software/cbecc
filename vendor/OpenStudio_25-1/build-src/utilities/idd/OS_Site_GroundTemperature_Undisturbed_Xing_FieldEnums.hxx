/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_UNDISTURBED_XING_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_UNDISTURBED_XING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Site_GroundTemperature_Undisturbed_XingFields
 *  \brief Enumeration of OS:Site:GroundTemperature:Undisturbed:Xing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Site_GroundTemperature_Undisturbed_XingFields, )
#else
class OS_Site_GroundTemperature_Undisturbed_XingFields: public ::EnumBase<OS_Site_GroundTemperature_Undisturbed_XingFields> {
 public: 
  enum domain 
  {
Handle, Name, SoilThermalConductivity, SoilDensity, SoilSpecificHeat, AverageSoilSurfaceTemperature, SoilSurfaceTemperatureAmplitude1, SoilSurfaceTemperatureAmplitude2, PhaseShiftofTemperatureAmplitude1, PhaseShiftofTemperatureAmplitude2,   };
  OS_Site_GroundTemperature_Undisturbed_XingFields()
   : EnumBase<OS_Site_GroundTemperature_Undisturbed_XingFields>(Handle) {} 
  OS_Site_GroundTemperature_Undisturbed_XingFields(const std::string &t_name) 
   : EnumBase<OS_Site_GroundTemperature_Undisturbed_XingFields>(t_name) {} 
  OS_Site_GroundTemperature_Undisturbed_XingFields(int t_value) 
   : EnumBase<OS_Site_GroundTemperature_Undisturbed_XingFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Site_GroundTemperature_Undisturbed_XingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Site_GroundTemperature_Undisturbed_XingFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Site_GroundTemperature_Undisturbed_XingFields>;
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
{ OS_Site_GroundTemperature_Undisturbed_XingFields::Handle, "Handle", "Handle"},
{ OS_Site_GroundTemperature_Undisturbed_XingFields::Name, "Name", "Name"},
{ OS_Site_GroundTemperature_Undisturbed_XingFields::SoilThermalConductivity, "SoilThermalConductivity", "Soil Thermal Conductivity"},
{ OS_Site_GroundTemperature_Undisturbed_XingFields::SoilDensity, "SoilDensity", "Soil Density"},
{ OS_Site_GroundTemperature_Undisturbed_XingFields::SoilSpecificHeat, "SoilSpecificHeat", "Soil Specific Heat"},
{ OS_Site_GroundTemperature_Undisturbed_XingFields::AverageSoilSurfaceTemperature, "AverageSoilSurfaceTemperature", "Average Soil Surface Temperature"},
{ OS_Site_GroundTemperature_Undisturbed_XingFields::SoilSurfaceTemperatureAmplitude1, "SoilSurfaceTemperatureAmplitude1", "Soil Surface Temperature Amplitude 1"},
{ OS_Site_GroundTemperature_Undisturbed_XingFields::SoilSurfaceTemperatureAmplitude2, "SoilSurfaceTemperatureAmplitude2", "Soil Surface Temperature Amplitude 2"},
{ OS_Site_GroundTemperature_Undisturbed_XingFields::PhaseShiftofTemperatureAmplitude1, "PhaseShiftofTemperatureAmplitude1", "Phase Shift of Temperature Amplitude 1"},
{ OS_Site_GroundTemperature_Undisturbed_XingFields::PhaseShiftofTemperatureAmplitude2, "PhaseShiftofTemperatureAmplitude2", "Phase Shift of Temperature Amplitude 2"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Site_GroundTemperature_Undisturbed_XingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Site_GroundTemperature_Undisturbed_XingFields> OptionalOS_Site_GroundTemperature_Undisturbed_XingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_SITE_GROUNDTEMPERATURE_UNDISTURBED_XING_FIELDENUMS_HXX
